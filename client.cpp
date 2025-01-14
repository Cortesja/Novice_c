#include <Novice.h>
#include <cmath>
#include <process.h>
#include <mmsystem.h>
#include <string>
#include <memory>
#include <fstream>

#pragma comment(lib,"wsock32.lib")
#pragma comment(lib, "winmm.lib")

#include  "assets/Player.h"
#include  "assets/myStructs.h"

DWORD WINAPI Threadfunc(void*);

SOCKET sWait;
bool bSocket = false;
HWND hwMain;

const char kWindowTitle[] = "クライアント";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

bool ChkCollision(const Circle player, const Circle fixed) {
	float dx = fixed.pos.x - player.pos.x;
	float dy = fixed.pos.y - player.pos.y;
	float distance = std::sqrtf(powf(dx, 2) + (powf(dy, 2)));
	return distance <= (player.radius + fixed.radius);
}

std::unique_ptr<Player> player = nullptr;
std::unique_ptr<Player> player2 = nullptr;

//Circle構造体をよい
Circle player2_;
//Player用のCirlce構造体
Circle player_;

// キー入力結果を受け取る箱
char keys[256] = { 0 };
char preKeys[256] = { 0 };

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WSADATA wdData;
	static HANDLE hThread;
	static DWORD dwID;

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	hwMain = GetDesktopWindow();
	// winsock初期化
	WSAStartup(MAKEWORD(2, 0), &wdData);

	//スレッド制作
	hThread = (HANDLE)CreateThread(NULL, 0, &Threadfunc, (LPVOID)&player2_, 0, &dwID);

	//プレイヤーの初期化
	player = std::make_unique<Player>();
	player2 = std::make_unique<Player>();

	player->Initialize({200,100}, 25.0f, 0xFFFFFFFF, 5.0f);
	player2->Initialize({ kWindowWidth / 2, kWindowHeight / 2 }, 50.0f, 0xFF0000FF, 2.0f);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		player->Update();
		//サーバーのグローバル変数にplayerの位置を代入
		player_ = player->GetPlayer();

		if (ChkCollision(player_, player2_)) {
			player->SetColor(0x0000FFFF);
		}
		else {
			player->SetColor(0xFFFFFFFF);
		}

		
		player2->SetPos(player2_);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		player2->Draw();
		player->Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();

	//winsock終了
	WSACleanup();

	return 0;
}

/* 通信スレッド関数 */
DWORD WINAPI Threadfunc(void*) {

	int sock = (int)socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addr;
	u_short wPort = 8000;
	char serverName[20];

	// リスンソケット
	ZeroMemory(&addr, sizeof(addr));

	std::ifstream ifs("ip.txt");
	ifs.getline(serverName, sizeof(serverName));

	HOSTENT* IpHost;
	unsigned int tempAddr;
	IpHost = gethostbyname(serverName);
	if (IpHost == NULL) {
		tempAddr = inet_addr(serverName);
		IpHost = gethostbyaddr((char*)&addr, 4, AF_INET);
	}
	if (IpHost == NULL) {
		SetWindowText(hwMain, L"Hostが見つけられません");
		closesocket(sock);
		return 1;
	}

	// 8000番に接続待機用ソケット作成
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = IpHost->h_addrtype;
	addr.sin_addr.s_addr = *((u_long*)IpHost->h_addr);
	addr.sin_port = htons(wPort);

	SetWindowText(hwMain, L"接続待機ソケット成功");

	int fromlen = (int)sizeof(addr);

	while (1)
	{
		// サーバ側キャラの位置情報を送信
		sendto(sock, (const char*)&player_, sizeof(player_), 0, (struct sockaddr*)&addr, sizeof(addr));

		// クライアント側キャラの位置情報を受け取り
		recvfrom(sock, (char*)&player2_, sizeof(player2_), 0, (struct sockaddr*)&addr, &fromlen);
	}

	shutdown(sock, 2);
	closesocket(sock);

	return 0;
}
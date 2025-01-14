#pragma once

#include <Novice.h>
#include <cmath>
#include <process.h>
#include <mmsystem.h>
#include <string>
#include <memory>

#pragma comment(lib,"wsock32.lib")
#pragma comment(lib, "winmm.lib")

#include "assets/Player.h"


class GameManager {
public: 
	GameManager() = default;
	~GameManager() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// while��
	/// </summary>
	void GameLoop();

	void InitializeThread();

	/// <summary>
	/// 
	/// </summary>
	void ThreadLoop();

public:
	bool ChkCollision(const Circle player, const Circle fixed);

private:
	//const char kWindowTitle[] = "�N���C�A���g";
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;


	std::unique_ptr<Player> player = nullptr;
	std::unique_ptr<Player> fixed = nullptr;

	Circle fixed_;
	Circle player_;

	// �L�[���͌��ʂ��󂯎�锠
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	HWND hwMain;
};
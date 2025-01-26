#include "Player.h"
#include "Novice.h"

void Player::Initialize(Pos pos, float radius, int color, float speed) {
	player_.pos = pos;
	player_.radius = radius;
	player_.color = color;
	speed_ = speed;
	reboundSpeed_ = 50.0f;
}

void Player::Update() {
	PlayerMove();
	ChangeType();
	if (player_.points >= 3) {
		player_.win = true;
	}
}

void Player::Draw(int x) {

	int kWindowWidth = 1280;
	int kWindowHeight = 720;

	Novice::DrawEllipse((int)player_.pos.x, (int)player_.pos.y, (int)player_.radius, (int)player_.radius, 0.0f, player_.color, kFillModeSolid);
	if(x == 1){
	Novice::ScreenPrintf(50, 700, "Score: %d", player_.points);
		if (player_.win) {
			Novice::ScreenPrintf(kWindowWidth / 2, kWindowHeight / 2, "Player1 Wins");
		}
	}
	else {
		Novice::ScreenPrintf(900, 700, "Score: %d", player_.points);
		if (player_.win) {
			Novice::ScreenPrintf(kWindowWidth / 2, kWindowHeight / 2, "Player2 Wins");
		}
	}
}

void Player::PlayerMove() {
	if (Novice::CheckHitKey(DIK_UP)) {
		player_.pos.y -= speed_;
	}
	if (Novice::CheckHitKey(DIK_DOWN)) {
		player_.pos.y += speed_;
	}
	if (Novice::CheckHitKey(DIK_LEFT)) {
		player_.pos.x -= speed_;
	}
	if (Novice::CheckHitKey(DIK_RIGHT)) {
		player_.pos.x += speed_;
	}
}

void Player::ChangeType() {
	if (Novice::CheckHitKey(DIK_1)) {
		style_ = Style::kRock;
	}
	if (Novice::CheckHitKey(DIK_2)) {
		style_ = Style::kPaper;
	}
	if (Novice::CheckHitKey(DIK_3)) {
		style_ = Style::kScissors;
	}

	switch (style_) {
	case Style::kRock:
		player_.color = 0xAA0000FF;
		break;
	case Style::kPaper:
		player_.color = 0x00AA00FF;
		break;
	case Style::kScissors:
		player_.color = 0x0000AAFF;
		break;
	}

}

void Player::SetReboundSpeedDirection(int plusMinus) {
	if (plusMinus > 0) {
		reboundSpeed_ = 50.0f;
	}
	else {
		reboundSpeed_ = -50.0f;
	}
}

void Player::Rebound() {
	player_.pos.x += reboundSpeed_;
}

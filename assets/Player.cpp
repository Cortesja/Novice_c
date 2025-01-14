#include "Player.h"
#include "Novice.h"

void Player::Initialize(Pos pos, float radius, int color, float speed){
	player_.pos = pos;
	player_.radius = radius;
	color_ = color;
	speed_ = speed;
}

void Player::Update(){
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

void Player::Draw(){
	Novice::DrawEllipse((int)player_.pos.x, (int)player_.pos.y, (int)player_.radius, (int)player_.radius, 0.0f, color_, kFillModeSolid);
}

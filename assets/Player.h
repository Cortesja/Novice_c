#pragma once
#include "assets/myStructs.h"

class Player {
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="radius"></param>
	/// <param name="color"></param>
	/// <param name="speed"></param>
	void Initialize(Pos pos, float radius, int color, float speed);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 円の情報ゲッター
	/// </summary>
	/// <param name="player"></param>
	/// <param name="fixed"></param>
	Circle GetPlayer() { return player_; }

	/// <summary>
	/// セッター
	/// </summary>
	/// <param name="currentPos"></param>
	void SetPos(Circle currentPos) { player_ = currentPos; }

	/// <summary>
	/// 色セッター
	/// </summary>
	/// <param name="color"></param>
	void SetColor(int color) { color_ = color; }

private:
	Circle player_;
	unsigned int color_;
	float speed_;
};
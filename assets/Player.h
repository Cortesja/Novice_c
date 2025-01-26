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
	/// XV
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw(int x);

	/// <summary>
	/// ‰~‚Ìî•ñƒQƒbƒ^[
	/// </summary>
	/// <param name="player"></param>
	/// <param name="fixed"></param>
	Circle GetPlayer() { return player_; }

	/// <summary>
	/// ƒZƒbƒ^[
	/// </summary>
	/// <param name="currentPos"></param>
	void SetPos(Circle currentPos) { player_ = currentPos; }

	/// <summary>
	/// ゲッター
	/// </summary>
	/// <returns></returns>
	Pos GetPos() { return player_.pos; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	unsigned int GetColor() { return player_.color; }

	/// <summary>
	/// FƒZƒbƒ^[
	/// </summary>
	/// <param name="color"></param>
	void SetColor(int color) { player_.color = color; }

	int GetPoints() { return player_.points; }

	void SetPoints(int points) { player_.points = points + 1; }


	/// <summary>
	/// プレイヤーの移動操作
	/// </summary>
	void PlayerMove();

	/// <summary>
	/// 形を変える操作
	/// </summary>
	void ChangeType();

	void SetReboundSpeedDirection(int plusMinus);

	void Rebound();

	Style GetStyle() { return style_; }

private:
	Circle player_;
	float speed_;
	float reboundSpeed_;

	Style style_ = Style::kRock;
};
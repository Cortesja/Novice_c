#pragma once
#include <cmath>

enum class Result {
	kDraw,
	kPlayer1,
	kPlayer2
};

enum class Style {
	kRock,
	kPaper,
	kScissors,
	kShapeNum
};

struct Pos {
	float x;
	float y;
};

struct Circle {
	Pos pos;
	float radius;
	unsigned int color;
	int points;
	bool win = false;
	Style style = Style::kRock;
};
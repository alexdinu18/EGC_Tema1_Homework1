#pragma once
#include "Framework/Rectangle2D.h"
#include "Framework/Transform2D.h"

#define PI 3.14159265358979323846

const float PLAYER_HEIGHT = 50.0;
const float PLAYER_WIDTH = 50.0;

class Player {
public:
	float x, y;
	float step, angle;
	bool jmp;
	bool move_up;
	bool land_on_platform;
	Rectangle2D *body, *mouth, *eye1, *eye2;
	Point2D center;

	Player(float x, float y);
	bool collision_detector(Object2D* obstacle);
	void jump();
	~Player();
private:
	void update_center();
};
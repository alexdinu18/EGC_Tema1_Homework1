#include "Framework/Player.h"
#include <iostream>
#include "Framework/DrawingWindow.h"

bool first_rot=true;
float step1 = 0.0;

Player::Player(float x, float y) {
	this->x = (float)x;
	this->y = (float)y;
	move_up = false;
	jmp = false;
	land_on_platform = false;
	step = 0;
	angle = 0;
	body = new Rectangle2D(Point2D(x, y), PLAYER_WIDTH, PLAYER_HEIGHT, Color(0,255,0), true);
	mouth = new Rectangle2D(Point2D(x + PLAYER_WIDTH / 6, y + PLAYER_HEIGHT / 6), 2 * PLAYER_WIDTH / 3, PLAYER_HEIGHT / 6, Color(0,0,0), true);
	eye1 = new Rectangle2D(Point2D(x + PLAYER_WIDTH / 6, y + 2 * PLAYER_HEIGHT / 3), PLAYER_WIDTH / 6, PLAYER_HEIGHT / 6, Color(0,255,255), true);
	eye2 = new Rectangle2D(Point2D(x + 2 * PLAYER_WIDTH / 3, y + 2 * PLAYER_HEIGHT / 3), PLAYER_WIDTH / 6, PLAYER_HEIGHT / 6, Color(0,255,255), true);
	update_center();
}

void Player::jump() {
	update_center();
	if(jmp) {
		if(!step) {
			move_up = true;
		}
		
		
		// rotatie in jurul centrului patratului
		angle -= PI / 24;
		if(step >= 120){
			move_up = false;
		}

		if (move_up) {
			step += 5.0;
			y += 5.0;
		}
		else {
			if (land_on_platform) {
				jmp = false;
				step = 0;
			}
			else {
				y -= 5.0;
				step -= 5.0;
			}
			
		}

		if (!step)
			jmp = false;
		
		Transform2D::loadIdentityMatrix();
		//Transform2D::translateMatrix(x-75, -y);
		//Transform2D::rotateMatrix(angle);
		//Transform2D::translateMatrix(center.x, center.y);
		Transform2D::translateMatrix(x-75,y);
		Transform2D::applyTransform(body);
		Transform2D::applyTransform(mouth);
		Transform2D::applyTransform(eye1);
		Transform2D::applyTransform(eye2);

	}
} 

bool Player::collision_detector(Object2D* obstacle) {

	// triunghiul se aproximeazã cu un dreptunghi
	if (obstacle->type == 4) {
		float x1, x2, y1, y2;
		x1 = obstacle->points[0]->x;
		y1 = obstacle->points[0]->y;
		x2 = obstacle->points[1]->x;
		y2 = obstacle->points[2]->y;

		// coliziune frontalã
		if (x + PLAYER_WIDTH > x1) {

			if (x2 > x) {
				if (y < y2) {
					return true;
				}
			}
		}

	}

	// cercuri
	if (obstacle->type == 3) {
		float x1, x2, y1, y2;
		x1 = obstacle->points[0]->x - 20;
		y1 = obstacle->points[0]->y - 10;
		x2 = obstacle->points[0]->x;
		y2 = obstacle->points[0]->y + 10;

		if (x + PLAYER_WIDTH >= x1) {

			if (x2 >= x) {
				if (y <= y2) {
					jmp = true;
					return true;
				}
			}
		}
	}
	
	// platforme
	if (obstacle->type == 2) {
		float x1, x2, y1, y2;
		x1 = obstacle->points[0]->x;
		y1 = obstacle->points[0]->y;
		x2 = obstacle->points[2]->x;
		y2 = obstacle->points[2]->y;
		if (x + PLAYER_WIDTH >= x1) {
			if (x2 >= x) {
				if (y2 <= y && y < y2 + 5) {
					land_on_platform = true;
					y = y2;
					return true;
				}
				if (y < y2 && y + PLAYER_HEIGHT > y1) {
					land_on_platform = false;
					return true;
				}
			}
		}
	}
	
	// steaguri
	if (obstacle->type == 1) {
		
		float x1, x2, y1, y2;
		x1 = obstacle->points[0]->x;
		y1 = obstacle->points[0]->y;
		x2 = obstacle->points[1]->x;
		y2 = obstacle->points[1]->y;
		if (x + PLAYER_WIDTH >= x1) {
			if (x2 >= x) {
				if (y1 <= y && y <=y2){
					return true;
				}
			}
		}
	}
	return false;
}

void Player::update_center() {
	center.x = x + PLAYER_WIDTH / 2;
	center.y = y + PLAYER_HEIGHT / 2;
}

Player::~Player() {
	delete body;
	delete mouth;
	delete eye1;
	delete eye2;
}
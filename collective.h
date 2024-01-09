#pragma once
#include <iostream>
#include "game.h" 
#include "collidable.h"


using namespace std;
enum PowerTypes { fireball, WindGlade, widePaddel, narrowPaddel, Magnet, MultipleBalls, Quicksand, ReverseDirection };
class collective : public collidable
{

	float vy;
	point z;
	int radius;
	PowerTypes Type;
public:
	collective(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void NewPosition();
	void print();
	~collective();
	void collisionAction();//override ;
	void CheckCollision();
	PowerTypes  get_type();
};
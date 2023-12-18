#pragma once
#include"collidable.h"
#include "gameConfig.h"
#include<iostream>
using namespace std;



class ball : public collidable
{
	int radius = 10;

	double deflection = rand() % 47;

	int Xinc = radius * 3 * cos(deflection* ( 3.1415 /180));
	int Yinc = radius * 3 * cos(deflection * (3.1415 / 180));

public:
	ball(point r_uprleft, int r_width, int r_height, game* r_pGame);

	void collisionAction() override;

	void draw() const;
	void move();
	void setPoint(point p);

	

};


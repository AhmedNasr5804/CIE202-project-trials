#pragma once
#include "collidable.h"
#include "gameConfig.h"
#include "CMUgraphicsLib/auxil.h"



class ball : public collidable
{
private:

	int radius = 10;
	int Xinc = 5;
	int Yinc = 5;
	point PrevUprL;

protected:
	collisionData info;
	

public:
	ball(point r_uprleft, int r_width, int r_height, game* r_pGame);
	~ball();
	void ballstart();
	void balldraw();
	void setYinc(int y);
	void setXinc(int x);
	void setYinc(float y);
	void setXinc(float x);
	void stop();
	void collisionAction();
	collisionData checkCollision(collidable* obj);
};


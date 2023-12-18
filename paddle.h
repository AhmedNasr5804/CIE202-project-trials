#pragma once
#include "collidable.h"

class paddle: public collidable
{
	point paddlePos;
public:
	paddle(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction() override;
	point getPoint() const;
	void setPoint(point p);

	void move_paddle();
};


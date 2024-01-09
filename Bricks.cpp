#include "Bricks.h"
#include "game.h"
#include "gameConfig.h"


////////////////////////////////////////////////////  class brick  ///////////////////////////////////////
brick::brick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	collidable(r_uprleft, r_width, r_height, r_pGame)
{
}

BrickType brick::getType()
{
	return bt;
}

void brick::setType(BrickType brk)
{
	bt = brk;
}

int brick::getStrength()
{
	return strenth;
}

void brick::setStrength(int s)
{
	strenth = s;
}

void brick::decStrength()
{
	strenth--;
}

BrickType brick::getbricktype() const
{
	return bt;
}

point brick::getPoint()
{
	return uprLft;
}

int brick::On_Collision()
{
	strenth--;
	return strenth;
}

void brick::collisionAction()
{
}

////////////////////////////////////////////////////  class normalBrick  /////////////////////////////////
normalBrick::normalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\bricks\\NormalBrick.jpg";
	setType(BRK_NRM);
	setStrength(1);
}

void normalBrick::collisionAction()
{
	auto collide = isColliding(this, pGame->getBall());

	if(collide.collision)
	{
		if (this->getStrength() > 0)
		{
			this->decStrength();
			config.scores++;
		}
		else
		{
			pGame->getGrid()->destroy(this);
		}
	}
}



////////////////////////////////////////////////////  class hardBrick  /////////////////////////////////
hardBrick::hardBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\Bricks\\AHardBrick.jpg";
	setType(BRK_HRD);
	setStrength(3);
}

void hardBrick::collisionAction()
{
	auto collide = isColliding(this, pGame->getBall());

	if (collide.collision)
	{
		if (this->getStrength() > 0)
		{
			this->decStrength();
			config.scores++;
		}
		else
		{
			pGame->getGrid()->destroy(this);
		}
	}
}


////////////////////////////////////////////////////  class bombBrick  /////////////////////////////////
bombBrick::bombBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\ToolbarIcons\\BombBrickIcon.jpeg";
	setStrength(1);
	setType(BRK_BOMB);
}


void bombBrick::collisionAction()
{
	auto collide = isColliding(this, pGame->getBall());

	if (collide.collision)
	{
		if (this->getStrength() > 0)
		{
			this->decStrength();
			config.scores++;
		}
		else
		{
			pGame->getGrid()->destroy(this);
			config.scores++;

		}
	}
}


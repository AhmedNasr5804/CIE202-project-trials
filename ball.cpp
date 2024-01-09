#include "ball.h"

#include "game.h"

ball::ball(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	collidable(r_uprleft, r_width, r_height, r_pGame)
{
	pWind = pGame->getWind();
}

ball::~ball()
{
	pGame->getGrid()->draw();
	pWind->SetBrush(config.bkGrndColor);
	pWind->SetPen(config.bkGrndColor);
	pWind->DrawCircle(config.ballrectX1 + config.ballRadius, config.ballrectY1 + config.ballRadius, config.ballRadius);
}

void ball::ballstart()
{
	grid = pGame->getGrid();
	pWind = pGame->getWind();
	pWind->SetBrush(config.bkGrndColor);
	pWind->SetPen(config.bkGrndColor);
	paddle* p = pGame->getPaddle();

	PrevUprL.x = config.ballrectX1 - Xinc;
	PrevUprL.y = config.ballrectY1 + Yinc;


	pWind->DrawCircle((PrevUprL.x + config.ballRadius), (PrevUprL.y + config.ballRadius), config.ballRadius);

	config.ballrectX1 += Xinc;
	config.ballrectX2 += Xinc;
	config.ballrectY1 -= Yinc;
	config.ballrectY2 -= Yinc;


	if (config.ballrectY1 <= config.gridHeight + config.toolBarHeight) {
		int rows = grid->getrows();
		int columns = grid->getcols();
		brick*** BricksMatrix = grid->getBrickMatrix();
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				if (checkCollision(BricksMatrix[i][j]).collision) {
					grid->destroy(BricksMatrix[i][j]);
					if (config.ballrectY1 == checkCollision(BricksMatrix[i][j]).collisionPoint.y || config.ballrectY2 == checkCollision(BricksMatrix[i][j]).collisionPoint.y) {
						setYinc(-Yinc);
					}
					if (config.ballrectX1 == checkCollision(BricksMatrix[i][j]).collisionPoint.x || config.ballrectX2 == checkCollision(BricksMatrix[i][j]).collisionPoint.x) {
						setXinc(-Xinc);
					}
					
					grid->destroy(BricksMatrix[i][j]);
					grid->draw();

					//}
				}
			}
		}
	}

	if (config.ballrectY2 == config.paddleAreaHeight && config.ballrectX1 >= p->getPoint().x && config.ballrectX2 <= p->getPoint().x + config.paddleWidth) 
	{
		setYinc(-Yinc);
	}




	if (config.ballrectY1 >= p->getPoint().y) {
		pWind->SetBrush(config.bkGrndColor);
		pWind->SetPen(config.bkGrndColor);
		pWind->DrawRectangle(0, config.paddleAreaHeight, config.windWidth, config.windHeight - config.statusBarHeight);
		config.ballrectX1 = (config.windWidth / 2) - (config.ballRadius);
		config.ballrectX2 = config.ballrectX1 + config.ballRadius * 2;
		config.ballrectY1 = config.paddleAreaHeight - config.ballRadius * 2;
		config.ballrectY2 = config.ballrectY1 + config.ballRadius * 2;
		//pGame->setmode(MODE_PLAY);
		point PP = { (config.windWidth / 2) - (config.paddleWidth / 2) , config.paddleAreaHeight };
		p->setPoint(PP);
		this->draw();
		p->draw();
		pWind->FlushKeyQueue();
		keytype Q;
		char Cha;
		Q = pWind->WaitKeyPress(Cha);
		if (Q == ASCII && Cha == ' ') {
			setXinc(5);
			setYinc(5);
			pWind->SetBrush(config.gridLinesColor);
			pWind->SetPen(config.gridLinesColor);
			pGame->getGrid()->draw();
		}

	}


	if (config.ballrectX2 >= config.windWidth - 10) {
		setXinc(-Xinc);
	}
	if (config.ballrectX1 <= 0) {
		setXinc(-Xinc);
	}
	if (config.ballrectY2 >= config.windHeight - config.statusBarHeight - 5) {
		setYinc(-Yinc);
	}
	if (config.ballrectY1 <= config.toolBarHeight + 10) {
		setYinc(-Yinc);
	}




	this->draw();
	pGame->getGrid()->draw();
	p->draw();
	Pause(20);
	pWind->UpdateBuffer();
}

void ball::balldraw()
{
	pWind = pGame->getWind();
	pWind->SetPen(config.bkGrndColor);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(config.ballrectX1, config.ballrectY1, config.ballrectX2, config.ballrectY2);
	pWind->SetPen(NAVYBLUE);
	pWind->SetBrush(NAVYBLUE);
	pWind->DrawCircle(config.ballrectX1 + config.ballRadius, config.ballrectY1 + config.ballRadius, config.ballRadius);
}

void ball::setYinc(int y)
{
	Yinc = y;
}

void ball::setXinc(int x)
{
	Xinc = x;
}

void ball::setYinc(float y)
{
	Yinc = y;
}

void ball::setXinc(float x)
{
	Xinc = x;
}

void ball::stop()
{
	setXinc(0);
	setYinc(0);
}

void ball::collisionAction()
{
	//to be done
}

collidable::collisionData ball::checkCollision(collidable* obj)
{
	info.collision = false;
	if (obj != nullptr) {
		int objLeft = obj->getPoint().x;
		int objRight = objLeft + config.brickWidth;
		int objTop = obj->getPoint().y;
		int objBot = objTop + config.brickHeight;

		int left = config.ballrectX1;
		int right = config.ballrectX2;
		int top = config.ballrectY1;
		int bot = config.ballrectY2;

		point center = { left + (config.ballRadius), top + (config.ballRadius) };

		//Check if bounding boxes overlap for left or right sides
		//calculating the collision point(x, y)



		if (objLeft == right) {
			if (objTop >= top && objTop <= bot) {
				info.collision = true;
				info.collisionPoint.x = objLeft;
				info.collisionPoint.y = objTop + ((bot - objTop) / 2);
			}
			else if (objBot >= top && objBot <= bot) {
				info.collision = true;
				info.collisionPoint.x = objLeft;
				info.collisionPoint.y = top + ((objBot - top) / 2);
			}
			else if (objTop <= top && objBot >= bot) {

				info.collision = true;
				info.collisionPoint.x = objLeft;
				info.collisionPoint.y = top + ((bot - top) / 2);
			}
		}




		if (objRight == left) {
			if (objTop >= top && objTop <= bot) {
				info.collision = true;
				info.collisionPoint.x = objRight;
				info.collisionPoint.y = objTop + ((bot - objTop) / 2);
			}
			else if (objBot >= top && objBot <= bot) {
				info.collision = true;
				info.collisionPoint.x = objRight;
				info.collisionPoint.y = top + ((objBot - top) / 2);
			}
			else if (objTop <= top && objBot >= bot) {
				info.collision = true;
				info.collisionPoint.x = objRight;
				info.collisionPoint.y = top + ((bot - top) / 2);
			}
		}


		if (objBot == top) {
			if (objRight >= left && objRight <= right) {
				info.collision = true;
				info.collisionPoint.x = objLeft + ((objRight - left) / 2);
				info.collisionPoint.y = objBot;
			}
			else if (left <= objLeft && right >= objLeft) {
				info.collision = true;
				info.collisionPoint.x = left + ((objLeft - left) / 2);
				info.collisionPoint.y = objBot;
			}
			else if (left >= objLeft && right <= objRight) {
				info.collision = true;
				info.collisionPoint.x = left + ((right - left) / 2);
				info.collisionPoint.y = objBot;
			}
			else if (center.x == objLeft) {
				info.collision = true;
				info.collisionPoint.y = objBot;
			}
			else if (center.x == objRight) {
				info.collision = true;
				info.collisionPoint.y = objBot;
			}
		}

		if (objTop == bot) {
			if (objRight >= left && objRight <= right) {
				info.collision = true;
				info.collisionPoint.x = objLeft + ((objRight - left) / 2);
				info.collisionPoint.y = objTop;
			}
			else if (left <= objLeft && right >= objLeft) {
				info.collision = true;
				info.collisionPoint.x = left + ((objLeft - left) / 2);
				info.collisionPoint.y = objTop;
			}
			else if (left >= objLeft && right <= objRight) {
				info.collision = true;
				info.collisionPoint.x = left + ((right - left) / 2);
				info.collisionPoint.y = objTop;
			}
			else if (center.x == objLeft) {
				info.collision = true;
				info.collisionPoint.y = objTop;
			}
			else if (center.x == objRight) {
				info.collision = true;
				info.collisionPoint.y = objTop;
			}
		}
	}
	return info;
}







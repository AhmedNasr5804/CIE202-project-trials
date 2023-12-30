#include "ball.h"

#include "game.h"

ball::ball(point r_uprleft, int r_width, int r_height, game* r_pGame):
	collidable(r_uprleft, r_width, r_height, r_pGame)
{

}

void ball::collisionAction()
{
	auto PaddleBallCollision = isColliding(this, pGame->getPaddle());
	if (PaddleBallCollision.collision== true)
	{
		this->move();
	}
}

void ball::draw() const
{
	window* pWind = pGame->getWind();
	pWind->SetPen(BLACK, 1);
	pWind->SetBrush(BLACK);
	pWind->DrawCircle(uprLft.x, uprLft.y, width, FILLED);
}

void ball::move()
{
	
	//pGame->getWind() ->SetBuffering(true);

	char cKeyData;
	keytype kType1;

	

	point paddlePoint = pGame->getPaddle()->getPoint();

	pGame->getWind()->FlushKeyQueue();
	kType1 = pGame->getWind()->GetKeyPress(cKeyData);

	auto PaddleBallCollision = isColliding(this, pGame->getPaddle());

	uprLft.x = Xinc;
	uprLft.y = Yinc;

	//vertical
	if(uprLft.y - radius <= config.toolBarHeight || PaddleBallCollision.collision)
	{
		

		Yinc = -Yinc;
	}

	//horizontal
	if(uprLft.x - radius <= 0 || uprLft.x + radius >= config.windWidth - 10)
	{
		Xinc = -Xinc;
	}

	//paddle collision
	if(PaddleBallCollision.collision)
	{
		Yinc = -abs(Yinc);
		double paddleCenterX = (pGame->getPaddle()->getPoint().x + (pGame->getPaddle()->getPoint().x + radius)) / 2.0;
		double offset = (uprLft.x - paddleCenterX) / (config.paddleWidth / 2.0);

		const double maxBounceAngle = 45.0;
		double bounceAngle = maxBounceAngle * offset;

		// Rotate the ball's direction by the calculated bounce angle
		float angle = atan2(Yinc, Xinc);
		angle = angle + bounceAngle * (3.1415926535 / 180.0f);
		float speed = hypot(Xinc, Yinc);
		Xinc = speed * cos(angle);
		Yinc = speed * sin(angle);
	}

	//draw the game elements
	pGame->getWind()->SetPen(LAVENDER, 1);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(0, 0, config.windWidth, config.windHeight, FILLED);
	pGame->getGrid()->draw();
	pGame->getToolBar()->draw();
	pGame->getPaddle()->draw();
	pGame->getWind()->SetPen(config.statusBarColor, 1);
	pGame->getWind()->SetBrush(config.statusBarColor);
	pGame->getWind()->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
	pGame->getWind()->SetPen(BLACK, 1);
	pGame->getWind()->SetBrush(BLACK);

	pGame->getWind()->DrawString(config.windWidth / 2, config.windHeight - config.statusBarHeight, "Score : " + to_string(config.scores));
	pGame->getWind()->DrawString(config.windWidth / 2 + 500, config.windHeight - config.statusBarHeight, "Lives : " + to_string(config.lives));
	this->draw();

	//moving the paddle with the ball at the same time thats why there are two key types
	
}

void ball::setPoint(point p)
{
	uprLft = p;
}




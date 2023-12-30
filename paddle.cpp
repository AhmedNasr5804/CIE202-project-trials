#include "paddle.h"

#include "game.h"
#include "gameConfig.h"

paddle::paddle(point r_uprleft, int r_width, int r_height, game* r_pGame):
	collidable(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\paddle\\paddle.jpg";
}

void paddle::collisionAction()
{

}

point paddle::getPoint() const
{
	return paddlePos;
}

void paddle::setPoint(point p)
{
	paddlePos = p;
}

//collidable::points paddle::getAllpoints() const
//{
//	points axis;
//
//	axis.upperLeft.x = paddlePos.x;
//	axis.upperLeft.y = paddlePos.y;
//
//	axis.lowerRight.x = paddlePos.x + width;
//	axis.lowerRight.y = paddlePos.y + height;
//
//	return axis;
//}

void paddle::move_paddle()
{
	char cKeyData;
	keytype kType;
	pGame->getWind()->FlushKeyQueue();
	pGame->getWind()->SetPen(LAVENDER, 1);
	pGame->getWind()->SetBrush(LAVENDER);
	

	// Loop until there escape is pressed
	
		kType = pGame->getWind()->GetKeyPress(cKeyData);

		if (kType == ARROW)
		{
			switch (cKeyData)
			{
			case 4:	//left Arrow
				if (uprLft.x > 10)
				{
					pGame->getPaddle()->uprLft.x -= 15;

					//drawing a rectangle that has the same color as the background

					//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
					pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
					//w.UpdateBuffer();
				}
				break;
			case 6:	//right Arrow
				if (uprLft.x < config.windWidth - width - 10)
				{
					pGame->getPaddle()->uprLft.x += 15;

					//drawing a rectangle that has the same color as the background

					//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
					pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
					//w.UpdateBuffer();
				}
				break;
			}

		}
		this->draw();
		pGame->getWind()->UpdateBuffer();
}





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
	keytype kType2;
	char cKeyData;

	kType2 = pGame->getWind()->GetKeyPress(cKeyData);
	pGame->getWind()->SetPen(config.bkGrndColor, 1);
	pGame->getWind()->SetBrush(config.bkGrndColor);

	if (kType2 == ARROW)
	{
		switch (cKeyData)
		{
		case 4: // right arrow
			if (paddlePos.x > 10) {
				paddlePos.x -= 40;
				pGame->getWind()->DrawRectangle(0, config.remainingHeight, config.windWidth, config.paddleAreaHeight, FILLED);
				setPoint(paddlePos);
			}
			break;

		case 6:
			// Move paddle right
			if (paddlePos.x < config.windWidth - 200) {
				paddlePos.x += 40;
				pGame->getWind()->DrawRectangle(0, config.remainingHeight, config.windWidth, config.paddleAreaHeight, FILLED);
				setPoint(paddlePos);
			}
			break;
		}

		//updated paddle
		draw();
	}


	pGame->getWind()->UpdateBuffer();
}





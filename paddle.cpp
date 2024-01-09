//#include "paddle.h"
//
//#include "game.h"
//#include "gameConfig.h"
//
//paddle::paddle(point r_uprleft, int r_width, int r_height, game* r_pGame):
//	collidable(r_uprleft, r_width, r_height, r_pGame)
//{
//	imageName = "images\\paddle\\paddle.jpg";
//}
//
//void paddle::collisionAction()
//{
//
//}
//
//point paddle::getPoint() const
//{
//	return paddlePos;
//}
//
//void paddle::setPoint(point p)
//{
//	paddlePos = p;
//}
//
//
//
//
////collidable::points paddle::getAllpoints() const
////{
////	points axis;
////
////	axis.upperLeft.x = paddlePos.x;
////	axis.upperLeft.y = paddlePos.y;
////
////	axis.lowerRight.x = paddlePos.x + width;
////	axis.lowerRight.y = paddlePos.y + height;
////
////	return axis;
////}
//
//void paddle::move_paddle()
//{
//	
//	char cKeyData;
//	keytype kType;
//	pGame->getWind()->FlushKeyQueue();
//
//	// Loop until there escape is pressed
//	kType = pGame->getWind()->GetKeyPress(cKeyData);
//	pGame->getWind()->SetPen(config.bkGrndColor, 1);
//	pGame->getWind()->SetBrush(config.bkGrndColor);
//		
//
//		if (kType == ARROW)
//		{
//			switch (cKeyData)
//			{
//			case 4:	//left Arrow
//				if (uprLft.x > 10)
//				{
//					pGame->getPaddle()->uprLft.x -= 30;
//
//					//drawing a rectangle that has the same color as the background
//
//					//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
//					pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
//					//w.UpdateBuffer();
//				}
//				break;
//			case 6:	//right Arrow
//				if (uprLft.x < config.windWidth - width - 10)
//				{
//					pGame->getPaddle()->uprLft.x += 30;
//
//					//drawing a rectangle that has the same color as the background
//
//					//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
//					pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
//					//w.UpdateBuffer();
//				}
//				break;
//			}
//
//		}
//		this->draw();
//		/*pGame->getWind()->UpdateBuffer();*/
//	
//}
//
//
//
//

#include "paddle.h"
#include "game.h"
#include "gameConfig.h"


paddle::paddle(point r_uprleft, int paddleWidth, int paddleHight, game* r_pGame) :
	collidable(r_uprleft, paddleWidth, paddleHight, r_pGame)
{
}

void paddle::draw()
{
	window* pWind = pGame->getWind();
	pWind->SetBrush(BLACK);
	pWind->SetPen(BLUEVIOLET);
	//pWind->DrawRectangle(500,530,(500+config.paddleWidth),(530+config.paddleHight));
	pWind->DrawRectangle(uprLft.x, uprLft.y - 40, (uprLft.x + width), (uprLft.y + height - 40), FILLED);
}
void paddle::collisionAction()
{
	//if (collidable::is_collision(game::playerPaddle,game::gameBall))
}

void paddle::move_paddle()
{
	window* pWind = pGame->getWind();
	//paddle::draw();
	char cKeyData;
	keytype kType;
	int speed = 10;
	kType = pWind->WaitKeyPress(cKeyData);
	color c = BLUE;
	color bg = LAVENDER;
	if (cKeyData == 4 && uprLft.x != 0)
	{
		uprLft.x -= speed;
	}
	if (cKeyData == 6 && uprLft.x < 1200 - width)
	{
		uprLft.x += speed;
	}
	pWind->SetBrush(bg);
	pWind->SetPen(bg);
	pWind->DrawRectangle(0, uprLft.y - 40, (1200), (uprLft.y + height - 40), FILLED);
	paddle::draw();
	pWind->UpdateBuffer();

	//switch (power->get_type())
	//{
	//case fireball:
	//	kType = pGame->getWind()->GetKeyPress(cKeyData);

	//	if (kType == ARROW)
	//	{
	//		switch (cKeyData)
	//		{
	//		case 4:	//left Arrow
	//			if (uprLft.x > 10)
	//			{
	//				pGame->getPaddle()->uprLft.x -= 15;

	//				//drawing a rectangle that has the same color as the background

	//				//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
	//				pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
	//				//w.UpdateBuffer();
	//			}
	//			break;
	//		case 6:	//right Arrow
	//			if (uprLft.x < config.windWidth - width - 10)
	//			{
	//				pGame->getPaddle()->uprLft.x += 15;

	//				//drawing a rectangle that has the same color as the background

	//				//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
	//				pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
	//				//w.UpdateBuffer();
	//			}
	//			break;
	//		}
	//	}

	//	this->draw();
	//	pGame->getWind()->UpdateBuffer();
	//	break;
	//case Magnet:
	//	kType = pGame->getWind()->GetKeyPress(cKeyData);

	//	if (kType == ARROW)
	//	{
	//		switch (cKeyData)
	//		{
	//		case 4:	//left Arrow
	//			if (uprLft.x > 10)
	//			{
	//				pGame->getPaddle()->uprLft.x -= 15;

	//				//drawing a rectangle that has the same color as the background

	//				//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
	//				pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
	//				//w.UpdateBuffer();
	//			}
	//			break;
	//		case 6:	//right Arrow
	//			if (uprLft.x < config.windWidth - width - 10)
	//			{
	//				pGame->getPaddle()->uprLft.x += 15;

	//				//drawing a rectangle that has the same color as the background

	//				//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
	//				pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
	//				//w.UpdateBuffer();
	//			}
	//			break;
	//		}
	//	}

	//	this->draw();
	//	pGame->getWind()->UpdateBuffer();
	//	break;
	//case MultipleBalls:
	//	kType = pGame->getWind()->GetKeyPress(cKeyData);

	//	if (kType == ARROW)
	//	{
	//		switch (cKeyData)
	//		{
	//		case 4:	//left Arrow
	//			if (uprLft.x > 10)
	//			{
	//				pGame->getPaddle()->uprLft.x -= 15;

	//				//drawing a rectangle that has the same color as the background

	//				//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
	//				pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
	//				//w.UpdateBuffer();
	//			}
	//			break;
	//		case 6:	//right Arrow
	//			if (uprLft.x < config.windWidth - width - 10)
	//			{
	//				pGame->getPaddle()->uprLft.x += 15;

	//				//drawing a rectangle that has the same color as the background

	//				//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
	//				pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
	//				//w.UpdateBuffer();
	//			}
	//			break;
	//		}
	//	}

	//	this->draw();
	//	pGame->getWind()->UpdateBuffer();
	//	break;

	//case WindGlade:
	//	kType = pGame->getWind()->GetKeyPress(cKeyData);

	//	if (kType == ARROW)
	//	{
	//		switch (cKeyData)
	//		{
	//		case 4:	//left Arrow
	//			if (uprLft.x > 10)
	//			{
	//				pGame->getPaddle()->uprLft.x -= 30;

	//				//drawing a rectangle that has the same color as the background

	//				//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
	//				pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
	//				//w.UpdateBuffer();
	//			}
	//			break;
	//		case 6:	//right Arrow
	//			if (uprLft.x < config.windWidth - width - 10)
	//			{
	//				pGame->getPaddle()->uprLft.x += 30;

	//				//drawing a rectangle that has the same color as the background

	//				//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
	//				pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
	//				//w.UpdateBuffer();
	//			}
	//		}
	//	}

	//	this->draw();
	//	pGame->getWind()->UpdateBuffer();
	//	break;
	//case widePaddel:
	//	kType = pGame->getWind()->GetKeyPress(cKeyData);

	//	if (kType == ARROW)
	//	{
	//		switch (cKeyData)
	//		{
	//		case 4:	//left Arrow
	//			if (uprLft.x > 10)
	//			{
	//				pGame->getPaddle()->uprLft.x -= 15;

	//				//drawing a rectangle that has the same color as the background

	//				//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
	//				pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
	//				//w.UpdateBuffer();
	//				config.paddleWidth *= 2;
	//			}
	//			break;
	//		case 6:	//right Arrow
	//			if (uprLft.x < config.windWidth - width - 10)
	//			{
	//				pGame->getPaddle()->uprLft.x += 15;

	//				//drawing a rectangle that has the same color as the background

	//				//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
	//				pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
	//				//w.UpdateBuffer();
	//				config.paddleWidth *= 2;
	//			}

	//			this->draw();
	//			pGame->getWind()->UpdateBuffer();

	//		}
	//	}

	//	break;
	//case narrowPaddel:
	//	kType = pGame->getWind()->GetKeyPress(cKeyData);

	//	if (kType == ARROW)
	//	{
	//		switch (cKeyData)
	//		{
	//		case 4:	//left Arrow
	//			if (uprLft.x > 10)
	//			{
	//				pGame->getPaddle()->uprLft.x -= 15;

	//				//drawing a rectangle that has the same color as the background

	//				//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
	//				pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
	//				//w.UpdateBuffer();
	//				config.paddleWidth /= 2;
	//			}
	//			break;
	//		case 6:	//right Arrow
	//			if (uprLft.x < config.windWidth - width - 10)
	//			{
	//				pGame->getPaddle()->uprLft.x += 15;

	//				//drawing a rectangle that has the same color as the background

	//				//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
	//				pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
	//				//w.UpdateBuffer();
	//				config.paddleWidth /= 2;
	//			}

	//			this->draw();
	//			pGame->getWind()->UpdateBuffer();

	//		}
	//	}

	//	break;
	//case Quicksand:
	//	kType = pGame->getWind()->GetKeyPress(cKeyData);

	//	if (kType == ARROW)
	//	{
	//		switch (cKeyData)
	//		{
	//		case 4:	//left Arrow
	//			if (uprLft.x > 10)
	//			{
	//				pGame->getPaddle()->uprLft.x -= 7.5;

	//				//drawing a rectangle that has the same color as the background

	//				//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
	//				pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
	//				//w.UpdateBuffer();
	//				config.paddleWidth /= 2;
	//			}
	//			break;
	//		case 6:	//right Arrow
	//			if (uprLft.x < config.windWidth - width - 10)
	//			{
	//				pGame->getPaddle()->uprLft.x += 7.5;

	//				//drawing a rectangle that has the same color as the background

	//				//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
	//				pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
	//				//w.UpdateBuffer();
	//				config.paddleWidth /= 2;
	//			}

	//			this->draw();
	//			pGame->getWind()->UpdateBuffer();

	//		}
	//	}

	//	break;
	//case ReverseDirection:
	//	kType = pGame->getWind()->GetKeyPress(cKeyData);

	//	if (kType == ARROW)
	//	{
	//		switch (cKeyData)
	//		{
	//		case 6:	//left Arrow
	//			if (uprLft.x > 10)
	//			{
	//				pGame->getPaddle()->uprLft.x -= 7.5;

	//				//drawing a rectangle that has the same color as the background

	//				//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
	//				pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
	//				//w.UpdateBuffer();
	//				config.paddleWidth /= 2;
	//			}
	//			break;
	//		case 4:	//right Arrow
	//			if (uprLft.x < config.windWidth - width - 10)
	//			{
	//				pGame->getPaddle()->uprLft.x += 7.5;

	//				//drawing a rectangle that has the same color as the background

	//				//w->DrawRectangle(prePos.x, prePos.y, config.windWidth, height);
	//				pGame->getWind()->DrawRectangle(0, 500, config.windWidth, 380);
	//				//w.UpdateBuffer();
	//				config.paddleWidth /= 2;
	//			}

	//			this->draw();
	//			pGame->getWind()->UpdateBuffer();

	//		}
	//	}

	//	break;

	//}
}

point paddle::getPoint()
{
	return uprLft;
}

void paddle::setPoint(point p)
{
	uprLft = p;
}

//===============================================================================================

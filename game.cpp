#include "game.h"
#include "gameConfig.h"


void game::updateGameTime()
{
	auto currentTime = chrono::steady_clock::now();
	chrono::duration<double> elapsedSecs = currentTime - startTime;
	double gameTime = elapsedSecs.count();
}

void game::updateScore(int p)
{
	score += p;
}

void game::decrementLives()
{
	lives--;
}

game::game()
{
	//Initialize playgrond parameters
	gameMode = MODE_DSIGN;


	//1 - Create the main window
	pWind = CreateWind(config.windWidth, config.windHeight, config.wx, config.wy);

	//2 - create and draw the toolbar
	point toolbarUpperleft;
	toolbarUpperleft.x = 0;
	toolbarUpperleft.y = 0;

	gameToolbar = new toolbar(toolbarUpperleft,0,config.toolBarHeight, this);
	gameToolbar->draw();

	//3 - create and draw the grid
	point gridUpperleft;
	gridUpperleft.x = 0;
	gridUpperleft.y = config.toolBarHeight;
	bricksGrid = new grid(gridUpperleft, config.windWidth, config.gridHeight, this);
	bricksGrid->draw();
	
	//4- Create the Paddle
	//TODO: Add code to create and draw the paddle
	point paddleUpperLeft;
	paddleUpperLeft.x = (config.windWidth / 2) + (config.paddleWidth/2) - 210;
	paddleUpperLeft.y = config.paddleAreaHeight + 300;
	gamePaddle = new paddle(paddleUpperLeft, config.paddleWidth, config.paddleHeight, this);
	gamePaddle->draw();

	//5- Create the ball
	//TODO: Add code to create and draw the ball
	point BallUpperLeft;
	BallUpperLeft.x = (config.windHeight / 2) + 240;
	BallUpperLeft.y = (config.paddleAreaHeight)  +  280;
	gameBall = new ball(BallUpperLeft, config.ballRadius, config.ballRadius, this);
	gameBall->draw();
	
	//6- Create and clear the status bar
	clearStatusBar();
}

game::~game()
{
	delete pWind;
	delete gameToolbar;
	delete bricksGrid;
	delete gamePaddle;
	delete gameBall;

}


clicktype game::getMouseClick(int& x, int& y) const
{
	return pWind->WaitMouseClick(x, y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
window* game::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(config.bkGrndColor);
	pW->SetPen(config.bkGrndColor, 1);
	pW->DrawRectangle(0, 0, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void game::clearStatusBar() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.statusBarColor, 1);
	pWind->SetBrush(config.statusBarColor);
	pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void game::printMessage(string msg) const	//Prints a message on status bar
{
	clearStatusBar();	//First clear the status bar

	pWind->SetPen(config.penColor, 100);
	pWind->SetFont(32, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);
}



window* game::getWind() const		//returns a pointer to the graphics window
{
	return pWind;
}



string game::getSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		printMessage(Label);
	}
}

grid* game::getGrid() const
{
	// TODO: Add your implementation code here.
	return bricksGrid;
}

paddle* game::getPaddle() const
{
	return gamePaddle;
}

toolbar* game::getToolBar() const
{
	return gameToolbar;
}

void game::updateGameInfo() 
{
	updateGameTime();

	// TODO: add the condtion for lives

	if (static_cast<int>(gameTime) % 1 == 0)
		updateScore(20);

	pWind->DrawString(600, 0, "lives: ");

}

void game::setMode(MODE mode)
{
	gameMode = mode;
}

void game::setPlay(bool play)
{
	isPlay = play;
}

void game::setExit(bool exit)
{
	isExit = exit;
}

void game::setPause(bool pause)
{
	isPause = pause;
}


////////////////////////////////////////////////////////////////////////
void game::go()
{
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	char c;

	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - Brick Breaker (CIE202-project) - - - - - - - - - -");
	
	do
	{
		updateGameInfo();

		printMessage("Ready...");
		getMouseClick(x, y);	//Get the coordinates of the user click


		if (gameMode == MODE_DSIGN)		//Game is in the Desgin mode
		{
			//[1] If user clicks on the Toolbar
			if (y >= 0 && y < config.toolBarHeight)
			{
				isExit=gameToolbar->handleClick(x, y);
			}
		}

		if(gameMode == MODE_PLAY)
		{
			do
			{
				pWind->GetMouseClick(x, y);

				if ((y>=0 && y < config.toolBarHeight)&& x>330)
				{
					gameToolbar->handleClick(x, y);
				}

				gameBall->move();
				gamePaddle->move_paddle();
			} while (isPlay && !isPause);

			gameMode = MODE_DSIGN;
		}

	} while (!isExit);
}
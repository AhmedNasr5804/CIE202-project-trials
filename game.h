#pragma once
#include "CMUgraphicsLib\CMUgraphics.h"
#include "toolbar.h"
#include "grid.h"
#include "paddle.h"
#include"ball.h"
#include<chrono>
using namespace std;



//Main class that coordinates the game operation
class game
{




	/// Add more members if needed
	bool isPlay;
	bool isPause;
	bool isExit;

	
	window* pWind;	//Pointer to the CMU graphics window
	toolbar* gameToolbar;
	grid* bricksGrid;
	paddle* gamePaddle;
	ball* gameBall;

	//starting the timer and managing the score and lives
	double gameTime;
	int score;
	int lives;
	chrono::steady_clock::time_point startTime;



public:
	game();
	~game();

	enum MODE	//Game mode
	{
		MODE_DSIGN,	//Desing mode (startup mode)
		MODE_PLAY	//Playing mode
	};

	MODE gameMode;

	clicktype getMouseClick(int& x, int& y) const;//Get coordinate where user clicks and returns click type (left/right)
	string getSrting() const;	 //Returns a string entered by the user


	window* CreateWind(int, int, int, int) const; //creates the game window


	void clearStatusBar() const;	//Clears the status bar


	void printMessage(string msg) const;	//Print a message on Status bar

	void go();

	window* getWind() const;		//returns a pointer to the graphics window



	grid* getGrid() const;
	paddle* getPaddle() const;
	toolbar* getToolBar() const;

	void updateGameTime();
	void updateScore(int p);
	void decrementLives();
	void updateGameInfo(); //to update the game time, live and score

	void  setMode(MODE mode);
	void setPlay(bool play);
	void setExit(bool exit);
	void setPause(bool pause);
};


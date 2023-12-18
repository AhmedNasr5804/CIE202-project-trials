#include "toolbar.h"
#include "game.h"
#include "grid.h"
#include "gameConfig.h"


////////////////////////////////////////////////////  class toolbarIcon   ////////////////////////////////////////////////////
toolbarIcon::toolbarIcon(point r_uprleft, int r_width, int r_height, game* r_pGame):
	drawable(r_uprleft, r_width, r_height,  r_pGame)
{}




////////////////////////////////////////////////////  class iconAddNormalBrick   //////////////////////////////////////////////
iconAddNormalBrick::iconAddNormalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame):
	toolbarIcon(r_uprleft, r_width, r_height,  r_pGame)
{}

void iconAddNormalBrick::onClick()
{
	
	pGame->printMessage("Click on empty cells to add Normal Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = x;
		clicked.y = y;
		grid* pGrid = pGame->getGrid();
		pGrid->addBrick(BRK_NRM, clicked);
		pGrid->draw();
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");

}


////////////////////////////////////////////////////  class iconAddHardBrick   //////////////////////////////////////////////
iconAddHardBrick::iconAddHardBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconAddHardBrick::onClick()
{
	pGame->printMessage("Click on empty cells to add Hard Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{
		point clicked;
		clicked.x = x;
		clicked.y = y;
		grid* pGrid = pGame->getGrid();
		pGrid->addBrick(BRK_HRD, clicked);
		pGrid->draw();
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");
}

//
////////////////////////////////////////////////////  class iconSave   //////////////////////////////////////////////
iconSave::iconSave(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconSave::onClick()
{
	//to be wriiten
}
//
////////////////////////////////////////////////////  class iconUpload   //////////////////////////////////////////////
iconUpload::iconUpload(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconUpload::onClick()
{
	//to be wriiten
}
//
////////////////////////////////////////////////////  class Play   //////////////////////////////////////////////
iconPlay::iconPlay(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconPlay::onClick()
{
	//to be wriiten
	pGame->setPlay(true);
	pGame->gameMode = game::MODE_PLAY;
}

////////////////////////////////////////////////////  class Pause   //////////////////////////////////////////////
iconPause::iconPause(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{}

void iconPause::onClick()
{
	//to be wriiten
	pGame->setPause(true);
	pGame->gameMode = game::MODE_DSIGN;

}


////////////////////////////////////////////////////  class iconExit   //////////////////////////////////////////////
iconExit::iconExit(point r_uprleft, int r_width, int r_height, game* r_pGame):
	toolbarIcon(r_uprleft, r_width, r_height,  r_pGame)
{}

void iconExit::onClick()
{
	//TO DO: add code for cleanup and game exit here
	pGame->clearStatusBar();

	pGame->getWind()->~window();
}

/////////////////////////////////////////////////   class IconDelete ///////////////////////////////////////////////////

iconDelete::iconDelete(point r_uprleft, int r_width, int r_height, game* r_pGame):
	toolbarIcon(r_uprleft, r_width, r_height, r_pGame)
{

}

void iconDelete::onClick()
{
	pGame->printMessage("Click on filled cells to remove Bricks  ==> Right-Click to stop <==");
	int x, y;
	clicktype t = pGame->getMouseClick(x, y);
	while (t == LEFT_CLICK)
	{

		point clicked;
		clicked.x = x;
		clicked.y = y;
		grid* pGrid = pGame->getGrid();
		pGrid->deleteBrick(clicked);
		pGrid->draw();
		t = pGame->getMouseClick(x, y);
	}
	pGame->printMessage("");
}


////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
toolbar::toolbar(point r_uprleft, int wdth, int hght, game* pG):
	drawable(r_uprleft, wdth, hght, pG)
{	
	
	height = hght;
	pGame = pG;

	//First prepare List of images for each icon
	//To control the order of these images in the menu, reoder them in enum ICONS above	
	iconsImages[ICON_ADD_NORM] = "images\\ToolbarIcons\\ANormalBrickIcon.jpg";
	iconsImages[ICON_ADD_HARD] = "images\\ToolbarIcons\\AHardBrickIcon.jpg";
	iconsImages[ICON_DELETE] = "images\\ToolbarIcons\\ADeleteIcon.jpg";
	iconsImages[ICON_SAVE] = "images\\ToolbarIcons\\ASaveIcon.jpg";
	iconsImages[ICON_UPLOAD] = "images\\ToolbarIcons\\AUpload.jpg";
	iconsImages[ICON_PLAY] = "images\\ToolbarIcons\\APlay.jpg";
	iconsImages[ICON_PAUSE] = "images\\ToolbarIcons\\APause.jpg";
	iconsImages[ICON_EXIT] = "images\\ToolbarIcons\\AExitIcon.jpg";

	point p;
	p.x = 0;
	p.y = 0;

	iconsList = new toolbarIcon* [ICON_COUNT];

	//For each icon in the tool bar
	//	1- Create an object setting its upper left corner, width and height
	iconsList[ICON_ADD_NORM] = new iconAddNormalBrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_ADD_HARD] = new iconAddHardBrick(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_DELETE] = new iconDelete(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_SAVE] = new iconSave(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_UPLOAD] = new iconUpload(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_PLAY] = new iconPlay(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_PAUSE] = new iconPause(p, config.iconWidth, height, pGame);
	p.x += config.iconWidth;
	iconsList[ICON_EXIT] = new iconExit(p, config.iconWidth, height, pGame);


	//	2-Set its image (from the above images list)
	for (int i = 0; i < ICON_COUNT; i++)
	{
		iconsList[i]->setImageName(iconsImages[i]);

	}
}

toolbar::~toolbar()
{
	for (int i = 0; i < ICON_COUNT; i++)
		delete iconsList[i];
	delete iconsList;
}

void toolbar::draw() const
{
	for (int i = 0; i < ICON_COUNT; i++)
		iconsList[i]->draw();
	window* pWind = pGame->getWind();
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, height, pWind->GetWidth(), height);

}

//handles clicks on toolbar icons, returns true if exit is clicked
bool toolbar::handleClick(int x, int y)
{
	if (x > ICON_COUNT * config.iconWidth)	//click outside toolbar boundaries
		return false;
	
	
	//Check whick icon was clicked
	//==> This assumes that menu icons are lined up horizontally <==
	//Divide x coord of the point clicked by the icon width (int division)
	//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

	int clickedIconIndex = (x / config.iconWidth);
	iconsList[clickedIconIndex]->onClick();	//execute onClick action of clicled icon

	//if (clickedIconIndex == ICON_EXIT) return true;	
	
	return false;


}


#include "grid.h"
#include "game.h"
#include "gameConfig.h"
#include <fstream>

grid::grid(point r_uprleft, int wdth, int hght, game* pG):
	drawable(r_uprleft, wdth, hght, pG)
{

	rows = height / config.brickHeight;
	cols = width / config.brickWidth;

	brickMatrix = new brick ** [rows];
	for (int i = 0; i < rows; i++)
		brickMatrix[i] = new brick * [cols];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			brickMatrix[i][j] = nullptr;
}

grid::~grid()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (brickMatrix[i][j])
				delete brickMatrix[i][j];	//delete all allocated bricks

	for (int i = 0; i < rows; i++)
		delete brickMatrix[i];

	delete brickMatrix;

}

void grid::draw() const
{
	window* pWind = pGame->getWind();
	//draw lines showing the grid
	pWind->SetPen(config.gridLinesColor,1);

	//draw horizontal lines
	for (int i = 0; i < rows; i++) {
		int y = uprLft.y + (i + 1) * config.brickHeight;
		pWind->DrawLine(0, y, width, y);
	}
	//draw vertical lines
	for (int i = 0; i < cols; i++) {
		int x = (i + 1) * config.brickWidth;
		pWind->DrawLine(x, uprLft.y, x, uprLft.y+ rows* config.brickHeight);
	}

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (brickMatrix[i][j])
				brickMatrix[i][j]->draw();	//draw exisiting bricks


}

int grid::addBrick(BrickType brkType, point clickedPoint)
{
	//TODO:
	// 1- Check that the clickedPoint is within grid range (and return -1)
	// 2- Check that the clickedPoint doesnot overlap with an exisiting brick (return 0)

	//Here we assume that the above checks are passed
	
	//From the clicked point, find out the index (row,col) of the corrsponding cell in the grid
	int gridCellRowIndex = (clickedPoint.y-uprLft.y) / config.brickHeight;
	int gridCellColIndex = clickedPoint.x / config.brickWidth;

	//Now, align the upper left corner of the new brick with the corner of the clicked grid cell
	point newBrickUpleft;
	newBrickUpleft.x = uprLft.x + gridCellColIndex * config.brickWidth;
	newBrickUpleft.y = uprLft.y+ gridCellRowIndex * config.brickHeight;

	switch (brkType)
	{
	case BRK_NRM:	//The new brick to add is Normal Brick
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new normalBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;

	case BRK_HRD:	//The new brick to add is Hard Brick
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new hardBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;

		//TODO: 
		// handle more types
	}
	return 1;
}

void grid::deleteBrick(point clickedPoint)
{
	int gridCellRowIndex = (clickedPoint.y - uprLft.y) / config.brickHeight;
	int gridCellColIndex = clickedPoint.x / config.brickWidth;
	point newBrickPos;
	newBrickPos.x = uprLft.x + gridCellColIndex * config.brickWidth;
	newBrickPos.y = uprLft.y + gridCellRowIndex * config.brickHeight;
	

	if (brickMatrix[gridCellRowIndex][gridCellColIndex] != nullptr) {
		delete brickMatrix[gridCellRowIndex][gridCellColIndex];
		brickMatrix[gridCellRowIndex][gridCellColIndex] = nullptr;
		pGame->getWind()->SetPen(LAVENDER, 1);
		pGame->getWind()->SetBrush(RED);
		pGame->getWind()->DrawRectangle(newBrickPos.x, newBrickPos.y, newBrickPos.x + config.brickWidth, newBrickPos.y + config.brickHeight, FILLED);
	}

}

void grid::destroy(brick* brk)
{
	BrickType type = brk->getType();
	
	int r = (uprLft.y - uprLft.y) / config.brickHeight;
	int c = uprLft.x / config.brickWidth;

	switch (type)
	{
	case BRK_NRM:
	case BRK_HRD:

		delete brickMatrix[r][c];
		brickMatrix[r][c] = nullptr;
		pGame->getWind()->SetPen(LAVENDER, 1);
		pGame->getWind()->SetBrush(RED);
		pGame->getWind()->DrawRectangle(brk->getPoint().x, brk->getPoint().y, brk->getPoint().x + config.brickWidth, brk->getPoint().y + config.brickHeight, FILLED);
	
		break;
	case BRK_BMB:
		destroy(brickMatrix[r + 1][c]);
		destroy(brickMatrix[r - 1][c]);
		destroy(brickMatrix[r][c + 1]);
		destroy(brickMatrix[r][c - 1]);
		delete brickMatrix[r][c];
		brickMatrix[r][c] = nullptr;
	}


}

brick*** grid::getBrickMatrix()
{
	return brickMatrix;
}

int grid::getrows() const
{
	return rows;
}

int grid::getcols() const
{
	return cols;
}

int grid::arethereremainingbricks()
{
	int remainingbricks = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (brickMatrix[i][j] != nullptr)
				remainingbricks++;
	return remainingbricks;

}

//void grid::save()
//{
//	ofstream infile;
//	infile.open("save.txt");
//
//	grid* pGrid = pGame->getGrid();
//
//	brick*** gameBrickMatrix = pGrid->getBrickMatrix();
//
//	int type;
//	for (int i = 0; i<rows;i++)
//		for (int j = 0; j<cols;j++)
//		{
//			if(gameBrickMatrix[i][j] != nullptr)
//			{
//				infile << i+1 << " ";
//				infile << j+1 << " ";
//				type = int(gameBrickMatrix[i][j]->getType());
//				infile << type<<endl;
//			}
//		}
//	infile.close();
//}

//void grid::load()
//{
//	
//		pGame->printMessage("Loading File... ==> Right-Click to stop <==");
//		ifstream infile;
//		grid* pGrid = pGame->getGrid();
//		infile.open("save.txt");
//		if (infile.is_open())
//		{
//
//			pGrid->draw();
//
//			// Load bricks from file
//			int i, j, type;
//			while (infile >> i >> j >> type)
//			{
//				// Add bricks to the grid
//				point uplft;
//				uplft.x = (j - 1) * config.brickWidth;
//				uplft.y = (i - 1) * config.brickHeight;
//				BrickType bt = BrickType(type);
//				pGrid->addBrick(bt, uplft);
//			}
//
//			infile.close();
//		}
//		else
//		{
//			pGame->printMessage("Failed to open the file for loading.");
//		}
//}




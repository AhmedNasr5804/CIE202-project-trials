#include "collective.h"


collective::collective(point r_uprleft, int r_width, int r_height, game* r_pGame) :collidable(r_uprleft, r_width, r_height, r_pGame)
{

}

void collective::NewPosition()
{
	z.y = +vy;


}

void collective::print()
{
	pGame->getGrid()->draw();
	pGame->getWind()->SetPen(PURPLE);
	pGame->getWind()->SetBrush(PURPLE);
	pGame->getWind()->DrawCircle(z.x, z.y, radius);
}

collective::~collective()
{
}
void collective::CheckCollision()
{

}
PowerTypes  collective::get_type()
{
	return Type;
}
//malak
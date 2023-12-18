#include "collidable.h"

collidable::collidable(point r_uprleft, int r_width, int r_height, game* r_pGame):
			drawable(r_uprleft, r_width, r_height,  r_pGame)
{
}

collidable::collisionData collidable::isColliding(const collidable* obj1, const collidable* obj2) const
{
	collisionData data;

	//definig the center of each object
	float centerx1 = obj1->uprLft.x + (obj1->width / 2);
	float centery1 = obj1->uprLft.y + (obj1->height / 2);
	float centerx2 = obj2->uprLft.x + (obj2->width / 2);
	float centery2 = obj2->uprLft.y + (obj2->height / 2);

	//finding the differnece between the centers to find if they over lap
	float diffX = abs(centerx1 - centerx2);
	float diffY = abs(centery1 - centery2);
	float overlapATx = (obj1->width) + (obj2->width) - diffX;
	float overlapATy = (obj1->height) + (obj2->height) - diffY;

	if (overlapATx > 0 && overlapATy > 0)
	{
		data.collision = true;

		// checking the direction at which the objects colides
		if (overlapATx > overlapATy)
		{
			data.collisionPoint.x = (diffX > 0) ? obj1->uprLft.x + width : obj1->uprLft.x;
			data.collisionPoint.y = centery1;
		}
		else
		{
			data.collisionPoint.y = (diffY > 0) ? obj1->uprLft.y + obj1->height : obj1->uprLft.y;
			data.collisionPoint.x = centerx1;
		}
	}
	return data;

}

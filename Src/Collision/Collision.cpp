#include "Collision.h"

//IsHitRect‚Ì’è‹`
bool IsHitRect(int myPos_X, int myPos_Y, int side, int Vertical,
	int pos_1X, int pos_1Y, int Rectside, int RectVertical)
{
	if (myPos_X < pos_1X + Rectside &&
		myPos_X + side > pos_1X &&
		myPos_Y + Vertical > pos_1Y &&
		myPos_Y < pos_1Y + RectVertical)
		return true;
	else
		return false;
}


//IsHitCircle‚Ì’è‹`
bool IsHitCircle(int PosX, int PosY, int circle1, int aPosX, int aPosY, int circle2)
{
	if ((circle1 + circle2) * (circle1 + circle2) >
		(aPosX - PosX) * (aPosX - PosX) + (aPosY - PosY) * (aPosY - PosY))
	{
		return true;
	}
	else
		return false;
}

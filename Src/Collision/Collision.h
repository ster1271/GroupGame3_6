#pragma once

//IsHitRectのプロトタイプ宣言
bool IsHitRect(int myPos_X, int myPos_Y, int side, int Vertical,
	int pos_1X, int pos_1Y, int Rectside, int RectVertical);

//IsHitCircleのプロトタイプ宣言
bool IsHitCircle(int PosX, int PosY, int circle1, int aPosX, int aPosY, int circle2);


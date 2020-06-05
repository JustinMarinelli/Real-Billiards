/**
* file: BurstSign.cpp
* author: Justin Marinelli
*/

#include "BurstSign.h"
#include <math.h>
#include "Game.h"

#define PI 3.14159265


using namespace std;

/**
* Constructor
*/
CBurstSign::CBurstSign(CGame* game, int numPoints, double x, double y, string text) : mGame(game)
{
	mNumPoints = numPoints;
	mX = x;
	mY = y;
	GenerateVertices();
	mText = text;


}

/**
* Generate the vertices of the sign
*/
void CBurstSign::GenerateVertices()
{
	int outerPPQ = mNumPoints / 4;
	int innerPPQ = ceil(float(mNumPoints + 1) / 4);
	
	double angle = (PI / 2) / outerPPQ;
	double innerAngle = (PI / 2) / innerPPQ;

	int outerAngleMult = 0;
	int innerAngleMult = 1;
	for (int i = 0; i < 2 * mNumPoints; i++)
	{
		if (i % 2 && i > 0)
		{
			mPoints.push_back(D2D1::Point2F(mX + mInnerRad * cos(angle * outerAngleMult), mY + mInnerRad * sin(angle * outerAngleMult)));
			outerAngleMult += 1;
		}
		else
		{
			mPoints.push_back(D2D1::Point2F(mX + mOuterRad * cos(angle * outerAngleMult), mY + mOuterRad * sin(angle * outerAngleMult)));
			outerAngleMult += 1;
		}
	}



}

CBurstSign::~CBurstSign()
{
}

/**
* Draw the burst sign at a particular coordinate and rotated by a specified 
* amount
* \param graphics: The graphics object we're drawing on
* \param angle: The angle we're rotating the sign by
*/
void CBurstSign::Draw(ID2D1HwndRenderTarget* graphics)
{

	int i = 0;
	D2D1_POINT_2F points[65] = {};
	for (D2D1_POINT_2F point : mPoints)
	{
		//graphics->DrawLine(&pen, PointF(mX, mY), point);
		points[i] = point;
		i++;
	}
	D2D1_POINT_2F* pPoints = points;

	mGame->GetFactory()->CreatePathGeometry(&mBurst);
	mBurst->Open(&mBurstSink);
	mBurstSink->AddLines(points, 65);

	mBurstSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	mBurstSink->Close();


	//graphics->FillGeometry(mBurst, mGame->GetBallBrushes()[3]);
	//DrawMessage(graphics);
}

void CBurstSign::DrawMessage(ID2D1HwndRenderTarget* graphics)
{
	D2D1_POINT_2F uRC = D2D1::Point2F(mX + cos(PI / 4) * mOuterRad, mY - sin(PI / 4) * mOuterRad);
	D2D1_POINT_2F uLC = D2D1::Point2F(mX - cos(PI / 4) * mOuterRad, mY - sin(PI / 4) * mOuterRad);
	D2D1_POINT_2F bRC = D2D1::Point2F(mX + cos(PI / 4) * mOuterRad, mY + sin(PI / 4) * mOuterRad);
	D2D1_POINT_2F bLC = D2D1::Point2F(mX - cos(PI / 4) * mOuterRad, mY + sin(PI / 4) * mOuterRad);
	D2D1_RECT_F textRect = D2D1::RectF(uLC.x, uLC.y, uLC.x + abs(uRC.x - uLC.x), uLC.y + bLC.y - uLC.y);
	//graphics->DrawRectangle(&pen, uLC.X, uLC.Y, abs(uRC.X - uLC.X), bLC.Y - uLC.Y);

	graphics->DrawText(L"MAX POWER!", 10, mGame->GetTextFormat(), textRect, mGame->GetBallBrushes()[1]);
}

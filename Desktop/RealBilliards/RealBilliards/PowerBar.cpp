/**
* file: PowerBar.cpp
* author: Justin Marinelli
*/

#include "math.h"
#include "PowerBar.h"
#include "Game.h"
using namespace std;



/**
* Constructor
*/
CPowerBar::CPowerBar(CGame* game) : mGame(game)
{
	mBurstSign = make_shared<CBurstSign>(game, 32, mX + mBorderWidth + 65, mY, "MAX POWER!");
	
}

/**
* Destructor
*/
CPowerBar::~CPowerBar()
{
}

/**
* Set the location of the power bar
*/
void CPowerBar::SetLocation()
{
	vector<D2D1_POINT_2F> tlPP = mGame->GetTable()->GetTLPocketPoints();
	vector<D2D1_POINT_2F> trPP = mGame->GetTable()->GetTRPocketPoints();
	double botTable = mGame->GetTable()->GetTLTable().y + mGame->GetTable()->GetTableWidth();
	double botScreen = mGame->GetRenderTarget()->GetSize().height;
	mY = botScreen - mBorderHeight;
	mX = mGame->GetTable()->GetTLTable().x;
	double dif = mGame->GetRenderTarget()->GetSize().width - 2 * mX;
	mBorderWidth = dif;
	mWidth = 0.95 * mBorderWidth;
}

/**
* Draw the power bar with its border
* \param graphics: The graphics object we are using to draw
*/
void CPowerBar::Draw(ID2D1HwndRenderTarget* graphics)
{
	D2D1_POINT_2F start = D2D1::Point2F(mX + (mBorderWidth - mWidth) / 2, mY + (mBorderHeight - mHeight) / 2);
	D2D1_POINT_2F end = D2D1::Point2F(start.x + mWidth, start.y);
	mPowerBrush->SetStartPoint(start);
	mPowerBrush->SetEndPoint(end);
	
	// Draw the border
	D2D1_RECT_F borderRect = D2D1::RectF(mX, mY, mX + mBorderWidth, mY + mBorderHeight);
	graphics->FillRectangle(borderRect, mWoodBrush);

	D2D1_RECT_F powerRect = D2D1::RectF(mX + (mBorderWidth - mWidth) / 2, mY + (mBorderHeight - mHeight) / 2,
		mX + (mBorderWidth - mWidth) / 2 + mWidth, mY + (mBorderHeight - mHeight) / 2 + mHeight);
	// If a power amount has been determined, fill in the power bar with a 
	// gradient brush
	if (mPower > 0)
	{
		graphics->FillRectangle(powerRect, mPowerBrush);
	}
	double blackL = mX + (mBorderWidth - mWidth) / 2 + mPower * mWidth / mMaxPower;
	double blackT = mY + (mBorderHeight - mHeight) / 2;
	double blackR = blackL + mWidth - floor(mPower * mWidth / mMaxPower);
	double blackB = blackT + mHeight;
	D2D1_RECT_F backgroundRect = D2D1::RectF(blackL, blackT, blackR, blackB);

	graphics->FillRectangle(backgroundRect, mBlackBrush);
	if (mPower > mMaxPower - 1)
	{
		mBurstSign->Draw(graphics);
	}
	//graphics->DrawEllipse(D2D1::Ellipse(end, 10, 10), mBlackBrush);
}

/**
* Check if a click what inside the power bar or now
* \param x: The x coordinate of the mouse click
* \param y: The y coordinate of the mouse click
*/
bool CPowerBar::HitTest(int x, int y)
{
	double leftBoundary = mX + (mBorderWidth - mWidth) / 2;
	double rightBoundary = leftBoundary + mWidth;
	double topBoundary = mY + (mBorderHeight - mHeight) / 2;
	double bottomBoundary = topBoundary + mHeight;

	if (x >= leftBoundary && x <= rightBoundary && y >= topBoundary && y <= bottomBoundary)
	{
		return true;
	}
	return false;
}

/**
* Set the power of the shot based on where the user click in the power bar
* \param x: The x coordinate of the click inside the power bar from the user
*/
void CPowerBar::SetPower(int x)
{
	double leftBoundary = mX + (mBorderWidth - mWidth) / 2;
	double power = (x - leftBoundary) / mWidth;
	if (power >= 1)
	{
		power = 1;
	}
	else if (power <= 0)
	{
		power = 0;
	}
	mPower = power * mMaxPower;
}

/**
* Change the power level
* \param delta: The amount to change the power by
*/
void CPowerBar::ChangePower(int delta)
{
	mPower += delta;
	if (mPower > mMaxPower)
	{
		mPower = mMaxPower;
	}
	else if (mPower < 0)
	{
		mPower = 0;
	}
}

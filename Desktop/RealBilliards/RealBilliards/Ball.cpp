/**
* file: Ball.cpp
* author: Justin Marinelli
*/


#include <memory>
#include "Ball.h"
#include <math.h>  
#include <algorithm>    
#include "Game.h"
#include <conio.h>
#include "d2d1.h"

#define PI 3.14159265


using namespace std;

/** Constructor
 * \param game The game this is a part of
 * \param the Id of this game item
*/
CBall::CBall(CGame* game) : CGameItem(game, this->GetId())
{

	
}

/**
 * Destructor
 */
CBall::~CBall()
{
}

void CBall::SetColor()
{
	int brushIndex = _wtoi(GetId());
	if (brushIndex > 8)
	{
		brushIndex -= 8;
		ConfigureStripe();
	}
	mColoredBrush = GetGame()->GetBallBrushes()[brushIndex];
	mWhiteBrush = GetGame()->GetBallBrushes()[0];
	mTextBrush = GetGame()->GetBallBrushes()[8];
}

/**
* Configure the correct dimensions for the stripe of the ball
*/
void CBall::ConfigureStripe()
{
	mStripeHeight = diameter / 2;
	mStripeLength = 2 * sqrt(mRad * mRad - 0.25 * mStripeHeight * mStripeHeight);

}


/**
* Handle updates in time of a ball
*
* This is called before we draw and allows us to
* move a ball. We add our speed times the amount
* of time that has elapsed.
* \param elapsed Time elapsed since the class call
*/
void CBall::Update(double elapsed)
{

	this->SetVelocityX(this->GetVelocityX() + this->GetAcceleration() * this->GetVelocityX() * elapsed);
	this->SetVelocityY(this->GetVelocityY() + this->GetAcceleration() * this->GetVelocityY() * elapsed);

	// If velocity is very low, set it to 0
	if (abs(this->GetVelocityX()) <= 5)
	{

		this->SetVelocityX(0.0);

	}
	if (abs(this->GetVelocityY()) <= 5)
	{

		this->SetVelocityY(0.0);

	}

	double xGoal = this->GetX() + this->GetVelocityX() * elapsed;
	double yGoal = this->GetY() + this->GetVelocityY() * elapsed;
	pair<double, double> newCoords = LinearInterpolate(xGoal, yGoal);
	SetX(newCoords.first);
	SetY(newCoords.second);
	AddLoc(pair<double, double>(GetCenter().first, GetCenter().second));


}

/**
* Draw the ball with as a circle
* \param graphics The GDI+ graphics context to draw on
*/
void CBall::Draw(ID2D1HwndRenderTarget* graphics)
{

	

	for (pair<double, double> loc : GetPrevLocs())
	{
		// graphics->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(loc.first, loc.second), 10, 10), GetGame()->GetBallBrushes()[0]);
	}



	if (wcstol(this->GetId(), nullptr, 10) < 9)
	{
		graphics->FillEllipse(D2D1::Ellipse(D2D1::Point2F(GetCenter().first, GetCenter().second), mRad, mRad), mColoredBrush);
	}
	else
	{
		double sLeft = GetCenter().first - 0.5 * mStripeLength;
		double sTop = GetCenter().second - 0.5 * mStripeHeight;
		double sRight = sLeft + mStripeLength;
		double sBottom = sTop + mStripeHeight;
		D2D1_RECT_F stripeRect = D2D1::RectF(sLeft, sTop, sRight, sBottom);
		D2D1_POINT_2F center = D2D1::Point2F(GetCenter().first, GetCenter().second);
		D2D1_POINT_2F leftTop = D2D1::Point2F(sLeft, sTop);
		D2D1_POINT_2F leftBottom = D2D1::Point2F(sLeft, sBottom);
		D2D1_POINT_2F rightTop = D2D1::Point2F(sRight, sTop);
		D2D1_POINT_2F rightBottom = D2D1::Point2F(sRight, sBottom);

		GetGame()->GetFactory()->CreatePathGeometry(&mStripe);
		mStripe->Open(&mStripeSink);
		mStripeSink->BeginFigure(
			center,
			D2D1_FIGURE_BEGIN_FILLED
		);
		mStripeSink->AddLine(leftTop);
		mStripeSink->AddArc(D2D1::ArcSegment(leftBottom, D2D1::SizeF(mRad, mRad), 0.0f, D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
		mStripeSink->AddLine(rightTop);
		mStripeSink->AddArc(D2D1::ArcSegment(rightBottom, D2D1::SizeF(mRad, mRad), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
		mStripeSink->EndFigure(D2D1_FIGURE_END_CLOSED);
		mStripeSink->Close();
		
		graphics->FillEllipse(D2D1::Ellipse(D2D1::Point2F(GetCenter().first, GetCenter().second), mRad, mRad), mWhiteBrush);
		graphics->FillGeometry(mStripe, mColoredBrush);
		graphics->FillRectangle(stripeRect, mColoredBrush);
	}

	IDWriteTextFormat* textFormat;
	GetGame()->IsBallOnTable(stoi(GetId())) ? textFormat = GetGame()->GetTextFormat() : textFormat = GetGame()->GetSunkenTextFormat();
	if (wcstol(this->GetId(), nullptr, 10) != 0)
	{
		graphics->FillEllipse(D2D1::Ellipse(D2D1::Point2F(GetCenter().first, GetCenter().second), mStripeHeight / 2, mStripeHeight / 2), mWhiteBrush);
		double squareHWid = (mRad / 2) * cos(PI / 4);
		D2D1_RECT_F textRect = D2D1::RectF(GetCenter().first - mStripeHeight / 2, GetCenter().second - mStripeHeight / 2, GetCenter().first + mStripeHeight / 2, GetCenter().second + mStripeHeight / 2);
		//graphics->DrawRectangle(textRect, GetGame()->GetBallBrushes()[8]);
		size_t size = wcslen(GetId());
		graphics->DrawText(
			GetId(),
			size,
			textFormat,
			textRect,
			mTextBrush
		);
	}


}

std::pair<double, double> CBall::GetCenter()
{
	return std::pair<double, double>(this->GetX() + this->GetDiameter() / 2,
		this->GetY() + this->GetDiameter() / 2);
}

void CBall::SetMass()
{

	if (this->GetId() == L"0")
	{

		this->mass = 0.17;

	}
	else
	{

		this->mass = 0.16;

	}

}

void CBall::SetId(const wchar_t* id)
{
	CGameItem::SetId(id);
	this->SetMass();
	

}

/**
 * Test to see if we hit this object with a mouse.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CBall::HitTest(int x, int y)
{
	double centerX = this->GetX() + this->GetDiameter() / 2;
	double centerY = this->GetY() + this->GetDiameter() / 2;

	double distX = abs(centerX - x);
	double distY = abs(y - centerY);
	double dist = sqrt(pow(distX, 2) + pow(distY, 2));

	// Test to see if x, y are in the image
	if (dist > this->GetDiameter())
	{
		// We are outside the image
		return false;
	}
	else
	{

		return true;

	}
}
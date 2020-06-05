/*
* file: Ball.h
* author: Justin Marinelli
*
* This is the class that represents a billiards ball
*/

#pragma once

#include "GameItem.h"

class CBall : public CGameItem
{

public:

	CBall(CGame* game);

	virtual ~CBall();

	void SetColor();

	void ConfigureStripe();


	bool operator ==(std::shared_ptr<CBall> ball) { return this->GetId() == ball->GetId(); }
	bool operator !=(std::shared_ptr<CBall> ball) { return this->GetId() == ball->GetId(); }

	void Update(double elapsed);
	
	// Default constructor (disabled)
	CBall() = delete;

	// Copy constructor (disabled)
	CBall(const CBall&) = delete;

	void Draw(ID2D1HwndRenderTarget* graphics);

	double GetX() { return CGameItem::GetX(); }
	double GetY() { return CGameItem::GetY(); }
	std::pair<double, double> GetCenter();

	double GetAcceleration() { return this->mAcceleration; }


	std::shared_ptr<CGame> GetGame() { return CGameItem::GetGame(); }

	double GetDiameter() { return this->diameter; }
	double GetRadius() { return this->mRad; }
	void SetDiameter(double diameter) { this->diameter = diameter; }
	void SetRadius(double rad) { this->mRad = rad; }
	void SetCenter(double x, double y) { this->SetX(x - diameter / 2); this->SetY(y - diameter / 2); }


	void SetMass();
	double GetMass() { return this->mass; }

	void SetId(const wchar_t* id) override;

	bool HitTest(int x, int y);

private:

	// The diameter of the ball
	double diameter = 20.0;

	// The radius of the ball
	double mRad = 10.0;

	// The mass of the ball in kg
	double mass = 0.0;

	// Acceleration of the ball
	double mAcceleration = -0.5;

	// The brush that paints the colored portion of the ball
	ID2D1SolidColorBrush* mColoredBrush;

	// The brush that paints the white portion of the ball
	ID2D1SolidColorBrush* mWhiteBrush;

	// The brush that paints the text
	ID2D1SolidColorBrush* mTextBrush;

	// The sink that makes up a ball's stripe
	ID2D1GeometrySink* mStripeSink;

	// The ball's stripe
	ID2D1PathGeometry* mStripe;

	// The height of the ball's stripe
	double mStripeHeight = diameter / 2;

	// The width of the ball's stripe, calculated by the ConfigureStripe function
	double mStripeLength = -1;
	

};


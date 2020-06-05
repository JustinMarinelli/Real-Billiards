/*
* file: PowerBar.h
* author: Justin Marinelli
*
* This allows a user to control how much power is used to shoot the cue ball
*/

#include <memory>
#include "BurstSign.h"
#include <d2d1.h>
#include <d2d1helper.h>

#pragma once

class CGame;

class CPowerBar
{
public:

	CPowerBar(CGame* game);

	virtual ~CPowerBar();

	void SetLocation();

	// Default constructor (disabled)
	CPowerBar() = delete;

	// Copy constructor (disabled)
	CPowerBar(const CPowerBar&) = delete;

	void Draw(ID2D1HwndRenderTarget* graphics);

	bool HitTest(int x, int y);

	void SetPower(int x);

	void ChangePower(int delta);

	double GetPower() { return this->mPower; }

	void ResetPower() { this->mPower = 0; }

	void SetAdjusting(bool adjusting) { this->mAdjusting = adjusting; }

	bool GetAdjusting() { return this->mAdjusting; }

	double GetMaxPower() { return this->mMaxPower; }

	void SetWoodBrush(ID2D1BitmapBrush* brush) { mWoodBrush = brush; }

	void SetPowerBrush(ID2D1LinearGradientBrush* brush) { mPowerBrush = brush; }

	void SetBackgroundBrush(ID2D1SolidColorBrush* brush) { mBlackBrush = brush; }

	std::shared_ptr<CBurstSign> GetBurstSign() { return mBurstSign; }

private:

	// The game this item is a part of 
	std::shared_ptr<CGame> mGame;

	// X coordinate of the top left corner of the border
	double mX = 0.0;

	// Y coordinate of the top left corner of the border
	double mY = 580;
	
	// Height of the power bar
	double mHeight = 40.0;

	// Width of the power bar
	double mWidth = 680.0;

	// Height of the border of the power bar
	double mBorderHeight = 64.0;

	// Width of the border of the power bar
	double mBorderWidth = 700.0;

	// The maximum power 
	double mMaxPower = 1500000;

	// The current power we have set
	double mPower = 1500000;

	// Determines if the user is currently adjusting the power
	bool mAdjusting = false;

	// The burst sign that is drawn when the max manimizes the power
	std::shared_ptr<CBurstSign> mBurstSign = nullptr;

	// The brush that draws the wood border
	ID2D1BitmapBrush* mWoodBrush;

	// The brush that draws the power gradient
	ID2D1LinearGradientBrush* mPowerBrush;

	// The brush that draws the background of the gradient
	ID2D1SolidColorBrush* mBlackBrush;
};


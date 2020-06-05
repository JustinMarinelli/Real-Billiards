/*
* file: BurstSign.h
* author: Justin Marinelli
*
* Burst sign graphic
*/

#include <memory>
#include <vector>
#include <string>
#include <d2d1.h>
#include <d2d1helper.h>


#pragma once

class CGame;

class CBurstSign
{
public:

	CBurstSign(CGame* game, int numPoints, double x, double y, std::string text);

	void GenerateVertices();

	virtual ~CBurstSign();

	void Draw(ID2D1HwndRenderTarget* graphics);

	void DrawMessage(ID2D1HwndRenderTarget* graphics);

	// Default constructor (disabled)
	CBurstSign() = delete;

	// Copy constructor (disabled)
	CBurstSign(const CBurstSign&) = delete;

	void SetBackgroundBrush(ID2D1SolidColorBrush* brush) { mBackgroundBrush = brush; }
	void SetTextBrush(ID2D1SolidColorBrush* brush) { mTextBrush = brush; }

private:

	// The game this item is a part of 
	std::shared_ptr<CGame> mGame;

	// The radius of the outer circle 
	double mOuterRad = 80.0;

	// The radius of the inner circle
	double mInnerRad = 55.0;

	// The number of points on the burst sign
	int mNumPoints = 0;

	// The points used in the sign
	std::vector<D2D1_POINT_2F> mPoints;

	// The x coordinate of the burst sign
	double mX = 0.0;

	// The y coordinate of the burst sign
	double mY = 0.0;

	std::string mText = "";
	
	// The sink that makes up a burst sign
	ID2D1GeometrySink* mBurstSink;

	// The brust sign
	ID2D1PathGeometry* mBurst;

	// The brush that paints the background of the burst sign
	ID2D1SolidColorBrush* mBackgroundBrush;

	// The brush that paints the text
	ID2D1SolidColorBrush* mTextBrush;
};


/*
* file: Table.h
* author: Justin Marinelli
*
* This class represents a billiards table
*/

#include <memory>
#include <vector>
#include <d2d1.h>
#include <d2d1helper.h>

#pragma once

class CGame;

class CTable
{

public:

	CTable(CGame* game);

	virtual ~CTable();

	void ConfigureTable();

	void Draw(ID2D1HwndRenderTarget* graphics);

	double GetRightCushionX() { return this->mRightCushionX; }
	double GetLeftCushionX() { return this->mLeftCushionX; }
	double GetTopCushionY() { return mTLPocketPoints[2].y; }
	double GetBottomCushionY() { return this->mBottomCushionY; }
	std::vector<D2D1_POINT_2F> GetTLPocketPoints() { return this->mTLPocketPoints; }
	std::vector<D2D1_POINT_2F> GetTRPocketPoints() { return this->mTRPocketPoints; }
	std::vector<D2D1_POINT_2F> GetBLPocketPoints() { return this->mBLPocketPoints; }
	std::vector<D2D1_POINT_2F> GetBRPocketPoints() { return this->mBRPocketPoints; }
	std::vector<D2D1_POINT_2F> GetTMPocketPoints() { return this->mTMPocketPoints; }
	std::vector<D2D1_POINT_2F> GetBMPocketPoints() { return this->mBMPocketPoints; }
	std::vector<D2D1_POINT_2F> GetPocket() { return this->mPocketOrigins; }
	std::pair<double, double> GetRackPoint() { return this->mRackPoint; }
	std::pair<double, double> GetScratchPoint() { return this->mScratchPoint; }
	void SetFeltBrush(ID2D1SolidColorBrush* brush) { mFeltBrush = brush; }
	void SetPocketBrush(ID2D1SolidColorBrush* brush) { mPocketBrush = brush; }
	void SetWoodBrush(ID2D1BitmapBrush* brush) { mWoodBrush = brush; }
	void SetCenter(std::pair<long, long> center) { mCenter = center; }
	D2D1_POINT_2F GetTLTable() { return mTLTable; }
	double GetTableWidth() { return mWidTable; }



private:

	// The game this table is a part of 
	std::shared_ptr<CGame> mGame;

	ID2D1GeometrySink* mFeltSink;

	ID2D1PathGeometry* mFelt;

	ID2D1GeometrySink* mOutlineSink;

	ID2D1PathGeometry* mOutline;

	// The brush that draws the felt
	ID2D1SolidColorBrush* mFeltBrush;

	// The brush that draws the pockets
	ID2D1SolidColorBrush* mPocketBrush;

	// The brush that draws the wood border
	ID2D1BitmapBrush* mWoodBrush;

	// The outermost felt rectangle
	D2D1_RECT_F mOuterFelt;

	// The rectangle that makes up the wood of the table
	D2D1_RECT_F mWoodBorder;

	// The x coordinate of the left cushion
	double mLeftCushionX = 318.0;

	// The x coordinate of the right cushion
	double mRightCushionX = 1262.0;

	// The y coordinate of the top cushion
	double mTopCushionY = 143.0;

	// The y coordinate of the bottom cushion
	double mBottomCushionY = 613.0;

	// The length of the table in pixels
	double mLenTable = 0.0;

	// The width of the table in pixels
	double mWidTable = 0.0;

	// The length of the felt in pixels
	double mFeltLen = 0.0;

	// The length of the felt in pixels
	double mFeltWid = 0.0;

	// The width of the rail in pixels
	double mRailWid = 0.0;

	// Point that the 1 ball is placed on the break
	std::pair<double, double> mRackPoint = std::make_pair<double, double>(0.0, 0.0);

	// Point that the cue ball is placed on the break and scratches
	std::pair<double, double> mScratchPoint = std::make_pair<double, double>(0.0, 0.0);

	// The point representing the top left of the table
	D2D1_POINT_2F mTLTable;

	// The point representing the top left of the felt area
	D2D1_POINT_2F mTLFelt;

	// Contains the origin points of the pockets
	std::vector<D2D1_POINT_2F> mPocketOrigins;

	// Contains the points that make up the top left pocket
	std::vector<D2D1_POINT_2F> mTLPocketPoints;

	// Contains the points that make up the top right pocket
	std::vector<D2D1_POINT_2F> mTRPocketPoints;

	// Contains the points that make up the bottom left pocket
	std::vector<D2D1_POINT_2F> mBLPocketPoints;

	// Contains the points that make up the bottom right pocket
	std::vector<D2D1_POINT_2F> mBRPocketPoints;

	// Contains the points that make up the top middle pocket
	std::vector<D2D1_POINT_2F> mTMPocketPoints;

	// Contains the points that make up the bottom middle pocket
	std::vector<D2D1_POINT_2F> mBMPocketPoints;

	// The sink that makes up the top left corner pocket
	ID2D1GeometrySink* mTLPocketSink;

	// The sink that makes up the top right corner pocket
	ID2D1GeometrySink* mTRPocketSink;

	// The sink that makes up the bottom left corner pocket
	ID2D1GeometrySink* mBLPocketSink;

	// The sink that makes up the bottom right corner pocket
	ID2D1GeometrySink* mBRPocketSink;

	// The sink that makes up the top middle pocket
	ID2D1GeometrySink* mTMPocketSink;

	// The sink that makes up the bottom middle pocket
	ID2D1GeometrySink* mBMPocketSink;

	// The path that makes up the top left corner pocket
	ID2D1PathGeometry* mTLPocket;

	// The path that makes up the bottom left corner pocket
	ID2D1PathGeometry* mBLPocket;

	// The path that makes up the top right corner pocket
	ID2D1PathGeometry* mTRPocket;

	// The path that makes up the bottom right corner pocket
	ID2D1PathGeometry* mBRPocket;

	// The path that makes up the top middle pocket
	ID2D1PathGeometry* mTMPocket;

	// The path that makes up the bottom middle pocket
	ID2D1PathGeometry* mBMPocket;

	// Determines if the table is configured or not
	bool mIsConfigured = false;

	// The center of the table
	std::pair<long, long> mCenter = std::make_pair<long, long>(0, 0);

};


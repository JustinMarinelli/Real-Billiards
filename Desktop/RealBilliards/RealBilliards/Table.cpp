/**
* file: Table.cpp
* author: Justin Marinelli
*/


#include "Table.h"
#include "Game.h"
#include <cstdio>
#include <ctime>
#include <conio.h>
using namespace std;


#define PI 3.14159265

/**
* Constructor
*/
CTable::CTable(CGame* game) : mGame(game)
{


}

/**
* Destructor
*/
CTable::~CTable()
{
}

/**
* Set the correct scale length and set the table dimensions accordingly
*/
void CTable::ConfigureTable()
{
	double tablePercScreen = 0.65;
	mLenTable = 116.0;
	mWidTable = 66.0;
	double scaleFactor = tablePercScreen * mGame->GetRenderTarget()->GetSize().width / mLenTable;
	mGame->SetScaleFactor(scaleFactor);
	mLenTable = scaleFactor * mLenTable;
	mWidTable = scaleFactor * mWidTable;
	double y = 0.5 * (mGame->GetRenderTarget()->GetSize().width - mLenTable);
	mTLTable = D2D1::Point2F(0.5 * (mGame->GetRenderTarget()->GetSize().width - mLenTable), 0.5 * (mGame->GetRenderTarget()->GetSize().height - mWidTable));



	mFeltWid = scaleFactor * 50;
	mFeltLen = scaleFactor * 100;
	double edgeWid = scaleFactor * 6;
	mRailWid = scaleFactor * 2;
	mTLFelt = D2D1::Point2F(mTLTable.x + edgeWid, mTLTable.y + edgeWid);
	double bankCornerLength = scaleFactor * (2 / tan(38 * PI / 180));
	double bankMiddleLength = scaleFactor * (2 / tan(70 * PI / 180));
	double pocketRad = 1.25 * bankCornerLength;
	double midPocketRad = 1.5 * bankCornerLength;

	D2D1_POINT_2F tlPocket1 = mTLFelt;
	D2D1_POINT_2F tlPocket2 = D2D1::Point2F(mTLFelt.x + pocketRad, mTLFelt.y);
	D2D1_POINT_2F tlPocket3 = D2D1::Point2F(tlPocket2.x + bankCornerLength, tlPocket2.y + mRailWid);
	D2D1_POINT_2F tlPocket5 = D2D1::Point2F(tlPocket1.x, tlPocket1.y + pocketRad);
	D2D1_POINT_2F tlPocket4 = D2D1::Point2F(tlPocket5.x + mRailWid, tlPocket5.y + bankCornerLength);


	D2D1_POINT_2F trPocket2 = D2D1::Point2F(tlPocket1.x + 2 * mRailWid + mFeltLen, tlPocket1.y);
	D2D1_POINT_2F trPocket1 = D2D1::Point2F(trPocket2.x - pocketRad, trPocket2.y);
	D2D1_POINT_2F trPocket5 = D2D1::Point2F(trPocket1.x - bankCornerLength, trPocket1.y + mRailWid);
	D2D1_POINT_2F trPocket3 = D2D1::Point2F(trPocket2.x, trPocket2.y + pocketRad);
	D2D1_POINT_2F trPocket4 = D2D1::Point2F(trPocket3.x - mRailWid, trPocket3.y + bankCornerLength);

	D2D1_POINT_2F brPocket4 = D2D1::Point2F(trPocket2.x, trPocket2.y + mFeltWid + 2 * mRailWid);
	D2D1_POINT_2F brPocket3 = D2D1::Point2F(brPocket4.x, brPocket4.y - pocketRad);
	D2D1_POINT_2F brPocket2 = D2D1::Point2F(brPocket3.x - mRailWid, brPocket3.y - bankCornerLength);
	D2D1_POINT_2F brPocket5 = D2D1::Point2F(brPocket4.x - pocketRad, brPocket4.y);
	D2D1_POINT_2F brPocket1 = D2D1::Point2F(brPocket5.x - bankCornerLength, brPocket5.y - mRailWid);

	D2D1_POINT_2F blPocket4 = D2D1::Point2F(tlPocket1.x, tlPocket1.y + 2 * mRailWid + mFeltWid);
	D2D1_POINT_2F blPocket3 = D2D1::Point2F(blPocket4.x + pocketRad, blPocket4.y);
	D2D1_POINT_2F blPocket2 = D2D1::Point2F(blPocket3.x + bankCornerLength, blPocket3.y - mRailWid);
	D2D1_POINT_2F blPocket5 = D2D1::Point2F(blPocket4.x, blPocket4.y - pocketRad);
	D2D1_POINT_2F blPocket1 = D2D1::Point2F(blPocket5.x + mRailWid, blPocket5.y - bankCornerLength);

	D2D1_POINT_2F topMiddleOrg = D2D1::Point2F(tlPocket1.x + pocketRad + 0.5 * mFeltLen, tlPocket1.y);
	D2D1_POINT_2F botMiddleOrg = D2D1::Point2F(blPocket4.x + pocketRad + 0.5 * mFeltLen, blPocket4.y);
	double midPocketWid = midPocketRad * 1.2;
	double midPocketHeight = 0.6 * midPocketRad;
	D2D1_POINT_2F midTopPocket1 = D2D1::Point2F(topMiddleOrg.x - midPocketWid / 2.0, topMiddleOrg.y);
	D2D1_POINT_2F midTopPocket2 = D2D1::Point2F(topMiddleOrg.x + midPocketWid / 2.0, topMiddleOrg.y);
	D2D1_POINT_2F midTopPocket3 = D2D1::Point2F(midTopPocket2.x + bankMiddleLength, tlPocket3.y);
	D2D1_POINT_2F midTopPocket4 = D2D1::Point2F(midTopPocket1.x - bankMiddleLength, tlPocket3.y);

	D2D1_POINT_2F midBotPocket4 = D2D1::Point2F(botMiddleOrg.x - midPocketWid / 2.0, botMiddleOrg.y);
	D2D1_POINT_2F midBotPocket3 = D2D1::Point2F(botMiddleOrg.x + midPocketWid / 2.0, botMiddleOrg.y);
	D2D1_POINT_2F midBotPocket1 = D2D1::Point2F(midBotPocket4.x - bankMiddleLength, blPocket2.y);
	D2D1_POINT_2F midBotPocket2 = D2D1::Point2F(midBotPocket3.x + bankMiddleLength, blPocket2.y);

	mLeftCushionX = tlPocket4.x;
	mRightCushionX = trPocket4.x;
	mTopCushionY = tlPocket3.y;
	mBottomCushionY = blPocket2.y;
	pair<double, double> rackP = make_pair<double, double>(tlPocket4.x + mFeltLen * 0.75, tlPocket3.y + mFeltWid * 0.5);
	pair<double, double> scratchP = make_pair<double, double>(tlPocket4.x + mFeltLen * 0.125, tlPocket3.y + mFeltWid * 0.5);
	mRackPoint = rackP;
	mScratchPoint = scratchP;

	mPocketOrigins = { tlPocket1, topMiddleOrg, trPocket2, brPocket3, botMiddleOrg, blPocket4 };
	mTLPocketPoints = { tlPocket1, tlPocket2, tlPocket3, tlPocket4, tlPocket5 };
	mTRPocketPoints = { trPocket1, trPocket2, trPocket3, trPocket4, trPocket5 };
	mBLPocketPoints = { blPocket1, blPocket2, blPocket3, blPocket4, blPocket5 };
	mBRPocketPoints = { brPocket1, brPocket2, brPocket3, brPocket4, brPocket5 };
	mTMPocketPoints = { midTopPocket1, midTopPocket2, midTopPocket3, midTopPocket4, topMiddleOrg };
	mBMPocketPoints = { midBotPocket1, midBotPocket2, midBotPocket3, midBotPocket4, botMiddleOrg };

	// Draw the pockets

	double cornPocketEdge = scaleFactor * 3;
	double cornSlope1 = 1.0;
	double topTLB = tlPocket2.y - cornSlope1 * tlPocket2.x;
	double dist1 = sqrt(pow(tlPocket2.x - tlPocket3.x, 2) + pow(tlPocket2.y - tlPocket3.y, 2));
	double botTLB = tlPocket5.y - cornSlope1 * tlPocket5.x;
	double topTLX = cornPocketEdge * (tlPocket2.x - tlPocket3.x) / dist1;
	D2D1_POINT_2F topEdge = D2D1::Point2F(tlPocket2.x + topTLX, (tlPocket2.x + topTLX) * cornSlope1 + topTLB);
	D2D1_POINT_2F botEdge = D2D1::Point2F(tlPocket5.x + topTLX, (tlPocket5.x + topTLX) * cornSlope1 + botTLB);
	HRESULT hr = S_OK;
	hr = mGame->GetFactory()->CreatePathGeometry(&mTLPocket);
	hr = mTLPocket->Open(&mTLPocketSink);
	mTLPocketSink->BeginFigure(
		topEdge,
		D2D1_FIGURE_BEGIN_FILLED
	);
	mTLPocketSink->AddLine(tlPocket2);
	mTLPocketSink->AddArc(D2D1::ArcSegment(tlPocket5, D2D1::SizeF(pocketRad, pocketRad), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mTLPocketSink->AddLine(botEdge);
	mTLPocketSink->AddArc(D2D1::ArcSegment(topEdge, D2D1::SizeF(pocketRad, pocketRad), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mTLPocketSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	hr = mTLPocketSink->Close();

	double cornSlope2 = -1.0;
	double topTRB = trPocket1.y - cornSlope2 * trPocket1.x;
	double botTRB = trPocket3.y - cornSlope2 * trPocket3.x;
	double topTRX = cornPocketEdge * (trPocket1.x - trPocket5.x) / dist1;
	D2D1_POINT_2F topEdge2 = D2D1::Point2F(trPocket1.x + topTRX, (trPocket1.x + topTRX) * cornSlope2 + topTRB);
	D2D1_POINT_2F botEdge2 = D2D1::Point2F(trPocket3.x + topTRX, (trPocket3.x + topTRX) * cornSlope2 + botTRB);
	hr = S_OK;
	hr = mGame->GetFactory()->CreatePathGeometry(&mTRPocket);
	hr = mTRPocket->Open(&mTRPocketSink);
	mTRPocketSink->BeginFigure(
		topEdge2,
		D2D1_FIGURE_BEGIN_FILLED
	);

	mTRPocketSink->AddLine(trPocket1);
	mTRPocketSink->AddArc(D2D1::ArcSegment(trPocket3, D2D1::SizeF(pocketRad, pocketRad), 0.0f, D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mTRPocketSink->AddLine(botEdge2);
	mTRPocketSink->AddArc(D2D1::ArcSegment(topEdge2, D2D1::SizeF(pocketRad, pocketRad), 0.0f, D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mTRPocketSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	hr = mTRPocketSink->Close();

	double topBRB = brPocket3.y - cornSlope1 * brPocket3.x;
	double botBRB = brPocket5.y - cornSlope1 * brPocket5.x;
	double topBRX = cornPocketEdge * (tlPocket3.x - tlPocket2.x) / dist1;
	D2D1_POINT_2F topEdge3 = D2D1::Point2F(brPocket3.x + topBRX, (brPocket3.x + topBRX) * cornSlope1 + topBRB);
	D2D1_POINT_2F botEdge3 = D2D1::Point2F(brPocket5.x + topBRX, (brPocket5.x + topBRX) * cornSlope1 + botBRB);
	hr = S_OK;
	hr = mGame->GetFactory()->CreatePathGeometry(&mBRPocket);
	hr = mBRPocket->Open(&mBRPocketSink);
	mBRPocketSink->BeginFigure(
		topEdge3,
		D2D1_FIGURE_BEGIN_FILLED
	);

	mBRPocketSink->AddLine(brPocket3);
	mBRPocketSink->AddArc(D2D1::ArcSegment(brPocket5, D2D1::SizeF(pocketRad, pocketRad), 0.0f, D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mBRPocketSink->AddLine(botEdge3);
	mBRPocketSink->AddArc(D2D1::ArcSegment(topEdge3, D2D1::SizeF(pocketRad, pocketRad), 0.0f, D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mBRPocketSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	hr = mBRPocketSink->Close();

	double topBLB = blPocket5.y - cornSlope2 * blPocket5.x;
	double botBLB = blPocket3.y - cornSlope2 * blPocket3.x;
	double topBLX = cornPocketEdge * (tlPocket3.x - tlPocket2.x) / dist1;
	D2D1_POINT_2F topEdge4 = D2D1::Point2F(blPocket5.x - topBLX, (blPocket5.x - topBLX) * cornSlope2 + topBLB);
	D2D1_POINT_2F botEdge4 = D2D1::Point2F(blPocket3.x - topBLX, (blPocket3.x - topBLX) * cornSlope2 + botBLB);

	hr = S_OK;
	hr = mGame->GetFactory()->CreatePathGeometry(&mBLPocket);
	hr = mBLPocket->Open(&mBLPocketSink);
	mBLPocketSink->BeginFigure(
		botEdge4,
		D2D1_FIGURE_BEGIN_FILLED
	);

	mBLPocketSink->AddLine(blPocket3);
	mBLPocketSink->AddArc(D2D1::ArcSegment(blPocket5, D2D1::SizeF(pocketRad, pocketRad), 0.0f, D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mBLPocketSink->AddLine(topEdge4);
	mBLPocketSink->AddArc(D2D1::ArcSegment(botEdge4, D2D1::SizeF(pocketRad, pocketRad), 0.0f, D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mBLPocketSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	hr = mBLPocketSink->Close();


	hr = S_OK;
	hr = mGame->GetFactory()->CreatePathGeometry(&mBMPocket);
	hr = mBMPocket->Open(&mBMPocketSink);
	mBLPocketSink->BeginFigure(
		midTopPocket2,
		D2D1_FIGURE_BEGIN_FILLED
	);

	mBLPocketSink->AddLine(D2D1::Point2F(midTopPocket2.x, midTopPocket2.y - cornPocketEdge));
	mBLPocketSink->AddArc(D2D1::ArcSegment(midBotPocket3, D2D1::SizeF(midPocketWid, midPocketHeight), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mBLPocketSink->AddLine(topEdge4);
	mBLPocketSink->AddArc(D2D1::ArcSegment(midBotPocket3, D2D1::SizeF(midPocketWid, midPocketHeight), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mBLPocketSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	hr = mBLPocketSink->Close();

	hr = S_OK;
	hr = mGame->GetFactory()->CreatePathGeometry(&mTMPocket);
	hr = mTMPocket->Open(&mTMPocketSink);
	mTMPocketSink->BeginFigure(
		midTopPocket2,
		D2D1_FIGURE_BEGIN_FILLED
	);

	mTMPocketSink->AddLine(D2D1::Point2F(midTopPocket2.x, midTopPocket2.y - 1.25 * cornPocketEdge));
	mTMPocketSink->AddArc(D2D1::ArcSegment(D2D1::Point2F(midTopPocket1.x, midTopPocket1.y - 1.25 * cornPocketEdge), D2D1::SizeF(midPocketWid, midPocketHeight), 0.0f, D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mTMPocketSink->AddLine(midTopPocket1);
	mTMPocketSink->AddArc(D2D1::ArcSegment(midTopPocket2, D2D1::SizeF(midPocketWid, midPocketHeight), 0.0f, D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE, D2D1_ARC_SIZE_SMALL));

	mTMPocketSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	hr = mTMPocketSink->Close();
	// Middle pockets
	/**
	mTMPocket.AddLine(midTopPocket2, D2D1::Point2F(midTopPocket2.x, midTopPocket2.y - cornPocketEdge));
	mTMPocket.AddArc(midTopPocket1.x, topMiddleOrg.y - 0.5 * midPocketHeight, midPocketWid, midPocketHeight, 0, 180);
	mTMPocket.AddLine(midTopPocket1, D2D1::Point2F(midTopPocket1.x, midTopPocket1.y - cornPocketEdge));
	mTMPocket.AddArc(midTopPocket1.x, midTopPocket3.y - 2 * cornPocketEdge, midPocketWid, midPocketHeight, 180, 180);

	mBMPocket.AddLine(midBotPocket3, D2D1::Point2F(midBotPocket3.x, midBotPocket3.y + cornPocketEdge));
	mBMPocket.AddArc(midBotPocket4.x, botMiddleOrg.y - 0.5 * midPocketHeight, midPocketWid, midPocketHeight, 0, -180);
	mBMPocket.AddLine(midBotPocket4, D2D1::Point2F(midBotPocket4.x, midBotPocket4.y + cornPocketEdge));
	mBMPocket.AddArc(midBotPocket4.x, midBotPocket4.y + 0.5 * cornPocketEdge, midPocketWid, midPocketHeight, 180, -180);
	*/

	hr = S_OK;
	hr = mGame->GetFactory()->CreatePathGeometry(&mBMPocket);
	hr = mBMPocket->Open(&mBMPocketSink);
	mBMPocketSink->BeginFigure(
		midBotPocket3,
		D2D1_FIGURE_BEGIN_FILLED
	);

	mBMPocketSink->AddLine(D2D1::Point2F(midBotPocket3.x, midBotPocket3.y + 1.25 * cornPocketEdge));
	mBMPocketSink->AddArc(D2D1::ArcSegment(D2D1::Point2F(midBotPocket4.x, midBotPocket4.y + 1.25 * cornPocketEdge), D2D1::SizeF(midPocketWid, midPocketHeight), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mBMPocketSink->AddLine(midBotPocket4);
	mBMPocketSink->AddArc(D2D1::ArcSegment(midBotPocket3, D2D1::SizeF(midPocketWid, midPocketHeight), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));

	mBMPocketSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	hr = mBMPocketSink->Close();


	hr = S_OK;
	hr = mGame->GetFactory()->CreatePathGeometry(&mFelt);
	hr = mFelt->Open(&mFeltSink);
	mFeltSink->BeginFigure(
		tlPocket2,
		D2D1_FIGURE_BEGIN_FILLED
	);
	/**
		newShapeSink->AddArc(
		D2D1::ArcSegment(
			points[1], // end point
			D2D1::SizeF(25, 25),
			0.0f, // rotation angle
			D2D1_SWEEP_DIRECTION_CLOCKWISE,
			D2D1_ARC_SIZE_LARGE
		));
	*/
	mFeltSink->AddArc(D2D1::ArcSegment(tlPocket5, D2D1::SizeF(pocketRad, pocketRad), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mFeltSink->AddLine(tlPocket4);
	mFeltSink->AddLine(blPocket1);
	mFeltSink->AddLine(blPocket5);
	mFeltSink->AddArc(D2D1::ArcSegment(blPocket3, D2D1::SizeF(pocketRad, pocketRad), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mFeltSink->AddLine(blPocket2);
	mFeltSink->AddLine(midBotPocket1);
	mFeltSink->AddLine(midBotPocket4);
	mFeltSink->AddArc(D2D1::ArcSegment(midBotPocket3, D2D1::SizeF(midPocketWid, midPocketHeight), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mFeltSink->AddLine(midBotPocket2);
	mFeltSink->AddLine(brPocket1);
	mFeltSink->AddLine(brPocket5);
	mFeltSink->AddArc(D2D1::ArcSegment(brPocket3, D2D1::SizeF(pocketRad, pocketRad), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mFeltSink->AddLine(brPocket2);
	mFeltSink->AddLine(trPocket4);
	mFeltSink->AddLine(trPocket3);
	mFeltSink->AddArc(D2D1::ArcSegment(trPocket1, D2D1::SizeF(pocketRad, pocketRad), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mFeltSink->AddLine(trPocket5);
	mFeltSink->AddLine(midTopPocket3);
	mFeltSink->AddLine(midTopPocket2);
	mFeltSink->AddArc(D2D1::ArcSegment(midTopPocket1, D2D1::SizeF(midPocketWid, midPocketHeight), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
	mFeltSink->AddLine(midTopPocket4);
	mFeltSink->AddLine(tlPocket3);
	mFeltSink->AddLine(tlPocket2);
	mFeltSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	hr = mFeltSink->Close();

	hr = S_OK;
	hr = mGame->GetFactory()->CreatePathGeometry(&mOutline);
	hr = mOutline->Open(&mOutlineSink);
	mOutlineSink->BeginFigure(
		tlPocket2,
		D2D1_FIGURE_BEGIN_FILLED
	);
	mOutlineSink->AddLine(tlPocket3);
	mOutlineSink->AddLine(midTopPocket4);
	mOutlineSink->AddLine(midTopPocket1);
	mOutlineSink->AddLine(tlPocket2);
	mOutlineSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	hr = mOutlineSink->Close();

	mOuterFelt = D2D1::RectF(tlPocket1.x, tlPocket1.y, tlPocket1.x + (trPocket2.x - tlPocket1.x), tlPocket1.y + (blPocket4.y - tlPocket1.y));

	mWoodBorder = D2D1::RectF(mTLTable.x, mTLTable.y, mTLTable.x + mLenTable, mTLTable.y + mWidTable);
}


/**
* Draw the table
* \param graphics The GDI+ graphics context to draw on
*/
void CTable::Draw(ID2D1HwndRenderTarget* graphics)
{
	if (!mIsConfigured)
	{
		ConfigureTable();
		mIsConfigured = true;
	}


	graphics->FillRectangle(mWoodBorder, mWoodBrush);
	graphics->FillRectangle(mOuterFelt, mFeltBrush);
	graphics->DrawRectangle(mOuterFelt, mPocketBrush);
	graphics->FillGeometry(mFelt, mFeltBrush);
	graphics->DrawGeometry(mFelt, mPocketBrush);
	graphics->FillGeometry(mTLPocket, mPocketBrush);
	graphics->FillGeometry(mTRPocket, mPocketBrush);
	graphics->FillGeometry(mBRPocket, mPocketBrush);
	graphics->FillGeometry(mBLPocket, mPocketBrush);
	graphics->FillGeometry(mBMPocket, mPocketBrush);
	graphics->FillGeometry(mTMPocket, mPocketBrush);


}



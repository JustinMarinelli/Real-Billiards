/*
* file: Cue.h
* author: Justin Marinelli
*
* This class represents a billiards cue stick
*/

#pragma once

#include "GameItem.h"


class CCue : public CGameItem
{

public:

	CCue(CGame* game);

	virtual ~CCue();

	// Default constructor (disabled)
	CCue() = delete;

	// Copy constructor (disabled)
	CCue(const CCue&) = delete;

	void TransformPoints(double theta);

	int orientation(D2D1_POINT_2F p, D2D1_POINT_2F q, D2D1_POINT_2F r);

	bool doIntersect(D2D1_POINT_2F p1, D2D1_POINT_2F q1, D2D1_POINT_2F p2, D2D1_POINT_2F q2);

	bool isInside(D2D1_POINT_2F polygon[], int n, D2D1_POINT_2F p);

	void Draw(ID2D1HwndRenderTarget* graphics);

	bool HitTest(int x, int y);

	void Update(double elapsed);

	double GetX() override { return this->mCenterTipX; }
	double GetY() override { return this->mCenterTipY; }
	void SetX(double x)  { CGameItem::SetX(x); }
	void SetY(double y)  { CGameItem::SetY(y); }

	void SetPoint(D2D1_POINT_2F point) { this->mMousePoint = point; }

	bool GetDragged() { return this->mDragged; }
	void SetDragged(bool dragged) { this->mDragged = dragged; }

	void SetShooting() { this->mStage = pullBack; }

	D2D1_POINT_2F GetTipCenter() { return mShaftPoints[9]; }
	D2D1_POINT_2F* GetShaftPoints() { return this->mShaftPoints; }
	D2D1_POINT_2F* GetHandlePoints() { return this->mHandlePoints; }
	int GetStage() { return mStage; }


private:

	// X coordinate of the center of the tip of the cue
	double mCenterTipX = 0.0;

	// Y coordinate of the center of the tip of the cue
	double mCenterTipY = 0.0;

	// Radius of the tip
	double mTipRadius = 2;

	// Radius of the back
	double mBackRadius = 5;

	// Length of the cue in pixels;
	double mLength = 400;

	// Points that make up the shaft
	D2D1_POINT_2F mShaftPoints[10] = {};

	// Points that make up the handle
	D2D1_POINT_2F mHandlePoints[6] = {};

	// Mouse pointer
	D2D1_POINT_2F mMousePoint;

	// Describes if the cue is being dragged by the pointer or not
	bool mDragged = false;

	// Describes if the cue is in the process of shooting
	bool mShooting = false;

	// The stages of the shot process
	enum mStages {aim = 0, pullBack = 1, shoot = 2};

	// Describes the stage of the shot the cue is in
	mStages mStage = aim;

	// Determines if the shot trajectory has been set
	bool mIsShotSet = false;

	// The unit vector of the short trajectory
	std::pair<double, double> mShotTracjectory;

	// The sink that make up the cue's shaft 
	ID2D1GeometrySink* mShaftSink;

	// The cue's shaft
	ID2D1PathGeometry* mShaft;

	// The sink that make up the cue's handle 
	ID2D1GeometrySink* mHandleSink;

	// The cue's handle
	ID2D1PathGeometry* mHandle;

};


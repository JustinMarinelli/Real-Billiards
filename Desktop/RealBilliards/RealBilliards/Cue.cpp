
#include <math.h>
#include "Cue.h"
#include "Game.h"
#include <iostream>
#include<algorithm>
using namespace std;


#define PI 3.14159265


/*
* Constructor
*/
CCue::CCue(CGame* game) : CGameItem(game, this->GetId())
{

	this->SetId(L"CUE");

	/**
	* By default, the center of the cue stick will start 10 pixels above the 
	* center of the cue ball.
	*/
	shared_ptr<CBall> cueBall = this->GetGame()->GetBalls()[0];
	pair<double, double> cueCenter = cueBall->GetCenter();
	this->mCenterTipX = cueCenter.first + 49;
	this->mCenterTipY = cueCenter.second;

	double rotationDeg = atan((this->mMousePoint.x - this->mCenterTipX) / (this->mMousePoint.y - this->mCenterTipY));
	double rotationRad = rotationDeg * PI / 180;

	// Construct points
	double angle = atan((this->mBackRadius - this->mTipRadius) / this->mLength);
	double endShaftHeight = tan(angle) * this->mLength / 2;
	// Points that make up the shaft
	D2D1_POINT_2F centerTip = D2D1::Point2F(this->mCenterTipX, this->mCenterTipY);

	D2D1_POINT_2F topTip = D2D1::Point2F(this->mCenterTipX, this->mCenterTipY - this->mTipRadius);
	D2D1_POINT_2F endShaftTop = D2D1::Point2F(this->mCenterTipX + this->mLength / 2, this->mCenterTipY - endShaftHeight);
	D2D1_POINT_2F bottomTip = D2D1::Point2F(this->mCenterTipX, this->mCenterTipY + this->mTipRadius);
	D2D1_POINT_2F endShaftBottom = D2D1::Point2F(this->mCenterTipX + this->mLength / 2, this->mCenterTipY + endShaftHeight);
	this->mShaftPoints[0] = centerTip;
	this->mShaftPoints[1] = topTip;
	this->mShaftPoints[2] = topTip;
	this->mShaftPoints[3] = endShaftTop;
	this->mShaftPoints[4] = endShaftTop;
	this->mShaftPoints[5] = endShaftBottom;
	this->mShaftPoints[6] = endShaftBottom;
	this->mShaftPoints[7] = bottomTip;
	this->mShaftPoints[8] = bottomTip;
	this->mShaftPoints[9] = centerTip;

	// Points that make up the handle
	D2D1_POINT_2F handleTop = D2D1::Point2F(this->mCenterTipX + this->mLength, this->mCenterTipY - this->mBackRadius);
	D2D1_POINT_2F handleBottom = D2D1::Point2F(this->mCenterTipX + this->mLength, this->mCenterTipY + this->mBackRadius);
	this->mHandlePoints[0] = endShaftTop;
	this->mHandlePoints[1] = handleTop;
	this->mHandlePoints[2] = handleTop;
	this->mHandlePoints[3] = handleBottom;
	this->mHandlePoints[4] = handleBottom;
	this->mHandlePoints[5] = endShaftBottom;
	//PointF handlePoints[] = { endShaftTop, handleTop, handleTop, handleBottom, handleBottom, endShaftBottom };


	for (D2D1_POINT_2F&point : mShaftPoints)
	{
		double difX = point.x - cueCenter.first;
		double difY = point.y - cueCenter.second;
		point.x = cueCenter.first - difX;
		point.y = cueCenter.second - difY;
	}

	for (D2D1_POINT_2F&point : mHandlePoints)
	{
		double difX = point.x - cueCenter.first;
		double difY = point.y - cueCenter.second;
		point.x = cueCenter.first - difX;
		point.y = cueCenter.second - difY;
	}

	if (this->GetGame()->GetUsingAssist())
	{
		shared_ptr<CShotAssistant> assistant = make_shared<CShotAssistant>(GetGame());
		this->GetGame()->SetAssistant(assistant);
	}


}

/*
* Destructor
*/
CCue::~CCue()
{
}

/**
* Draw the pool cue in relation to the cue ball
* \param graphics The GDI+ graphics context to draw on
*/
void CCue::Draw(ID2D1HwndRenderTarget* graphics)
{


	GetGame()->GetFactory()->CreatePathGeometry(&mShaft);
	mShaft->Open(&mShaftSink);
	mShaftSink->BeginFigure(
		mShaftPoints[0],
		D2D1_FIGURE_BEGIN_FILLED
	);
	mShaftSink->AddLines(mShaftPoints, 10);
	mShaftSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	mShaftSink->Close();

	GetGame()->GetFactory()->CreatePathGeometry(&mHandle);
	mHandle->Open(&mHandleSink);
	mHandleSink->BeginFigure(
		mHandlePoints[0],
		D2D1_FIGURE_BEGIN_FILLED
	);
	mHandleSink->AddLines(mHandlePoints, 6);
	mHandleSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	mHandleSink->Close();



	graphics->FillGeometry(mShaft, GetGame()->GetShaftBrush());
	graphics->FillGeometry(mHandle, GetGame()->GetHandleBrush());

	shared_ptr<CBall> cueBall = GetGame()->GetBalls()[0];
	pair<double, double> cueCenter = cueBall->GetCenter();




	if (this->mStage == aim)
	{

		mCenterTipX = cueCenter.first + 49;
		mCenterTipY = cueCenter.second;

	}
	D2D1_POINT_2F p = this->mShaftPoints[9];
	//graphics->DrawEllipse(&pen, Rect(p.x - 5, p.y - 5, 10, 10));
	//graphics->DrawEllipse(&pen, Rect(mMousePoint.x, mMousePoint.y, 10, 10));
	if (this->GetGame()->GetUsingAssist())
	{
		this->GetGame()->GetAssistant()->Show(graphics);
	}

	//Pen hbPen(Color(255, 255, 0, 0));
	D2D1_POINT_2F tip1 = this->mShaftPoints[1];
	D2D1_POINT_2F tip2 = this->mShaftPoints[8];
	D2D1_POINT_2F back1 = this->mHandlePoints[1];
	D2D1_POINT_2F back2 = this->mHandlePoints[4];
	D2D1_POINT_2F backMP = D2D1::Point2F((back1.x + back2.x) / 2, (back1.y + back2.y) / 2);
	D2D1_POINT_2F centerTip = mShaftPoints[0];
	D2D1_POINT_2F hb[5] = { tip1, back1, back2, tip2 };
	//graphics->DrawPolygon(&hbPen, hb, 4);
	//graphics->DrawLine(&hbPen, tlTip, trHandle);
	//graphics->DrawLine(&hbPen, trHandle, brHandle);

	double lenScaleFact = 1.25;
	double widScaleFact = 20;

	double m1 = (back1.y - back2.y) / (back1.x - back2.x);
	if (back1.x == back2.x)
	{
		m1 = 100000;
	}
	double b1 = back1.y - m1 * back1.x;
	double hlfBackWid = sqrt(pow(backMP.x - back2.x, 2) + pow(backMP.y - back2.y, 2));
	double k1 = hlfBackWid + hlfBackWid * (widScaleFact - 1) / 2;
	double x1 = backMP.x + k1 * abs(backMP.x - back1.x) / hlfBackWid;
	double y1 = m1 * x1 + b1;
	D2D1_POINT_2F p1 = D2D1::Point2F(x1, y1);
	double x2 = backMP.x - k1 * abs(backMP.x - back1.x) / hlfBackWid;
	double y2 = m1 * x2 + b1;
	D2D1_POINT_2F p2 = D2D1::Point2F(x2, y2);
	//graphics->DrawLine(&hbPen, p1, p2); // Line between 2 wide points at back
	double b2 = tip1.y - m1 * tip1.x;
	double hlfTipWid = sqrt(pow(mCenterTipX - tip2.x, 2) + pow(mCenterTipY - tip2.y, 2));
	double k2 = hlfTipWid * (widScaleFact - 1) / 2;
	double x3 = centerTip.x + k2 * abs(centerTip.x - tip1.x) / hlfTipWid;
	double y3 = m1 * x3 + b2;
	D2D1_POINT_2F p3 = D2D1::Point2F(x3, y3);
	double x4 = centerTip.x - k2 * abs(centerTip.x - tip1.x) / hlfTipWid;
	double y4 = m1 * x4 + b2;
	D2D1_POINT_2F p4 = D2D1::Point2F(x4, y4);
	//graphics->DrawLine(&hbPen, p3, p4); // Line between 2 wide points at tip
	if (back1.x == back2.x)
	{
		p1 = D2D1::Point2F(backMP.x, backMP.y + 0.5 * widScaleFact * hlfBackWid);
		p2 = D2D1::Point2F(centerTip.x, centerTip.y + 0.5 * widScaleFact * hlfTipWid);
		p3 = D2D1::Point2F(backMP.x, backMP.y - 0.5 * widScaleFact * hlfBackWid);
		p4 = D2D1::Point2F(centerTip.x, centerTip.y - 0.5 * widScaleFact * hlfTipWid);
	}
	double dt = sqrt(pow(p1.x - p3.x, 2) + (p1.y - p3.y, 2));
	D2D1_POINT_2F hbPs[4] = { p1, p3, p4, p2 };

	// The sink that make up the cue's handle 
	ID2D1GeometrySink* hbSink;

	// The cue's handle
	ID2D1PathGeometry* hb1;

	//graphics->DrawPolygon(&hbPen, hbPs, 4);
	/**
	GetGame()->GetFactory()->CreatePathGeometry(&hb1);
	hb1->Open(&hbSink);
	hbSink->BeginFigure(
		hbPs[0],
		D2D1_FIGURE_BEGIN_FILLED
	);
	hbSink->AddLines(hbPs, 4);
	hbSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	hbSink->Close();
	ID2D1SolidColorBrush* bt = GetGame()->GetBallBrushes()[3];
	graphics->DrawGeometry(hb1, bt);
	*/



}


/**
 * Test to see if we hit this object with a mouse.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CCue::HitTest(int x, int y)
{

	/**
	// Get corners of the pool cue
	PointF edge1Handle = this->mHandlePoints[3];
	PointF edge1Tip = this->mShaftPoints[1];
	PointF edge2Handle = this->mHandlePoints[5];
	PointF edge2Tip = this->mShaftPoints[7];

	if ((x > abs(edge1Handle.x) && x < abs(edge1Tip.x)) ||
		(x > abs(edge1Tip.x) && x < abs(edge1Handle.x)))
	{

		// Figure our equations for the lines that run along the edges of the
		// pool cue

		// Line 1
		double mSlope1 = (edge1Handle.y - edge1Tip.y) / (edge1Handle.x - edge1Tip.x);
		double line1 = edge1Tip.y + mSlope1 * ((double)x - edge1Tip.x);

		// Line 2
		double mSlope2 = (edge2Handle.y - edge2Tip.y) / (edge2Handle.x - edge2Tip.x);
		double line2 = edge2Tip.y + mSlope2 * ((double)x - edge2Tip.x);

		// If the pointer clicked between the lines, the cue has been clicked. 
		// 30 pixels in padding has been given to the cue for convenience of the
		// user.
		if (y >= line1 - 30 && y <= line2 + 30)
		{

			return true;

		}

	}

	return false;
	*/

	D2D1_POINT_2F tip1 = this->mShaftPoints[1];
	D2D1_POINT_2F tip2 = this->mShaftPoints[8];
	D2D1_POINT_2F back1 = this->mHandlePoints[1];
	D2D1_POINT_2F back2 = this->mHandlePoints[4];
	D2D1_POINT_2F backMP = D2D1::Point2F((back1.x + back2.x) / 2, (back1.y + back2.y) / 2);
	D2D1_POINT_2F centerTip = mShaftPoints[0];
	D2D1_POINT_2F hb[5] = { tip1, back1, back2, tip2 };
	//graphics->DrawLine(&hbPen, tlTip, trHandle);
	//graphics->DrawLine(&hbPen, trHandle, brHandle);

	double lenScaleFact = 1.25;
	double widScaleFact = 20;

	double m1 = (back1.y - back2.y) / (back1.x - back2.x);
	if (back1.x == back2.x)
	{
		m1 = 100000;
	}
	double b1 = back1.y - m1 * back1.x;
	double hlfBackWid = sqrt(pow(backMP.x - back2.x, 2) + pow(backMP.y - back2.y, 2));
	double k1 = hlfBackWid + hlfBackWid * (widScaleFact - 1) / 2;
	double x1 = backMP.x + k1 * abs(backMP.x - back1.x) / hlfBackWid;
	double y1 = m1 * x1 + b1;
	D2D1_POINT_2F p1 = D2D1::Point2F(x1, y1);
	double x2 = backMP.x - k1 * abs(backMP.x - back1.x) / hlfBackWid;
	double y2 = m1 * x2 + b1;
	D2D1_POINT_2F p2 = D2D1::Point2F(x2, y2);
	double b2 = tip1.y - m1 * tip1.x;
	double hlfTipWid = sqrt(pow(mCenterTipX - tip2.x, 2) + pow(mCenterTipY - tip2.y, 2));
	double k2 = hlfTipWid * (widScaleFact - 1) / 2;
	double x3 = centerTip.x + k2 * abs(centerTip.x - tip1.x) / hlfTipWid;
	double y3 = m1 * x3 + b2;
	D2D1_POINT_2F p3 = D2D1::Point2F(x3, y3);
	double x4 = centerTip.x - k2 * abs(centerTip.x - tip1.x) / hlfTipWid;
	double y4 = m1 * x4 + b2;
	D2D1_POINT_2F p4 = D2D1::Point2F(x4, y4);
	if (back1.x == back2.x)
	{
		p1 = D2D1::Point2F(backMP.x, backMP.y + 0.5 * widScaleFact * hlfBackWid);
		p2 = D2D1::Point2F(centerTip.x, centerTip.y + 0.5 * widScaleFact * hlfTipWid);
		p3 = D2D1::Point2F(backMP.x, backMP.y - 0.5 * widScaleFact * hlfBackWid);
		p4 = D2D1::Point2F(centerTip.x, centerTip.y - 0.5 * widScaleFact * hlfTipWid);
	}
	double dt = sqrt(pow(p1.x - p3.x, 2) + (p1.y - p3.y, 2));
	D2D1_POINT_2F hbPs[4] = { p1, p3, p4, p2 };

	bool inside = isInside(hbPs, 4, D2D1::Point2F(x, y));
	return inside;



}


/**
* Handle updates in time of the pool cue
*
* This is called before we draw and allows us to
* animate the cue. 
* \param elapsed Time elapsed since the class call
*/
void CCue::Update(double elapsed)
{

	pair<double, double> cueCenter = this->GetGame()->GetBalls()[0]->GetCenter();

	switch (this->mStage)
	{
		case aim:
		{
			// Get unit vector from center of the cue ball to the mouse
			double distX = this->mMousePoint.x - cueCenter.first;
			double distY = this->mMousePoint.y - cueCenter.second;
			double dist = sqrt(pow(distX, 2) + pow(distY, 2));
			double unitX = distX / dist;
			double unitY = distY / dist;
			double angle = atan(distY / distX);

			// Transform points of shaft based on the location of the mouse pointer
			if (this->mDragged)
			{
				TransformPoints(angle);
			}

			this->mCenterTipX = cueCenter.first + unitX * 7;
			this->mCenterTipY = cueCenter.second + unitY * 7;
		}
		break;

		case pullBack:
		{

			double distX2 = this->mShaftPoints[0].x - cueCenter.first;
			double distY2 = this->mShaftPoints[0].y - cueCenter.second;
			double dist2 = sqrt(pow(distX2, 2) + pow(distY2, 2));

			if (dist2 < 80)

			{
				double unitX2 = distX2 / dist2;
				double unitY2 = distY2 / dist2;
				if (!mIsShotSet)
				{
					mShotTracjectory = pair<double, double>(unitX2, unitY2);
					mIsShotSet = true;
				}
				double velocity2 = 50;
				this->SetVelocityX(unitX2 * velocity2);
				this->SetVelocityY(unitY2 * velocity2);

				for (D2D1_POINT_2F &point : this->mHandlePoints)
				{


					point.x = point.x + this->GetVelocityX() * elapsed;
					point.y = point.y + this->GetVelocityY() * elapsed;

				}
				for (D2D1_POINT_2F &point : this->mShaftPoints)
				{


					point.x = point.x + this->GetVelocityX() * elapsed;
					point.y = point.y + this->GetVelocityY() * elapsed;

				}

			}
			else
			{

				this->mStage = shoot;

			}
		}
		break;
		case shoot:
		{
			D2D1_POINT_2F tipCenter = this->mShaftPoints[9];
			double distX2 = tipCenter.x - cueCenter.first;
			double distY2 = tipCenter.y - cueCenter.second;
			double dist2 = sqrt(pow(distX2, 2) + pow(distY2, 2));
			if (dist2 > this->GetGame()->GetBalls()[0]->GetDiameter() / 2)
			{
				double unitX2 = distX2 / dist2;
				double unitY2 = distY2 / dist2;
				double velocity2 = 500.0;
				this->SetVelocityX(-mShotTracjectory.first * velocity2);
				this->SetVelocityY(-mShotTracjectory.second *velocity2);
				for (D2D1_POINT_2F& point : this->mHandlePoints)
				{
					point.x = point.x + this->GetVelocityX() * elapsed;
					point.y = point.y + this->GetVelocityY() * elapsed;
				}
				for (D2D1_POINT_2F& point : this->mShaftPoints)
				{
					point.x = point.x + this->GetVelocityX() * elapsed;
					point.y = point.y + this->GetVelocityY() * elapsed;
				}
			}
			else
			{
				this->SetVelocityX(0.0);
				this->SetVelocityY(0.0);
				double unitX2 = distX2 / dist2;
				double unitY2 = distY2 / dist2;
				this->GetGame()->SetShotTaken(true);
				// Get unit vector from center of the cue ball to the mouse
				shared_ptr<CBall> cueBall = this->GetGame()->GetBalls()[0];
				pair<double, double> cueCenter = cueBall->GetCenter();
				double velocity = this->GetGame()->GetPowerBar()->GetPower();
				cueBall->SetVelocityX(-mShotTracjectory.first * velocity);
				cueBall->SetVelocityY(-mShotTracjectory.second * velocity);
				mIsShotSet = false;
				this->mShooting = false;
				this->GetGame()->GetPowerBar()->ResetPower();
				this->mStage = aim;
			}
		}
		
		break;
	}
}

/**
* Transform the set of points that make up the drawing of the cue by a certain 
* angle
* \param theta The angle we are rotation by
*/
void CCue::TransformPoints(double theta)
{

	// Construct points
	double angle = atan((this->mBackRadius - this->mTipRadius) / this->mLength);
	double endShaftHeight = tan(angle) * this->mLength / 2;
	// Points that make up the shaft
	D2D1_POINT_2F centerTip = D2D1::Point2F(this->mCenterTipX, this->mCenterTipY);
	D2D1_POINT_2F topTip = D2D1::Point2F(this->mCenterTipX, this->mCenterTipY - this->mTipRadius);
	D2D1_POINT_2F endShaftTop = D2D1::Point2F(this->mCenterTipX + this->mLength / 2, this->mCenterTipY - endShaftHeight);
	D2D1_POINT_2F bottomTip = D2D1::Point2F(this->mCenterTipX, this->mCenterTipY + this->mTipRadius);
	D2D1_POINT_2F endShaftBottom = D2D1::Point2F(this->mCenterTipX + this->mLength / 2, this->mCenterTipY + endShaftHeight);
	this->mShaftPoints[0] = centerTip;
	this->mShaftPoints[1] = topTip;
	this->mShaftPoints[2] = topTip;
	this->mShaftPoints[3] = endShaftTop;
	this->mShaftPoints[4] = endShaftTop;
	this->mShaftPoints[5] = endShaftBottom;
	this->mShaftPoints[6] = endShaftBottom;
	this->mShaftPoints[7] = bottomTip;
	this->mShaftPoints[8] = bottomTip;
	this->mShaftPoints[9] = centerTip;


	// Points that make up the handle
	D2D1_POINT_2F handleTop = D2D1::Point2F(this->mCenterTipX + this->mLength, this->mCenterTipY - this->mBackRadius);
	D2D1_POINT_2F handleBottom = D2D1::Point2F(this->mCenterTipX + this->mLength, this->mCenterTipY + this->mBackRadius);
	this->mHandlePoints[0] = endShaftTop;
	this->mHandlePoints[1] = handleTop;
	this->mHandlePoints[2] = handleTop;
	this->mHandlePoints[3] = handleBottom;
	this->mHandlePoints[4] = handleBottom;
	this->mHandlePoints[5] = endShaftBottom;


	pair<double, double> cueCenter = this->GetGame()->GetBalls()[0]->GetCenter();
	// Find difference in angle between theta and the angle made with the 
	// center of the cue ball and the tip of the pool cue
	double distX = this->mCenterTipX - cueCenter.first;
	double distY = this->mCenterTipY - cueCenter.second;
	double dist = sqrt(pow(distX, 2) + pow(distY, 2));
	double unitX = distX / dist;
	double unitY = distY / dist;
	double beta = atan(distY / distX);
	double phi = theta - beta;

	if (this->mMousePoint.x < cueCenter.first)
	{

		phi += PI;

	}

	// Transform shaft
	for (D2D1_POINT_2F& point : this->mShaftPoints)
	{

		double newX = cueCenter.first + (point.x - cueCenter.first) * cos(phi) - (point.y - cueCenter.second) * sin(phi);
		double newY = cueCenter.second + (point.x - cueCenter.first) * sin(phi) + (point.y - cueCenter.second) * cos(phi);
		point.x = newX;
		point.y = newY;

	}

	// Transform handle
	for (D2D1_POINT_2F& point : this->mHandlePoints)
	{

		double newX = cueCenter.first + (point.x - cueCenter.first) * cos(phi) - (point.y - cueCenter.second) * sin(phi);
		double newY = cueCenter.second + (point.x - cueCenter.first) * sin(phi) + (point.y - cueCenter.second) * cos(phi);
		point.x = newX;
		point.y = newY;

	}

}

// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool onSegment(D2D1_POINT_2F p, D2D1_POINT_2F q, D2D1_POINT_2F r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;
	return false;
}

// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int CCue::orientation(D2D1_POINT_2F p, D2D1_POINT_2F q, D2D1_POINT_2F r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // colinear 
	return (val > 0) ? 1 : 2; // clock or counterclock wise 
}

// The function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool CCue::doIntersect(D2D1_POINT_2F p1, D2D1_POINT_2F q1, D2D1_POINT_2F p2, D2D1_POINT_2F q2)
{
	// Find the four orientations needed for general and 
	// special cases 
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case 
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases 
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1 
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and p2 are colinear and q2 lies on segment p1q1 
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2 
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2 
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases 
}

// Returns true if the point p lies inside the polygon[] with n vertices 
bool CCue::isInside(D2D1_POINT_2F polygon[], int n, D2D1_POINT_2F p)
{
	// There must be at least 3 vertices in polygon[] 
	if (n < 3)  return false;

	// Create a point for line segment from p to infinite 
	D2D1_POINT_2F extreme = { 10000, p.y };

	// Count intersections of the above line with sides of polygon 
	int count = 0, i = 0;
	do
	{
		int next = (i + 1) % n;

		// Check if the line segment from 'p' to 'extreme' intersects 
		// with the line segment from 'polygon[i]' to 'polygon[next]' 
		if (doIntersect(polygon[i], polygon[next], p, extreme))
		{
			// If the point 'p' is colinear with line segment 'i-next', 
			// then check if it lies on segment. If it lies, return true, 
			// otherwise false 
			if (orientation(polygon[i], p, polygon[next]) == 0)
				return onSegment(polygon[i], p, polygon[next]);

			count++;
		}
		i = next;
	} while (i != 0);

	// Return true if count is odd, false otherwise 
	return count & 1;  // Same as (count%2 == 1) 
}
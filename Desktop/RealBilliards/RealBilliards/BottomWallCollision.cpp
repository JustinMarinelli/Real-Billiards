
#include "BottomWallCollision.h"
#include "Collision.h"
#include "WallCollision.h"
#include "Game.h"
#include "GameItem.h"
#include <memory>
#include <d2d1.h>
#include <d2d1helper.h>
using namespace std;

#define PI 3.14159265


/**
* Constructor
*/
CBottomWallCollision::CBottomWallCollision(shared_ptr<CBall> ball) : CWallCollision(ball)
{

}

/**
* Destructor
*/
CBottomWallCollision::~CBottomWallCollision()
{
}

/**
* Analyze and perform a ball and Bottom wall collision
*/
void CBottomWallCollision::Collide()
{
	auto x = this->GetBall()->GetX();
	pair<double, double> ballCenter = GetBall()->GetCenter();
	auto dist = this->GetDistance();
	double rad = GetBall()->GetDiameter() / 2;

	vector<D2D1_POINT_2F> blPP = GetBall()->GetGame()->GetTable()->GetBLPocketPoints();
	vector<D2D1_POINT_2F> brPP = GetBall()->GetGame()->GetTable()->GetBRPocketPoints();
	vector<D2D1_POINT_2F> bmPP = GetBall()->GetGame()->GetTable()->GetBMPocketPoints();
	vector<double> bankBLResults = GetBankCollision(blPP[1], blPP[2]);
	vector<double> bankMLResults = GetBankCollision(bmPP[3], bmPP[0]);
	vector<double> bankMRResults = GetBankCollision(bmPP[1], bmPP[2]);
	vector<double> bankBRResults = GetBankCollision(brPP[0], brPP[4]);

	if ((this->GetBall() != nullptr && !this->hasCollided()) && this->GetDistance() <= 0)
	{
		if ((ballCenter.first >= blPP[1].x && ballCenter.first <= bmPP[0].x) ||
			(ballCenter.first >= bmPP[1].x && ballCenter.first <= brPP[0].x))
		{
			double m = GetBall()->GetVelocityY() / GetBall()->GetVelocityX();
			double b = ballCenter.second - m * ballCenter.first;
			double boundary = blPP[1].y;
			double xInt = (boundary - b) / m;
			double yInt = boundary;
			double dX = ballCenter.first - xInt;
			double dY = ballCenter.second - yInt;
			double dist = sqrt(dX * dX + dY * dY) + 1;
			double diag = sqrt(rad * rad + rad * rad);
			pair<double, double> unit(dX / dist, dY / dist);
			GetBall()->SetCenter(xInt + dist * unit.first, yInt + dist * unit.second);
			this->GetBall()->SetVelocityY(-1 * GetBall()->GetVelocityY());
		}
		else if (bankBLResults[0] <= rad)
		{
			PerformBankCollision(bankBLResults);

		}
		else if (bankMLResults[0] <= rad)
		{
			PerformBankCollision(bankMLResults);
		}
		else if (bankMRResults[0] <= rad)
		{
			PerformBankCollision(bankMRResults);
		}
		else if (bankBRResults[0] <= rad)
		{
			PerformBankCollision(bankBRResults);
		}
	}

	if (this->GetBall() != nullptr && this->GetDistance() > 0 && 
		this->GetBall()->GetY() < this->GetBall()->GetGame()->GetTable()->GetBottomCushionY())
	{
		this->SetCollided(false);
	}


}

/**
* Calculate the distance between the ball and the Bottom cushion
*/
double CBottomWallCollision::GetDistance()
{
	return this->GetBall()->GetGame()->GetTable()->GetBottomCushionY() -
		(this->GetBall()->GetY() + this->GetBall()->GetDiameter());
}


#include "LeftWallCollision.h"
#include "Collision.h"
#include "WallCollision.h"
#include "Game.h"
#include "GameItem.h"
#include <memory>

using namespace std;


#define PI 3.14159265


/**
* Constructor
*/
CLeftWallCollision::CLeftWallCollision(shared_ptr<CBall> ball) : CWallCollision(ball)
{

}

/**
* Destructor
*/
CLeftWallCollision::~CLeftWallCollision()
{
}

/**
* Analyze and perform a ball and left wall collision
*/
void CLeftWallCollision::Collide()
{
	auto x = this->GetBall()->GetX();
	double rad = GetBall()->GetDiameter() / 2;
	auto dist = this->GetDistance();
	pair<double, double> ballCenter = GetBall()->GetCenter();

	vector<D2D1_POINT_2F> tlPP = GetBall()->GetGame()->GetTable()->GetTLPocketPoints();
	vector<D2D1_POINT_2F> blPP = GetBall()->GetGame()->GetTable()->GetBLPocketPoints();
	vector<double> bankTLResults = GetBankCollision(tlPP[4], tlPP[3]);
	vector<double> bankBLResults = GetBankCollision(blPP[4], blPP[0]);

	if ((this->GetBall() != nullptr && !this->hasCollided()) && this->GetDistance() <= 0)
	{

		if (this->GetBall()->GetCenter().second >= tlPP[3].y && this->GetBall()->GetCenter().second <= blPP[0].y)
		{
			double m = GetBall()->GetVelocityY() / GetBall()->GetVelocityX();
			double b = ballCenter.second - m * ballCenter.first;
			double boundary = tlPP[3].x;
			double xInt = boundary;
			double yInt = m * xInt + b;
			double dX = ballCenter.first - xInt;
			double dY = ballCenter.second - yInt;
			double dist = sqrt(dX * dX + dY * dY) + 1;
			double diag = sqrt(rad * rad + rad * rad);
			pair<double, double> unit(dX / dist, dY / dist);
			GetBall()->SetCenter(xInt + dist * unit.first, yInt + dist * unit.second);
			this->GetBall()->SetVelocityX(-1 * GetBall()->GetVelocityX());
		}
		else if (bankTLResults[0] <= rad)
		{
			PerformBankCollision(bankTLResults);
		}
		else if (bankBLResults[0] <= rad)
		{
			PerformBankCollision(bankBLResults);
		}
		

	}
	if (this->GetBall() != nullptr && this->GetDistance() > 0 &&
		this->GetBall()->GetX() > this->GetBall()->GetGame()->GetTable()->GetLeftCushionX())
	{

		this->SetCollided(false);

	}

}

/**
* Calculate the distance between the ball and the left cushion
*/
double CLeftWallCollision::GetDistance()
{
	return this->GetBall()->GetX() -
		this->GetBall()->GetGame()->GetTable()->GetLeftCushionX();
}

#include "RightWallCollision.h"
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
CRightWallCollision::CRightWallCollision(shared_ptr<CBall> ball) : CWallCollision(ball)
{

}

/**
* Destructor
*/
CRightWallCollision::~CRightWallCollision()
{
}

/**
* Analyze and perform a ball and Right wall collision
*/
void CRightWallCollision::Collide()
{
	auto x = this->GetBall()->GetX();
	double rad = GetBall()->GetDiameter() / 2;
	pair<double, double> ballCenter = GetBall()->GetCenter();
	auto dist = this->GetDistance();

	vector<D2D1_POINT_2F> trPP = GetBall()->GetGame()->GetTable()->GetTRPocketPoints();
	vector<D2D1_POINT_2F> brPP = GetBall()->GetGame()->GetTable()->GetBRPocketPoints();
	vector<double> bankTRResults = GetBankCollision(trPP[2], trPP[3]);
	vector<double> bankBRResults = GetBankCollision(brPP[1], brPP[2]);
	if ((this->GetBall() != nullptr && !this->hasCollided()) && this->GetDistance() <= 0)
	{

		if (ballCenter.second >= trPP[3].y && ballCenter.second <= brPP[1].y)
		{
			double m = GetBall()->GetVelocityY() / GetBall()->GetVelocityX();
			double b = ballCenter.second - m * ballCenter.first;
			double boundary = trPP[3].x;
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
		else if (bankTRResults[0] <= rad)
		{
			PerformBankCollision(bankTRResults);
		}
		else if (bankBRResults[0] <= rad)
		{
			PerformBankCollision(bankBRResults);
		}
	}

	if (this->GetBall() != nullptr && this->GetDistance() > 0 &&
		this->GetBall()->GetX() < this->GetBall()->GetGame()->GetTable()->GetRightCushionX())
	{

		this->SetCollided(false);

	}

}

/**
* Calculate the distance between the ball and the Right cushion
*/
double CRightWallCollision::GetDistance()
{
	return this->GetBall()->GetGame()->GetTable()->GetRightCushionX() -
		(this->GetBall()->GetX() + this->GetBall()->GetDiameter());
}

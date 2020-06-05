
#include "TopWallCollision.h"
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
CTopWallCollision::CTopWallCollision(shared_ptr<CBall> ball) : CWallCollision(ball)
{

}

/**
* Destructor
*/
CTopWallCollision::~CTopWallCollision()
{
}

/**
* Analyze and perform a ball and Top wall collision
*/
void CTopWallCollision::Collide()
{
	auto x = this->GetBall()->GetX();
	auto dist = this->GetDistance();
	pair<double, double> ballCenter = GetBall()->GetCenter();
	vector<D2D1_POINT_2F> tlPP = GetBall()->GetGame()->GetTable()->GetTLPocketPoints();
	vector<D2D1_POINT_2F> trPP = GetBall()->GetGame()->GetTable()->GetTRPocketPoints();
	vector<D2D1_POINT_2F> tmPP = GetBall()->GetGame()->GetTable()->GetTMPocketPoints();


	double rad = GetBall()->GetDiameter() / 2;

	vector<double> bankMLResults = GetBankCollision(tmPP[0], tmPP[3]);
	vector<double> bankMRResults = GetBankCollision(tmPP[1], tmPP[2]);
	vector<double> bankTLResults = GetBankCollision(tlPP[1], tlPP[2]);
	vector<double> bankTRResults = GetBankCollision(trPP[0], trPP[4]);
	vector<double> bankTopResults = GetBankCollision(tlPP[2], tmPP[3]);

	if ((this->GetBall() != nullptr && !this->hasCollided()) && this->GetDistance() <= 0)
	{
		// Determine if the ball is being shot off the angled part of the wall

		
		if ((this->GetBall()->GetCenter().first >= tlPP[2].x && this->GetBall()->GetCenter().first <= tmPP[3].x)
			|| (this->GetBall()->GetCenter().first >= tmPP[2].x && this->GetBall()->GetCenter().first <= trPP[4].x))
		{
			double m = GetBall()->GetVelocityY() / GetBall()->GetVelocityX();
			double b = ballCenter.second - m * ballCenter.first;
			double boundary = tlPP[2].y;
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
		else if (bankMLResults[0] <= rad)
		{
			PerformBankCollision(bankMLResults);

		}
		else if (bankMRResults[0] <= rad)
		{
			PerformBankCollision(bankMRResults);
		}
		else if (bankTLResults[0] <= rad)
		{
			PerformBankCollision(bankTLResults);
		}
		else if (bankTRResults[0] <= rad)
		{
			PerformBankCollision(bankTRResults);
		}
	}
	if (this->GetBall() != nullptr && this->GetDistance() > 0 &&
		this->GetBall()->GetY() > this->GetBall()->GetGame()->GetTable()->GetTopCushionY())
	{

		this->SetCollided(false);
	}

}

/**
* Calculate the distance between the ball and the Top cushion
*/
double CTopWallCollision::GetDistance()
{
	pair<double, double> ballCenter = GetBall()->GetCenter();
	return this->GetBall()->GetY() - 
		this->GetBall()->GetGame()->GetTable()->GetTopCushionY();
}



/**
* file: WallCollision.cpp
* author: Justin Marinelli
*/


#include <vector>
#include <algorithm> 
#include "WallCollision.h"
#include "Game.h"
#include "GameItem.h"

using namespace std;

/**
* Constructor
*/
CWallCollision::CWallCollision(std::shared_ptr<CBall> ball) : CCollision()
{

	this->mBall = ball;

}

/**
* Destructor
*/
CWallCollision::~CWallCollision()
{
}


/**
* Get the distance a ball is from a bank and the normal vector
* \param point1: 1 point making the bank
* \param point2: The other point that makes the bank
* \return: A vector containing the ball's distance from the bank, the x and y 
* coordinates of the intersection between the bank and the ball's velocity vector,
* and the x and y dimensions of a normal vector of the bank.
*/
vector<double> CWallCollision::GetBankCollision(D2D1_POINT_2F point1, D2D1_POINT_2F point2)
{
	pair<double, double> ballCenter = GetBall()->GetCenter();
	double bankAngle = atan2(point1.y - point2.y, (point1.x - point2.x));
	double bankSlope = (point1.y - point2.y) / (point1.x - point2.x);
	double bankB = point1.y - bankSlope * point1.x;
	double normSlope = -1 / bankSlope;
	if (bankSlope == 0)
	{
		normSlope = 1000000;
	}
	double normB = GetBall()->GetCenter().second - normSlope * GetBall()->GetCenter().first;
	double intX = (bankB - normB) / (normSlope - bankSlope);
	double intY = intX * normSlope + normB;
	double rad = GetBall()->GetDiameter() / 2;
	double distToInt = sqrt(pow(intX - ballCenter.first, 2) + pow(intY - ballCenter.second, 2));
	double nX = -sin(bankAngle);
	double nY = cos(bankAngle);
	vector<double> results = { distToInt, intX, intY, nX, nY };
	return results;
}

/**
* Perform a bank off of a banked wall given the details about the reflection
* \param details: A vector containing the ball's distance from the bank, the x and y 
* coordinates of the intersection between the bank and the ball's velocity vector,
* and the x and y dimensions of a normal vector of the bank.
*/
void CWallCollision::PerformBankCollision(vector<double> details)
{
	double rad = GetBall()->GetDiameter() / 2;
	double intX = details[1];
	double intY = details[2];
	double nX = details[3];
	double nY = details[4];
	pair<double, double> ballCenter = GetBall()->GetCenter();
	double difX = ballCenter.first - intX;
	double difY = ballCenter.second - intY;
	double dist = sqrt(difX * difX + difY * difY);
	pair<double, double> unit(difX / dist, difY / dist);
	double dot = GetBall()->GetVelocityX() * nX + GetBall()->GetVelocityY() * nY;
	GetBall()->SetCenter(intX + unit.first * rad, intY + unit.second * rad);
	GetBall()->SetVelocityX(GetBall()->GetVelocityX() - 2 * dot * nX);
	GetBall()->SetVelocityY(GetBall()->GetVelocityY() - 2 * dot * nY);
}
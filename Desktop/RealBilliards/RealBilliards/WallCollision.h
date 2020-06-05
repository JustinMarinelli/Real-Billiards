/*
* file: WallCollision.h
* author: Justin Marinelli
*
* This class will analyze and perform a wall collision
*/

#pragma once
#include <vector>
#include "Collision.h"

class CWallCollision : public CCollision
{

public:

	CWallCollision(std::shared_ptr<CBall> ball);

	virtual ~CWallCollision();

	virtual std::vector<double> GetBankCollision(D2D1_POINT_2F point1, D2D1_POINT_2F point2);

	virtual void PerformBankCollision(std::vector<double> details);

	// Default constructor (disabled)
	CWallCollision() = delete;

	// Copy constructor (disabled)
	CWallCollision(const CBall&) = delete;

	virtual void Collide() = 0;

	std::shared_ptr<CBall> GetBall() { return this->mBall; }

	bool hasCollided() { return CCollision::GetCollided(); }

private:

	std::shared_ptr<CBall> mBall = nullptr;

};


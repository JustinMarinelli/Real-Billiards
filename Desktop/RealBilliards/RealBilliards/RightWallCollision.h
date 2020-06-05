/*
* file: RightWallCollision.h
* author: Justin Marinelli
*
* This class will analyze and perform a right wall collision
*/

#pragma once

#include "WallCollision.h"
#include "Collision.h"

class CRightWallCollision : public CWallCollision
{

public:


	CRightWallCollision(std::shared_ptr<CBall> ball);

	virtual ~CRightWallCollision();

	// Default constructor (disabled)
	CRightWallCollision() = delete;

	// Copy constructor (disabled)
	CRightWallCollision(const CBall&) = delete;

	void Collide() override;

	bool GetCollided() { return CCollision::GetCollided(); }

	double GetDistance() override;

	std::shared_ptr<CBall> GetBall() { return CWallCollision::GetBall(); }

};


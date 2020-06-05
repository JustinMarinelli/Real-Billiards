/*
* file: LeftWallCollision.h
* author: Justin Marinelli
*
* This class will analyze and perform a left wall collision
*/

#pragma once

#include "WallCollision.h"
#include "Collision.h"

class CLeftWallCollision : public CWallCollision
{

public:


	CLeftWallCollision(std::shared_ptr<CBall> ball);

	virtual ~CLeftWallCollision();

	// Default constructor (disabled)
	CLeftWallCollision() = delete;

	// Copy constructor (disabled)
	CLeftWallCollision(const CBall&) = delete;

	void Collide() override;

	bool GetCollided() { return CCollision::GetCollided(); }

	double GetDistance() override;

	std::shared_ptr<CBall> GetBall() { return CWallCollision::GetBall(); }

};


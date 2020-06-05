/*
* file: TopWallCollision.h
* author: Justin Marinelli
*
* This class will analyze and perform a top wall collision
*/

#pragma once

#include "WallCollision.h"
#include "Collision.h"

class CTopWallCollision : public CWallCollision
{

public:


	CTopWallCollision(std::shared_ptr<CBall> ball);

	virtual ~CTopWallCollision();

	// Default constructor (disabled)
	CTopWallCollision() = delete;

	// Copy constructor (disabled)
	CTopWallCollision(const CBall&) = delete;

	void Collide() override;

	bool GetCollided() { return CCollision::GetCollided(); }

	double GetDistance() override;

	std::shared_ptr<CBall> GetBall() { return CWallCollision::GetBall(); }

};


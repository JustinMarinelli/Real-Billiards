/*
* file: BottomWallCollision.h
* author: Justin Marinelli
*
* This class will analyze and perform a bottom wall collision
*/

#pragma once

#include "WallCollision.h"
#include "Collision.h"

class CBottomWallCollision : public CWallCollision
{

public:


	CBottomWallCollision(std::shared_ptr<CBall> ball);

	virtual ~CBottomWallCollision();

	// Default constructor (disabled)
	CBottomWallCollision() = delete;

	// Copy constructor (disabled)
	CBottomWallCollision(const CBall&) = delete;

	void Collide() override;

	bool GetCollided() { return CCollision::GetCollided(); }

	double GetDistance() override;

	std::shared_ptr<CBall> GetBall() { return CWallCollision::GetBall(); }

};


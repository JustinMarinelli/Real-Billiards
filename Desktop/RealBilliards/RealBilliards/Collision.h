/*
* file: Collision.h
* author: Justin Marinelli
*
* This class will analyze a collision and set the post-collision velocities
* for both balls
*/

#include <memory>
#include "GameItem.h"
#include "Ball.h"

#pragma once

class CCollision
{

public:

	CCollision();

	virtual ~CCollision();

	// Copy constructor (disabled)
	CCollision(const CCollision&) = delete;

	virtual void Collide() {};
	virtual double GetDistance() = 0;
	virtual bool GetCollided() { return this->mCollided; }
	virtual void SetCollided(bool collided) { this->mCollided = collided; }



private:

	// A ball in the collision
	std::shared_ptr<CBall> mBall1 = nullptr;

	// A ball in the collision
	std::shared_ptr<CBall> mBall2 = nullptr;

	// Determines if the collision has taken place yet
	bool mCollided = false;

};


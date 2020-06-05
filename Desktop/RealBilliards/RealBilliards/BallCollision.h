/*
* file: Collision.h
* author: Justin Marinelli
*
* This class will conduct a ball on ball collision
*/

#include <memory>
#include "Collision.h"
#include "Ball.h"

class CBallCollision : public CCollision
{

public:

	CBallCollision(std::shared_ptr<CBall> ball1, std::shared_ptr<CBall> ball2);

	virtual ~CBallCollision();

	void Collide() override;

	bool GetCollided() { return CCollision::GetCollided(); }
	void SetCollided(bool collided) { CCollision::SetCollided(collided); }
	double GetDistance();

	std::shared_ptr<CBall> GetBall1() { return this->mBall1; }
	std::shared_ptr<CBall> GetBall2() { return this->mBall2; }

private:

	// A ball in the collision
	std::shared_ptr<CBall> mBall1 = nullptr;

	// A ball in the collision
	std::shared_ptr<CBall> mBall2 = nullptr;

};
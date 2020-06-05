/**
* file: BallCollision.cpp
* author: Justin Marinelli
*/

#include "BallCollision.h"

using namespace std;

#define PI 3.14159265

/**
* Constructor
*/
CBallCollision::CBallCollision(std::shared_ptr<CBall> ball1, std::shared_ptr<CBall> ball2) : CCollision()
{

	this->mBall1 = ball1;
	this->mBall2 = ball2;

}

/**
* Destructor
*/
CBallCollision::~CBallCollision()
{
}


/**
* Analyze and perform a ball on ball collision
*/
void CBallCollision::Collide()
{
	if (this->mBall1 != nullptr && this->mBall2 != nullptr &&
		this->GetDistance() <= this->mBall1->GetDiameter() / 2 +
		this->mBall2->GetDiameter() / 2)
	{

		double sumOfRadii = this->mBall1->GetDiameter() / 2 +
			this->mBall2->GetDiameter() / 2;

		// Center coordinate of the balls
		pair<double, double> cBall1 = this->mBall1->GetCenter();
		pair<double, double> cBall2 = this->mBall2->GetCenter();

		double distanceX = cBall1.first - cBall2.first;
		double distanceY = cBall1.second - cBall2.second;
		double distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));

		// Get unit vectors
		double unitX = distanceX / distance;
		double unitY = distanceY / distance;

		// Adjust coordinates to eliminate overlap
		this->mBall1->SetX(this->mBall2->GetX() + unitX * (sumOfRadii + 1));
		this->mBall1->SetY(this->mBall2->GetY() + unitY * (sumOfRadii + 1));

		// Find normalized vectors
		double normX = (this->mBall1->GetX() - this->mBall2->GetX()) / this->GetDistance();
		double normY = (this->mBall1->GetY() - this->mBall2->GetY()) / this->GetDistance();

		// Find a tangent vector
		double tanX = -normY;
		double tanY = normX;

		// Dot product along tangent vector
		double dpTan1 = this->mBall1->GetVelocityX() * tanX + this->mBall1->GetVelocityY() * tanY;
		double dpTan2 = this->mBall2->GetVelocityX() * tanX + this->mBall2->GetVelocityY() * tanY;

		// Dot product along normal vector
		double dpNorm1 = this->mBall1->GetVelocityX() * normX + this->mBall1->GetVelocityY() * normY;
		double dpNorm2 = this->mBall2->GetVelocityX() * normX + this->mBall2->GetVelocityY() * normY;

		// Conserve momentum 
		double p1 = (dpNorm1 * (this->mBall1->GetMass() - this->mBall2->GetMass()) + 2.0 * this->mBall2->GetMass() * dpNorm2) / (this->mBall1->GetMass() + this->mBall2->GetMass());
		double p2 = (dpNorm2 * (this->mBall2->GetMass() - this->mBall1->GetMass()) + 2.0 * this->mBall1->GetMass() * dpNorm1) / (this->mBall1->GetMass() + this->mBall2->GetMass());

		// Set velocities
		this->mBall1->SetVelocityX(tanX * dpTan1 + normX * p1);
		this->mBall1->SetVelocityY(tanY * dpTan1 + normY * p1);
		this->mBall2->SetVelocityX(tanX * dpTan2 + normX * p2);
		this->mBall2->SetVelocityY(tanY * dpTan2 + normY * p2);

		/*
		double centerXBall1 = mBall1->GetX() + mBall1->GetDiameter() / 2;
		double centerYBall1 = mBall1->GetY() + mBall1->GetDiameter() / 2;
		double centerXBall2 = mBall2->GetX() + mBall2->GetDiameter() / 2;
		double centerYBall2 = mBall2->GetY() + mBall2->GetDiameter() / 2;

		// Get the distance between the center of the balls
		double distance = this->GetDistance();

		// If the balls are touching, perform the collision.
		if (distance <= this->mBall1->GetDiameter() + this->mBall2->GetDiameter())
		{

			// The slope of the line that passes through the center of both
			// balls
			double slopeThroughCenters =
				(centerYBall2 - centerYBall1) / (centerXBall2 -
					centerXBall1);
			// The angle between a vertical and the deflection direction of
			// ball 1)
			double angleOfVelocity1 = 0.0;
			// The angle between a horizontal line and the deflection
			// direction of ball 2
			double angleOfVelocity2 = 0.0;
			double complimentaryAngle = atan(slopeThroughCenters);


			if (centerXBall1 <= centerXBall2 && centerYBall1 <= centerYBall2)
			{

				angleOfVelocity1 = PI - complimentaryAngle;
				angleOfVelocity2 = complimentaryAngle;

			}
			else if (centerXBall1 >= centerXBall2 && centerYBall1 <= centerYBall2)
			{

				angleOfVelocity1 = -complimentaryAngle;
				angleOfVelocity2 = PI / 2 - complimentaryAngle;

			}
			else if (centerXBall1 >= centerXBall2 && centerYBall1 >= centerYBall2)
			{

				angleOfVelocity1 = -complimentaryAngle;
				angleOfVelocity2 = 3 * PI / 2 - complimentaryAngle;

			}
			else if (centerXBall1 <= centerXBall2 && centerYBall1 >= centerYBall2)
			{

				angleOfVelocity1 = PI - complimentaryAngle;
				angleOfVelocity2 = 3 * PI / 2 - complimentaryAngle;

			}
			else if (centerXBall1 == centerXBall2 || centerYBall1 == centerYBall2)
			{

				angleOfVelocity1 = PI;
				angleOfVelocity2 = 3 * PI;

			}




			double initialVelocityBall1 = this->mBall1->GetVelocity();
			double initialVelocityBall2 = this->mBall2->GetVelocity();
			double initialVelocity = 0.0;
			if (initialVelocityBall1 > initialVelocityBall2)
			{

				initialVelocity = initialVelocityBall1;

			}
			else
			{

				initialVelocity = initialVelocityBall2;

			}
			double finalVelocityBall1 = ((this->mBall1->GetMass() - this->mBall2->GetMass()) * initialVelocity) /
				(this->mBall1->GetMass() + this->mBall2->GetMass());
			double finalVelocityBall2 = (2 * this->mBall1->GetMass() * initialVelocity) /
				(this->mBall1->GetMass() + this->mBall2->GetMass());

			double finalVelocity = 0.0;
			if (finalVelocityBall1 > finalVelocityBall2)
			{

				finalVelocity = finalVelocityBall1;

			}
			else
			{

				finalVelocity = finalVelocityBall2;

			}
			if (finalVelocity == 0)
			{


			}


			double velocityXBall1 = finalVelocity * cos(angleOfVelocity1);
			double velocityYBall1 = finalVelocity * sin(angleOfVelocity1);
			double velocityXBall2 = finalVelocity * cos(angleOfVelocity2);
			double velocityYBall2 = finalVelocity * sin(angleOfVelocity2);

			if ((velocityXBall1 == 0 && velocityYBall1 == 0) ||
				(velocityXBall2 == 0 && velocityYBall2 == 0))
			{

				auto id1 = this->GetBall1()->GetId();
				auto id2 = this->GetBall2()->GetId();
				auto x = angleOfVelocity1;
				auto y = angleOfVelocity2;

			}

			this->mBall1->SetVelocityX(velocityXBall1);
			this->mBall1->SetVelocityY(velocityYBall1);
			this->mBall2->SetVelocityX(velocityXBall2);
			this->mBall2->SetVelocityY(velocityYBall2);

			this->SetCollided(true);

		}
	}
	*/

	}
}



/**
* Get the distance between the 2 balls
* \return The distance between the 2 balls
*/
double CBallCollision::GetDistance()
{

	if (mBall1 != nullptr && mBall2 != nullptr)
	{

		double centerXBall1 = mBall1->GetX() + mBall1->GetDiameter() / 2;
		double centerYBall1 = mBall1->GetY() + mBall1->GetDiameter() / 2;
		double centerXBall2 = mBall2->GetX() + mBall2->GetDiameter() / 2;
		double centerYBall2 = mBall2->GetY() + mBall2->GetDiameter() / 2;
		double distance = sqrt((pow((centerXBall2 - centerXBall1), 2) +
			pow((centerYBall2 - centerYBall1), 2)));
		return distance;
	}

}

#include "ShotAssistant.h"
#include "Game.h"

using namespace std;


/**
* Constructor
*/
CShotAssistant::CShotAssistant(std::shared_ptr<CGame> game) : mGame(game)
{
	//mGame->SetAssistant(make_shared<CShotAssistant>(this));
}

/**
* Destructor
*/
CShotAssistant::~CShotAssistant()
{
}

/**
* Calculate the distance between the center of the ball and the trajectory of
* the cue ball
* \return: The distance between the center of the ball and the trajectory of
* the cue ball
*/
float CShotAssistant::GetDistanceToCueBallTrajectory(shared_ptr<CBall> ball)
{
	shared_ptr<CBall> cueBall = mGame->GetBalls()[0];
	pair<double, double> cueCenter(cueBall->GetX() + cueBall->GetDiameter() / 2, cueBall->GetY() + cueBall->GetDiameter() / 2);
	double m = (mBackCenter.second - cueCenter.second) / (mBackCenter.first - cueCenter.first);
	double yInt = (cueCenter.second - m * cueCenter.first);
	double a = -m;
	double b = 1;
	double c = -yInt;

	pair<double, double> ballCenter(ball->GetX() + ball->GetDiameter() / 2, ball->GetY() + ball->GetDiameter() / 2);
	return abs(a * ballCenter.first + b * ballCenter.second + c) / sqrt(a * a + b * b);
}


/**
* Find the first ball the cue ball will strike if the shot is taken
* \input ballsinTraj: A vector of the balls that are int he cue ball's current
* trajectory
* \return: A pointer to the first ball the cue ball will strike if the shot is
taken. If a wall will be struck before a ball, nullptr is returned.
*/
shared_ptr<CBall> CShotAssistant::GetClosestBallToTrajectory(vector<shared_ptr<CBall>> ballsInTrajec)
{
	vector<shared_ptr<CBall>> balls = mGame->GetBalls();
	shared_ptr<CBall> cueBall = balls[0];
	shared_ptr<CBall> closestBall = nullptr;
	double closestDist = 1000;
	for (shared_ptr<CBall> ball : ballsInTrajec)
	{
		double dist = GetDistanceToCueBallTrajectory(ball);
		if (dist < closestDist)
		{
			closestBall = ball;
		}
	}

	return closestBall;
}

void CShotAssistant::Update() {
	mBackCenter.first = (mGame->GetCue()->GetHandlePoints()[1].x + mGame->GetCue()->GetHandlePoints()[4].x) / 2;
	mBackCenter.second = (mGame->GetCue()->GetHandlePoints()[1].y + mGame->GetCue()->GetHandlePoints()[4].y) / 2;
}

/**
* Draw the trajectories of the cue ball and the target and the cursor
*/
void CShotAssistant::Show(ID2D1HwndRenderTarget* graphics) {
	//Pen pen(Color(255, 225, 221, 0));
	Update();
	shared_ptr<CBall> cueBall = mGame->GetBalls()[0];




	// Get line from center of tip through cue center onward
	pair<double, double> cueCenter = cueBall->GetCenter();
	double m = (mBackCenter.second - (cueBall->GetY() + cueBall->GetDiameter() / 2)) / (mBackCenter.first - (cueBall->GetX() + cueBall->GetDiameter() / 2));
	double b = (cueBall->GetY() + cueBall->GetDiameter() / 2) - m * (cueBall->GetX() + cueBall->GetDiameter() / 2);
	double x = 2000;
	if (cueCenter.first < mBackCenter.first)
	{
		x *= -1;
	}
	//graphics->DrawEllipse(&pen, Rect(mBackCenter.first - 5, mBackCenter.second - 5, 10, 10));
	graphics->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(mBackCenter.first, mBackCenter.second), 10, 10), mGame->GetBallBrushes()[1]);
	//graphics->DrawLine(&pen, mTipCenter.first, mTipCenter.second, x, m * x + b);

	vector<shared_ptr<CBall>> bIT = GetBallsInTrajectory();
	shared_ptr<CBall> ball = GetClosestBallToTrajectory(bIT);
	if (ball != nullptr)
	{
		double ghostRad = cueBall->GetDiameter() + abs(cueBall->GetDiameter() - ball->GetDiameter());
		pair<double, double> ballCenter(ball->GetX() + ball->GetDiameter() / 2, ball->GetY() + ball->GetDiameter() / 2);
		//graphics->DrawEllipse(&pen, float(ballCenter.first - ghostRad), ballCenter.second - ghostRad, ghostRad * 2, ghostRad * 2);

		double A = m * m + 1;
		double B = 2 * (m * b - m * ballCenter.second - ballCenter.first);
		double C = (ballCenter.second * ballCenter.second - ghostRad * ghostRad + ballCenter.first * ballCenter.first -
			2 * b * ballCenter.second + b * b);
		double x1 = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
		double x2 = (-B - sqrt(B * B - 4 * A * C)) / (2 * A);
		vector<double> x1x2 = { x1 - cueCenter.first, cueCenter.first };
		double closeX = 0;
		if (abs(x1 - cueCenter.first) < abs(x2 - cueCenter.first))
		{
			closeX = x1;
		}
		else
		{
			closeX = x2;
		}
		double closeY = m * closeX + b;

		double d = sqrt(pow(cueCenter.first - closeX, 2) + pow(cueCenter.second - closeY, 2));

		pair<double, double> markerBox(closeX - cueBall->GetDiameter() / 2, closeY - cueBall->GetDiameter() / 2);
		///Pen pen2(Color(255, 255, 255, 255));
		//graphics->DrawRectangle(&pen2, float(markerBox.first), markerBox.second, cueBall->GetDiameter() / 2, cueBall->GetDiameter() / 2);
		double dx = markerBox.first + cueBall->GetDiameter() / 2 - ballCenter.first;
		double dy = markerBox.second + cueBall->GetDiameter() / 2 - ballCenter.second;
		double dist = sqrt(dx * dx + dy * dy);
		pair<double, double> unit(dx / dist, dy / dist);
		D2D1_POINT_2F markerCenter = D2D1::Point2F(ballCenter.first + unit.first * (ball->GetDiameter() / 2 + cueBall->GetDiameter() / 2),
			ballCenter.second + unit.second * (ball->GetDiameter() / 2 + cueBall->GetDiameter() / 2));

		graphics->DrawEllipse(D2D1::Ellipse(markerCenter, cueBall->GetDiameter() / 2, cueBall->GetDiameter() / 2), mGame->GetBallBrushes()[1]);
		// Get unit vector for a line running through the centers

		D2D1_POINT_2F cueCent = D2D1::Point2F(cueCenter.first, cueCenter.second);
		D2D1_POINT_2F p2 = D2D1::Point2F(float(ballCenter.first - 40 * unit.first), ballCenter.second - 40 * unit.second);
		///graphics->DrawLine(cueCent, p2, mGame->GetBallBrushes()[1]);
		D2D1_POINT_2F target1 = D2D1::Point2F(ballCenter.first, ballCenter.second);
		D2D1_POINT_2F target2 = D2D1::Point2F(ballCenter.first - 40 * unit.first, ballCenter.second - 40 * unit.second);
		graphics->DrawLine(target1, target2, mGame->GetBallBrushes()[1]);
		//graphics->DrawEllipse(&pen, ballCenter.first + unit.first * (ball->GetDiameter() / 2 + cueBall->GetDiameter() / 2), 
			//ballCenter.second + unit.second * (ball->GetDiameter() / 2 + cueBall->GetDiameter() / 2), 5, 5);
		
			
		graphics->DrawLine(cueCent, markerCenter, mGame->GetBallBrushes()[1]);
	}

}


/**
* For each ball on the table, determine if it is in the trajectory of the
* cue ball in the shot were to be taken right now
* \return: A vector of balls in the cue ball's trajectory
*/
std::vector<shared_ptr<CBall>> CShotAssistant::GetBallsInTrajectory()
{
	Update();
	shared_ptr<CBall> cueBall = mGame->GetBalls()[0];
	pair<double, double> cueCenter(cueBall->GetX() + cueBall->GetDiameter() / 2, cueBall->GetY() + cueBall->GetDiameter() / 2);
	vector<shared_ptr<CBall>> ballsInTrajectory;
	for (shared_ptr<CBall> ball : mGame->GetBalls())
	{
		if (ball->GetId() == L"0")
		{
			continue;
		}
		pair<double, double> ballCenter(ball->GetX() + ball->GetDiameter() / 2, ball->GetY() + ball->GetDiameter() / 2);
		if (cueCenter.first >= mBackCenter.first && ballCenter.first >= cueCenter.first)
		{
			// Cue ball is to the right of the cue
			if (GetDistanceToCueBallTrajectory(ball) <= ball->GetDiameter() / 2 + cueBall->GetDiameter() / 2)
			{
				ballsInTrajectory.push_back(ball);
			}
		}
		else if (cueCenter.first <= mBackCenter.first && ballCenter.first <= cueCenter.first)
		{
			// Cue ball is to the left of the cue
			if (GetDistanceToCueBallTrajectory(ball) <= ball->GetDiameter() / 2 + cueBall->GetDiameter() / 2)
			{
				ballsInTrajectory.push_back(ball);
			}
		}

		
	}
	return ballsInTrajectory;
}

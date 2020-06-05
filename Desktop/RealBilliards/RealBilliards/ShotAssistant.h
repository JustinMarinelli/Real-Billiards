/*
* file: ShotAssistant.h
* author: Justin Marinelli
*
* The shot assistance allows a player to see the trajectory of the cue ball
* and the first ball or wall it strikes if a shot was taken.
*/

#include <memory>
#include "Ball.h"
#include <vector>

#pragma once

class CGame;


class CShotAssistant
{
public:

	CShotAssistant(std::shared_ptr<CGame> game);

	~CShotAssistant();

	float GetDistanceToCueBallTrajectory(std::shared_ptr<CBall> ball);

	std::shared_ptr<CBall> GetClosestBallToTrajectory(std::vector<std::shared_ptr<CBall>> ballsInTrajec);

	void Update();

	void SetBackCenter(std::pair<long, long> backCenter) { mBackCenter = backCenter; }

	void Show(ID2D1HwndRenderTarget* graphics);

	void SetPoint(D2D1_POINT_2F point) { this->mMousePoint = point; }

	std::vector<std::shared_ptr<CBall>> GetBallsInTrajectory();

private:
	
	// A pointer to the current game
	std::shared_ptr<CGame> mGame = nullptr;

	// The size of the radius of the cursoe
	int mRadius = 10;

	// Center of the cursor
	std::pair<long, long> mCursorCenter = std::make_pair<long, long>(0, 0);

	// Center of the back handle of the cue
	std::pair<long, long> mBackCenter = std::make_pair<long, long>(0, 0);

	// Mouse pointer
	D2D1_POINT_2F mMousePoint;

};


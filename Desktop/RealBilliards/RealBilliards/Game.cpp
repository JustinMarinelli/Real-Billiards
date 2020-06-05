/**
* file: Game.cpp
* author: Justin Marinelli
*/


#include <vector>
#include <memory>
#include <math.h>
#include "Game.h"
#include "Ball.h"
#include "Cue.h"
#include "PowerBar.h"
#include <conio.h>
#include <cstdio>
#include <ctime>
#include <string>
#define PI 3.14159265



using namespace std;


// Y = 379 = CENTER OF TABLE

/**
* Constructor
*/
CGame::CGame()
{
	this->mTable = make_shared<CTable>(this);
	this->mPowerBar = make_shared<CPowerBar>(this);

	shared_ptr<CPlayer> player1 = make_shared<CPlayer>();
	player1->SetName(L"Justin");
	shared_ptr<CPlayer> player2 = make_shared<CPlayer>();
	player2->SetName(L"Joe Shmoe");
	this->mPlayers.push_back(player1);
	this->mPlayers.push_back(player2);
	
}

/**
* Destructor
*/
CGame::~CGame()
{
}

/**
* Draw the game
* \param graphics The GDI+ graphics context to draw on
*/
void CGame::OnDraw(ID2D1HwndRenderTarget* graphics)
{
	int x = m_pRenderTarget->GetSize().width;
	int y = m_pRenderTarget->GetSize().height;
	graphics->FillRectangle(D2D1::RectF(0.0f, 0.0f, m_pRenderTarget->GetSize().width, m_pRenderTarget->GetSize().height), mBackgroundBrush);
	mTable->Draw(graphics);

	if (!mBallsDrawn)
	{
		DrawBalls();
		this->CreateCollisions();
		mBallsDrawn = true;
		for (shared_ptr<CBall> ball : this->mBalls)
		{
			ball->SetColor();
		}
		this->mCue = make_shared<CCue>(this);
		GetPowerBar()->SetLocation();
		this->mScoreboard = make_shared<CScoreboard>(this);
	}
	for (shared_ptr<CBall> ball : this->mBalls)
	{
		ball->Draw(graphics);
	}
	
	this->mPowerBar->Draw(graphics);
	mScoreboard->Draw(graphics);
	this->mCue->Draw(graphics);
}

/**
* Start a new game
*/
void CGame::DrawBalls()
{

	pair<double, double> rackPoint = mTable->GetRackPoint();
	pair<double, double> scratchPoint = mTable->GetScratchPoint();
	for (int i = 0; i < 16; i++)
	{
		//CreateBall(i, i * 50, i * 50);
	}
	/**
	* Location of every numbered ball is based on the position of the 1-ball.
	*/
	shared_ptr<CBall> cueBall = make_shared<CBall>(this);
	cueBall->SetId(L"0");
	// X: 379.0
	// Y: 379.0 - (25 / 2)
	cueBall->SetX(scratchPoint.first);
	double d = cueBall->GetDiameter();
	cueBall->SetY(scratchPoint.second - 0.5 * cueBall->GetDiameter());
	cueBall->SetVelocityX(0.0);
	cueBall->SetVelocityY(0.0);
	this->mBalls.push_back(cueBall);


	shared_ptr<CBall> ball1 = make_shared<CBall>(this);
	ball1->SetId(L"1");
	// X: 1028.0 - 12.50
	// Y: 378.0 - 12.50
	ball1->SetX(rackPoint.first);
	ball1->SetY(rackPoint.second - 1 * cueBall->GetDiameter() / 2);
	this->mBalls.push_back(ball1);

	shared_ptr<CBall> ball2 = make_shared<CBall>(this);
	ball2->SetId(L"2");
	ball2->SetX(ball1->GetX() + 4 * ball1->GetDiameter());
	ball2->SetY(ball1->GetY() + 2 * cueBall->GetDiameter() / 2);
	this->mBalls.push_back(ball2);


	shared_ptr<CBall> ball3 = make_shared<CBall>(this);
	ball3->SetId(L"3");
	ball3->SetX(ball1->GetX() + 3 * ball1->GetDiameter());
	ball3->SetY(ball1->GetY() - ball1->GetDiameter() / 2);
	this->mBalls.push_back(ball3);

	shared_ptr<CBall> ball4 = make_shared<CBall>(this);
	ball4->SetId(L"4");
	ball4->SetX(ball1->GetX() + 4 * ball1->GetDiameter());
	ball4->SetY(ball1->GetY() - ball1->GetDiameter());
	this->mBalls.push_back(ball4);

	shared_ptr<CBall> ball5 = make_shared<CBall>(this);
	ball5->SetId(L"5");
	ball5->SetX(ball1->GetX() + 3 * ball1->GetDiameter());
	ball5->SetY(ball1->GetY() + 3 * ball1->GetDiameter() / 2);
	this->mBalls.push_back(ball5);

	shared_ptr<CBall> ball6 = make_shared<CBall>(this);
	ball6->SetId(L"6");
	ball6->SetX(ball1->GetX() + ball1->GetDiameter());
	ball6->SetY(ball1->GetY() + ball1->GetDiameter() / 2);
	this->mBalls.push_back(ball6);

	shared_ptr<CBall> ball7 = make_shared<CBall>(this);
	ball7->SetId(L"7");
	ball7->SetX(ball1->GetX() + 2 * ball1->GetDiameter());
	ball7->SetY(ball1->GetY() - ball1->GetDiameter());
	this->mBalls.push_back(ball7);

	shared_ptr<CBall> ball8 = make_shared<CBall>(this);
	ball8->SetId(L"8");
	ball8->SetX(ball1->GetX() + 2 * ball1->GetDiameter());
	ball8->SetY(ball1->GetY());
	this->mBalls.push_back(ball8);

	shared_ptr<CBall> ball9 = make_shared<CBall>(this);
	ball9->SetId(L"9");
	ball9->SetX(ball1->GetX() + 3 * ball1->GetDiameter());
	ball9->SetY(ball1->GetY() - 3 * ball1->GetDiameter() / 2);
	this->mBalls.push_back(ball9);

	shared_ptr<CBall> ball10 = make_shared<CBall>(this);
	ball10->SetId(L"10");
	ball10->SetX(ball1->GetX() + ball1->GetDiameter());
	ball10->SetY(ball1->GetY() - ball1->GetDiameter() / 2);
	this->mBalls.push_back(ball10);

	shared_ptr<CBall> ball11 = make_shared<CBall>(this);
	ball11->SetId(L"11");
	ball11->SetX(ball1->GetX() + 4 * ball1->GetDiameter());
	ball11->SetY(ball1->GetY() + 4 * cueBall->GetDiameter() / 2);
	this->mBalls.push_back(ball11);

	shared_ptr<CBall> ball12 = make_shared<CBall>(this);
	ball12->SetId(L"12");
	ball12->SetX(ball1->GetX() + 3 * ball1->GetDiameter());
	ball12->SetY(ball1->GetY() + ball1->GetDiameter() / 2);
	this->mBalls.push_back(ball12);

	shared_ptr<CBall> ball13 = make_shared<CBall>(this);
	ball13->SetId(L"13");
	ball13->SetX(ball1->GetX() + 4 * ball1->GetDiameter());
	ball13->SetY(ball1->GetY() - 2 * ball1->GetDiameter());
	this->mBalls.push_back(ball13);

	shared_ptr<CBall> ball14 = make_shared<CBall>(this);
	ball14->SetId(L"14");
	ball14->SetX(ball1->GetX() + 2 * ball1->GetDiameter());
	ball14->SetY(ball1->GetY() + ball1->GetDiameter());
	this->mBalls.push_back(ball14);

	shared_ptr<CBall> ball15 = make_shared<CBall>(this);
	ball15->SetId(L"15");
	ball15->SetX(ball1->GetX() + 4 * ball1->GetDiameter());
	ball15->SetY(ball1->GetY());
	this->mBalls.push_back(ball15);


}

/**
* Create all possible collisions
*/
void CGame::CreateCollisions()
{

	for (int slowIndex = 0; slowIndex < this->mBalls.size(); slowIndex++)
	{

		for (int fastIndex = slowIndex + 1; fastIndex < this->mBalls.size(); fastIndex++)
		{

			if (slowIndex == fastIndex)
			{

				continue;

			}

			shared_ptr<CBall>& ball1 = this->mBalls[slowIndex];
			shared_ptr<CBall>& ball2 = this->mBalls[fastIndex];
			this->mBallCollisions.push_back(make_shared<CBallCollision>(ball1, ball2));

		}

	}

	for (shared_ptr<CBall>& ball : this->mBalls)
	{

		this->mLeftWallCollisions.push_back(make_shared<CLeftWallCollision>(ball));

	}

	for (shared_ptr<CBall>& ball : this->mBalls)
	{

		this->mRightWallCollisions.push_back(make_shared<CRightWallCollision>(ball));

	}

	for (shared_ptr<CBall>& ball : this->mBalls)
	{

		this->mTopWallCollisions.push_back(make_shared<CTopWallCollision>(ball));

	}

	for (shared_ptr<CBall>& ball : this->mBalls)
	{

		this->mBottomWallCollisions.push_back(make_shared<CBottomWallCollision>(ball));

	}


}

/** Test an x,y click location to see if it clicked
* on some item in the game.
* \param x X location
* \param y Y location
* \returns Pointer to item we clicked on or nullptr if none.
*/
shared_ptr<CGameItem> CGame::HitTest(int x, int y)
{
	for (shared_ptr<CBall> ball : this->mBalls)
	{
		if (ball->HitTest(x, y))
		{
			return ball;
		}
	}

	if (this->mCue->HitTest(x, y))
	{
		return this->mCue;
	}

	if (GetPowerBar()->HitTest(x, y))
	{
		GetPowerBar()->SetPower(x);
		GetPowerBar()->SetAdjusting(true);
	}

	return  nullptr;
}

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CGame::Update(double elapsed)
{

	// Top left pocket
	// 265 90

	if (mCue->GetStage() != 0)
	{
		this->mCue->Update(elapsed);
	}
	
	for (auto& ball : this->mBalls)
	{
		ball->Update(elapsed);
	}

	vector<D2D1_POINT_2F> tlPocketPoints = mTable->GetTLPocketPoints();
	vector<D2D1_POINT_2F> trPocketPoints = mTable->GetTRPocketPoints();
	vector<D2D1_POINT_2F> blPocketPoints = mTable->GetBLPocketPoints();
	vector<D2D1_POINT_2F> brPocketPoints = mTable->GetBRPocketPoints();
	vector<D2D1_POINT_2F> tmPocketPoints = mTable->GetTMPocketPoints();
	vector<D2D1_POINT_2F> bmPocketPoints = mTable->GetBMPocketPoints();

	for (shared_ptr<CBall>& ball : this->mBalls)
	{
		double cornerDistThresh = tlPocketPoints[1].x - tlPocketPoints[0].x;

		if (ball != nullptr)
		{
			// Distance between ball and all of the pockets
			double dUpperLeft = sqrt(pow(ball->GetCenter().first - tlPocketPoints[0].x, 2) + pow(ball->GetCenter().second - tlPocketPoints[0].y, 2));
			double dUpperRight = sqrt(pow(ball->GetCenter().first - trPocketPoints[1].x, 2) + pow(ball->GetCenter().second - trPocketPoints[1].y, 2));
			double dUpperMiddle = sqrt(pow(ball->GetCenter().first - tmPocketPoints[4].x, 2) + pow(ball->GetCenter().second - tmPocketPoints[4].y, 2));
			double dBottomLeft = sqrt(pow(ball->GetCenter().first - blPocketPoints[3].x, 2) + pow(ball->GetCenter().second - blPocketPoints[3].y, 2));
			double dBottomRight = sqrt(pow(ball->GetCenter().first - brPocketPoints[3].x, 2) + pow(ball->GetCenter().second - brPocketPoints[3].y, 2));
			double dBottomMiddle = sqrt(pow(ball->GetCenter().first - bmPocketPoints[4].x, 2) + pow(ball->GetCenter().second - bmPocketPoints[4].y, 2));

			if (dUpperLeft < cornerDistThresh || dUpperRight < cornerDistThresh ||
				dBottomLeft < cornerDistThresh || dBottomRight < cornerDistThresh)
			{
				ball->SetVelocityX(0.0);
				ball->SetVelocityY(0.0);
				this->mPottedThisTurn.push_back(stoi(ball->GetId()));
				// Check if sides have been chosen yet
				if (this->mPlayers[0]->GetBallType() == -1)
				{
					if (mPottedThisTurn[0] < 9)
					{
						this->mPlayers[this->mTurn % 2]->SetBallType(0);
						this->mPlayers[abs(this->mTurn % 2 - 1.0)]->SetBallType(1);
					}
					else
					{
						this->mPlayers[this->mTurn % 2]->SetBallType(1);
						this->mPlayers[abs(this->mTurn % 2 - 1.0)]->SetBallType(0);
					}
				}



				if (ball->GetId() != L"0")
				{
					if (stoi(ball->GetId()) < 9)
					{
						this->mSunkenSolidBalls.push_back(ball);
					}
					else
					{
						this->mSunkenStripedBalls.push_back(ball);
					}
					this->mBalls.erase(find(this->mBalls.begin(), this->mBalls.end(), ball));
				}
				else
				{
					ball->SetX(mTable->GetScratchPoint().first);
					ball->SetY(mTable->GetScratchPoint().second);
				}

			}
		}

	}



	for (shared_ptr<CBallCollision>& collision : this->mBallCollisions)
	{
		collision->Collide();

	}

	for (shared_ptr<CLeftWallCollision>& collision : this->mLeftWallCollisions)
	{
		collision->Collide();
	}

	for (shared_ptr<CRightWallCollision>& collision : this->mRightWallCollisions)
	{
		collision->Collide();
	}

	for (shared_ptr<CTopWallCollision>& collision : this->mTopWallCollisions)
	{
		collision->Collide();
	}

	for (shared_ptr<CBottomWallCollision>& collision : this->mBottomWallCollisions)
	{
		collision->Collide();
	}


	for (auto& ball : this->mBalls)
	{
		ball->Update(elapsed);
	}



	if (this->mWinner == nullptr)
	{
		this->CheckWinner();
	}
	if (this->TurnOver())
	{
		vector<shared_ptr<CCollision>> collisions;
		for (int i = 0; i < mBottomWallCollisions.size(); i++)
		{
			if (mBottomWallCollisions[i]->GetCollided())
			{
				collisions.push_back(mBottomWallCollisions[i]);
			}
			if (mTopWallCollisions[i]->GetCollided())
			{
				collisions.push_back(mTopWallCollisions[i]);
			}
			if (mLeftWallCollisions[i]->GetCollided())
			{
				collisions.push_back(mLeftWallCollisions[i]);
			}
			if (mRightWallCollisions[i]->GetCollided())
			{
				collisions.push_back(mRightWallCollisions[i]);
			}

		}
		this->mShotTaken = false;
		this->mTurn++;


	}
}

/**
* Checks if a ball is on the table or not
* \param ballNumber1 The number of the ball we're checking for
* return true if the ball is on the table, false otherwise
*/
bool CGame::IsBallOnTable(int ballNumber1)
{
	for (shared_ptr<CBall> ball : this->mBalls)
	{
		if (ballNumber1 == stoi(ball->GetId()))
		{
			return true;
		}
	}
	return false;
}

/**
* Determine if there are any balls that are currently moving
* \return true if there is at least 1 ball in motion, false otherwise
*/
bool CGame::AreBallsInMotion()
{
	for (shared_ptr<CBall> ball : this->mBalls)
	{
		if (ball->GetVelocity() != 0.0)
		{
			return true;
		}
	}
	return false;
}

/**
* Check if a player has won the game. If a player has won, the mWinner member
* variable is assigned to the player that has won.
*/
void CGame::CheckWinner()
{
	shared_ptr<CPlayer> shootingPlayer = this->mPlayers[this->mTurn % 2];
	if (count(this->mPottedThisTurn.begin(), this->mPottedThisTurn.end(), 8))
	{
		// Check if the 8 ball was potted. If the player pots the 8 
		// ball before they sink all their other balls, the game is 
		// over.
		if (shootingPlayer->GetPotted() < 7)
		{
			shared_ptr<CPlayer> sittingPlayer = this->mPlayers[abs(this->mTurn % 2 - 1)];
			shared_ptr<CPlayer> shootingPlayer = this->mPlayers[this->mTurn % 2];
			this->mWinner = sittingPlayer;
		}
		else
		{
			shared_ptr<CPlayer> sittingPlayer = this->mPlayers[abs(this->mTurn % 2 - 1)];
			shared_ptr<CPlayer> shootingPlayer = this->mPlayers[this->mTurn % 2];
			this->mWinner = shootingPlayer;
		}
	}
}

void CGame::SetWndDimensions(pair<long, long> window)
{
	this->mWindowDimensions = window;
	mTable->SetCenter(make_pair<long, long>(window.first / 2, window.second / 2));
}

/**
* Add an item into the collection of items
* \param item The item we are adding
*/
void CGame::AddBall(std::shared_ptr<CBall> item)
{
	this->mBalls.push_back(item);
}

/**
* Create a new ball to be added to the game
* \param id: The number of the ball
* \param x: The x coordinate the ball will be drawn at
* \param y: The y coordinate the ball will be drawn at
*/
void CGame::CreateBall(int id, double x, double y)
{
	shared_ptr<CBall> cueBall = make_shared<CBall>(this);

	wchar_t itemId[256];
	swprintf_s(itemId, L"%d", id);
	wprintf(L"%s\n", itemId);
	cueBall->SetId(itemId);
	// X: 379.0
	// Y: 379.0 - (25 / 2)
	cueBall->SetX(379.0);
	cueBall->SetY(378.0 - (25 / 2) + 10);
	cueBall->SetVelocityX(0.0);
	cueBall->SetVelocityY(0.0);
}

/**
* Determines if someone's turn is over
* \return true if a player's shot is over, false otherwise
*/
bool CGame::TurnOver()
{
	if (this->mShotTaken && !this->AreBallsInMotion())
	{
		if (this->mPottedThisTurn.size())
		{
			if (count(this->mPottedThisTurn.begin(), this->mPottedThisTurn.end(), 0))
			{
				// Cue ball sunk (scratch)
				this->mBallInHand = true;
				return true;
			}

			// If a player potted a ball, check if they sunk one of their balls
			// before an opponent's ball.
			shared_ptr<CPlayer> shootingPlayer = this->mPlayers[this->mTurn % 2];

			int firstBallPotted = this->mPottedThisTurn[0];
			shootingPlayer->IncrementPotted(this->mPottedThisTurn.size());
			this->mPottedThisTurn.clear();
			if (!shootingPlayer->GetBallType() && firstBallPotted > 8)
			{
				// Player is shooting at solids but potted a striped ball first
				return true;
			}
			else if (shootingPlayer->GetBallType() > 0 && firstBallPotted < 8)
			{
				// Player is shooting at stripes but potted a solid ball first
				return true;
			}
			else
			{
				// A correct ball was potted first and the player keeps their turn
				this->mShotTaken = false;
				return false;

			}
		}
		return true;
	}
	return false;
}
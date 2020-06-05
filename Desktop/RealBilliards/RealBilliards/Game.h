/*
* file: Game.h
* author: Justin Marinelli
*
* This class represents a game
*/

#include <memory>
#include <vector>
#include <d2d1.h>
#include <wincodec.h>
#include "Table.h"
#include "Player.h"
#include "Collision.h"
#include "WallCollision.h"
#include "LeftWallCollision.h"
#include "RightWallCollision.h"
#include "TopWallCollision.h"
#include "BottomWallCollision.h"
#include "BallCollision.h"
#include "Cue.h"
#include "ShotAssistant.h"
#include "PowerBar.h"
#include "Scoreboard.h"

#pragma once

class CGameItem;
class CBall;

class CGame
{
	
public:

	CGame();

	virtual ~CGame();

	void OnDraw(ID2D1HwndRenderTarget* graphics);

	std::shared_ptr<CTable> GetTable() { return this->mTable; }

	ID2D1Factory* GetFactory() { return m_pDirect2dFactory; }

	ID2D1HwndRenderTarget* GetRenderTarget() { return m_pRenderTarget; }

	void SetRenderTarget(ID2D1HwndRenderTarget* renderTarget) { m_pRenderTarget = renderTarget; }

	void SetFactory(ID2D1Factory* factory) { m_pDirect2dFactory = factory; }

	void SetBallBrushes(std::vector<ID2D1SolidColorBrush*> brushes) { mBallBrushes = brushes; }

	void SetBallTextFormat(IDWriteTextFormat* format) { mBallTextFormat = format; }

	IDWriteTextFormat* GetTextFormat() { return mBallTextFormat; }

	void SetSunkenBallTextFormat(IDWriteTextFormat* format) { mSunkenBallTextFormat = format; }

	IDWriteTextFormat* GetSunkenTextFormat() { return mSunkenBallTextFormat; }

	std::vector<ID2D1SolidColorBrush*> GetBallBrushes() { return mBallBrushes; }

	void CreateCollisions();

	void DrawBalls();

	std::vector<std::shared_ptr<CBall>> GetBalls() { return this->mBalls; }

	bool GetUsingAssist() { return mIsUsingAssist; }

	void SetAssistant(std::shared_ptr<CShotAssistant> assistant) { this->mAssistant = assistant; }

	std::shared_ptr<CCue> GetCue() { return this->mCue; }

	std::shared_ptr<CShotAssistant> GetAssistant() { return this->mAssistant; }

	void SetShotTaken(bool taken) { this->mShotTaken = taken; }

	bool IsBallInHand() { return this->mBallInHand; }

	bool GetDevMode() { return this->mDevMode; }

	void SetHandleBrush(ID2D1SolidColorBrush* brush) { mHandleBrush = brush; }

	void SetShaftBrush(ID2D1SolidColorBrush* brush) { mShaftBrush = brush; }

	ID2D1SolidColorBrush* GetHandleBrush() { return mHandleBrush; }

	ID2D1SolidColorBrush* GetShaftBrush() { return mShaftBrush; }

	std::shared_ptr<CGameItem> HitTest(int x, int y);

	void Update(double elapsed);

	std::shared_ptr<CPowerBar> GetPowerBar() { return this->mPowerBar; }

	void AddBall(std::shared_ptr<CBall> ball);

	void CreateBall(int id, double x, double y);

	bool TurnOver();

	bool IsBallOnTable(int ballNumber);

	bool AreBallsInMotion();

	void CheckWinner();

	std::vector<std::shared_ptr<CBall>> GetSunken() { return this->mSunkenSolidBalls; }

	std::vector<std::shared_ptr<CBall>> GetStriped() { return this->mSunkenStripedBalls; }

	void SetBallInHand(bool isBallInHand) { this->mBallInHand = isBallInHand; }

	void SetWndDimensions(std::pair<long, long> window);

	std::pair<long, long> GetWndDimensions() { return this->mWindowDimensions; }

	void SetScaleFactor(double scaleFactor) { this->mScaleFactor = scaleFactor; }

	void SetBackgroundBrush(ID2D1BitmapBrush* brush) { mBackgroundBrush = brush; }
	void SetLeftTextFormat(IDWriteTextFormat* format) { mTextLeft = format; }
	void SetRightTextFormat(IDWriteTextFormat* format) { mTextRight = format; }
	IDWriteTextFormat* GetLeftTextFormat() { return mTextLeft; }
	IDWriteTextFormat* GetRightTextFormat() { return mTextRight; }

	int GetTurn() { return mTurn; }

	std::vector<std::shared_ptr<CPlayer>> GetPlayers() { return mPlayers; }
	std::shared_ptr<CScoreboard> GetScoreboard() { return mScoreboard; }

	std::vector<std::shared_ptr<CBall>> GetSunkenStripes() { return mSunkenStripedBalls; }
	std::vector<std::shared_ptr<CBall>> GetSunkenSolids() { return mSunkenSolidBalls; }
	void SetWinnerTextFormat(IDWriteTextFormat* format) { mWinnerTextFormat = format; }
	IDWriteTextFormat* GetWinnerTextFormat() { return mWinnerTextFormat; }
	std::shared_ptr<CPlayer> GetWinner() { return mWinner; }

private:

	// The Direct2D factory
	ID2D1Factory* m_pDirect2dFactory;

	// The target we're rendering to
	ID2D1HwndRenderTarget* m_pRenderTarget;

	// The format for the text on the balls
	IDWriteTextFormat* mBallTextFormat;

	// The format for the text on the sunken balls
	IDWriteTextFormat* mSunkenBallTextFormat;

	// The format for the left player
	IDWriteTextFormat* mTextLeft;

	// The format for the right player
	IDWriteTextFormat* mTextRight;

	// The format for winner text
	IDWriteTextFormat* mWinnerTextFormat;

	// Background image to use
	std::unique_ptr<ID2D1Bitmap> mBackground;

	// The brush that paints the shaft of the cue
	ID2D1SolidColorBrush* mShaftBrush;

	// The brush that paints the handle of the cue
	ID2D1SolidColorBrush* mHandleBrush;

	// The table the game is being player on
	std::shared_ptr<CTable> mTable;

	// Players in the game
	std::vector<std::shared_ptr<CPlayer>> mPlayers;

	// Whose turn it is
	int mTurn = 0;

	// Contains the brushes for the balls
	std::vector<ID2D1SolidColorBrush*> mBallBrushes;

	// Scale factor for drawing
	double mScaleFactor = 1.0;

	// Determines if the ball have been drawn yet
	bool mBallsDrawn = false;

	// The collection of game items
	std::vector<std::shared_ptr<CBall>> mBalls;

	// The collection of ball collisions
	std::vector<std::shared_ptr<CBallCollision>> mBallCollisions;

	// Vector of balls and left wall collisions
	std::vector<std::shared_ptr<CLeftWallCollision>> mLeftWallCollisions;

	// Vector of balls and right wall collisions
	std::vector<std::shared_ptr<CRightWallCollision>> mRightWallCollisions;

	// Vector of balls and top wall collisions
	std::vector<std::shared_ptr<CTopWallCollision>> mTopWallCollisions;

	// Vector of balls and bottom wall collisions
	std::vector<std::shared_ptr<CBottomWallCollision>> mBottomWallCollisions;

	// The pool cue being used
	std::shared_ptr<CCue> mCue = nullptr;

	// Determines if shot assist is enabled
	bool mIsUsingAssist = true;

	// The shot assistant
	std::shared_ptr<CShotAssistant> mAssistant = nullptr;

	// Determines if the player has taken their shot
	bool mShotTaken = false;

	// Determines if the player can move the ball
	bool mBallInHand = false;

	// Determines if we are in developer mode
	bool mDevMode = true;

	// The power bar for shooting the cue ball
	std::shared_ptr<CPowerBar> mPowerBar = nullptr;

	// Upper left corner pocket center
	std::pair<double, double> mCenterUpperLeft = std::make_pair<double, double>(0.0, 0.0);

	// Upper right corner pocket center
	std::pair<double, double> mCenterUpperRight = std::make_pair<double, double>(0.0, 0.0);

	// Upper middle pocket center
	std::pair<double, double> mCenterUpperMiddle = std::make_pair<double, double>(0.0, 0.0);

	// Bottom left corner pocket center
	std::pair<double, double> mCenterBottomLeft = std::make_pair<double, double>(0.0, 0.0);

	// Bottom right corner pocket center
	std::pair<double, double> mCenterBottomRight = std::make_pair<double, double>(0.0, 0.0);

	// Bottom middle pocket center
	std::pair<double, double> mCenterBottomMiddle = std::make_pair<double, double>(0.0, 0.0);

	// Sunken solid balls
	std::vector<std::shared_ptr<CBall>> mSunkenSolidBalls;

	// Sunken striped balls
	std::vector<std::shared_ptr<CBall>> mSunkenStripedBalls;

	// The numbers of the balls potted after a particular turn
	std::vector<int> mPottedThisTurn;

	// Determines if a player has won the game
	bool mIsGameOver = false;

	// The winner of the game (nullptr if the game is not over
	std::shared_ptr<CPlayer> mWinner = nullptr;

	// Center of the viewing window
	std::pair<double, double> mWindowDimensions = std::make_pair<long, long>(0, 0);
	
	// The brush that paints the background
	ID2D1BitmapBrush* mBackgroundBrush;

	// The scoreboard for the game
	std::shared_ptr<CScoreboard> mScoreboard;
};

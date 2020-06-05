/*
* file: Scoreboard.h
* author: Justin Marinelli
*
* This class represents the scoreboard of the game, including the names of 
* the players, the balls that have been sunk, showing who is currently 
* shooting, and if someone has won the game.
*/

#pragma once

#include <vector>
#include <memory>
#include <d2d1.h>
#include <d2d1helper.h>

class CGame;

class CScoreboard
{
public:

	CScoreboard(CGame* game);

	virtual ~CScoreboard();

	// Default constructor (disabled)
	CScoreboard() = delete;

	// Copy constructor (disabled)
	CScoreboard(const CScoreboard&) = delete;

	void Draw(ID2D1HwndRenderTarget* graphics);

	void SetTextboxLocations();

	void ShowText(ID2D1HwndRenderTarget* graphics);

	void DrawSunkenBalls(ID2D1HwndRenderTarget* graphics);

	void ShowWinner(ID2D1HwndRenderTarget* graphics);

private:

	// The game this item is a part of 
	std::shared_ptr<CGame> mGame;

	// The rectangle that surrounds the sunken right balls
	D2D1_RECT_F mRightBallsRect;

	// The rectangle that surrounds the sunken left balls
	D2D1_RECT_F mLeftBallsRect;

	// The rectangle that surrounds the left player's name
	D2D1_RECT_F mLeftNameRect;

	// The rectangle that surrounds the right player's name
	D2D1_RECT_F mRightNameRect;

	// The rectangle that surrounds the shooting text on the left
	D2D1_RECT_F mLeftShootingRect;

	// The rectangle that surrounds the shooting text on the right
	D2D1_RECT_F mRightShootingRect;

	// The rectangle that surrounds the text that shows the winner
	D2D1_RECT_F mWinnerRect;

};


/**
* file: Scoreboard.cpp
* author: Justin Marinelli
*/


#include "Scoreboard.h"
#include "Game.h"

using namespace std;

/**
* Constructor
*/
CScoreboard::CScoreboard(CGame* game) : mGame(game)
{
	SetTextboxLocations();
}

/**
* Destructor
*/
CScoreboard::~CScoreboard()
{

}

/**
* Draw the sunken balls, the players names, who is shooting, and the 
* player who won (if there is one yet)
* \param graphics: The graphics object we're drawing on
*/
void CScoreboard::Draw(ID2D1HwndRenderTarget* graphics)
{
	/**
	Debugging purposes
	graphics->DrawRectangle(mLeftBallsRect, mGame->GetBallBrushes()[0]);
	graphics->DrawRectangle(mRightBallsRect, mGame->GetBallBrushes()[0]);
	graphics->DrawRectangle(mLeftNameRect, mGame->GetBallBrushes()[0]);
	graphics->DrawRectangle(mRightNameRect, mGame->GetBallBrushes()[0]);
	graphics->DrawRectangle(mLeftShootingRect, mGame->GetBallBrushes()[0]);
	graphics->DrawRectangle(mRightShootingRect, mGame->GetBallBrushes()[0]);
	graphics->DrawRectangle(mWinnerRect, mGame->GetBallBrushes()[0]);
	*/ 
	
	ShowText(graphics);
	DrawSunkenBalls(graphics);
	if (mGame->GetWinner() != nullptr)
	{
		ShowWinner(graphics);
	}

}

/**
* Set the locations of each textbox on the screen according to the dimensions
* of the window.
*/
void CScoreboard::SetTextboxLocations()
{
	D2D1_POINT_2F tableTop = mGame->GetTable()->GetTLTable();
	double wndRight = mGame->GetRenderTarget()->GetSize().width;
	double wndBot = mGame->GetRenderTarget()->GetSize().height;
	double sunkenBoxWidth = tableTop.x;
	double nameBoxHeight = tableTop.y / 2;
	double winnerTextPerc = 0.5;
	double winnerBoxWid = winnerTextPerc * mGame->GetRenderTarget()->GetSize().width;
	double winnerBoxHeight = winnerTextPerc * mGame->GetRenderTarget()->GetSize().height;
	double windWid = mGame->GetRenderTarget()->GetSize().width;
	double windHeight = mGame->GetRenderTarget()->GetSize().height;

	mLeftBallsRect = D2D1::RectF(0.0f, 0.0f, sunkenBoxWidth, wndBot);
	mRightBallsRect = D2D1::RectF(wndRight - sunkenBoxWidth, 0.0f, wndRight, wndBot);
	mLeftNameRect = D2D1::RectF(sunkenBoxWidth, 0.0f, wndRight / 2, nameBoxHeight);
	mRightNameRect = D2D1::RectF(wndRight / 2, 0.0f, wndRight - sunkenBoxWidth, nameBoxHeight);
	mLeftShootingRect = D2D1::RectF(sunkenBoxWidth, nameBoxHeight, wndRight / 2, tableTop.y);
	mRightShootingRect = D2D1::RectF(wndRight / 2, nameBoxHeight, wndRight - sunkenBoxWidth, tableTop.y);
	mWinnerRect = D2D1::RectF(windWid / 2 - 0.5 * winnerBoxWid, windHeight / 2 - 0.5 * winnerBoxHeight,
		windWid / 2 + 0.5 * winnerBoxWid, windHeight / 2 + 0.5 * winnerBoxHeight);

}

/**
* Responsible for drawing the text (names and who's shooting)
* on the scoreboard
* \param graphics: The graphics object we're drawing on
*/
void CScoreboard::ShowText(ID2D1HwndRenderTarget* graphics)
{
	size_t sizeL = wcslen(mGame->GetPlayers()[0]->GetName());
	graphics->DrawText(
		mGame->GetPlayers()[0]->GetName(),
		sizeL,
		mGame->GetLeftTextFormat(),
		mLeftNameRect,
		mGame->GetBallBrushes()[1]
	);

	size_t sizeR = wcslen(mGame->GetPlayers()[1]->GetName());
	graphics->DrawText(
		mGame->GetPlayers()[1]->GetName(),
		sizeR,
		mGame->GetRightTextFormat(),
		mRightNameRect,
		mGame->GetBallBrushes()[1]
	);
	D2D1_RECT_F shootingRect;
	IDWriteTextFormat* shootingF;
	mGame->GetTurn() % 2 ? shootingF = mGame->GetRightTextFormat() : shootingF = mGame->GetLeftTextFormat();
	mGame->GetTurn() % 2 ? shootingRect = mRightShootingRect : shootingRect = mLeftShootingRect;
	graphics->DrawText(
		L"Shooting",
		8,
		shootingF,
		shootingRect,
		mGame->GetBallBrushes()[3]
	);
}

/**
* Draw the sunken balls on the screen
* \param graphics: The graphics object we're drawing on
*/
void CScoreboard::DrawSunkenBalls(ID2D1HwndRenderTarget* graphics)
{
	double ballBoxWidth = mLeftBallsRect.right;

	double ballRad = mLeftBallsRect.bottom / 20;
	vector<shared_ptr<CBall>> stripes = mGame->GetSunkenStripes();
	vector<shared_ptr<CBall>> solids = mGame->GetSunkenSolids();
	vector<shared_ptr<CBall>> leftBalls;
	vector<shared_ptr<CBall>> rightBalls;
	int ballType = mGame->GetPlayers()[0]->GetBallType();
	if (ballType != -1)
	{
		if (!mGame->GetPlayers()[0]->GetBallType())
		{
			leftBalls = solids;
			rightBalls = stripes;
		}
		else
		{
			leftBalls = stripes;
			rightBalls = solids;
		}

		int counter = 0;
		for (shared_ptr<CBall>& ball : leftBalls)
		{
			ball->SetRadius(ballRad);
			ball->SetDiameter(ballRad * 2);
			ball->ConfigureStripe();
			ball->SetCenter(ballBoxWidth / 2, 2 * counter * ballRad + ballRad);
			ball->Draw(graphics);
			counter++;
		}
		counter = 0;
		for (shared_ptr<CBall>& ball : rightBalls)
		{
			ball->SetRadius(ballRad);
			ball->SetDiameter(ballRad * 2);
			ball->ConfigureStripe();
			ball->SetCenter(graphics->GetSize().width - ballBoxWidth / 2, 2 * counter * ballRad + ballRad);
			ball->Draw(graphics);
			counter++;
		}
	}
}

/**
* If there is a winner, display the winning message on the screen
* \param graphics: The graphics object we're drawing on
*/
void CScoreboard::ShowWinner(ID2D1HwndRenderTarget* graphics)
{
	wchar_t winnerText[80];
	wcscpy_s(winnerText, mGame->GetWinner()->GetName());
	wcscat_s(winnerText, L" Wins!");
	size_t size = wcslen(winnerText);
	graphics->DrawText(
		winnerText,
		size,
		mGame->GetWinnerTextFormat(),
		mWinnerRect,
		mGame->GetBallBrushes()[1]
	);
}
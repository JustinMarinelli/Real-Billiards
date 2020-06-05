/*
* file: Player.h
* author: Justin Marinelli
*
* This class represents a player
*/


#pragma once


class CPlayer
{

public:

	CPlayer();

	virtual ~CPlayer();

	void SetName(const wchar_t* name) { this->mName = name; }
	const wchar_t* GetName() { return this->mName; }
	void SetBallType(int ballType) { this->mBallType = ballType; }
	int GetBallType() { return this->mBallType; }
	void IncrementPotted(int numPotted) { this->mPotted += numPotted; }
	bool IsOnFinalShot();
	int GetPotted() { return this->mPotted; }

private:

	// The name of the player
	const wchar_t* mName = L"Player Name";

	// The balls the player should keep on the table 
	// (-1 = undecided, 0 = solids, 1 = stripes)
	int mBallType = -1;

	// Number of balls potted
	int mPotted = 0;

};


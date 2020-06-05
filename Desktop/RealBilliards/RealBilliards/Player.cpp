/**
* file: Player.cpp
* author: Justin Marinelli
*/

#include "Player.h"


/**
* Constructor
*/
CPlayer::CPlayer()
{
	
}

/**
* Destructor
*/
CPlayer::~CPlayer()
{

}

/**
* Determines if the player is on their final shot
* \return true if the player is on their last shot, false otherwise.
*/
bool CPlayer::IsOnFinalShot()
{
	return this->mPotted == 7;
}

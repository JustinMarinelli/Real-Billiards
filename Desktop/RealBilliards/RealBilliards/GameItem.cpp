/**
* file: GameItem.cpp
* author: Justin Marinelli
*/

#include "GameItem.h"
#include "Game.h"

using namespace std;


/**
* Contructor
* \param game The game that this item is associated with
* \param id The ID we are assigning to the item
*/
void CGameItem::AddLoc(std::pair<double, double> loc)
{
	mPrevLocations.push_back(loc);
	if (mPrevLocations.size() > 10)
	{
		mPrevLocations.erase(mPrevLocations.begin());
	}
}
CGameItem::CGameItem(CGame* game, const wchar_t* id) : mGame(game)
{

	this->mId = id;

}

/**
* Destructor
*/
CGameItem::~CGameItem()
{
}



/**
* Set the image path for the item based
* \param path The path to the image
*/
void CGameItem::SetImagePath(const wchar_t* path)
{

	this->mImagePath = path;

}

/**
* Interpolate our position
* \param xGoal: The goal x coordinate
* \param yGoal: The goal y coordinate
*/
std::pair<double, double> CGameItem::LinearInterpolate(double xGoal, double yGoal)
{
	double dt = 0.0008;
	double xNew = (xGoal - GetX()) * dt + GetX();
	double yNew = (yGoal - GetY()) * dt + GetY();
	return std::pair<double, double>(xNew, yNew);
}
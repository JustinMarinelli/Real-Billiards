/*
* file: GameItem.h
* author: Justin Marinelli
*
* This is the base class for all game items that can collide with another,
* such as a pool cue and a ball.
*/

#include <memory>
#include <vector>
#include <string>
#include <math.h>
#include <d2d1.h>
#include <d2d1helper.h>
#pragma once

class CGame;

class CGameItem
{
public:

	virtual ~CGameItem();

	// Default constructor (disabled)
	CGameItem() = delete;

	// Copy constructor (disabled)
	CGameItem(const CGameItem&) = delete;

	virtual void Draw(ID2D1HwndRenderTarget* graphics) = 0;

	virtual bool HitTest(int x, int y) = 0;

	// Getters and setters

	virtual void SetId(const wchar_t* id) { this->mId = id; }
	virtual const wchar_t* GetId() { return this->mId; }

	void SetImagePath(const wchar_t* path);
	virtual std::pair<double, double> LinearInterpolate(double xGoal, double yGoal);
	virtual const wchar_t* GetImagePath() { return this->mImagePath; }

	virtual void Update(double elapsed) {}

	virtual void SetX(double x) { this->mX = x; }
	virtual void SetY(double y) { this->mY = y; }
	virtual double GetX() { return this->mX; }
	virtual double GetY() { return this->mY; }

	virtual void SetVelocityX(double v) { this->mVelocityX = v; }
	virtual void SetVelocityY(double v) { this->mVelocityY = v; }
	virtual double GetVelocityX() { return this->mVelocityX; }
	virtual double GetVelocityY() { return this->mVelocityY; }
	virtual double GetVelocity() { return sqrt(pow(this->mVelocityX, 2) + pow(this->mVelocityY, 2)); }

	std::shared_ptr<CGame> GetGame() { return mGame; }
	virtual std::vector<std::pair<double, double>> GetPrevLocs() { return mPrevLocations; }
	virtual void AddLoc(std::pair<double, double> loc);

protected:
	CGameItem(CGame* game, const wchar_t* id);

private:

	// The game this item is a part of 
	std::shared_ptr<CGame> mGame;

	// Image for the item
	const wchar_t* mImagePath = L"";

	// Indicates the type of item
	const wchar_t* mId = L"";

	// X coordinate of the item
	double mX = 0.0;

	// Y coordinate of the item
	double mY = 0.0;

	// X velocity
	double mVelocityX = 0.0;

	// Y velocity
	double mVelocityY = 0.0;

	// Vector of the previous locations this item has been
	std::vector<std::pair<double, double>> mPrevLocations;
};


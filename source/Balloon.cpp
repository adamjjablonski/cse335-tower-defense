/**
 * \file Balloon.cpp
 *
 * \author Jacob Zawacki
  * \author Diego Marzejon
 */

#include <string>
#include "pch.h"
#include "Balloon.h"
#include "Board.h"

using namespace Gdiplus;
using std::unique_ptr;
using std::wstring;

/// Balloon filename 
const wstring BalloonImageName = L"data/images/red-balloon.png";

/** 
 * Constructor
 * \param board The board this is a member of
 */
CBalloon::CBalloon(CBoard* board) : CItem(board)
{
	mBalloonImage = unique_ptr<Bitmap>(Bitmap::FromFile(BalloonImageName.c_str()));
	if (mBalloonImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += BalloonImageName;
		AfxMessageBox(msg.c_str());
	}

}


/**
 * Destructor
 */
CBalloon::~CBalloon()
{
}


/**
 * Draw the balloon
 * \param graphics The graphics context to draw on
 */
void CBalloon::Draw(Gdiplus::Graphics* graphics)
{
	double wid = mBalloonImage->GetWidth();
	double hit = mBalloonImage->GetHeight();
	graphics->DrawImage(mBalloonImage.get(),
		float(GetX() - wid / 2), float(GetY() - hit / 2),
		(float)mBalloonImage->GetWidth(), (float)mBalloonImage->GetHeight());
}


/**
 * Handles updates in time of our balloons
 *
 * Checks for collisions and sets speed
 *
 * \param elapsed Time elapsed since last class call
 */
void CBalloon::Update(double elapsed)
{
	GetBoard()->CheckDartCollision(this);
	GetBoard()->CheckRingCollision(this);
	GetBoard()->CheckBombCollision(this);

    mT += 2.0 * elapsed;
}

/**
 * Test to see if we hit this object with a mouse.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CBalloon::HitTest(double x, double y)
{
	return false;
}
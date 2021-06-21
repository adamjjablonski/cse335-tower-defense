/**
 * \file ButtonGo.cpp
 *
 * \author Adam Jablonski
 */

#include "pch.h"
#include "ButtonGo.h"


/**
 * Custom constructor
 * \param board 
 */
CButtonGo::CButtonGo(CBoard* board) : CItem(board)
{
	SetImage(L"button-go.png");
}

/**
 * Destructor
 */
CButtonGo::~CButtonGo()
{

}

/**
 * Test to see if we hit this object with a mouse.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CButtonGo::HitTest(double x, double y)
{
	double hit = GetImageHeight();
	double wid = GetImageWidth();

	double testX = x - (GetX() * 64);
	double testY = y - (GetY() * 64);

	// Test to see if x, y are in the image
	if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
	{
		// We are outside the image
		return false;
	}

	// Test to see if x, y are in the drawn part of the image
	auto format = GetImagePixelFormat();
	if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
	{
		// This image has an alpha map, which implements the 
		// transparency. If so, we should check to see if we
		// clicked on a pixel where alpha is not zero, meaning
		// the pixel shows on the screen.
		Color color;
		GetImagePixel((int)testX, (int)testY, &color);
		if (color.GetAlpha() != 0)
		{
			SetBoardStart(true);
			mShowButton = false;
			return true;
		}
	}
	else 
	{
		SetBoardStart(true);
		mShowButton = false;
		return true;
	}
}

void CButtonGo::Draw(Gdiplus::Graphics* graphics)
{
	if (mShowButton == true)
	{
		CItem::Draw(graphics);
	}
}
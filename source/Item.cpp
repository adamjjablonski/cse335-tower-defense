/**
 * \file Item.cpp
 *
 * \author Christopher D. Belack
 */

#include "pch.h"
#include "Item.h"
#include "Board.h"

 /// The directory containing all images
const wstring CItem::ImagesDirectory = L"../data/images/";

/**
 * Constructor
 * \param board The board this item is a member of
 */
CItem::CItem(CBoard* board) : mBoard(board)
{
}


/**
 *  Destructor
 */
CItem::~CItem()
{
}


/**
 * Set the image file to draw.
 * \param file The base filename. Blank files are allowed.
 */
void CItem::SetImage(const wstring& file)
{
	if (!file.empty())
	{
		wstring filename = ImagesDirectory + file;
		mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
		if (mItemImage->GetLastStatus() != Ok)
		{
			wstring msg(L"Failed to open ");
			msg += filename;
			AfxMessageBox(msg.c_str());
			return;
		}
	}

	mFile = file;
}


/**
 * Draw the item
 * \param graphics The graphics context to draw on
 */
void CItem::Draw(Gdiplus::Graphics* graphics)
{
	if (mItemImage != nullptr)
	{
		int wid = GetImageWidth() + 1;
		int hit = GetImageHeight() + 1;

		graphics->DrawImage(mItemImage.get(),
			(GetX() * 64), (GetY() * 64),
			wid, hit);
	}
}


/**
 * Check if mouse click hits tile. Override this
 * to implement different functionality specific
 * to a particular class.
 * \param x The X coordinate of the mouse click.
 * \param y The y coordinate of the mouse click.
 */
bool CItem::HitTest(double x, double y)
{
	double hit = GetImageHeight();
	double wid = GetImageWidth();

	// Make x and y relative to the top-left corner of the bitmap image
	// Subtracting the center makes x, y relative to the image center
	// Adding half the size makes x, y relative to theimage top corner
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
		return (color.GetAlpha() != 0);
	}
	else
	{
		return true;
	}
}


/**
 * Sets the board to the starting state
 * \param startValue whether or not we set the board to start
 */
void CItem::SetBoardStart(bool startValue)
{
	CBoard* temp = GetBoard();
	temp->SetGameStart(startValue);
}



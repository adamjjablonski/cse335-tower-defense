/**
 * \file ButtonGo.h
 *
 * \author Adam Jablonski
 *
 * Class that implements the Go! button.
 */

#pragma once

#include "Item.h"

/**
 * Class that implements the Go! button.
 */
class CButtonGo : public CItem
{
public:
	// // // // Public Constructors and Destructors: // // // //

	/// Default constructor (disabled)
	CButtonGo() = delete;

	CButtonGo(CBoard* board);

	~CButtonGo();

	bool HitTest(double x, double y);

	// // // // Public Getters: // // // //

	/**
	 * Get the value of ShowButton, i.e., should button be shown?
	 * \returns true if button should be shown.
	 */
	bool GetShowButton() { return mShowButton; }

	// // // // Public Setters: // // // //

	/**
	 * Set the value of ShowButton.
	 * \param buttonValue The new value of ShowButton.
	 */
	void SetShowButton(bool buttonValue) { mShowButton = buttonValue; }

	// // // // Public Methods: // // // //

	/**
	 * Draws the Go Button
	 * \param graphics The Graphics context to draw on
	 */
	void Draw(Gdiplus::Graphics* graphics) override;

private:
	/// Show Go! button
	bool mShowButton = false;
};

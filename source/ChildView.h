/**
 * \file ChildView.h
 *
 * \author Adam Jablonski
 *
 * Interface of the the CChildView class.
 */

#pragma once

#include "Board.h"
#include "TowerBomb.h"
/**
 * CChildView window.
 */
class CChildView : public CWnd
{
public:
	// Constructors and Destructors:

	/// Default constructor
	CChildView();

	/// Destructor
	virtual ~CChildView();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	

protected:
	// Methods:

	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()


	// Member variables:

	/// Window created?
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

private:
	// Member Variables:

	/// An object that describes our game board.
	CBoard mBoard;

	/// True until the first time we draw
	bool mFirstDraw = true;

	/// Last time we read the timer
	long long mLastTime=0;
	
	/// Rate the timer updates
	double mTimeFreq=0;

	/// Item grabbed by mouse
	std::shared_ptr<CItem> mGrabbedItem;
};

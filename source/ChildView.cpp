
// ChildView.cpp : implementation of the CChildView class
//

#include <string>
#include "pch.h"
#include "framework.h"
#include "project1.h"
#include "Board.h"
#include "Item.h"
#include "Tile.h"
#include "ChildView.h"
#include "DoubleBufferDC.h"
#include "TowerBomb.h"


using namespace Gdiplus;

/// Frame duration in milliseconds
const int FrameDuration = 40;

/// Maximum amount of time to allow for elapsed
const double MaxElapsed = 0.050;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	srand((unsigned int)time(nullptr));
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC paintDC(this); // device context for painting

	CDoubleBufferDC dc(&paintDC); // device context for painting
	Graphics graphics(dc.m_hDC);

	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		* Initialize the elapsed time system
		*/
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);

		mBoard.LoadLevel1();
	}

	/*
	 * Compute the elapsed time since the last draw
	 */
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = ((double(diff) / mTimeFreq)/2);
	mLastTime = time.QuadPart;
	mBoard.Update(elapsed);
	//
	// Prevent tunnelling
	//
	while (elapsed > MaxElapsed)
	{
		mBoard.Update(MaxElapsed);

		elapsed -= MaxElapsed;
	}

	// Consume any remaining time
	if (elapsed > 0)
	{
		mBoard.Update(elapsed);
	}

	CRect rect;
	GetClientRect(&rect);

	// Draw the board.
	mBoard.OnDraw(&graphics, rect.Width(), rect.Height());



}



void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	Invalidate();
	CWnd::OnTimer(nIDEvent);
}



BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return false;
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//CWnd::OnLButtonDown(nFlags, point);
	if (mBoard.GetGameStart())
	{
		return;
	}

	double oX = (point.x - mBoard.GetmXOffset()) / mBoard.GetmScale();
	double oY = (point.y - mBoard.GetmYOffset()) / mBoard.GetmScale();


	mGrabbedItem = mBoard.HitTest(oX , oY);
	if (mGrabbedItem != nullptr)
	{
		// We have selected an item will 
		// move it to the end of mItems
		mBoard.MoveToEnd(mGrabbedItem);
		mBoard.LoadTowers(mGrabbedItem);
	}

}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//CWnd::OnLButtonUp(nFlags, point);
	// invoke OnMouseMove
	OnMouseMove(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//CWnd::OnMouseMove(nFlags, point);

	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		double oX = (point.x - mBoard.GetmXOffset()) / mBoard.GetmScale();
		double oY = (point.y - mBoard.GetmYOffset()) / mBoard.GetmScale();
		int snappedOX = oX / 64;
		int snappedOY = oY / 64;
	


		// If an item is being moved, we only continue to 
		// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{
			//for (auto item : mBoard.mI)
			mGrabbedItem->SetLocation(snappedOX, snappedOY);
		}
		else
		{
			// When the left button is released, we release the
			// item.

			std::shared_ptr<CItem> tile = mBoard.HitTest(snappedOX, snappedOY);

			if (tile != nullptr)
			{
				if (tile->GetPlaceTower())
				{
					mGrabbedItem->SetLocation(snappedOX, snappedOY);
					tile->SetPlaceTowers(false);
				}
				else
				{
					mBoard.AddToDelete(mGrabbedItem);
					mGrabbedItem = nullptr;
				}
			}
			else
			{
				mBoard.AddToDelete(mGrabbedItem);
				mGrabbedItem = nullptr;
			}

			mGrabbedItem = nullptr;
		}

		Invalidate();
	}
}


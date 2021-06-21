/**
 * \file Dart.cpp
 *
 * \author Zhendong Liu
 * 
 */

#include <string>
#include "pch.h"
#include "Dart.h"
#include "Board.h"
#include "VisitorDart.h"
#include <math.h>  
#include "Item.h"
#include "TowerEight.h"

using namespace Gdiplus;
using std::unique_ptr;
using std::wstring;

/// Constant to covert radians to degrees.
const double RtoD = 57.2957795;

/**
 * Constructor
 * \param board The board this is a member of
 */
CDart::CDart(CBoard* board): CItem(board)
{

    SetImage(L"dart.png");
    
}


/**
 * Destructor
 */
CDart::~CDart()
{
}



/**
 * Draw the rotated dart. Rotation is determined by the member
 * variable mAngle, which is the rotation in radians.
 *
 * @param graphics The graphics context to draw on.
 */
void CDart::Draw(Gdiplus::Graphics* graphics)
{

    // Draw rotated dart
    int wid = GetImageWidth();
    int hit = GetImageHeight();
    auto save = graphics->Save();
    graphics->TranslateTransform((REAL)(GetX()),
        (REAL)(GetY()));
    graphics->RotateTransform((REAL)(mAngle * RtoD));
    graphics->DrawImage(GetImage().get(), -wid / 2,  -hit / 2, wid, hit);
    graphics->Restore(save);


}
/**
 * Handle updates in time of our fish
 *
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * \param elapsed Time elapsed since the class call
 */
void CDart::Update(double elapsed)
{
  
    mT += elapsed*200;

  
    SetLocation(mT, 0);

    if(mT >= 100) {
        mToFar = true;
        GetBoard()->DeleteLater(this);
    }
    
}




/**
 * Test to see if we hit this object with a mouse.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CDart::HitTest(double x, double y)
{
    return false;
}

/**
 * Test to see x location of dart.
 * \return x location of dart.
 */
double CDart::GetX()
{
    double a = GetAngle();
   
    double cs = cos(a);
    double x = cs * mT + mOrigin.X;
    return x;
}
/**
 * Test to see y location of dart.
 * \return y location of dart.
 */
double CDart::GetY()
{
    double a = GetAngle();
    double sn = sin(a);

    double y = sn * mT+ mOrigin.Y;
    return y;
}



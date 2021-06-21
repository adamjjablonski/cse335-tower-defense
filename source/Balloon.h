/**
 * \file Balloon.h
 *
 * \author Jacob Zawacki
 * \author Diego Marzejon
 *
 *  Class for managing the balloon object
 */

#pragma once

#include "Item.h"
#include "Balloon.h"


/**
 * Class that implements Balloon object
 */
class CBalloon : public CItem
{
public:
    // Constructors and Destructors:

    /// Disable default constructor.
    CBalloon() = delete;

    /// Copy constructor (disabled)
    CBalloon(const CBalloon&) = delete;

    /// Custom constructor
    CBalloon(CBoard* board);

    /// Destructor
    ~CBalloon();

    // // // // Public Getters: // // // //

    /**
     * Function that returns the T value of a balloon
     * \returns mT The T value of the balloon
     */
    double GetT() { return mT; }

    /**
     * Function that returns the last direction the balloon was moving
     * \returns mLastDirection The last direction the balloon was moving
     */
    wstring GetLastDirection() { return mLastDirection; }

    /**
     * Function that returns whether or not a balloon is moving forward across a tile
     * \returns mIsForward Whether or not the balloon is moving forward across a tile
     */
    bool IsForward() { return mIsForward; }


    // // // // Public Setters: // // // //

    /**
     * Sets the balloons orientation on the tile
     * \param is Whether or not balloon is going forward
     */
    void SetForward(bool is) { mIsForward = is; }

    /**
     * Sets the balloons direction on the tile
     * \param last The last direction the balloon was going
     */
    void SetLastDirection(wstring last) { mLastDirection = last; }


    // // // // Public Methods: // // // //

    void Update(double elapsed);

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    /** 
     *Accept a visitor
     * \param visitor The visitor we accept */
    virtual void Accept(CVisitor* visitor) override { visitor->VisitBalloon(this); }

    bool HitTest(double x, double y);

    /**
     * Decreases the balloons T value
     */
    void DecT() { mT -= 1; }


private:
    // Member Variables:

    /// The image of the balloon
    std::unique_ptr<Gdiplus::Bitmap> mBalloonImage;

    /// T value of balloon
    double mT = 0.0;

    /// bool to check if balloon is going forward
    bool mIsForward = true;

    /// last direction the balloon was moving
    wstring mLastDirection = L"east";

};

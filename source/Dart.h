/**
 * \file Dart.h
 *
 * \author Zhendong Liu
 * 
 *
 * Implements CDart class
 */

#pragma once


#include "Item.h"
#include "Dart.h"
#include<vector>

 /**
  * Implements the CDart class.
  */
class CDart : public CItem
{
public:
    // Constructors and Destructors:

    /// Disable default constructor
    CDart() = delete;

    /// Copy constructor (disabled)
    CDart(const CDart&) = delete;

    /// Custom constructor
    CDart(CBoard* board);

    /// Destructor
    ~CDart();


    // // // // Public Getters: // // // //

    /**
     * Get angle of dart
     * \returns mAngle The angle of the dart
     */
    double GetAngle() { return mAngle; }

    /**
     * Make the longest distance
     * \returns mToFar 100 pixel away from tower
     */
    bool GetToFar() { return mToFar; };

    /** Get x location */
    virtual double GetX() override;

    /** Get y location */
    virtual double GetY() override;


    // // // // Public Setters: // // // //

    /**
     * Sets angle of dart rotation
     * \param angle Angle dart is to be rotated to
     */
    void SetAngle(double angle) { mAngle = angle; }

    /**
     * Set orgin point of dart
     * \param x X location of dart
     * \param y Y location of dart
     */
    void SetOrigin(int x, int y) { mOrigin = Gdiplus::Point(x, y); }

    // // // // Public Methods: // // // //

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    void Update(double elapsed);


    /**
     *Accept a visitor
     * \param visitor The visitor we accept
     */
    virtual void Accept(CVisitor* visitor) override { visitor->VisitDart(this); }


    bool HitTest(double x, double y);


private:
  
    /// origin point for dart
    Gdiplus::Point mOrigin;

    ///the rotation in radians.
    double mAngle = 0;

    ///The distance from the tower is indicated by the variable
    double mT=20;

    ///Decide if the dart move 100 pixel after tower`
    bool mToFar = false;
};


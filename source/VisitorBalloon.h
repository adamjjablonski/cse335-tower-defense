/**
 * \file VisitorBalloon.h
 *
 * \author Diego Marzejon
 *
 * Visitor specific for balloon items
 */

#pragma once
#include "Visitor.h"
#include <vector>

/**
 * Visitor specific for balloons
 */
class CVisitorBalloon : public CVisitor
{

public:

    /** 
     * Visit a CBalloon object
     * \param balloon Balloon we are visiting 
     */
    virtual void VisitBalloon(CBalloon* balloon);

private:
    /// List of balloon locations
    std::vector<std::vector<double>> mLocations;
};


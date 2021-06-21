/**
 * \file VisitorTowerRing.h
 *
 * \author Adam Jablonski
 *
 * Implements a tower ring visitor
 */

#pragma once
#include "Visitor.h"
#include <vector>

class CTowerRing;

/**
 * Visitor that visits ring towers
 */
class CVisitorTowerRing : public CVisitor
{
public:

    /**
     * Visit a CTowerRing
     * \param ring The ring tower we are visiting.
     */
    void VisitTowerRing(CTowerRing* ring);

    /**
     * Gets the list of ring tower locations
     * \return mLocations of ring tower locations
     */
    std::vector<std::vector<double>> GetLocations() { return mLocations; }


private:
    /// List of ring tower locations
    std::vector<std::vector<double>> mLocations;
};

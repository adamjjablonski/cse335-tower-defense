/**
 * \file VisitorDart.h
 *
 * \author Diego Marzejon
 *
 * A visitor that visits darts
 */

#pragma once
#include "Visitor.h"
#include <vector>

class CDart;

/**
 * Visitor that visits darts
 */
class CVisitorDart : public CVisitor
{
public:

    /** 
     * Visit a CDart object
     * \param dart Dart we are visiting 
     */
    void VisitDart(CDart* dart);

    /** 
     * Gets the list of dart locations
     * \return mLocations of dart locations
     */
    std::vector<std::vector<double>> GetLocations() { return mLocations; }


private:
    /// List of dart locations
    std::vector<std::vector<double>> mLocations;
};


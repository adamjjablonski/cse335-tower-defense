/**
 * \file VisitorTowerRing.cpp
 *
 * \author Adam Jablonski
 */

#include "pch.h"
#include "VisitorTowerRing.h"
#include "TowerRing.h"

void CVisitorTowerRing::VisitTowerRing(CTowerRing* ring)
{
    std::vector<double> loc;
    loc.push_back(ring->GetX());
    loc.push_back(ring->GetY());
    mLocations.push_back(loc);

}

/**
 * \file VisitorDart.cpp
 *
 * \author Diego Marzejon
 */

#include "pch.h"
#include "VisitorDart.h"
#include "Dart.h"

void CVisitorDart::VisitDart(CDart* dart)
{
    std::vector<double> loc;
    loc.push_back(dart->GetX());
    loc.push_back(dart->GetY());
    mLocations.push_back(loc);

}

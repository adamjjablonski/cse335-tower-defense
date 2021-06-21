/**
 * \file XmlTileDeclaration.cpp
 *
 * \author Adam Jablonski
 */

#include "pch.h"
#include "XmlTileDeclaration.h"

/**
 * Custom constructor
 * \param node The XML node used to create this declaration
 */
CXmlTileDeclaration::CXmlTileDeclaration(shared_ptr<CXmlNode> node)
{
	mId = node->GetAttributeValue(L"id", L"");
	mImage = node->GetAttributeValue(L"image", L"");
	mType = node->GetAttributeValue(L"type", L"");
}


/**
 * Destructor
 */
CXmlTileDeclaration::~CXmlTileDeclaration()
{
}
/**
 * \file XmlTileDeclaration.h
 *
 * \author Adam Jablonski
 *
 * File used to load the xml file
 */

#pragma once

#include "XmlNode.h"

using std::shared_ptr;
using std::wstring;
using xmlnode::CXmlNode;

/**
 * Implementation of the CXmlTileDeclaration class
 */
class CXmlTileDeclaration
{
public:
	// // // // Public Constructors and Destructors: // // // //
	
	/// Default constructor (disabled)
	CXmlTileDeclaration() = delete;

	CXmlTileDeclaration(shared_ptr<CXmlNode> node);

	~CXmlTileDeclaration();

	// // // // Public Getters: // // // //

	/**
	 * Get the tile ID.
	 * \returns tile ID.
	 */
	wstring GetId() { return mId; }

	/**
	 * Get the tile image.
	 * \returns tile image.
	 */
	wstring GetImage() { return mImage; }

	/**
	 * Get the tile type.
	 * \returns tile type.
	 */
	wstring GetType() { return mType; }

private:
	// Private Member Variables:

	/// Tile ID
	wstring mId = L"";

	/// Tile image
	wstring mImage = L"";

	/// Tile type if road
	wstring mType = L"";

};


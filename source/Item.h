/**
 * \file Item.h
 *
 * \author Christopher D. Belack
 * \author Adam Jablonski
 *
 * Implements the purely abstract CItem superclass.
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <vector>
#include "Visitor.h"
#include "XmlNode.h"

using namespace Gdiplus;
using std::begin;
using std::cout;
using std::end;
using std::endl;
using std::map;
using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::wstring;
using xmlnode::CXmlNode;

class CBoard;

/**
 * Implements the purely asbtract CItem superclass.
 */
class CItem
{
public:
	// // // // Public Constants: // // // //

	/// The directory where images are stored
	static const wstring ImagesDirectory;

	/// Tile offset to left of center
	const static int OffsetLeft = 32;

	/// Tile offset above center
	const static int OffsetDown = 32;

	/// Tile grid spacing
	static const int GridSpacing = 64;


	// // // // Public Constructors and Destructors: // // // //

	/// Default constructor (disabled)
	CItem() = delete;

	/// Copy constructor (disabled)
	CItem(const CItem&) = delete;

	/// Destructor
	virtual ~CItem();


	// // // // Public Getters: // // // //

	/**
	 * Get the file name for this item's image.
	 * \returns Filename or blank if none
	 */
	std::wstring GetFile() { return mFile; }

	/**
	 * Get the x location of the item.
	 * \returns x location in pixels
	 */
	virtual double GetX() { return mX; }

	/**
	 * Get the y location of the item.
	 * \returns y location in pixels
	 */
	virtual double GetY()  { return mY; }

	/**
	 * Gets the image file for the current item
	 * \returns The item's image file
	 */
	shared_ptr<Bitmap> CItem::GetImage() { return  mItemImage; };

	/**
	 * Getter for image width
	 * \returns mItemImage int width of image
	 */
	double GetImageWidth() { return mItemImage->GetWidth(); }

	/**
	 * Getter for image height
	 * \returns mItemImage int height of image
	 */
	double GetImageHeight() { return mItemImage->GetHeight(); }

	/**
	 * Getter for image pixel format
	 * \returns The pixel format for mItemImage
     */
	int GetImagePixelFormat() { return mItemImage->GetPixelFormat(); }

	/**
	 * Getter for image pixel
	 * \param testX X pixel to test
	 * \param testY Y pixel to test
	 * \param color Color of pixel
	 */
	void GetImagePixel(double testX, double testY, Color *color) { mItemImage->GetPixel((int)testX, (int)testY, color); }

	/**
	 * Get the board this item is in
	 * \returns board pointer
	 */
	CBoard* GetBoard() { return mBoard; }

	/**
	 * Get the values of mPlaced.
	 * \returns the value of mPlaced.
	 */
	bool GetPlaced() { return mPlaced; }


	// // // // Public Setters: // // // //

	/// Set the item location
    /// \param x X location
    /// \param y Y location
	void SetLocation(double x, double y) { mX = x; mY = y; }

	/**
	 * Set the item's x location
	 * \param x X location
	 */
	void SetX(double x) { mX = x; }

	/**
	 * Set the item's y location
	 * \param y Y location
	 */
	void SetY(double y) { mY = y; }

	void SetImage(const wstring& file);

	void SetBoardStart(bool startValue);
	
	/**
	 * Set the mirror status
	 * \param m New mirror flag
	 */
	void SetMirror(bool m) { mMirror = m; }

	/**
	 * Set the value of mPlaceTowers.
	 * \param newValue The new value of mPlaceTowers
	 */
	void SetPlaceTowers(bool newValue) { mPlaceTowers = newValue; }

	/**
	 * Returns if you can place towers on this tile
	 * \returns if you can place towers on this tile
	 */
	bool GetPlaceTower() { return mPlaceTowers; }

	/**
	 * Set mPlaced for items that are placed.
	 * \param newValue The new value of mPlaced.
	 */
	void SetPlaced(bool newValue) { mPlaced = newValue; }

	// // // // Public Methods: // // // //

	virtual void Draw(Gdiplus::Graphics* graphics);

	/**
	 * Handle updates for animation.
	 * \param elapsed The time since the last update
	 */
	virtual void Update(double elapsed) {}

	/** 
	 * Pure virtual function handling whether a mouse click hits an item
	 * \returns Whether or not a mouse click hit an item
	 */
	virtual bool HitTest(double x, double y) = 0;

	/** 
	 *Accept a visitor
	 * \param visitor The visitor we accept 
	 */
	virtual void Accept(CVisitor* visitor) {}

	/**
	 * Used to add a balloon to the track
	 * \param balloon balloon to be added
	 */
	virtual void Add(std::shared_ptr<CBalloon> balloon) {}

	/**
	 * Used to check balloon collision with ring tower rings.
	 * \param balloon The balloon to check
	 * \param double x The x coordinate of the balloon
	 * \param double y The y coordinate of the balloon
	 */
	virtual bool CheckRingCollision(shared_ptr<CItem> balloon) { return false; }

	/**
	 * Used to check balloon collision with ring tower rings.
	 * \param balloon The balloon to check
	 * \param double x The x coordinate of the balloon
	 * \param double y The y coordinate of the balloon
	 */
	virtual bool CheckBombCollision(shared_ptr<CItem> balloon) { return false; }

protected:
	// // // // Protected Constructors and Destructors: // // // //

	/**
	 * Image constructor
	 * \param aquarium Aquarium node
	 * \param filename Filename string of item
	 */
	CItem(CBoard* board);

private:
	// // // // Private Member Variables: // // // //

	/// The board this item is contained in.
	CBoard* mBoard;

	// Item location on the board.
	double   mX = 0;     ///< X location for the center of the item
	double   mY = 0;     ///< Y location for the center of the item

	/// The image of this tile
	shared_ptr<Bitmap> mItemImage;

	/// The file for this item's image.
	wstring mFile;

	/// True mirrors the item's image.
	bool mMirror = false;

	/// Item is a tower from menu that was placed
	bool mPlaced = false;

	/// Can towers be placed on this?
	bool mPlaceTowers = false;
};

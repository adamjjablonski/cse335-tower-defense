/**
 * \file Board.h
 *
 * \author Diego Marzejon
 *
 * Board that contains all items
 */

#pragma once

#include "pch.h"
#include "Item.h"
#include "ButtonGo.h"
#include "Tile.h"
#include "XmlNode.h"
#include "XmlTileDeclaration.h"

using namespace Gdiplus;
using std::make_shared;

class CItem;

/**
 * Implements a board to be inhabited by CItems
 */
class CBoard
{
public:
	// Public Constructors and Destructors:

	/// Default constructor
	CBoard();

	/// Copy constructor (disabled)
	CBoard(const CBoard&) = delete;

	// Public Methods:

	void OnDraw(Gdiplus::Graphics* graphics, int width, int height);

	void Add(std::shared_ptr<CItem> item);

	void AddTile(std::shared_ptr<CTile> tile);

	void MoveToEnd(std::shared_ptr<CItem> item);

	std::shared_ptr<CItem> HitTest(double x, double y);

	void Clear();

	void LoadLevel(const wstring& filename);

	void XmlTile(shared_ptr<CXmlNode> node);
	
	void SetupTile(shared_ptr<CXmlNode> node, shared_ptr<CTile> tile);

	void LoadLevel1();

	void LoadLevel2();

	void LoadLevel3();

	void Update(double elapsed);

	bool CheckDartCollision(CBalloon* balloon);

	bool CheckRingCollision(CBalloon* balloon);

	bool CheckBombCollision(CBalloon* balloon);

	virtual void Accept(CVisitor* visitor);

	void DeleteItem(std::shared_ptr<CItem> item);

	void AddBalloon();
	void DeleteLater(CItem* item);

	void LoadTowers(std::shared_ptr<CItem> mGrabbedItem);

	/** Subtracts a point from the game score */
	void SubtractScore() { mGameScore -= 1; }

	/** Adds a point to the Number of Balloons Resolved. Called when a balloon leaks. */
	void BalloonLeaked() { mNumberBalloonsResolved += 1; }

	/** Increments the tower bomb count */
	void IncrementTowerBombCount() { mTowerBombCount += 1; }

	// // // // Public Getters: // // // //

	/** 
	 * Get the scale for pixels
	 * \returns mScale The pixel scale
	 */
	double GetmScale() const { return mScale; }

	/** 
	 * Get the X offset
	 * \returns mXOffset the x offset
	 */
	double GetmXOffset() const { return mXOffset; }

	/**
	 * Get the Y offset
	 * \returns mYOffset the y offset
	 */
	double GetmYOffset() const { return mYOffset; }

	/**
	 * Gets the Tower Bomb Count
	 * \returns mTowerBombCount The Tower Bomb Count
	 */
	int GetTowerBombCount() const { return mTowerBombCount; }

	/**
	 * Get the game height
	 * \returns Height Game area height in virtual pixels
	 */
	double GetHeight() { return Height; }

	/**
	 * Get the game width
	 * \returns Width Game area width in virtual pixels
	 */
	double GetWidth() { return Width; }

	/**
	 * Determines whether the game starts or not
	 * \returns mGameStart Bool that determines whether the game starts
	 */
	bool GetGameStart() { return mGameStart; };

	/**
	 * Gets the number of items
	 * \returns The size of the item list
	 */
	int GetItemsSize() { return mItems.size(); }

	// // // // Public Setters: // // // //

	void SetGameStart(bool startValue);





	/** 
	 * Adds an item to mItemsToDelete
	 * \param toDelete item that needs to be deleted later
	 */
	void AddToDelete(std::shared_ptr<CItem> toDelete) { mItemsToDelete.push_back(toDelete); }

	// // // // Public Iterators: // // // //

	/** Iterator that iterates over the Board Items */
	class Iter
	{
	public:
		/** Constructor
		 * \param board The Board we are iterating over
		 * \param pos the pos of the Board 
		 */
		Iter(CBoard* board, int pos) : mBoard(board), mPos(pos) {}

		/** Test for end of the iterator
		 * \param other the other iterator compared to
		 *  \returns True if we this position equals not equal to the other position */
		bool operator!=(const Iter& other) const
		{
			return mPos != other.mPos;
		}

		/** Get value at current position
		 * \returns Value at mPos in the collection 
		 */
		std::shared_ptr<CItem> operator *() const { return mBoard->mItems[mPos]; }

		/** Increment the iterator
		 * \returns Reference to this iterator 
		 */
		const Iter& operator++()
		{
			mPos++;
			return *this;
		}


	private:
		CBoard* mBoard;   ///< Board we are iterating over
		int mPos;       ///< Position in the collection
	};

	/**
	 * Get an iterator for the beginning of the collection
	 * \returns Iter object at position 0
	 */
	Iter begin() { return Iter(this, 0); }

	/**
	 * Get an iterator for the end of the collection
	 * \returns Iter object at position past the end
	 */
	Iter end() { return Iter(this, mItems.size()); }




private:
	// // // // Private Member Variables: // // // //

	/// Game area width in virtual pixels
	const static int Width = 1224;

	/// Game area height in virtual pixels
	const static int Height = 1024;

	/// Temporary list of items to be deleted from the board
	std::vector<std::shared_ptr<CItem>> mItemsToDelete;

	/// All of the items to populate our Board
	vector<shared_ptr<CItem> > mItems;

	/// Tile declaration nodes from XML file
	/// These are NOT items on the game board
	map<wstring, shared_ptr<CXmlTileDeclaration> > mDeclarations;

	/// Scale for pixels
	float mScale = 0;
	
	/// X offset
	float mXOffset = 0;

	/// Y offset.
	float mYOffset = 0;
	
	/// flag if there needs to be a new starting tile set.
	bool mStart = true;

	/// Pointer to Go! button
	shared_ptr<CButtonGo> mGoButton;
	
	/// Current level
	int mGameLevel = 1;
	
	/// Timer for game elements.
	double mGameTimer = 0;

	/// Game Score.
	int mGameScore = 0;

	/// Start game
	bool mGameStart = false;

	/// End game
	bool mGameEnd = false;

	/// Game won?
	bool mGameWon = false;

	/// Number of balloons in level.
	int mNumberBalloons = 0;

	/// Time until next balloon gets sent/loads in
	double mTimeToNextBalloon = 0;

	/// Maximum number of balloons allowed.
	const int mMaxNumberBalloons = 30;

	/// Number of balloons which have popped or escaped.
	int mNumberBalloonsResolved = 0;

	/// pointer to starting tile
	shared_ptr<CTile> mStartTile;

	/// vector of tiles 
	std::vector<shared_ptr<CTile>> mTiles;

	/// Level splash timer
	double mLevelSplashTimer = 0;
	
	/// Level start splash
	wstring mLevelStartSplash = L"";

	/// Level complete splash
	wstring mLevelCompleteSplash = L"Level Complete!";

	/// Level loss splash
	wstring mLevelLossSplash = L"You Lose!";

	/// Tower bomb count
	int mTowerBombCount = 0;

};

/**
 * \file Board.cpp
 *
 * \author Chris Belack
 * \author Adam Jablonski
 * \author Diego Marzejon
 * \author Jacob Zawacki
 * \author Liu Zhendong
 */

#include <typeinfo>

#include "pch.h"
#include "Board.h"

#include "Balloon.h"
#include "ButtonGo.h"
#include "Dart.h"
#include "Tile.h"
#include "TileHouse.h"
#include "TileOpen.h"
#include "TileRoad.h"
#include "TileTrees.h"
#include "TowerBomb.h"
#include "TowerEight.h"
#include "TowerRing.h"
#include "Visitor.h"
#include "TowerVisitor.h"
#include "VisitorBalloon.h"
#include "VisitorDart.h"
#include "VisitorTowerRing.h"
#include "Item.h"
#include "TowerSeek.h"

using namespace std;

/**
 * Board constructor
 */
CBoard::CBoard()
{
}


/**
 * Draw the Board
 * \param graphics The GDI+ graphics context to draw on
 * \param width Width of game window
 * \param height Height of game window
 */
void CBoard::OnDraw(Gdiplus::Graphics* graphics, int width, int height)
{
	// Fill the background with black
	SolidBrush brush(Color::Black);
	graphics->FillRectangle(&brush, 0, 0, width, height);

	// Automatic Scaling
	float scaleX = float(width) / float(Width);
	float scaleY = float(height) / float(Height);
	mScale = min(scaleX, scaleY);

	// Ensure it is centered horizontally
	mXOffset = (float)((width - Width * mScale) / 2);

	// Ensure it is centered vertically
	mYOffset = (float)((height - Height * mScale) / 2);

	graphics->TranslateTransform(mXOffset, mYOffset);
	graphics->ScaleTransform(mScale, mScale);

	// Draw items on board
	for (auto item : mItems)
	{
		item->Draw(graphics);
	}

	// Draw scoreboard
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font ScoreboardFont(&fontFamily,
		40, 
		FontStyleRegular, 
		UnitPixel);

	SolidBrush yellow(Color(255, 255, 0));
	Gdiplus::StringFormat ScoreboardFormat;
	ScoreboardFormat.SetAlignment(StringAlignmentCenter);
	ScoreboardFormat.SetLineAlignment(StringAlignmentCenter);

	graphics->DrawString(L"Score:",
		-1,
		&ScoreboardFont,
		PointF(1120, 512),
		&ScoreboardFormat,
		&yellow);

	wstring GameScoreString = to_wstring(mGameScore);
	const wchar_t* GameScoreStringPtr = GameScoreString.c_str();
	graphics->DrawString(GameScoreStringPtr,
		-1,
		&ScoreboardFont,
		PointF(1120, 560),
		&ScoreboardFormat,
		&yellow);

	// Draw level splashes
	Gdiplus::Font SplashFont(&fontFamily,
		100,
		FontStyleBold,
		UnitPixel);

	SolidBrush red(Color(235, 64, 52));
	Gdiplus::StringFormat SplashFormat;
	SplashFormat.SetAlignment(StringAlignmentCenter);
	SplashFormat.SetLineAlignment(StringAlignmentCenter);

	if (mGameStart == false && mLevelSplashTimer < 3)
	{
		graphics->DrawString(mLevelStartSplash.c_str(),
			-1,
			&SplashFont,
			PointF(512, 512),
			&SplashFormat,
			&red);
	}

	if (mGameStart == true && mGameEnd == true && mGameWon == false && mLevelSplashTimer < 3)
	{
		graphics->DrawString(mLevelLossSplash.c_str(),
			-1,
			&SplashFont,
			PointF(512, 512),
			&SplashFormat,
			&red);
	}

	if (mGameStart == true && mGameEnd == true && mGameWon == true && mLevelSplashTimer < 3)
	{
		graphics->DrawString(mLevelCompleteSplash.c_str(),
			-1,
			&SplashFont,
			PointF(512, 512),
			&SplashFormat,
			&red);
	}

}


/**
 * Add an item to the Board
 * \param item New item to add
 */
void CBoard::Add(std::shared_ptr<CItem> item)
{
	mItems.push_back(item);
}


/**
 * Adds a tile to the Board
 * \param tile New tile to add
 */
void CBoard::AddTile(std::shared_ptr<CTile> tile)
{
	mTiles.push_back(tile);
}


/**
 * Move an item to the end of the vector
 * \param item New item to move
 */
void CBoard::MoveToEnd(std::shared_ptr<CItem> item)
{
	auto loc = find(::begin(mItems), ::end(mItems), item);
	if (loc != ::end(mItems))
	{
		item = *loc;
		mItems.erase(loc);
		mItems.push_back(item);

	}

}


/**
 * Test an x,y click location to see if it clicked
 * on some item in the Board.
 * \param x X location
 * \param y Y location
 * \returns Pointer to item we clicked on or nullptr if none.
 */
std::shared_ptr<CItem> CBoard::HitTest(double x, double y)
{

	for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
	{
		//shared_ptr<CItem> bomb = make_shared<CTowerBomb>(this);
		
		//if (typeid(bomb) == typeid(i) && (*i)->HitTest(x, y))
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}

	}

	return  nullptr;
}


/**
 * Clear the existing contents of the board.
 */
void CBoard::Clear()
{
	map<wstring, shared_ptr<CXmlTileDeclaration> >().swap(mDeclarations);
	vector<shared_ptr<CItem> >().swap(mItems);
	vector<shared_ptr<CItem> >().swap(mItemsToDelete);
}


/**
 * Loads a new tower to the menu after one gets picked up
 * \param mGrabbedItem The original menu tower that just got picked up
 */
void CBoard::LoadTowers(std::shared_ptr<CItem> mGrabbedItem)
{
	if (mGrabbedItem->GetY() == 3 && mGrabbedItem->GetX() == 17)
	{
		mGrabbedItem->SetPlaced(true);
		auto NewMenuTowerEight = make_shared<CTowerEight>(this);
		NewMenuTowerEight->SetLocation(17, 3);
		this->Add(NewMenuTowerEight);

	}
	else if (mGrabbedItem->GetY() == 4.5 && mGrabbedItem->GetX() == 17)
	{
		mGrabbedItem->SetPlaced(true);
		auto NewMenuTowerRing = make_shared<CTowerRing>(this);
		NewMenuTowerRing->SetLocation(17, 4.5);
		this->Add(NewMenuTowerRing);
	}
	else if (mGrabbedItem->GetY() == 6 && mGrabbedItem->GetX() == 17)
	{
		mGrabbedItem->SetPlaced(true);
		auto NewMenuTowerBomb = make_shared<CTowerBomb>(this);
		NewMenuTowerBomb->SetLocation(17, 6);
		this->Add(NewMenuTowerBomb);
	}
	else if (mGrabbedItem->GetY() == 1.5 && mGrabbedItem->GetX() == 17)
	{
		mGrabbedItem->SetPlaced(true);
		auto NewMenuTowerSeek = make_shared<CTowerSeek>(this);
		NewMenuTowerSeek->SetLocation(17, 1.5);
		this->Add(NewMenuTowerSeek);
	}
}



/**
 * Load all tiles from a level XML file.
 * \param filename The name of the level XML file.
 */
void CBoard::LoadLevel(const wstring& filename)
{
	// Clear the board.
	Clear();

	mStart = true;

	// Add menu items to board

	auto MenuTowerSeek = make_shared<CTowerSeek>(this);
	MenuTowerSeek->SetLocation(17, 1.5);
	this->Add(MenuTowerSeek);

	auto MenuTowerEight = make_shared<CTowerEight>(this);
	MenuTowerEight->SetLocation(17, 3);
	this->Add(MenuTowerEight);

	auto MenuTowerRing = make_shared<CTowerRing>(this);
	MenuTowerRing->SetLocation(17, 4.5);
	this->Add(MenuTowerRing);

	auto MenuTowerBomb = make_shared<CTowerBomb>(this);
	MenuTowerBomb->SetLocation(17, 6);
	this->Add(MenuTowerBomb);

	auto MenuButtonGo = make_shared<CButtonGo>(this);
	MenuButtonGo->SetLocation(16.4, 14);
	this->Add(MenuButtonGo);
	mGoButton = MenuButtonGo;

	try
	{
		// Open the level XML file.
		shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

		if (root == nullptr)
		{
			wstring msg(L"Failed to open ");
			msg += filename;
			AfxMessageBox(msg.c_str());
			return;
		}
		
		// Traverse the chhildren of the XML document root node.
		for (auto child : root->GetChildren())
		{
			if (child->GetType() == NODE_ELEMENT)
			{
				wstring name = child->GetName();

				if (child->GetName() == L"declarations")
				{
					for (auto grandchild : child->GetChildren())
					{
						auto declaration = make_shared<CXmlTileDeclaration>(grandchild);

						mDeclarations[declaration->GetId()] = declaration;
					}
				}

				if (child->GetName() == L"items")
				{
					for (auto grandchild : child->GetChildren())
					{
						XmlTile(grandchild);
					}
				}
			}
		}
	}
	catch (CXmlNode::Exception ex)
	{
		cout << ex.Message().c_str() << endl;
	}
}

/**
 * Called by LoadLevel to create tiles using
 * XML file nodes.
 * \param node The XML node of the tile to create.
 */
void CBoard::XmlTile(shared_ptr<CXmlNode> node)
{
	if (node->GetName() == L"road")
	{
		shared_ptr<CTileRoad> tile;
		tile = make_shared<CTileRoad>(this);

		// Get type from declarations
		auto id = node->GetAttributeValue(L"id", L"");
		tile->SetType(mDeclarations[id]->GetType());

		// set flag if it is the start tile
		if (mStart)
		{
			tile->SetStart(true);
			mStart = false;
			mStartTile = tile;
		}

		SetupTile(node, tile);
	}

	if (node->GetName() == L"open")
	{
		shared_ptr<CTileOpen> tile;
		tile = make_shared<CTileOpen>(this);
		tile->SetPlaceTowers(true);
		SetupTile(node, tile);
	}

	if (node->GetName() == L"house")
	{
		shared_ptr<CTileHouse> tile;
		tile = make_shared<CTileHouse>(this);
		SetupTile(node, tile);
	}

	if (node->GetName() == L"trees")
	{
		shared_ptr<CTileTrees> tile; 
		tile = make_shared<CTileTrees>(this);
		SetupTile(node, tile);
	}
}


/**
 * Reads an xml node and prepares the tile for placement
 * \param node Xml Node with tile info
 * \param tile The Tile being created from the xml node
 */
void CBoard::SetupTile(shared_ptr<CXmlNode> node, shared_ptr<CTile> tile)
{

	auto id = node->GetAttributeValue(L"id", L"");
	auto x = node->GetAttributeIntValue(L"x", 0);
	auto y = node->GetAttributeIntValue(L"y", 0);

	tile->SetImage(mDeclarations[id]->GetImage());
	tile->SetX(x);
	tile->SetY(y);

	if (tile != nullptr)
	{
		Add(tile);
		AddTile(tile);
	}
}


/**
 * Loads Level 1
 */
void CBoard::LoadLevel1()
{
	this->LoadLevel(L"../data/levels/level1.xml");
	mGameStart = false;
	mGameEnd = false;
	mGameLevel = 1;
	mLevelStartSplash = L"Level 1\nBegin!";
	mLevelSplashTimer = 0;
	mNumberBalloons = 0;
	mNumberBalloonsResolved = 0;
	mGoButton->SetShowButton(false);
}

/**
 * Loads level 2
 */
void CBoard::LoadLevel2()
{
	this->LoadLevel(L"../data/levels/level2.xml");
	mGameStart = false;
	mGameEnd = false;
	mGameLevel = 2;
	mLevelStartSplash = L"Level 2\nBegin!";
	mLevelSplashTimer = 0;
	mNumberBalloons = 0;
	mNumberBalloonsResolved = 0;
	mGoButton->SetShowButton(false);
}

/**
 * Loads level 3
 */
void CBoard::LoadLevel3()
{
	this->LoadLevel(L"../data/levels/level3.xml");
	mGameStart = false;
	mGameEnd = false;
	mGameLevel = 3;
	mLevelStartSplash = L"Level 3\nBegin!";
	mLevelSplashTimer = 0;
	mNumberBalloons = 0;
	mNumberBalloonsResolved = 0;
	mGoButton->SetShowButton(false);
}

/** 
 * Accept a visitor for the collection
 * \param visitor The visitor for the collection
 */
void CBoard::Accept(CVisitor* visitor)
{
	for (auto item : mItems)
	{
		item->Accept(visitor);
	}
}

/**  
 * Delete an item from the board
 * \param item The item to delete.
 */
void CBoard::DeleteItem(std::shared_ptr<CItem> item)
{
	auto loc = find(::begin(mItems), ::end(mItems), item);
	if (loc != ::end(mItems))
	{
		mItems.erase(loc);
	}
}

/**
 * Adds a balloon to a tile and the board
 */
void CBoard::AddBalloon()
{
	auto balloon = make_shared<CBalloon>(this);

	for (auto item : mItems)
	{
		if (item.get() == mStartTile.get())
		{
			Add(balloon);
			item->Add(balloon);
			break;
		}
	}
}

/**
 * Manages a temporary list of items to delete
 * \param toDelete pointer to the item to be deleted
 */
void CBoard::DeleteLater(CItem* toDelete)
{
	for (auto item : mItems) {
		if (item.get() == toDelete) mItemsToDelete.push_back(item);
	}
}

/**
 * Handle updates for animation
 * \param elapsed The time since the last update
 */
void CBoard::Update(double elapsed)
{
	//original if statement was: (mGameStart == true && mTimeToNextBalloon <= 0 && mNumberBalloons <= mMaxNumberBalloons)
	// changing that led to only 30 balloons
	if (mGameStart == true && mTimeToNextBalloon <= 0 && mNumberBalloons < mMaxNumberBalloons)
	{
		AddBalloon();
		mNumberBalloons++;
		mTimeToNextBalloon = (18.0 / 128.0) * 4;
	}

	for (auto deletableItem : mItemsToDelete)
	{
		DeleteItem(deletableItem);
	}

	vector<shared_ptr<CItem> >().swap(mItemsToDelete);
	
	mTimeToNextBalloon -= elapsed;

	if (mGameStart == false)
	{
		mLevelSplashTimer += elapsed;
		if (mLevelSplashTimer > 3)
		{
			mGoButton->SetShowButton(true);
		}
	}

	if (mGameStart == true)
	{
		mGameTimer += elapsed;
	}
	
	if (mNumberBalloonsResolved == mMaxNumberBalloons)
	{
		mGameEnd = true;
		mLevelSplashTimer += elapsed;
		if (mGameScore > 0)
		{
			mGameWon = true;
		}
		if (mLevelSplashTimer > 3)
		{
			if (mGameWon == true)
			{
				if (mGameLevel == 1)
				{
					LoadLevel2();
				}
				
				else if (mGameLevel == 2)
				{
					LoadLevel3();
				}

				else if (mGameLevel == 3)
				{
					LoadLevel3();
				}
			}

			else
			{
				if (mGameLevel == 1)
				{
					LoadLevel1();
				}

				else if (mGameLevel == 2)
				{
					LoadLevel2();
				}

				else if (mGameLevel == 3)
				{
					LoadLevel3();
				}
			}
		}

	}

	for (auto item : mItems)
	{
		if (item != nullptr)
		{
			item->Update(elapsed);
		}
		
	}

}

/**
 * Takes a balloon, checks all darts locations, if there is overlap, delete the balloon
 *
 * \param balloon balloon to check if collision
 * \returns true if there was a collsion, false otherwise
 */
bool CBoard::CheckDartCollision(CBalloon* balloon)
{
	// find the balloon in mItems
	std::shared_ptr<CItem> balloonSmart;
	for (auto item : mItems)
	{
		if (item.get() == balloon)
		{
			balloonSmart = item;
		}
	}

	CVisitorDart visitor;
	Accept(&visitor);
	std::vector<std::vector<double>> loc = visitor.GetLocations();
	for (auto item : loc)
	{
		double diffX = item[0] - balloon->GetX();
		double diffY = item[1] - balloon->GetY();

		if (diffX >= -15 && diffX <= 15)
		{
			if (diffY >= -15 && diffY <= 15)
			{
				AddToDelete(balloonSmart);
				mNumberBalloonsResolved += 1;
				// call to add points to scoreboard
				mGameScore+=10;
				return true;
			}
		}
	}

	return false;
}

/**
 * Takes a balloon, checks all ring location, if there is overlap, delete the balloon
 *
 * \param balloon balloon to check if collision
 * \returns true if there was a collsion, false otherwise
 */
bool CBoard::CheckRingCollision(CBalloon* balloon)
{
	// find the balloon in mItems
	std::shared_ptr<CItem> balloonSmart;
	for (auto item : mItems)
	{
		if (item.get() == balloon)
		{
			balloonSmart = item;
		}
	}

	for (auto item : mItems)
	{
		if (item->CheckRingCollision(balloonSmart))
		{
			AddToDelete(balloonSmart);
			mNumberBalloonsResolved += 1;
			// call to add points to scoreboard
			mGameScore += 3;				
			return true;
		}
	}
	return false;
}

/**
 * Takes a balloon, checks all ring location, if there is overlap, delete the balloon
 *
 * \param balloon balloon to check if collision
 * \returns true if there was a collsion, false otherwise
 */
bool CBoard::CheckBombCollision(CBalloon* balloon)
{
	// find the balloon in mItems
	std::shared_ptr<CItem> balloonSmart;
	for (auto item : mItems)
	{
		if (item.get() == balloon)
		{
			balloonSmart = item;
		}
	}

	for (auto item : mItems)
	{
		if (item->CheckBombCollision(balloonSmart))
		{
			DeleteItem(balloonSmart);
			mNumberBalloonsResolved += 1;
			// call to add points to scoreboard
			mGameScore += 2;
			return true;
		}
	}
	return false;
}

/**
 * Sets the game to its starting state
 * \param startValue Whether or not the game is loaded into starting state
 */
void CBoard::SetGameStart(bool startValue)
{ 
	mGameStart = startValue;
	mLevelSplashTimer = 0;
}

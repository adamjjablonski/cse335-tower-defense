

#include "pch.h"
#include "CppUnitTest.h"

#include "Board.h"

#include "TowerBomb.h"
#include "TowerEight.h"
#include "TowerRing.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(TowerTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestNothing)
		{
			// This is an empty test just to ensure the system is working
		}

		TEST_METHOD(TestTowerConstructs)
		{
			CBoard board;

			CTowerBomb towerBomb(&board);

			CTowerEight towerEight(&board);

			CTowerRing towerRing(&board);

		}
	};
}
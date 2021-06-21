#include "pch.h"
#include "CppUnitTest.h"

#include "Board.h"
#include "Dart.h"
#include "Balloon.h"

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CollisionTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestCollision)
		{
			CBoard board;

			auto dart1 = make_shared<CDart>(&board);
			dart1->SetLocation(100, 100);
			board.Add(dart1);

			Assert::IsTrue(dart1->GetX() == 100);

			Assert::IsTrue(dart1->GetY() == 100);

			auto balloon1 = make_shared<CBalloon>(&board);
			balloon1->SetLocation(100, 100);
			board.Add(balloon1);

			Assert::IsTrue(balloon1->GetX() == 100);

			Assert::IsTrue(balloon1->GetY() == 100);

			int before = board.GetItemsSize();

			//Assert::IsTrue(before == 5);

			board.Update(.05);

			// is getting erased from the list - check for memory leaks once it runs
			Assert::IsTrue(before == board.GetItemsSize()+1);

			//Assert::IsTrue(balloon1 == nullptr);
			
		}
	};
}

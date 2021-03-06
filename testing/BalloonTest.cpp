#include "pch.h"
#include "CppUnitTest.h"

#include "Board.h"

#include "Balloon.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(BalloonTest)
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

		TEST_METHOD(TestBalloon)
		{
			CBoard board;

			CBalloon balloon1(&board);

			Assert::IsTrue(balloon1.GetX() == 0);

			balloon1.SetX(50);

			Assert::IsTrue(balloon1.GetX() == 50);

			Assert::IsTrue(balloon1.GetY() == 0);





		}

	};
}
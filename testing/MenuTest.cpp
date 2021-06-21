#include "pch.h"
#include "CppUnitTest.h"

#include "Board.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(MenuTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(ScoreboardConstruct)
		{
			CBoard board;
			//CScoreboard scoreboard(&board);
		}

		TEST_METHOD(ScoreboardMath)
		{
			/*
			CBoard board;
			CScoreboard scoreboard(&board);

			Assert::IsTrue(scoreboard.GetScore() == 0);

			scoreboard.AddScore(100);
			Assert::IsTrue(scoreboard.GetScore() == 100);

			scoreboard.SubtractScore(50);
			Assert::IsTrue(scoreboard.GetScore() == 50);
			*/
		}

	};
}
#include "pch.h"
#include "CppUnitTest.h"
#include "Board.h"
#include "Dart.h"
#include "VisitorDart.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(VisitorTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		TEST_METHOD(TestVisitors)
		{

			CBoard board;

			auto dart1 = make_shared<CDart>(&board);
			dart1->SetLocation(100, 100);
			board.Add(dart1);

			auto dart2 = make_shared<CDart>(&board);
			dart2->SetLocation(100, 100);
			board.Add(dart2);


			CVisitorDart visitor;
			board.Accept(&visitor);

			std::vector<std::vector<double>> locs = visitor.GetLocations();
			
			Assert::IsTrue(locs.size() == 2);

			for (auto loc : locs)
			{
				Assert::IsTrue(loc[0] == 100);
				Assert::IsTrue(loc[1] == 100);
			}

		}

	};
}
#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab_10_1_B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Lab101BTests
{
	TEST_CLASS(CountVidminnoTest)
	{
	public:
		TEST_METHOD(CountsOnlyAllFives)
		{
			StudentB s[2]{};
			s[0].specialnist = KN; s[0].physics = 5; s[0].math = 5; s[0].third.programming = 5;
			s[1].specialnist = KN; s[1].physics = 5; s[1].math = 4; s[1].third.programming = 5;

			Assert::AreEqual(1, CountVidminno(s, 2));
		}
	};
}
#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab_10_1_A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab101ATests
{
	TEST_CLASS(Lab101ATests)
	{
	public:

		TEST_METHOD(TestPercentPhysic5)
		{
			const int N = 4;
			Student students[N] =
			{
				{ "Коваленко", 1, RI, 5, 5, 5 },
				{ "Шевченко",  2, IK, 4, 5, 4 },
				{ "Бондар",    1, PZ, 5, 3, 4 },
				{ "Ткаченко",  3, RI, 3, 4, 5 }
			};

			double actual = PercentPhysic_5(students, N);
			double expected = 50.0;

			Assert::AreEqual(expected, actual, 0.0001);
		}
	};
}
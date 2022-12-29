#include "pch.h"
#include "CppUnitTest.h"
#include "../lab3_3sem/lab3_3sem.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Graph gr(5);
			gr.set_an_element(0, 0, 0);
			gr.set_an_element(0, 1, 1);
			gr.set_an_element(0, 2, 0);
			gr.set_an_element(0, 3, 0);
			gr.set_an_element(0, 4, 0);

			gr.set_an_element(1, 0, 0);
			gr.set_an_element(1, 1, 0);
			gr.set_an_element(1, 2, 0);
			gr.set_an_element(1, 3, 6);
			gr.set_an_element(1, 4, 0);

			gr.set_an_element(2, 0, 0);
			gr.set_an_element(2, 1, 0);
			gr.set_an_element(2, 2, 0);
			gr.set_an_element(2, 3, 7);
			gr.set_an_element(2, 4, 0);

			gr.set_an_element(3, 0, 0);
			gr.set_an_element(3, 1, 0);
			gr.set_an_element(3, 2, 0);
			gr.set_an_element(3, 3, 0);
			gr.set_an_element(3, 4, 5);

			gr.set_an_element(4, 0, 0);
			gr.set_an_element(4, 1, 0);
			gr.set_an_element(4, 2, 0);
			gr.set_an_element(4, 3, 0);
			gr.set_an_element(4, 4, 0);

			gr.dijkstra_algorithm(0);

			int elem_expected = 5;
			int elem_actual = 0;
			int arr[5] = { 0,1,INT32_MAX,7,12 };
			for (int i = 0; i < 5; i++)
				if (arr[i] == gr.shortest_distances[i])
					++elem_actual;
			Assert::AreEqual(elem_expected, elem_actual);
		}

		TEST_METHOD(TestMethod2)
		{
			Graph gr(5);
			gr.set_an_element(0, 0, 0);
			gr.set_an_element(0, 1, 1);
			gr.set_an_element(0, 2, 0);
			gr.set_an_element(0, 3, 0);
			gr.set_an_element(0, 4, 0);

			gr.set_an_element(1, 0, 0);
			gr.set_an_element(1, 1, 0);
			gr.set_an_element(1, 2, 0);
			gr.set_an_element(1, 3, 6);
			gr.set_an_element(1, 4, 0);

			gr.set_an_element(2, 0, 0);
			gr.set_an_element(2, 1, 0);
			gr.set_an_element(2, 2, 0);
			gr.set_an_element(2, 3, 7);
			gr.set_an_element(2, 4, 0);

			gr.set_an_element(3, 0, 0);
			gr.set_an_element(3, 1, 0);
			gr.set_an_element(3, 2, 0);
			gr.set_an_element(3, 3, 0);
			gr.set_an_element(3, 4, 5);

			gr.set_an_element(4, 0, 0);
			gr.set_an_element(4, 1, 0);
			gr.set_an_element(4, 2, 0);
			gr.set_an_element(4, 3, 0);
			gr.set_an_element(4, 4, 0);

			gr.bellman_ford_algorithm(0);

			int elem_expected = 5;
			int elem_actual = 0;
			int arr[5] = { 0,1,INT32_MAX,7,12 };
			for (int i = 0; i < 5; i++)
				if (arr[i] == gr.shortest_distances[i])
					++elem_actual;
			Assert::AreEqual(elem_expected, elem_actual);
		}

		TEST_METHOD(TestMethod3)
		{
			Graph gr(5);
			gr.set_an_element(0, 0, 0);
			gr.set_an_element(0, 1, 1);
			gr.set_an_element(0, 2, 0);
			gr.set_an_element(0, 3, 0);
			gr.set_an_element(0, 4, 0);

			gr.set_an_element(1, 0, 0);
			gr.set_an_element(1, 1, 0);
			gr.set_an_element(1, 2, 0);
			gr.set_an_element(1, 3, 6);
			gr.set_an_element(1, 4, 0);

			gr.set_an_element(2, 0, 0);
			gr.set_an_element(2, 1, 0);
			gr.set_an_element(2, 2, 0);
			gr.set_an_element(2, 3, 7);
			gr.set_an_element(2, 4, 0);

			gr.set_an_element(3, 0, 0);
			gr.set_an_element(3, 1, 0);
			gr.set_an_element(3, 2, 0);
			gr.set_an_element(3, 3, 0);
			gr.set_an_element(3, 4, 5);

			gr.set_an_element(4, 0, 0);
			gr.set_an_element(4, 1, 0);
			gr.set_an_element(4, 2, 0);
			gr.set_an_element(4, 3, 0);
			gr.set_an_element(4, 4, 0);

			gr.floyd_warshall_algorithm(0);

			int elem_expected = 5;
			int elem_actual = 0;
			int arr[5] = { 0,1,INT32_MAX,7,12 };
			for (int i = 0; i < 5; i++)
				if (arr[i] == gr.shortest_distances[i])
					++elem_actual;
			Assert::AreEqual(elem_expected, elem_actual);
		}
	};
}

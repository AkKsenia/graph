#include "pch.h"
#include "CppUnitTest.h"
#include "../new_task/new_task.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Matrix matrix(5, 4);
			for (int i = 0; i < matrix.number_of_cells_vertically; i++)
				for (int j = 0; j < matrix.number_of_cells_horizontally; j++) {
					matrix.data[i][j] = 0;
					matrix.visited[i][j] = false;
				}

			matrix.data[1][1] = -1;
			matrix.data[1][2] = 2;
			matrix.data[1][3] = 1;
			matrix.data[2][3] = 1;
			matrix.data[3][3] = 1;
			matrix.data[4][3] = 1;

			matrix.origin_coordinate_i = 1;
			matrix.origin_coordinate_j = 1;
			matrix.end_coordinate_i = 1;
			matrix.end_coordinate_j = 2;

			int elem_expected = 1;
			int elem_actual = matrix.processing();
			Assert::AreEqual(elem_expected, elem_actual);
		}

		TEST_METHOD(TestMethod2)
		{
			Matrix matrix(5, 4);
			for (int i = 0; i < matrix.number_of_cells_vertically; i++)
				for (int j = 0; j < matrix.number_of_cells_horizontally; j++) {
					matrix.data[i][j] = 0;
					matrix.visited[i][j] = false;
				}

			matrix.data[4][2] = -1;
			matrix.data[1][2] = 2;
			matrix.data[1][3] = 1;
			matrix.data[2][3] = 1;
			matrix.data[3][3] = 1;
			matrix.data[4][3] = 1;

			matrix.origin_coordinate_i = 4;
			matrix.origin_coordinate_j = 2;
			matrix.end_coordinate_i = 1;
			matrix.end_coordinate_j = 2;

			int elem_expected = 3;
			int elem_actual = matrix.processing();
			Assert::AreEqual(elem_expected, elem_actual);
		}

		TEST_METHOD(TestMethod3)
		{
			Matrix matrix(5, 4);
			for (int i = 0; i < matrix.number_of_cells_vertically; i++)
				for (int j = 0; j < matrix.number_of_cells_horizontally; j++) {
					matrix.data[i][j] = 0;
					matrix.visited[i][j] = false;
				}

			matrix.data[1][1] = -1;
			matrix.data[0][3] = 2;
			matrix.data[0][2] = 1;
			matrix.data[1][3] = 1;

			matrix.origin_coordinate_i = 1;
			matrix.origin_coordinate_j = 1;
			matrix.end_coordinate_i = 0;
			matrix.end_coordinate_j = 3;

			int elem_expected = -1;
			int elem_actual = matrix.processing();
			Assert::AreEqual(elem_expected, elem_actual);
		}
	};
}

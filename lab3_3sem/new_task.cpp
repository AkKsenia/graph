#include <iostream>
using namespace std;

//Задача: дана матрица, в которой 0 обозначает пустую клетку, по которой возможно движение, -1 - начальное положение, 1 - препятствие, 2 - конец маршрута. 
//Необходимо найти кратчайший путь от начальной клетки до конечной

class Matrix {
private:
	int** data;
	int number_of_cells_horizontally;
	int number_of_cells_vertically;
	int origin_coordinate_i;
	int origin_coordinate_j;
	int end_coordinate_i;
	int end_coordinate_j;
	bool** visited;
public:
	Matrix(int amount_v, int amount_h) {
		number_of_cells_horizontally = amount_h;
		number_of_cells_vertically = amount_v;

		data = new int* [number_of_cells_vertically];
		visited = new bool* [number_of_cells_vertically];

		for (int i = 0; i < number_of_cells_vertically; i++) {
			data[i] = new int[number_of_cells_horizontally];
			visited[i] = new bool[number_of_cells_horizontally];
		}

		origin_coordinate_i = 0;
		origin_coordinate_j = 0;
		end_coordinate_i = number_of_cells_vertically - 1;
		end_coordinate_j = number_of_cells_horizontally - 1;
	}
	~Matrix() {
		for (int i = 0; i < number_of_cells_vertically; i++) {
			delete[] data[i];
			delete[] visited[i];
		}
		delete[] data;
		delete[] visited;
	}

	void fill_the_matrix() {
		for (int i = 0; i < number_of_cells_vertically; i++)
			for (int j = 0; j < number_of_cells_horizontally; j++) {
				data[i][j] = 0;
				visited[i][j] = false;
			}

		int coordinate_i = -1, coordinate_j = -1;
		while (coordinate_i < 0 || coordinate_i >= number_of_cells_vertically || coordinate_j < 0 || coordinate_j >= number_of_cells_horizontally) {
			cout << "Введите координату начала: ";
			cin >> coordinate_i >> coordinate_j;
			if (coordinate_i >= 0 && coordinate_i < number_of_cells_vertically && coordinate_j >= 0 && coordinate_j < number_of_cells_horizontally) {
				data[coordinate_i][coordinate_j] = -1;
				origin_coordinate_i = coordinate_i;
				origin_coordinate_j = coordinate_j;
			}
			else cout << "Формат ввода не соответствует требованиям. Осуществите ввод заново!" << endl;
		}

		coordinate_i = -1;
		coordinate_j = -1;
		while (coordinate_i < 0 || coordinate_i >= number_of_cells_vertically || coordinate_j < 0 || coordinate_j >= number_of_cells_horizontally) {
			cout << "Введите координату конца: ";
			cin >> coordinate_i >> coordinate_j;
			if (coordinate_i >= 0 && coordinate_i < number_of_cells_vertically && coordinate_j >= 0 && coordinate_j < number_of_cells_horizontally) {
				if (data[coordinate_i][coordinate_j] == 0) {
					data[coordinate_i][coordinate_j] = 2;
					end_coordinate_i = coordinate_i;
					end_coordinate_j = coordinate_j;
				}
				else {
					cout << "Формат ввода не соответствует требованиям. Осуществите ввод заново!" << endl;
					coordinate_i = -1;
				}
			}
			else cout << "Формат ввода не соответствует требованиям. Осуществите ввод заново!" << endl;
		}

		cout << "Введите количество препятствий: ";
		int amount;
		cin >> amount;

		coordinate_i = -1;
		coordinate_j = -1;
		while (coordinate_i < 0 || coordinate_i >= number_of_cells_vertically || coordinate_j < 0 || coordinate_j >= number_of_cells_horizontally) {
			while (amount != 0) {
				cout << "Введите координату препятствия: ";
				cin >> coordinate_i >> coordinate_j;
				if (coordinate_i >= 0 && coordinate_i < number_of_cells_vertically && coordinate_j >= 0 && coordinate_j < number_of_cells_horizontally) {
					if (data[coordinate_i][coordinate_j] == 0) {
						data[coordinate_i][coordinate_j] = 1;
						--amount;
					}
					else {
						cout << "Формат ввода не соответствует требованиям. Осуществите ввод заново!" << endl;
						coordinate_i = -1;
					}
				}
				else cout << "Формат ввода не соответствует требованиям. Осуществите ввод заново!" << endl;
			}
		}
	}
	void transform() {
		for (int i = 0; i < number_of_cells_vertically; i++)
			for (int j = 0; j < number_of_cells_horizontally; j++) {
				if (data[i][j] == 1)
					data[i][j] = -2;
				if (data[i][j] == 2)
					data[i][j] = -3;
			}
	}

	void counting_paths(int i_, int j_) {
		if (i_ - 1 >= 0 && i_ - 1 < number_of_cells_vertically && j_ >= 0 && j_ < number_of_cells_horizontally)
			if ((data[i_ - 1][j_] > data[i_][j_] + 1) || (data[i_ - 1][j_] == 0 && !visited[i_ - 1][j_])) {
				data[i_ - 1][j_] = data[i_][j_] + 1;
				if (data[i_ - 1][j_] == 0)
					visited[i_ - 1][j_] = true;
				counting_paths(i_ - 1, j_);
			}

		if (i_ >= 0 && i_ < number_of_cells_vertically && j_ + 1 >= 0 && j_ + 1 < number_of_cells_horizontally)
			if ((data[i_][j_ + 1] > data[i_][j_] + 1) || (data[i_][j_ + 1] == 0 && !visited[i_][j_ + 1])) {
				data[i_][j_ + 1] = data[i_][j_] + 1;
				if (data[i_][j_ + 1] == 0)
					visited[i_][j_ + 1] = true;
				counting_paths(i_, j_ + 1);
			}

		if (i_ + 1 >= 0 && i_ + 1 < number_of_cells_vertically && j_ >= 0 && j_ < number_of_cells_horizontally)
			if ((data[i_ + 1][j_] > data[i_][j_] + 1) || (data[i_ + 1][j_] == 0 && !visited[i_ + 1][j_])) {
				data[i_ + 1][j_] = data[i_][j_] + 1;
				if (data[i_ + 1][j_] == 0)
					visited[i_ + 1][j_] = true;
				counting_paths(i_ + 1, j_);
			}

		if (i_ >= 0 && i_ < number_of_cells_vertically && j_ - 1 >= 0 && j_ - 1 < number_of_cells_horizontally)
			if ((data[i_][j_ - 1] > data[i_][j_] + 1) || (data[i_][j_ - 1] == 0 && !visited[i_][j_ - 1])) {
				data[i_][j_ - 1] = data[i_][j_] + 1;
				if (data[i_][j_ - 1] == 0)
					visited[i_][j_ - 1] = true;
				counting_paths(i_, j_ - 1);
			}
	}
	void processing() {
		transform();
		counting_paths(origin_coordinate_i, origin_coordinate_j);

		int number[4] = { -2,-2,-2,-2 };
		int i_ = end_coordinate_i, j_ = end_coordinate_j;

		if (i_ - 1 >= 0 && i_ - 1 < number_of_cells_vertically && j_ >= 0 && j_ < number_of_cells_horizontally)
			number[0] = data[i_ - 1][j_];
		if (i_ >= 0 && i_ < number_of_cells_vertically && j_ + 1 >= 0 && j_ + 1 < number_of_cells_horizontally)
			number[1] = data[i_][j_ + 1];
		if (i_ + 1 >= 0 && i_ + 1 < number_of_cells_vertically && j_ >= 0 && j_ < number_of_cells_horizontally)
			number[2] = data[i_ + 1][j_];
		if (i_ >= 0 && i_ < number_of_cells_vertically && j_ - 1 >= 0 && j_ - 1 < number_of_cells_horizontally)
			number[3] = data[i_][j_ - 1];

		int key = 0, min = INT32_MAX, key_1 = 0;

		for (int i = 0; i < 4; i++) {
			if (number[i] > 0)
				++key;
			if (number[i] == -1)
				++key_1;
		}

		if (key_1 == 1) {
			cout << "Кратчайшее расстояние равно: " << key_1 << endl;
		}
		else {
			if (key > 0) {
				for (int i = 0; i < 4; i++)
					if (number[i] > 0 && number[i] < min)
						min = number[i];
				cout << "Кратчайшее расстояние равно: " << min + 2 << endl;
			}
			else {
				cout << "Невозможно проложить маршрут от начальной координаты до конечной!" << endl;
			}
		}
	}
};

int main() {
	setlocale(LC_ALL, "Russian");

	int number_of_cells_horizontally, number_of_cells_vertically;

	cout << "Укажите размер матрицы по вертикали: ";
	cin >> number_of_cells_vertically;
	cout << "Укажите размер матрицы по горизонтали: ";
	cin >> number_of_cells_horizontally;

	Matrix matrix(number_of_cells_vertically, number_of_cells_horizontally);
	matrix.fill_the_matrix();

	matrix.processing();

	return 0;
}
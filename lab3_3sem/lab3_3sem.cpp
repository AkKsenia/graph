#include <iostream>
#include <stack>
using namespace std;

template<class T>
class Graph {
public:
	int number_of_vertices;
	T** data;
	int* shortest_distances;
	bool* state;
public:
	Graph(int amount_) {
		this->number_of_vertices = amount_;

		data = new T * [amount_];
		shortest_distances = new int[amount_];
		state = new bool[amount_];

		for (int i = 0; i < amount_; i++) {
			data[i] = new T[amount_];
			shortest_distances[i] = INT32_MAX;
			state[i] = false;
		}
	}
	Graph(const Graph<T>& other) {
		number_of_vertices = other.number_of_vertices;
		for (int i = 0; i < number_of_vertices; i++) {
			for (int j = 0; j < number_of_vertices; j++)
				data[i][j] = other.data[i][j];
			shortest_distances[i] = other.shortest_distances[i];
			state[i] = other.state[i];
		}
	}
	~Graph() {
		for (int i = 0; i < number_of_vertices; i++)
			delete[] data[i];
		delete[] data;
		delete[] shortest_distances;
		delete[] state;
	}

	void fill_the_graph() {
		T data_;
		for (int i = 0; i < number_of_vertices; i++) {
			for (int j = 0; j < number_of_vertices; j++) {
				cout << "Задайте длину пути между вершинами " << i << " и " << j << ": ";
				cin >> data_;
				data[i][j] = data_;
			}
		}
	}
	void set_an_element(int beginning, int ending, int length) {
		data[beginning][ending] = length;
	}

	//Алгоритм Дейкстры
	int finding_minimum_distance() {
		int minimum = INT32_MAX, index = 0;
		for (int i = 0; i < number_of_vertices; i++)
			if (!state[i] && shortest_distances[i] <= minimum) {
				minimum = shortest_distances[i];
				index = i;
			}
		return index;
	}
	void dijkstra_algorithm(int index_of_source_node) {
		for (int i = 0; i < number_of_vertices; i++) {
			shortest_distances[i] = INT32_MAX;
			state[i] = false;
		}

		shortest_distances[index_of_source_node] = 0;
		for (int i = 0; i < number_of_vertices; i++) {
			int index_of_node_with_minimum_distance = finding_minimum_distance();
			state[index_of_node_with_minimum_distance] = true;
			for (int j = 0; j < number_of_vertices; j++)
				if (!state[j] && data[index_of_node_with_minimum_distance][j] && shortest_distances[index_of_node_with_minimum_distance] != INT32_MAX && shortest_distances[index_of_node_with_minimum_distance] + data[index_of_node_with_minimum_distance][j] < shortest_distances[j])
					shortest_distances[j] = shortest_distances[index_of_node_with_minimum_distance] + data[index_of_node_with_minimum_distance][j];
		}
	}

	//Алгоритм Беллмана Форда
	void bellman_ford_algorithm(int index_of_source_node) {
		for (int i = 0; i < number_of_vertices; i++) {
			shortest_distances[i] = INT32_MAX;
			state[i] = false;
		}

		shortest_distances[index_of_source_node] = 0;
		for (int i = 1; i <= number_of_vertices - 1; i++)
			for (int j = 0; j < number_of_vertices; j++)
				for (int k = 0; k < number_of_vertices; k++)
					if (data[j][k] && shortest_distances[j] != INT32_MAX && shortest_distances[j] + data[j][k] < shortest_distances[k])
						shortest_distances[k] = shortest_distances[j] + data[j][k];
		//проверка на отсутствие циклов с отрицательным весом
		for (int j = 0; j < number_of_vertices; j++)
			for (int k = 0; k < number_of_vertices; k++)
				if (data[j][k] && shortest_distances[j] != INT32_MAX && shortest_distances[j] + data[j][k] < shortest_distances[k]) {
					cout << "Граф содержит цикл с отрицательным весом" << endl;
					return;
				}
	}

	//Топологическая сортировка
	void all_the_way(const T& vertex, stack<T>& stack) {
		state[vertex] = true;
		for (int i = 0; i < number_of_vertices; i++)
			if (data[vertex][i] != 0)
				if (!state[i]) {
					all_the_way(i, stack);
					stack.push(i);
				}
	}
	void topological_sort() {
		for (int i = 0; i < number_of_vertices; i++)
			state[i] = false;

		stack<T> stack;
		for (int i = 0; i < number_of_vertices; i++)
			if (!state[i]) {
				all_the_way(i, stack);
				stack.push(i);
			}
		while (!stack.empty()) {
			cout << stack.top() << ' ';
			stack.pop();
		}
	}

	//Алгоритм Флойда-Уоршелла
	void floyd_warshall_algorithm(int index_of_source_node) {
		for (int i = 0; i < number_of_vertices; i++)
			shortest_distances[i] = INT32_MAX;

		T** data_ = new T * [number_of_vertices];
		for (int i = 0; i < number_of_vertices; i++)
			data_[i] = new T[number_of_vertices];

		for (int i = 0; i < number_of_vertices; i++)
			for (int j = 0; j < number_of_vertices; j++) {
				data_[i][j] = data[i][j];
				if (i != j && data[i][j] == 0)
					data_[i][j] = INT32_MAX;
			}

		for (int i = 0; i < number_of_vertices; i++)
			for (int j = 0; j < number_of_vertices; j++)
				for (int k = 0; k < number_of_vertices; k++)
					if (data_[j][k] > data_[j][i] + data_[i][k] && data_[i][k] != INT32_MAX && data_[j][i] != INT32_MAX)
						data_[j][k] = data_[j][i] + data_[i][k];

		for (int i = 0; i < number_of_vertices; i++)
			shortest_distances[i] = data_[index_of_source_node][i];

		for (int i = 0; i < number_of_vertices; i++)
			delete[] data_[i];
		delete[] data_;
	}

	//Поиск кратчайшего пути
	void finding_the_shortest_path() {
		try {
			int index_of_source_node;
			cout << "Введите номер исходного узла: ";
			cin >> index_of_source_node;
			if ((index_of_source_node < 0) || (index_of_source_node >= number_of_vertices))
				throw(-1);
			floyd_warshall_algorithm(index_of_source_node);
			cout << endl;
			for (int i = 0; i < number_of_vertices; i++) {
				if (shortest_distances[i] != INT32_MAX)
					cout << "Кратчайший путь от узла с номером " << index_of_source_node << " до узла с номером " << i << " равен: " << shortest_distances[i] << endl;
				else cout << "Кратчайший путь от узла с номером " << index_of_source_node << " до узла с номером " << i << " равен: " << "INF" << endl;
			}
		}
		catch (int index) {
			cout << endl;
			cout << "Узлов с такими номерами не существует. Операцию поиска кратчайшего пути произвести невозможно!" << endl;
			cout << "Работа функции завершилась с кодом " << index << endl;
		}
	}
};

int main() {
	setlocale(LC_ALL, "Russian");

	return 0;
}
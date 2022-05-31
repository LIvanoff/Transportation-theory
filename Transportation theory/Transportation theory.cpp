#include "pch.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>


using namespace std;


class Matrix
{
private:
	int size_row;
	int size_column;
	int potential_i;
	int potential_j;
	int func;
	bool way = false;
	char symbol = '-';
	vector <int> min_vec;
	int minimal_element;
	vector <vector <int>> matrix;
	vector <vector <int>> price_matrix = { {4, 8, 1, 6},
										   {3, 5, 3, 4},
										   {2, 6, 4, 3}, 
										   {1, 4, 5, 3} };
	vector <vector <int>> free_matrix = { {0, 0, 0, 0},
										   {0, 0, 0, 0},
										   {0, 0, 0, 0},
										   {0, 0, 0, 0} };
	vector <vector <char>> matrix_plus_minus = { {'0', '0', '0', '0'},
												{'0', '0', '0','0'},
												{'0', '0', '0', '0'},
												{'0', '0', '0', '0'} };

public:

	Matrix(int size_row, int size_column)
	{
		this->size_row = size_row;
		this->size_column = size_column;
	}

	/*
	int mininmumCost2()
	{
		int transport_cost = 0;

		for (int point = 1; point < 15; point++) {

			for (int i = 1; i < this->size_row; i++) {
				for (int j = 1; j < this->size_column; j++) {

					if (this->matrix[i][j] == point) {

						int different = this->matrix[i][0] - this->matrix[0][j];

						if (different > 0) {
							transport_cost += this->matrix[0][j] * this->matrix[i][j];
							this->matrix[i][0] -= this->matrix[0][j];
							this->matrix[0][j] = 0;
						}
						else if (different < 0) {
							transport_cost += this->matrix[i][0] * this->matrix[i][j];
							this->matrix[0][j] -= this->matrix[i][0];
							this->matrix[i][0] = 0;
						}
						else {
							transport_cost += this->matrix[i][0] * this->matrix[i][j];
							this->matrix[i][0] = 0;
							this->matrix[0][j] = 0;
						}
					}
				}
			}
		}
		return transport_cost;
	}
	*/

	int mininmumCost()
	{
		vector <int> resources = { 70, 80, 90, 80 };
		vector <int> consumers = { 60, 40, 120, 100 };
		while(IsItEmpty(resources) || IsItEmpty(consumers))
		{
			for(int point = 1; point < 6; point++)
			{
				for (int i = 0; i < size_row; i++)
				{
					for (int j = 0; j < size_column; j++)
					{
						if(price_matrix[i][j] == point)
						{
							if (resources.at(i) < consumers.at(j) && resources.at(i) != 0 && consumers.at(j) !=0)
							{
								matrix[i][j] += resources[i];
								consumers[j] -= resources[i];
								resources[i] -= resources[i];
							}
							else if (resources.at(i) == consumers.at(j) && resources.at(i) != 0 && consumers.at(j) != 0)
							{
								matrix[i][j] = consumers[j];
								resources[i] -= consumers[j];
								consumers.erase(consumers.begin() + i);
							}
							else if(resources.at(i) > consumers.at(j) && resources.at(i) != 0 && consumers.at(j) != 0)
							{
								matrix[i][j] += resources.at(i) - (resources.at(i) - consumers.at(j));
								resources[i] -= consumers[j];
								consumers[j] -= consumers[j];
							}
						}
					}
				}
			}
		}

		return 0;
	}

	bool IsItEmpty(vector<int> &vec)
	{
		for (auto c : vec)
		{
			if (c > 0)
			{
				return 1;
			}
		}
		return 0;
	}

	/*
	int northwestCorner1()
	{
		int transport_cost = 0;

		for (int i = 1; i < this->size_row; i++) {
			for (int j = 1; j < this->size_column; j++) {

				if ((this->matrix[i][0] != 0) && (this->matrix[0][j] != 0)) {

					int different = this->matrix[i][0] - this->matrix[0][j];

					if (different > 0) {
						transport_cost += this->matrix[0][j] * this->matrix[i][j];
						this->matrix[i][0] -= this->matrix[0][j];
						this->matrix[0][j] = 0;
					}
					else if (different < 0) {
						transport_cost += this->matrix[i][0] * this->matrix[i][j];
						this->matrix[0][j] -= this->matrix[i][0];
						this->matrix[i][0] = 0;
					}
					else {
						transport_cost += this->matrix[i][0] * this->matrix[i][j];
						this->matrix[i][0] = 0;
						this->matrix[0][j] = 0;
					}
				}
			}
		}
		return transport_cost;
	}
	*/

	void northwestCorner()
	{
		vector <int> resources = {70, 80, 90, 80};
		vector <int> consumers = {60, 40, 120, 100 };
		
		for (int i = 0; i < this->size_row; i++) 
		{
			for (int j = 0; j < this->size_column; j++) 
			{
				if (resources.at(i) < consumers.at(j) && resources.at(i) != 0 && consumers.at(j) != 0)
				{
					matrix[i][j] += resources[i];
					consumers[j] -= resources[i];
					resources[i] -= resources[i];
				}
				else if (resources.at(i) == consumers.at(j) && resources.at(i) != 0 && consumers.at(j) != 0)
				{
					matrix[i][j] = consumers[j];
					resources[i] -= consumers[j];
					consumers.erase(consumers.begin() + i);
				}
				else if (resources.at(i) > consumers.at(j) && resources.at(i) != 0 && consumers.at(j) != 0)
				{
					matrix[i][j] += resources.at(i) - (resources.at(i) - consumers.at(j));
					resources[i] -= consumers[j];
					consumers[j] -= consumers[j];
				}
			}
		}
	}
	

	void fillMatrix(vector <int> matrix)
	{
		int z = 0;
		for (int i = 0; i < this->size_row; i++) {
			vector <int> tmp_vec;
			for (int j = 0; j < this->size_column; j++) {
				tmp_vec.push_back(matrix[z++]);
			}
			this->matrix.push_back(tmp_vec);
		}
	}

	void printMatrix()
	{
		for (int i = 0; i < size_row; i++) {
			for (int j = 0; j < size_column; j++) {
				cout << right << setw(4) << this->matrix[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}
	void printPriceMatrix()
	{
		for (int i = 0; i < size_row; i++) {
			for (int j = 0; j < size_column; j++) {
				cout << right << setw(4) << this->price_matrix[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}

	bool potentials() // метод потенциалов
	{
		vector <bool> boolU = { true, false, false, false };
		vector <bool> boolV = { false, false, false, false };
		vector <int> u_vec = { 0, 0, 0, 0 };
		vector <int> v_vec = { 0, 0, 0, 0 };

		while (IsItTrue(boolU) || IsItTrue(boolV))
		{
			for (int i = 0; i < size_row; i++)
			{
				for (int j = 0; j < size_column; j++)
				{
					if(matrix[i][j] != 0)
					{
						if(boolU[i] != false)
						{
							v_vec[j] = price_matrix[i][j] - u_vec[i];
							boolV[j] = true;
						}
						if(boolV[j] != false)
						{
							u_vec[i] = price_matrix[i][j] - v_vec[j];
							boolU[i] = true;
						}
					}
				}
			}
		}
		if(delta(u_vec, v_vec))
		{
			return 1;
		}
		return 0;
	}

	bool delta(vector<int> u_vec, vector<int> v_vec)
	{
		int negative = 0;
		for(int i = 0; i < size_row; i++)
		{
			for( int j = 0; j < size_column; j++)
			{
				if(matrix[i][j] == 0)
				{
					this->free_matrix[i][j] = price_matrix[i][j] - (u_vec[i] + v_vec[j]);
					//нахождение наибольшего отрицательного значения
					if(free_matrix[i][j]<0 && free_matrix[i][j] < negative)
					{
						negative = free_matrix[i][j];
					}
				}
			}
		}
		// проверка существование отрицательных значений
		if(negative<0)
		{
			//vector <int> ::iterator it = min_element(negative_vec.begin(), negative_vec.end());
			for (int i = 0; i < size_row; i++)
			{
				for (int j = 0; j < size_column; j++)
				{
					if(negative == free_matrix[i][j])
					{
						//cout <<setw(10) <<negative<<endl;
						this->potential_i = i;
						this->potential_j = j;
						return 1;
					}
				}
			}
		}
		return 0;
	}

	bool IsItTrue(vector<bool> &bool_vec)
	{
		for(auto c : bool_vec)
		{
			if(c == false)
			{
				return 1;
			}
		}
		return 0;
	}

	void target_func() // подсчёт целевой функции
	{
		this->func = 0;
		for(int i = 0; i <size_row; i++)
		{
			for (int j = 0; j < size_column; j++)
			{
				if(matrix[i][j] != 0)
				{
					this->func += matrix[i][j] * price_matrix[i][j];
				}
			}
		}
		cout << " F = " << this->func<<endl;
	}

	void min_func() // нахождение минимального элемента
	{
		for (int i = 0; i < size_row; i++)
		{
			for (int j = 0; j < size_column; j++)
			{
				if(matrix_plus_minus[i][j] == '-')
				{
					this->min_vec.push_back(matrix[i][j]);
				}
			}
		}
		vector <int> ::iterator it = min_element(min_vec.begin(), min_vec.end());
		minimal_element = *it;
		min_vec.clear();
	}

	// поиск цикла

	void searchLoop(int i, int j)
	{
		//cout << "i = " << i<<endl;
		//cout << "j = " << j << endl;
		matrix_plus_minus[i][j] = '+';
		if ((j != 0) && !way)
		{
			go_left(i, j - 1);
		}
		if ((j != size_column - 1) && !way) 
		{
			go_right(i, j + 1);
		}
		if ((i != 0) && !way) {
			go_up(i - 1, j);
		}
		if ((i != size_row - 1) && !way) 
		{
			go_down(i + 1, j);
		}
		way = false;
		symbol = '-';
	}

	void go_down(int i, int j)
	{
		if ((i == potential_i) && (j == potential_j)) 
		{
			way = true;
		}
		if ((i != this->size_column - 1) && !way) 
		{
			go_down(i + 1, j);
		}
		if ((j != 0) && (matrix[i][j] != 0) && !way) 
		{
			go_left(i, j - 1);
			if (way and matrix[i][j] != '0') 
			{
				matrix_plus_minus[i][j] = symbol;
				if (symbol == '+') { symbol = '-'; }
				else { symbol = '+'; }
			}
		}
		if ((j != this->size_row - 1) && (matrix[i][j] != 0) && !way) 
		{
			go_right(i, j + 1);
			if (way and matrix[i][j] != '0') 
			{
				matrix_plus_minus[i][j] = symbol;
				if (symbol == '+') { symbol = '-'; }
				else { symbol = '+'; }
			}
		}
	}

	void go_up(int i, int j)
	{
		if ((i == potential_i) && (j == potential_j))
		{
			way = true;
		}
		if ((i != 0) && !way) 
		{
			go_up(i - 1, j);
		}
		if ((j != 0) && (matrix[i][j] != 0) && !way) 
		{
			go_left(i, j - 1);
			if (way and matrix[i][j] != '0') 
			{
				matrix_plus_minus[i][j] = symbol;
				if (symbol == '+') { symbol = '-'; }
				else { symbol = '+'; }
			}
		}
		if ((j != this->size_row - 1) && (matrix[i][j] != 0) && !way) 
		{
			go_right(i, j + 1);
			if (way and matrix[i][j] != '0') 
			{
				matrix_plus_minus[i][j] = symbol;
				if (symbol == '+') { symbol = '-'; }
				else { symbol = '+'; }
			}
		}
	}

	void go_right(int i, int j)
	{
		if ((i == potential_i) && (j == potential_j)) 
		{
			way = true;
		}
		if ((j != this->size_row - 1) && !way) 
		{
			go_right(i, j + 1);
		}
		if ((i != 0) && (matrix[i][j] != 0) && !way) 
		{
			go_up(i - 1, j);
			if (way and matrix[i][j] != '0') 
			{
				matrix_plus_minus[i][j] = symbol;
				if (symbol == '+') { symbol = '-'; }
				else { symbol = '+'; }
			}
		}
		if ((i != this->size_row - 1) && (matrix[i][j] != 0) && !way) 
		{
			go_down(i + 1, j);
			if (way and matrix[i][j] != '0') 
			{
				matrix_plus_minus[i][j] = symbol;
				if (symbol == '+') { symbol = '-'; }
				else { symbol = '+'; }
			}
		}
	}

	void go_left(int i, int j)
	{
		if ((i == potential_i) && (j == potential_j)) 
		{
			way = true;
		}
		if ((j != 0) && !way) 
		{
			go_left(i, j - 1);
		}
		if ((i != 0) && (matrix[i][j] != 0) && !way) 
		{
			go_up(i - 1, j);
			if (way and matrix[i][j] != '0') 
			{
				matrix_plus_minus[i][j] = symbol;
				if (symbol == '+') { symbol = '-'; }
				else { symbol = '+'; }
			}
		}
		if ((i != this->size_row - 1) && (matrix[i][j] != 0) && !way) 
		{
			go_down(i + 1, j);
			if (way and matrix[i][j] != '0') 
			{
				matrix_plus_minus[i][j] = symbol;
				if (symbol == '+') { symbol = '-'; }
				else { symbol = '+'; }
			}
		}
	}

	void calculating()
	{
		for (int i = 0; i < size_row; i++) 
		{
			for (int j = 0; j < size_column; j++) 
			{
				if (matrix_plus_minus[i][j] == '-') 
				{
					matrix[i][j] -= minimal_element;
				}
				else if (matrix_plus_minus[i][j] == '+') 
				{
					matrix[i][j] += minimal_element;
				}
			}
		}
		minimal_element = 0;
	}

	void start()
	{
		while (potentials())
		{
			matrix_plus_minus = { {'0', '0', '0', '0'},
									{'0', '0', '0','0'},
									{'0', '0', '0', '0'},
									{'0', '0', '0', '0'} };
			searchLoop(potential_i, potential_j);
			/*
			for (int i = 0; i < size_row; i++)
			{
				for (int j = 0; j < size_column; j++)
				{
					cout << matrix_plus_minus[i][j];
				}
				cout << endl;
			}*/
			min_func();
			calculating();
			printMatrix();
		}
	}
	int getSize_row() { return this->size_row; }

	int getSize_column() { return this->size_column; }

	vector <vector <int>> getMatrix() { return this->matrix; }
		
};


int main()
{
	setlocale(0, "");

	vector <int> transport_data_vector2 = { 0, 20, 10, 15, 75, 40, 1, 7, 2, 5, 30, 3, 8, 4, 1, 50, 6, 3, 5, 3 };
	
	vector <int> value_vec1 = { 60, 10, 0, 0,
								0, 30, 50, 0,
								0, 0, 70, 20,
								0, 0, 0, 80 };
	vector <int> value_vec2 = { 0, 0, 0, 0,
							0, 0, 0, 0,
							0, 0, 0, 0,
							0, 0, 0, 0 };

	Matrix C(4, 4);
	C.fillMatrix(value_vec2);
	cout << "Метод минимальной стоимости>>> " << endl;
	C.printPriceMatrix();
	C.mininmumCost();
	C.printMatrix();
	C.target_func();
	
	Matrix D(4, 4);
	D.fillMatrix(value_vec2);
	cout << "Метод северо-западного угла>>> " << endl;
	D.printPriceMatrix();
	D.northwestCorner();
	D.printMatrix();
	D.target_func();
	cout << "Метод потенциалов>>> " << endl;
	D.start();
	D.target_func();

	/*
	Matrix A(4, 4);
	A.fillMatrix(value_vec1);
	cout << "Метод потенциалов>>> " << endl;
	A.start();
	A.printMatrix();
	
	
	Matrix B(5, 5);
	vector <int> transport_data_vector1 = { 0, 60, 40, 120, 100, 70, 4, 8, 1, 6, 80, 3, 5, 3, 4, 90, 2, 6, 4, 5, 80, 1,4 ,5 ,3 };
	B.fillMatrix(transport_data_vector1);
	cout << "Метод северо-западного угла>>> " << endl;
	cout << "Метод северо-западного угла: " << B.northwestCorner() << endl<<endl;
	*/
}
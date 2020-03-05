#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <ctime>
#include <string>
#include <iomanip>

class Matrix
{
private:
	std::vector<std::vector<double> > m_values;
public:
	explicit Matrix(int dim);
	Matrix(std::initializer_list<std::initializer_list<double> > element);
	Matrix(unsigned dim1, unsigned dim2, double def_value = 0);

	inline std::vector<double>& operator[](unsigned index);
	Matrix operator+(const Matrix& matr);
	Matrix operator-(const Matrix& matr);
	Matrix operator*(const double& number);
	friend Matrix operator*(const double& number, const Matrix& matr);
	Matrix operator*(const Matrix& matr);
	bool operator==(const Matrix& matr);

	void const print(int prec = 0);
	void randfill(int min_random, int max_random);
};


#include "matrix.h"

Matrix::Matrix(int dim)
{
	if (dim <= 0) throw std::invalid_argument("Matrix dimension must be positive");
	m_values = std::vector<std::vector<double> >(dim, std::vector<double>(dim, 0));
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double> > element) : Matrix(element.size(), element.begin()->size(), 0)
{
	unsigned loop1 = 0;
	for (auto row = element.begin(); row != element.end(); row++)
	{
		unsigned loop2 = 0;
		for (auto val = row->begin(); val != row->end(); val++)
		{
			m_values[loop1][loop2] = *val;
			loop2++;
		}
		if (loop2 != m_values[0].size()) throw std::invalid_argument("Error - this is not a matrix (different row size)");
		loop1++;
	}
}

Matrix::Matrix(unsigned rows, unsigned columns, double def_value) //def_value = 0
{
	if (rows <= 0 or columns <= 0) throw std::invalid_argument("Invalid matrix dimensions - must be positive");
	m_values = std::vector<std::vector<double> >(rows, std::vector<double>(columns, def_value));
}

//===== '[]' OPERATOR OVERLOAD =====
inline std::vector<double>& Matrix::operator[](unsigned index)
{
	return m_values[index];
}

//===== '+' OPERATOR OVERLOAD =====
Matrix Matrix::operator+(const Matrix& matr)
{
	Matrix tmp = Matrix(m_values.size(), m_values[0].size());
	for (unsigned i = 0; i < m_values.size(); i++)
	{
		if (m_values[i].size() != matr.m_values.size())
			throw std::invalid_argument("Left matrix column dimension do not equals right matrix row dimension");
		for (unsigned j = 0; j < m_values[i].size(); j++)
		{
			tmp[i][j] = m_values[i][j] + matr.m_values[i][j];
		}
	}
	return tmp;
}
//===== '-' OPERATOR OVERLOAD =====
Matrix Matrix::operator-(const Matrix& matr)
{
	Matrix tmp = Matrix(m_values.size(), m_values[0].size());
	for (unsigned i = 0; i < m_values.size(); i++)
	{
		if (m_values[i].size() != matr.m_values.size())
			throw std::invalid_argument("Left matrix column dimension do not equals right matrix row dimension");
		for (unsigned j = 0; j < m_values[i].size(); j++)
		{
			tmp[i][j] = m_values[i][j] - matr.m_values[i][j];
		}

	}
	return tmp;
}

//===== '*' OPERATOR OVERLOAD (MATRIX * NUMBER) =====
Matrix Matrix::operator*(const double& number)
{
	Matrix tmp = *this;
	
	for (unsigned i = 0; i < tmp.m_values.size(); i++)
	{
		for (unsigned j = 0; j < tmp.m_values[i].size(); j++)
		{
			tmp[i][j] *= number;
		}
	}
	return tmp;
}

//===== '*' OPERATOR OVERLOAD (NUMBER * MATRIX) =====
Matrix operator*(const double& number, const Matrix& matr)
{
	Matrix tmp = matr;

	for (unsigned i = 0; i < tmp.m_values.size(); i++)
	{
		for (unsigned j = 0; j < tmp.m_values[i].size(); j++)
		{
			tmp[i][j] *= number;
		}
	}
	return tmp;
}

//===== '*' OPERATOR OVERLOAD (MATRIX * MATRIX) =====
Matrix Matrix::operator*(const Matrix& matr)
{
	if (m_values.size() != matr.m_values[0].size()) throw std::invalid_argument("You cannot multiply these matrixes");
	Matrix tmp = Matrix(m_values.size(), matr.m_values[0].size(), 0);
	for (unsigned i = 0; i < tmp.m_values.size(); i++)
	{
		for (unsigned j = 0; j < tmp.m_values[0].size(); j++)
		{
			for (unsigned k = 0; k < matr.m_values.size(); k++)
			{
				tmp[i][j] += m_values[i][k] * matr.m_values[k][j];
			}
		}
	}
	return tmp;
}

//===== '==' OPERATOR OVERLOAD =====
bool Matrix::operator==(const Matrix& matr)
{
	if (m_values[0].size() != matr.m_values[0].size()) return false;
	if (m_values.size() != matr.m_values.size()) return false;
	for (unsigned i = 0; i < m_values.size(); i++)
	{
		for (unsigned j = 0; j < m_values[i].size(); j++)
		{
			if (m_values[i][j] != matr.m_values[i][j]) return false;
		}
	}
	return true;
}

//===== PRINT MATRIX WITH GIVEN PRECISION =====
void const Matrix::print(int prec) //default value of prec = 0
{
	std::cout << std::fixed;
	std::cout.precision(prec);
	std::string max_len = std::string();
	for (unsigned i = 0; i < m_values.size(); i++)
	{
		for (unsigned j = 0; j < m_values[i].size(); j++)
		{
			std::string len = std::to_string(m_values[i][j]);
			if (len.size() > max_len.size())
				max_len = len;
		}
	}
	for (unsigned i = 0; i < m_values.size(); i++)
	{
		for (unsigned j = 0; j < m_values[i].size(); j++)
		{
			unsigned buf = max_len.size() - std::to_string(m_values[i][j]).size();
			for (unsigned k = 0; k < buf; k++)
			{
				std::cout << " ";
			}
			std::cout << m_values[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

//===== FILL MATRIX WITH RANDOM NUMBERS WITHIN DEFINED RANGE =====
void Matrix::randfill(int min_random, int max_random)
{
	for (unsigned i = 0; i < m_values.size(); i++)
	{
		for (unsigned j = 0; j < m_values[i].size(); j++)
		{
			m_values[i][j] = fmod(rand(), max_random - min_random) + (min_random);
		}
	}
}


#include "Matrices.h"
#include <iomanip>

namespace Matrices
{
	Matrix::Matrix(int _rows, int _cols)
	{
		rows = _rows;
		cols = _cols;
		a.resize(rows, vector<double>(cols, 0));
		
	}

	///Add each corresponding element.
	///usage: c = a + b;
	Matrix operator+(const Matrix& a, const Matrix& b)
	{
		if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
		{
			throw runtime_error("Error: dimensions must agree");
		}
		//if we get here, the dimenstions match
		Matrix c(a.getRows(), a.getCols());

		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				c(i, j) = a(i, j) + b(i, j);
			}
		}
		return c;
	}

	///Matrix multiply. See description.
	///usage: c = a * b;
	Matrix operator*(const Matrix& a, const Matrix& b)
	{
		
		if (a.getCols() != b.getRows())
		{
			throw runtime_error("Error: dimensions must agree");
		}

		Matrix c(a.getRows(), b.getCols());

		for(int k = 0; k < b.getCols(); k++)
		{
			for (int i = 0; i < a.getRows(); i++)
			{
				for (int j = 0; j < b.getRows(); j++)
				{
					c(i,k) += a(i,j) * b(j,k);
				}
			}
		}
		return c;
	}
	
	///Matrix comparison. See description.
	///usage: a == b
	bool operator==(const Matrix& a, const Matrix& b)
	{
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
		{
			return false;
		}
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getRows(); j++)
			{
				if (abs(a(i, j) - b(i, j)) < 0.001)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	

	///Matrix comparison. See description.
	///usage: a != b
	bool operator!=(const Matrix& a, const Matrix& b)
	{
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
		{
			return true;
		}
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getRows(); j++)
			{
				if ((abs(a(i, j) - b(i, j)) < 0.001))
				{
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}

	///Output matrix.
	///Separate columns by ' ' and rows by '\n'
	ostream& operator<<(ostream& os, const Matrix& a)
	{
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				os << setw(8) << a(i, j) << " ";
			}
			os << '\n';
		}

		return os;
	}

	RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
	{
		a.at(0).at(0) = cos(theta);
		a.at(0).at(1) = -sin(theta);
		a.at(1).at(0) = sin(theta);
		a.at(1).at(1) = cos(theta);
	}

	ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
	{
		a.at(0).at(0) = scale;
		a.at(0).at(1) = 0;
		a.at(1).at(0) = 0;
		a.at(1).at(1) = scale;
	}

	TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix (2, nCols)
	{
		for (int i = 0; i < nCols; i++)
		{
			a.at(0).at(i) = xShift;
			a.at(1).at(i) = yShift;
		}
	}
}

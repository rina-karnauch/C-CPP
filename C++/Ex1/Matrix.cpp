//
// Created by Rina Karnauch on 11/06/2020.
//
#include <iostream>
#include "Matrix.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ostream;
using std::istream;


// FRIENDS WITH BENEFITS
/**
 * a function to print out an error of allocation error
 */
void _allocError()
{
	cerr << ALLOC_ERR << endl;
	exit(EXIT_FAILURE);
}

/**
 * a function to print out an error of matrix size
 */
void _matrixSizeError()
{
	cerr << MATRIX_SIZE_ERR << endl;
	exit(EXIT_FAILURE);
}

/**
 * a function to print out an error of matrix multiplication
 */
void _matrixMulError()
{
	cerr << MATRIX_MUL_ERR << endl;
	exit(EXIT_FAILURE);
}

/**
 * a function to print out an error of out of range index
 */
void _indexOutOfRange()
{
	cerr << INDEX_RANGE_ERR << endl;
	exit(EXIT_FAILURE);
}

/**
 * a function to print out an error of matrix addition
 */
void _matrixAddError()
{
	cerr << MATRIX_ADD_ERR << endl;
	exit(EXIT_FAILURE);
}

/**
 * a function to print out that the file is no good good
 */
void _fileNotGoodError()
{
	cerr << FILE_ERR << endl;
	exit(EXIT_FAILURE);
}

// C'TORS:
/**
 * a non defualtive constructor to Matrix
 * @param rows: rows amount
* @param cols: cols amount
 */
Matrix::Matrix(const int rows, const int cols) : _dim{.rows = rows, .cols = cols}, _mArr(nullptr)
{

	if (rows <= 0 || cols <= 0)
	{
		_matrixSizeError();
	}

	MatrixDims dimension;
	dimension.rows = rows;
	dimension.cols = cols;

	_dim = dimension;

	_mArr = new (std::nothrow) float[(rows) * (cols)]{ZERO};

	if (_mArr == nullptr)
	{
		_allocError();
	}
}

/**
 * a defaultive constructor to Matrix
 * create a 1x1 matrix
 */
Matrix::Matrix() : Matrix(DEF_SIZE_ROWS, DEF_SIZE_COLS)
{};

/**
 * a copy constructor
 * @param m: the matrix we are copying
 */
Matrix::Matrix(const Matrix &m) : _dim{.rows = m._dim.rows, .cols = m._dim.cols}, _mArr(nullptr)
{
	_dim = m._dim;

	int rows = _dim.rows;
	int cols = _dim.cols;

	_mArr = new (std::nothrow) float[(rows) * (cols)]{ZERO};

	if (_mArr == nullptr)
	{
		_allocError();
	}

	for (int i = 0; i < ((rows) * (cols)); i++)
	{
		_mArr[i] = m[i];
	}
}

/**
 * a destructor
 */
Matrix::~Matrix()
{
	delete[] _mArr;
}

// METHODS:
/**
 * a function to get the rows amount
 * @return: int of rows amount
 */
int Matrix::getRows() const
{
	return _dim.rows;
}

/**
 * a function to get the cols amount
 * @return: int of cols amount
 */
int Matrix::getCols() const
{
	return _dim.cols;
}

/**
 * a function to return a vector out of a matrix
 * @return: a matrix of (rows)x(1)
 */
Matrix &Matrix::vectorize()
{
	int rows = _dim.rows;
	int cols = _dim.cols;

	_dim.rows = rows * cols;
	_dim.cols = DEF_SIZE_COLS;

	return *this;
}

/**
 * a function to print out the matrix
 */
void Matrix::plainPrint() const
{
	int rows = _dim.rows;
	int cols = _dim.cols;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (j == cols)
			{
				cout << _mArr[(i * cols) + j];
			}
			else
			{
				cout << _mArr[(i * cols) + j] << " ";
			}
		}
		cout << endl;
	}
}

// OPERATORS:
/**
 * a function to check equality between 2 matrixes
* @param rhs
* @return
*/
bool Matrix::operator==(const Matrix &rhs) const
{
	int thisR = _dim.rows;
	int thisC = _dim.cols;
	int rhsR = rhs.getRows();
	int rhsC = rhs.getCols();

	if (thisR != rhsR || thisC != rhsC)
	{
		return FALSE;
	}

	for (int i = 0; i < rhsR * rhsC; i++)
	{
		if (_mArr[i] != rhs[i])
		{ return FALSE; }
	}
	return TRUE;
}

/**
 * a function to deep copy a matrix to another
 * @param rhs: the matrix we are copying
 * @return: reference to the new matrix we created
 */
Matrix &Matrix::operator=(const Matrix &rhs)
{

	if (this == &rhs)
	{
		return *this;
	}

	delete[] _mArr;

	_dim.rows = rhs.getRows();

	int rows = _dim.rows;
	int cols = _dim.cols;

	_mArr = new(std::nothrow) float[rows * cols];

	if (_mArr == nullptr)
	{
		_allocError();
	}

	for (int i = 0; i < rows * cols; i++)
	{
		_mArr[i] = rhs[i];
	}

	return *this;
}


/**
 * non const access version
 * Brackets indexing
 * @param coord: coordinate we want to change or whatever
 * @return: float value from matrix
 */
float &Matrix::operator[](const int coord)
{
	int rows = this->getCols();
	int cols = this->getRows();

	if (coord < 0 || coord >= rows * cols)
	{
		_indexOutOfRange();
	}
	return _mArr[coord];
}

/**
 * const access version
 * Brackets indexing
 * @param coord: coordinate we want
 * @return: float value from matrix
 */
const float &Matrix::operator[](const int coord) const
{
	int rows = this->getCols();
	int cols = this->getRows();

	if (coord < 0 || coord >= rows * cols)
	{
		_indexOutOfRange();
	}
	return _mArr[coord];
}

/**
 * a function to add a matrix to another one
 * @param rhs: the matrix added
 * @return: we change the original matrix
 */
Matrix &Matrix::operator+=(const Matrix &rhs)
{
	int rows = this->getRows();
	int cols = this->getCols();
	int rowsR = rhs.getRows();
	int colsR = rhs.getCols();

	if (rows != rowsR || cols != colsR)
	{
		_matrixAddError();
	}

	for (int i = 0; i < (rows * cols); i++)
	{
		_mArr[i] = _mArr[i] + rhs[i];
	}

	return *this;
}

/**
 * a function to return the value inside the (a,b) place in the array
 * @param r : row
 * @param c : colm
 * @return: the value
 */
float Matrix::operator()(int r, int c) const
{
	int rows = this->getRows();
	int cols = this->getCols();

	if (r < 0 || r >= rows || c < 0 || c >= cols)
	{
		_indexOutOfRange();
	}

	float value = (this->_mArr)[(r * cols) + c];
	return value;
}

/**
 * a function to get the element at the certain position, changable
 * @param r: poisition of row
 * @param c: poosition of col
 * @return
 */
float &Matrix::operator()(const int r, const int c)
{
	int rows = this->getRows();
	int cols = this->getCols();

	if (r < 0 || r >= rows || c < 0 || c >= cols)
	{
		_indexOutOfRange();
	}

	return (this->_mArr)[(r * cols) + c];
}

/**
 * a function to mul a matrix from the left
 * @param lhs:  the matrix
 * @param c: value of float
 * @return the matrix
 */
Matrix &Matrix::operator*(const float &c)
{
	int rows = this->getRows();
	int cols = this->getCols();

	for (int i = 0; i < (rows * cols); i++)
	{
		_mArr[i] = (_mArr[i] * c);
	}
	return *this;
}

/**
 * a function to make matrix addition
 * @param A: matrix from left
 * @param B: matrix from right
 * @return: return added matrix
 */
Matrix Matrix::operator+(const Matrix &B) const
{
	int rowsA = this->getRows();
	int colsA = this->getCols();
	int rowsB = B.getRows();
	int colsB = B.getCols();

	if (rowsA != rowsB || colsA != colsB)
	{
		_matrixAddError();
	}

	Matrix aAddB = Matrix(*this);
	for (int i = 0; i < (rowsA * colsA); i++)
	{
		aAddB[i] = aAddB[i] + B[i];
	}

	return aAddB;
}

/**
 * a function to multiply two matrices
 * @param B: multiplying matrix
 * @return: a new matrix
 */
Matrix Matrix::operator*(const Matrix &B) const
{
	int aRows = this->getRows();
	int aCols = this->getCols();
	int bRows = B.getRows();
	int bCols = B.getCols();

	if (aCols != bRows)
	{
		_matrixMulError();
	}

	Matrix AB = Matrix(aRows, bCols);
	for (int i = 0; i < aRows; i++)
	{
		for (int j = 0; j < bCols; j++)
		{
			float sum = 0.0;

			for (int k = 0; k < bRows; k++)
			{
				sum = sum + ((_mArr[(i * aCols) + k]) * (B[(k * bCols) + j]));
			}
			AB[(i * bCols) + j] = sum;
		}
	}
	return AB;
}

// FRIENDS

/**
 * a function to mul a matrix from the right
 * @param c: value of float
 * @param rhs: the matrix
 * @return: the matrix but multiplied
 */
Matrix &operator*(const float &c, Matrix &rhs)
{
	int rows = rhs.getRows();
	int cols = rhs.getCols();

	for (int i = 0; i < (rows * cols); i++)
	{
		rhs[i] = (rhs[i] * c);
	}
	return rhs;
}


/**
 * a function to output a matrix
 * @param out: ostream
 * @param m: the matrix
 * @return: the stream
 */
ostream &operator<<(ostream &out, Matrix &m)
{
	int rows = m.getRows();
	int cols = m.getCols();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (m(i, j) <= (0.1f))
			{
				cout << "  ";
			}
			else
			{
				cout << "**";
			}
		}
		cout << endl;
	}
	return out;
}

/**
 * a fucntion to input a matrix
 * @param in: the in stream
 * @param m: the matrix
 * @return: the stream
 */
istream &operator>>(istream &in, Matrix &m)
{
	int rows = m.getRows();
	int cols = m.getCols();


	for (int i = 0; i < (rows * cols); i++)
	{
		in.read((char *) &(m[i]), sizeof(float));
		if (!in.good())
		{
			_fileNotGoodError();
		}
	}
	if (in.peek() != EOF)
	{
		_fileNotGoodError();
	}
	return in;
}
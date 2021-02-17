//
// Matrix H file
//

#ifndef EX1_MATRIX_H
#define EX1_MATRIX_H

// messages
#define ALLOC_ERR "Error:Allocation error"
#define MATRIX_SIZE_ERR "Error:Matrix Size invalid"
#define MATRIX_MUL_ERR "Error:Matrices Sizes do not allow multiplication"
#define MATRIX_ADD_ERR "Error:Matrices Sizes do not allow addition"
#define INDEX_RANGE_ERR "Error:Index out of range"
#define FILE_ERR "Error:File Error- File not good"

// MACROS
#define DEF_SIZE_ROWS 1
#define DEF_SIZE_COLS 1
#define ZERO 0
#define FALSE 0
#define TRUE 1

#include <iostream>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ostream;
using std::istream;

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims
{
	int rows, cols;
} MatrixDims;

/**
 * a class of Matrices
 */
class Matrix
{
private:
	MatrixDims _dim;
	float *_mArr;

	friend class Activation;

	/**
	 * a function to print out an error of allocation error
 	*/
	friend void _allocError();

	/**
	 * a function to print out an error of matrix size
	 */
	friend void _matrixSizeError();

	/**
	 * a function to print out an error of matrix multiplication
	 */
	friend void _matrixMulError();

	/**
	 * a function to print out an error of out of range index
	 */
	friend void _indexOutOfRange();

	/**
	 * a function to print out an error of matrix addition
	 */
	friend void _matrixAddError();

	/**
	 * a function to print out that the file is no good good
	 */
	friend void _fileNotGoodError();

	/**
	 * a function to return the exp sum at the softmax equation
	 * @param m: the matrix
	 * @return the sum
	 */
	friend float _sumSoftMax(const Matrix &m);

	/**
	 * a function to check equality between 2 matrixes
	* @param rhs
	* @return
	*/
	bool operator==(const Matrix &rhs) const;

public:
	// C'TORS:
	/**
	 * a non defualtive constructor to Matrix
	 * @param rows: rows amount
	* @param cols: cols amount
	 */
	Matrix(int rows, int cols);

	/**
	 * a defaultive constructor to Matrix
	 * create a 1x1 matrix
	 */
	Matrix();

	/**
	 * a copy constructor
	 * @param m: the matrix we are copying
	 */
	Matrix(const Matrix &m);

	/**
	 * a destructor
	 */
	~Matrix();

	// METHODS:
	/**
	 * a function to get the rows amount
	 * @return: int of rows amount
	 */
	int getRows() const;

	/**
	 * a function to get the cols amount
	 * @return: int of cols amount
	 */
	int getCols() const;

	/**
	 * a function to return a vector out of a matrix
	 * @return: a matrix of (rows)x(1)
	 */
	Matrix &vectorize();

	/**
	 * a function to print out the matrix
	 */
	void plainPrint() const;

	// OPERATORS:
	/**
	 * a function to deep copy a matrix to another
	 * @param rhs: the matrix we are copying
	 * @return: reference to the new matrix we created
	 */
	Matrix &operator=(const Matrix &rhs);

	/**
	 * non const access version
	 * Brackets indexing
	 * @param coord: coordinate we want to change or whatever
	 * @return: float value from matrix
	 */
	float &operator[](int coord);

	/**
	 * const access version
	 * Brackets indexing
	 * @param coord: coordinate we want
	 * @return: float value from matrix
	 */
	const float &operator[](int coord) const;

	/**
	 * a function to add a matrix to another one
	 * @param rhs: the matrix added
	 * @return: we change the original matrix
	 */
	Matrix &operator+=(const Matrix &rhs);

	/**
	 * a function to return the value inside the (a,b) place in the array
	 * @param r : row
	 * @param c : colm
	 * @return: the value
	 */
	float operator()(int r, int c) const;

	/**
	 * a function to get the element at the certain position, changable
	 * @param r: poisition of row
	 * @param c: poosition of col
	 * @return
	 */
	float &operator()(int r, int c);

	/**
	 * a function to make matrix addition
	 * @param A: matrix from left
	 * @param B: matrix from right
	 * @return: return added matrix
	 */
	Matrix operator+(const Matrix &B) const;

	/**
	 * a function to multiply two matrices
	 * @param B: multiplying matrix
	 * @return: a new matrix
	 */
	Matrix operator*(const Matrix &B) const;

	/**
	 * a function to mul a matrix from the left
	 * @param lhs:  the matrix
	 * @param c: value of float
	 * @return the matrix
	 */
	Matrix &operator*(const float &c);

	/**
	 * a function to mul a matrix from the right
	 * @param c: value of float
	 * @param rhs: the matrix
	 * @return: the matrix but multiplied
	 */
	friend Matrix &operator*(const float &c, Matrix &rhs);


	/*friend Matrix operator*(Matrix &A, Matrix &B);*/

	/**
	 * a function to output a matrix
	 * @param out: ostream
	 * @param m: the matrix
	 * @return: the stream
	 */
	friend ostream &operator<<(ostream &out, Matrix &m);

	/**
	 * a fucntion to input a matrix
	 * @param in: the in stream
	 * @param m: the matrix
	 * @return: the stream
	 */
	friend istream &operator>>(istream &in, Matrix &m);

};

#endif //EX1_MATRIX_H

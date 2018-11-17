#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// Matrix class
class Matrix {
	public:
		// Constructor
		Matrix(int rowsVal, int columnsVal) {
			rows = rowsVal;
			columns = columnsVal;
			initMatrix();
		}

		// Properties
		int rows = 0; // Rows of the matrix
		int columns = 0; // Columns of the matrix
		vector<vector<double>> matrix; // Array for matrix elements
		bool init = false; // Flag to indicate is matrix initialized

		// Methods
	    void initMatrix() { // Function that initializes new matrix dynamically

			if (rows > 0 && columns > 0) {
				if (!init) {
					init = true;
				}
				matrix.resize(rows);
				for (int i = 0; i < rows; i++) {
					matrix[i] = vector<double> (columns);
				}
			} else {
				cout << "Error: Invalid rows or columns value" << endl;
			}
	    }

	    void inputMatrix() { // Function that allows you to input matrix elements from keyboard

			if (init) {
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < columns; j++) {
						cout << "Input element of row " << i + 1 << " and column " << j + 1 << " : ";
						cin >> matrix[i][j];
					}
				}
			} else {
				cout << "Error: matrix should be initialized" << endl;
			}
	    }

	    void outputMatrix() { // Function that outputs the matrix

			if (init) {
				cout << endl;
				for (int i = 0; i < rows; i++) {
				      for (int j = 0; j < columns; j++) {
					      cout << setw(10) << right << matrix[i][j] << " | ";
				      }
				      cout << endl;
				}
				cout << endl;
			} else {
				cout << "Error: matrix should be initialized" << endl;
			}
	    }

	    Matrix getTransposedMatrix() {

	   		Matrix transposedMatrix(columns, rows);
	   		for (int i = 0; i < rows; i++) {
	   			for (int j = 0; j < columns; j++) {
	   				transposedMatrix.matrix[j][i] = matrix[i][j];
	   			}
	   		}

	   		return transposedMatrix;
	    }

	    Matrix multiplyOnMatrix(Matrix matrix1) { // Function that multiplies current matrix on another matrix

	    	int rowsResult = rows, columnsResult = matrix1.columns;

	    	if (columns != matrix1.rows) { // Error: matrices can't be multiplied
				cout << "Error: columns of the 1st matrix and rows of the second matrix should be equal." << endl;
			} else { // Everything is ok
				// Initialize result matrix
				Matrix matrixResult(rowsResult, columnsResult);

				// Matrix multiplication
				for (int i = 0; i < matrixResult.rows; i++) {
					for (int j = 0; j < matrixResult.columns; j++) {
						matrixResult.matrix[i][j] = 0;

						for (int k = 0; k < columns; k++) {
							matrixResult.matrix[i][j] += matrix[i][k] * matrix1.matrix[k][j];
						}
					}
				}

				return matrixResult;
			}
	    }

	    Matrix getInverseMatrix() { // Function that finds an inverse matrix of the current matrix

	    	if (rows != columns) {
	    		cout << "Error: inverse matrix can't be found -> matrix should have a determinant" << endl;
	    	} else {
	    		double determinant = 0, minor = 0;
	    		determinant = getDeterminant();
	    		Matrix inverseMatrix(columns, rows);
	    		Matrix minorMatrix(rows - 1, columns - 1);

	    		for (int i = 0; i < rows; i++) {
	    			for (int j = 0; j < columns; j++) {
	    				minorMatrix = getMinorMatrix(i + 1, j + 1);
	    				minor = minorMatrix.getDeterminant();
	    				if ((i + j) % 2) {
	    					minor *= (-1);
	    				}
	    				inverseMatrix.matrix[j][i] = minor / determinant;
	    			}
	    		}
	    		return inverseMatrix;
	    	}
	    }

	    Matrix getMinorMatrix(int row, int column) { // Function that allows you to get any minor matrix of the current full matrix

	    	if (row > rows || column > columns || row < 1 || column < 1) { // Error: minor matrix can't be found
	    		cout << "Error: minor matrix can't be found" << endl;
	    	} else if (rows != columns) { // Error: minor matrix can't be found
	    		cout << "Error: minor matrix can't be found -> matrix should have a determinant" << endl;
	    	} else { // Everything is ok
	    		Matrix minorMatrix(rows - 1, columns - 1);

	    		int rowsIndex = 0, columnsIndex = 0;

	    		for (int i = 0; i < rows; i++) {
	    			if (i != (row - 1)) {
	    				for (int j = 0; j < columns; j++) {
	    					if (j != (column - 1)) {
	    						minorMatrix.matrix[rowsIndex][columnsIndex] = matrix[i][j];
	    						columnsIndex++;
	    					}
	    				}
	    				rowsIndex++;
	    				columnsIndex = 0;
	    			}
	    		}

	    		return minorMatrix;
	    	}
		}

		int getRank() { // Function that allows you to get the rank of the current matrix

	    	int rowsIndex = 0, columnsIndex = 0;
	    	int currentRow = 0, currentColumn = 0;
	    	int k = 0;
	    	double determinant = 0;

	    	if (rows < columns) {
	    		k = rows;
	    	} else {
	    		k = columns;
	    	}

	    	Matrix minorMatrix(k, k);


	    	while (k > 0) {
		    	// Getting minor matrix
		    	for (int i = currentRow; i < currentRow + k; i++) {
		    		for (int j = currentColumn; j < currentColumn + k; j++) {
		    			minorMatrix.matrix[rowsIndex][columnsIndex] = matrix[i][j];
		    			columnsIndex++;
		    		}
		    		rowsIndex++;
		    		columnsIndex = 0;
		    	}

		    	determinant = minorMatrix.getDeterminant();
		    	rowsIndex = 0;
		    	columnsIndex = 0;

		    	// Determinant > 0 -> rank was found
		    	if (determinant != 0) {
		    		break;
		    	}
		    	// If we found all the minor matrices and all their determinants were 0 -> decrease k
		    	if ((currentRow + k) == rows && (currentColumn + k) == columns) {
		    		currentRow = 0;
		    		currentColumn = 0;
		    		k--;
		    		if (k > 0) { // If k is greater than 0 -> it was not the last iteration
		    			// Manage minor matrix size fields and memory
			    		minorMatrix.rows = k;
			    		minorMatrix.columns = k;
			    		minorMatrix.initMatrix();
		    		}
		    	} else if ((currentColumn + k) == columns) { // If we came to the end of the column -> go to the next row
		    		currentRow++;
		    		currentColumn = 0;
		    	} else {
		    		currentColumn++;
		    	}
		    }

		    return k;
	    }

	    double getDeterminant() { // Function that allows you to get the determinant of the current matrix

	    	int column = 0;
	    	double determinant = 0;

	    	if (rows != columns) {
	    		cout << "Error: determinant can't be found, matrix number of rows and columns should be the same" << endl;
	    		return 0;
	    	}

	    	if (rows == 1 && columns == 1) {
	    		return matrix[0][0];
	    	}

	    	Matrix minorMatrix(rows - 1, columns - 1);

	    	for (int i = 0; i < rows; i++) {
	    		minorMatrix = getMinorMatrix(i + 1, column + 1);
	    		if (i % 2) {
	    			determinant += matrix[i][column] * minorMatrix.getDeterminant() * (-1);
	    		} else {
	    			determinant += matrix[i][column] * minorMatrix.getDeterminant();
	    		}
	    	}

	    	return determinant;
	    }
};

// Main function
int main() {

	// Multiplication
	int rows1 = 0, columns1 = 0, rows2 = 0, columns2 = 0;

    // Input the number of rows and columns of two matrices
    cout << "Rows of the 1st matrix: ";
    cin >> rows1;
    cout << "Columns of the 1st matrix: ";
    cin >> columns1;
    cout << "Rows of the 2nd matrix: ";
    cin >> rows2;
    cout << "Columns of the 2nd matrix: ";
    cin >> columns2;

    // Matrices
    Matrix matrix1(rows1, columns1);
    Matrix matrix2(rows2, columns2);

    // Input matrix values
    cout << endl << "Input the 1st matrix values: " << endl;
    matrix1.inputMatrix();
    cout << endl << "Input the 2nd matrix values: " << endl;
    matrix2.inputMatrix();

    // Test output
    cout << endl << "Matrix 1:" << endl;
    matrix1.outputMatrix();
    cout << endl << "Matrix 2:" << endl;
    matrix2.outputMatrix();

    Matrix matrix3 = matrix1.multiplyOnMatrix(matrix2);
    cout << endl << "Multiplied matrix:" << endl;
    matrix3.outputMatrix();

    // Determinant, rank, inverse matrix
    /*int rows = 0, columns = 0;

    cout << "Rows: ";
    cin >> rows;
    cout << "Columns: ";
    cin >> columns;

    Matrix matrix(rows, columns);
    matrix.inputMatrix();
    matrix.outputMatrix();

    double determinant = matrix.getDeterminant();
    cout << "Determinant: " << determinant << endl;
    int rank = matrix.getRank();
    cout << "Rank: " << rank << endl;
    Matrix inverseMatrix = matrix.getInverseMatrix();
    inverseMatrix.outputMatrix();*/

    return 0;
}

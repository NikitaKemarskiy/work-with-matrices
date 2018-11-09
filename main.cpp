#include <iostream>
#include <iomanip>

using namespace std;

// Matrix class
class Matrix {
	public:
		// Class constructor
		Matrix(int rowsVal, int columnsVal) {
			rows = rowsVal;
			columns = columnsVal;
			initMatrix();
		}

		// Properties
		int rows = 0; // Rows of the matrix
		int columns = 0; // Columns of the matrix
		int** matrix; // Array for matrix elements
		int init = false; // Flag to indicate is matrix initialized

		// Methods
	    void initMatrix() { // Function that initializes new matrix dynamically
	      if (rows > 0 && columns > 0) {
	        if (!init) {
	        	init = true;
	    	} else {
	    		deleteMatrix();
	    	}
	        matrix = new int* [rows];
	        for (int i = 0; i < rows; i++) {
	    	    matrix[i] = new int [columns];
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
	      } else {
	        cout << "Error: matrix should be initialized" << endl;
	      }
	    }

	    void deleteMatrix() { // Function that deletes matrix elements from memory
	    	for (int i = 0; i < rows; i++) {
				delete [] matrix[i];
			}
			delete [] matrix;
	    }

	    void multiplyOnMatrix(Matrix matrix1) {

	    	int rowsResult = rows, columnsResult = matrix1.columns;

	    	if (columns != matrix1.rows) { // Matrices can't be multiplied
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

				// Output result matrix
				cout << endl << "Result matrix:" << endl;
				matrixResult.outputMatrix();
				matrixResult.deleteMatrix();
			}
	    }
};

// Main function
int main() {

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

    matrix1.multiplyOnMatrix(matrix2);

    return 0;
}

#include <iostream>
#include <iomanip>

using namespace std;

// Functions prototypes
void multiplyMatrices(int**, int**, int, int, int, int);
void deleteMatrix(int**, int);

// Matrix class
class Matrix {
	private:
		// Properties
		int init = false; // Flag to indicate is matrix initialized
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

   /* // Multiply the 1st and the 2nd matrices
    multiplyMatrices(matrix1, matrix2, rows1, columns1, rows2, columns2);

    // Delete matrices from memory
    deleteMatrix(matrix1, rows1);
    deleteMatrix(matrix2, rows2);*/

    return 0;
}

// Functions
/*void multiplyMatrices(int** matrix1, int** matrix2, int rows1, int columns1, int rows2, int columns2) { // Function that multiplies matrices
	if (columns1 != rows2) { // Matrices can't be multiplied
		cout << "Error: columns of the 1st matrix and rows of the second matrix should be equal." << endl;
	} else { // Everything is ok
		// Initialize result matrix
		int rowsResult = rows1;
		int columnsResult = columns2;
		int** matrixResult = new int* [rowsResult];

		for (int i = 0; i < rowsResult; i++) {
			matrixResult[i] = new int [columnsResult];
		}

		// Matrix multiplication
		for (int i = 0; i < rowsResult; i++) {
			for (int j = 0; j < columnsResult; j++) {

				matrixResult[i][j] = 0;

				for (int k = 0; k < columns1; k++) {
					matrixResult[i][j] += matrix1[i][k] * matrix2[k][j];
				}
			}
		}

		// Output result matrix
		cout << endl << "Result matrix:" << endl;
		outputMatrix(matrixResult, rowsResult, columnsResult);
		deleteMatrix(matrixResult, rowsResult);
	}
}*/


/*void deleteMatrix(int** matrix, int rows) { // Function that deletes matrix from memory

	for (int i = 0; i < rows; i++) {
		delete [] matrix[i];
	}
	delete [] matrix;
}*/

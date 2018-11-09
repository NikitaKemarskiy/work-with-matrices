#include <iostream>
#include <iomanip>

using namespace std;

void multiplyMatrices(int**, int**, int, int, int, int);
void inputMatrix(int**, int, int);
void outputMatrix(int**, int, int);
void deleteMatrix(int**, int);

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

    // Initialize arrays for matrices
    int** matrix1 = new int* [rows1];
    int** matrix2 = new int* [rows2];

    for (int i = 0; i < rows1; i++) {
    	matrix1[i] = new int [columns1];
    }

    for (int i = 0; i < rows2; i++) {
    	matrix2[i] = new int [columns2];
    }

    // Input matrix values
    cout << endl << "Input the 1st matrix values: " << endl;
    inputMatrix(matrix1, rows1, columns1);
    cout << endl << "Input the 2nd matrix values: " << endl;
    inputMatrix(matrix2, rows2, columns2);


    // Test output
    cout << endl << "Matrix 1:" << endl;
    outputMatrix(matrix1, rows1, columns1);
    cout << endl << "Matrix 2:" << endl;
    outputMatrix(matrix2, rows2, columns2);

    // Multiply the 1st and the 2nd matrices
    multiplyMatrices(matrix1, matrix2, rows1, columns1, rows2, columns2);

    // Delete matrices from memory
    deleteMatrix(matrix1, rows1);
    deleteMatrix(matrix2, rows2);

    return 0;
}

// Functions
void multiplyMatrices(int** matrix1, int** matrix2, int rows1, int columns1, int rows2, int columns2) { // Function that multiplies matrices
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
}

void inputMatrix(int** matrix, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << "Input element of row " << i + 1 << " and column " << j + 1 << " : ";
			cin >> matrix[i][j];
		}
	}
}

void outputMatrix(int** matrix, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << setw(10) << right << matrix[i][j] << " | ";
		}
		cout << endl;
	}
}

void deleteMatrix(int** matrix, int rows) { // Function that deletes matrix from memory

	for (int i = 0; i < rows; i++) {
		delete [] matrix[i];
	}
	delete [] matrix;
}

#include <iostream>
#include <stdlib.h>
#include "Spectral.h"
using namespace std;


int main(){
	//Define a Matrix specifing the number of rows and the number of columns
	Matrix M(4, 4);
	Matrix N(4, 4);
	for (int i = 0; i < M.rowNum; i++) {
		for (int j = 0; j < M.colNum; j++) {
			//Assing values using the square braket notation
			M[i][j] = rand()%10+1;
			N[i][j] = rand()%7+1;
		}
	}
	//Use the method print() to visualize the matrix in the terminal
	//M.print();
	//N.print();
	//Matrices can be summed and multiplied according to rowXcolumn product rule
	{
		Matrix A = M + N;
		Matrix B = M * N;
		B.print();
		//Use the Spectral static method det(Matrix A) to calculate the determinant
		cout << "Det(A) = " << Spectral::det(A) << endl;

		//If det(B) != 0, the matrix can be inverted
		cout << "Det(B) = " << Spectral::det(B) << endl;
		Matrix C = Spectral::inverse(M);
		Spectral::roundMatrix(C * M).print();
	}
	// Spectral::transpose(A) to transpose a matrix
	/*Matrix A(2, 4);
	A[0][0] = 1; A[0][1] = 0; A[0][2] = 0; A[0][3] = 0;
	A[1][0] = 0; A[1][1] = 1; A[1][2] = 0; A[1][3] = 0;*/
	Matrix A(4, 2);
	A[0][0] = 1; A[0][1] = 0;
	A[1][0] = 0; A[1][1] = 1;
	A[2][0] = 0; A[2][1] = 0;
	A[3][0] = 0; A[3][1] = 0;

	Vector V(4);
	V[0] = 1; V[1] = 2; V[2] = 3; V[3] = 4;

	Vector projV = Spectral::inverse(Spectral::transpose(A) * A) * Spectral::transpose(A) * V; //Normal equation
	V.print();
	projV.print();
}

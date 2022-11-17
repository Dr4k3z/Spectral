#ifndef SPECTRAL_H_INCLUDED
#define SPECTRAL_H_INCLUDED

#include <iostream>
#include <vector>
#include "matrix.h"
#include "vector.h"
#include "vectorspace.h"
using namespace std;

class Spectral {
public:
    Spectral();
    //Matrix methods
    static int rank(Matrix M); //DONE
    static Matrix reduce(Matrix M); //DONE
    static Matrix diagonalize(Matrix M); //Not related to eigenvalues DONE
    static Vector pivot(Matrix M); //TODO
    static Vector linsolve(Matrix M, Vector b); //TODO, think about infinite number of solutions
    static float det(Matrix M); //DONE
    static float trace(Matrix M); //DONE
    static Vector eigenValue(Matrix M); //TODO
    static Vector solve(Matrix A, Vector b); //TODO: Solve the linear system Ax=b
    static Matrix inverse(Matrix A); //DONE: Use Gauss-Jordan, not cofactors too expensive
    static Matrix transpose(Matrix A); //DONE
    static void swap(Matrix* A, int a, int b); //DONE, swap row a with row b
    static Matrix roundMatrix(Matrix A);
    //Vector methods
    static Vector cross(Vector v, Vector w); //TODO
    static Vector projection(Vector v, VectorSpace L); //TODO
    //Vectorspace methods
    static bool linearlyIndependent(vector<Vector> span); //Done
    static int dimension(VectorSpace L); //Done
};

#endif // SPECTRAL_H_INCLUDED

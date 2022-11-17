#include "spectral.h"
#include "pch.h"
#include <math.h>
#include <iostream>
using namespace std;

// Credits:
// Algorithm for matrix rank: https://www.geeksforgeeks.org/program-for-rank-of-matrix/

Spectral::Spectral() {}

// Matrix methods

void zeros(vector<float> v) {
    for (unsigned int i = 0; i < v.size(); i++) {
        v[i] = 0;
    }
}

void Spectral::swap(Matrix* M, int a, int b) {
    vector<float> temp = M->data[a];
    M->data[a] = M->data[b];
    M->data[b] = temp;
    M->numSwap++;
}

int Spectral::rank(Matrix m) {
    int rank = m.colNum;

    for (int row = 0; row < rank; row++) {
        if (m[row][row]) {
            for (int col = 0; col < m.rowNum; col++) {
                if (col != row) {
                    float mult = (float)m[col][row] / m[row][row];
                    for (int i = 0; i < rank; i++) {
                        m[col][i] -= mult * m[row][i];
                    }
                }
            }
        }
        else {
            bool reduce = true;
            for (int i = row + 1; i < m.rowNum; i++) {
                if (m[i][row]) {
                    swap(&m, row, i);
                    reduce = false;
                    break;
                }
            }
            if (reduce) {
                rank--;
                for (int i = 0; i < m.rowNum; i++)
                    m[i][row] = m[i][rank];
            }
            row--;
        }
    }

    return rank;
}

Matrix Spectral::transpose(Matrix A) {
    int m = A.rowNum;
    int n = A.colNum;
    Matrix trans(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            trans[i][j] = A[j][i];
        }
    }
    return trans;
}


Matrix Spectral::reduce(Matrix A) {
    for (int i = 0; i < A.rowNum; i++) { //This isnt properly correct
        if (A[i][i] == 0) {
            swap(&A, i, i + 1);
        }
        Vector firstRow(A[i]);
        for (int j = i + 1; j < A.rowNum; j++) {
            Vector oldRow(A[j]);
            Vector newRow = oldRow - firstRow * (oldRow[i] / firstRow[i]);
            A.substitute(j, newRow);
        }
    }
    return A;
}

int firstNonZero(Vector v) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] != 0) {
            return i;
        }
    }
    cout << "not found" << endl;
    return -1;
}

Matrix Spectral::diagonalize(Matrix M) {
    //M = reduce(M);
    for (int i = M.rowNum - 1; i >= 0; i--) {
        Vector lastRow(M[i]);
        for (int j = i - 1; j >= 0; j--) {
            Vector oldRow(M[j]);
            Vector newRow(M.colNum);
            int q = firstNonZero(lastRow);
            for (int k = 0; k < M.colNum; k++) {
                if (k < q) {
                    newRow[k] = oldRow[k];
                }
                else {
                    newRow[k] = oldRow[k] - lastRow[k] * (oldRow[q] / lastRow[q]);
                }
            }
            M.substitute(j, newRow);
        }
    }

    for (int i = 0; i < M.rowNum; i++) {
        Vector v(M[i]);
        int q = firstNonZero(v);
        v = v * (1 / v[q]);
        M.substitute(i, v);
    }

    return M;
}

Vector Spectral::pivot(Matrix M) {
    //This methods returns where the pivots are, 
    //this informations can be used to locate the linearly indepedent vectors
    Matrix U = reduce(M);
    vector<float> p;
    for (int i = 0; i < M.rowNum; i++) {
        for (int j = 0; j < M.colNum; j++) {
            if (M[i][j] != 0) {
                p.push_back(i);
                break;
            }
        }
    }
    Vector pvt(p);
    return pvt;
}

Matrix Spectral::inverse(Matrix M) {
    if (M.rowNum != M.colNum) {
        cout << "Matrix must be square!!!" << endl;
        return M;
    }
    Matrix inv(M.rowNum, M.colNum * 2);
    for (int i = 0; i < inv.rowNum; i++) {
        for (int j = 0; j < inv.colNum; j++) {
            if (i < M.rowNum && j < M.colNum) {
                inv[i][j] = M[i][j];
            }
            else if (j - M.colNum == i) {
                inv[i][j] = 1;
            }
            else {
                inv[i][j] = 0;
            }
        }
    }
    inv = reduce(inv);
    inv = diagonalize(inv);
    Matrix A(M.rowNum, M.colNum);
    for (int i = 0; i < A.rowNum; i++) {
        for (int j = 0; j < A.colNum; j++) {
            A[i][j] = inv[i][j + M.colNum];
        }
    }

    return A;
}

Vector Spectral::linsolve(Matrix M, Vector b) {
    if (M.rowNum != b.size()) {
        cout << "Wrong size!" << endl;
        return b; //Think something smarter
    }
    int r = rank(M);
    M.addColumn(b);
    if (rank(M) != r) {
        cout << "System cannot be solved! Use least square!" << endl;
        return b; //Think something smarter
    }
    if (rank(M) > b.size()) {
        //Yet to implement
        cout << "Since rank < n, the solution is not unique. This feature will be introduce soon" << endl;
        return b; //Think something smarter
    }
    Matrix U = reduce(M);
    int i = U.rowNum;
    int j = U.colNum;
    Vector solution(i);
    solution[i - 1] = U[i - 1][j - 1] / U[i - 1][j - 2];
    for (int q = i - 2; q >= 0; q--) {

    }
    return b;
}

float Spectral::det(Matrix M) {
    if (M.colNum != M.rowNum) {
        cout << "Matrix must be square!" << endl;
        return INT_MIN;
    }
    Matrix U = reduce(M);
    float d = U[0][0];
    for (int i = 1; i < U.colNum; i++) {
        d = d * U[i][i];
    }
    int n = U.numSwap;
    d = pow(-1, n) * d;
    return d;
}

Matrix Spectral::roundMatrix(Matrix A) {
    int n = A.rowNum;
    int m = A.colNum;
    Matrix rounded(n,m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rounded[i][j] = round(A[i][j]);
        }
    }
    return rounded;
}


// Vector methods
int min(int a, int b) {
    if (a < b) {
        return a;
    }
    else {
        return b;
    }
}

bool Spectral::linearlyIndependent(vector<Vector> span) {
    int c = span[0].size();
    int r = span.size();

    Matrix M(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            M[i][j] = span[i][j];
        }
    }
    if (rank(M) == min(r, c)) {
        return true;
    }
    else {
        return false;
    }
}

// Vectorspace methods

int Spectral::dimension(VectorSpace L) {
    int n = L.spannedBy().size();
    Vector v0 = L.spannedBy()[0];
    int cont = 1;
    for (int i = 1; i < n; i++) {
        if (linearlyIndependent({ v0,L.spannedBy()[i] })) { cont++; }
    }
    return cont;
}

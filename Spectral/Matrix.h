#pragma once
#ifndef MATRIX_H
#include <vector>
#include "vector.h"
#include <iostream>
#include <cmath>
#define MATRIX_H
using namespace std;

class Matrix
{
public:
    //Constructors
    Matrix(vector<vector<float>> _data);
    Matrix(int r, int c);

    int colNum;
    int rowNum;
    vector<vector<float>> data;
    vector<vector<float>> zeros(int r, int c);
    void addColumn(Vector col);
    void addRow(Vector row);

    //Methods
    void print();
    void substitute(int i, Vector v);
    vector<float> operator [](int a) const {
        return data[a];
    }
    vector<float>& operator [](int a) {
        return data[a];
    }

    Matrix operator +(const Matrix& M) {
        if (M.colNum != colNum || M.rowNum != rowNum) {
            cout << "Error! Can't add vectors of different size!" << endl;
            return zeros(rowNum, colNum);
        }
        Matrix sum(rowNum, colNum);
        for (int i = 0; i < rowNum; i++) {
            for (int j = 0; j < colNum; j++) {
                sum[i][j] = data[i][j] + M[i][j];
            }
        }
        return sum;
    }
    Matrix operator *(float b) const {
        Matrix prod(rowNum, colNum);
        for (int i = 0; i < rowNum; i++) {
            for (int j = 0; j < colNum; j++) {
                prod[i][j] = data[i][j] * b;
            }
        }
        return prod;
    }
    Matrix operator *(Matrix m) const {
        if (colNum != m.rowNum) {
            cout << "Error! Matrices not compatible!" << endl;
        }
        Matrix prod(rowNum, m.colNum);

        /*for (int i = 0; i < rowNum; i++) {
            for (int j = 0; j < m.colNum; j++) {
                Vector col(rowNum);
                for (int k = 0; k < rowNum; k++) {
                    col[k] = m.data[k][j];
                }
                prod[i][j] = Vector::dot(data[i], col);
            }
        }
        return prod;
        */
        for (int i = 0; i < rowNum; i++) {
            for (int j = 0; j < m.colNum; j++) {
                for (int k = 0; k < colNum; k++) {
                    prod[i][j] = prod[i][j] + data[i][k] * m.data[k][j];
                }
            }
        }
        return prod;
    }
    Vector operator *(Vector v) const {
        if (colNum != v.size()) {
            cout << "Error! Matrix and vector are not compatible!" << endl;
        }
        Vector prod(rowNum);
        for (int i = 0; i < rowNum; i++) {
            prod[i] = Vector::dot(data[i], v.getElements());
        }
        return prod;
    }
    Matrix operator -(const Matrix& M) {
        if (M.colNum != colNum || M.rowNum != rowNum) {
            cout << "Error! Can't add matrices of different size!" << endl;
            return zeros(rowNum, colNum);
        }
        Matrix sum(rowNum, colNum);
        for (int i = 0; i < rowNum; i++) {
            for (int j = 0; j < colNum; j++) {
                sum[i][j] = data[i][j] - M[i][j];
            }
        }
        return sum;
    }
    static Matrix rotation2D(float angle);
    static Matrix rotation3D(float theta, float phi);

private:
    int numSwap; //This counter keeps track of how many times the rows of the matrix have been swapped
};

#endif // MATRIX_H



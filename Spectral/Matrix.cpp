#include "matrix.h"
#include "pch.h"
#include <iostream>
using namespace std;

Matrix::Matrix(vector<vector<float>> _data) {
    rowNum = _data[0].size();
    colNum = _data.size();
    for (int i = 0; i < rowNum; i++) {
        data.push_back(_data[i]);
    }
    numSwap = 0;
}

vector<vector<float>> Matrix::zeros(int r, int c) {
    vector<float> z;
    for (int i = 0; i < c; i++) {
        z.push_back(0);
    }
    vector<vector<float>> M;
    for (int i = 0; i < r; i++) {
        M.push_back(z);
    }
    return M;
}

Matrix::Matrix(int r, int c) {
    rowNum = r;
    colNum = c;
    data = zeros(rowNum, colNum);
}

void Matrix::addRow(Vector row) {
    if (row.size() != colNum) {
        cout << "Error! Size must be equal to the number of columns!" << endl;
        return;
    }
    data.push_back(row.getElements());
    rowNum++;
}

void Matrix::addColumn(Vector col) {
    if (col.size() != rowNum) {
        cout << "Error! size() must be equal to the number of rows!" << endl;
        return;
    }
    for (int i = 0; i < rowNum; i++) {
        data[i].push_back(col[i]);
    }
    colNum++;
}

void Matrix::print() {
    for (int i = 0; i < rowNum; i++) {
        for (int j = 0; j < colNum; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Matrix::substitute(int i, Vector v) {
    vector<float> row = v.getElements();
    for (int k = 0; k < colNum; k++) {
        data[i][k] = row[k];
    }
}

Matrix Matrix::rotation2D(float angle) {
    Matrix Q(2, 2);
    Q[0][0] = cos(angle); Q[0][1] = -sin(angle);
    Q[1][0] = sin(angle); Q[1][1] = cos(angle);
    return Q;
}


Matrix Matrix::rotation3D(char axis,float theta) {
    Matrix R(3, 3);
    if (axis == 'x') {
        R[0][0] = 1; R[0][1] = 0; R[0][2] = 0;
        R[1][0] = 0; R[1][1] = cos(theta); R[1][2] = -sin(theta);
        R[2][0] = 0; R[2][1] = sin(theta); R[2][2] = cos(theta);
    }
    else if (axis == 'y') {
        R[0][0] = cos(theta); R[0][1] = 0; R[0][2] = sin(theta);
        R[1][0] = 0; R[1][1] = 1; R[1][2] = 0;
        R[2][0] = -sin(theta); R[2][1] = 0; R[2][2] = cos(theta);
    }
    else if (axis == 'z') {
        R[0][0] = cos(theta); R[0][1] = -sin(theta); R[0][2] = 0;
        R[1][0] = sin(theta); R[1][1] = cos(theta); R[1][2] = 0;
        R[2][0] = 0; R[2][1] = 0; R[2][2] = 1;
    }
}
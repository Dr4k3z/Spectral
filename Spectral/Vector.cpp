#include "vector.h"
#include "pch.h"
#include <iostream>
using namespace std;

Vector::Vector(vector<float> _data) {
    n = _data.size();
    for (int i = 0; i < n; i++) {
        data.push_back(_data[i]);
    }
}

Vector::Vector(int _n) {
    n = _n;
    data = zeros(n);
}

vector<float> Vector::zeros(int n) {
    vector<float> z;
    for (int i = 0; i < n; i++) {
        z.push_back(0);
    }
    return z;
}

void Vector::print() {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << data[i] << ",";
    }
    cout << "]" << endl;
}

int Vector::size() {
    return n;
}

vector<float> Vector::getElements() {
    return data;
}

float Vector::dot(Vector a, Vector b) {
    int n = a.size();
    if (n != b.size()) {
        cout << "Error! Vectors must be same size!" << endl;
        return -1; //HOW TO MANAGE INTERNAL ERRORS?
    }
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum = a[i] * b[i] + sum;
    }
    return sum;
}

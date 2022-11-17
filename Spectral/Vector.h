#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Vector {
public:
    //Constructors
    Vector(vector<float> v);
    Vector(int c);
    //static Vector buildVector(vector<float>); //TODO
    //Getters
    int size();
    vector<float> getElements();
    //Methods
    vector<float> zeros(int n);
    void print();
    static float dot(Vector a, Vector b);
    //Overloaded operators
    float operator [](int a) const {
        return data[a];
    }
    float& operator [](int a) {
        return data[a];
    }
    Vector operator +(const Vector& b) {
        if (b.n != n) {
            cout << "Error! Can't add vectors of different size!" << endl;
            return zeros(n);
        }
        Vector sum(n);
        for (int i = 0; i < n; i++) {
            sum[i] = data[i] + b[i];
        }
        return sum;
    }
    Vector operator *(float b) const {
        Vector prod(n);
        for (int i = 0; i < n; i++) {
            prod[i] = data[i] * b;
        }
        return prod;
    }
    Vector operator -(const Vector& v) {
        if (v.n != n) {
            cout << "Error! Can't add vectors of different size!" << endl;
            return zeros(n);
        }
        Vector sum(n);
        for (int i = 0; i < n; i++) {
            sum[i] = data[i] - v[i];
        }
        return sum;
    }
private:
    int n;
    vector<float> data;
};

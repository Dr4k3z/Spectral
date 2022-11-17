#include "vectorspace.h"
#include "pch.h"
#include <iostream>
using namespace std;

VectorSpace::VectorSpace(vector<Vector> _base) {
    for (unsigned int i = 0; i < _base.size(); i++) {
        baseVectors.push_back(_base[i]);
    }
}

vector<Vector> VectorSpace::spannedBy() {
    return baseVectors;
}

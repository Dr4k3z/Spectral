#pragma once
#ifndef VECTORSPACE_H
#include "Matrix.h"
#include "Vector.h"
#define VECTORSPACE_H

// The constructors will have a variable number of arguments
// I know c++11 has some feature to do so, which i haven't studied yet
// Therefore, we gonna use a vector of arguments, in this case a vector of vector.
// Will update in the future.

class VectorSpace
{
public:
    VectorSpace(vector<Vector> _base);
    //Methods
    vector<Vector> spannedBy();
protected:
    vector<Vector> baseVectors;
};

#endif // VECTORSPACE_H



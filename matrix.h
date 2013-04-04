#ifndef MATRIX_H
#define MATRIX_H

#include "includes.h"

template <class Type>
class Matrix
{
public:
    Matrix()
    {
        n=0; m=0;
    }

    Matrix(int _n, int _m)
    {
        n=_n;
        m=_m;
    }

    Matrix(QVector<QVector<Type> > _a);
    bool addRow(QVector<Type> row);
    bool addCol(QVector<Type> col);

private:
    int n,m;
    QVector<QVector<Type> > a;
};

#endif // MATRIX_H

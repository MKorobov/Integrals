#ifndef INTEGRAL_H
#define INTEGRAL_H

#include "polynomial.h"
#include "fraction.h"

class Integral
{
public:
    Integral();
    static QString simpleFunction(PolyFraction f);
    static QString simpleFunction(Polynomial p, Polynomial q, int n);
    static QString simpleFunction1Type(Polynomial p, Polynomial q);
    static QString simpleFunction2Type(Polynomial p, Polynomial q, int n);
    static QString simpleFunction3Type(Polynomial p, Polynomial q);
    static QString simpleFunction4Type(Polynomial p, Polynomial q, int n);
    static QString simpleFunctionNotFraction(Polynomial p, Polynomial q);
    static QString notSimpleFunction(Polynomial p, Polynomial q, bool error);
};

#endif // INTEGRAL_H

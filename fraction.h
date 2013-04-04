#ifndef FRACTION_H
#define FRACTION_H

#include <QString>
#include "polynomial.h"

class Fraction
{
public:
    Fraction();
    Fraction(double _a, double _b);
    Fraction(QString str);
    QString toString();
    void normalize();
    Fraction add(Fraction arg);
    Fraction multiply(Fraction arg);
    Fraction divide(Fraction arg);
    Fraction operator=(Fraction arg);
    //Fraction operator+(Fraction arg1, Fraction arg2);
    Fraction operator+=(Fraction arg);
    //Fraction operator*(Fraction arg1, Fraction arg2);
    Fraction operator*=(Fraction arg);
    //Fraction operator/(Fraction arg1, Fraction arg2);
    Fraction operator/=(Fraction arg);
    int integerPart();
    Fraction fractionPart();
    static Fraction toFraction(double _a, double _b);
    static Fraction toFraction(QString str);
    int getNumerator();
    int getDenominator();
    void setA(double _a);
    void setB(double _b);
    bool isOne();

private:
    double a,b;
};

class PolyFraction
{
public:
    PolyFraction();
    PolyFraction(Polynomial _a, Polynomial _b);
    static PolyFraction toPolyFraction(Polynomial _a, Polynomial _b);
    static PolyFraction toPolyFraction(Polynomial _a, Polynomial _b, int _n);
    Polynomial getNumerator();
    Polynomial getDenominator();
    void setA(Polynomial _a);
    void setB(Polynomial _b);
    void setDenominatorDegree(int _n);
    int getDenominatorDegree();

private:
    Polynomial a,b;
    int denominatorDegree;
};

#endif // FRACTION_H

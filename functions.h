#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QVector>
#include <vector>
#include "fraction.h"
using namespace std;

class Functions
{
public:
    Functions();
    static int gcd(int a, int b);
    static double binPow(double x, int n);
    static double abs(double x);
    static QVector<PolyFraction> undeterminedCoefficients(PolyFraction main, QVector<Polynomial> vec, QVector<int> degrees, int n);
    static int gauss(QVector<QVector<double> > a, vector<double> & ans);
    static Polynomial gcd(Polynomial a, Polynomial b);
    static void swap(Polynomial &a, Polynomial &b);
    static void swap(double &a, double &b);
    static QString deleteSups(QString str);
};

#endif // FUNCTIONS_H

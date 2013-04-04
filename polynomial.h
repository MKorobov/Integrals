#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <QString>
#include <QVector>

class Polynomial
{
public:
    Polynomial();
    Polynomial(int _n);
    Polynomial(QString str);
    int getDeg();
    QString toString();
    QString toStringWithoutSups();
    Polynomial add(Polynomial p);
    Polynomial sub(Polynomial p);
    Polynomial derivative();
    bool isEqual(Polynomial b);
    Polynomial operator=(Polynomial arg);
    Polynomial operator*=(Polynomial arg);
    Polynomial multiply(Polynomial p);
    static Polynomial toPolynomial(int arg);
    static Polynomial toPolynomial(QString arg);
    long long valueInPoint(long long x);
    bool isNullInPoint(double x);
    //QVector<double> findRoots();
    QVector<Polynomial> findQuads();
    void preFindQuads(double *a, double *b, double *c, int n);
    bool isNull();
    Polynomial divide(Polynomial p);
    Polynomial mod(Polynomial p);
    double getCoef(int n);
    void setCoef(int n, double val);
    bool getError();
    void changeMyself(Polynomial p);

private:
    double degrees[1001];
    int n;
    QVector<Polynomial> quads;
    bool error;
};

#endif // POLYNOMIAL_H

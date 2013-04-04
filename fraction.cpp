#include "fraction.h"
#include "functions.h"
#include <math.h>

Fraction::Fraction()
{
}

Fraction::Fraction(double _a, double _b)
{
    a=_a;
    b=_b;
}

Fraction::Fraction(QString str)
{
    int pos = str.indexOf("/");
    a = str.mid(0,pos).toInt();
    b = str.mid(pos+1).toInt();
}

void Fraction::normalize()
{
    if(b<0) {
        a*=-1;
        b*=-1;
    }
    int d = abs(Functions::gcd(a,b));
    a/=d;
    b/=d;
}

Fraction Fraction::add(Fraction arg)
{
    Fraction ret;
    ret.a = a*arg.b+arg.a*b;
    ret.b = b*arg.b;
    ret.normalize();
    return ret;
}

Fraction Fraction::multiply(Fraction arg)
{
    Fraction ret;
    ret.a = a*arg.a;
    ret.b = b*arg.b;
    ret.normalize();
    return ret;
}

Fraction Fraction::divide(Fraction arg)
{
    Fraction ret;
    ret.a = a*arg.b;
    ret.b = b*arg.a;
    ret.normalize();
    return ret;
}

Fraction Fraction::toFraction(double _a, double _b)
{
    Fraction ret(_a,_b);
    return ret;
}

Fraction Fraction::toFraction(QString str)
{
    int pos = str.indexOf("/");
    int a = str.mid(0,pos).toInt();
    int b = str.mid(pos+1).toInt();
    return Fraction::toFraction(a,b);
}

int Fraction::integerPart()
{
    return (int)a/b;
}

Fraction Fraction::fractionPart()
{
    return toFraction(a - int(a/b)*b,b);
}

int Fraction::getNumerator()
{
    return a;
}

int Fraction::getDenominator()
{
    return b;
}

Fraction Fraction::operator =(Fraction arg)
{
    this->a = arg.getNumerator();
    this->b = arg.getDenominator();
    return *this;
}

Fraction Fraction::operator *=(Fraction arg)
{
    this->a = this->getNumerator()*arg.getNumerator();
    this->b = this->getDenominator()*arg.getDenominator();
    return *this;
}

Fraction Fraction::operator +=(Fraction arg)
{
    this->a = this->a*arg.getDenominator()+arg.getNumerator()*this->b;
    this->b = this->b*arg.getDenominator();
    this->normalize();
    return *this;
}

Fraction Fraction::operator /=(Fraction arg)
{
    this->a = this->getNumerator()*arg.getDenominator();
    this->b = this->getDenominator()*arg.getNumerator();
    this->normalize();
    return *this;}

QString Fraction::toString()
{
    if(isOne())
        return "1";
    if(b==1.0)
        return QString::number(a);
    return QString::number(a)+"/"+QString::number(b);
}

void Fraction::setA(double _a)
{
    a = _a;
}

void Fraction::setB(double _b)
{
    b = _b;
}

bool Fraction::isOne()
{
    return a==b;
}


PolyFraction::PolyFraction()
{
}

PolyFraction::PolyFraction(Polynomial _a, Polynomial _b)
{
    a = _a;
    b = _b;
}

Polynomial PolyFraction::getNumerator()
{
    return a;
}

Polynomial PolyFraction::getDenominator()
{
    return b;
}

void PolyFraction::setA(Polynomial _a)
{
    a = _a;
}

void PolyFraction::setB(Polynomial _b)
{
    b = _b;
}

void PolyFraction::setDenominatorDegree(int _n)
{
    denominatorDegree = _n;
}

PolyFraction PolyFraction::toPolyFraction(Polynomial _a, Polynomial _b)
{
    PolyFraction ret;
    ret.setA(_a);
    ret.setB(_b);
    return ret;
}

PolyFraction PolyFraction::toPolyFraction(Polynomial _a, Polynomial _b, int _n)
{
    PolyFraction ret;
    ret.setA(_a);
    ret.setB(_b);
    ret.setDenominatorDegree(_n);
    return ret;
}

int PolyFraction::getDenominatorDegree()
{
    return denominatorDegree;
}



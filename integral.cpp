#include "integral.h"
#include "functions.h"
#define EPS 1e-12
#include <cmath>
#include <map>
#include <QDebug>

using namespace std;

Integral::Integral()
{
}

QString Integral::simpleFunctionNotFraction(Polynomial p, Polynomial q)
{
    int n = p.getDeg();
    Fraction tmp;
    QString ret;
    bool first = true;
    for(int i=n;i>=0;--i) {
        tmp.setA(p.getCoef(i));
        if(!tmp.getNumerator())
            continue;
        tmp.setB((i+1)*q.getCoef(0));
        tmp.normalize();
        if(tmp.getNumerator()>0 && !first)
            ret += "+";
        if(fabs(tmp.getNumerator()) != fabs(tmp.getDenominator())) {
            ret += tmp.toString()+"*";
        }
        else {
            if(tmp.getNumerator() != tmp.getDenominator())
                ret += "-";
        }
        ret += "x";
        if(i)
            ret += "<sup>"+QString::number(i+1)+"</sup>";
        first = false;
    }
    return ret;
}

QString Integral::simpleFunction1Type(Polynomial p, Polynomial q)
{
    QString ret;/*
    if(p.getCoef(0)!=q.getCoef(1))
        ret += Fraction::toFraction((int)p.getCoef(0),q.getCoef(1)).toString();*/
    double tmp = p.getCoef(0)/q.getCoef(1);
    if(fabs(tmp)!=1.0)
        ret += QString::number(tmp);
    else {
        if(tmp!=1.0)
            ret += "-";
    }
    if(fabs(tmp)<EPS)
        return "";
    return ret+"ln("+q.toString()+")";
}

QString Integral::simpleFunction2Type(Polynomial p, Polynomial q, int n)
{
    if(n==1)
        return Integral::simpleFunction1Type(p,q);
    if(!p.getCoef(0))
        return "";
    QString ret;
    ret += QString::number(q.getCoef(1)<0?p.getCoef(0):-p.getCoef(0))+"/(";
    if((n-1)*q.getCoef(1)!=1)
        ret += QString::number(abs((n-1)*q.getCoef(1)));
    ret += "("+q.toString()+")";
    if(n!=2)
        ret += "<sup>"+QString::number(n-1)+"</sup>";
    ret += ")";
    return ret;
}

QString Integral::simpleFunction3Type(Polynomial p, Polynomial q)
{
    QString radicOpen("&radic;<span style='text-decoration:overline'>");
    QString radicClose("</span>");
    QString ret;
    double m=p.getCoef(1),n=p.getCoef(0);
    double a = q.getCoef(2);
    q.setCoef(1,q.getCoef(1)/q.getCoef(2));
    q.setCoef(0,q.getCoef(0)/q.getCoef(2));
    q.setCoef(2,1.0);
    double b=q.getCoef(1),c=q.getCoef(0);
    if(fabs(a-1.0)>=EPS)
        ret += "1/"+QString::number(a)+"*(";
    if(fabs(m)>=EPS) {
        if(m/2.0!=1.0)
            ret += QString::number(m/2.0);
        ret += "ln("+q.toString()+")";
    }
    if(fabs(2.0*n-m*b)>=EPS) {
        if(2*n-m*b>=EPS)
            ret += "+";
        ret += QString::number(2*n-m*b)+"/";
        ret += radicOpen+QString::number(4*c-b*b)+radicClose+"*";
        ret += "arctg((2x";
        if(fabs(b)>=EPS)
            ret += "+"+QString::number(b)+")/";
        else
            ret += ")/";
        ret += radicOpen+QString::number(4*c-b*b)+radicClose+")";
    }
    if(fabs(a-1.0)>=EPS)
        ret += ")";
    if(ret[0]=='+')
        ret.remove(0,1);
    return ret;
}

QString Integral::simpleFunction4Type(Polynomial p, Polynomial q, int n)
{
    if(n==1)
        return Integral::simpleFunction3Type(p,q);
    QString ret;
    if(p.getCoef(1)==0 && p.getCoef(0)==1) {
        ret += "(2x+"+QString::number(q.getCoef(1))+")/";
        ret += "("+QString::number((n-1)*(4*q.getCoef(0)-q.getCoef(1)*q.getCoef(1)))+")";
        ret += "("+q.toString()+")";
        if(n!=2)
            ret += "<sup>"+QString::number(n-1)+"</sup>";
        ret += "+";
        ret += QString::number(4*n-6)+"/"+QString::number((n-1)*(4*q.getCoef(0)-q.getCoef(1)*q.getCoef(1)));
        ret += "(" + Integral::simpleFunction4Type(p,q,n-1) + ")";
        return ret;
    }

    if(fabs(p.getCoef(1))>=EPS) {
        ret += QString::number(-p.getCoef(1))+"/(";
        ret += QString::number(2*(n-1))+"(";
        ret += q.toString()+")";
        if(n!=2)
            ret += "<sup>"+QString::number(n-1)+"</sup>";
        ret += ")";
    }
    ret += "("+QString::number(p.getCoef(0));
    if(q.getCoef(1)*p.getCoef(1) != 0)
        ret += "-"+QString::number(q.getCoef(1)*p.getCoef(1))+"/2";
    ret += ")";
    return ret;
}

QString Integral::simpleFunction(Polynomial p, Polynomial q, int n)
{
    if(q.getDeg()==0) {
        if(q.getCoef(0)==0)
            return "Dividing by zero.";
        return simpleFunctionNotFraction(p,q);
    }
    if(q.getDeg()==1 && p.getDeg()==0) {
        return simpleFunction2Type(p,q,n);
    }
    if(q.getDeg()==2 && p.getDeg()==1){
        return simpleFunction4Type(p,q,n);
    }
    return "We don't know how to integrate this function.";
}

QString Integral::notSimpleFunction(Polynomial p, Polynomial q, bool error)
{
    qDebug() << p.toStringWithoutSups();
    qDebug() << q.toStringWithoutSups();
    map<QString,int> degreesM;
    QString ret;

    if(q.getDeg()==0) {
        return Integral::simpleFunctionNotFraction(p,q);
    }

    if(p.getDeg()>=q.getDeg()) {
        ret += Integral::simpleFunctionNotFraction(p.divide(q),Polynomial::toPolynomial("1"))+"+";
        p = p.mod(q);
    }

    QVector<Polynomial> quads;
    quads = q.findQuads();
    qDebug() << "!!!!!!!!!!!!!!!!!!!!!!" << quads.size();
    error = q.getError();
    QVector<int> degrees;
    int n = 0;
    for(int i=0,len=quads.size();i<len;++i){
        n += quads[i].getDeg();
        degreesM[quads[i].toString()]++;
        degrees.push_back(degreesM[quads[i].toString()]);
    }
    QVector<PolyFraction> fractions = Functions::undeterminedCoefficients(PolyFraction::toPolyFraction(p,q),quads,degrees,n);
    for(int i=0,len=fractions.size();i<len;++i) {
        ret += Integral::simpleFunction(fractions[i].getNumerator(),fractions[i].getDenominator(),fractions[i].getDenominatorDegree())+"+";
    }
    for(int i=0,len=ret.size();i<len-1;++i){
        if((ret[i]=='+') && (ret[i+1]=='-' || ret[i+1]=='+')){
            ret.remove(i,1);
            i--;
        }
    }
    ret.remove(ret.size()-1,1);
    if(ret[0]=='+')
        ret.remove(0,1);
    return ret;
}

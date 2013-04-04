#include "polynomial.h"
#include "functions.h"
#include <cmath>
#include <QDebug>
#include <algorithm>
#define EPS 1e-6
using namespace std;

Polynomial::Polynomial()
{
    n=0;
    memset(degrees,0,sizeof(degrees));
}

Polynomial::Polynomial(int _n)
{
    n=_n;
    memset(degrees,0,sizeof(degrees));
}

Polynomial::Polynomial(QString str)
{
    n=0;
    memset(degrees,0,sizeof(degrees));
    QString tmp;
    int len=str.size();
    int lastSign=1;
    int i;
    if(str[0]=='-')
        i=1,lastSign*=-1;
    else
        i=0;
    for(;i<len;++i) {
        if(str[i]!='+' && str[i]!='-')
            tmp+=str[i];
        else {
            int pos = tmp.indexOf("x");
            int c,d; // coef and degree

            QString coef = tmp.mid(0,pos);
            if(coef=="")
                c=1;
            else
                c=coef.toInt();
            c*=lastSign;
            if(str[i]=='+')
                lastSign=1;
            else
                lastSign=-1;

            if(tmp[tmp.size()-1]=='x')
                d=1;
            else {
                if(pos==-1)
                    d=0;
                else {
                    QString degree = tmp.mid(pos+2);
                    d=degree.toInt();
                }
            }

            tmp="";
            degrees[d]+=c;
            if(d>n)
                n=d;
        }
    }
    if(tmp!=""){
        int pos = tmp.indexOf("x");
        int c,d;

        QString coef = tmp.mid(0,pos);
        if(coef=="")
            c=1;
        else
            c=coef.toInt();
        c*=lastSign;

        if(tmp[tmp.size()-1]=='x')
            d=1;
        else {
            if(pos==-1)
                d=0;
            else {
                QString degree = tmp.mid(pos+2);
                d=degree.toInt();
            }
        }
        if(d>n)
            n=d;
        degrees[d]+=c;
    }
}


QString Polynomial::toString()
{
    if(n==-1)
        return "0";
    QString ret;
    for(int i=n;i>=0;--i){
        if(!degrees[i])
            continue;
        if(degrees[i]>0)
            ret+="+";
        if(degrees[i]!=1 || ((degrees[i]==1 || degrees[i]==-1) && !i)){
            if(degrees[i]!=-1 || (degrees[i]==-1 && !i))
                ret+=(QString::number(degrees[i]));
            else
                ret+="-";
        }
        if(i!=0)
            ret+="x";
        if(i!=0 && i!=1)
            ret+=("<sup>"+(QString::number(i))+"</sup>");
    }
    if(ret[0]=='+')
        ret = ret.mid(1);
    return ret;
}

QString Polynomial::toStringWithoutSups()
{
    if(n==-1)
        return "0";
    QString ret;
    for(int i=n;i>=0;--i){
        if(!degrees[i])
            continue;
        if(degrees[i]>0)
            ret+="+";
        if(degrees[i]!=1 || ((degrees[i]==1 || degrees[i]==-1) && !i)){
            if(degrees[i]!=-1 || (degrees[i]==-1 && !i))
                ret+=(QString::number(degrees[i]));
            else
                ret+="-";
        }
        if(i!=0)
            ret+="x";
        if(i!=0 && i!=1)
            ret+=("^"+QString::number(i));
    }
    if(ret[0]=='+')
        ret = ret.mid(1);
    return ret;
}

int Polynomial::getDeg()
{
    return n;
}

Polynomial Polynomial::derivative()
{
    Polynomial ret(this->getDeg()-1);
    for(int i=1;i<=n;++i)
        ret.degrees[i-1]=degrees[i]*i;
    return ret;
}


Polynomial Polynomial::add(Polynomial p)
{
    int len=max(n,p.getDeg());
    Polynomial ret(len);
    for(int i=0;i<=len;++i)
        ret.degrees[i]=this->degrees[i]+p.degrees[i];
    return ret;
}

Polynomial Polynomial::sub(Polynomial p)
{
    int len=max(n,p.getDeg());
    Polynomial ret(len);
    for(int i=0;i<=len;++i)
        ret.degrees[i]=this->degrees[i]-p.degrees[i];
    return ret;
}

bool Polynomial::isEqual(Polynomial b)
{
    if(this->getDeg() != b.getDeg())
        return false;
    for(int i=0;i<n;++i)
        if(degrees[i] != b.degrees[i])
            return false;
    return true;
}


Polynomial Polynomial::operator =(Polynomial arg)
{
    this->n = arg.getDeg();
    for(int i=0;i<=n;++i)
        this->degrees[i]=arg.degrees[i];
    return *this;
}

Polynomial Polynomial::operator *=(Polynomial arg)
{
    this->n += arg.getDeg();
    for(int i=0;i<=getDeg();++i)
        for(int j=0;j<=arg.getDeg();++j)
            this->degrees[i+j]+=degrees[i]*arg.degrees[j];
    return *this;
}

Polynomial Polynomial::multiply(Polynomial p)
{
    Polynomial ret;
    ret.n = getDeg()+p.getDeg();
    for(int i=0;i<=getDeg();++i)
        for(int j=0;j<=p.getDeg();++j)
            ret.degrees[i+j]+=degrees[i]*p.degrees[j];
    return ret;
}

Polynomial Polynomial::toPolynomial(int arg)
{
    Polynomial ret;
    ret.n=1;
    ret.degrees[0]=arg;
    return ret;
}

Polynomial Polynomial::toPolynomial(QString arg)
{
    Polynomial ret(arg);
    return ret;
}

long long Polynomial::valueInPoint(long long x)
{
    long long oldX=x;
    long long ans=(long long)this->degrees[0];
    for(int i=1;i<=this->getDeg();++i) {
        ans+=(long long)this->degrees[i]*x;
        x*=oldX;
    }
    return ans;
}

bool Polynomial::isNullInPoint(double x)
{
    if(!(valueInPoint(x)))
        return true;
    return false;
}

/*QVector<double> Polynomial::findRoots()
{
    QVector<double> ret;
    for(int m=1;m*m<=degrees[n];++m) {
        if(degrees[n]%m)
            continue;
        for(int n=1;n*n<=degrees[0];++n) {
            if(degrees[0]%n)
                continue;
            if(isNullInPoint(m/n))
                ret.push_back(m/n);
            if(isNullInPoint(m/n*(-1.0)))
                ret.push_back(-m/n);
        }
    }
    return ret;
}*/

bool Polynomial::isNull()
{
    for(int i=0;i<=this->getDeg();++i)
        if(this->degrees[i])
            return false;
    return true;
}

Polynomial Polynomial::divide(Polynomial p)
{
    if(this->getDeg()<p.getDeg())
        return Polynomial::toPolynomial("0");
    Polynomial tmp(toStringWithoutSups()),ret;
    tmp.n = this->n;
    ret.n = this->getDeg()-p.getDeg();
    int pos=ret.n;
    while(!tmp.isNull() && tmp.getDeg()>=p.getDeg()){
        Polynomial tmp2;
        tmp2.n = pos;

        pos = tmp.getDeg()-p.getDeg();
        ret.degrees[pos] = tmp.degrees[tmp.getDeg()]/p.degrees[p.getDeg()];
        tmp2.degrees[pos] = ret.degrees[pos];

        tmp = tmp.sub(tmp2.multiply(p));
        while(!tmp.degrees[tmp.getDeg()])
            tmp.n--;
    }
    return ret;
}

void Polynomial::changeMyself(Polynomial p)
{
    memset(degrees,0,sizeof(degrees));
    n = p.getDeg();
    for(int i=0;i<=n;++i)
        degrees[i] = p.getCoef(i);
}

Polynomial Polynomial::mod(Polynomial p)
{
    if(this->getDeg()<p.getDeg())
        return *this;
    Polynomial tmp(toStringWithoutSups()),ret;
    tmp.n = this->n;
    ret.n = this->getDeg()-p.getDeg();
    int pos=ret.n;
    while(!tmp.isNull() && tmp.getDeg()>=p.getDeg()){
        Polynomial tmp2;
        tmp2.n = pos;

        pos = tmp.getDeg()-p.getDeg();
        ret.degrees[pos] = tmp.degrees[tmp.getDeg()]/p.degrees[p.getDeg()];
        tmp2.degrees[pos] = ret.degrees[pos];

        tmp = tmp.sub(tmp2.multiply(p));
        while(!tmp.degrees[tmp.getDeg()])
            tmp.n--;
    }
    return tmp;
}

double Polynomial::getCoef(int n)
{
    return degrees[n];
}

void Polynomial::setCoef(int n, double val)
{
    degrees[n]=val;
}

void Polynomial::preFindQuads(double *a, double *b, double *c, int n)
{
    double r,s,dn,dr,ds,drn,dsn,eps;
    int i,iter;

    r = s = 0;
    dr = 1.0;
    ds = 0;
    eps = 1e-14;
    iter = 1;

    while ((fabs(dr)+fabs(ds)) > eps) {
        if ((iter % 200) == 0) {
            r=(double)rand()/16000.;
        }
        if ((iter % 500) == 0) {
            eps*=10.0;
            error = true;
        }
        b[1] = a[1] - r;
        c[1] = b[1] - r;

        for (i=2;i<=n;i++){
            b[i] = a[i] - r * b[i-1] - s * b[i-2];
            c[i] = b[i] - r * c[i-1] - s * c[i-2];
        }
        dn=c[n-1] * c[n-3] - c[n-2] * c[n-2];
        drn=b[n] * c[n-3] - b[n-1] * c[n-2];
        dsn=b[n-1] * c[n-1] - b[n] * c[n-2];

        if (fabs(dn) < 1e-16) {
            dn = 1;
            drn = 1;
            dsn = 1;
        }
        dr = drn / dn;
        ds = dsn / dn;

        r += dr;
        s += ds;
        iter++;
    }
    for (i=0;i<n-1;i++)
        a[i] = b[i];
    a[n] = s;
    a[n-1] = r;
}

QVector<Polynomial> Polynomial::findQuads()
{
    QVector<Polynomial> ret;
    Polynomial old(n);
    for(int i=0;i<=n;++i)
        old.setCoef(i,getCoef(i));

    if(degrees[n]==1){
        for(int i=-1000;i<=1000;++i){
            if(i && !((long long)degrees[0]%i) && isNullInPoint((long long)i)){
                QString p = "x";
                if(i<0)
                    p += "+";
                if(i != 0)
                    p += QString::number(i*(-1));
                ret.push_back(Polynomial::toPolynomial(p));
                changeMyself(divide(ret[ret.size()-1]));
                qDebug() << toStringWithoutSups() << ret[ret.size()-1].toStringWithoutSups();
            }
        }
    }

    if(getDeg()==0 && degrees[0]==1){
        changeMyself(old);
        return ret;
    }
    double a[n],b[n],c[n];
    a[0] = degrees[n];
    for(int i=1;i<=n;++i)
        a[i]=degrees[n-i]/a[0];
    a[0]=1.0;
    b[0]=c[0]=1.0;
    int _n = n;
    while(_n>=2) {
        preFindQuads(a,b,c,_n);
        _n-=2;
    }
    for(int i=n;i>=2;i-=2){
        if(fabs(a[i])<EPS)
            a[i]=0.0;
        if(fabs(a[i-1])<EPS)
            a[i-1]=0.0;
        if(a[i-1]*a[i-1]-4*a[i]<-EPS) {
            Polynomial tmp(2);
            tmp.setCoef(2,1.0);
            tmp.setCoef(1,floor(a[i-1]*10000+.5)/10000);
            tmp.setCoef(0,floor(a[i]*10000+.5)/10000);
            ret.push_back(tmp);
            continue;
        }
        if(a[i-1]*a[i-1]-4*a[i]>EPS){
            Polynomial tmp(1);
            double d = a[i-1]*a[i-1]-4*a[i];
            tmp.setCoef(1,1.0);
            double x = -((-a[i-1]-sqrt(d))/2.0);
            tmp.setCoef(0,floor(x*10000+.5)/10000);
            ret.push_back(tmp);
            x = -((-a[i-1]+sqrt(d))/2.0);
            tmp.setCoef(0,floor(x*10000+.5)/10000);
            ret.push_back(tmp);
            continue;
        }
        if(fabs(a[i-1]*a[i-1]-4*a[i])<EPS) {
            Polynomial tmp(1);
            tmp.setCoef(1,1.0);
            a[i-1] = floor(a[i-1]*10000+.5)/10000;
            tmp.setCoef(0,floor(a[i-1]/2.0*10000+.5)/10000);
            ret.push_back(tmp);
            ret.push_back(tmp);
        }
    }
    if(_n != 0) {
        Polynomial tmp(1);
        if(fabs(a[1])<EPS)
            a[1]=0.0;
        tmp.setCoef(1,1.0);
        tmp.setCoef(0,a[1]);
        ret.push_back(tmp);
    }
    changeMyself(old);
    return ret;
}

bool Polynomial::getError()
{
    return error;
}

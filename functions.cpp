#include "functions.h"
#include "fraction.h"
#include "polynomial.h"
#include <QDebug>
#include <algorithm>
#include <cmath>
#include <map>
#define EPS 1e-9

using namespace std;

Functions::Functions()
{
}

int Functions::gcd(int a, int b)
{
    if(!b)
        return a;
    return gcd(b,a%b);
}

double Functions::binPow(double x, int n)
{
    if(n==0)
        return 1.0;
    if(n==1)
        return x;
    if(n%2)
        return Functions::binPow(x,n-1)*x;
    else {
        double tmp = Functions::binPow(x,n/2);
        return tmp*tmp;
    }
}

double Functions::abs(double x)
{
    if(x<0)
        return x*-1;
    return x;
}

int Functions::gauss(QVector<QVector<double> > a, vector<double> &ans)
{
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    QVector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return 9999999;
    return 1;
}

QVector<PolyFraction> Functions::undeterminedCoefficients(PolyFraction main, QVector<Polynomial> vec, QVector<int> degrees, int n)
{
    QVector<PolyFraction> ret;
    QVector<QVector<double> > a(n);
    vector<double> ans;
    for(int i=0;i<n;++i) {
        a[i].resize(n+1);
        a[i].fill(0);
    }
    int coef=0;
    for(int i=0,len=vec.size();i<len;++i) {
        Polynomial tmp,divisor("1");
        for(int j=0;j<degrees[i];++j)
            divisor=divisor.multiply(vec[i]);
        tmp = main.getDenominator().divide(divisor);
        qDebug() << main.getDenominator().toStringWithoutSups();

        if(vec[i].getDeg()==2){
            for(int j=0;j<=tmp.getDeg();++j)
                a[j+1][coef] = tmp.getCoef(j);
            coef++;
        }

        for(int j=0;j<=tmp.getDeg();++j)
            a[j][coef] = tmp.getCoef(j);
        coef++;
    }

    for(int i=0;i<=main.getNumerator().getDeg();++i)
        a[i][coef] = main.getNumerator().getCoef(i);
/*
    for(int i=0;i<n;++i,qDebug()<<"")
        for(int j=0;j<=n;++j)
            qDebug() << a[i][j];
*/

    int numberOfSolutions = Functions::gauss(a,ans);
    if(numberOfSolutions==1) {
        int a=0; // current fraction
        for(int i=0,len=ans.size();i<len;++i) {
            if(vec[a].getDeg()==1) {
                Polynomial tmp(0);
                if(fabs(ans[i])<EPS)
                    ans[i]=0.0;
                tmp.setCoef(0,ans[i]);
                qDebug() << tmp.getCoef(0);

                ret.push_back(PolyFraction::toPolyFraction(tmp,vec[a],degrees[a]));
                a++;
                continue;
            }

            if(vec[a].getDeg()==2) {
                Polynomial tmp(1);
                if(fabs(ans[i])<EPS)
                    ans[i]=0.0;
                if(fabs(ans[i-1])<EPS)
                    ans[i-1]=0.0;
                tmp.setCoef(1,ans[i]);
                tmp.setCoef(0,ans[i+1]);
                ret.push_back(PolyFraction::toPolyFraction(tmp,vec[a],degrees[a]));
                a++;
                i++;
                continue;
            }
        }
    }
    return ret;
}

void Functions::swap(Polynomial &a, Polynomial &b)
{
    Polynomial tmp;
    tmp = a;
    a = b;
    b = tmp;
}

Polynomial Functions::gcd(Polynomial a, Polynomial b)
{
    while(!b.isNull()){
        a = a.mod(b);
        Functions::swap(a,b);
    }
    return a;
}

void Functions::swap(double &a, double &b)
{
    double tmp = a;
    a = b;
    b = tmp;
}

QString Functions::deleteSups(QString str)
{
    if(str[str.size()-1]=='|')
        str = str.mid(0,str.size()-1);
    int pos=0;
    while(pos<str.size())
    {
        if(str[pos]=='<' && str[pos+1]=='s'){
            while(str[pos]!='>')
                str = str.mid(0,pos)+str.mid(pos+1);
            str = str.mid(0,pos)+"^"+str.mid(pos+1);
        }
        if(str[pos]=='<' && str[pos+1]!='s'){
            while(str[pos]!='>')
                str = str.mid(0,pos)+str.mid(pos+1);
            str = str.mid(0,pos)+str.mid(pos+1);
        }
        pos++;
    }
    return str;
}





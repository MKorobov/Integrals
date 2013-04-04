#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>
#include <algorithm>
using namespace std;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void display();
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *ev);
    void timerEvent(QTimerEvent *);
    int lineSizePixels(QString str);

private:
    QLabel *numerator,*denominator,*line,*integral,*diff,*answer;
    bool isActiveNumerator;
    bool isVisibleDenominator;
    bool isS;
};

#endif // WIDGET_H

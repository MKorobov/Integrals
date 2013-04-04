#include "widget.h"
#include "polynomial.h"
#include "functions.h"
#include "integral.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background-color:white;");
    isVisibleDenominator = false;
    isActiveNumerator = true;
    isS=0;

    numerator = new QLabel("<font size=16>");
    numerator->setFixedHeight(50);
    denominator = new QLabel("<font size=16>");
    denominator->setFixedHeight(50);

    integral = new QLabel;
    integral->setPixmap(QPixmap::fromImage(QImage(":/integral.png")));
    diff = new QLabel;
    diff->setPixmap(QPixmap::fromImage(QImage(":/diff.png")));
    answer = new QLabel;
    line = new QLabel;

    startTimer(750);
    display();
}

void Widget::timerEvent(QTimerEvent *)
{
    if(isActiveNumerator){
        if(numerator->text().at(numerator->text().size()-1)=='|')
            numerator->setText(numerator->text().mid(0,numerator->text().size()-1));
        else
            numerator->setText(numerator->text()+"|");
    }
    else {
        if(denominator->text().at(denominator->text().size()-1)=='|')
            denominator->setText(denominator->text().mid(0,denominator->text().size()-1));
        else
            denominator->setText(denominator->text()+"|");
    }
}

Widget::~Widget()
{

}

int Widget::lineSizePixels(QString str)
{
    int ret=0;
    for(int i=14,n=str.size();i<n;++i){
        if(str[i]=='<'){
            if(str[i+1]=='/')
                i+=5;
            else
                i+=4;
        }
        else
            ret++;
    }
    return ret*15;
}

void Widget::mousePressEvent(QMouseEvent *ev)
{
    if(numerator->text().at(numerator->text().size()-1)=='|')
        numerator->setText(numerator->text().mid(0,numerator->text().size()-1));
    if(denominator->text().at(denominator->text().size()-1)=='|')
        denominator->setText(denominator->text().mid(0,denominator->text().size()-1));
    if(ev->y()<line->y()) {
        isActiveNumerator = true;
    }
    else {
        isActiveNumerator = false;
    }
}

void Widget::display()
{
    delete layout();
    QSpacerItem *space1 = new QSpacerItem(100,10);
    QSpacerItem *space2 = new QSpacerItem(100,10);
    QSpacerItem *space3 = new QSpacerItem(10,10);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addSpacerItem(space1);
    hlayout->addWidget(integral);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(numerator);
    if(this->isVisibleDenominator){
        QPixmap lineP(max(lineSizePixels((QString)numerator->text()),lineSizePixels((QString)denominator->text())),2);
        QPainter paint;
        paint.begin(&lineP);
        paint.setBrush(QBrush(Qt::black));
        paint.eraseRect(0,0,1000,1000);
        paint.drawRect(0,0,1000,1000);
        paint.end();
        line->setPixmap(lineP);
        layout->addWidget(line);
        layout->addWidget(denominator);
    }
    hlayout->addLayout(layout);
    hlayout->addSpacerItem(space3);
    hlayout->addWidget(diff);
    hlayout->addSpacerItem(space2);
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(hlayout);
    vlayout->addWidget(answer);
    setLayout(vlayout);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return){

        if(numerator->text() == "<font size=16>"){
            answer->setText("<br><font size=16>No.");
        }
        else {
            if(denominator->text() == "<font size=16>") {
                Polynomial p(Functions::deleteSups(numerator->text()));
                Polynomial q("1");
                qDebug() << p.toStringWithoutSups() << q.toStringWithoutSups();
                answer->setText("<br><font size=16>Answer: "+Integral::notSimpleFunction(p,q,0));
            }
            else {
                qDebug() << Functions::deleteSups(numerator->text()) << Functions::deleteSups(denominator->text());
                Polynomial p(Functions::deleteSups(numerator->text()));
                Polynomial q(Functions::deleteSups(denominator->text()));
                qDebug() << p.toStringWithoutSups() << q.toStringWithoutSups();
                answer->setText("<br><font size=16>Answer: "+Integral::notSimpleFunction(p,q,0));
            }
        }
    }
    if(numerator->text().at(numerator->text().size()-1)=='|')
        numerator->setText(numerator->text().mid(0,numerator->text().size()-1));
    if(denominator->text().at(denominator->text().size()-1)=='|')
        denominator->setText(denominator->text().mid(0,denominator->text().size()-1));
    if(event->key() == 94) {
        if(isActiveNumerator)
            numerator->setText(numerator->text()+"<sup>");
        else
            denominator->setText(denominator->text()+"<sup>");
        isS = true;
        display();
        return;
    }

    if(event->key() == 16777236){
        if(isS) {
            if(isActiveNumerator)
                numerator->setText(numerator->text()+"</sup>");
            else
                denominator->setText(denominator->text()+"</sup>");
            isS = false;
        }
        display();
        return;
    }

    if(event->key() == 16777219){
        if(isActiveNumerator) {
            if(numerator->text().at(numerator->text().size()-1)=='>')
                numerator->setText(numerator->text().mid(0,numerator->text().size()-5-(int)!isS));
            else
                numerator->setText(numerator->text().mid(0,numerator->text().size()-1));
        }
        else {
            if(denominator->text().at(denominator->text().size()-1)=='>')
                denominator->setText(denominator->text().mid(0,denominator->text().size()-5-(int)!isS));
            else
                denominator->setText(denominator->text().mid(0,denominator->text().size()-1));
        }
    }

    if(event->key() == 88 && !isS) {
        if(isActiveNumerator)
            numerator->setText(numerator->text()+'x');
        else
            denominator->setText(denominator->text()+'x');
    }
    if(event->key()<='9' && event->key()>='0') {
        if(isActiveNumerator)
            numerator->setText(numerator->text()+char(event->key()));
        else
            denominator->setText(denominator->text()+char(event->key()));
    }
    if((event->key() == '+' || event->key() == '-') && !isS) {
        if(isActiveNumerator)
            numerator->setText(numerator->text()+char(event->key()));
        else
            denominator->setText(denominator->text()+char(event->key()));
    }
    if(event->key() == '/'){
        isVisibleDenominator = true;
        isActiveNumerator = false;
    }
    display();
}

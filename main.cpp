#include "widget.h"
#include "functions.h"
#include "fraction.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("CAS.Integrals v1.0a 19/03/2013");
    w.show();
    return a.exec();
}

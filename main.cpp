#include <QApplication>

#include "calculatorwindow.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);

    CalculatorWindow cal;
    cal.show();

    return app.exec();
}


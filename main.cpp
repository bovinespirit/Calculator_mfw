#include <QApplication>
#include <QFile>

#include "calculatorwindow.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);

    QFile file(":style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);

    CalculatorWindow cal;
    cal.show();

    return app.exec();
}


#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QWidget>
#include "calculate.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QLabel;
QT_END_NAMESPACE

class CalculatorWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CalculatorWindow(QWidget *parent = 0);
    
signals:
    
private slots:
    void buttonPressed();
    void execute();
    void calculationDone(const QString& result);

private:
    QLabel *history;
    QLineEdit *display;
    QPushButton *digitButtons[10];

    Calculate thread;
};

#endif // CALCULATORWINDOW_H

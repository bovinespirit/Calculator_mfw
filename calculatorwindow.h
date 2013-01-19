#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QLabel;
class QVBoxLayout;
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
    void calculationDone();

private:
    QVBoxLayout *history;
    QLineEdit *display;
    QPushButton *digitButtons[10];
};

#endif // CALCULATORWINDOW_H

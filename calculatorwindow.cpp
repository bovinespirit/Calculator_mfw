#include <QtGui>
#include <math.h>

#include "calculatorwindow.h"

struct operandData {
    QString str;
    int x;
    int y;
};

CalculatorWindow::CalculatorWindow(QWidget *parent) :
    QWidget(parent)
{
    int i;
    QPushButton *button;
    static const int numOperands = 6;
    static const operandData operands[numOperands] =
    {{"+", 0, 3}, {"-", 0, 4}, {"*", 0, 5}, {"/", 0, 6}, {".", 1, 6}, {"0", 2, 6}};

    QGridLayout *glayout = new QGridLayout;

    for(i = 0; i < 9; ++i) {
        digitButtons[i] = new QPushButton(QString::number(i + 1));
        connect(digitButtons[i], SIGNAL(clicked()), this, SLOT(buttonPressed()));
        glayout->addWidget(digitButtons[i], 5 - (i / 3), (i % 3) + 1, 1, 1);
    }

    for(i = 0; i < numOperands; ++i) {
        const operandData d = operands[i];
        button = new QPushButton(d.str);
        connect(button, SIGNAL(clicked()), this, SLOT(buttonPressed()));
        glayout->addWidget(button, d.y, d.x);
    }

    button = new QPushButton("=");
    connect(button, SIGNAL(clicked()), this, SLOT(execute()));
    glayout -> addWidget(button, 6, 3);

    display = new QLineEdit("");
    glayout -> addWidget(display, 2, 0, 1, 4);

    history = new QLabel("test label");
    history -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    history -> setFrameStyle(QFrame::StyledPanel);
    glayout -> addWidget(history, 0, 0, 2, 4);

    connect(&thread, SIGNAL(haveAnswer(QString)), this, SLOT(calculationDone(QString)));

    setLayout(glayout);
    setWindowTitle(tr("Calculator"));
}

void CalculatorWindow::buttonPressed() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    display->setText(display->text() + button -> text());
}

void CalculatorWindow::execute() {
    const QString& txt(display->text());
    if (txt != "") {
        thread.setupCalculation(txt);
        display->setText("");
    }
}

void CalculatorWindow::calculationDone(const QString& result) {
    history -> setText(history->text() + "\n" + result);
}


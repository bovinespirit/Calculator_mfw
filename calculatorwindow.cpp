#include <QtGui>
#include <math.h>

#include "historyitem.h"
#include "calculatorwindow.h"
#include "calculate.h"

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
        {{"+", 0, 3}, {"-", 0, 4}, {"*", 0, 5}, {"/", 0, 6}, {".", 1, 6},
         {"0", 2, 6}};

    QGridLayout *glayout = new QGridLayout;

    for(i = 0; i < 9; ++i) {
        digitButtons[i] = new QPushButton(QString::number(i + 1));
        connect(digitButtons[i], SIGNAL(clicked()),
                this, SLOT(buttonPressed()));
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
    display -> setObjectName("display");
    display -> setReadOnly(true);
    display -> setMaxLength(12);
    display -> setPlaceholderText("0");
    glayout -> addWidget(display, 2, 0, 1, 4);

    historyArea = new QScrollArea;
    historyArea -> setContentsMargins(0, 0, 0, 0);
    historyArea -> setWidgetResizable(true);

    QFrame* gb = new QFrame();
    gb -> setObjectName("historyFrame");
    gb -> setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
    gb -> setContentsMargins(0, 0, 0, 0);

    history = new QVBoxLayout();
    history -> setSpacing(0);
    history -> setSizeConstraint(QLayout::SetMinAndMaxSize);
    gb -> setLayout(history);

    historyArea -> setWidget(gb); // This needs to happen after setLayout()
    glayout -> addWidget(historyArea, 0, 0, 2, 4);

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
        Calculate *thread = new Calculate();
        HistoryItem *lbl = new HistoryItem(txt);
        history -> addWidget(lbl);
        connect(thread, SIGNAL(haveAnswer(QString)),
                lbl, SLOT(showResult(QString)));
        connect(thread, SIGNAL(haveAnswer(QString)),
                this, SLOT(calculationDone()));
        thread -> setupCalculation(txt);
        display -> setText("");
        QScrollBar * const vs = historyArea -> verticalScrollBar();
        vs -> setValue(vs -> maximum());
    }
}

void CalculatorWindow::calculationDone() {
    sender() -> disconnect();
    delete sender();
}

void CalculatorWindow::keyPressEvent(QKeyEvent *ke) {
    switch (ke -> key()) {
    case Qt::Key_Equal:
    case Qt::Key_Enter:
    case Qt::Key_Return:
        execute();
        break;
    case Qt::Key_Minus:
    case Qt::Key_Plus:
    case Qt::Key_multiply:
    case Qt::Key_Asterisk:
    case Qt::Key_division:
    case Qt::Key_Slash:
    case Qt::Key_0:
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
        display->setText(display->text() + (ke -> text()));
        break;
    default:
        QWidget::keyPressEvent(ke);
    }
}

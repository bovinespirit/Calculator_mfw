#include "historyitem.h"

HistoryItem::HistoryItem(const QString& str, QWidget *parent) :
    QLabel(parent), waiting(true)
{
    setAutoFillBackground(true);
    // List of possible colours:
    // http://www.w3.org/TR/SVG/types.html#ColorKeywords
    setStyleSheet("QLabel { color: grey; }");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setText(str);
}

void HistoryItem::showResult(const QString &result) {
    setStyleSheet("QLabel { color: black;\n }");
    waiting = false;
    setText(result);
}

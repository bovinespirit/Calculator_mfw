#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include <QLabel>

class HistoryItem : public QLabel
{
    Q_OBJECT
public:
    explicit HistoryItem(const QString& str, QWidget *parent = 0);
    
signals:
    
public slots:
    void showResult(const QString& result);
private:
    bool waiting;
};

#endif // HISTORYITEM_H

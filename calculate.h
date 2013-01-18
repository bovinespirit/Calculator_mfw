#ifndef CALCULATE_H
#define CALCULATE_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class Calculate : public QThread
{
    Q_OBJECT
public:
    explicit Calculate(QObject *parent = 0);
    ~Calculate();
    
signals:
    void haveAnswer(const QString &str);

public slots:
    void setupCalculation(const QString &query);

protected:
    void run();

private:
    QMutex mutex;
    QWaitCondition condition;
    bool abort;

    QString query;

    void sleep(unsigned long sleepMs);
};

#endif // CALCULATE_H

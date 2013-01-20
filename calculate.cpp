#include "calculate.h"
#include <QtScript>

Calculate::Calculate(QObject *parent) :
    QThread(parent),
    abort(false) {}

Calculate::~Calculate() {
    mutex.lock();
    abort = true;
    condition.wakeOne();
    mutex.unlock();

    wait();
}

void Calculate::setupCalculation(const QString &query) {
    QMutexLocker locker(&mutex);

    if (!isRunning()) {
        this -> query = query;
        start(LowPriority);
    }
}

void Calculate::run() {
    mutex.lock();
    const QString q = query;
    mutex.unlock();

    QScriptEngine engine;
    QScriptValue result;
    QString op;

    sleep(1000);
    result = engine.evaluate(q);

    if (result.isNumber())
        op = query + " = " + result.toString();
    else
        op = "Error!";

    emit haveAnswer(op);
}

void Calculate::sleep(unsigned long sleepMs) {
        condition.wait(&mutex, sleepMs);
    }

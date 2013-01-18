#include "calculate.h"

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

    sleep(1000);

    emit haveAnswer("Done!");
}

void Calculate::sleep(unsigned long sleepMs) {
        condition.wait(&mutex, sleepMs);
    }

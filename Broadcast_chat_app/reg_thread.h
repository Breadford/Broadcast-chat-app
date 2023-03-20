#ifndef REG_THREAD_H
#define REG_THREAD_H

#include <QObject>
#include <QThread>
#include <iostream>
using namespace std;

class reg_thread : public QThread
{
    Q_OBJECT
public:
    reg_thread();
private:
    void run();
signals:
    void binterupt();
public slots:
};

#endif // REG_THREAD_H

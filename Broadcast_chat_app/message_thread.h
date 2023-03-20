#ifndef MESSAGE_THREAD_H
#define MESSAGE_THREAD_H

#include <QObject>
#include <QThread>
#include <iostream>
using namespace std;

class message_thread : public QThread
{
    Q_OBJECT
public:
    message_thread();
private:
    void run();
signals:
    void enter_message();
};

#endif // MESSAGE_THREAD_H

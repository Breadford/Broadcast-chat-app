#ifndef BE_SERVICE_H
#define BE_SERVICE_H

#include <QObject>
#include <QThread>
#include <iostream>
using namespace std;


class be_service : public QThread
{
    Q_OBJECT
public:
    be_service();
private:
    void run();
signals:
    void binterupt();
public slots:
};

#endif // BE_SERVICE_H

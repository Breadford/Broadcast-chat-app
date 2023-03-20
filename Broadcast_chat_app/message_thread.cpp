#include "message_thread.h"

message_thread::message_thread()
{

}

void message_thread::run(){
    while (1) {
        QThread::msleep(500);
        emit enter_message();

    }
}

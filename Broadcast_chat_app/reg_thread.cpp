#include "reg_thread.h"

reg_thread::reg_thread()
{

}
void reg_thread::run(){
    while(1){
        QThread::msleep(500);
        emit binterupt();
    }
}

#include "be_service.h"

be_service::be_service()
{

}
void be_service::run(){
    while(1){
        QThread::msleep(500);
        emit binterupt();
    }

}

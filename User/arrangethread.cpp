#include "arrangeThread.h"
#include <head.h>
#include <QDebug>
#include "DataStruct.h"

arrangeThread::arrangeThread(QObject* par) : QThread(par)
{}

arrangeThread::~arrangeThread()
{}

void arrangeThread::run()
{
    clientConnector.startClient();

    int count;
    m_isCanRun=true;
    while(1)
    {
        count=0;
        qDebug()<<"send";
        QMutexLocker locker(&m_lock);
        if(!m_isCanRun)
        {
            qDebug()<<"close";
            return;
        }

        //发包
        DataStruct message;
        message.kind=_query_reservation;//数据包类型为查询预约
        message.customer_id=password;
        message.name=username;
        clientConnector.sendMessage(message);
        //收包
        //改history

        qDebug()<<"end_send";

        DataStruct data;
        while(clientConnector.getMessage(data)==0)
        {
            count++;
            sleep(1);
            if(count>5)break;
        }

        if(count>5)break;

        history.clear();

        //-----测试
        history=data.result;
        //-----测试

        sleep(0.1);
        emit send("");
        qDebug()<<"send_done";
    }


}
void arrangeThread::stopImmediately()
{
    QMutexLocker locker(&m_lock);
    m_isCanRun = false;
}
void arrangeThread::setID(string name, string pass)
{
    username=name;
    password=pass;
}

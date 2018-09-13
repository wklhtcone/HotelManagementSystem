#include "chooseThread.h"
#include <head.h>
#include <QDebug>
#include "DataStruct.h"
chooseThread::chooseThread(QObject* par) : QThread(par)
{}

chooseThread::~chooseThread()
{}

void chooseThread::run()
{
    clientConnector.startClient();

    string temp;
    m_isCanRun=true;
    while(1)
    {  
        count=0;
        QMutexLocker locker(&m_lock);
        if(!m_isCanRun)
        {
            qDebug()<<"close";
            return;
        }

        //发包
        DataStruct message;
        message.kind=_time_query;//发送数据包查询房间
        temp=startd.toString("yyyy-MM-dd").toStdString();
        message.start_time=temp;
        temp=endd.toString("yyyy-MM-dd").toStdString();
        message.end_time=temp;        
        clientConnector.sendMessage(message);

        qDebug()<<startd.toString("yyyy-MM-dd");

        qDebug()<<"send";
        //收包
        //改roomnums
        DataStruct data;
        while(!clientConnector.getMessage(data)||data.kind!=_time_query)
        {
            count++;
            sleep(1);
            if(count>5)break;
        }

        if(count>5)break;

        qDebug()<<count<<"x";
        qDebug()<<data.result.size()<<"b";
        qDebug()<<data.result[0].size()<<"w";

        roomNums[0]=QString::fromStdString(data.result[0][1]).toInt();
        roomNums[1]=QString::fromStdString(data.result[2][1]).toInt();
        roomNums[2]=QString::fromStdString(data.result[1][1]).toInt();
        roomNums[3]=QString::fromStdString(data.result[3][1]).toInt();

        roomPrices[0]=QString::fromStdString(data.result[0][2]).toInt();
        roomPrices[1]=QString::fromStdString(data.result[2][2]).toInt();
        roomPrices[2]=QString::fromStdString(data.result[1][2]).toInt();
        roomPrices[3]=QString::fromStdString(data.result[3][2]).toInt();

        sleep(0.1);

        emit send(count);

        qDebug()<<"send_done";
    }


}
void chooseThread::stopImmediately()
{
    QMutexLocker locker(&m_lock);
    m_isCanRun = false;
}
void chooseThread::setDate(QDate a, QDate b)
{
    startd=a;
    endd=b;
}

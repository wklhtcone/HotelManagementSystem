//
//  main.cpp
//  HMS
//
//  Created by zhouyuxiang on 2018/7/12.
//  Copyright ? 2018Äê zhouyuxiang. All rights reserved.
//

#include <QCoreApplication>
#include <iostream>
#include "DataStruct.h"
#include "Function.hpp"
#include "Function_front.hpp"
#include <QDebug>

ServerConnector serverConnector;
SQL_ODBC sql;

int main(int argc, char * argv[]) {

    QCoreApplication a(argc, argv);

    if(!serverConnector.startServer())
    {
        //server start failed
    }
    else
    {
        //server start successful
    }

    if(!sql.initSQL("Hotel","IbukiAlice",""))
    {
        //database connect failed
    }
    else
    {
        //database connect successful
    }

    sql.changeDebugMode(1);

    DataStruct message;
    while(1){
        int Client;
        if(serverConnector.getMessage(message,Client)){
            handle_message_client(message,Client);
            handle_message_front(message,Client);
        }
    }
    return a.exec();
}

bool cmpDataString(string threeBitStr,char *twoBitStr)
{
    if(0==QString::compare(QString::fromStdString(threeBitStr),QString::fromLocal8Bit(twoBitStr)))
    {
        return true;
    }
    return false;
}

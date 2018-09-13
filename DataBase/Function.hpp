//
//  Function.hpp
//  HMS
//
//  Created by zhouyuxiang on 2018/7/13.
//  Copyright ? 2018年 zhouyuxiang. All rights reserved.
//

#ifndef Function_hpp
#define Function_hpp

#include <stdio.h>
#include "DataStruct.h"
#include "sql_odbc.h"
#include "ServerConnector.h"
#include <string>

extern ServerConnector serverConnector;
extern SQL_ODBC sql;

using namespace std;

extern bool cmpDataString(string threeBitStr,char *twoBitStr);

void handle_message_client(DataStruct  message,int Client);//处理客户机请求

void handle_query(DataStruct message,int clientNumber);//查询时间段内空余的房间

void handle_reservation(DataStruct message,int clientNumber);//处理预约请求

void handle_cancel(DataStruct message,int clientNumber);//取消预约功能

void handle_stay_over(DataStruct message,int clientNumber);//续住功能

void handle_reservation_query(DataStruct message,int clientNumber);//查看预约信息

time_t convert(int year, int month, int day);//时间转换

int get_days(const char* from, const char* to);//获取天数

int get_total_price(DataStruct  message);//计算总价

string getTime(); //获取当前时间并格式化转换为字符串

void handle_total_price(DataStruct message, int clientNumber);//用户确认预定、入住前需要返回总价格

#endif /* Function_hpp */

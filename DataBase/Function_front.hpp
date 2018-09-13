//
//  Function_front.hpp
//  HMS
//
//  Created by zhouyuxiang on 2018/7/15.
//  Copyright ? 2018年 zhouyuxiang. All rights reserved.
//

#ifndef Function_front_hpp
#define Function_front_hpp

#include <stdio.h>
#include "DataStruct.h"
#include "Server.h"
#include "sql_odbc.h"
#include <vector>
#include <string>

using namespace std;

void handle_message_front(DataStruct message,int Client);//前台处理函数

void handle_reserved_check_in(DataStruct message, int clientNum);//办理预约入住

void handle_directly_check_in(DataStruct message, int clientNum);//办理直接入住

void handle_check_out(DataStruct message,int clientNumber);//办理退房

void handle_room_query(int clientNumber);//查询所有房间状态

void handle_room_info(DataStruct message,int clientNumber);//查询具体房间信息

//void handle_room_check_in(DataStruct message,int clientNumber);//具体房间的入住功能

//void handle_room_reservation(DataStruct message,int clientNumber);//具体房间的预约功能

void handle_client_reserverd(DataStruct message,int clientNumber); //处理入住请求

void handle_stay_over_info(DataStruct message,int clientNumber);

void handle_register(DataStruct message,int Client);//查询登陆信息
#endif /* Function_front_hpp */

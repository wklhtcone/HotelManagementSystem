//
//  Function_front.cpp
//  HMS
//
//  Created by zhouyuxiang on 2018/7/15.
//  Copyright ? 2018年 zhouyuxiang. All rights reserved.
//

#include "Function_front.hpp"
#include "Function.hpp"
#include <QDebug>


void handle_message_front(DataStruct message,int Client){//处理前台数据包
    switch (message.kind) {
        case _check_in_directly://办理入住功能
            handle_directly_check_in(message, Client);
            break;
        case _check_in_reserverd://办理已预约用户入住功能
            handle_reserved_check_in(message,Client);
            break;
        case _check_out://办理退房
            handle_check_out(message, Client);
            break;
        case _room_query://查询所有房间
            handle_room_query(Client);
            break;
        case _room_info_query://查询房间信息
            handle_room_info(message, Client);
            break;
        /*case _room_check_in://具体房间入住
            handle_room_check_in(message, Client);
            break;
        case _room_reservation://具体房间预约
            handle_room_reservation(message, Client);
            break;*/
        case _check_in_query://处理入住请求
            handle_client_reserverd(message,Client);
            break;
        case _stay_over_info://查询续住信息
            handle_stay_over_info(message,Client);
            break;
        case _register://查询登陆信息
            handle_register(message,Client);
            break;
    }
}

void handle_register(DataStruct message,int Client){//查询登陆信息
     string sql_sentence="select * from employee where employee_id='"+message.name+"' and password='"+message.customer_id+"'";
     vector<vector<string>> result;
     sql.sql(sql_sentence,result);
     DataStruct ack;
     ack.kind=_register;
     if(result.size()==1){
         ack.isSucceed=1;
     }else ack.isSucceed=0;
     serverConnector.sendMessage(ack,Client);
}


void handle_stay_over_info(DataStruct message,int Client){
    sql.beginTran();
    string sql_sentence="select dateadd(day,"+to_string(message.day)+",end_time),unit_price from check_in join customer on customer.customer_id=check_in.customer_id and customer.start_time=check_in.start_time join room on room.room_id=check_in.room_id where customer.customer_id='"+message.customer_id+"'and flag=1 and name='"+message.name+"'";
    vector<vector<string>> result;
    //qDebug()<<QString::fromStdString(sql_sentence);
    sql.sql(sql_sentence, result);//查询是否入住
    sql.commitTran();
    if(result.size()==0){//当前未办理入住，办理续住失败
        DataStruct fail;
        fail.kind=_stay_over_info;
        fail.isSucceed=0;
        serverConnector.sendMessage(fail,Client);
    }else{
        DataStruct ack;
        ack.kind=_stay_over_info;
        ack.isSucceed=1;
        ack.end_time=result[0][0];
        ack.price=to_string(message.day*stoi(result[0][1]));
        serverConnector.sendMessage(ack,Client);
    }
}

void handle_client_reserverd(DataStruct message,int clientNumber){//处理入住请求
    string now=getTime();//获取当前日期
    string sql_sentence="select room.room_id,customer.start_time,end_time,room_type  from customer join check_in on customer.customer_id=check_in.customer_id and customer.start_time=check_in.start_time join room on room.room_id=check_in.room_id where customer.customer_id='"+message.customer_id+"' and name='"+message.name+"' and customer.start_time<='"+now+"' and end_time>='"+now+"'"+"and flag=0";
    //qDebug()<<QString::fromStdString(sql_sentence);
    vector<vector<string>> result;
    sql.sql(sql_sentence,result);//
    DataStruct ack;
    if(result.size()==0){
        ack.kind=_check_in_query;
        ack.isSucceed=0;
        serverConnector.sendMessage(ack,clientNumber);
    }else {
        ack.isSucceed=1;
        ack.kind=_check_in_query;//
        ack.room_id=result[0][0];
        ack.start_time=result[0][1];
        ack.end_time=result[0][2];
        ack.room_type=result[0][3];
        serverConnector.sendMessage(ack,clientNumber);
    }
}

void handle_room_check_in(DataStruct message, int clientNumber) {//具体房间的入住功能
    
    int is_legal = 1;
    sql.beginTran();
    string str0 = "select start_time from check_in where customer_id =";
    string str1 = "select start_time from check_in where room_id =";
    string statement0 = str0;
    string statement1 = str1;
    
    if ((message.room_type=="大床房") || (message.room_type=="双人间")) {//此种情况需要两个人的customer_id，进行分割
        int location = 0;
        for (location = 0; message.customer_id[location] != ','; location++);
        string result1 = message.customer_id.substr(0, location);
        statement0 += "'" + result1 + "'";
    }
    else
        statement0 += "'" + message.customer_id + "'";//语句0用于排除这个顾客入住时间和预约时间重叠的情况
    statement1 += "'" + message.room_id + "'";        //语句1用于排除这个房间入住时间和预约时间重叠的情况
    
    vector<vector<string>> reserve_info_1, reserve_info_2;
    sql.sql(statement0, reserve_info_1);
    sql.sql(statement0, reserve_info_2);
    
    
    if (reserve_info_1.size() != 0) {
        int i = 0;
        int j = reserve_info_1.size();
        
        DataStruct ack;
        for (i = 0; i < j; i++) {
            if (message.end_time >= reserve_info_1[i][0]) {
                is_legal = 0;//入住的时间和此顾客已预约的某段时间重合，不合法，拒绝请求
                sql.commitTran();
                ack.kind=_room_check_in;
                ack.isSucceed=false;
                serverConnector.sendMessage(ack, clientNumber);

                return;
            }
        }
    }
    
    if (reserve_info_2.size() != 0) {
        int i = 0;
        int j = reserve_info_2.size();
        
        DataStruct ack;
        for (i = 0; i < j; i++) {
            if (message.end_time >= reserve_info_2[i][0]) {
                is_legal = 0;//入住的时间和此房间已预约的某段时间重合，不合法，拒绝请求
                sql.commitTran();
                ack.kind=_room_check_in;
                ack.isSucceed=false;
                serverConnector.sendMessage(ack, clientNumber);

                return;
            }
        }
    }
    
    //可以在此房间号入住
    if (is_legal == 1) {
        if ((message.room_type=="大床房") || (message.room_type=="双人间")) {//需要两个人的信息
            int location = 0;
            for (location = 0; message.customer_id[location] != ','; location++);
            string id1 = message.customer_id.substr(0, location);
            string id2 = message.customer_id.substr(location + 1);
            
            for (location = 0; message.name[location] != ','; location++);
            string name1 = message.name.substr(0, location);
            string name2 = message.name.substr(location + 1);
            
            //写customer表
            string str6 = "('" + id1 + "','" + name1 + "','" + message.start_time + "','" + message.end_time + "')";
            string statement1 = "insert into customer values" + str6;
            sql.sql(statement1);
            
            str6 = "('" + id2 + "','" + name2 + "','" + message.start_time + "','" + message.end_time + "')";
            statement1 = "insert into customer values" + str6;
            sql.sql(statement1);
            
            //写check_in表
            int price_temp = get_total_price(message);
            string total_price = std::to_string(price_temp);
            string str7 = "('" + id1 + "','" + message.start_time + "','" + message.room_id + "','" + total_price + "','" + "1" + "')";//check_in表的flag：0代表只预约未入住，1代表已入住
            string statement2 = "insert into check_in values" + str7;
            sql.sql(statement2);
            
            str7 = "('" + id2 + "','" + message.start_time + "','" + message.room_id + "','" + total_price + "','" + "1" + "')";//check_in表的flag：0代表只预约未入住，1代表已入住
            statement2 = "insert into check_in values" + str7;
            sql.sql(statement2);
            
            
            //写check_in_log表
            string str8 = "('" + message.room_id + "','" + id1 + "','" + name1 + "','" + message.start_time + "','1990-01-01')";
            string statement3 = "insert into check_in_log values" + str8;
            sql.sql(statement3);
            
            str8 = "('" + message.room_id + "','" + id2 + "','" + name2 + "','" + message.start_time + "','1990-01-01')";
            statement3 = "insert into check_in_log values" + str8;
            sql.sql(statement3);
            
            
        }
        else {//只需要一个人的信息
            
            //写customer表
            string str6 = "('" + message.customer_id + "','" + message.name + "','" + message.start_time + "','" + message.end_time + "')";
            string statement1 = "insert into customer values" + str6;
            sql.sql(statement1);
            
            //写check_in表
            int price_temp = get_total_price(message);
            string total_price = std::to_string(price_temp);
            string str7 = "('" + message.customer_id + "','" + message.start_time + "','" + message.room_id + "','" + total_price + "','" + "1" + "')";//check_in表的flag：0代表只预约未入住，1代表已入住
            string statement2 = "insert into check_in values" + str7;
            sql.sql(statement2);
            
            //写check_in_log表
            string str8 = "('" + message.room_id + "','" + message.customer_id + "','" + message.name + "','" + message.start_time+ "','1990-01-01')";
            string statement3 = "insert into check_in_log values" + str8;
            sql.sql(statement3);
        }
        int price_temp = get_total_price(message);
        sql.commitTran();
        DataStruct ack;
        ack.kind=_room_check_in;
        ack.isSucceed = true;
        ack.price = price_temp;
        qDebug()<<"Send room_check_in:"<<serverConnector.sendMessage(ack, clientNumber);//有用的信息存在属性price中，告诉前端（客户）他选的房间类型对应的分配到的房间号以及这几天的总价格

    }
}

void handle_room_reservation(DataStruct message, int clientNumber) {//具体房间的预约功能
    
    int is_legal = 1;
    sql.beginTran();
    string str0 = "select start_time,end_time from customer where customer_id =";
    string str1 = "select customer.start_time, end_time from check_in join customer on check_in.customer_id = customer.customer_id and check_in.start_time = customer.start_time where room_id =";
    string statement0 = str0;
    string statement1 = str1;
    
    if ((message.room_type=="大床房") || (message.room_type=="双人间")) {//此种情况需要两个人的customer_id，进行分割
        int location = 0;
        for (location = 0; message.customer_id[location] != ','; location++);
        string result1 = message.customer_id.substr(0, location);
        statement0 += "'" + result1 + "'";
    }
    else
        statement0 += "'" + message.customer_id + "'";//语句0用于排除这个顾客入住时间和预约时间重叠的情况
    statement1 += "'" + message.room_id + "'";        //语句1用于排除这个房间入住时间和预约时间重叠的情况
    
    vector<vector<string>> reserve_info_1, reserve_info_2;
    sql.sql(statement0, reserve_info_1);
    sql.sql(statement0, reserve_info_2);
    
    
    if (reserve_info_1.size() != 0) {
        int i = 0;
        int j = reserve_info_1.size();
        
        DataStruct ack;
        for (i = 0; i < j; i++) {
            if ((message.start_time >= reserve_info_1[i][0] && message.start_time <= reserve_info_1[i][1]) || (message.end_time >= reserve_info_1[i][0] && message.end_time <= reserve_info_1[i][1]) || (message.end_time >= reserve_info_1[i][1] && message.start_time <= reserve_info_1[i][0])|| (message.end_time <= reserve_info_1[i][1] && message.start_time >= reserve_info_1[i][0])) {
                is_legal = 0;//入住的时间和此顾客已预约的某段时间重合，不合法，拒绝请求
                sql.commitTran();
                ack.kind=_room_reservation;
                ack.isSucceed=false;
                serverConnector.sendMessage(ack, clientNumber);

                return;
            }
        }
    }
    
    if (reserve_info_2.size() != 0) {
        int i = 0;
        int j = reserve_info_2.size();
        
        DataStruct ack;
        for (i = 0; i < j; i++) {
            if ((message.start_time >= reserve_info_2[i][0] && message.start_time <= reserve_info_2[i][1]) || (message.end_time >= reserve_info_2[i][0] && message.end_time <= reserve_info_2[i][1]) || (message.end_time >= reserve_info_2[i][1] && message.start_time <= reserve_info_2[i][0]) || (message.end_time <= reserve_info_2[i][1] && message.start_time >= reserve_info_2[i][0])) {
                is_legal = 0;//入住的时间和此房间已预约的某段时间重合，不合法，拒绝请求
                sql.commitTran();
                ack.kind=_room_reservation;
                ack.isSucceed=false;
                serverConnector.sendMessage(ack, clientNumber);

                return;
            }
        }
    }
    
    //可以在此房间号入住
    if (is_legal == 1) {
        if ((message.room_type=="大床房") || (message.room_type=="双人间")) {//需要两个人的信息
            int location = 0;
            for (location = 0; message.customer_id[location] != ','; location++);
            string id1 = message.customer_id.substr(0, location);
            string id2 = message.customer_id.substr(location + 1);
            
            for (location = 0; message.name[location] != ','; location++);
            string name1 = message.name.substr(0, location);
            string name2 = message.name.substr(location + 1);
            
            //写customer表
            string str6 = "('" + id1 + "','" + name1 + "','" + message.start_time + "','" + message.end_time + "')";
            string statement1 = "insert into customer values" + str6;
            sql.sql(statement1);
            
            str6 = "('" + id2 + "','" + name2 + "','" + message.start_time + "','" + message.end_time + "')";
            statement1 = "insert into customer values" + str6;
            sql.sql(statement1);
            
            //写check_in表
            int price_temp = get_total_price(message);
            string total_price = std::to_string(price_temp);
            string str7 = "('" + id1 + "','" + message.start_time + "','" + message.room_id + "','" + total_price + "','" + "0" + "')";//check_in表的flag：0代表只预约未入住，1代表已入住
            string statement2 = "insert into check_in values" + str7;
            sql.sql(statement2);
            
            str7 = "('" + id2 + "','" + message.start_time + "','" + message.room_id + "','" + total_price + "','" + "0" + "')";//check_in表的flag：0代表只预约未入住，1代表已入住
            statement2 = "insert into check_in values" + str7;
            sql.sql(statement2);
            
            
            //写reservation_log表
            string str8 = "('" + message.room_id + "','" + id1 + "','" + name1 + "','" + message.start_time + "','" + message.end_time + "','" + "1" + "','" + message.now_time + "')";//reservation_log表的flag：1代表创建预约，0代表取消预约。
            string statement3 = "insert into reservation_log values" + str8;
            sql.sql(statement3);
            
            str8 = "('" + message.room_id + "','" + id2 + "','" + name2 + "','" + message.start_time + "','" + message.end_time + "','" + "1" + "','" + message.now_time + "')";//reservation_log表的flag：1代表创建预约，0代表取消预约。
            statement3 = "insert into reservation_log values" + str8;
            sql.sql(statement3);
            
        }
        else {//只需要一个人的信息
            
            //写customer表
            string str6 = "('" + message.customer_id + "','" + message.name + "','" + message.start_time + "','" + message.end_time + "')";
            string statement1 = "insert into customer values" + str6;
            sql.sql(statement1);
            
            
            //写check_in表
            int price_temp = get_total_price(message);
            string total_price = std::to_string(price_temp);
            string str7 = "('" + message.customer_id + "','" + message.start_time + "','" + message.room_id + "','" + total_price + "','" + "0" + "')";//check_in表的flag：0代表只预约未入住，1代表已入住
            string statement2 = "insert into check_in values" + str7;
            sql.sql(statement2);
            
            
            //写reservation_log表
            string str8 = "('" + message.room_id + "','" + message.customer_id + "','" + message.name + "','" + message.start_time + "','" + message.end_time + "','" + "1" + "','" + message.now_time + "')";//reservation_log表的flag：1代表创建预约，0代表取消预约。
            string statement3 = "insert into reservation_log values" + str8;
            sql.sql(statement3);
        }
        int price_temp = get_total_price(message);
        sql.commitTran();
        DataStruct ack;
        ack.kind=_room_reservation;
        ack.isSucceed = true;
        ack.price = price_temp;
        qDebug()<<"Send room_resevation:"<<serverConnector.sendMessage(ack, clientNumber);//有用的信息存在属性price中，告诉前端（客户）这几天的总价格
        
    }
    
}

void handle_directly_check_in(DataStruct message, int clientNum) {//办理直接入住功能
    //直接入住
    int is_legal = 1;
    sql.beginTran();
    string str0 = "select start_time, end_time from customer where customer_id =";
    string statement0 = str0;
    
    if ((message.room_type=="大床房") || (message.room_type=="双人间")) {//此种情况需要两个人的customer_id，进行分割
        int location = 0;
        for (location = 0; message.customer_id[location] != ','; location++);
        string result1 = message.customer_id.substr(0, location);
        statement0 += "'" + result1 + "'";
    }
    else
        statement0 += "'" + message.customer_id + "'";
    
    vector<vector<string>> reserve_info;
    sql.sql(statement0, reserve_info);
    
    if (reserve_info.size() != 0) {
        int i = 0;
        int j = reserve_info.size();
        
        DataStruct ack;
        for (i = 0; i < j; i++) {
            if (message.end_time >=reserve_info[i][0]){
                is_legal = 0;//要入住的时间和已预约的某段时间重合，不合法，拒绝请求

                ack.kind=_check_in_directly;
                ack.isSucceed=false;
                serverConnector.sendMessage(ack, clientNum);
                sql.commitTran();
                return;
            }
        }
    }
    
    if (reserve_info.size() == 0 || is_legal == 1) {
        string str1 = "select room_id from room where room_id in";
        string str2 = "(select room.room_id from(check_in join customer on check_in.customer_id = customer.customer_id) right join room on check_in.room_id = room.room_id ";
        string str3 = "where customer.start_time is null OR customer.start_time>";
        string str4 = "'" + message.end_time + "'" + "OR customer.end_time<";
        string str5 = "'" + message.start_time + "')" + "AND room_type =" + "'" + message.room_type + "'";
        string statement = str1 + str2 + str3 + str4 + str5;
        
        vector<vector<string>> available_room_id;
        sql.sql(statement, available_room_id);
        message.room_id = available_room_id[0][0];//一共n行一列，选第一行的那个作为room_id;
        
        if ((message.room_type=="大床房") || (message.room_type=="双人间")) {//需要两个人的信息
            int location = 0;
            for (location = 0; message.customer_id[location] != ','; location++);
            string id1 = message.customer_id.substr(0, location);
            string id2 = message.customer_id.substr(location + 1);
            
            for (location = 0; message.name[location] != ','; location++);
            string name1 = message.name.substr(0, location);
            string name2 = message.name.substr(location + 1);
            
            //写customer表
            string str6 = "('" + id1 + "','" + name1 + "','" + message.start_time + "','" + message.end_time + "')";
            string statement1 = "insert into customer values" + str6;
            sql.sql(statement1);
            
            str6 = "('" + id2 + "','" + name2 + "','" + message.start_time + "','" + message.end_time + "')";
            statement1 = "insert into customer values" + str6;
            sql.sql(statement1);
            
            //写check_in表
            int price_temp = get_total_price(message);
            string total_price = std::to_string(price_temp);
            string str7 = "('" + id1 + "','" + message.start_time + "','" + message.room_id + "','" + total_price + "','" + "1" + "')";//check_in表的flag：0代表只预约未入住，1代表已入住
            string statement2 = "insert into check_in values" + str7;
            sql.sql(statement2);
            
            str7 = "('" + id2 + "','" + message.start_time + "','" + message.room_id + "','" + total_price + "','" + "1" + "')";//check_in表的flag：0代表只预约未入住，1代表已入住
            statement2 = "insert into check_in values" + str7;
            sql.sql(statement2);
            
            
            //写check_in_log表
            string str8 = "('" + message.room_id + "','" + id1 + "','" + name1 + "','" + message.start_time + "','1990-01-01')";
            string statement3 = "insert into check_in_log values" + str8;
            sql.sql(statement3);
            
            str8 = "('" + message.room_id + "','" + id2 + "','" + name2 + "','" + message.start_time + "','1990-01-01')";
            statement3 = "insert into check_in_log values" + str8;
            sql.sql(statement3);
            
            
        }
        else {//只需要一个人的信息
            
            //写customer表
            string str6 = "('" + message.customer_id + "','" + message.name + "','" + message.start_time + "','" + message.end_time + "')";
            string statement1 = "insert into customer values" + str6;
            sql.sql(statement1);
            
            //写check_in表
            int price_temp = get_total_price(message);
            string total_price = std::to_string(price_temp);
            string str7 = "('" + message.customer_id + "','" + message.start_time + "','" + message.room_id + "','" + total_price + "','" + "1" + "')";//check_in表的flag：0代表只预约未入住，1代表已入住
            string statement2 = "insert into check_in values" + str7;
            sql.sql(statement2);
            
            //写check_in_log表
            string str8 = "('" + message.room_id + "','" + message.customer_id + "','" + message.name + "','" + message.start_time + "','1990-01-01')";
            string statement3 = "insert into check_in_log values" + str8;
            sql.sql(statement3);
        }
        int price_temp = get_total_price(message);
        sql.commitTran();
        DataStruct ack;
        ack.kind=_check_in_directly;
        ack.room_id=available_room_id[0][0];//一共n行一列，选第一行的那个作为room_id;
        ack.isSucceed = true;
        ack.price = price_temp;
        qDebug()<<"Send directly_check_in:"<<serverConnector.sendMessage(ack, clientNum);//有用的信息存在属性room_id、price中，告诉前端（客户）他选的房间类型对应的分配到的房间号以及这几天的总价格
        
    }
    
}

void handle_reserved_check_in(DataStruct message, int clientNumber) {//办理已预约用户入住功能
    //已预约的办理入住
    sql.beginTran();
    if ((message.room_type=="大床房") || (message.room_type=="双人间")) {//需要两个人的信息
        int location = 0;
        for (location = 0; message.customer_id[location] != ','; location++);
        string id1 = message.customer_id.substr(0, location);
        string id2 = message.customer_id.substr(location + 1);
        
        for (location = 0; message.name[location] != ','; location++);
        string name1 = message.name.substr(0, location);
        string name2 = message.name.substr(location + 1);

        string statement0="select customer_id from check_in where room_id='"+message.room_id+"' and start_time='"+message.start_time+"'";
        vector<vector<string>> cus_id;
        sql.sql(statement0,cus_id);

        if((cus_id[0][0]==id1&&cus_id[1][0]==id2)||(cus_id[0][0]==id2&&cus_id[1][0]==id1)){
            /*
            cout<<message.customer_id<<" "<<message.name<<endl;
            cout<<id1<<" "<<id2<<endl;
            cout<<name1<<" "<<name2<<endl;
            */

            //修改check_in表
            string str1 = "update check_in set flag = '1' where customer_id=";
            string str2 = "'" + id1 + "'" + "and start_time=" + "'" + message.start_time + "'";
            string str3 = "'" + id2 + "'" + "and start_time=" + "'" + message.start_time + "'";
            string statement1 = str1 + str2;
            string statement2 = str1 + str3;
            sql.sql(statement1);
            sql.sql(statement2);

            //在check_in_log增加一条记录
            string str4 = "('" + message.room_id + "','" + id1 + "','" + name1 + "','" + message.start_time+ "','1990-01-01')";
            string str5 = "('" + message.room_id + "','" + id2 + "','" + name2 + "','" + message.start_time+ "','1990-01-01')";
            string statement3 = "insert into check_in_log values" + str4;
            string statement4 = "insert into check_in_log values" + str5;
            cout<<statement3<<endl<<statement4<<endl;
            sql.sql(statement3);
            sql.sql(statement4);

        }
        else{
            sql.commitTran();
            DataStruct ack;
            ack.kind=_check_in_reserverd;
            ack.isSucceed=false;
            qDebug()<<"Send reserved_check_in:"<<serverConnector.sendMessage(ack, clientNumber);
            return;
        }

        
    }
    else {
        string statement0="select customer_id from check_in where room_id='"+message.room_id+"' and start_time='"+message.start_time+"'";
        vector<vector<string>> cus_id;
        sql.sql(statement0,cus_id);
        if(cus_id[0][0]==message.customer_id){
            //修改check_in表
            string str1 = "update check_in set flag = '1' where customer_id=";
            string str2 = "'" + message.customer_id + "'" + "and start_time=" + "'" + message.start_time + "'";
            string statement1 = str1 + str2;
            sql.sql(statement1);


            //在check_in_log增加一条记录
            string str3 = "('" + message.room_id + "','" + message.customer_id + "','" + message.name + "','" + message.start_time+ "','1990-01-01')";
            string statement2 = "insert into check_in_log values" + str3;
            sql.sql(statement2);

        }
        else{
            sql.commitTran();
            DataStruct ack;
            ack.kind=_check_in_reserverd;
            ack.isSucceed=false;
            qDebug()<<"Send reserved_check_in:"<<serverConnector.sendMessage(ack, clientNumber);
            return;

        }

        

    }
    sql.commitTran();
    DataStruct ack;
    ack.kind=_check_in_reserverd;
    ack.isSucceed=true;
    qDebug()<<"Send reserved_check_in:"<<serverConnector.sendMessage(ack, clientNumber);
}

void handle_check_out(DataStruct message,int clientNumber){//办理退房
    sql.beginTran();
    string sql_sentence="select * from check_in where customer_id='"+message.customer_id+"'and flag=1";
    vector<vector<string>> result;
    sql.sql(sql_sentence, result);//查询是否入住
    if(result.size()==0){//当前未办理入住，退房失败
        DataStruct fail;
        fail.kind=_check_out;
        fail.isSucceed=0;
        serverConnector.sendMessage(fail,clientNumber);
    }else{//成功退房
        string now=getTime();
        vector<vector<string>> partern;
        sql_sentence="select customer_id from check_in where room_id in (select room_id from check_in where customer_id='"+message.customer_id+"') and start_time in (select start_time from check_in where customer_id = '"+message.customer_id+"') and customer_id<>'"+message.customer_id+"'";
        //qDebug()<<QString::fromStdString(sql_sentence)<<endl;
        sql.sql(sql_sentence,partern);
        sql_sentence="delete from customer where customer_id='"+message.customer_id+"'and start_time<='"+now+"'";
        sql.sql(sql_sentence);//删除customer信息
        sql_sentence="delete from check_in where customer_id='"+message.customer_id+"'and flag=1";
        sql.sql(sql_sentence);//删除check_in信息
        sql_sentence="update check_in_log set end_time='"+now+"' where customer_id='"+message.customer_id+"' and end_time='1990-01-01'";
        sql.sql(sql_sentence);//完善入住日志
        if(partern.size()!=0){
            sql_sentence="delete from customer where customer_id='"+partern[0][0]+"'and start_time<='"+now+"'";
            sql.sql(sql_sentence);//删除customer信息
            sql_sentence="delete from check_in where customer_id='"+partern[0][0]+"'and flag=1";
            sql.sql(sql_sentence);//删除check_in信息
            sql_sentence="update check_in_log set end_time='"+now+"' where customer_id='"+partern[0][0]+"' and end_time='1990-01-01'";
            sql.sql(sql_sentence);//完善入住日志
        }
        sql.commitTran();
        DataStruct ack;
        ack.kind=_check_out;
        ack.isSucceed=1;
        serverConnector.sendMessage(ack,clientNumber);//发送成功
    }
}

void handle_room_query(int clientNumber){//查询房间状态
    string sql_sentence="select  distinct room.room_id, room_type,unit_price,flag from room left join (select room_id,flag from check_in where start_time<='"+getTime()+"') as T on room.room_id=T.room_id ";
    vector<vector<string>> result;
    sql.sql(sql_sentence,result);
    DataStruct ack;
    ack.kind=_room_query;
    ack.result=result;
    serverConnector.sendMessage(ack,clientNumber);

}

void handle_room_info(DataStruct message,int clientNumber){//查询具体房间信息
    string sql_sentence="select customer.customer_id,name,customer.start_time,end_time,total_price from check_in join room on check_in.room_id=room.room_id join customer on customer.customer_id=check_in.customer_id and customer.start_time=check_in.start_time where room.room_id='"+message.room_id+"' order by start_time";
    vector<vector<string>> result;
    sql.sql(sql_sentence,result);//查询房间信息
    DataStruct ack;
    ack.kind=_room_info_query;
    ack.result=result;
    serverConnector.sendMessage(ack,clientNumber);
}





















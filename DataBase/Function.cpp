//
//  Function.cpp
//  HMSle//
//  Created by zhouyuxiang on 2018/7/13.
//  Copyright ? 2018年 zhouyuxiang. All rights reserved.
//

#include "Function.hpp"
#include <stdio.h>
#include <vector>
#include<math.h>
#include<time.h>
#include "ServerConnector.h"
#include <QDebug>


void handle_message_client(DataStruct message,int Client){//后端处理用户机数据包
    switch (message.kind) {
        case _time_query://处理客户的房间查询请求
        //
            handle_query(message,Client);
            break;
        case _reservation://房间预约功能
        //
            handle_reservation(message,Client);
            break;
        case _cancel://取消预约功能
            handle_cancel(message, Client);
            break;
        case _stay_over://续住功能
            handle_stay_over(message,Client);
            break;
        case _query_reservation://查询预约信息
            handle_reservation_query(message,Client);
            break;
        case _cost_query://获取价格信息
        //
            handle_total_price(message, Client);
            break;
    }
}

void handle_reservation_query(DataStruct message,int clientNumber){//查询预约信息
    string sql_sentence="select room.room_id,room_type,check_in.start_time,end_time,flag  from check_in join room on room.room_id=check_in.room_id join customer on check_in.customer_id=customer.customer_id and check_in.start_time=customer.start_time where customer.customer_id='"+message.customer_id+"'";
    //qDebug()<<QString::fromStdString(sql_sentence)<<endl;
    DataStruct ack;
    ack.kind=_query_reservation;
    sql.sql(sql_sentence,ack.result);
    serverConnector.sendMessage(ack,clientNumber);
}

void handle_cancel(DataStruct message,int clientNumber){//取消预约功能
    sql.beginTran();
    string sql_sentence="delete from check_in where room_id='"+message.room_id+"'and start_time='"+message.start_time+"'";
    sql.sql(sql_sentence);//删除预约信息
    cout<<sql_sentence;
    sql_sentence="delete from customer where customer_id='"+message.customer_id+"'and start_time='"+message.start_time+"'";
    sql.sql(sql_sentence);//删除客户信息
    cout<<sql_sentence;
    sql_sentence="insert into reservation_log values('"+message.room_id+"','"+message.customer_id+"','"+message.name+"','"+message.start_time+"','"+message.end_time+"',0,'"+getTime()+"')";
    sql.sql(sql_sentence);//添加取消预约的记录
    cout<<sql_sentence;
    sql.commitTran();
}

void handle_stay_over(DataStruct message,int clientNumber){//续住功能
    sql.beginTran();
    string sql_sentence;
    sql_sentence="select * from check_in join customer on check_in.customer_id=customer.customer_id and check_in.start_time=customer.start_time where customer.customer_id='"+message.customer_id+"'and flag=1 and name='"+message.name+"'";
    vector<vector<string>> result;
    //qDebug()<<QString::fromStdString(sql_sentence)<<endl;
    sql.sql(sql_sentence, result);//查询是否入住
    if(result.size()==0){//当前未办理入住，办理续住失败
        DataStruct fail;
        fail.kind=_stay_over;
        fail.isSucceed=0;
        serverConnector.sendMessage(fail,clientNumber);
    }else{
        sql_sentence="select end_time,room_type,room.room_id,unit_price from customer join check_in on customer.customer_id=check_in.customer_id and customer.start_time=check_in.start_time join  room on check_in.room_id=room.room_id where customer.customer_id='"+message.customer_id+"' and flag=1";
        vector<vector<string>> info;
        sql.sql(sql_sentence,info);//获取当前住房的信息
        string str2 = "(select room.room_id from room where room_type='"+info[0][1]+"')except(select room.room_id from(check_in join customer on check_in.customer_id = customer.customer_id and check_in.start_time = customer.start_time) right join room on check_in.room_id = room.room_id ";
        string str3 = "where";
        string str4 = "(customer.start_time>=dateadd(day,1,'"+info[0][0]+"') and customer.end_time<=dateadd(day,"+to_string(message.day)+",'"+info[0][0] + "'))";
        string str5 = "OR(customer.start_time<=dateadd(day,1,'"+info[0][0]+"') and customer.end_time>=dateadd(day,"+to_string(message.day)+",'"+info[0][0]+"'))";
        string str6 = "OR(customer.start_time<=dateadd(day,1,'"+info[0][0]+"') and customer.end_time>=dateadd(day,1,'"+info[0][0]+"'))";
        string str7 = "OR(customer.start_time<=dateadd(day,"+to_string(message.day)+",'"+info[0][0]+"') and customer.end_time>=dateadd(day,"+to_string(message.day)+",'"+info[0][0]+"')))";
        sql_sentence=str2+str3+str4+str5+str6+str7;
        //sql_sentence="select room_id from room where room_id in (select room.room_id from (check_in join customer on check_in.customer_id=customer.customer_id) right join room on check_in.room_id=room.room_id where customer.start_time is null OR customer.start_time>dateadd(day,1,'"+info[0][0]+"') OR customer.end_time<='"+info[0][0]+"') AND room_type='"+info[0][1]+"'";
        qDebug()<<QString::fromStdString(sql_sentence);
        vector<vector<string>> room;
        sql.sql(sql_sentence,room);//筛选满足条件的房间
        DataStruct ack;
        ack.kind=_stay_over;
        if(room.size()==0){//无空房，续住失败
            ack.kind=_stay_over;
            ack.isSucceed=0;
            serverConnector.sendMessage(ack, clientNumber);
        }else{
            int is_empty=0;
            for(int i=0;i<room.size();i++){
                if(room[i][0]==info[0][2])//若当前住房可以续住
                {
                    is_empty=1;
                    break;
                }
            }
            if(is_empty==1){//直接续住当前房间
                /*sql_sentence="select room_id from check_in where customer_id='"+message.customer_id+"' and flag=1";
                vector<vector<string>> room;
                sql.sql(sql_sentence,room);//获取需要修改的房间
                sql_sentence="update customer set end_time=dateadd(day,"+to_string(message.day)+",'"+info[0][0]+"') where room_id='"+room[0][0]+"'and flag=1";
                cout<<sql_sentence<<endl;
                sql.sql(sql_sentence);//修改入住结束日期*/
                string now=getTime();
                sql_sentence="update customer set end_time=dateadd(day,"+to_string(message.day)+",'"+info[0][0]+"') where customer_id='"+message.customer_id+"'and start_time<='"+now+"'";
                sql.sql(sql_sentence);//修改customer
                //qDebug()<<QString::fromStdString(sql_sentence)<<endl;
                int cost=stoi(info[0][3])*message.day;
                sql_sentence="update check_in set total_price=total_price+"+to_string(cost)+" where customer_id='"+message.customer_id+"' and flag=1";
                sql.sql(sql_sentence);//修改check_in
                //qDebug()<<QString::fromStdString(sql_sentence)<<endl;
                sql_sentence="select customer.customer_id,customer.name from check_in join customer on customer.customer_id=check_in.customer_id and customer.start_time=check_in.start_time where room_id='"+info[0][2]+"'and flag=1 and customer.customer_id<>'"+message.customer_id+"'";
                vector<vector<string>> partner;
                sql.sql(sql_sentence,partner);//获取其他住房人信息
                if(partner.size()!=0){//修改其它住房人信息
                    sql_sentence="update customer set end_time=dateadd(day,"+to_string(message.day)+",'"+info[0][0]+"') where customer_id='"+partner[0][0]+"'and start_time<='"+now+"'";
                    qDebug()<<QString::fromStdString(sql_sentence)<<endl;
                    sql.sql(sql_sentence);//修改customer
                    int cost=stoi(info[0][3])*message.day;
                    sql_sentence="update check_in set total_price=total_price+"+to_string(cost)+" where customer_id='"+partner[0][0]+"' and flag=1";
                    sql.sql(sql_sentence);//修改check_in
                }
                ack.kind=_stay_over;
                ack.isSucceed=1;
                ack.room_id=info[0][2];
                serverConnector.sendMessage(ack,clientNumber);//发送成功
            }else {//选择其他房间续住
                sql_sentence="insert into customer values('"+message.customer_id+"','"+message.name+"',dateadd(day,1,'"+info[0][0]+"'),"+"dateadd(day,"+to_string(message.day)+",'"+info[0][0]+"'))";
                sql.sql(sql_sentence);//在customer中加入信息
                int cost=message.day*stoi(info[0][3]);
                sql_sentence="insert into check_in values('"+message.customer_id+"',dateadd(day,1,'"+info[0][0]+"'),'"+room[0][0]+"',"+to_string(cost)+",0)";
                sql.sql(sql_sentence);//在check_in中加入信息
                sql_sentence="select customer.customer_id,customer.name from check_in join customer on customer.customer_id=check_in.customer_id and customer.start_time=check_in.start_time where room_id='"+info[0][2]+"'and flag=1 and customer.customer_id<>'"+message.customer_id+"'";
                vector<vector<string>> partner;
                sql.sql(sql_sentence,partner);//获取其他住房人信息
                if(partner.size()!=0){
                    sql_sentence="insert into customer values('"+partner[0][0]+"','"+partner[0][1]+"',dateadd(day,1,'"+info[0][0]+"'),"+"dateadd(day,"+to_string(message.day)+",'"+info[0][0]+"'))";
                    sql.sql(sql_sentence);
                    sql_sentence=sql_sentence="insert into check_in values('"+partner[0][0]+"',dateadd(day,1,'"+info[0][0]+"'),'"+room[0][0]+"',"+to_string(cost)+",0)";
                    sql.sql(sql_sentence);//将其他住房人信息加入数据库中
                }
                ack.isSucceed=1;
                ack.room_id=room[0][0];
                serverConnector.sendMessage(ack,clientNumber);//发送成功
            }
        }
    }
    sql.commitTran();
}


void handle_query(DataStruct  message, int clientNum) {//查询时间段内空余的房间
    
    string str1 = "select room_type, COUNT(room_id), unit_price  from room  where room_id in";
    string str2 = "((select room.room_id from room)except(select room.room_id from(check_in join customer on check_in.customer_id = customer.customer_id and check_in.start_time = customer.start_time) right join room on check_in.room_id = room.room_id ";
    string str3 = "where";
    string str4 = "(customer.start_time>='"+message.start_time+"' and customer.end_time>='" + message.end_time + "')";
    string str5 = "OR(customer.start_time<='"+message.start_time+"'and customer.end_time>='"+message.end_time+"')";
    string str6 = "OR(customer.start_time<='"+message.start_time+"'and customer.end_time>='"+message.start_time+"')";
    string str7 = "OR(customer.start_time<='"+message.end_time+"'and customer.end_time>='"+message.end_time+"')))"+"group by room_type, unit_price";
    string statement = str1 + str2 + str3 + str4 + str5 + str6 + str7;
    //cout<<statement<<endl;
    vector<vector<string>> available_room_info;
    sql.sql(statement, available_room_info);

    vector<vector<string>> info(4,vector<string>(3));
    vector<vector<string>> price1,price2,price3,price4;


    info[0][0] = "单人间";
    info[1][0] = "大床房";
    info[2][0] = "双人间";
    info[3][0] = "总统套房";
    string up1="select unit_price from room where room_type='单人间'";
    string up2="select unit_price from room where room_type='大床房'";
    string up3="select unit_price from room where room_type='双人间'";
    string up4="select unit_price from room where room_type='总统套房'";

    sql.sql(up1,price1);
    sql.sql(up2,price2);
    sql.sql(up3,price3);
    sql.sql(up4,price4);

    info[0][2] = price1[0][0];
    info[1][2] = price2[0][0];
    info[2][2] = price3[0][0];
    info[3][2] = price4[0][0];

    if (available_room_info.size() != 0) {
        int i = 0, j = 0;
        int flag = 0;
        for (i = 0; i <= 3; i++) {
            for (j = 0; j < available_room_info.size(); j++)
                if (available_room_info[j][0]==info[i][0]) {
                    flag = 1;
                    info[i][1] = available_room_info[j][1];
                    break;
                }
            if (flag == 0)
                info[i][1] = "0";
            flag = 0;
        }
    }
    else {
        int i = 0;
        for (i = 0; i < 4; i++)
            info[i][1] = "0";
    }


    bool res=(available_room_info[0][0]==info[0][0]);
    //qDebug()<<QString::fromStdString(info[0][0])<<","<<QString::fromStdString(available_room_info[0][0]);
    //qDebug()<<res;
    //qDebug()<<QString::fromStdString(info[1][0])<<","<<QString::fromStdString(available_room_info[1][0]);
    //qDebug()<<QString::fromStdString(info[2][0])<<","<<QString::fromStdString(available_room_info[2][0]);
    //qDebug()<<QString::fromStdString(info[3][0])<<","<<QString::fromStdString(available_room_info[3][0]);

    /*qDebug()<<QString::fromStdString(info[0][0])<<","<<QString::fromStdString(info[0][1])<<","<<QString::fromStdString(info[0][2])<<endl;
    qDebug()<<QString::fromStdString(info[1][0])<<","<<QString::fromStdString(info[1][1])<<","<<QString::fromStdString(available_room_info[1][2])<<endl;
    qDebug()<<QString::fromStdString(info[2][0])<<","<<QString::fromStdString(info[2][1])<<","<<QString::fromStdString(info[2][2])<<endl;
    qDebug()<<QString::fromStdString(info[3][0])<<","<<QString::fromStdString(info[3][1])<<","<<QString::fromStdString(info[3][2])<<endl;*/






    DataStruct ack;
    ack.result = info;
    ack.kind=_time_query;
    serverConnector.sendMessage(ack, clientNum);//有用的信息存储在二维vector result中，告诉前端（用户）所选时间段可用房间类型、余量及单价
}

void handle_reservation(DataStruct message, int clientNum) {//处理预约请求
    //此用户已预约过重叠时间段内的房间
    sql.beginTran();
    int is_legal = 1;
    string str0 = "select start_time, end_time from customer where customer_id =";
    string statement0=str0;
    
    qDebug()<<"THR:"<<QString::fromStdString(message.room_type)<<",CONST:"<<QString::fromStdString("大床房");

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
    
 /*
    cout<<"The size is: "<<reserve_info.size()<<endl;
    cout<<"start time is:"<<reserve_info[0][0]<<endl;
    cout<<"end time is:"<<reserve_info[0][1]<<endl;
*/
    if (reserve_info.size() != 0) {
        int i = 0;
        int j = reserve_info.size();
        DataStruct ack;

        for (i = 0; i < j; i++) {
            if ((message.start_time >= reserve_info[i][0] && message.start_time <= reserve_info[i][1]) || (message.end_time >= reserve_info[i][0] && message.end_time <= reserve_info[i][1]) || (message.end_time >= reserve_info[i][1] && message.start_time <= reserve_info[i][0]) || (message.end_time <= reserve_info[i][1] && message.start_time >= reserve_info[i][0])) {
                is_legal = 0;//要预约的时间和已预约的某段时间重合，不合法，拒绝请求
                sql.commitTran();
                ack.kind=_reservation;
                ack.isSucceed=false;
                serverConnector.sendMessage(ack, clientNum);
                return;
            }
        }
    }
    
    //此用户此用户没有预约过房间 或 已预约过房间但时间段不重叠,对三条日志进行修改
    if (reserve_info.size() == 0 || is_legal==1) {

        string str2 = "(select room.room_id from room where room_type='"+message.room_type+"')except(select room.room_id from(check_in join customer on check_in.customer_id = customer.customer_id and check_in.start_time = customer.start_time) right join room on check_in.room_id = room.room_id ";
        string str3 = "where";
        string str4 = "(customer.start_time>='"+message.start_time+"' and customer.end_time>='" + message.end_time + "')";
        string str5 = "OR(customer.start_time<='"+message.start_time+"'and customer.end_time>='"+message.end_time+"')";
        string str6 = "OR(customer.start_time<='"+message.start_time+"'and customer.end_time>='"+message.start_time+"')";
        string str7 = "OR(customer.start_time<='"+message.end_time+"'and customer.end_time>='"+message.end_time+"'))";
        string statement = str2 + str3 + str4 + str5 + str6+str7;

        qDebug()<<QString::fromStdString(statement);
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

            //qDebug()<<"This is two people"<<endl;
            //qDebug()<<QString::fromStdString(id1)<<endl<<QString::fromStdString(id2);
            
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
            string str8 = "('" + message.room_id + "','" + id1 + "','" + name1 + "','" + message.start_time + "','" + message.end_time + "','" + "1" + "','" + getTime() + "')";//reservation_log表的flag：1代表创建预约，0代表取消预约。
            string statement3 = "insert into reservation_log values" + str8;
            sql.sql(statement3);
            
            str8 = "('" + message.room_id + "','" + id2 + "','" + name2 + "','" + message.start_time + "','" + message.end_time + "','" + "1" + "','" +getTime() + "')";//reservation_log表的flag：1代表创建预约，0代表取消预约。
            statement3 = "insert into reservation_log values" + str8;
            sql.sql(statement3);
            
        }
        else {//只需要一个人的信息
            

           // qDebug()<<"This is one person"<<endl;
            //qDebug()<<QString::fromStdString(message.customer_id)<<endl<<QString::fromStdString(message.name);
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
            string str8 = "('" + message.room_id + "','" + message.customer_id + "','" + message.name + "','" + message.start_time + "','" + message.end_time + "','" + "1" + "','" + getTime() + "')";//reservation_log表的flag：1代表创建预约，0代表取消预约。
            string statement3 = "insert into reservation_log values" + str8;
            sql.sql(statement3);
        }
        int price_temp = get_total_price(message);
        sql.commitTran();
        DataStruct ack;
        ack.kind=_reservation;
        ack.room_id=available_room_id[0][0];
        ack.isSucceed = true;
        ack.price = price_temp;
        qDebug()<<"Send resevation:"<<serverConnector.sendMessage(ack, clientNum);//有用的信息存在属性room_id、price中，告诉前端（客户）他选的房间类型对应的分配到的房间号以及这几天的总价格
        
    }
}


int get_total_price(DataStruct  message)//计算价格
{
    int unit_price = 0;
    vector<vector<string>> price_str;
    const char* time1 = message.start_time.data();
    const char* time2 = message.end_time.data();
    int days = get_days(time1, time2);
   // qDebug()<<"day="<<days<<endl;
    string statement = "select unit_price from room where room_type='" + message.room_type+"'";
    sql.sql(statement, price_str);
    //qDebug()<<"price:"<<atoi(price_str[0][0].c_str())<<endl;
    unit_price = atoi(price_str[0][0].c_str());
    return unit_price * days;

}


int get_days(const char* from, const char* to)//计算天数
{
    int year, month, day;
    sscanf(from, "%d-%d-%d", &year, &month, &day);
    int fromSecond = (int)convert(year, month, day);
    sscanf(to, "%d-%d-%d", &year, &month, &day);
    int toSecond = (int)convert(year, month, day);
    return (toSecond - fromSecond) / 24 / 3600;
}


time_t convert(int year, int month, int day)//时间格式转换
{
    tm info = { 0 };
    info.tm_year = year - 1900;
    info.tm_mon = month - 1;
    info.tm_mday = day;
    return mktime(&info);
}


string getTime()//获取当前时间并格式化转换为字符串
{
    time_t timep;
    time (&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d",localtime(&timep));
    return tmp;
}

void handle_total_price(DataStruct message, int clientNumber) {//用户确认预定、入住前需要返回总价格
    int total_price = get_total_price(message);
    DataStruct ack;
    ack.kind=_cost_query;
    ack.price =to_string(total_price);
    //qDebug()<<QString::fromStdString(ack.price)<<endl;
    serverConnector.sendMessage(ack, clientNumber);
}
















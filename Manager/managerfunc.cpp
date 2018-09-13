//manager function
#include <QString>
#include <QDebug>
#include <vector>
#include <string>
#include "sql_odbc.h"
#include "managerfunc.h"

extern SQL_ODBC sql;

using namespace std;

//Room options

bool addNewRoom(QString room_id,QString room_type,float unit_price)
{
    QString t_sql="insert into room values('"+room_id+"','"+room_type+"',";
    t_sql+=QString::number(unit_price)+")";

    return sql.sql(t_sql.toStdString());
}

bool deleteRoom(QString room_id)
{
    vector<vector<string>> res;

    bool bres=true;

    if(!sql.beginTran()) return false;

    QString t_sql="select * from check_in where room_id='"+room_id+"'";

    if(!sql.sql(t_sql.toStdString(),res)) bres=false;//query failed
    else if(res.size()) bres=false;//room is being used

    t_sql="delete from room where room_id='"+room_id+"'";

    //delete room
    bres=bres&&sql.sql(t_sql.toStdString());

    bres=bres&&sql.commitTran();

    return bres;
}

bool alterRoom(QString old_room_id,QString new_room_id,QString room_type,float unit_price)
{
    vector<vector<string>> res;

    bool bres=true;

    if(!sql.beginTran()) return false;

    QString t_sql="select * from check_in where room_id='"+old_room_id+"'";

    if(!sql.sql(t_sql.toStdString(),res)) bres=false;//query failed
    else if(res.size()) bres=false;//room is being used

    t_sql="update room set room_id='"+new_room_id+"',room_type='"+room_type;
    t_sql+="',unit_price="+QString::number(unit_price);
    t_sql+=" where room_id='"+old_room_id+"'";

    //update
    bres=bres&&sql.sql(t_sql.toStdString());

    bres=bres&&sql.commitTran();

    return bres;
}



bool queryRoom(vector<vector<string>> &res, QString keyword, QueryKeyCode orderBy, QueryKeyCode orderType)
{
    vector<vector<string>> _res;

    QString t_sql="";
    t_sql+="select room.room_id,room.room_type,room.unit_price,case count(check_in.room_id) when 0 then 0 else 1 end";
    t_sql+=" from room left outer join check_in on room.room_id=check_in.room_id";
    t_sql+=" where room.room_id like '%"+keyword+"%' or room.room_type like '%"
            +keyword+"%' or room.unit_price like'%"+keyword+"%'";
    t_sql+=" group by room.room_id,room.room_type,room.unit_price";

    switch(orderBy)
    {
        case _order_by_rid:
            t_sql+=" order by room.room_id ";
        break;

        case _order_by_rtype:
            t_sql+=" order by room.room_type ";
        break;

        case _order_by_rprice:
            t_sql+=" order by room.unit_price ";
        break;

        default:
            t_sql+=" order by room.room_id ";
        break;
    }

    t_sql+=(orderType==_descend?"DESC":"ASC");

    //query
    if(!sql.sql(t_sql.toStdString(),_res)) return false;//query failed

    res=_res;

    return true;
}


//Employee options

bool addNewEmployee(QString e_id,QString e_type,QString password)
{
    QString t_sql="insert into employee";
    t_sql+=" values('"+e_id+"','"+e_type+"','"+password+"')";

    return sql.sql(t_sql.toStdString());
}

bool deleteEmployee(QString e_id)
{

    QString t_sql="delete from employee where employee_id='"+e_id+"'";

    //delete employee
    return sql.sql(t_sql.toStdString());
}

bool alterEmployee(QString old_e_id,QString new_e_id,QString e_type,QString password)
{
    QString t_sql="update employee";
    t_sql+=" set employee_id='"+new_e_id+"',employee_type='"+e_type+"',password='"+password+"'";
    t_sql+=" where employee_id='"+old_e_id+"'";

    //update
    return sql.sql(t_sql.toStdString());
}

bool queryEmployee(vector<vector<string>> &res, QString keyword, QueryKeyCode orderBy, QueryKeyCode orderType)
{
    vector<vector<string>> _res;

    QString t_sql="select *";
    t_sql+=" from employee";
    t_sql+=" where employee_id like '%"+keyword+"%' or employee_type like '%"+keyword+"%'";

    switch(orderBy)
    {
        case _order_by_eid:
            t_sql+=" order by employee_id ";
        break;

        case _order_by_etype:
            t_sql+=" order by employee_type ";
        break;

        default:
            t_sql+=" order by employee_id ";
        break;
    }

    t_sql+=(orderType==_descend?"DESC":"ASC");

    //query
    if(!sql.sql(t_sql.toStdString(),_res)) return false;//query failed

    res=_res;

    return true;
}


//Reservation_log options

bool queryReservationLog(vector<vector<string>> &res, QString keyword, QueryKeyCode orderBy, QueryKeyCode orderType,QString startTime,QString endTime)
{
    vector<vector<string>> _res;

    QString t_sql="select *";
    t_sql+=" from reservation_log";
    t_sql+=" where room_id like '%"+keyword+"%'";
    t_sql+=" or customer_id like '%"+keyword+"%'";
    t_sql+=" or name like '%"+keyword+"%'";
    t_sql+=" or start_time like '%"+keyword+"%'";
    t_sql+=" or end_time like '%"+keyword+"%'";
    t_sql+=" or now_time like '%"+keyword+"%'";

    switch(orderBy)
    {
        case _order_by_rid:
            t_sql+=" order by room_id ";
        break;

        case _order_by_cid:
            t_sql+=" order by customer_id ";
        break;

        case _order_by_name:
            t_sql+=" order by name ";
        break;

        case _order_by_start_time:
            t_sql+=" order by start_time ";
        break;

        case _order_by_end_time:
            t_sql+=" order by end_time ";
        break;

        case _order_by_now_time:
            t_sql+=" order by now_time ";
        break;

        default:
            t_sql+=" order by room_id ";
        break;
    }

    t_sql+=(orderType==_descend?"DESC":"ASC");

    //query
    if(!sql.sql(t_sql.toStdString(),_res)) return false;//query failed

    res=_res;

    return true;
}


//Check_in_log options

bool queryCheckInLog(vector<vector<string>> &res, QString keyword, QueryKeyCode orderBy, QueryKeyCode orderType,QString startTime,QString endTime)
{
    vector<vector<string>> _res;

    QString t_sql="select *";
    t_sql+=" from check_in_log";
    t_sql+=" where room_id like '%"+keyword+"%'";
    t_sql+=" or customer_id like '%"+keyword+"%'";
    t_sql+=" or name like '%"+keyword+"%'";
    t_sql+=" or start_time like '%"+keyword+"%'";
    t_sql+=" or end_time like '%"+keyword+"%'";

    switch(orderBy)
    {
        case _order_by_rid:
            t_sql+=" order by room_id ";
        break;

        case _order_by_cid:
            t_sql+=" order by customer_id ";
        break;

        case _order_by_name:
            t_sql+=" order by name ";
        break;

        case _order_by_start_time:
            t_sql+=" order by start_time ";
        break;

        case _order_by_end_time:
            t_sql+=" order by end_time ";
        break;

        default:
            t_sql+=" order by room_id ";
        break;
    }

    t_sql+=(orderType==_descend?"DESC":"ASC");

    //query
    if(!sql.sql(t_sql.toStdString(),_res)) return false;//query failed

    res=_res;

    return true;
}

bool queryRoomPrice(std::vector<std::vector<std::string>> &res)
{
    vector<vector<string>> _res;

    QString t_sql="select distinct room_type,unit_price from room";

    if(!sql.sql(t_sql.toStdString(),_res)) return false;//query failed

    res=_res;

    return true;
}

bool alterRoomPrice(QString room_type,float unit_price)
{
    QString t_sql="update room set unit_price="+QString::number(unit_price);
    t_sql+=" where room_type='"+room_type+"'";

    return sql.sql(t_sql.toStdString());
}

bool loginCheck(QString employee_id,QString password)
{
    vector<vector<string>> _res;

    QString t_sql="select * from employee";
    t_sql+=" where employee_id='"+employee_id+"' and password='"+password+"' and employee_type='经理'";

    if(!sql.sql(t_sql.toStdString(),_res)) return false;//query failed
    else if(_res.size()) return true;

    return false;
}

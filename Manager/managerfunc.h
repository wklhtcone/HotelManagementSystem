#ifndef MANAGERFUNC_H
#define MANAGERFUNC_H

#include <vector>
#include <string>

enum QueryKeyCode
{
    //Room result order by something
    _order_by_rid=1,
    _order_by_rtype,
    _order_by_rprice,

    //Employee result order by something
    _order_by_eid,
    _order_by_etype,

    //Reservation_log result order by something
    //_order_by_rid,
    _order_by_cid,
    _order_by_name,
    _order_by_start_time,
    _order_by_end_time,
    _order_by_now_time,

    //Check_in_log result order by something
    //_order_by_rid,
    //_order_by_cid,
    //_order_by_name,
    //_order_by_start_time,
    //_order_by_end_time,


    //order ascend or descend
    _ascend=1,
    _descend
};

extern bool addNewRoom(QString room_id,QString room_type,float unit_price);
extern bool deleteRoom(QString room_id);
extern bool alterRoom(QString old_room_id,QString new_room_id,QString room_type,float unit_price);
extern bool queryRoom(std::vector<std::vector<std::string>> &res
                      ,QString keyword="",QueryKeyCode orderBy=_order_by_rid,QueryKeyCode orderType=_ascend);


extern bool addNewEmployee(QString e_id,QString e_type,QString password);
extern bool deleteEmployee(QString e_id);
extern bool alterEmployee(QString old_e_id,QString new_e_id,QString e_type,QString password);
extern bool queryEmployee(std::vector<std::vector<std::string>> &res
                          , QString keyword="", QueryKeyCode orderBy=_order_by_eid, QueryKeyCode orderType=_ascend);

extern bool queryReservationLog(std::vector<std::vector<std::string>> &res
                                , QString keyword="", QueryKeyCode orderBy=_order_by_rid, QueryKeyCode orderType=_ascend
                                ,QString startTime="1980-01-01",QString endTime="2100-01-01");

extern bool queryCheckInLog(std::vector<std::vector<std::string>> &res
                            , QString keyword="", QueryKeyCode orderBy=_order_by_rid, QueryKeyCode orderType=_ascend
                            ,QString startTime="1980-01-01",QString endTime="2100-01-01");

extern bool queryRoomPrice(std::vector<std::vector<std::string>> &res);
extern bool alterRoomPrice(QString room_type,float unit_price);

extern bool loginCheck(QString employee_id,QString password);

#endif // MANAGERFUNC_H

#ifndef _DATASTRUCT_
#define _DATASTRUCT_

#include <string>
#include <vector>


enum kindCode
{
    //客户机的信息类型
    _time_query=1,
	_reservation,
	_cancel,
	_stay_over,
    _query_reservation,
    _cost_query,
    
    //前台的信息类型
    _check_in_directly,
    _check_in_reserverd,
    _check_out,
    _room_check_in,
    _room_reservation,
    _room_query,
    _room_info_query,
    _check_in_query,
    _stay_over_info,
    _register
};

typedef struct
{
	int kind;		//all kind is in kindCode

	/*---------1-----------
		kind = _reservation
	*/
	std::string now_time;
    std::string customer_id;
    std::string name;
    std::string start_time;
    std::string end_time;
    std::string room_id;
    std::string room_type;
    std::string price;
    //---------1-----------


    /*---------2-----------
    	kind = _check_in
    */
    //std::string customer_id;
    //std::string name;
    //std::string start_time;
    //std::string end_time;
    //std::string room_id;
    //---------2-----------


    /*---------3-----------
		kind = _cancel
	*/
	//std::string customer_id;
    //std::string name;
    //std::string room_id;
    //std::string now_time;
    //std::string start_time;
    //std::string end_time;
    //---------3-----------


	/*---------4-----------
		kind = _stay_over
	*/
	//std::string customer_id;
    int day;
    //---------4-----------


    /*---------5-----------
		kind = _check_out
	*/
    //std::string customer_id;
    //---------5-----------


	/*---------6-----------
		kind = _query_result
	*/
	bool isSucceed;
	std::vector<std::vector<std::string>> result; 
	//---------6-----------

}DataStruct;

#endif	//!_DATASTRUCT_

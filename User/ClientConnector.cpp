#include "ClientConnector.h"

#include <QDebug>

ClientConnector::ClientConnector() {}

ClientConnector::~ClientConnector() {}

bool ClientConnector::getMessage(DataStruct & data)
{
	char str[MAX_BUF_LEN];
	unsigned int len;

	if (!Client::getMessage(str, len))
	{
		//non message in queue
		return false;
	}

	//char[] to DataStruct
	CtoD(data, str, len);

    qDebug()<<"get kind="<<data.kind;

	return true;
}

bool ClientConnector::sendMessage(const DataStruct & data)
{
	char str[MAX_BUF_LEN];
	unsigned int len;
	
	//DataStruct to char[]
	DtoC(data, str, len);

    qDebug()<<"send kind="<<data.kind;

	return Client::sendMessage(str, len);
}

void ClientConnector::DtoC(const DataStruct & data, char str[MAX_BUF_LEN], unsigned int & len)
{
	char *pstr = str;
	unsigned int tmpI;
	bool tmpB;

	#define ITOC *(pstr++) = tmpI & 0xFF;		\
		*(pstr++) = (tmpI & 0xFF00) >> 8;		\
		*(pstr++) = (tmpI & 0xFF0000) >> 16;	\
		*(pstr++) = (tmpI & 0xFF000000) >> 24

	#define BTOC *(pstr++) = (char)tmpB

	//kind
	tmpI = data.kind;
	ITOC;

	//day
	tmpI = data.day;
	ITOC;

	//isSucceed
	tmpB = data.isSucceed;
	BTOC;

	//---------dealing string---------
	#define STRTOC(x) tmpI = x.length();				\
		ITOC;											\
		memcpy_s(pstr, MAX_BUF_LEN,x.c_str(), tmpI);	\
		pstr += tmpI

	//now_time
	STRTOC(data.now_time);

	//customer_id
	STRTOC(data.customer_id);

	//name
	STRTOC(data.name);

	//start_time
	STRTOC(data.start_time);

	//end_time
	STRTOC(data.end_time);

	//room_id
	STRTOC(data.room_id);

	//room_type
	STRTOC(data.room_type);

	//price
	STRTOC(data.price);

	//---------dealing vector<vector<string>>---------

	tmpI = data.result.size();	//row
	ITOC;
	if (data.result.size() == 0)
	{
		//set col to zero
		ITOC;
	}
	else //row > 0
	{
		tmpI = data.result[0].size();//col
		ITOC;
		for (int i = 0; i < data.result.size(); ++i)
		{
			for (int j = 0; j < data.result[i].size(); ++i)
			{
				STRTOC(data.result[i][j]);
			}
		}
	}

    len = (unsigned int)(pstr - str);

	#undef ITOC
	#undef BTOC
	#undef STRTOC
}

void ClientConnector::CtoD(DataStruct & data, char str[MAX_BUF_LEN], unsigned int len)
{
	unsigned int tmpI;
	bool tmpB;
	char tmpS[CLEN];
	char *pstr = str;

	#define CTOI tmpI = (unsigned char)(*(pstr++));	\
		tmpI += (unsigned char)(*(pstr++)) << 8;	\
		tmpI += (unsigned char)(*(pstr++)) << 16;	\
		tmpI += (unsigned char)(*(pstr++)) << 24	

	#define CTOB tmpB = (bool)(*(pstr++))
	

	//kind
	CTOI;
	data.kind = tmpI;

	//day
	CTOI;
	data.day = tmpI;

	//isSucceed
	CTOB;
	data.isSucceed = tmpB;

	//-------dealing string-------
	#define CTOSTR(x) CTOI;					\
		memcpy_s(tmpS, CLEN, pstr, tmpI);	\
		tmpS[tmpI] = 0;						\
		x = tmpS;							\
		pstr += tmpI;

	//now_time
	CTOSTR(data.now_time);

	//customer_id
	CTOSTR(data.customer_id);

	//name
	CTOSTR(data.name);

	//start_time
	CTOSTR(data.start_time);

	//end_time
	CTOSTR(data.end_time);

	//room_id
	CTOSTR(data.room_id);

	//room_type
	CTOSTR(data.room_type);

	//price
	CTOSTR(data.price);
	
	//---------dealing vector<vector<string>>---------
	CTOI;
	data.result.resize(tmpI);
	CTOI;

	unsigned int tmpCol = tmpI;
	for (int i = 0; i < data.result.size(); ++i)
	{
		data.result[i].resize(tmpCol);
		for (int j = 0; j < data.result[i].size(); ++j)
		{
			CTOSTR(data.result[i][j]);
		}
	}

	#undef CTOI
	#undef CTOB
	#undef CTOSTR
}

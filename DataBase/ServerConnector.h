#pragma once

#include "Server.h"
#include "DataStruct.h"

#define CLEN 40

class ServerConnector:public Server
{
public:
	ServerConnector();

	~ServerConnector();

	bool getMessage(DataStruct &data,int &clientNumber);

	bool sendMessage(const DataStruct &data, int clientNumber);

private:
	void DtoC(const DataStruct &data, char str[MAX_BUF_LEN], unsigned int &len);

	void CtoD(DataStruct &data, char str[MAX_BUF_LEN], unsigned int len);
};
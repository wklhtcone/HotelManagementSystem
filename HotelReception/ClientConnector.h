#pragma once

#include "DataStruct.h"
#include "Client.h"

#define CLEN 40

class ClientConnector :public Client
{
public:
	ClientConnector();

	~ClientConnector();

	bool getMessage(DataStruct &data);

	bool sendMessage(const DataStruct &data);

private:
	void DtoC(const DataStruct &data, char str[MAX_BUF_LEN], unsigned int &len);

	void CtoD(DataStruct &data, char str[MAX_BUF_LEN], unsigned int len);
};
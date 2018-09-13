#pragma once

#include <winsock2.h>
#include <iostream>
#include <cstdlib>
#include <List>

#pragma comment(lib,"ws2_32.lib")

#define SER_PORT 5000     
#define SER_IP "10.8.222.223"
#define MAX_CLIENT 2
#define MAX_BUF_LEN 0xFFFF

struct Buffer
{
	char buf[MAX_BUF_LEN];
	int sourceID;
	int len;
};

class Server
{
private:
	//Data

	HANDLE hThreadServer;

	SOCKET server;
	SOCKET client[MAX_CLIENT];
	SOCKADDR_IN serAddr;
	SOCKADDR_IN cliAddr[MAX_CLIENT];
	int cliNum;		//record the number of current clients

	fd_set fdRead;

	WORD wVersionRequested;
	WSADATA wsaData;

	int cliAddrLen;

	bool isThreadRunning;

	bool exitCode;

	std::list<Buffer> msgList;

	//Functions

	bool checkClientConnect(int &ret, const FD_SET fd);

	bool checkDataFromClient(int &ret, int cliOrder, const FD_SET fd);

	bool sendingMsgToClient(int cliOrder, const char * buf, unsigned int len);

	void clearClient(int cliOrder);

	static DWORD  WINAPI ServerThread(LPVOID lpParam);

	void serverRun(void);

public:
	Server();

	bool startServer();

	void endServer();

	bool isServerRunning(void);

	bool getMessage(char buf[MAX_BUF_LEN], unsigned int &len, int &destClientID);

	bool sendMessage(const char buf[MAX_BUF_LEN], unsigned int len, int destClientID);
};


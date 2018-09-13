#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WINSOCK2.H>
#include <cstring>
#include <list>

#pragma comment(lib,"WS2_32.lib")

#define DES_IP "10.8.222.223"
#define DES_PORT 5000
#define MAX_BUF_LEN 0xFFFF

struct Buffer
{
	char buf[MAX_BUF_LEN];
	int len;
};

class Client
{
private:
	//Data

	SOCKET sock;	//Server's socket
	SOCKADDR_IN serAddr;

	FD_SET fdRead;

	WSADATA wsaData;
	WORD wVersionRequired;

	HANDLE hThread;

	std::list<Buffer> msgList;

	bool isThreadRunning;

	bool exitCode;

	//Function

	bool sendingMsgToServer(const char * buf, unsigned int len);

	bool checkDataFromServer(int & ret, const FD_SET fd);

	static DWORD WINAPI clientThread(LPVOID lparama);

	void clientRun(void);

public:
	Client();

	~Client();

	bool startClient(void);

	void endClient(void);

	bool getMessage(char buf[MAX_BUF_LEN], unsigned int &len);

	bool sendMessage(const char buf[MAX_BUF_LEN], unsigned int len);
};

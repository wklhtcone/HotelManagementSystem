#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "Server.h"

#include <QDebug>

using namespace std;

Server::Server()
{
	isThreadRunning = false;
}

//Private

//Thread function
DWORD WINAPI Server::ServerThread(LPVOID lpParam)
{
	Server *obj = (Server*)lpParam;

	obj->exitCode = true;

	//really start server
	obj->serverRun();

	obj->exitCode = false;
	obj->isThreadRunning = false;

	return 0;
}

//Real running function
void Server::serverRun(void)
{
	while (exitCode)
	{
		if (int i = listen(server, MAX_CLIENT) != 0)
		{
			cout << "Listen error:" << WSAGetLastError() << endl;
			return;
		}

		//get new client or recv data
		FD_SET(server, &fdRead);
		fd_set fdSav;
		while (exitCode)
		{
			fdSav = fdRead;

			int selectRet;
			timeval t = { 1 ,0 };//1 second delay
			if ((selectRet = select(0, &fdSav, NULL, NULL, &t)) <= 0)
			{
				//Time out or select error
				continue;
			}

			//if new client request to connect
			checkClientConnect(selectRet,fdSav);
			FD_CLR(server, &fdSav);

			//recv data from client(s)
			for (int i = 0; selectRet > 0 && i < cliNum; ++i)
			{
				if (!checkDataFromClient(selectRet, i, fdSav))
				{
					//Clear this client
					FD_CLR(client[i], &fdRead);
					closesocket(client[i]);
					clearClient(i);
				}
			}

			FD_ZERO(&fdSav);
		}

	}//while [wait client]
}

bool Server::checkClientConnect(int &ret, const FD_SET fd)
{
	if (ret > 0 && FD_ISSET(server, &fd))
	{
		//check clients number
		if (cliNum >= MAX_CLIENT)
		{
			cout << "Clients is full!" << endl;
			return false;
		}

		//get new client
		if ((client[cliNum] 
			= accept(server, (SOCKADDR *)&cliAddr[cliNum], &cliAddrLen))
			== INVALID_SOCKET)
		{
			cout << "Client lost connect!\n\n";
			return false;
		}
		else
		{
			--ret;
			FD_SET(client[cliNum], &fdRead);

			cout << "Client Ip: "
				<< inet_ntoa(cliAddr[cliNum].sin_addr) << endl;
			cout << "Client Port: "
				<< ntohs(cliAddr[cliNum++].sin_port) << endl;
		}
	}
	return true;
}

bool Server::checkDataFromClient(int & ret, int cliOrder, const FD_SET fd)
{
	//check if this client has sending request
	if (!FD_ISSET(client[cliOrder], &fd))
	{
		return true;
	}

	//start recv
	int RecvBytes = 0;
	unsigned int len = 0;
	char buf[MAX_BUF_LEN + 1];
	Buffer tmp = { 0 ,0 ,0 };

	//get package length
	RecvBytes = recv(client[cliOrder], buf, 4, 0);
	if (RecvBytes == SOCKET_ERROR || RecvBytes == 0)
	{
		cout << "Receive error or client lost!\n";
		return false;
	}

	len += (unsigned char)buf[0] + ((unsigned char)buf[1] << 8)
		+ ((unsigned char)buf[2] << 16) + ((unsigned char)buf[3] << 24);
	tmp.len = len;

	char *pbuf = tmp.buf;

	do
	{
		RecvBytes = recv(client[cliOrder], buf, len, 0);
		if (RecvBytes == SOCKET_ERROR || RecvBytes == 0)
		{
			cout << "Receive error or client lost!\n";
			return false;
		}

		//store the package
		memcpy_s(pbuf, MAX_BUF_LEN, buf, RecvBytes);

		//move pointer
		len -= RecvBytes;
		pbuf += RecvBytes;

	} while (len > 0);

	//insert into the message list
	tmp.sourceID = cliOrder;
	msgList.push_back(tmp);

	return true;
}

bool Server::sendingMsgToClient(int cliOrder, const char * buf,unsigned int len)
{
	//add package length
    char _buf[MAX_BUF_LEN + 4];

	_buf[0] = (len & 0xFF);
	_buf[1] = (len & 0xFF00) >> 8;
	_buf[2] = (len & 0xFF0000) >> 16;
	_buf[3] = (len & 0xFF000000) >> 24;

	memcpy_s(_buf + 4, MAX_BUF_LEN, buf, len);


	if (SOCKET_ERROR == (send(client[cliOrder], _buf, len + 4, 0)))
	{
        cout<<"ErrorCode:"<<WSAGetLastError()<<endl;
		cout << "\nSend Error!(To the client " << cliOrder << endl;
		return false;
	}
	return true;
}

void Server::clearClient(int cliOrder)
{
	if (cliOrder >= cliNum || cliOrder < 0) return;
	--cliNum;

	for (int i = cliOrder; i < cliNum; ++i)
	{
		client[i] = client[i + 1];
		cliAddr[i] = cliAddr[i + 1];
	}
}

//Public
bool Server::startServer()
{
	//check if server is running
	if (isThreadRunning)
	{
		cout << "Error:Server is running!" << endl;
		return false;
	}

	wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
	{
		cout << "Error:Init WSA error!\n";
		return false;
	}

	//Init server
	serAddr.sin_family = AF_INET;
	serAddr.sin_addr.S_un.S_addr = inet_addr(SER_IP);
	serAddr.sin_port = htons(SER_PORT);
	memset(serAddr.sin_zero, 0, 8);
	server = socket(AF_INET, SOCK_STREAM, 0);

	//Init fd_set
	fdRead.fd_count = 0;

	if (server == INVALID_SOCKET)
	{
		cout << "Error:Create socket error!\n";
		return false;
	}

	//Init client list
	cliNum = 0;
	memset(client, 0, sizeof(client));
	memset(cliAddr, 0, sizeof(cliAddr));

	cliAddrLen = sizeof(SOCKADDR);

	if (bind(server, (SOCKADDR *)&serAddr, sizeof(SOCKADDR)) != 0)
	{
		cout << "Error:Bind error\n";
		return false;
	}
	else
	{
		cout << "Server start successful......\n\n";
	}

	//Init message list
	msgList.clear();

	//Start running server
	hThreadServer = CreateThread(NULL, 0, ServerThread, (LPVOID)this, 0, NULL);
	isThreadRunning = true;

	return true;
}

void Server::endServer()
{
	exitCode = false;
	Sleep(1000);	//wait for thread ending

	cout << "---End---\nclean state and quit..." << endl;

	FD_ZERO(&fdRead);

	closesocket(server);
	WSACleanup();
	msgList.clear();
}

bool Server::isServerRunning(void)
{
	return isThreadRunning;
}

bool Server::getMessage(char buf[MAX_BUF_LEN], unsigned int &len, int &destClientID)
{
	//check if server is running
	if (!isThreadRunning)
	{
		cout << "Server is not running!" << endl;
		return false;
	}
	else if (msgList.empty())
	{
		//no new message
		return false;
	}
	else
	{
		unsigned int _len = msgList.front().len;
		
		len = _len;
		memcpy_s(buf, MAX_BUF_LEN, msgList.front().buf, _len);
		destClientID = msgList.front().sourceID;

		msgList.pop_front();
	}
	return true;
}

bool Server::sendMessage(const char buf[MAX_BUF_LEN], unsigned int len,int destClientID)
{
	//check if server is running
	if (!isThreadRunning)
	{
		cout << "Server is not running!" << endl;
		return false;
	}
	//check if client is exist
	else if (destClientID >= cliNum || destClientID < 0)
	{
		cout << "Client is not exist!" << endl;
		return false;
    }

	return sendingMsgToClient(destClientID, buf, len);
}

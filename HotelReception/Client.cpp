#include "Client.h"
#include <QDebug>

using namespace std;

Client::Client()
{
	isThreadRunning = false;
}

Client::~Client()
{
	endClient();
}

//Private

bool Client::sendingMsgToServer(const char * buf, unsigned int len)
{
	//add package length
	char _buf[MAX_BUF_LEN + 4];

	_buf[0] = (len & 0xFF);
	_buf[1] = (len & 0xFF00) >> 8;
	_buf[2] = (len & 0xFF0000) >> 16;
	_buf[3] = (len & 0xFF000000) >> 24;

	memcpy_s(_buf + 4, MAX_BUF_LEN, buf, len);

    qDebug()<<"len="<<len;

	if (SOCKET_ERROR == (send(sock, _buf, len + 4, 0)))
	{
		cout << "Send error!" << endl;
		return false;
	}

	return true;
}

//Thread function
DWORD WINAPI Client::clientThread(LPVOID lparama)
{
	Client *obj = (Client*)lparama;

	obj->exitCode = true;

	obj->clientRun();

	obj->exitCode = false;

	return 0;
}

//Real running function
void Client::clientRun(void)
{
	while (exitCode)
	{
		timeval t = { 1,0 };
		fd_set fdSav;
		int selectRet = 0;

		while (exitCode)
		{
			fdSav = fdRead;
			
			if ((selectRet = select(0, &fdSav, NULL, NULL, &t) <= 0))
			{
				//Time out or error
				continue;
			}

			if (!checkDataFromServer(selectRet, fdSav))
			{
				//lost connection
				endClient();
				return;
			}
			
		}
	}
}


bool Client::checkDataFromServer(int & ret, const FD_SET fd)
{
	//check if this client has sending request
	if (!FD_ISSET(sock, &fd))
	{
		return true;
	}

	//start recv
	int RecvBytes = 0;
	unsigned int len = 0;
	char buf[MAX_BUF_LEN + 1];
	Buffer tmp = { 0 ,0 };

	//get package length
	RecvBytes = recv(sock, buf, 4, 0);
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
		RecvBytes = recv(sock, buf, len, 0);
		if (RecvBytes == SOCKET_ERROR || RecvBytes == 0)
		{
			cout << "Receive error or lost connection!\n";
			return false;
		}
		
		//store the package
		memcpy_s(pbuf, MAX_BUF_LEN, buf, RecvBytes);

		//move pointer
		pbuf += RecvBytes;
		len -= RecvBytes;

	} while (len > 0);

	//insert into message list
	msgList.push_back(tmp);

	return true;
}

//Public

bool Client::startClient(void)
{
	//check if client is running
	if (isThreadRunning)
	{
		cout << "Error:Client is running!" << endl;
        return true;
	}

	wVersionRequired = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequired, &wsaData) != 0)
	{
		cout << WSAGetLastError() << endl;
		cout << "Error:Failed in WSA init!\n";
		return false;
	}

	//Create socket
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		cout << "Error:Failed to create socket£¡\n\n";
		return false;
	}

	//init server address
	serAddr.sin_addr.S_un.S_addr = inet_addr(DES_IP);
	serAddr.sin_port = htons(DES_PORT);
	serAddr.sin_family = AF_INET;
	memset(serAddr.sin_zero, 0, 8);

	//connect to the server
	if (connect(sock, (SOCKADDR *)&serAddr, sizeof(SOCKADDR_IN)) != 0)
	{
		int nError = WSAGetLastError();
		cout << "Error:Connecting failed\n";
		return false;
	}
	else
	{
		cout << "Connecting succeed\n";
	}

	FD_ZERO(&fdRead);
	FD_SET(sock, &fdRead);

	//Create thread
	hThread = CreateThread(NULL, 0, &clientThread, this, 0, NULL);
	isThreadRunning = true;

	return true;
}

void Client::endClient(void)
{
	exitCode = false;
    isThreadRunning=false;
	Sleep(1000);	//wait for thread ending

	FD_ZERO(&fdRead);

	closesocket(sock);
	WSACleanup();
}

bool Client::getMessage(char buf[MAX_BUF_LEN], unsigned int &len)
{
	//check if client is running
	if (!isThreadRunning)
	{
		cout << "client is not running!" << endl;
		return false;
	}
	else if(msgList.empty())
	{
		//no new message
		return false;
	}
	else
	{
		int _len = msgList.front().len;
		len = _len;
		memcpy_s(buf, MAX_BUF_LEN, msgList.front().buf, _len);
		msgList.pop_front();
	}
	return true;
}

bool Client::sendMessage(const char buf[MAX_BUF_LEN], unsigned int len)
{
	//check if client is running
	if (!isThreadRunning)
	{
		cout << "client is not running!" << endl;
		return false;
	}
	return sendingMsgToServer(buf, len);
}


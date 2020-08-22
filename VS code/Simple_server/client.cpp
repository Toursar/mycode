#include<iostream>
#include<string.h>
#include<winsock.h>
#pragma comment(lib, "ws2_32.lib")

void initialization();

int main()
{
	SOCKET socketfd;
	SOCKADDR_IN server_addr;
	initialization();
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(8080);
	//创建套接字
	socketfd = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(socketfd, (SOCKADDR*)&server_addr, sizeof(SOCKADDR))
		== SOCKET_ERROR)
	{
		std::cout << "服务器连接失败！" << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "服务器连接成功！" << std::endl;
	}
	int sendlen;
	int mesglen;
	char mesg[100];
	char recv_mesg[100];
	while (1)
	{
		memset(mesg, 0, sizeof(mesg));
		std::cout << "input word: ";
		std::cin >> mesg;
		sendlen = send(socketfd, mesg, 100, 0);
		if (sendlen < 0)
		{
			std::cerr << "send error" << std::endl;
			break;
		}
		memset(recv_mesg, 0, sizeof(recv_mesg));
		mesglen = recv(socketfd, recv_mesg, 100, 0);
		if (mesglen < 0)
		{
			std::cerr << "recieve error" << std::endl;
			break;
		}
		else
		{
			std::cout << "message is: " << recv_mesg << std::endl;
			if (!strcmp(recv_mesg, "bye"))
			{
				break;
			}
		}
	}
	std::cout << "任意键以结束";
	std::cin.get();
	std::cin.get();
	closesocket(socketfd);
	WSACleanup();
	return 0;
}

void initialization()
{
	WORD w_req = MAKEWORD(2, 2);
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0)
	{
		std::cerr << "socket error" << std::endl;
	}
	else
	{
		std::cout << "socket success" << std::endl;
	}
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2)
	{
		std::cerr << "套接字库版本号不符！" << std::endl;
		WSACleanup();
	}
	else
	{
		std::cout << "socket success" << std::endl;
	}
}
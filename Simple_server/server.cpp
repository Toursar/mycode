#include<iostream>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
void initialization();
int main() {
	SOCKET socketfd;
	SOCKADDR_IN server_addr;
	initialization();
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(8080);
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(socketfd, (SOCKADDR*)&server_addr, sizeof(server_addr)))
	{
		std::cout << "socket success" << std::endl;
		WSACleanup();
		return 0;
	}
	if (listen(socketfd, 5) < 0)
	{
		std::cerr << "listen error" << std::endl;
		WSACleanup();
	}
	std::cout << "listening..." << std::endl;
	int sock_len = sizeof(SOCKADDR);
	SOCKADDR_IN accept_addr;
	SOCKET acceptfd = accept(socketfd, (SOCKADDR*)&accept_addr, &sock_len);
	if (acceptfd == SOCKET_ERROR)
	{
		std::cerr << "connect error" << std::endl;
		WSACleanup();
		return -1;
	}
	std::cout << "connect establish" << std::endl;
	char recv_mesg[100] = { '0' };
	char mesg[100];
	while (1)
	{
		memset(recv_mesg, 0, sizeof(recv_mesg));
		int recv_len = recv(acceptfd, recv_mesg, 100, 0);
		if (recv_len < 0)
		{
			std::cerr << "accept message error" << std::endl;
			break;
		}
		else
		{
			std::cout << "message: " << recv_mesg << std::endl;
			if (!strcmp(recv_mesg, "bye")) 
			{
				send(acceptfd, "bye", 4, 0);
				break;
			}
		}
		memset(mesg, 0, sizeof(mesg));
		std::cout << "reply :";
		cin >> mesg;
		int send_len = send(acceptfd, mesg, 100, 0);
		if (send_len < 0)
		{
			std::cerr << "send error" << std::endl;
			break;
		}
	}
	std::cout << "任意键以结束";
	std::cin.get();
	//关闭套接字
	closesocket(socketfd);
	closesocket(acceptfd);
	//释放DLL资源
	WSACleanup();
	return 0;
}
void initialization() {
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "初始化套接字库失败！" << endl;
	}
	else {
		cout << "初始化套接字库成功！" << endl;
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "套接字库版本号不符！" << endl;
		WSACleanup();
	}
	else {
		cout << "套接字库版本正确！" << endl;
	}
	//填充服务端地址信息

}
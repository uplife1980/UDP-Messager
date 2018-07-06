#pragma comment(lib,"ws2_32.lib")//导入网络API依赖
#include<WinSock2.h>//使用Windows提供的关于网络的函数
#include<WS2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#include "overall.h"//定义全局常量/变量

void broadcastRec()
{
	BOOL optval = TRUE;
	int addr_bro_len;
	char buf[256];
	DWORD i = 0;


	WORD   wVersionRequested;//定义socket1.1或者socket2.0   
	WSADATA   wsaData;   //定义装载socket版本的变量
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);


	addr_bro_rec.sin_family = AF_INET;
	addr_bro_rec.sin_addr.S_un.S_addr = options.bro_addr;
	addr_bro_rec.sin_port = htons(options.bro_port);


	addr_bro_len = sizeof(addr_bro_rec);

	socket_bro_rec = socket(AF_INET, SOCK_DGRAM, 0);

	if (INVALID_SOCKET == socket_bro_rec)
	{
		printf("socket创建失败,错误代码%d", WSAGetLastError());
		WSACleanup();
		system("pause");

		return;
	}
	//设置套接字可以重用
	if (setsockopt(socket_bro_rec, SOL_SOCKET, SO_REUSEADDR, (char FAR*)&optval,sizeof(optval))==SOCKET_ERROR)
	{
		printf("设置失败,错误代码%d", WSAGetLastError());
		closesocket(socket_bro_rec);
		WSACleanup();
		system("pause");

		return;
	}
	//参数绑定
	if (bind(socket_bro_rec, (sockaddr*)&addr_bro_rec, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		printf("绑定套接字地址失败,错误码%d", WSAGetLastError());
		closesocket(socket_bro_rec);
		WSACleanup();
		system("pause");

		return;
	}

	while (i < options.bro_count)
	{
		recvfrom(socket_bro_rec, buf, 255, 0, (struct sockaddr FAR*)&options.bro_addr, (int FAR*)&addr_bro_len);
		printf("收到消息:%s\n", buf);
		ZeroMemory(buf, 256);
		i++;
	}
	closesocket(socket_bro_rec);
	WSACleanup();
}
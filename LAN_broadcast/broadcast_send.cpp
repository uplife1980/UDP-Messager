#pragma comment(lib,"ws2_32.lib")//导入网络API依赖
#include<WinSock2.h>//使用Windows提供的关于网络的函数
#include<WS2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#include "overall.h"//定义全局常量/变量

void broadcastSend() 
{
	int nlen = sizeof(addr_bro_send);
	BOOL opt = true;
	int ret;
	DWORD i = 0;
	WORD   wVersionRequested;//定义socket1.1或者socket2.0   
	WSADATA   wsaData;   //定义装载socket版本的变量
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);
	socket_bro_send = WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
	if (socket_bro_send == INVALID_SOCKET)
	{
		puts("创建失败,,错误代码");
		printf("%d", WSAGetLastError());
		WSACleanup();
		system("pause");
		return;
	}
	//将设置赋值
	addr_bro_send.sin_family = AF_INET;
	addr_bro_send.sin_addr.S_un.S_addr = options.bro_addr;
	addr_bro_send.sin_port = htons(options.bro_port);

	if (setsockopt(socket_bro_send, SOL_SOCKET, SO_BROADCAST, (char FAR*)&opt, sizeof(opt)) == SOCKET_ERROR)
	{
		printf("设置失败,错误代码:%d", WSAGetLastError());
		closesocket(socket_bro_send);
		WSACleanup();
		system("pause");

		return;
	}

	while (i < options.bro_count)
	{
		char* msg = new char[100];
		fgets(msg, 99, stdin);
	ret = sendto(socket_bro_send,(char*)msg, 256, 0, (const struct  sockaddr*)&addr_bro_send, nlen);
		if (ret == SOCKET_ERROR)
			printf("失败,错误码:%d", WSAGetLastError());
		else {
			printf("发送消息%d次", i);
		}
		i++;
	}
	system("pause");

	closesocket(socket_bro_send);
	WSACleanup();
}
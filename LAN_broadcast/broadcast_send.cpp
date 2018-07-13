#pragma comment(lib,"ws2_32.lib")//导入网络API依赖
#include<WinSock2.h>//使用Windows提供的关于网络的函数
#include<WS2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#include "overall.h"//定义全局常量/变量


//功能:发送信息
//传入变量:无
//传出变量:无
void broadcastSend() 
{
	int nlen = sizeof(addr_bro_send);
	BOOL opt = true;
	int ret;
	DWORD i = 0;
	WORD   wVersionRequested;//定义socket1.1或者socket2.0   
	WSADATA   wsaData;   //定义装载socket版本的变量



	//详情参见broadcast_rec.cpp
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);
	socket_bro_send = WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
	if (socket_bro_send == INVALID_SOCKET)
	{
		puts("----socket创建失败,,错误代码");
		printf("%d\n\n----", WSAGetLastError());
		WSACleanup();
		system("pause");
		return;
	}
	//将设置赋值
	addr_bro_send.sin_family = AF_INET;
	addr_bro_send.sin_addr.S_un.S_addr = options.bro_addr;
	addr_bro_send.sin_port = htons(options.bro_port);


	//详情参见broadcast_rec.cpp
	if (setsockopt(socket_bro_send, SOL_SOCKET, SO_BROADCAST, (char FAR*)&opt, sizeof(opt)) == SOCKET_ERROR)
	{
		printf("----设置失败,错误代码:%d-----\n", WSAGetLastError());
		closesocket(socket_bro_send);
		WSACleanup();
		system("pause");

		return;
	}

	while (i < options.bro_count)
	{
		char* msg = new char[100];
		printf("\n请输入消息:\n");
		fgets(msg, 99, stdin);//等同于gets(),更安全,防溢出
		encrypt(msg);			//对消息进行加密
	ret = sendto(socket_bro_send,(char*)afterpass, 256, 0, (const struct  sockaddr*)&addr_bro_send, nlen);//发送消息并捕获错误:发送参数,数据报的地址,数据报文大小,常数0,发送地址,对方地址长度
		if (ret == SOCKET_ERROR)
			printf("----消息发送失败,错误码:%d\n-----", WSAGetLastError());
		else {
			printf("\n发送成功  (第%d次)\n", i+1);
		}
		i++;
	}
	system("pause");

	closesocket(socket_bro_send);
	WSACleanup();//释放资源
}
#pragma comment(lib,"ws2_32.lib")//导入网络API依赖
#include<WinSock2.h>//使用Windows提供的关于网络的函数
#include<WS2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#include "overall.h"//定义全局常量/变量



//功能:接收数据
//传入变量:无
//传出变量:无
void broadcastRec()
{
	BOOL optval = TRUE;//可重用==TRUE
	int addr_bro_len= sizeof(addr_bro_rec);
	char *buf=new char[256];
	unsigned long int i = 0;
	char *password = options.password;

	WORD   wVersionRequested;//定义socket2.0(socket1.1也可以)   
	WSADATA   wsaData;   //定义装载socket版本的变量
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);//启动


	addr_bro_rec.sin_family = AF_INET;//在socket中只能是静态值AF_INET
	addr_bro_rec.sin_addr.S_un.S_addr = options.bro_addr;//ip赋值
	addr_bro_rec.sin_port = htons(options.bro_port);//端口号赋值

	socket_bro_rec = socket(AF_INET, SOCK_DGRAM, 0);

	if (INVALID_SOCKET == socket_bro_rec)//捕捉错误,错误代码可以从网上找到对应问题
	{
		printf("\n-----socket创建失败,错误代码%d-----", WSAGetLastError());
		WSACleanup();
		system("pause");

		return;
	}
	//设置套接字可以重用
	if (setsockopt(socket_bro_rec, SOL_SOCKET, SO_REUSEADDR, (char FAR*)&optval,sizeof(optval))==SOCKET_ERROR)//名称,基本套接,允许重用,返回值指向的地址
	{
		printf("\n-----重用设置失败,错误代码%d-----", WSAGetLastError());
		closesocket(socket_bro_rec);			//释放资源
		WSACleanup();
		system("pause");
		return;
	}
	//参数绑定
	if (bind(socket_bro_rec, (sockaddr*)&addr_bro_rec, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		printf("\n-----绑定套接字地址失败,错误码%d-----", WSAGetLastError());
		closesocket(socket_bro_rec);
		WSACleanup();
		system("pause");

		return;
	}

	while (i < options.bro_count)		//开始监听端口,并将获得的信息打印出来
	{
		puts("开始接收消息\n");
		recvfrom(socket_bro_rec, buf, 255, 0, (struct sockaddr FAR*)&options.bro_addr, (int FAR*)&addr_bro_len);//参数,报文缓存地址,长度,常数0,数据来源,地址大小
		unencrypt(buf,password);//对消息进行解密
		printf("收到消息:   %s\n", beforepass);
		ZeroMemory(buf, 256);//用0来填充buf
		i++;
	}
	puts("-----消息接收完毕!-----");
	closesocket(socket_bro_rec);
	WSACleanup();		//释放资源
}
#pragma comment(lib,"ws2_32.lib")//导入网络API依赖
#include<WinSock2.h>//使用Windows提供的关于网络的函数
#include<WS2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#include "overall.h"//定义全局常量/变量


int main()
{
	WSADATA wsd;
	initial();
	getOptions();
	printf("%lu\n\n\n\n", options.bro_addr);
	printf("当前参数为:IP地址:%d.%d.%d.%d\n 消息总数:%lu条\n 监听端口:%d\n 工作模式:%d\n启动:%d", a[0],a[1],a[2],a[3], options.bro_count, options.bro_port, options.isSender, options.isSending);
	system("pause");
	getchar();
	if (options.isSending) {
		if (options.isSender)
			broadcastSend();
		else
			broadcastRec();
	}
	return 0;
}
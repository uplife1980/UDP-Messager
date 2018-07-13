#pragma comment(lib,"ws2_32.lib")//导入网络API依赖
#include<WinSock2.h>//使用Windows提供的关于网络的函数
#include<WS2tcpip.h>
#include<stdio.h>
#include "overall.h"//定义全局常量/变量
#include<conio.h>


int main()
{
	initial();	//初始化所有量
	char c;
	do{
	system("cls");
	puts("\n输入  ?  以查看帮助,其余按键进入配置选项");
	_getch() == '?' ? help() : system("cls");
	getOptions();//获取参数
	printf("\n\n当前参数为:IP地址:%d.%d.%d.%d\n 消息总数:%lu条\n 监听端口:%d\n 工作模式:%s\n 工作状态:%s\n传输密码:%s\n\n\n",
		a[0],a[1],a[2],a[3], options.bro_count, options.bro_port, (options.isSender?"发送":"接收"), ((options.isSending)?"工作就绪":"未工作"),options.password);
	printf("----------------------------------\n");
	puts("r 确认,其余按键重新配置");
	while(getchar()!='\n');
	c = _getch();
	} while (c!='r');
	if (options.isSending) {
		if (options.isSender)
			broadcastSend();
		else
			broadcastRec();
	}
	else
	{
		puts("程序没有启动!\n(下次试试输入 -b ?)");
	}
	puts("程序结束,再见!");
	getchar();
	return 0;
}
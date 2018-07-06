#pragma comment(lib,"ws2_32.lib")//导入网络API依赖
#include<WinSock2.h>//使用Windows提供的关于网络的函数
#include<WS2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#include "overall.h"//定义全局常量/变量
unsigned int a[4];

int getNumber()
{
	int temp;
	printf(":");
	if (scanf_s("%d", &temp) == 1)
	{
		return temp;
	}
	else
	{
		return 0;
	}
}
unsigned long int getIP()//输入的是字符串变量,不是const常量,不能使用inet_addr()自动转换成IP
{
	scanf_s("%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]);
	for (int i = 0;i < 4;i++)
	{
		if (a[i] > 255) return 0;
	}
	unsigned long int ip = a[0] + a[1] * 256 + a[2] * 256*256 + a[3] * 256 * 256*256;
	return ip;
}
unsigned long int getIP2()
{
	char temp[16];
	const char *temp2;
	scanf_s("%s", temp);
	temp2 = (const char*)temp;
	unsigned long int i = inet_addr(temp2);
	printf("%lu",i);
	return i;
}
void getOptions()
{
	int i;
	do {
		fgets(get_options, 3, stdin);
		char *j = get_options;
		if (*j == '-') {
			j++;
			switch (*j) {
			case 'b': {	//设置广播启动
				options.isSending = 1;
				break;
			}
			case 'h': {	//hostIP
				
				options.bro_addr = getIP();
				break;
			}
			case 'n': {//消息数目
				
				i=getNumber();
				i ? options.bro_count = i : puts("消息数目输入失败,请重试");
				break;
			}
			case 'p': {//监听端口
				i = getNumber();
				i ? options.bro_port=i: puts("监听端口输入失败,请重试");
				break;
			}
			case 's': {//设置为接受者/发送者
				(!getNumber()) ? options.isSender = 0 : options.isSender = 1;
				break;
			}
			case 'q': {//退出设置选项
				return;
			}
			default: {
				printf("参数设置有误,请重新输入.");
			}
			}
		}
		else{printf("请继续输入参数, -q 退出");}
	} while (1);
}
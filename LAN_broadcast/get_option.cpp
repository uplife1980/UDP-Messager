#pragma comment(lib,"ws2_32.lib")//导入网络API依赖
#include<WinSock2.h>//使用Windows提供的关于网络的函数
#include<WS2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#include "overall.h"//定义全局常量/变量
unsigned int a[4] = {0};

unsigned int getNumber()
{
	unsigned int temp=0;
	printf("请输入值:  ");
	scanf_s("%u", &temp);
	return temp;

}
unsigned long int getIP()//输入的是字符串变量,不是const常量,不能使用inet_addr()自动转换成IP,只能手动转换
{
	scanf_s("%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]);
	for (int i = 0;i < 4;i++)
	{
		if (a[i] > 255) 
			return 0;
	}
	unsigned long int ip = a[0] + a[1] * 256 + a[2] * 256*256 + a[3] * 256 * 256*256;
	return ip;
}

void getOptions()
{
	unsigned int i;
	puts("-----------进入配置页面--------");
	do {
		printf("\n-----请输入参数, -q 退出-----\n");
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
				unsigned long int x = getIP();
				x ? options.bro_addr = x: puts("ip获取失败,请重试");
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
				i = !getNumber();
				i ? options.isSender = 0 : options.isSender = 1;
				break;
			}
			case 'q': {//退出设置选项
				return;
			}
			default: {
				printf("\n-----参数设置有误,请重新输入.-----\n");
				continue;
			}
			}
		}
		else {
			continue;
		}
	} while (1);
}
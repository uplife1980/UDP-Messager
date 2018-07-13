#include <stdio.h>
#include<string.h>
#pragma comment(lib,"ws2_32.lib")//导入网络API依赖
#include<WinSock2.h>//使用Windows提供的关于网络的函数
#include<WS2tcpip.h>
#include "overall.h"//定义全局常量/变量
void encrypt(char *ch1)//使用xor进行加密消息
{
	int len = strlen(ch1);
	int i;
	for (i = 0;i < len-1;i++)
	{
		afterpass[i] = ch1[i] ^ options.password[(i%strlen(options.password))];
	}
	afterpass[i] ='\0';
}
void unencrypt(char *ch1,char *password)//用同样的方式解密消息,但是由于同一台电脑上不能有两个函数同时读取options.password(会读到null),所以通过传递变量的方式获取秘钥
{
	int len = strlen(ch1);
	int i;
	for (i = 0;i < len;i++)
	{
		beforepass[i] = ch1[i] ^ password[(i%strlen(password))];
	}
	beforepass[i] = '\0';
}

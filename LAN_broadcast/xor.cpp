#include <stdio.h>
#include<string.h>
#pragma comment(lib,"ws2_32.lib")//导入网络API依赖
#include<WinSock2.h>//使用Windows提供的关于网络的函数
#include<WS2tcpip.h>
#include "overall.h"//定义全局常量/变量

//功能:对将要发送的字符串进行加密,存储在全局变量afterpass中
//传入变量:用户输入的字符串
//传出变量:无
void encrypt(char *ch1)//使用xor进行加密消息
{
	int len = strlen(ch1);
	int i;
	for (i = 0;i < len-1;i++)
	{
		afterpass[i] = ch1[i] ^ options.password[(i%strlen(options.password))];//防止password位数不足,使用循环
	}
	afterpass[i] ='\0';//对\0不加密
}

//功能:对接收到的字符串进行解密
//传入参数:获得的字符串,秘钥
//传出参数:无
void unencrypt(char *ch1,char *password)//用同样的方式解密消息,但是由于同一台电脑上不能有两个函数同时读取options.password(会读到null),所以通过传递变量的方式获取秘钥
{
	int len = strlen(ch1);
	int i;
	for (i = 0;i < len;i++)
	{
		beforepass[i] = ch1[i] ^ password[(i%strlen(password))];
	}
	beforepass[i] = '\0';		//结尾补\0
}

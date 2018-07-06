#pragma comment(lib,"ws2_32.lib")//导入网络API依赖
#include<WinSock2.h>//使用Windows提供的关于网络的函数
#include<WS2tcpip.h>
#include "overall.h"//定义全局常量/变量

//在这里定义所有的全局变量
SOCKET socket_bro_send; //定义套接
SOCKET socket_bro_rec;
struct sockaddr_in addr_bro_send; //发送者主机数据,包含端口号和ip   
struct sockaddr_in addr_bro_rec;	//接受者主机
char get_options[3];				//未经处理的options
struct options options;
void initial()//初始化全局变量
{
	options.isSender = 0;		//默认是接受者
	options.isSending = 1;		//默认不开启功能
	options.bro_count = MAX_MASSAGES;//每次最多接收/发送的消息数目
	options.bro_port = BROADCAST_PORT;//使用的端口,默认14567
	options.bro_addr = 0xffffffff;//默认ip:255.255.255.255(网关地址)
}
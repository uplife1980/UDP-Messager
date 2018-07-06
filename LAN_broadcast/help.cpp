#include<stdio.h>
#include<conio.h> //用于无回显地读取字符

void help()
{
	printf("-----  -b  开启通讯服务       ----\n\n");
	printf("-----  -h  修改ip地址         ----\n");
	printf("-----    注:发送端和接收端必须----\n");
	printf("-----    同时指向接收端的ip   ----\n\n");
	printf("-----  -s    角色             ----\n");
	printf("-----    1:发送端             ----\n");
	printf("-----    0:接收端(默认)       ----\n\n");
	printf("-----  -p  服务通讯端口       ----\n");
	printf("-----    默认值:14567         ----\n\n");
	printf("-----  -n  发送/接收消息总数  ----\n");
	printf("-----    默认值:20            ----\n\n");
	printf("-----  -q  退出配置界面       ----\n\n");
	printf("-----  任意键继续......       ----\n\n");

	_getch();
}
#include <stdio.h>
#include<string.h>
#pragma comment(lib,"ws2_32.lib")//��������API����
#include<WinSock2.h>//ʹ��Windows�ṩ�Ĺ�������ĺ���
#include<WS2tcpip.h>
#include "overall.h"//����ȫ�ֳ���/����

//����:�Խ�Ҫ���͵��ַ������м���,�洢��ȫ�ֱ���afterpass��
//�������:�û�������ַ���
//��������:��
void encrypt(char *ch1)//ʹ��xor���м�����Ϣ
{
	int len = strlen(ch1);
	int i;
	for (i = 0;i < len-1;i++)
	{
		afterpass[i] = ch1[i] ^ options.password[(i%strlen(options.password))];//��ֹpasswordλ������,ʹ��ѭ��
	}
	afterpass[i] ='\0';//��\0������
}

//����:�Խ��յ����ַ������н���
//�������:��õ��ַ���,��Կ
//��������:��
void unencrypt(char *ch1,char *password)//��ͬ���ķ�ʽ������Ϣ,��������ͬһ̨�����ϲ�������������ͬʱ��ȡoptions.password(�����null),����ͨ�����ݱ����ķ�ʽ��ȡ��Կ
{
	int len = strlen(ch1);
	int i;
	for (i = 0;i < len;i++)
	{
		beforepass[i] = ch1[i] ^ password[(i%strlen(password))];
	}
	beforepass[i] = '\0';		//��β��\0
}

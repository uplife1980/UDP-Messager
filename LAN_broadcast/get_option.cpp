#pragma comment(lib,"ws2_32.lib")//��������API����
#include<WinSock2.h>//ʹ��Windows�ṩ�Ĺ�������ĺ���
#include<WS2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#include "overall.h"//����ȫ�ֳ���/����
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
unsigned long int getIP()//��������ַ�������,����const����,����ʹ��inet_addr()�Զ�ת����IP
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
			case 'b': {	//���ù㲥����
				options.isSending = 1;
				break;
			}
			case 'h': {	//hostIP
				
				options.bro_addr = getIP();
				break;
			}
			case 'n': {//��Ϣ��Ŀ
				
				i=getNumber();
				i ? options.bro_count = i : puts("��Ϣ��Ŀ����ʧ��,������");
				break;
			}
			case 'p': {//�����˿�
				i = getNumber();
				i ? options.bro_port=i: puts("�����˿�����ʧ��,������");
				break;
			}
			case 's': {//����Ϊ������/������
				(!getNumber()) ? options.isSender = 0 : options.isSender = 1;
				break;
			}
			case 'q': {//�˳�����ѡ��
				return;
			}
			default: {
				printf("������������,����������.");
			}
			}
		}
		else{printf("������������, -q �˳�");}
	} while (1);
}
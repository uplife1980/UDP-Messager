#pragma comment(lib,"ws2_32.lib")//��������API����
#include<WinSock2.h>//ʹ��Windows�ṩ�Ĺ�������ĺ���
#include<WS2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#include "overall.h"//����ȫ�ֳ���/����


int main()
{
	WSADATA wsd;
	initial();
	getOptions();
	printf("%lu\n\n\n\n", options.bro_addr);
	printf("��ǰ����Ϊ:IP��ַ:%d.%d.%d.%d\n ��Ϣ����:%lu��\n �����˿�:%d\n ����ģʽ:%d\n����:%d", a[0],a[1],a[2],a[3], options.bro_count, options.bro_port, options.isSender, options.isSending);
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
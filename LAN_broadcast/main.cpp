#pragma comment(lib,"ws2_32.lib")//��������API����
#include<WinSock2.h>//ʹ��Windows�ṩ�Ĺ�������ĺ���
#include<WS2tcpip.h>
#include<stdio.h>
#include "overall.h"//����ȫ�ֳ���/����
#include<conio.h>


int main()
{
	initial();	//��ʼ��������
	char c;
	do{
	system("cls");
	puts("\n����  ?  �Բ鿴����,���ఴ����������ѡ��");
	_getch() == '?' ? help() : system("cls");
	getOptions();//��ȡ����
	printf("\n\n��ǰ����Ϊ:IP��ַ:%d.%d.%d.%d\n ��Ϣ����:%lu��\n �����˿�:%d\n ����ģʽ:%s\n ����״̬:%s\n��������:%s\n\n\n",
		a[0],a[1],a[2],a[3], options.bro_count, options.bro_port, (options.isSender?"����":"����"), ((options.isSending)?"��������":"δ����"),options.password);
	printf("----------------------------------\n");
	puts("r ȷ��,���ఴ����������");
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
		puts("����û������!\n(�´��������� -b ?)");
	}
	puts("�������,�ټ�!");
	getchar();
	return 0;
}
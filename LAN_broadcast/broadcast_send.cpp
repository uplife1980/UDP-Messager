#pragma comment(lib,"ws2_32.lib")//��������API����
#include<WinSock2.h>//ʹ��Windows�ṩ�Ĺ�������ĺ���
#include<WS2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#include "overall.h"//����ȫ�ֳ���/����


//����:������Ϣ
//�������:��
//��������:��
void broadcastSend() 
{
	int nlen = sizeof(addr_bro_send);
	BOOL opt = true;
	int ret;
	DWORD i = 0;
	WORD   wVersionRequested;//����socket1.1����socket2.0   
	WSADATA   wsaData;   //����װ��socket�汾�ı���



	//����μ�broadcast_rec.cpp
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);
	socket_bro_send = WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
	if (socket_bro_send == INVALID_SOCKET)
	{
		puts("----socket����ʧ��,,�������");
		printf("%d\n\n----", WSAGetLastError());
		WSACleanup();
		system("pause");
		return;
	}
	//�����ø�ֵ
	addr_bro_send.sin_family = AF_INET;
	addr_bro_send.sin_addr.S_un.S_addr = options.bro_addr;
	addr_bro_send.sin_port = htons(options.bro_port);


	//����μ�broadcast_rec.cpp
	if (setsockopt(socket_bro_send, SOL_SOCKET, SO_BROADCAST, (char FAR*)&opt, sizeof(opt)) == SOCKET_ERROR)
	{
		printf("----����ʧ��,�������:%d-----\n", WSAGetLastError());
		closesocket(socket_bro_send);
		WSACleanup();
		system("pause");

		return;
	}

	while (i < options.bro_count)
	{
		char* msg = new char[100];
		printf("\n��������Ϣ:\n");
		fgets(msg, 99, stdin);//��ͬ��gets(),����ȫ,�����
		encrypt(msg);			//����Ϣ���м���
	ret = sendto(socket_bro_send,(char*)afterpass, 256, 0, (const struct  sockaddr*)&addr_bro_send, nlen);//������Ϣ���������:���Ͳ���,���ݱ��ĵ�ַ,���ݱ��Ĵ�С,����0,���͵�ַ,�Է���ַ����
		if (ret == SOCKET_ERROR)
			printf("----��Ϣ����ʧ��,������:%d\n-----", WSAGetLastError());
		else {
			printf("\n���ͳɹ�  (��%d��)\n", i+1);
		}
		i++;
	}
	system("pause");

	closesocket(socket_bro_send);
	WSACleanup();//�ͷ���Դ
}
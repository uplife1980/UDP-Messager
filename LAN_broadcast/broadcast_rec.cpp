#pragma comment(lib,"ws2_32.lib")//��������API����
#include<WinSock2.h>//ʹ��Windows�ṩ�Ĺ�������ĺ���
#include<WS2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#include "overall.h"//����ȫ�ֳ���/����

void broadcastRec()
{
	BOOL optval = TRUE;
	int addr_bro_len;
	char buf[256];
	DWORD i = 0;


	WORD   wVersionRequested;//����socket1.1����socket2.0   
	WSADATA   wsaData;   //����װ��socket�汾�ı���
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);


	addr_bro_rec.sin_family = AF_INET;
	addr_bro_rec.sin_addr.S_un.S_addr = options.bro_addr;
	addr_bro_rec.sin_port = htons(options.bro_port);


	addr_bro_len = sizeof(addr_bro_rec);

	socket_bro_rec = socket(AF_INET, SOCK_DGRAM, 0);

	if (INVALID_SOCKET == socket_bro_rec)
	{
		printf("socket����ʧ��,�������%d", WSAGetLastError());
		WSACleanup();
		system("pause");

		return;
	}
	//�����׽��ֿ�������
	if (setsockopt(socket_bro_rec, SOL_SOCKET, SO_REUSEADDR, (char FAR*)&optval,sizeof(optval))==SOCKET_ERROR)
	{
		printf("����ʧ��,�������%d", WSAGetLastError());
		closesocket(socket_bro_rec);
		WSACleanup();
		system("pause");

		return;
	}
	//������
	if (bind(socket_bro_rec, (sockaddr*)&addr_bro_rec, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		printf("���׽��ֵ�ַʧ��,������%d", WSAGetLastError());
		closesocket(socket_bro_rec);
		WSACleanup();
		system("pause");

		return;
	}

	while (i < options.bro_count)
	{
		recvfrom(socket_bro_rec, buf, 255, 0, (struct sockaddr FAR*)&options.bro_addr, (int FAR*)&addr_bro_len);
		printf("�յ���Ϣ:%s\n", buf);
		ZeroMemory(buf, 256);
		i++;
	}
	closesocket(socket_bro_rec);
	WSACleanup();
}
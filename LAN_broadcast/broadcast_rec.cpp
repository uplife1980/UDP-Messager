#pragma comment(lib,"ws2_32.lib")//��������API����
#include<WinSock2.h>//ʹ��Windows�ṩ�Ĺ�������ĺ���
#include<WS2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#include "overall.h"//����ȫ�ֳ���/����



//����:��������
//�������:��
//��������:��
void broadcastRec()
{
	BOOL optval = TRUE;//������==TRUE
	int addr_bro_len= sizeof(addr_bro_rec);
	char *buf=new char[256];
	unsigned long int i = 0;
	char *password = options.password;

	WORD   wVersionRequested;//����socket2.0(socket1.1Ҳ����)   
	WSADATA   wsaData;   //����װ��socket�汾�ı���
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);//����


	addr_bro_rec.sin_family = AF_INET;//��socket��ֻ���Ǿ�ֵ̬AF_INET
	addr_bro_rec.sin_addr.S_un.S_addr = options.bro_addr;//ip��ֵ
	addr_bro_rec.sin_port = htons(options.bro_port);//�˿ںŸ�ֵ

	socket_bro_rec = socket(AF_INET, SOCK_DGRAM, 0);

	if (INVALID_SOCKET == socket_bro_rec)//��׽����,���������Դ������ҵ���Ӧ����
	{
		printf("\n-----socket����ʧ��,�������%d-----", WSAGetLastError());
		WSACleanup();
		system("pause");

		return;
	}
	//�����׽��ֿ�������
	if (setsockopt(socket_bro_rec, SOL_SOCKET, SO_REUSEADDR, (char FAR*)&optval,sizeof(optval))==SOCKET_ERROR)//����,�����׽�,��������,����ֵָ��ĵ�ַ
	{
		printf("\n-----��������ʧ��,�������%d-----", WSAGetLastError());
		closesocket(socket_bro_rec);			//�ͷ���Դ
		WSACleanup();
		system("pause");
		return;
	}
	//������
	if (bind(socket_bro_rec, (sockaddr*)&addr_bro_rec, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		printf("\n-----���׽��ֵ�ַʧ��,������%d-----", WSAGetLastError());
		closesocket(socket_bro_rec);
		WSACleanup();
		system("pause");

		return;
	}

	while (i < options.bro_count)		//��ʼ�����˿�,������õ���Ϣ��ӡ����
	{
		puts("��ʼ������Ϣ\n");
		recvfrom(socket_bro_rec, buf, 255, 0, (struct sockaddr FAR*)&options.bro_addr, (int FAR*)&addr_bro_len);//����,���Ļ����ַ,����,����0,������Դ,��ַ��С
		unencrypt(buf,password);//����Ϣ���н���
		printf("�յ���Ϣ:   %s\n", beforepass);
		ZeroMemory(buf, 256);//��0�����buf
		i++;
	}
	puts("-----��Ϣ�������!-----");
	closesocket(socket_bro_rec);
	WSACleanup();		//�ͷ���Դ
}
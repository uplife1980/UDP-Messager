#pragma comment(lib,"ws2_32.lib")//��������API����
#include<WinSock2.h>//ʹ��Windows�ṩ�Ĺ�������ĺ���
#include<WS2tcpip.h>
#include "overall.h"//����ȫ�ֳ���/����

//�����ﶨ�����е�ȫ�ֱ���
SOCKET socket_bro_send; //�����׽�
SOCKET socket_bro_rec;
struct sockaddr_in addr_bro_send; //��������������,�����˿ںź�ip   
struct sockaddr_in addr_bro_rec;	//����������
char get_options[3];				//δ�������options
struct options options;
void initial()//��ʼ��ȫ�ֱ���
{
	options.isSender = 0;		//Ĭ���ǽ�����
	options.isSending = 1;		//Ĭ�ϲ���������
	options.bro_count = MAX_MASSAGES;//ÿ��������/���͵���Ϣ��Ŀ
	options.bro_port = BROADCAST_PORT;//ʹ�õĶ˿�,Ĭ��14567
	options.bro_addr = 0xffffffff;//Ĭ��ip:255.255.255.255(���ص�ַ)
}
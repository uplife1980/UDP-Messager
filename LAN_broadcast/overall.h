//�������г���
#define BROADCAST_PORT 14567 //�㲥ʹ�õĶ˿�
#define MAX_MASSAGES 20//�����յ���Ϣ

//�������е�extern����
extern char get_options[3];
struct options {
	int isSender; //�жϽ����߻��Ƿ�����
	int bro_port;//�㲥�˿�
	unsigned long bro_addr;//�㲥��ַ
	unsigned long bro_count; //message����
	int isSending; //�Ƿ��ڽ���ģʽ
};
extern SOCKET socket_bro_send; 
extern SOCKET socket_bro_rec;
extern struct options options;
extern 	unsigned int a[4]; //��¼IP
extern struct sockaddr_in addr_bro_send; //������ip
extern struct sockaddr_in addr_bro_rec;	//������ip
//�������к���
int main();
void initial();
void getOptions();
void broadcastSend();
void broadcastRec();


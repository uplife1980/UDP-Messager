//包含所有常量
#define BROADCAST_PORT 14567 //广播使用的端口
#define MAX_MASSAGES 20//最多接收的信息

//包含所有的extern变量
extern char get_options[3];
struct options {
	int isSender; //判断接受者还是发送者
	int bro_port;//广播端口
	unsigned long bro_addr;//广播地址
	unsigned long bro_count; //message总数
	int isSending; //是否处于接受模式
};
extern SOCKET socket_bro_send; 
extern SOCKET socket_bro_rec;
extern struct options options;
extern 	unsigned int a[4]; //记录IP
extern struct sockaddr_in addr_bro_send; //发送者ip
extern struct sockaddr_in addr_bro_rec;	//接受者ip
//包含所有函数
int main();
void initial();
void getOptions();
void broadcastSend();
void broadcastRec();


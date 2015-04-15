#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "util.h"
#ifndef __SOCKET__
#define __SOCKET__
#include<sys/socket.h>
#include<sys/un.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#endif


extern bool loginflag;
const int LEN =  256;
extern int msgqid;
struct msg_s
{
	long int mytype;
	char msgtext[LEN];
};

//mytype = 1 //login ok
class client
{
public:
	int m_socket;
	char *m_ip;
	int m_port;
	string username;
	string passwd;
	string m_lotterynum; //开奖次数
    string m_lotteryinterval; //多少秒间隔
	
	struct msg_s msg;
	static int frame;
    client()	
	{
		m_socket = socket(AF_INET, SOCK_STREAM, 0);
		if(m_socket < 0)
		{
			cout << "client error\n";
		}

		mutex_init(&m_mutex);
		loginflag = false;
		memset(&msg, 0, sizeof(msg));
	}
	
	~client()
	{
	}
	void readconf(const char* file);
	int m_connect();
	int m_setlotteryinter(int interval);
	int m_setlottnum(int num);
	int m_tcprecv(char *recvbuf, int len, int timeout);
	int m_tcpsend(char *sendbuf, int len) const;
	int m_loginserver(int cmd) const;
	int m_getLottery(int cmd) const;
	void varygetlottery(char *buf) const;
	void m_recvthrdstart(client* cli);
	void varyloginOK(client* cli, char * buf);
	void varysetlotOK(client* cli, char *buf);
	void varyplayend(client *cli, char *buf);
	int m_setLottery(int cmd) const;
friend void recvthrdfunc(void *arg);
private:	

	char *m_record;
	char *m_recordfile;
	pthread_t pid;
	pthread_mutex_t m_mutex;
};



#endif

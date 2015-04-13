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

	struct msg_s msg;
	static int frame;
    client(char *ip, int port, int lotterynum, int lotteryinterval, char *record, char *recordfile):
		m_ip(ip),m_port(port),m_lotterynum(lotterynum),m_lotteryinterval(lotteryinterval),m_record(record),m_recordfile(recordfile)
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
	int m_connect();
	int m_setlotteryinter(int interval);
	int m_setlottnum(int num);
	int m_tcprecv(char *recvbuf, int len, int timeout);
	int m_tcpsend(char *sendbuf, int len) const;
	int m_loginserver(int cmd, const string& username, const string& passwd) const;
	int m_getLottery(int cmd) const;
	void varygetlottery(char *buf) const;
	void m_recvthrdstart(client* cli);
	void varyloginOK(client* cli, char * buf);
	void varysetlotOK(client* cli, char *buf);
	void varyplayend(client *cli, char *buf);
	int m_setLottery(int cmd, const string& num, const string& timeval) const;
friend void recvthrdfunc(void *arg);
private:
	int m_lotterynum; //开奖次数
    int m_lotteryinterval; //多少秒间隔
	char *m_record;
	char *m_recordfile;
	pthread_t pid;
	pthread_mutex_t m_mutex;
};



#endif

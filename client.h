#include "util.h"
#include<sys/socket.h>
#include<sys/un.h>
#include<netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <ctime>

extern bool loginflag;
class client
{
public:
	 int m_socket;

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
	}
	
	~client()
	{
		delete m_ip;
		m_ip = NULL;
		delete m_recordfile;
		m_recordfile = NULL;
	}
	
	int m_connect();
	int m_setlotteryinter(int interval);
	int m_setlotterynum(int num);
	int m_tcprecv(char *recvbuf, int len, int timeout);
	int m_tcpsend(char *sendbuf, int len);
	int m_loginserver(int cmd, const string& username, const string& passwd);
	void m_recvthrdstart(client* cli);
	void varyloginOK(char * buf);
friend void recvthrdfunc(void *arg);
private:
	char *m_ip;
	int m_port;
	int m_lotterynum; //开奖次数
    int m_lotteryinterval; //多少秒间隔
	char *m_record;
	char *m_recordfile;
	pthread_t pid;
	pthread_mutex_t m_mutex;
};




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

class client
{
private:
	char *m_ip;
	int m_port;
	int m_lotterynum; //开奖次数
    int m_lotteryinterval; //多少秒间隔
	char *m_record;
	char *m_recordfile;
	int m_socket;
public:
    client(char *ip, int port, int lotterynum, int lotteryinterval, char *record, char *recordfile):
		m_ip(ip),m_port(port),m_lotterynum(lotterynum),m_lotteryinterval(lotteryinterval),m_record(record),m_recordfile(recordfile)
	{
		m_socket = socket(AF_INET, SOCK_STREAM, 0);
		if(m_socket < 0)
		{
			cout << "client error\n";
		}
	}
	
	~client()
	{
		delete m_ip;
		m_ip = NULL;
		delete m_recordfile;
		m_recordfile = NULL;
  		delete m_lotterynum;
		m_lotterynum = NULL;
	}
	
	int m_connect();
	int m_setlotteryinter(int interval);
	int m_setlotterynum(int num);
	int m_tcprecv();
	int m_tcpsend();
	
};

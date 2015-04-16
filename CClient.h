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


const int LEN =  256;
extern int msgqid;
struct msg_s
{
	long int mytype;
	char msgtext[LEN];
};

//mytype = 1 //login ok
class CClient
{
public:
	int m_socket;
	char *m_ip;
	int m_port;
	string m_username;
	string m_passwd;
	string m_lotterynum; //开奖次数
    string m_lotteryinterval; //多少秒间隔
	
	struct msg_s m_msg;
	static int sm_frame;
    CClient()	
	{
		m_socket = socket(AF_INET, SOCK_STREAM, 0);
		if(m_socket < 0)
		{
			cout << "CClient error\n";
		}

		mutex_init(&m_mutex);
		memset(&m_msg, 0, sizeof(m_msg));
	}
	
	~CClient()
	{
	}
	void ReadConf(const char* file);
	int ConnServer();
	int SetLotInterval(int interval);
	int SetLotNum(int num);
	int TcpRecv(char *recvbuf, int len, int timeout);
	int TcpSend(char *sendbuf, int len) const;
	int LoginServer(int cmd) const;
	int GetLottery(int cmd) const;
	void VaryGetLottery(char *buf) const;
	void RecvThrdStart(CClient* cli);
	void VaryLoginOK(CClient* cli, char * buf);
	void VarySetLotOK(CClient* cli, char *buf);
	void VaryPlayEnd(CClient *cli, char *buf);
	int SetLottery(int cmd) const;
friend void RecvThrdFunc(void *arg);
private:	

	char *m_record;
	char *m_recordfile;
	pthread_t m_pid;
	pthread_mutex_t m_mutex;
};



#endif


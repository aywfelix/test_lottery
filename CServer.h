/*
 * Filename: CServer.h
 *                
 * Version:       
 * Author:        LaiJia <laijia2008@126.com>
 * Created at:    Wed Apr  8 16:54:50 2015
 *                
 * Description:   
 *
 */
#ifndef __SERVER_H__
#define __SERVER_H__
#include "util.h"
#ifndef __SOCKET__
#define __SOCKET__
#include<sys/socket.h>
#include<sys/un.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#endif
#ifndef __CONTAINER__
#define __CONTAINER__
#include <vector>
#include <map>
#endif
#include <sys/epoll.h>

const int MAX_NUM = 200;
const int BACKLOG = 10;
//默认服务器端 ip 127.0.0.1 port 9999

class CServer
{
public:
	epoll_event m_events[MAX_NUM];
	int m_epfd;
	int m_socket;
	int m_clisock;
	int m_TmpSock;
	static int sm_frame;
	map<string, string> m_userpwd; //保存用户名和密码,密码暂用明文
	map<int, string> m_user;
	int m_lotterynum;
	int m_lotteryinterval;
	pthread_mutex_t m_mutex;
	pthread_t m_pid;
	CServer()
	{
		m_socket = socket(AF_INET, SOCK_STREAM, 0);
		if(m_socket < 0)
		{
			cout << "create socket error\n";
			return;
		}

		mutex_init(&m_mutex);
		m_vec.resize(100);
	}
	~CServer()
	{
		close(m_socket);
	}
	void SetAddr(struct sockaddr_in &sin) const;
	void SetParameters() const;
	int Bind( struct sockaddr_in& sin) const;
	int Listen( int backlog) const;
	int Accept(struct sockaddr_in* cin) const;
	int ReadUser(const string userfile);
	void GetPocketPool();
	void Play(int* array) const;
	int	TcpRecv(int m_socket, char *recvbuf, int len, int timeout);
	int TcpSend(int m_socket, char *sendbuf, int len) const;
	void InitEvent();
	int ReadConf(const char* file);
	// void RecvThrdFunc(void *arg)
private:
	char *m_ip;
	int m_port;

	vector<int> m_vec; //pocket pool
    char content[256];

};
void RecvThrdFunc(void* arg);
void RecvThrd(CServer* serv);
int LoginOK(CServer* serv, bool flag, int sockfd);
int SetLottery(char* buf, CServer* serv, int sockfd);
int VaryLogin(char *buf, CServer* serv ,int sockfd);
int SetLotteryOK(CServer* serv, int sockfd);
int Lottery2Client(int* array, CServer* serv, int sockfd);
int PlayEnd(CServer* serv, int sockfd);
int AddFd(CServer* serv, bool flag);
void ET(CServer* serv, int num);
void DeleteFd(CServer* serv, int fd);

#endif












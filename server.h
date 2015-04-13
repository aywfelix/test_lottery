/*
 * Filename: server.h
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

//默认服务器端 ip 127.0.0.1 port 9999
class server
{
public:

	static int frame;
	map<string, string> userpwd; //保存用户名和密码,密码暂用明文
	int lotterynum;
	int lotteryinterval;
	server(char *ip, int port):m_ip(ip), m_port(port)
	{
		if(m_ip == NULL || m_port <0)
		{
			cout << "server ip and port error\n";
			return;
		}
		m_socket = socket(AF_INET, SOCK_STREAM, 0);
		if(m_socket < 0)
		{
			cout << "create socket error\n";
			return;
		}

		mutex_init(&m_mutex);
		vec.resize(100);
	}
	~server()
	{
		delete m_ip;
		close(m_socket);
	}
	void m_setaddr(struct sockaddr_in &sin) const;
	void m_setparameters() const;
	int m_bind( struct sockaddr_in& sin) const;
	int m_listen( int backlog) const;
	int m_accept(struct sockaddr_in* cin) const;
	int m_readuser(const string userfile);
	void m_getpocketpoll();
	void m_recvthrdstart(server* serv);
	void m_play(int* array) const;
	int	m_tcprecv(int m_socket, char *recvbuf, int len, int timeout);
	int m_tcpsend(int m_socket, char *sendbuf, int len) const;

	friend void recvthrdfunc(void *arg);
    
private:
	char *m_ip;
	int m_port;
	int m_socket;
	vector<int> vec; //pocket pool
	char recvbuf[1024];
	char sendbuf[1024];
	pthread_t m_pid;
	pthread_mutex_t m_mutex;
};

extern int clisock;
inline int m_loginOK(server* serv, bool flag);
inline int setlottery(char* buf, server* serv);
inline int m_varylogin(char *buf, server* serv);
inline int setLotteryOK(server* serv);
inline int lotterytoclient(int* array, server* serv);
inline int playend(server* serv);
#endif







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

#include "util.h"
#include<sys/socket.h>
#include<sys/un.h>
#include<netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

//默认服务器端 ip 127.0.0.1 port 9999
class server
{
public:
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
	
	}
	~server()
	{
		delete m_ip;
		close(m_socket);
	}
	void m_setaddr(struct sockaddr_in &sin);
	void m_setparameters();
	int m_bind( struct sockaddr_in& sin);
	int m_listen( int backlog);
	int m_accept(struct sockaddr_in* cin);
	int m_tcprecv();
	int m_tcpsend();
private:
	char *m_ip;
	int m_port;
	int m_socket;
	char recvbuf[1024];
	char sendbuf[1024];
};


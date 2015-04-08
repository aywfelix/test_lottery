#include "server.h"
void server::m_setaddr(struct sockaddr_in &sin)
{
	// struct sockaddr_in sin;
	memset(&sin, 0 , sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(m_ip);
	sin.sin_port = htons(m_port);
}

void server::m_setparameters()
{
	int readdr = 1,recvbuf = 128*1024, sendbuf = 128*1024;
	struct linger ling;
	ling.l_linger = 0;
	ling.l_onoff = 1;

	setsockopt(m_socket, SOL_SOCKET,SO_REUSEADDR, &readdr, sizeof(int));
	setsockopt(m_socket, SOL_SOCKET,SO_RCVBUF, &recvbuf, sizeof(int));
	setsockopt(m_socket, SOL_SOCKET, SO_SNDBUF, &sendbuf, sizeof(int));
	setsockopt(m_socket, SOL_SOCKET, SO_LINGER, (const char *)&ling, sizeof(struct linger));

}

int server::m_bind( struct sockaddr_in& sin)
{
	int ret = 0;
	ret = bind(m_socket, (struct sockaddr*)&sin, sizeof(sin));
	if(ret <0)
	{
		cout << "bind error\n";
	}
	return ret;
}

int server::m_listen( int backlog)
{
	int ret = 0;
	if((ret = listen(m_socket, backlog)) < 0)
	{
		cout<< "listen error\n";
	}
	return ret;
}

int server::m_accept(struct sockaddr_in* cin)
{
	socklen_t socklen = sizeof(cin);
	int clisock = 0;
    clisock = accept(m_socket, (struct sockaddr*)cin, &socklen);
	if(clisock <0)
	{
		cout << " server accept error\n";
		return -1;
	}
	return clisock;
}

int server::m_tcprecv()
{}

int server::m_tcpsend()
{}

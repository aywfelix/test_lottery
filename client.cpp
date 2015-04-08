#include "client.h"

int client::m_connect()
{
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(m_ip);
	sin.sin_port = htons(m_port);
	int ret = connect(m_socket, (struct sockaddr *)&sin, sizeof(struct sockaddr));
	if(ret < 0)
	{
		cout << "connect server error\n";		
		return -1;
	}
		
	cout << "connect server ok\n";
}

int client::m_setlotteryinter(int interval)
{
	m_lotteryinterval = interval;
}
int client::m_setlotterynum(int num)
{
	m_lotterynum = num;
}

int client::m_tcprecv(char *recvbuf, int len, int timeout)
{
	if(NULL == recvbuf || len <=0 )
		return -1;
	int ret = 0;
	fd_set fds;
	struct timeval interval;
   	memset(recvbuf ,0 ,sizeof(recvbuf));
	FD_ZERO(&fds);
	FD_SET(m_socket, &fds);
    if(timeout < 0)
	{
		ret = select(m_socket+1, &fds, NULL,NULL,NULL);
		if(FD_ISSET(m_socket, &fds))
		{
			ret = recv(m_socket , recvbuf, len, 0);
		}
   	}
	else
	{
		interval.tv_sec = timeout;
		interval.tv_usec = 0;
		ret = select(m_socket +1, &fds, NULL, NULL, &interval);
		if(FD_ISSET(m_socket , &fds))
		{
			ret = recv(m_socket , recvbuf, len, 0);
		}
	}

	return (ret > 0)?ret :-2;

}

int client::m_tcpsend(char *sendbuf, int len)
{
	if(NULL == sendbuf || len <=0)
		return -1;
	int ret =0;
	int data_left = len;
	int send_tol = 0;
	while(data_left > 0)
	{
		ret = send(m_socket, sendbuf + send_tol, data_left, 0);
        if(ret < 0)
		{
			if(errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
			{
				usleep(100000);
				ret = 0;
			}
				
		}
		send_tol += ret;
		data_left = len - send_tol;
   	}
	return send_tol;

}

#include "client.h"

int client::m_connect()
{
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(m_ip);
	sin.sin_port = htons(m_port);

	int ret = connect(m_socket, (struct sockaddr*)&sin, sizeof(sin));
	if(ret < 0)
		return -1;
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
int client::m_tcprecv()
{}
int client::m_tcpsend()
{}

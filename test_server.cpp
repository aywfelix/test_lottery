#include "server.h"

int main(int argc, char *argv[])
{
	signal(SIGPIPE,SIG_IGN);
    server serv;
	serv.readconf("./config/server.ini");
	serv.m_getpocketpoll();
	
    struct sockaddr_in sin, cin;
	serv.m_setaddr(sin);
	serv.m_setparameters();
	serv.m_bind(sin);
	serv.m_listen(10);
	serv.initevent();
	serv.m_readuser("./config/userlist");

	//	serv.m_recvthrdstart(&serv); //start thread to recv client data
    cout << "server start to accept client...\n";
	int clisock = -1;

    for(;;)
	{
		int num = epoll_wait(serv.epfd, serv.events, MAX_NUM, -1);
		if(num <0)
		{
			cout << "epoll_wait error\n";
			break;
		}
		et(&serv, num);
	}
    return 0;
}

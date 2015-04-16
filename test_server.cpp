#include "CServer.h"

int main(int argc, char *argv[])
{
	signal(SIGPIPE,SIG_IGN);
    CServer serv;
	serv.ReadConf("./config/server.ini");
	serv.GetPocketPool();
	
    struct sockaddr_in sin, cin;
	serv.SetAddr(sin);
	serv.SetParameters();
	serv.Bind(sin);
	serv.Listen(10);
	serv.InitEvent();
	serv.ReadUser("./config/userlist");

	//	serv.m_recvthrdstart(&serv); //start thread to recv client data
    cout << "CServer start to accept client...\n";
	//	int clisock = -1;

    for(;;)
	{
		int num = epoll_wait(serv.m_epfd, serv.m_events, MAX_NUM, -1);
		if(num <0)
		{
			cout << "epoll_wait error\n";
			break;
		}
		ET(&serv, num);
	}
    return 0;
}

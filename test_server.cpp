#include "CServer.h"

int main(int argc, char *argv[])
{
	signal(SIGPIPE,SIG_IGN);
    int ret = checkeprogram("ps -ef| grep test_server", "./test_server");
	if(ret == 1)
	{
		cout << "the program already exist\n";
		return -1;
	}
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

    cout << "CServer start to accept client...\n";

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

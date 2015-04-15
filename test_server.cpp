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
	serv.m_readuser("./config/userlist");

	serv.m_recvthrdstart(&serv); //start thread to recv client data
    cout << "server start to accept client...\n";
	int clisock = -1;
	do
	{
	
		clisock = serv.m_accept(&cin);
		if(clisock < 0)
		{
			cout << "test server accept error\n";
			sleep(2);
			continue;
		}
		cout << "client connect server:"<<clisock << string(inet_ntoa(cin.sin_addr)) << endl;

	} while (1);
	
    return 0;
}

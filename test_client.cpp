#include "client.h"

int main(int argc, char *argv[])
{
	int ret;
    string servip = readconfig("./config/client.ini", "net", "servip", "127.0.0.1");
	string servport = readconfig("./config/client.ini", "net", "servport", "8888");
	string username = readconfig("./config/client.ini", "user", "name", "haha");
	string passwd = readconfig("./config/client.ini", "user", "passwd", "1234");
    const char *ip = servip.c_str();
	int port = atoi(servport.c_str());
	client cli(const_cast<char*>(ip), port, 0, 0, NULL, NULL);
	cli.m_recvthrdstart(&cli);
	while(1)
	{
		ret = cli.m_connect();
		if(ret == 0)
		{
			break;
		}
		else
		{
			close(cli.m_socket);
			cli.m_socket = -1;
		}
		sleep(1);
	}
	do
	{
		ret = cli.m_loginserver(0x0001,username, passwd);
		if(ret < 0)
		{
			cout << "login send error\n";
			continue;
		}
		sleep(1);
		if(loginflag)
		{break;}
	}while(1);
	
	string line;
	getline(cin, line);
    return 0;
}

	

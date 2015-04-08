#include "server.h"

int main(int argc, char *argv[])
{
    string sip = readconfig("./config/server.ini", "net", "servip", "127.0.0.1");
	string sport = readconfig("./config/server.ini","[net]", "servport", "9999");
    const char *ip = sip.c_str();
	int port = atoi(sport.c_str());
	// cout << sip << " "<<sport <<endl;
    server serv(const_cast<char*>(ip), port);
    struct sockaddr_in sin, cin;
	serv.m_setaddr(sin);
	serv.m_setparameters();
	serv.m_bind(sin);
	serv.m_listen(10);
    cout << "server start to accept client...\n";
	int clisock = 0;
	do
	{
		clisock = serv.m_accept(&cin);
		if(clisock < 0)
		{
			cout << "test server accept error\n";
			break;
		}
		cout << "client connect server:"<<clisock << string(inet_ntoa(cin.sin_addr)) << endl;
	} while (1);
	
    return 0;
}

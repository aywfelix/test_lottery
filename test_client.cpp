#include "client.h"

int main(int argc, char *argv[])
{
    string servip = readconfig("./config/client.ini", "net", "servip", "127.0.0.1");
	string servport = readconfig("./config/client.ini", "net", "servport", "9999");
    const char *ip = servip.c_str();
	int port = atoi(servport.c_str());
	client cli(const_cast<char*>(ip), port, 0, 0, NULL, NULL);
	cout << string(ip) << " " << port << endl;
	cli.m_connect();
	cout << "client init ok\n";
	string line;
	getline(cin, line);
    return 0;
}

	

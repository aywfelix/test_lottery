#include "client.h"

int main(int argc, char *argv[])
{
    string servip = readconfig("./config/client.ini", "net", "servip", "127.0.0.1");
	string servport = readconfig("./config/client.ini", "net", "servport", "9999");
    const char *ip = servip.c_str();
	int port = atoi(servport.c_str());
	client cli(const_cast<char*>(ip), 0, 0, )
    return 0;
}

	

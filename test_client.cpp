#include "client.h"

int main(int argc, char *argv[])
{
	signal(SIGPIPE,SIG_IGN);
	int ret;
    // string servip = readconfig("./config/client.ini", "net", "servip", "127.0.0.1");
	// string servport = readconfig("./config/client.ini", "net", "servport", "8888");
	// string username = readconfig("./config/client.ini", "user", "name", "haha");
	// string passwd = readconfig("./config/client.ini", "user", "passwd", "1234");
	// string lotterynum = readconfig("./config/client.ini", "set", "lotterynum", "5");
    // string interval = readconfig("./config/client.ini", "set", "lotteryinterval", "3");
    // const char *ip = servip.c_str();
	// int port = atoi(servport.c_str());
	//	
	msgqid = msgq_init("./", 1, (int)IPC_CREAT|0666);
	client cli;
	cli.readconf("./config/client.ini");
	// cli.m_recvthrdstart(&cli);
	while(1)
	{
		ret = cli.m_connect();
		if(ret != 0)
		{
			sleep(1);
			close(cli.m_socket);
			cli.m_socket = socket(AF_INET, SOCK_STREAM, 0);
			if(cli.m_socket)
			{
				struct sockaddr_in sin;
				memset(&sin, 0, sizeof(sin));
				sin.sin_family = AF_INET;
				sin.sin_addr.s_addr = inet_addr(cli.m_ip);
				sin.sin_port = htons(cli.m_port);
			
			}
			continue;
		}
		break;
	}
	cli.m_recvthrdstart(&cli);
	sleep(2);
	do
	{
		ret = cli.m_loginserver(0x0001);
		if(ret < 0)
		{
			cout << "login send error\n";
			continue;
		}
		msgq_rcv(msgqid, &(cli.msg), sizeof(cli.msg), 1, 0);
		string s = cli.msg.msgtext;
		if(s.find("login_OK") == string::npos)
		{
			cout << "the defult user name or passwd is not correct, please try to input username and passwd correctly:\n";
			cin >> cli.username >> cli.passwd;
			continue;
		}
		else 
		{
			break;
		}
	}while(1);
	do
	{
		cout << "start to play the game...\n";
		cli.m_setLottery(0x0002);
		msgq_rcv(msgqid, &cli.msg, sizeof(cli.msg), 2, 0);
		string s = cli.msg.msgtext;
		if(s.find("set") == string::npos)
		{
			cout << "please input lotterynum and interval:\n";
			cin >> cli.m_lotterynum >> cli.m_lotteryinterval;
			continue;
		}
		cli.m_getLottery(0x0003);
		msgq_rcv(msgqid, &cli.msg, sizeof(cli.msg), 3, 0);
		string s2 = cli.msg.msgtext;
		
		if(s2.find("end") != string::npos)
		{
			cout << "do you want play again, yes(y) or no(n):\n";
			string chose;
			cin >>chose;
			if(chose == "y" || chose == "yes")
			{
				cout << "please input lotterynum and interval:\n";
				cin >> cli.m_lotterynum >> cli.m_lotteryinterval;
			}
			else
				break;
	
		}
		
	}while(1);


    close(cli.m_socket);
    msgq_free(msgqid);
	string line;
	getline(cin, line);
    return 0;
}

	







#include "client.h"

int main(int argc, char *argv[])
{
	int ret;
    string servip = readconfig("./config/client.ini", "net", "servip", "127.0.0.1");
	string servport = readconfig("./config/client.ini", "net", "servport", "8888");
	string username = readconfig("./config/client.ini", "user", "name", "haha");
	string passwd = readconfig("./config/client.ini", "user", "passwd", "1234");
	string lotterynum = readconfig("./config/client.ini", "set", "lotterynum", "5");
    string interval = readconfig("./config/client.ini", "set", "lotteryinterval", "3");
    const char *ip = servip.c_str();
	int port = atoi(servport.c_str());
	//
	msgqid = msgq_init("./", 1, (int)IPC_CREAT|0666);
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
		msgq_rcv(msgqid, &(cli.msg), sizeof(cli.msg), 1, 0);
		string s = cli.msg.msgtext;
		if(s.find("login_OK") == string::npos)
		{
			cout << "the defult user name or passwd is not correct, please try to input username and passwd correctly:\n";
		    cin >> username >> passwd;
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
		cli.m_setLottery(0x0002, lotterynum, interval);
		msgq_rcv(msgqid, &cli.msg, sizeof(cli.msg), 2, 0);
		string s = cli.msg.msgtext;
		if(s.find("set") == string::npos)
		{
			cout << "please input lotterynum and interval:\n";
			cin >> lotterynum >> interval;
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
				cin >> lotterynum >> interval;
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

	







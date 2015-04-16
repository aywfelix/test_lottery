#include "client.h"

int client::frame = 0; //static type must init here
bool loginflag = false;
int msgqid = 0;

void client::readconf(const char* file)
{
	string servip = readconfig(file, "net", "servip", "127.0.0.1");
	string servport = readconfig(file, "net", "servport", "8888");
	username = readconfig(file, "user", "name", "haha");
	passwd = readconfig(file, "user", "passwd", "1234");
	m_lotterynum = readconfig(file, "set", "lotterynum", "5");
    m_lotteryinterval = readconfig(file, "set", "lotteryinterval", "3");
    m_ip = const_cast<char*>(servip.c_str());
	m_port = atoi(servport.c_str());
   
}
int client::m_connect()
{
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(m_ip);
	sin.sin_port = htons(m_port);
	int ret = connect(m_socket, (struct sockaddr *)&sin, sizeof(struct sockaddr)); //connect ok return 0
	if(ret < 0)
	{
		cout << "connect server error\n";		
		return -1;
	}
	return ret;	
	cout << "connect server ok\n";
}

int client::m_setlotteryinter(int interval)
{
	m_lotteryinterval = interval;
}
int client::m_setlottnum(int num)
{
	m_lotterynum = num;
}

int client::m_tcprecv(char *recvbuf, int len, int timeout)
{
	if(NULL == recvbuf || len <=0 )
		return -1;
	int ret = 0;
	fd_set fds;
	struct timeval interval;
   	memset(recvbuf ,0 ,sizeof(recvbuf));
	FD_ZERO(&fds);
	FD_SET(m_socket, &fds);
    if(timeout < 0)
	{
		ret = select(m_socket+1, &fds, NULL,NULL,NULL);
		if(FD_ISSET(m_socket, &fds))
		{
			ret = recv(m_socket , recvbuf, len, 0);
		}
   	}
	else
	{
		interval.tv_sec = timeout;
		interval.tv_usec = 0;
		ret = select(m_socket +1, &fds, NULL, NULL, &interval);
		if(FD_ISSET(m_socket , &fds))
		{
			ret = recv(m_socket , recvbuf, len, 0);
		}
	}

	return (ret > 0)?ret :-2;
}

int client::m_tcpsend(char *sendbuf, int len) const
{
	if(NULL == sendbuf || len <=0)
		return -1;
	int ret =0;
	int data_left = len;
	int send_tol = 0;
	while(data_left > 0)
	{
		ret = send(m_socket, sendbuf + send_tol, data_left, 0);
        if(ret < 0)
		{
			if(errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
			{
				usleep(100);
				ret = 0;
			}
				
		}
		send_tol += ret;
		data_left = len - send_tol;
   	}
	return send_tol;
}

int client::m_loginserver(int cmd) const
{
	//	int cmd = 0x0001;
    char buf[256];
	memset(buf, 0, 256);
	string sndstring = username + "|" + passwd;
	char *snd = const_cast<char*>(sndstring.c_str());
	int sndlen = strlen(snd);
	buf[0] = 0xff;
	buf[1] = 0xff;
	memcpy(buf+2, "000000", 6);
	memcpy(buf+8, "111111", 6);
    buf[14] = cmd / 256;
    buf[15] = cmd % 256;
	if(client::frame >= 65535)
		client::frame = 0;
    buf[16] = client::frame / 256;
	buf[17] = client::frame % 256;
    buf[18] = sndlen / 256;
    buf[19] = sndlen % 256;
    memcpy(buf+20, snd, sndlen);
   
    unsigned short crc = crc_check2(buf+2, 18+sndlen);
	buf[21+sndlen] = crc / 256;
	buf[22 + sndlen] = crc % 256;
// cout << crc << "----" << 22 + sndlen << endl;
   int ret = m_tcpsend(buf, 22+sndlen);
   return ret;

}

int client::m_setLottery(int cmd) const
{
	//	int cmd = 0x0002;
    char buf[256];
	memset(buf, 0, 256);
	string s = m_lotterynum + "|" + m_lotteryinterval;
	char *snd = const_cast<char*>(s.c_str());
	trim(snd);
	int sndlen = strlen(snd);
	buf[0] = 0xff;
	buf[1] = 0xff;
	memcpy(buf+2, "000000", 6);
	memcpy(buf+8, "111111", 6);
    buf[14] = cmd / 256;
    buf[15] = cmd % 256;
	if(client::frame >= 65535)
		client::frame = 0;
    buf[16] = client::frame / 256;
	buf[17] = client::frame % 256;
    buf[18] = sndlen / 256;
    buf[19] = sndlen % 256;
    memcpy(buf+20, snd, sndlen);

    unsigned short crc = crc_check2(buf+2, 18+sndlen);
	buf[21+sndlen] = crc / 256;
	buf[22 + sndlen] = crc % 256;
	// cout << crc << "----" << 22 + sndlen << endl;
	int ret = m_tcpsend(buf, 22+sndlen);
	return ret;
	
}

int client::m_getLottery(int cmd) const
{
	//	int cmd = 0x0002;
    char buf[256];
	memset(buf, 0, 256);
	char *snd = '\0';
	int sndlen = 0;
	buf[0] = 0xff;
	buf[1] = 0xff;
	memcpy(buf+2, "000000", 6);
	memcpy(buf+8, "111111", 6);
    buf[14] = cmd / 256;
    buf[15] = cmd % 256;
	if(client::frame >= 65535)
		client::frame = 0;
    buf[16] = client::frame / 256;
	buf[17] = client::frame % 256;
    buf[18] = sndlen / 256;
    buf[19] = sndlen % 256;
    memcpy(buf+20, snd, sndlen);

    unsigned short crc = crc_check2(buf+2, 18+sndlen);
	buf[21+sndlen] = crc / 256;
	buf[22 + sndlen] = crc % 256;
	// cout << crc << "----" << 22 + sndlen << endl;
	int ret = m_tcpsend(buf, 22+sndlen);
	return ret;
	
}

void recvthrdfunc(void *arg)
{
	client *cli = (client*) arg;
	int ret = 0, cmd = 0, len = 0;
	unsigned short  crc;
	char buf[1024];
	char content[256];
	do
	{
		while(1)
		{
			if(cli->m_socket < 0)
			{
				continue;
			}
			//paser the data  message
			memset(buf, 0, sizeof(buf));
			memset(content, 0, sizeof(content));
			ret = cli->m_tcprecv( buf, 2, -1); //recv start data
			if((ret != 2) || ((unsigned char)buf[0] != 0xFF) || ((unsigned char)buf[1] != 0xFF))
			{
				break;
			}
			// bzero(buf, sizeof(buf));
			ret = cli->m_tcprecv( buf+2, 6, -1);  //recv source addr
			if((ret != 6) || (strcmp(buf+2, "111111")!= 0))
			{
				break;
			}
			ret = cli->m_tcprecv( buf+8, 6, -1); //recv destination addr
			if((ret != 6)||(strncmp(buf+8, "000000", 6) != 0))
			{
   				break;
			}
			ret = cli->m_tcprecv(buf+14, 2, -1); //recv cmd
			if(ret != 2)
			{
				break;
			}
			cmd = (unsigned char)buf[14]*256 + (unsigned char)buf[15];	
			ret = cli->m_tcprecv( buf+16, 2, -1); //recv message num
			ret = cli->m_tcprecv( buf+18, 2, -1); //the length content
			len = (unsigned char)buf[18]*256 + (unsigned char)buf[19];
			ret = cli->m_tcprecv(buf+20, len+2, -1);  //the last data
			crc = crc_check2(buf+2, len+18);
			unsigned short crc2 = (unsigned char)buf[21 + len]*256 + (unsigned char)buf[22 + len];
			// cout << crc <<"====" <<crc2 << endl;
			// cout << 22 + len << endl;
			// if(crc != crc2)
			// {
			// 	perror("crc error");
			// 	return ;
			// }
			memcpy(content, buf+20, len);
			//			cout << content << endl;
			switch(cmd)
			{
			case 0x1001:
				cli->varyloginOK(cli, content);
				break;
			case 0x1002:
			    cli->varysetlotOK(cli, content);
				break;
			case 0x1003:
				cli->varygetlottery(content);
			case 0x1004:
				cli->varyplayend(cli, content);
			default:
				break;
			}

		}
		if(ret < 0)
		{
			sleep(5);
			close(cli->m_socket);
			cli->m_socket = socket(AF_INET, SOCK_STREAM, 0);
			if(cli->m_socket)
			{
				struct sockaddr_in sin;
				memset(&sin, 0, sizeof(sin));
				sin.sin_family = AF_INET;
				sin.sin_addr.s_addr = inet_addr(cli->m_ip);
				sin.sin_port = htons(cli->m_port);
				continue;
			}
			cli->m_connect();
  		}
	
	} while (1);
	
}

void client::m_recvthrdstart(client* cli)
{
	thread_create(&pid, (void*)recvthrdfunc, cli, 1);
}

void client::varyloginOK(client* cli, char * buf)
{
	string login = buf;
    cli->msg.mytype = 1;
	strcpy(cli->msg.msgtext, buf);	
	if(login == "login_OK")
	{
		loginflag = true;
	    int ret = msgq_send(msgqid, &cli->msg, sizeof(cli->msg), 0);
		if(ret < 0)
		{
			cout << __LINE__<<":msgq_send error\n";
		}
	}
	else if(login == "login_ERROR")
	{

		int ret = msgq_send(msgqid, &cli->msg, sizeof(cli->msg), 0);
		if(ret < 0)
		{
			cout << __LINE__<<":msgq_send error\n";
		}
	    loginflag = false;
		// close(m_socket);
		// m_socket = -1;
	}
}

void client::varysetlotOK(client* cli, char * buf)
{
	string login = buf;
	cli->msg.mytype = 2;
	strcpy(cli->msg.msgtext, buf);
	if(login == "set ok")
	{
		int ret = msgq_send(msgqid, &cli->msg, sizeof(cli->msg), 0);
		if(ret < 0)
		{
			cout << __LINE__<<":msgq_send error\n";
		}
	}
	else
	{
		cout << "set lottery error\n";
	}
}

void client::varygetlottery(char *buf) const
{
   	cout << buf << endl;
	string s = buf;
	ofstream outfile("./record", ofstream::out|ofstream::app);
	if(!outfile)
		cout << "open record file error\n";
	outfile<< s <<endl;
	outfile<<endl;
	outfile.clear();
	outfile.close();
	//	cout << "get lottery ok\n";
}

void client::varyplayend(client *cli, char *buf)
{
	string s = buf;
    cli->msg.mytype = 3;
	strcpy(cli->msg.msgtext, buf);
	if(s == "end")
	{
		int ret = msgq_send(msgqid, &cli->msg, sizeof(cli->msg), 0);
		if(ret < 0)
		{
			cout << "msgq_send error\n";
		}
	}
	else{}
}

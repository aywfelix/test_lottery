#include "util.h"

//读取配置文件
/********************************* 
 * Function Name:
 * Function description:
 * Author: jensonhjt 
 * Input parameter: 
 *
 * Return value: 
 *
 **********************************/
extern string readconfig(const string filepath, const string section, const string key, string value)
{
	ifstream infile(filepath.c_str(), ifstream::in);
	if(!infile)
	{
		cout << __FILE__ << __LINE__<< "file not exit\n";
	}
	string s, sword;
    int flag = 0;

	while(getline(infile, s))
	{
		if(s[0] == '#' || s[0] == ' ' || s[0] == '/')
			continue;
		if(s[0] == '[')
		{
			if(s.find(section) != string::npos)
			{
				while(getline(infile, s))
				{
					if(s.find(key) != string::npos)
					{
						int pos = s.find("=");
						sword = s.substr(pos+1);
						flag = 1;
						break;
					}
				}
				if(flag)
					break;
			}
		}
	}
	if(!flag)
		sword = value;
	
    infile.clear();
	infile.close();
	return sword;
}
/********************************* 
 * Function Name:
 * Function description:
 * Author: jensonhjt 
 * Input parameter: 
 *
 * Return value: 在min max获取随机数
 *
 **********************************/
extern int genrandom(double min, double max)
{
	if(min >= max)
		return -1;
	//	int t = min + rand()%(max-min + 1.0);
	// int t = min + mtirand()%(max-min + 1.0);
	int t;
	return t;
}
//[start, end)
// extern unsigned int random(double start, double end)
// {
//     return start+(end-start)*mtirand()/(RAND_MAX + 1.0);
// }
extern int Random(int low, int high)  
{  
    return low + mtirand() % (high - low + 1);  
}  
extern int thread_create(pthread_t *threadid, void *pfunction, void *arg, int flag)
{
	int ret = 0;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	if(0 == flag)
	{
		pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);		
	}
	else if(1 == flag)
	{
		ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		if(ret < 0)
		{
			pthread_attr_destroy(&attr);
		    return ret;
		}
	}
 	pthread_create(threadid, &attr,(void*(*)(void*))pfunction, arg);
	pthread_attr_destroy(&attr);

	return ret;
}

extern void thread_exit(void)
{
	pthread_exit((void*)0);
}

extern int mutex_init(pthread_mutex_t *mutex)
{
	int ret = 0;
	
	ret = pthread_mutex_init(mutex, NULL);

	return (ret == 0) ? 0 : -1;
}

extern int mutex_lock(pthread_mutex_t *mutex)
{
	int ret = 0;
	ret = pthread_mutex_lock(mutex);

	return (ret == 0) ? 0 : -1;
}

extern int mutex_unlock(pthread_mutex_t *mutex)
{
	int ret =0;
	ret = pthread_mutex_unlock( mutex);

	return (ret == 0) ? 0 : -1;
}

unsigned short crc_check(char *pbuf,unsigned int len)
{
	unsigned short mid=0;
	unsigned short times=0,index=0;
	unsigned short crc=0xFFFF;
	while(len)
	{
		crc=pbuf[index]^crc;//把数据帧中的第一个字节的8位与CRC寄存器中的低字节进行异或运算，结果存回CRC寄存器
		for(times=0;times<8;times++)
		{
			mid=crc;
			crc=crc>>1;
			if( mid&0x0001 )
			{crc=crc^0xA001;}
		}
		++index;
		--len;
	}
    return crc;
}

extern unsigned short crc_check2(char *start, unsigned int len)
{
	unsigned short crcreturn = 0;
	unsigned char da;
	unsigned int crc_ta[16] = {
		0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
		0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef
	};

 	while(len--){
		da = ((unsigned char)(crcreturn / 256)) / 16;
		crcreturn <<= 4;
		crcreturn ^= crc_ta[da ^ (*start / 16)];
		da=((unsigned char)(crcreturn / 256)) / 16;
		crcreturn <<= 4;
		crcreturn ^= crc_ta[da ^ (*start & 0x0f)];
		start++;
	}

	return(crcreturn); 
}

extern void ltrim(string& str)
{
	str.erase(0, str.find_first_not_of(' '));
}

extern void rtrim(string& str)
{
	str.erase(str.find_last_not_of(' ')+1);
}

extern void trim(string& str)
{
	str.erase(0, str.find_first_not_of(' '));
	str.erase(str.find_last_not_of(' ')+1);
}

extern char *trim(char *str)
{
	if(str == NULL || strlen(str) == 0 || *str == ' ')
		return NULL;
	
	while(*str == ' '|| *str == '\t')
		++str;
	char *end = str + strlen(str) - 1;
	while(*end == ' '|| *end == '\t')
		--end;
	*(++end) = '\0';
	return str;
}
//time

char* lib_time_now(char *outtime, int flag)
{
	time_t now_t;
	struct tm *now_tm;
	if(NULL == outtime)
		return NULL;
	now_t = time(NULL);
	now_tm = localtime(&now_t);

	if(0 == flag)
		strftime(outtime, 20, "%Y-%m-%d %H:%M:%S", now_tm);
	else
		strftime(outtime, 15, "%Y%m%d%H%M%S", now_tm);
	return outtime;
}

extern string num2str(int num)
{
	stringstream ss;
	ss << num;
	return ss.str();
}
extern int str2num(string& s)
{
	int num;
	stringstream ss(s);
	ss >> num;
	return num;
}

extern int msgq_init(const char *filename, int id, int msgflag)
{
	int ret = 0;
	//	ret = msgget(ftok(filename, id), msgflag);
	ret = msgget(IPC_PRIVATE, msgflag);
	return ret;	
}
/********************************* 
 * Function Name:
 * Function description:
 * Author: jensonhjt 
 * Input parameter: 
 *   msgqid : 
 * Return value: 
 *
 **********************************/
extern int msgq_send(int msgid, const void *msgp, size_t msgsz, int msgflg)
{
	int ret = 0;
	ret = msgsnd(msgid, msgp, msgsz,  msgflg);
	return ret;
}

extern int msgq_rcv(int msqid, void *msgp, size_t msgsz, long msgtyp,int msgflg)
{
	int ret = 0;
	ret = msgrcv(msqid, msgp, msgsz, msgtyp, msgflg);
	return ret;
}

extern int msgq_free(int msqid)
{
	int ret = 0;
	struct msqid_ds buf;
	ret = msgctl(msqid, IPC_RMID, &buf);

	return ret;
}

extern int msgq_stat(int msqid,  struct msqid_ds *info)
{
	int ret = 0;
	ret = msgctl(msqid, IPC_STAT, info);
	return ret;
}

extern int setnonblock(int fd)
{
	int oldopt = fcntl(fd, F_GETFL);
	int newopt = oldopt | O_NONBLOCK;
	fcntl(fd, F_SETFL, newopt);
	return oldopt;
}

extern int checkeprogram(const char* shellstr, const char* str)
{
	int live = 0;
	char line[120];
	FILE* fp = popen(shellstr, "r");
	if(fp == NULL)
	{
		cout << "popen error\n";
		return -1;
	}
	while(!feof(fp)){
		memset(line, 0, sizeof(line));
		fgets(line, sizeof(line), fp);
		if(strstr(line, str) != NULL){
			live++;
			if(live == 2){
				break;
			}
		}
	}
	pclose(fp);
	if(live == 2){
		return 1;
	}
	return 0;
}

void char2hex(char* str, char* hex)
{
	int tmp;
	sscanf(str, "%d", &tmp);
	sprintf(hex, "%x", tmp);
}

void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

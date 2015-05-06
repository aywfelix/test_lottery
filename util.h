/*
 * Filename: util.h
 *                
 * Version:       
 * Author:        LaiJia <laijia2008@126.com>
 * Created at:    Wed Apr  8 13:53:45 2015
 *                
 * Description:   
 *
 */
#ifndef __UTIL_H__
#define __UTIL_H__
#ifndef __STREAM__
#define __STREAM__
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#endif
#ifndef __SOCKET__
#define __SOCKET__
#include<sys/socket.h>
#include<sys/un.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#endif
#ifndef __STRING__
#define __STRING__
#include <string>
#include <cstring>
#endif
#include <ctime>
#include <cstdlib>
#include <pthread.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include "Random.h"
using namespace std;
using std::string;

//Function
extern string readconfig(const string filepath, const string section, const string key, string value);
extern int genrandom(double min, double max);
// extern unsigned int random(double start, double end);
extern int Random(int low, int high);
extern int thread_create(pthread_t *threadid, void* pfunction, void *arg, int flag);
extern void thread_exit(void);
extern int mutex_init(pthread_mutex_t *mutex);
extern int mutex_lock(pthread_mutex_t *mutex);
extern int mutex_unlock(pthread_mutex_t *mutex);
extern unsigned short crc_check(char *pbuf,unsigned int len);
extern unsigned short crc_check2(char *start, unsigned int len);
extern void ltrim(string& str);
extern void rtrim(string& str);
extern void trim(string& str);
extern char *trim(char *str);
extern char* lib_time_now(char *outtime, int flag);
extern string num2str(int num);
extern int str2num(string& s);
extern int msgq_init(const char *filename, int id, int msgflag);
extern int msgq_send(int msgid, const void *msgp, size_t msgsz, int msgflg);
extern int msgq_rcv(int msqid, void *msgp, size_t msgsz, long msgtyp,int msgflg);
extern int msgq_free(int msqid);
extern int msgq_stat(int msqid,  struct msqid_ds *info);
extern int setnonblock(int fd);
extern int checkeprogram(const char* shellstr, const char* str);
void char2hex(char* str, char* hex);
void swap(int &a, int &b);
#endif

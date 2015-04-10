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

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <pthread.h>

using namespace std;
using std::string;

//Function
extern string readconfig(const string filepath, const string section, const string key, string value);
extern int genrandom(int min, int max);
extern double random(double start, double end);
extern int thread_create(pthread_t *threadid, void* pfunction, void *arg, int flag);
extern void thread_exit(void);
extern int mutex_init(pthread_mutex_t *mutex);
extern int mutex_lock(pthread_mutex_t *mutex);
extern int mutex_unlock(pthread_mutex_t *mutex);
extern unsigned short crc_check(char *pbuf,unsigned int len);
extern unsigned short crc_check2(char *start, unsigned int len);
// extern void ltrim(std::basic_string<char*>& str);
// extern void rtrim(std::basic_string<char*>& str);
// extern void trim(std::basic_string<char*>& str);
extern char *trim(char *str);

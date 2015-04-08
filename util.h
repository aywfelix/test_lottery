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
using namespace std;
using std::string;

//Function
extern string readconfig(const string filepath, const string section, const string key, string value);
extern int genrandom(int min, int max);
extern double random(double start, double end);

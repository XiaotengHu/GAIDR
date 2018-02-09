/*
 * 
 * Created on: Dec 26, 2017
 * Author: Xiaoteng Hu
 * Description:stringOper.h
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#ifndef SRC_UTILS_STRINGOPER_H_
#define SRC_UTILS_STRINGOPER_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../struct/structs.h"

using namespace std;

vector<string> split(string str, string pattern);

string request2String(RequestInfo request, string pattern);

RequestInfo string2Request(string reqStr, string pattern);

string intxy2String(string filename, int sx, int sy, int ex,int ey);



#endif /* SRC_UTILS_STRINGOPER_H_ */

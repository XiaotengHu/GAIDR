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

RequestInfo string2Request(string reqstr, string pattern);

#endif

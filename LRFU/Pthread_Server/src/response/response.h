/*
 * 
 * Created on: Dec 27, 2017
 * Author: Xiaoteng Hu
 * Description:response.h
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#ifndef SRC_RESPONSE_RESPONSE_H_
#define SRC_RESPONSE_RESPONSE_H_

#include <iostream>
#include <stdio.h>
#include "fitsio.h"
#include "string"
#include <sstream>
#include "stdlib.h"
#include <sys/time.h>

#include "../variables/variables.h"
#include "../struct/structs.h"

using namespace std;

//extern double time[500];


double response(string filename, int sx, int sy, int ex, int ey, int x0, int y0, string path);
//void *responseReplica(void *rr);

#endif /* SRC_RESPONSE_RESPONSE_H_ */

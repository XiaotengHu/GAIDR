/*
 * 
 * Created on: Dec 31, 2017
 * Author: Xiaoteng Hu
 * Description:capacity.h
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#ifndef SRC_CAPACITY_CAPACITY_H_
#define SRC_CAPACITY_CAPACITY_H_

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <string>
#include "../variables/variables.h"
using namespace std;

int getCapacity(string path);

int getFileSize(string path);



#endif /* SRC_CAPACITY_CAPACITY_H_ */

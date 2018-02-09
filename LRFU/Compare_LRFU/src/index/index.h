/*
 * 
 * Created on: Dec 27, 2017
 * Author: Xiaoteng Hu
 * Description:index.h
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#ifndef SRC_INDEX_INDEX_H_
#define SRC_INDEX_INDEX_H_

#include <iostream>
#include <map>
#include <list>
#include <string>

#include "../struct/structs.h"
#include "../mydb/mydb.h"
#include "../mapxy/mapxy.h"
#include "../replacement/replacement.h"
#include "../capacity/capacity.h"

using namespace std;

int comArea(int startx,int starty, int endx,int endy);

int comCrossArea(int oldStartx, int oldStarty,int oldEndx, int oldEndy, int newStartx, int newStarty, int newEndx, int newEndy);

bool fileNameHit(RequestInfo request);

bool areaHit(RequestInfo request);

IndexInfo merge(IndexInfo oldIndex, RequestInfo request);

bool searchInIndex(RequestInfo request);

bool searchInLocalIndex(RequestInfo request);


void insertIntoIndex(RequestInfo request, int* mapxy);


void updateAllIndex(long currentTime, string fiilname);

double comPriority(IndexInfo index, int currentTime);

void updateTotalCapacity();

bool searchInLocalIndex(RequestInfo request);

bool fileNameAndIpHit(RequestInfo request);

string searchFitsfilesIp(RequestInfo request);

string updateIndex(RequestInfo request);




#endif /* SRC_INDEX_INDEX_H_ */

/*
 * structs.h
 *
 * Created on: Dec 26, 2017
 * Author:
 */

#ifndef SRC_STRUCT_STRUCTS_H_
#define SRC_STRUCT_STRUCTS_H_

#include <string>
#include <stdlib.h>
using namespace std;

struct FileInfo{
	int filename;
	int hot;
	int type;
	int hotzone;
	int reqcpunts;
	int idletime;
};

struct RequestInfo{
	string fileName;
	int startx;
	int starty;
	int endx;
	int endy;

	long genTime;
	long endTime;
	double qos;
	int hit;

	bool operator < (RequestInfo & b){
		return genTime < b.genTime;
	}
};

struct IndexInfo{
	string fileName;
	int startx;
	int starty;
	int endx;
	int endy;

	int count;
	int idleTime;
	double size;

	double priority;

	string subName;



	bool operator < (IndexInfo & b){
		return priority < b.priority;
	}

	bool operator == (IndexInfo & b){
		if(fileName==b.fileName && startx==b.startx && starty==b.starty && endx == b.endx && endy==b.endy && count==b.count
				&& idleTime==b.idleTime && size ==b.size && priority==b.priority)
		return true;

		return false;
	}
};

#endif /* SRC_STRUCT_STRUCTS_H_ */

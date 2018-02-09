/*
 * 
 * Created on: Dec 28, 2017
 * Author: Xiaoteng Hu
 * Description:run.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <list>

#include "../variables/variables.h"
#include "../socket/socket.h"
#include "../utils/stringOper.h"
#include "../response/response.h"
#include "../track/track.h"


using namespace std;

double TOTAL_QOS = 0.0;
list<RequestInfo> resultList;

int main(){
    cout<<"start run"<<endl;
	struct sockaddr_in s_in;
	struct sockaddr_in c_in;
	int l_fd,c_fd;
	socklen_t len;
	char buf[NUM_MAX];
	string path = "";
	string subFitsName = "";
	struct timeval start, end;
	double qos = 0.0;
	list<RequestInfo> resultList;

	memset((void *)&s_in, 0 ,sizeof(s_in));

	s_in.sin_family = AF_INET;
	s_in.sin_addr.s_addr = INADDR_ANY;
	s_in.sin_port = htons(PORT);

	l_fd = socket(AF_INET, SOCK_STREAM, 0);

	bind(l_fd, (struct sockaddr *)&s_in, sizeof(s_in));

	listen(l_fd, NUM_MAX);

	while(1){

		c_fd = accept(l_fd,(struct sockaddr *)&c_in,&len);

		memset(&buf, 0 ,sizeof(buf));
		read(c_fd, buf, NUM_MAX);

		string reqStr(buf);
        gettimeofday(&start, NULL);
		RequestInfo request = string2Request(reqStr,PATTERN);
		qos = 0.0;
		cout << "request" << request.fileName<< endl;
        path = ORIGINAL_SOURCE1_PATH;
		subFitsName = request.fileName + ".fits";

		int x0 = 0, y0 =0;
		vector<string> result = split(subFitsName, "_");

		if(result.size() >2){
			x0 = atoi(result[1].c_str());
			y0 = atoi(result[2].c_str());


		}
		response(subFitsName,request.startx,request.starty,request.endx,request.endy, x0, y0, path);

		const char *name = subFitsName.c_str();
		char pcCMD[255];
		cout<<"send fits files"<<endl;
		sprintf(pcCMD,"scp /home/lby/disk/TargetTmpFITS/%s_%d_%d_%d_%d.fits summer@summer-pc:/home/summer/disks/hdd2/TargetFITS", name, request.startx, request.starty,request.endx,request.endy);
		system(pcCMD);
		cout<<"send end"<<endl;
		gettimeofday(&end, NULL);

		request.endTime = end.tv_sec*1000 + end.tv_usec/1000;
		qos = (end.tv_sec-start.tv_sec)*1000 + (end.tv_usec-start.tv_usec)/1000;
		resultList.push_back(request);

		request.qos = qos;

		resultList.push_back(request);
		cout<<"TOTAL_QOSTOTAL_QOSTOTAL_QOS:"<<request.genTime<<endl;
		cout<<"TOTAL_QOSTOTAL_QOSTOTAL_QOS:"<<request.endTime<<endl;

		TOTAL_QOS += (request.endTime-request.genTime);

		close(c_fd);
		record(resultList);
	}


}




/**
 * ################################################
 * ################## Main Function ###############
 * ################################################
 *
 * Version: 1.0
 * File: run.cpp
 * Author: Xiaoteng Hu
 * Description: Main Function
 * Date: 2017-12-26
 * Copyright (C) 2017 NAOC-TJUCS
 **/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <map>
#include <string.h>
#include <list>
#include "../struct/structs.h"
#include "../variables/variables.h"
#include "../mydb/mydb.h"
#include "../socket/socket.h"
#include "../index/index.h"
#include "../response/response.h"
#include "../track/track.h"
#include "../file/file.h"


using namespace std;

int REPLICA_HIT = 0;
double TOTAL_QOS = 0;
int threadNum = 2;
long timePthread[500];
long totalTimePthread;
int indexPthread = 0;

void *responseReplica(void *rr){
	    ResponseReplica *rrTmp = (ResponseReplica *)rr;

	    fitsfile *infptr, *outfptr;
		int status =0;
		string filename = rrTmp->filename;
        int sx = rrTmp->sx;
        int sy = rrTmp->sy;
        int ex = rrTmp->ex;
        int ey = rrTmp->ey;
        int x0 = rrTmp->x0;
        int y0 = rrTmp->y0;
        string path = rrTmp->path;
		struct timeval start, end;
		long duration;
		int my_idPthread = indexPthread++;

		int newsx = (sx-x0) ? (sx-x0) : 1;
		int newex = (ex-x0) ? (ex-x0) : 1;
		int newsy = (sy-y0) ? (sy-y0) : 1;
		int newey = (ey-y0) ? (ey-y0) : 1;

		gettimeofday(&start, NULL);
		stringstream instrStream;
		instrStream<<"["<<newsx<<":"<<newex<<","<<newsy<<":"<<newey<<"]";
		string s1 = instrStream.str();
		string infilename = path + filename + s1;

		if(!fits_open_file(&infptr, infilename.c_str(), READONLY, &status)){
		        stringstream outstrStream;
		        outstrStream<<"_"<<sx<<"_"<<sy<<"_"<<ex<<"_"<<ey<<".fits";
		        string s2 = outstrStream.str();
		        string outfilename = TARGET_PATH + filename + s2;

		        if(!fits_create_file(&outfptr, outfilename.c_str(), &status)){
		            fits_copy_file(infptr, outfptr, 1, 1, 1, &status);
		            fits_close_file(outfptr, &status);
		        }
		        fits_close_file(infptr, &status);
		    }

		    gettimeofday(&end, NULL);
		    duration = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000.0;
		    timePthread[my_idPthread] = duration;
		    cout<<"my_idPthread:   "<<my_idPthread<<"timePthread[my_idPthread]:   "<<timePthread[my_idPthread]<<"duration:   "<<duration<<endl;
}


int main(){

	cout <<"=================》》start run server《《==================" << endl;
	// store all requests result
	list<RequestInfo> resultList;
	// init database
	init_db();
	//connect database
	if(conn_db(DB_HOST_NAME,DB_USER_NAME,DB_PASSWORD,DB_DB_NAME)!=0){
		return -1;
	}

	double qos = 0.0;
	string serverIp = SERVER_IP;
	string path = "";
	struct timeval start,end;
	pthread_t *pid;
	pid = (pthread_t *)malloc(threadNum * sizeof(pthread_t));

	FileInfo files[NUM_FILES];
	initFiles(files);
	list<RequestInfo> requestsList;
	list<RequestInfo>::iterator reqIter;

	genReqFromTrack(&requestsList);

	if(requestsList.size()>0){
	    cout << "requests size:  "<< requestsList.size()<<endl;
	}

	qos = 0.0;
	string subFitsName = "";
	gettimeofday(&start, NULL);
	long START = start.tv_sec;
	long START_m = start.tv_sec*1000 + start.tv_usec/1000;
	struct timeval now,sleepEnd;
	int i =1;
	for(reqIter =requestsList.begin(); reqIter!=requestsList.end(); reqIter++){
	   gettimeofday(&now, NULL);
	   long NOW = now.tv_sec;
	   if((*reqIter).genTime >(NOW-START)){
	   sleep((*reqIter).genTime - (NOW-START));
	   }
	   gettimeofday(&sleepEnd, NULL);
	   (*reqIter).genTime = (*reqIter).genTime*1000 + START_m;
	   long nowTime1 = (*reqIter).genTime;
	   long nowTime2 = sleepEnd.tv_sec*1000 + sleepEnd.tv_usec/1000;
	   if(nowTime1>=nowTime2){
	    (*reqIter).genTime = nowTime2;
	   }else{
		(*reqIter).genTime = nowTime1;
	   }
	 RequestInfo request = (*reqIter);
	 cout<<"Req:"<< i++ <<"  time:   "<<request.genTime<<endl;
		if(searchInIndex(request)){                  //hit in replica files
				subFitsName = updateIndex(request);
				int x0=0, y0=0;
				vector<string> result = split(subFitsName, "_");
		        if(result.size() > 2){
					x0 = atoi(result[1].c_str());
					y0 = atoi(result[2].c_str());
				}
				ResponseReplica *rr1 = new ResponseReplica();
				rr1->filename = subFitsName;
				rr1->sx = request.startx;
				rr1->sy = request.starty;
				rr1->ex = request.endx;
				rr1->ey = request.endy;
				rr1->x0 = x0;
				rr1->y0 = y0;
				rr1->path = Replica_PATHONE;
				pthread_create(&pid[0], NULL,responseReplica,(void *)rr1);
				request.hit = 1;
				REPLICA_HIT++;

				gettimeofday(&end, NULL);
				long timeuse = end.tv_sec*1000 + end.tv_usec/1000;
				request.endTime = timeuse;
				request.qos = qos;
				resultList.push_back(request);
				cout<<"request.genTime"<<request.genTime<<"request.endTime"<<request.endTime<<endl;
		}else{
			 if(searchInLocalIndex(request)){       //hit in local data center
             path = ORIGINAL_SOURCE_PATH;
             subFitsName = request.fileName + ".fits";
             //pthread
             int x0=0, y0=0;
             vector<string> result = split(subFitsName, "_");
             if(result.size() > 2){
             x0 = atoi(result[1].c_str());
             y0 = atoi(result[2].c_str());
             }
             response(subFitsName,request.startx,request.starty,request.endx,request.endy, x0, y0, path);
             gettimeofday(&end, NULL);
             long timeuse = end.tv_sec*1000 + end.tv_usec/1000;
      		 request.endTime = timeuse;
             request.qos = qos;
             resultList.push_back(request);
             cout<<"request.genTime"<<request.genTime<<"request.endTime"<<request.endTime<<endl;
			 }else{                                 //hit in other data centers
			 send(SERVER_IP,request,PATTERN);       //send message to cachemanager
		     serverIp = searchFitsfilesIp(request);
		     cout <<"serverIp"<<serverIp<<endl;
             send(serverIp,request,PATTERN);        //send message to newcenterserver
             cout<<"send request to"<<serverIp<<endl;
             gettimeofday(&end, NULL);
             long timeuse = end.tv_sec*1000 + end.tv_usec/1000;
             request.endTime = timeuse;
             request.qos = qos;
             resultList.push_back(request);
             cout<<"request.genTime"<<request.genTime<<"request.endTime"<<request.endTime<<endl;
			 }

		}
		TOTAL_QOS += (request.endTime - request.genTime);
	}

	cout<<"HitTimes: "<<REPLICA_HIT<<"    hitrate:"<<((double)REPLICA_HIT/(double)resultList.size())<<endl;
	cout<<"total_qos:"<<TOTAL_QOS<<"      average_qos:"<< (TOTAL_QOS/(double)resultList.size())<<endl;
	stringstream hitRate;
	hitRate<<"RequestSize,ReplicaHitTimes,HitRate,TotalQos,AvgrageQos\n"<<resultList.size()<<","
			<<REPLICA_HIT<<","<<((double)REPLICA_HIT/(double)resultList.size())<<","
			<<TOTAL_QOS<<","<<(TOTAL_QOS/(double)resultList.size())<<"\n";
	recordRate(hitRate.str());
	record(resultList);
	for(int i=0;i<500;i++){
			totalTimePthread +=timePthread[i];
	}
	cout<<"totalTime:          "<<totalTimePthread<<endl;


}

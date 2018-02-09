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
#include <pthread.h>
#include <list>
#include "../struct/structs.h"
#include "../variables/variables.h"
#include "../mydb/mydb.h"
#include "../socket/socket.h"
#include "../index/index.h"
#include "../response/response.h"
#include "../track/track.h"


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
        cout<<"sxsxsxsxsxsxsxsxssx"<<sx<<endl;
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
		    cout<<"durationdurationdurationdurationduration"<<duration<<endl;
		    cout<<"timePthread[my_idPthread]timePthread[my_idPthread]timePthread[my_idPthread]timePthread[my_idPthread]"<<my_idPthread<<"wqwqwq"<<timePthread[my_idPthread]<<"errwerew"<<duration<<endl;
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
	struct sockaddr_in s_in;
	struct sockaddr_in c_in;
	int l_fd,c_fd;
	socklen_t len;
	char buf[NUM_MAX];

	memset((void *)&s_in, 0 ,sizeof(s_in));

	s_in.sin_family = AF_INET;
	s_in.sin_addr.s_addr = INADDR_ANY;
	s_in.sin_port = htons(SERVER_PORT);

	l_fd = socket(AF_INET, SOCK_STREAM, 0);

	bind(l_fd, (struct sockaddr *)&s_in, sizeof(s_in));

	listen(l_fd, NUM_MAX);

	double qos = 0.0;
	string serverIp = SERVER_IP;

	string path = "";
	struct timeval start,end;
	pthread_t *pid;
	pid = (pthread_t *)malloc(threadNum * sizeof(pthread_t));

	while(1){
		c_fd = accept(l_fd,(struct sockaddr *)&c_in,&len);
		memset(&buf,0,sizeof(buf));
		read(c_fd, buf, NUM_MAX);

		string reqStr(buf);

	//	cout <<"reqStrreqStrreqStrreqStrreqStrreqStrreqStrreqStrreqStrreqStrreqStrreqStrreqStr:  "<< reqStr<<endl;
		if(reqStr == "EOF"){
			break;
		}
		gettimeofday(&start, NULL);
		RequestInfo request = string2Request(reqStr,PATTERN);
	//	cout <<"request.genTimerequest.genTimerequest.genTimerequest.genTimerequest.genTime:  "<< request.genTime<<endl;
	//	cout <<"request:  "<< request.fileName<<endl;

		qos = 0.0;
		string subFitsName = "";

		if(searchInIndex(request)){                  //hit in replica files
	//		cout<<"pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1"<<endl;
			int fileName = atoi(request.fileName.c_str());
	//		cout<<"pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1"<<fileName<<endl;
			if(fileName%2 == 1){
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
			}else{
				subFitsName = updateIndex(request);
		//		cout<<"pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1pthread1"<<subFitsName<<endl;
		//		cout<<"pthread1"<<request.startx<<endl;
				int x0=0, y0=0;
				vector<string> result = split(subFitsName, "_");
			    if(result.size() > 2){
				x0 = atoi(result[1].c_str());
				y0 = atoi(result[2].c_str());
				}
	//		    cout<<"pthread1qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"<<endl;
				ResponseReplica *rr2 = new ResponseReplica();
	//			cout<<"pthread1wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"<<endl;
				rr2->filename = subFitsName;
				rr2->sx = request.startx;
				rr2->sy = request.starty;
				rr2->ex = request.endx;
				rr2->ey = request.endy;
				rr2->x0 = x0;
				rr2->y0 = y0;
				rr2->path = Replica_PATHTWO;
	//			cout<<"pthread1wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwrrrrrrrrrrrrrr"<<endl;
				string filename1 = rr2 -> filename;
	//			cout<<"pthread1"<<filename1<<endl;
				pthread_create(&pid[1], NULL,responseReplica,(void *)rr2);
		//		path = Replica_PATHTWO;
				request.hit = 1;
				REPLICA_HIT++;
			}
          //  for(int i = 0; i < threadNum; i++){
			//  pthread_join(pid[i], NULL);
        //    }
		//	free(pid);

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
			 }else{                                 //hit in other data centers
			 send(SERVER_IP,request,PATTERN);       //send message to cachemanager
		     serverIp = searchFitsfilesIp(request);
		     cout <<"serverIpserverIpserverIpserverIpserverIpserverIpserverIpserverIp"<<serverIp<<endl;
             send(serverIp,request,PATTERN);        //send message to newcenterserver
             cout<<"send request to"<<serverIp<<endl;
			 }

		}

//		int x0=0, y0=0;
//		vector<string> result = split(subFitsName, "_");

//		if(result.size() > 2){
//			x0 = atoi(result[1].c_str());
//			y0 = atoi(result[2].c_str());
//		}
//		response(subFitsName,request.startx,request.starty,request.endx,request.endy, x0, y0, path);

		gettimeofday(&end, NULL);
		long timeuse = end.tv_sec*1000 + end.tv_usec/1000;
		request.endTime = timeuse;
		request.qos = qos;
		resultList.push_back(request);
		cout<<"request.genTime"<<request.genTime<<endl;
		cout<<"request.endTime"<<timeuse<<endl;
		TOTAL_QOS += (request.endTime - request.genTime);
        close(c_fd);
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
	cout<<"totalTimetotalTimetotalTime"<<totalTimePthread<<endl;
}

/*
 * 
 * Created on: Dec 30, 2017
 * Author: Xiaoteng Hu
 * Description:run.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#include <iostream>
#include <map>
#include <list>
#include <sys/time.h>
#include "../mydb/mydb.h"
#include "../variables/variables.h"
#include "../socket/socket.h"
#include "../utils/stringOper.h"
#include "../struct/structs.h"
#include "../index/index.h"
#include "../mapxy/mapxy.h"
#include "../capacity/capacity.h"

using namespace std;

int REPLICA_HIT = 0;
double TOTAL_QOS = 0;
string serverIp = "";

int main(){
    cout<<"start run cache manager"<<endl;
    init_db();
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
    s_in.sin_port = htons(CACHEPORT);

    l_fd = socket(AF_INET,SOCK_STREAM, 0);
    bind(l_fd, (struct sockaddr *)&s_in, sizeof(s_in));

    listen(l_fd,NUM_MAX);

    struct timeval cur;

    while(1){
    	c_fd =accept(l_fd,(struct sockaddr *)&c_in,&len);
    	memset(&buf,0,sizeof(buf));
    	read(c_fd, buf, NUM_MAX);
    	string reqStr(buf);
    	RequestInfo request = string2Request(reqStr, PATTERN);
    	int *mapxy;

    	mapxy = mapXY(request.startx,request.starty,request.endx,request.endy);

    	cout<<request.startx<<request.starty<<request.endx<<request.endy<<endl;

    	IndexInfo temIndex;

    	if(fileNameHit(request)){

    		if(!areaHit(request)){

    			list<IndexInfo> indexList;

    			string sql = "select * from `index` where filename='"+ request.fileName + "'";

    			indexList = getIndexList(sql.c_str());

    			list<IndexInfo>::iterator indexIter;

    			for(indexIter =indexList.begin(); indexIter!=indexList.end(); indexIter++){
    				int newArea = comArea(request.startx,request.starty,request.endx,request.endy);
    				int oldArea = comArea((*indexIter).startx,(*indexIter).starty,(*indexIter).endx,(*indexIter).endy);

    				int crossArea = comCrossArea((*indexIter).startx,(*indexIter).starty,(*indexIter).endx,(*indexIter).endy,
    						request.startx,request.starty,request.endx,request.endy);
    				double oldProportion = ((double) crossArea /(double) oldArea);
    				double newProportion = ((double) crossArea/(double) newArea);

    				if(oldProportion>=AREA_THRESHOLD || newProportion>=AREA_THRESHOLD){
    					temIndex = merge((*indexIter),request);

    					mapxy = mapXY(temIndex.startx,temIndex.starty,temIndex.endx,temIndex.endy);

    					break;

    				}
    			}
    		}

    	}
    	request.startx = mapxy[0];
    	request.starty = mapxy[1];
    	request.endx = mapxy[2];
    	request.endy = mapxy[3];
    	serverIp = searchFitsfilesIp(request);
    	cout <<"serverIp"<<serverIp<<endl;
    	cacheSendCenter(serverIp,request,PATTERN);        //send message to newcenterserver
    	sleep(35);
    	insertIntoIndex(request,mapxy);

    	while((getCapacity(Replica_PATHONE)+getCapacity(Replica_PATHTWO))>TOTAL_REPLICA_SIZE){
    		gettimeofday(&cur, NULL);
    		long currentTime = cur.tv_sec*1000 + cur.tv_usec/1000;
    		updateAllIndex(currentTime,request.fileName);
    	}

    	close(c_fd);


    }
}


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <map>
#include <list>

#include "../file/file.h"
#include "../socket/socket.h"
#include "../struct/structs.h"
#include "../variables/variables.h"
#include "../track/track.h"
#include "../utils/stringOper.h"
using namespace std;

int main(){
	cout << "================》》start run《《================== \n"<<endl;
	cout << "================》》init files《《================== \n"<<endl;

	//files
	FileInfo files[NUM_FILES];

	initFiles(files);

	list<RequestInfo> requestsList;

	list<RequestInfo> resultList;

	list<RequestInfo>::iterator reqIter;

	cout << "================》》generate requests《《================== \n"<<endl;

    //generate requests from csv
	genReqFromTrack(&requestsList);

	if(requestsList.size()>0){
		cout << "requests size:  "<< requestsList.size()<<endl;
	}
	cout <<"send requests to ip  "<< SERVER_IP <<endl;
	string serverIp = SERVER_IP;
	int i = 1;

	for(reqIter=requestsList.begin();reqIter!=requestsList.end();reqIter++){

		sleep((*reqIter).idle);
	    struct timeval tv;
	    gettimeofday(&tv,NULL);
	    long timeuse = tv.tv_sec*1000 + tv.tv_usec/1000;

	    cout<<"Req:"<< i++ <<"  time:   "<<timeuse<<endl;
	    (*reqIter).genTime = timeuse;
	    cout<<" (*reqIter).genTime"<< (*reqIter).genTime<<endl;
	    send(serverIp,*reqIter,PATTERN);
	}
   reqEOF();
}

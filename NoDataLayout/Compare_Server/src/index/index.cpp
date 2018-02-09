/*
 * 
 * Created on: Dec 27, 2017
 * Author: Xiaoteng Hu
 * Description:index.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#include "index.h"
#include "../variables/variables.h"
#include <sstream>

bool fileNameHit(RequestInfo request){
	int count = 0;
	stringstream instrStream;
	instrStream<<"select count(*) from `index` where filename='"<<request.fileName<<"'";
	string sql = instrStream.str();
	count = getCount(sql.c_str());
	if(count>0){
		return true;
	}
	return false;

}

bool fileNameAndIpHit(RequestInfo request){
	int count = 0;
	stringstream instrStream;
	instrStream<<"select count(*) from `localIndex` where filename='"<<request.fileName<<"' and ip ='"<<LOCAL_IP<<"'";
	string sql = instrStream.str();
	count = getCount(sql.c_str());
	if(count>0){
		return true;
	}
	return false;

}

bool areaHit(RequestInfo request){
	int count = 0;

	stringstream instrStream;
	instrStream<<"select count(*) from `index` where filename='"<<request.fileName<<
			"' and start_x<="<<request.startx<<" and start_y<="<<request.starty<<
			" and end_x>="<<request.endx<<" and end_y>="<<request.endy;
	string sql = instrStream.str();
	count = getCount(sql.c_str());

	if(count>0){
		return true;
	}
	return false;
}


bool searchInIndex(RequestInfo request){
	if(!fileNameHit(request)){
		return false;
	}
	if(areaHit(request)){
		return true;
	}
	return false;
}

bool searchInLocalIndex(RequestInfo request){
	if(fileNameAndIpHit(request)){
		return true;
	}
	return false;
}

string updateIndex(RequestInfo request){
	string subFitsName = "";

	stringstream instrStream;
	instrStream<<"select `sub_name` from `index` where filename='"<<request.fileName<<
			"' and start_x<="<<request.startx<<" and start_y<="<<request.starty<<
			" and end_x>="<<request.endx<<" and end_y>="<<request.endy;
	string sql =  instrStream.str();

	subFitsName = getValue(sql.c_str());
    cout<<"subFitsName"<<subFitsName<<endl;
	if(subFitsName != ""){
		stringstream instrStream;
		instrStream<<"update `index` set `count`=`count`+1,idle_time="<<request.genTime<<" where `sub_name`='"<<subFitsName<<"'";
		string sql = instrStream.str();

		updateInfo(sql.c_str());
	}
	return subFitsName;

}
string searchFitsfilesIp(RequestInfo request){
	string ip ="";
	stringstream instrStream;
	instrStream<<"select `ip` from `localIndex` where filename='"<<request.fileName<<"'";
	string sql = instrStream.str();
	cout<<"ipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipip"<<sql<<endl;
	ip = getValue(sql.c_str());
	cout<<"ipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipipip"<<ip<<endl;
	return ip;

}



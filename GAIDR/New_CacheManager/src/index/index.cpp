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

int comArea(int startx,int starty, int endx,int endy){
	return (endx-startx)*(endy-starty);
}

int comCrossArea(int oldStartx, int oldStarty, int oldEndx, int oldEndy, int newStartx, int newStarty, int newEndx, int newEndy){
	if(newEndx<oldStartx || newEndy<oldStarty || oldEndx<newStartx || oldEndy<newStarty){
		return 0;
	}
	int startx = newStartx>oldStartx ? newStartx : oldStartx;
	int starty = newStarty>oldStarty ? newStarty : oldStarty;
	int endx = newEndx<oldEndx ? newEndx : oldEndx;
	int endy = newEndy<oldEndy ? newEndy : oldEndy;

	return comArea(startx,starty,endx,endy);

}

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
	ip = getValue(sql.c_str());
	return ip;

}
IndexInfo merge(IndexInfo oldIndex, RequestInfo request){
	int * mapxy = mapXY(request.startx, request.starty, request.endx,request.endy);

	int newStartx = oldIndex.startx<mapxy[0] ? oldIndex.startx : mapxy[0];
	int newStarty = oldIndex.starty<mapxy[1] ? oldIndex.starty : mapxy[1];
	int newEndx = oldIndex.endx > mapxy[2] ? oldIndex.endx : mapxy[2];
	int newEndy = oldIndex.endy > mapxy[3] ? oldIndex.endy : mapxy[3];

	double newSize = 0;
	IndexInfo newIndex = {request.fileName, newStartx, newStarty, newEndx, newEndy,oldIndex.count,
			request.genTime, newSize, oldIndex.priority,""};
	string sql = "delete from `index` where `sub_name` = '"+ oldIndex.subName +"'";
	updateInfo(sql.c_str());

	removeFile(oldIndex.subName,request.fileName);

	return newIndex;

}
void insertIntoIndex(RequestInfo request, int* mapxy){

	stringstream outstrStream;
	outstrStream<<"_"<<mapxy[0]<<"_"<<mapxy[1]<<"_"<<mapxy[2]<<"_"<<mapxy[3]<<".fits";
	string tmpstr = outstrStream.str();
	string indexFileName = request.fileName + tmpstr;

	double size = getFileSize(Replica_PATHONE + indexFileName);

	IndexInfo newIndex = {request.fileName, mapxy[0], mapxy[1], mapxy[2], mapxy[3],1,
	                      request.genTime, size, 0.0, indexFileName};

	stringstream instrStream;
	instrStream<<"insert into `index`(`filename`,`start_x`, `start_y`, `end_x`, `end_y`, `count`, `idle_time`, `size`, `priority`, `sub_name`) values('"
			<<newIndex.fileName<<"',"<<newIndex.startx<<","<<newIndex.starty<<","<<newIndex.endx<<","<<newIndex.endy<<","<<newIndex.count<<","<<newIndex.idleTime<<
			","<<newIndex.size<<","<<newIndex.priority<<",'"<<newIndex.subName<<"')";
	string sql = instrStream.str();

	updateInfo(sql.c_str());

}
void updateAllIndex(long currentTime, string filename){

	stringstream instrStream;
	int hotArea = atoi(filename.c_str());
	double a = 0.8;
	double b = 0.2;
	int c = 0;
	if(hotArea>=0 && hotArea<=200){
		c = 8;
	}else{
		c = 2;
	}
	instrStream<<"update `index` set `priority` = "<<a<<"*(1000*'count'/("<<currentTime<<"- `idle_time`+1)) + "<<b<<"*"<<c<<"";
	string sql = instrStream.str();

	updateInfo(sql.c_str());

	stringstream instrStreamOne, instrStreamTwo;
	instrStreamOne<<"select `sub_name` from `index` where `priority` = (select min(priority) from `index`)";
	instrStreamTwo<<"select `filename` from `index` where `priority` = (select min(priority) from `index`)";

	sql = instrStreamOne.str();
	string subName = getValue(sql.c_str());

	sql = instrStreamTwo.str();
	string fileName = getValue(sql.c_str());

	sql = "delete from `index` where `sub_name` = '" + subName +"'";
	updateInfo(sql.c_str());

	removeFile(subName,fileName);

}



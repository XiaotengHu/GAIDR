/*
 * 
 * Created on: Dec 26, 2017
 * Author: Xiaoteng Hu
 * Description:stringOper.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */


#include "stringOper.h"

vector<string> split(string str, string pattern){
	string::size_type pos;
	vector<string> result;

	str +=pattern;
	int size = str.size();

	for(int i =0; i<size; i++){
		pos = str.find(pattern,i);

		if(pos < size){
			string s = str.substr(i,pos-i);
			cout <<"s"<<  s <<endl;
			result.push_back(s);
			i = pos + pattern.size()-1;
		}
	}
	return result;
}

string request2String(RequestInfo request, string pattern){

	stringstream strStream;
	strStream<<request.fileName<<pattern<<request.startx<<pattern<<request.starty<<pattern<<request.endx<<pattern<<request.endy<<pattern
			<<request.genTime<<pattern<<request.endTime<<pattern<<request.qos<<pattern;

	string reqStr = strStream.str();

	return reqStr;
}

RequestInfo string2Request(string reqStr, string pattern){
	vector<string> infos = split(reqStr, pattern);

	string fileName = infos[0];
	int startx = atoi(infos[1].c_str());
	int starty = atoi(infos[2].c_str());
	int endx = atoi(infos[3].c_str());
	int endy = atoi(infos[4].c_str());

	long genTime = atol(infos[5].c_str());
	cout<<"genTimegenTimegenTimegenTimegenTimegenTimegenTimegenTimegenTime"<<genTime<<endl;
	long endTime = atol(infos[6].c_str());
	double qos = 0.0;

	RequestInfo request = {fileName, startx, starty, endx, endy, genTime, endTime, qos};

	return request;
}


/*
 * 
 * Created on: Dec 30, 2017
 * Author: Xiaoteng Hu
 * Description:replacement.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#include "replacement.h"

void removeFile(string fileName,string fileName2){
	int file = atoi(fileName2.c_str());
	string rfileName;
	if(file%2 == 1){
    rfileName = SHELL_PATH1 + fileName;
	}else{
	rfileName = SHELL_PATH2 + fileName;
	}
	cout<<"filefilefilefilefile"<<file<<endl;
	cout<<"rfileNamerfileNamerfileNamerfileName"<<rfileName<<endl;
	char buffer[1024];

	strcpy(buffer, rfileName.c_str());

	printf("%s\n", buffer);

	system(buffer);
}




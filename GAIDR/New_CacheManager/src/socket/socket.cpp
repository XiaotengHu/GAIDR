/*
 * 
 * Created on: Dec 27, 2017
 * Author: Xiaoteng Hu
 * Description:socket.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#include "socket.h"

void send(string ip,RequestInfo request, string pattern){
	struct sockaddr_in s_in;
	int s_fd;

	memset((void *)&s_in,0,sizeof(s_in));
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(PORT);
	inet_pton(AF_INET, ip.c_str(),(void *)&s_in.sin_addr);
	s_fd = socket(AF_INET,SOCK_STREAM,0);

	connect(s_fd,(struct sockaddr *)&s_in, sizeof(s_in));
	string reqStr  = request2String(request, pattern);
	write(s_fd,reqStr.c_str(),reqStr.size());
	close(s_fd);

}

void cacheSendCenter(string ip,RequestInfo request, string pattern){
	struct sockaddr_in s_in;
	int s_fd;

	memset((void *)&s_in,0,sizeof(s_in));
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(CACHESENDPORT);
	inet_pton(AF_INET, ip.c_str(),(void *)&s_in.sin_addr);
	s_fd = socket(AF_INET,SOCK_STREAM,0);

	connect(s_fd,(struct sockaddr *)&s_in, sizeof(s_in));
	string reqStr  = request2String(request, pattern);
	write(s_fd,reqStr.c_str(),reqStr.size());
	close(s_fd);

}




#include "socket.h"

void send(string ip, RequestInfo request, string pattern){
	struct sockaddr_in s_in;
	int s_fd;

	memset((void *)&s_in,0,sizeof(s_in));

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, ip.c_str(), (void *)&s_in.sin_addr);

	s_fd = socket(AF_INET,SOCK_STREAM,0);

	connect(s_fd,(struct sockaddr *)&s_in,sizeof(s_in));

	string reqStr = request2String(request,pattern);

	write(s_fd, reqStr.c_str(), reqStr.size());

	close(s_fd);

}

void reqEOF(){

	struct sockaddr_in s_in;
	int s_fd;

	memset((void *)&s_in,0,sizeof(s_in));

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(SERVER_PORT);

	vector<string> ips = split(SERVER_IP, ",");

	string msg = "EOF";

	for(int i=0; i<ips.size(); i++){
		inet_pton(AF_INET, ips[i].c_str(), (void *)&s_in.sin_addr);

		s_fd = socket(AF_INET,SOCK_STREAM,0);

		connect(s_fd,(struct sockaddr *)&s_in,sizeof(s_in));

		write(s_fd,msg.c_str(),msg.size());

		close(s_fd);
	}
}


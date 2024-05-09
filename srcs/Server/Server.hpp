//
// Created by sgurb on 6.05.2024.
//

#ifndef FT_IRC_SERVER_HPP
#define FT_IRC_SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <sys/poll.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <cerrno>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

#define MAX_CLIENTS 10

class Server {
private:
	std::string	pass;
	int 		port;
	int			socket;

	struct sockaddr_in		serverAddress;
public:
	int CreateSocket();
	Server(int port, std::string pass);
	~Server();
};


#endif

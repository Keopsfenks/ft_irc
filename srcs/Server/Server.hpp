//
// Created by sgurb on 6.05.2024.
//

#pragma once
#ifndef FT_IRC_SERVER_HPP
#define FT_IRC_SERVER_HPP

#include "../includes/ft_irc.hpp"

class Server {
private:
	std::string	pass;
	int 		port;
	int		    sockFD;

	struct sockaddr_in		serverAddress;
	fd_set master;
	std::vector<struct pollfd> poll_fd;
	std::vector<Client *> clients;
public:
	int CreateSocket();
	void InitializeServer();
	void ClientCreated(fd_set &tmpMaster);
	void Start();
	Server(int port, std::string pass);
	~Server();
};


#endif

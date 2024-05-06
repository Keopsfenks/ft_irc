//
// Created by sgurb on 6.05.2024.
//

#include "Server.hpp"

int Server::CreateSocket() {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		throw std::runtime_error("Socket is not created!");

	return sockfd;
}

Server::Server(int port, std::string pass) {
	this->pass = pass; this->port = port;

}
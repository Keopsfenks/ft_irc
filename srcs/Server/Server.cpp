//
// Created by sgurb on 6.05.2024.
//

#include "Server.hpp"

int Server::CreateSocket() {
	int sockFD = socket(AF_INET, SOCK_STREAM, 0);
	if (sockFD < 0)
		throw std::runtime_error("Socket is not created!");

	return sockFD;
}

Server::Server(int port, std::string pass) {
	this->pass = pass; this->port = port;
	this->socket = this->CreateSocket();

	std::cout << "Server port opened as " << this->port << std::endl;
	std::cout << "Server password opened as " << this->pass << std::endl;

	if (bind(this->socket, (struct sockaddr *)&this->serverAddress, sizeof(this->serverAddress)) < 0)
		throw std::runtime_error("Bind created as failed!");

	this->serverAddress.sin_family = AF_INET;
	this->serverAddress.sin_addr.s_addr = INADDR_ANY;
	this->serverAddress.sin_port = htons(this->port);
	if (listen(this->socket, MAX_CLIENTS) < 0)
		throw std::runtime_error("Listen mode as failed!");
}

Server::~Server() {
	std::cout << "Server Closed!" << std::endl;
}
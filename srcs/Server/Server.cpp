//
// Created by sgurb on 6.05.2024.
//

#include "../includes/ft_irc.hpp"

int Server::CreateSocket() {
	int tmpsockFD = socket(AF_INET, SOCK_STREAM, 0);
	if (tmpsockFD < 0)
		throw std::runtime_error("Socket is not created!");

	return (tmpsockFD);
}


void Server::InitializeServer() {
	int opt = 1;
	this->sockFD = this->CreateSocket();

	if (setsockopt(this->sockFD, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == ERROR)
		throw std::runtime_error("Setsockopt created as failed!");
	memset(&this->serverAddress, 0, sizeof(this->serverAddress));
	this->serverAddress.sin_family = AF_INET;
	this->serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	this->serverAddress.sin_port = htons(this->port);
	if (bind(this->sockFD, reinterpret_cast<struct sockaddr *>(&this->serverAddress), sizeof(this->serverAddress)) == ERROR)
		throw std::runtime_error("Bind created as failed!");
	if (listen(this->sockFD, MAX_CLIENTS) == ERROR)
		throw std::runtime_error("Listen mode as failed!");
	
	poll_fd.resize(1);
	poll_fd[0].fd = this->sockFD;
	poll_fd[0].events = POLLIN;

}

void Server::ClientCreated() {
		if (poll_fd[0].revents & POLLIN) {
			struct sockaddr_in clientAddress;
			socklen_t clientLen = sizeof(clientAddress);
			int clientFD = accept(this->sockFD, reinterpret_cast<struct sockaddr *>(&clientAddress), &clientLen);
			if (clientFD < 0)
				throw std::runtime_error("Accept mode as failed!");
			else {
				Client *client = new Client(clientFD);
				clients.push_back(client);
				std::cout << "New connection from " << inet_ntoa(clientAddress.sin_addr) << ":" << ntohs(clientAddress.sin_port) << std::endl;
				fcntl(clientFD, F_SETFL, O_NONBLOCK);
				poll_fd.resize(poll_fd.size() + 1);
				poll_fd[poll_fd.size() - 1].fd = clientFD;
				poll_fd[poll_fd.size() - 1].events = POLLIN;
		}
	}
}

void Server::Start() {
	while (poll(&poll_fd[0], poll_fd.size(), -1)) {
		for (size_t i = 0; i < poll_fd.size(); i++) {
			if (poll_fd[i].revents & POLLIN) {
				this->ClientCreated();
			}
		}
	}
}

Server::Server(int port, std::string pass) {
	this->pass = pass; this->port = port;
	std::cout << std::endl;
	std::cout << "Server created!" << std::endl;
	std::cout << "Server port opened as " << this->port << std::endl;
	std::cout << "Server password opened as " << this->pass << std::endl;
	this->InitializeServer();
}

Server::~Server() {
	close (this->sockFD);
	std::cout << "Server Closed!" << std::endl;
}
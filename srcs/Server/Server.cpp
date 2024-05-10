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

	//soketin bağlantı sonlandıktan hemen sonra yeniden kullanılabilmesini sağlar.
	if (setsockopt(this->sockFD, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw std::runtime_error("Setsockopt created as failed!");
	memset(&this->serverAddress, 0, sizeof(this->serverAddress));
	this->serverAddress.sin_family = AF_INET;
	this->serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	this->serverAddress.sin_port = htons(this->port);
	if (bind(this->sockFD, reinterpret_cast<struct sockaddr *>(&this->serverAddress), sizeof(this->serverAddress)) < 0)
		throw std::runtime_error("Bind created as failed!");
	if (listen(this->sockFD, MAX_CLIENTS) < 0)
		throw std::runtime_error("Listen mode as failed!");
	FD_ZERO(&this->master);
	FD_SET(this->sockFD, &this->master);
}

void Server::ClientCreated(fd_set &tmpMaster) {
    if (FD_ISSET(sockFD, &tmpMaster)) {
        struct sockaddr_in clientAddress;
        socklen_t clientLen = sizeof(clientAddress);
        int clientFD = accept(this->sockFD, reinterpret_cast<struct sockaddr *>(&clientAddress), &clientLen);
        if (clientFD < 0)
            throw std::runtime_error("Accept mode as failed!");
        else {
            Client *client = new Client(clientFD);
            clients.push_back(client);
            std::cout << "New connection from " << inet_ntoa(clientAddress.sin_addr) << ":" << ntohs(clientAddress.sin_port) << std::endl;
            FD_SET(clientFD, &tmpMaster);
        }
    }
}

void Server::Start() {
    while (true) {
        fd_set tmpMaster = this->master;
        if (select(FD_SETSIZE, &tmpMaster, nullptr, nullptr, nullptr) < 0)
            throw std::runtime_error("Select mode as failed!");
        this->ClientCreated(tmpMaster);
        char buffer[1024] = {0};
        for (size_t i = 0; i < clients.size(); i++) {
            if (FD_ISSET(clients[i]->getSocket(), &tmpMaster)) {
                clients[i]->setRecData(recv(clients[i]->getSocket(), buffer, sizeof(buffer), 0));
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
	delete (this);
	std::cout << "Server Closed!" << std::endl;
}
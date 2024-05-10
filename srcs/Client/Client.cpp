#include "Client.hpp"

Client::Client()
{
    this->pass = "";
    this->nickName = "";
    this->userName = "";
	this->ip = "";
	this->socket = -1;
    this->loggedIn = 0;
}

Client::Client(int sockfd)
{
    this->socket = sockfd;
    this->loggedIn = 0;
}

int         Client::getSocket() { return this->socket; }

bool		Client::getLoggedIn() { return this->loggedIn; }

std::string Client::getIp(){ return this->ip; }

std::string Client::getUserName(){ return this->userName; }

std::string Client::getNickName(){ return this->nickName;}

std::string Client::getPass(){ return this->pass; }

int         Client::getRecData() { return this->recData; }

void        Client::setSocket(int sockfd) { this->socket = sockfd; }

void        Client::setUserName(std::string user_name) { this->userName = user_name; }

void        Client::setNickName(std::string nick_name) { this->nickName = nick_name; }

void        Client::setPass(std::string pass) { this->pass = pass; }

void        Client::setLoggedIn(bool sign) { this->loggedIn = sign; }

void		Client::setIp(std::string ip) { this->ip = ip;}

void        Client::print(std::string str) { send(this->socket, str.c_str(), str.size(), 0); }

void        Client::setRecData(int data) { this->recData = data; }

Client::~Client() { delete this; }
#pragma once
#include <iostream>
#include <vector>
#include <sys/socket.h>

class Client
{
    private:
        int         socket;
        bool        loggedIn;
        std::string userName;
        std::string nickName;
        std::string pass;
        std::string ip;
        int     recData;
    public:
		Client();
		Client(int sockfd);
        int         getSocket();
        bool        getLoggedIn();
        std::string getUserName();
        std::string getNickName();
        std::string getPass();
        std::string getIp();
        int         getRecData();

		void        print(std::string str);
		void        setSocket(int sockfd);
        void        setLoggedIn(bool sign);
        void        setUserName(std::string user_name);
        void        setNickName(std::string nick_name);
        void        setPass(std::string pass);
		void		setIp(std::string ip);
        void        setRecData(int data);


		~Client();
};
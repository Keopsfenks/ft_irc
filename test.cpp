class Server
{
    private:
        int socket_fd;
        std::string port;
        std::string pass;
        std::vector<int> clients;
        std::vector<ClientInfo> users;
        std::vector<struct pollfd> poll_fd;
        std::vector<Channel> channels;
    protected:
    public:
        Server(std::string, std::string);
        ~Server();
        void start();
        void setup();
        void userAccept();
        void takeMassage();
        std::string Prefix(ClientInfo) const;
        void precommands(std::string, int);
        bool commands(std::string, int);
        void WELCOME(int);
        void PASS(std::string, int);
        void NICK(std::string, int);
        void USER(ClientInfo &, std::string);
        void JOIN(std::string massage, int i);
        void PRIVMSG(std::string massage, int i);
        void KICK(std::string massage, int i);
        void MODE(std::string massage, int i);
        void WHO(std::string massage, int i);
        void TOPIC(std::string massage, int i);
        void LIST(std::string massage, int i);
        void INVITE(std::string massage, int i);
        void NOTICE(std::string massage, int i);
        void QUIT(std::string massage, int i);
};

Server::Server(std::string port, std::string pass)
{
	this->port = port;
	this->pass = pass;
	if (this->pass == "")
		throw std::invalid_argument("Enter a password please");
}
Server::~Server()
{
	std::cout << "Server destroyed !!!" << std::endl;
}
void Server::setup()
{
	int opt = 1;
	this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	fcntl(this->socket_fd, F_SETFL, O_NONBLOCK);
	if (this->socket_fd < 0)
		throw std::runtime_error("server socket creation failed");
	sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(std::stoi(port));
	if (setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw std::runtime_error("socket option");
	if (bind(this->socket_fd, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr)) < 0)
		throw std::runtime_error("bind server socket failed");
	else
		std::cout << "Server is active now" << std::endl;
	if (listen(this->socket_fd, 5) < 0)
		throw std::runtime_error("listening error");
	poll_fd.resize(1);
	poll_fd[0].fd = socket_fd;
	poll_fd[0].events = POLLIN;
}
void ClientInit(ClientInfo &user, int client_fd)
{
	user.client_fd = client_fd;
	user.nick = "";
	user.username = "";
	user.hostname = "";
	user.servername = "";
	user.realname = "";
	user.pass_correct = 0;
	user.user_correct = 0;
	user.nick_correct = 0;
}
void Server::userAccept()
{
	if (poll_fd[0].revents & POLLIN)
	{
		sockaddr_in client_addr;
		socklen_t client_len = sizeof(client_addr);
		int client_fd = accept(this->socket_fd, reinterpret_cast<sockaddr *>(&client_addr), &client_len);
		if (client_fd < 0)
			throw std::runtime_error("accept error");
		else
		{
			ClientInfo user;
			ClientInit(user, client_fd);
            sender(user.client_fd, "c\r\n");
			users.push_back(user);
			std::cout << "New connection from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;
			fcntl(client_fd, F_SETFL, O_NONBLOCK);
			poll_fd.resize(poll_fd.size() + 1);
			poll_fd[poll_fd.size() - 1].fd = client_fd;
			poll_fd[poll_fd.size() - 1].events = POLLIN;
		}
	}
}
void Server::takeMassage()
{
	for (size_t i = 0; i < poll_fd.size(); i++)
	{
		if (poll_fd[i].revents & POLLIN)
		{
			int j = -1;
			userAccept();
			char buff[1024];
			std::string buffer;
			if (i != 0)
			{
				j = recv(poll_fd[i].fd, buff, 1020, 0);
				if (j < 0)
					throw std::runtime_error("recv error");
				if(j > 0 && j < 1024)
				{
					buff[j] = '\0';
					buffer = buff;
					for(unsigned long k = 0; k < buffer.length(); k++)
						if (buffer[k] == '\r' || buffer[k] == '\n')
							buffer = buffer.substr(0, k);
				}
				else
					buffer = "";
			}
			if(poll_fd[i].revents & POLLHUP)
			{
				QUIT("Control + C", i - 1);
				continue;
			}
			if (j != -1)
			{
				if (users[i - 1].pass_correct == 0 || users[i - 1].user_correct == 0 || users[i - 1].nick_correct == 0)
					precommands(buffer, i - 1);
				else if (users[i - 1].pass_correct && users[i - 1].user_correct && users[i - 1].nick_correct)
				{
					if (commands(buffer, i - 1))
					{
						if(buffer == "QUIT")
							std::cout << "Connection closed" << std::endl;
						else
							std::cout << users[i - 1].nick << " " << buffer << std::endl;
					}
					else
						std::cout << "Error: Invalid command" << std::endl;
				}
			}
			j = -1;
		}
	}
}
void Server::start()
{
	std::cout << "Server started !!!" << std::endl;
	std::cout << "Port: " << this->port << std::endl;
	std::cout << "Pass: " << this->pass << std::endl;
	setup();
	while (poll(&poll_fd[0], poll_fd.size(), -1))
	{
		takeMassage();
	}
}
11:09
struct Channel;
struct ClientInfo
{
    std::string username;
    std::string hostname;
    std::string servername;
    std::string realname;
    std::string nick;
    std::string pass;
    int client_fd;
    int pass_correct;
    int user_correct;
    int nick_correct;
    int _operator;
};
struct Channel
{
    std::string name;
    std::vector<ClientInfo> users;
    std::vector<int> operators;
    std::string topic;
};
void sender(int fd, const std::string msj);
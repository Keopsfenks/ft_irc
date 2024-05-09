#include "includes/ft_irc.hpp"

int main(int ac, char **av) {
	try {
		if (ac != 3) {
			throw std::runtime_error("This server only two parameters accepted!");
		}
		Server *server = new Server(std::atoi(av[1]), av[2]);
		server->Start();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
}

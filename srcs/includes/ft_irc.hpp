#pragma once

#include <vector>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
#include <string.h>

#include "../Client/Client.hpp"
#include "../Server/Server.hpp"

#define MAX_CLIENTS 10
#define ERROR -1
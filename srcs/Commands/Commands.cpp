#include "../includes/ft_irc.hpp"

Commands::Commands() {
    command = "";
    isLogin = false;
}

Commands::Commands(std::string command, bool isLogin) {
    this->command = command;
    this->isLogin = isLogin;
}

Commands::~Commands() {

}

std::string Commands::GetCommand() const {
    return command;
}

bool Commands::GetIsLogin() const {
    return isLogin;
}

void Commands::SetCommand(std::string command) {
    this->command = command;
}

void Commands::SetIsLogin(bool isLogin) {
    this->isLogin = isLogin;
}

void Pass::Run() {
    std::cout << "Pass command is running" << std::endl;
}
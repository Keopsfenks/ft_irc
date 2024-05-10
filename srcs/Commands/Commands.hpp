#include "../includes/ft_irc.hpp"

//Abstract class for commands
class Commands {
    protected:
        std::string command;
        bool        isLogin;
    public:
        Commands();
        Commands(std::string command, bool isLogin);
        virtual ~Commands();
        virtual void Run() = 0;
        std::string GetCommand() const;
        bool        GetIsLogin() const;

        void        SetCommand(std::string command);
        void        SetIsLogin(bool isLogin);
};


//Command class for login

class Pass : public Commands {
    public:
        Pass();
        Pass(std::string command, bool isLogin);
        ~Pass();
        void Run();
};

class Nick : public Commands {
    public:
        Nick();
        Nick(std::string command, bool isLogin);
        ~Nick();
        void Run();
};

class User : public Commands {
    public:
        User();
        User(std::string command, bool isLogin);
        ~User();
        void Run();
};

class Quit : public Commands {
    public:
        Quit();
        Quit(std::string command, bool isLogin);
        ~Quit();
        void Run();
};

//Command class for channel

class Join : public Commands {
    public:
        Join();
        Join(std::string command, bool isLogin);
        ~Join();
        void Run();
};

class Kick : public Commands {
    public:
        Kick();
        Kick(std::string command, bool isLogin);
        ~Kick();
        void Run();
};

class Part : public Commands {
    public:
        Part();
        Part(std::string command, bool isLogin);
        ~Part();
        void Run();
};

class Topic : public Commands {
    public:
        Topic();
        Topic(std::string command, bool isLogin);
        ~Topic();
        void Run();
};

class PrivMsg : public Commands {
    public:
        PrivMsg();
        PrivMsg(std::string command, bool isLogin);
        ~PrivMsg();
        void Run();
};

class Who : public Commands {
    public:
        Who();
        Who(std::string command, bool isLogin);
        ~Who();
        void Run();
};
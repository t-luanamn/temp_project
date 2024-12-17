#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "Client.hpp"
# include "Server.hpp"

class Server;

class Command
{
  public:
    Command(Server *server);
    void execute(Client *client, const std::vector<std::string> &tokens);

  private:
    Server *server;

    bool checkPassword(Client *client, const std::string &enteredPassword);
    void setUsername(Client *client, const std::string &message);
    void printStatus(Client *client);
    void sendToUser(Client *client, const std::string &message);
    void createGroup(Client *client, const std::string &message);
    void loginToGroup(Client *client, const std::string &message);
    void sendToGroup(Client *client, const std::string &message);
    void joinGroup(Client *client, const std::string &message);
    void invite(Client *client, const std::string &message);
    void kick(Client *client, const std::string &message);
    void changeTopic(Client *client, const std::string &message);
    void setMode(Client *client, const std::string &message);
};

#endif

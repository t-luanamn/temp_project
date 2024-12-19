#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/select.h>
# include <sys/socket.h>
# include <unistd.h>
# include <vector>
# include <string>
# include <sstream>
# include <cctype>

# include "Log.hpp"
# include "Client.hpp"

# define MAX_CLIENTS 5
# define IP_ADDR "127.0.0.1"
# define OPER_PASS "bean"
class Server
{
  public:
    Server(const std::string &name, int port, const std::string &password);
    ~Server();

    void start();

  private:
    std::string _servName;
    int _port;
    std::string _password;
    int _serverfd;
    std::vector<Client *> clientList;
    std::vector<Group *> groupList;
    Log log;

    void handleClientMessages(fd_set &readfds);
    void handleMessage(Client *client, const std::string &message);
    std::string sendWelcomeMessage(Client* client);
    void handleUserLogin(Client* client);
    // void print_status() const;
    // void find_and_send_to_group(const std::string &src_string);
    // void join_group(const std::string &targetGroup, Client *client);
    void sendPrivateMessage(Client* senderClient, const std::vector<std::string> &tokens);
    Client* findClient(const std::string &name);
    // void create_group(Client *current_client, const std::string &newGroupName);
    // void add_to_group(const std::string &src_string, Client *current_client);
    // void kick_from_group(const std::string &src_string, Client *current_client);
    // bool isClientValidForGroup(Client *current_client, const std::string &groupName);
    // void remove_operator_privilege(const std::string &src_string, Client *current_client);
    // void set_remove_invite_only(const std::string &src_string, Client *current_client);
    // void set_channel_password(const std::string &src_string, Client *current_client);
    // void set_user_limit(const std::string &src_string, Client *current_client);
    // void set_remove_topic(const std::string &src_string, Client *current_client);
    // void login_to_group(const std::string &src_string, Client *current_client);
    // void change_group_topic(const std::string &src_string, Client *current_client);

    void execute(Client *client, const std::vector<std::string> &tokens);
    void checkPassword(Client *client, const char *message);
    void setUser(Client *client, const std::vector<std::string> &tokens);
    void setNick(Client *client, const std::vector<std::string> &tokens);
    void setOper(Client *client, const std::vector<std::string> &tokens);
    // void printStatus(Client *client);
    // void sendToUser(Client *client, const std::string &message);
    // void createGroup(Client *client, const std::string &message);
    // void loginToGroup(Client *client, const std::string &message);
    // void sendToGroup(Client *client, const std::string &message);
    // void joinGroup(Client *client, const std::string &message);
    // void invite(Client *client, const std::string &message);
    // void kick(Client *client, const std::string &message);
    // void changeTopic(Client *client, const std::string &message);
    // void setMode(Client *client, const std::string &message);    
};

// Utility functions
bool isNumber(const std::string &str);
bool validateInput(int ac, char **av);
bool isValidChannelName(const std::string& channelName);

#endif
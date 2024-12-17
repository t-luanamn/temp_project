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
# include "Command.hpp"

# define MAX_CLIENTS 5
# define IP_ADDR "127.0.0.1"
class Server
{
  public:
    Server(const std::string &name, int port, const std::string &password);
    ~Server();

    void start();
    void print_status() const;
    void find_and_send_to_group(const std::string &src_string);
    void join_group(const std::string &targetGroup, Client *client);
    void send_to_user(const std::string &src_string);
    void create_group(Client *current_client, const std::string &newGroupName);
    void add_to_group(const std::string &src_string, Client *current_client);
    void kick_from_group(const std::string &src_string, Client *current_client);
    bool isClientValidForGroup(Client *current_client, const std::string &groupName);
    void remove_operator_privilege(const std::string &src_string, Client *current_client);
    void set_remove_invite_only(const std::string &src_string, Client *current_client);
    void set_channel_password(const std::string &src_string, Client *current_client);
    void set_user_limit(const std::string &src_string, Client *current_client);
    void set_remove_topic(const std::string &src_string, Client *current_client);
    void login_to_group(const std::string &src_string, Client *current_client);
    void change_group_topic(const std::string &src_string, Client *current_client);

  private:
    std::string _servName;
    int _port;
    std::string _password;
    int _serverfd;
    std::vector<Client *> clientList;
    std::vector<Group *> groupList;

    void handleClientMessages(fd_set &readfds);
    void handleMessage(Client *client, const std::string &message);
    std::string sendWelcomeMessage(void);
    Log log;
};

// Utility functions
bool isNumber(const std::string &str);
bool validateInput(int ac, char **av);

#endif
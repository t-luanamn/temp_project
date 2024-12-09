#include "../inc/Server.hpp"

Server::Server(int port, const std::string &password) : _port(port), _password(password)
{
  Log::nl("Server is created", G);
  serverfd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverfd <= 0)
  {
    std::cerr << "socket creation error\n";
    exit(1);
  }
  int opt = 1;
  if (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof opt) < 0)
  {
    std::cerr << "setSocketopt error\n";
    exit(2);
  }
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
  if (bind(serverfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
  {
    std::cerr << "bind error\n";
    exit(3);
  }
  if (listen(serverfd, 5) < 0)
  {
    std::cerr << "listen error\n";
    exit(4);
  }
}

Server::~Server()
{
  Log::nl("Server is destroyed", R);
  close(serverfd);
  for (std::vector<Client *>::iterator it = clientList.begin(); it != clientList.end(); ++it)
  {
    delete *it;
  }
  for (std::vector<Group *>::iterator it = groupList.begin(); it != groupList.end(); ++it)
  {
    delete *it;
  }
}

void Server::start()
{
  fd_set readfds;
  while (true)
  {
    FD_ZERO(&readfds);
    FD_SET(serverfd, &readfds);
    int maxfd = serverfd;
    for (std::vector<Client *>::iterator it = clientList.begin(); it != clientList.end(); ++it)
    {
      int sd = (*it)->getClientfd();
      FD_SET(sd, &readfds);
      if (sd > maxfd)
      {
        maxfd = sd;
      }
    }
    int activity = select(maxfd + 1, &readfds, NULL, NULL, NULL);
    if (activity < 0)
    {
      std::cerr << "select error\n";
      continue;
    }
    if (FD_ISSET(serverfd, &readfds))
    {
      int clientfd = accept(serverfd, (struct sockaddr *)NULL, NULL);
      if (clientfd < 0)
      {
        std::cerr << "accept error\n";
        continue;
      }
      Client *new_client = new Client(clientfd);
      clientList.push_back(new_client);
      std::string buffer = "Login:\n";
      send(clientfd, buffer.c_str(), buffer.length(), MSG_DONTROUTE);
    }
    char message[1024];
    for (std::vector<Client *>::iterator it = clientList.begin(); it != clientList.end(); ++it)
    {
      int sd = (*it)->getClientfd();
      if (FD_ISSET(sd, &readfds))
      {
        int valread = read(sd, message, 1024);
        if (valread == 0)
        {
          close(sd);
          delete *it;
          clientList.erase(it);
          --it;
        }
        else
        {
          message[valread] = '\0';
          handleMessage(*it, message);
        }
      }
    }
  }
}

void Server::print_status() const
{
  // Implementation of print_status
}

void Server::find_and_send_to_group(const std::string &src_string)
{
  // Implementation of find_and_send_to_group
}

void Server::join_group(const std::string &targetGroup, Client *client)
{
  // Implementation of join_group
}

void Server::send_to_user(const std::string &src_string)
{
  // Implementation of send_to_user
}

void Server::create_group(Client *current_client, const std::string &newGroupName)
{
  // Implementation of create_group
}

void Server::add_to_group(const std::string &src_string, Client *current_client)
{
  // Implementation of add_to_group
}

void Server::kick_from_group(const std::string &src_string, Client *current_client)
{
  // Implementation of kick_from_group
}

bool Server::isClientValidForGroup(Client *current_client, const std::string &groupName)
{
  // Implementation of isClientValidForGroup
}

void Server::remove_operator_privilege(const std::string &src_string, Client *current_client)
{
  // Implementation of remove_operator_privilege
}

void Server::set_remove_invite_only(const std::string &src_string, Client *current_client)
{
  // Implementation of set_remove_invite_only
}

void Server::set_channel_password(const std::string &src_string, Client *current_client)
{
  // Implementation of set_channel_password
}

void Server::set_user_limit(const std::string &src_string, Client *current_client)
{
  // Implementation of set_user_limit
}

void Server::set_remove_topic(const std::string &src_string, Client *current_client)
{
  // Implementation of set_remove_topic
}

void Server::login_to_group(const std::string &src_string, Client *current_client)
{
  // Implementation of login_to_group
}

void Server::change_group_topic(const std::string &src_string, Client *current_client)
{
  // Implementation of change_group_topic
}

void Server::handleMessage(Client *client, const std::string &message)
{
  // Implementation of handleMessage
}

bool isNumber(const std::string &str)
{
  for (std::string::const_iterator i = str.begin(); i != str.end(); ++i)
  {
    if (!std::isdigit(*i))
    {
      return false;
    }
  }
  return true;
}

bool validateInput(int ac, char **av)
{
  Log log;

  if (ac != 3)
  {
    log.nl("Usage: ./ircserv <port> <password>", R);
    return false;
  }
  if (!isNumber(av[1]))
  {
    log.nl("Port must be a number and be between 0 and 65535", R);
    return false;
  }
  int port = atoi(av[1]);
  if (port > 65535 || port < 0)
  {
    log.nl("Port must be a number and be between 0 and 65535", R);
    return false;
  }
  return true;
}
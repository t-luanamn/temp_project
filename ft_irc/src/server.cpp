#include "../inc/Server.hpp"

Server::Server(int port, const std::string &password) : _port(port), _password(password)
{
  log.nl("Server is created", G);
  log.out("Server listening on Port: ", G);
  log.nl(_port, B);

  serverfd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverfd <= 0)
  {
    std::cerr << "Socket creation error\n";
    exit(1);
  }

  int opt = 1;
  if (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
  {
    std::cerr << "Set socket option error\n";
    close(serverfd);
    exit(2);
  }

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(_port);
  if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0)
  {
    std::cerr << "Invalid address/ Address not supported\n";
    close(serverfd);
    exit(3);
  }

  if (bind(serverfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
  {
    std::cerr << "Bind error\n";
    close(serverfd);
    exit(4);
  }

  if (listen(serverfd, 5) < 0)
  {
    std::cerr << "Listen error\n";
    close(serverfd);
    exit(5);
  }
}

Server::~Server()
{
  log.nl("Server is destroyed", R);
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
          clientList.erase(it);
          break;
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

void Server::handleMessage(Client *client, const std::string &message)
{
  (void)client; // Mark as unused
  (void)message; // Mark as unused
  // Handle the message received from the client
}

void Server::print_status() const
{
  Log log;

  log.nl("Server Status:", G);
  log.nl("----------------------------------------", G);
  log.out("Server File Descriptor: ", G);
  log.nl(serverfd, B);
  log.nl("Connected Clients:", G);

  for (size_t i = 0; i < clientList.size(); ++i)
  {
    Client *client = clientList[i];
    if (client)
    {
      log.out("Client ID: ", G);
      log.nl(client->getClientfd(), B);
      log.out("Username: ", G);
      log.nl(client->getUsername(), B);
      log.out("Logged In: ", G);
      log.nl(client->getLoginStatus() ? "Yes" : "No", B);
    }
  }
}

void Server::find_and_send_to_group(const std::string &src_string)
{
  char delimiter = ' ';
  size_t pos = src_string.find(delimiter);

  std::string GroupName = src_string.substr(0, pos);
  std::string message = src_string.substr(pos + 1);

  for (size_t i = 0; i < groupList.size(); i++)
  {
    if (groupList[i]->getGroupName() == GroupName)
    {
      std::cout << "Found Group with name: " << GroupName << std::endl;
      Group *target_group = groupList[i];
      std::vector<Client *> members = target_group->getMembersList();
      for (size_t j = 0; j < members.size(); j++)
      {
        send(members[j]->getClientfd(), message.c_str(), message.length(), MSG_DONTROUTE);
      }
      return;
    }
  }
  std::cout << "No Group with name " << GroupName << " found." << std::endl;
}

void Server::join_group(const std::string &targetGroup, Client *client)
{
  for (size_t i = 0; i < groupList.size(); ++i)
  {
    if (groupList[i]->getGroupName() == targetGroup)
    {
      std::cout << "Found Group with name: " << targetGroup << std::endl;

      if (groupList[i]->getMemberLimit() > 0 && static_cast<int>(groupList[i]->getMembersList().size()) >= groupList[i]->getMemberLimit())
      {
        std::cout << "Cannot join group: Member limit reached." << std::endl;
        return;
      }

      groupList[i]->addMember(client);
      client->addGroup(groupList[i]);

      std::cout << "Client added to group: " << targetGroup << std::endl;
      return;
    }
  }
  std::cout << "No Group with name " << targetGroup << " found." << std::endl;
}

void Server::send_to_user(const std::string &src_string)
{
  std::cout << "Command: Send To User\n";
  char delimiter = ' ';
  size_t spacePos = src_string.find(delimiter);

  std::string target_username = src_string.substr(0, spacePos);
  std::string message = src_string.substr(spacePos + 1);

  for (size_t i = 0; i < clientList.size(); i++)
  {
    if (clientList[i]->getUsername() == target_username)
    {
      send(clientList[i]->getClientfd(), message.c_str(), message.length(), MSG_DONTROUTE);
      return;
    }
  }
  std::cout << "No user with username: " << target_username << " found." << std::endl;
}

void Server::create_group(Client *current_client, const std::string &newGroupName)
{
  Group *newGroup = new Group(newGroupName); // Use constructor to set group name
  newGroup->addMember(current_client); // Add current client as a member
  newGroup->setOwner(current_client); // Set current client as the owner
  newGroup->addOperator(current_client); // Add current client as an operator
  current_client->addGroup(newGroup); // Add new group to the client's group list
  groupList.push_back(newGroup); // Add new group to the server's group list
}

void Server::add_to_group(const std::string &src_string, Client *current_client)
{
  size_t spacePos = src_string.find(' ');
  if (spacePos == std::string::npos)
  {
    std::cerr << "Invalid input format for Add to Group\n";
    return;
  }

  std::string GroupName = src_string.substr(0, spacePos);
  std::string newUser = src_string.substr(spacePos + 1);

  for (size_t i = 0; i < clientList.size(); ++i)
  {
    if (clientList[i]->getUsername() == newUser)
    {
      std::cout << "Client exists: " << newUser << std::endl;

      for (size_t j = 0; j < groupList.size(); ++j)
      {
        if (groupList[j]->getGroupName() == GroupName)
        {
          if (!groupList[j]->isOperator(current_client))
          {
            std::cout << "You must be an operator to add members to the group: " << GroupName << ".\n";
            return;
          }

          if (groupList[j]->getMemberLimit() > 0 && static_cast<int>(groupList[j]->getMembersList().size()) >= groupList[j]->getMemberLimit())
          {
            std::cout << "Cannot add to group: Member limit reached." << std::endl;
            return;
          }

          groupList[j]->addMember(clientList[i]);
          clientList[i]->addGroup(groupList[j]);

          std::cout << "Client added to group: " << GroupName << std::endl;
          return;
        }
      }
      std::cout << "Group: " << GroupName << " does not exist." << std::endl;
      return;
    }
  }
  std::cout << "New member: " << newUser << " does not exist." << std::endl;

  std::string buffer = "Failed to add " + newUser + " to " + GroupName + ". Try again.\n";
  send(current_client->getClientfd(), buffer.c_str(), buffer.length(), MSG_DONTROUTE);
}

void Server::kick_from_group(const std::string &src_string, Client *current_client)
{
  size_t spacePos = src_string.find(' ');
  if (spacePos == std::string::npos)
  {
    std::cerr << "Invalid input format for Kick From Group\n";
    return;
  }

  std::string GroupName = src_string.substr(0, spacePos);
  std::string targetUser = src_string.substr(spacePos + 1);

  for (size_t j = 0; j < groupList.size(); ++j)
  {
    Group *group = groupList[j];

    if (group->getGroupName() == GroupName)
    {
      std::cout << "Group exists: " << GroupName << std::endl;

      if (!group->isOperator(current_client))
      {
        std::cout << "You must be an operator to kick members from the group: " << GroupName << ".\n";
        return;
      }

      std::vector<Client *> members = group->getMembersList();
      for (size_t i = 0; i < members.size(); ++i)
      {
        if (members[i]->getUsername() == targetUser)
        {
          group->removeMember(members[i]);
          std::cout << "User " << targetUser << " removed from group " << GroupName << std::endl;
          return;
        }
      }

      std::cout << "User " << targetUser << " not found in group " << GroupName << std::endl;
      return;
    }
  }

  std::string buffer = "Failed to remove " + targetUser + " from " + GroupName + ". Try again.\n";
  send(current_client->getClientfd(), buffer.c_str(), buffer.length(), MSG_DONTROUTE);
}

bool Server::isClientValidForGroup(Client *current_client, const std::string &groupName)
{
  for (size_t j = 0; j < groupList.size(); j++)
  {
    if (groupList[j]->getGroupName() == groupName)
    {
      bool isLoggedIn = current_client->getLoginStatus();
      bool isPartOfGroup = std::find(groupList[j]->getMembersList().begin(), groupList[j]->getMembersList().end(), current_client) != groupList[j]->getMembersList().end();

      if (!isLoggedIn || !isPartOfGroup)
      {
        std::cerr << "Client is not logged in or not part of the group.\n";
        return false;
      }

      if (groupList[j]->getPassword() != "")
      {
        std::string enteredPassword;
        std::cout << "Enter password for group " << groupName << ": ";
        std::cin >> enteredPassword;

        if (enteredPassword != groupList[j]->getPassword())
        {
          std::cerr << "Incorrect password.\n";
          return false;
        }
      }
      return true;
    }
  }
  std::cerr << "Group not found.\n";
  return false;
}

void Server::remove_operator_privilege(const std::string &src_string, Client *current_client)
{
  size_t spacePos = src_string.find(' ');
  if (spacePos == std::string::npos)
  {
    std::cerr << "Invalid input format for Remove Operator Privilege\n";
    return;
  }
  std::string GroupName = src_string.substr(0, spacePos);
  std::string targetUser = src_string.substr(spacePos + 1);

  for (size_t j = 0; j < groupList.size(); j++)
  {
    if (groupList[j]->getGroupName() == GroupName)
    {
      if (!groupList[j]->isOperator(current_client))
      {
        std::cout << "You do not have permission to remove operator privileges.\n";
        return;
      }

      std::vector<Client *> operators = groupList[j]->getOperatorList();
      for (size_t i = 0; i < operators.size(); i++)
      {
        if (operators[i]->getUsername() == targetUser)
        {
          groupList[j]->removeOperator(operators[i]);
          std::cout << "Operator privileges removed from " << targetUser << " in group " << GroupName << std::endl;
          return;
        }
      }
      std::cout << targetUser << " not found in operator list.\n";
      return;
    }
  }
  std::cout << "Group " << GroupName << " not found.\n";
}

void Server::set_remove_invite_only(const std::string &src_string, Client *current_client)
{
  size_t spacePos = src_string.find(' ');
  if (spacePos == std::string::npos)
  {
    std::cerr << "Invalid input format for Set/Remove Invite Only\n";
    return;
  }
  std::string GroupName = src_string.substr(0, spacePos);
  std::string set = src_string.substr(spacePos + 1);

  for (size_t j = 0; j < groupList.size(); j++)
  {
    if (groupList[j]->getGroupName() == GroupName)
    {
      if (!groupList[j]->isOperator(current_client))
      {
        std::cout << "You do not have permission to change invite-only setting.\n";
        return;
      }

      if (set == "set")
        groupList[j]->setInviteOnly(true);
      else if (set == "remove")
        groupList[j]->setInviteOnly(false);

      std::cout << "Invite-only setting changed for group " << GroupName << std::endl;
      return;
    }
  }
  std::cout << "Group " << GroupName << " not found.\n";
}

void Server::set_channel_password(const std::string &src_string, Client *current_client)
{
  std::istringstream stream(src_string);

  std::string GroupName, set, newPassword;
  stream >> GroupName >> set >> newPassword;

  for (size_t j = 0; j < groupList.size(); j++)
  {
    if (groupList[j]->getGroupName() == GroupName)
    {
      if (!groupList[j]->isOperator(current_client))
      {
        std::cout << "You do not have permission to set or remove the channel password.\n";
        return;
      }

      if (set == "set")
      {
        groupList[j]->setPasswordOn(true);
        groupList[j]->setPassword(newPassword);
      }
      else if (set == "remove")
      {
        groupList[j]->setPasswordOn(false);
        groupList[j]->setPassword("");
      }

      std::cout << "Channel password setting changed for group " << GroupName << std::endl;
      return;
    }
  }
  std::cout << "Group " << GroupName << " not found.\n";
}

void Server::set_user_limit(const std::string &src_string, Client *current_client)
{
  std::istringstream stream(src_string);

  std::string GroupName, limit_bool, str_number;
  stream >> GroupName >> limit_bool >> str_number;

  for (size_t j = 0; j < groupList.size(); j++)
  {
    if (groupList[j]->getGroupName() == GroupName)
    {
      if (!groupList[j]->isOperator(current_client))
      {
        std::cout << "You do not have permission to change user limit.\n";
        return;
      }

      if (limit_bool == "set")
      {
        groupList[j]->setMemberLimitOn(true);
        groupList[j]->setMemberLimit(atoi(str_number.c_str()));
      }
      else if (limit_bool == "remove")
      {
        groupList[j]->setMemberLimitOn(false);
        groupList[j]->setMemberLimit(2147483647);
      }

      std::cout << "User limit setting changed for group " << GroupName << std::endl;
      return;
    }
  }
  std::cout << "Group " << GroupName << " not found.\n";
}

void Server::set_remove_topic(const std::string &src_string, Client *current_client)
{
  std::istringstream stream(src_string);

  std::string GroupName, topic_bool, str_topic;
  stream >> GroupName >> topic_bool >> str_topic;

  for (size_t j = 0; j < groupList.size(); j++)
  {
    if (groupList[j]->getGroupName() == GroupName)
    {
      if (!groupList[j]->isOperator(current_client))
      {
        std::cout << "You do not have permission to change the topic.\n";
        return;
      }

      if (topic_bool == "set")
      {
        groupList[j]->setTopicBool(true);
        groupList[j]->setTopic(str_topic);
      }
      else if (topic_bool == "remove")
      {
        groupList[j]->setTopicBool(false);
        groupList[j]->setTopic("");
      }

      std::cout << "Topic setting changed for group " << GroupName << std::endl;
      return;
    }
  }
  std::cout << "Group " << GroupName << " not found.\n";
}

void Server::login_to_group(const std::string &src_string, Client *current_client)
{
  std::istringstream stream(src_string);

  std::string GroupName, password_guess;
  stream >> GroupName >> password_guess;

  for (size_t j = 0; j < groupList.size(); j++)
  {
    if (groupList[j]->getGroupName() == GroupName)
    {
      if (!groupList[j]->getPasswordOn())
      {
        groupList[j]->addCurrentlySignedIn(current_client);
        std::cout << "Client logged into group: " << GroupName << std::endl;
        return;
      }
      else
      {
        if (groupList[j]->getPassword() == password_guess)
        {
          groupList[j]->addCurrentlySignedIn(current_client);
          std::cout << "Client logged into group: " << GroupName << std::endl;
          return;
        }
        else
        {
          std::cerr << "Incorrect password for group: " << GroupName << std::endl;
          return;
        }
      }
    }
  }
  std::cerr << "Group not found: " << GroupName << std::endl;
}

void Server::change_group_topic(const std::string &src_string, Client *current_client)
{
  size_t spacePos = src_string.find(' ');
  if (spacePos == std::string::npos)
  {
    std::cerr << "Invalid input format for Change Group Topic\n";
    return;
  }
  std::string GroupName = src_string.substr(0, spacePos);
  std::string newTopic = src_string.substr(spacePos + 1);

  for (size_t j = 0; j < groupList.size(); j++)
  {
    if (groupList[j]->getGroupName() == GroupName)
    {
      if (!groupList[j]->isOperator(current_client))
      {
        std::cout << "You do not have permission to change the topic.\n";
        return;
      }

      groupList[j]->setTopicBool(true);
      groupList[j]->setTopic(newTopic);

      std::cout << "Topic changed for group " << GroupName << " to " << newTopic << std::endl;
      return;
    }
  }
  std::cerr << "Group not found: " << GroupName << std::endl;
}

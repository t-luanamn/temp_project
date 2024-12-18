/*
Command: INVITE
   Parameters: <nickname> <channel>
*/

#include "../inc/Server.hpp"

void Command::invite(Client *client, const std::string &message)
{
    if (server->isClientValidForGroup(client, message.substr(7)))
    {
        server->add_to_group(message.substr(7), client);
    }
}

// ------------------

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


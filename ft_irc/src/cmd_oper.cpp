/*
Command: OPER
   Parameters: <name> <password>
*/

#include "../inc/Command.hpp"

void Server::create_group(Client *current_client, const std::string &newGroupName)
{
  Group *newGroup = new Group(newGroupName); // Use constructor to set group name
  newGroup->addMember(current_client); // Add current client as a member
  newGroup->setOwner(current_client); // Set current client as the owner
  newGroup->addOperator(current_client); // Add current client as an operator
  current_client->addGroup(newGroup); // Add new group to the client's group list
  groupList.push_back(newGroup); // Add new group to the server's group list
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

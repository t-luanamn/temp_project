/*
Command: TOPIC
   Parameters: <channel> [ <topic> ]
*/

#include "../inc/Server.hpp"

void Command::changeTopic(Client *client, const std::string &message)
{
    if (server->isClientValidForGroup(client, message.substr(6)))
    {
        server->change_group_topic(message.substr(6), client);
    }
}

// ------------------

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

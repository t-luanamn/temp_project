/*
Command: KICK
   Parameters: <channel> *( "," <channel> ) <user> *( "," <user> )
               [<comment>]
   Examples:

   KICK &Melbourne Matthew         ; Command to kick Matthew from
                                   &Melbourne

   KICK #Finnish John :Speaking English
                                   ; Command to kick John from #Finnish
                                   using "Speaking English" as the
                                   reason (comment).

   :WiZ!jto@tolsun.oulu.fi KICK #Finnish John
                                   ; KICK message on channel #Finnish
                                   from WiZ to remove John from channel
*/

#include "../inc/Command.hpp"

void Command::kick(Client *client, const std::string &message)
{
    if (server->isClientValidForGroup(client, message.substr(5)))
    {
        server->kick_from_group(message.substr(5), client);
    }
}

// ------------------

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

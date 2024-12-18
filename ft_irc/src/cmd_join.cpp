/*
Command: JOIN
   Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] )
               / "0"
   The JOIN command is used by a user to request to start listening to
   the specific channel.  Servers MUST be able to parse arguments in the
   form of a list of target, but SHOULD NOT use lists when sending JOIN
   messages to clients.

   Once a user has joined a channel, he receives information about
   all commands his server receives affecting the channel.  This
   includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.
   This allows channel members to keep track of the other channel
   members, as well as channel modes.

   If a JOIN is successful, the user receives a JOIN message as
   confirmation and is then sent the channel's topic (using RPL_TOPIC) and
   the list of users who are on the channel (using RPL_NAMREPLY), which
   MUST include the user joining.

   Note that this message accepts a special argument ("0"), which is
   a special request to leave all channels the user is currently a member
   of.  The server will process this message as if the user had sent
   a PART command (See Section 3.2.2) for each channel he is a member
   of.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
           ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
           ERR_CHANNELISFULL               ERR_BADCHANMASK
           ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
           ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
           RPL_TOPIC

   Examples:

   JOIN #foobar                    ; Command to join channel #foobar.

   JOIN &foo fubar                 ; Command to join channel &foo using
                                   key "fubar".
   JOIN #foo,&bar fubar            ; Command to join channel #foo using
                                   key "fubar" and &bar using no key.

   JOIN #foo,#bar fubar,foobar     ; Command to join channel #foo using
                                   key "fubar", and channel #bar using
                                   key "foobar".

   JOIN #foo,#bar                  ; Command to join channels #foo and
                                   #bar.

   JOIN 0                          ; Leave all currently joined
                                   channels.

   :WiZ!jto@tolsun.oulu.fi JOIN #Twilight_zone ; JOIN message from WiZ
                                   on channel #Twilight_zone
*/

#include "../inc/Server.hpp"

/*
void Server::createGroup(Client *client, const std::string &message)
{
    server->create_group(client, message.substr(13));
}

void Server::loginToGroup(Client *client, const std::string &message)
{
    server->login_to_group(message.substr(15), client);
}

void Server::sendToGroup(Client *client, const std::string &message)
{
    if (server->isClientValidForGroup(client, message.substr(14)))
    {
        server->find_and_send_to_group(message.substr(14));
    }
}

void Server::joinGroup(Client *client, const std::string &message)
{
    if (server->isClientValidForGroup(client, message.substr(11)))
    {
        server->join_group(message.substr(11), client);
    }
}

// ------------------

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

*/
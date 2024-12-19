/*
Channels names are strings (beginning with a '&', '#', '+' or '!'
   character) of length up to fifty (50) characters.  Apart from the
   requirement that the first character is either '&', '#', '+' or '!',
   the only restriction on a channel name is that it SHALL NOT contain
   any spaces (' '), a control G (^G or ASCII 7), a comma (',').  Space
   is used as parameter separator and command is used as a list item
   separator by the protocol).  A colon (':') can also be used as a
   delimiter for the channel mask.  Channel names are case insensitive.

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

467    ERR_KEYSET
      "<channel> :Channel key already set"
471    ERR_CHANNELISFULL
      "<channel> :Cannot join channel (+l)"
472    ERR_UNKNOWNMODE
      "<char> :is unknown mode char to me for <channel>"
473    ERR_INVITEONLYCHAN
      "<channel> :Cannot join channel (+i)"
474    ERR_BANNEDFROMCHAN
      "<channel> :Cannot join channel (+b)"
475    ERR_BADCHANNELKEY
      "<channel> :Cannot join channel (+k)"
476    ERR_BADCHANMASK
      "<channel> :Bad Channel Mask"
477    ERR_NOCHANMODES
      "<channel> :Channel doesn't support modes"
478    ERR_BANLISTFULL
      "<channel> <char> :Channel list is full"

481    ERR_NOPRIVILEGES
      ":Permission Denied- You're not an IRC operator"

  - Any command requiring operator privileges to operate
    MUST return this error to indicate the attempt was
    unsuccessful.

482    ERR_CHANOPRIVSNEEDED
      "<channel> :You're not channel operator"

  - Any command requiring 'chanop' privileges (such as
    MODE messages) MUST return this error if the client
    making the attempt is not a chanop on the specified
    channel.
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

/*
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

*/




//bool isValidChannelName(const std::string& channelName)

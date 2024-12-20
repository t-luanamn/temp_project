/*
Command: MODE
   Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )

   The MODE command is provided so that users may query and change the
   characteristics of a channel.  For more details on available modes
   and their uses, see "Internet Relay Chat: Channel Management" [IRC-
   CHAN].  Note that there is a maximum limit of three (3) changes per
   command for modes that take a parameter.

   The available modes are as follows:
   · i: Set/remove Invite-only channel
   · t: Set/remove the restrictions of the TOPIC command to channel operators
   · k: Set/remove the channel key (password)
   · o: Give/take channel operator privilege
   · l: Set/remove the user limit to channel

   The following examples are given to help understanding the syntax of
   the MODE command, but refer to modes defined in "Internet Relay Chat:
   Channel Management" [IRC-CHAN].

   Examples:

   MODE #Finnish +o Kilroy         ; Command to give 'chanop' privileges
                                   to Kilroy on channel #Finnish.

   MODE #Finnish +v Wiz            ; Command to allow WiZ to speak on
                                   #Finnish.

   MODE #42 +k oulu                ; Command to set the channel key to
                                   "oulu".

   MODE #42 -k oulu                ; Command to remove the "oulu"
                                   channel key on channel "#42".




*/

#include "../inc/Server.hpp"

void Server::setMode(Client *client, const std::vector<std::string> &tokens)
{
  if (tokens.size() < 3)
  {
    std::string msg = "\033[0;31mError: Not enough parameters.\033[0;0m\n";
    msg.append("Usage: MODE <channel> <( \"-\" / \"+\" )modes> [parameters]\n");
    send(client->getClientfd(), msg.c_str(), msg.length(), MSG_DONTROUTE);
    return;
  }

  if (!client->getOperator())
  {
    std::string msg = "\033[0;31mError: You're not channel operator.\033[0;0m\n";
    send(client->getClientfd(), msg.c_str(), msg.length(), MSG_DONTROUTE);
    return;
  }

  std::string channelName = tokens[1];
  Channel *channel = findChannelByName(channelName);
  if (!channel)
  {
    std::string msg = "\033[0;31mError: No such channel.\033[0;0m\n";
    send(client->getClientfd(), msg.c_str(), msg.length(), MSG_DONTROUTE);
    return;
  }

  if (!channel->isUserInChannel(client))
  {
    std::string msg = "\033[0;31mError: You're not on that channel.\033[0;0m\n";
    send(client->getClientfd(), msg.c_str(), msg.length(), MSG_DONTROUTE);
    return;
  }

  std::string modes = tokens[2];
  bool adding = true;
  size_t paramIndex = 3;

  for (size_t i = 0; i < modes.size(); ++i)
  {
    char mode = modes[i];
    if (mode == '+')
    {
      adding = true;
    }
    else if (mode == '-')
    {
      adding = false;
    }
    else
    {
      switch (mode)
      {
        case 'i':
          channel->setInviteOnly(adding);
          break;
        case 't':
          // Implement setting/removing topic restriction
          break;
        case 'k':
          if (paramIndex < tokens.size())
          {
            if (adding)
              channel->setKey(tokens[paramIndex]);
            else
              channel->setKey("");
            paramIndex++;
          }
          break;
        case 'o':
          if (paramIndex < tokens.size())
          {
            Client *targetClient = findClient(tokens[paramIndex]);
            if (targetClient && channel->isUserInChannel(targetClient))
            {
              if (adding)
                channel->addOperator(targetClient);
              else
                channel->removeOperator(targetClient);
            }
            paramIndex++;
          }
          break;
        case 'l':
          if (paramIndex < tokens.size())
          {
            if (adding)
            {
              channel->setLimit(std::atoi(tokens[paramIndex].c_str()));
            }
            else
            {
              channel->setLimit(0);
            }
            paramIndex++;
          }
          break;
        default:
          std::string msg = "\033[0;31mError: Unknown mode.\033[0;0m\n";
          send(client->getClientfd(), msg.c_str(), msg.length(), MSG_DONTROUTE);
          break;
      }
    }
  }
}

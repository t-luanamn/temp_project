/*
Internet Relay Chat: Client Protocol
https://datatracker.ietf.org/doc/html/rfc2812


The commands described here are used to register a connection with an
   IRC server as a user as well as to correctly disconnect.

   A "PASS" command is not required for a client connection to be
   registered, but it MUST precede the latter of the NICK/USER
   combination (for a user connection) or the SERVICE command (for a
   service connection). The RECOMMENDED order for a client to register
   is as follows:

                           1. Pass message
           2. Nick message                 2. Service message
           3. User message

   Upon success, the client will receive an RPL_WELCOME (for users) or
   RPL_YOURESERVICE (for services) message indicating that the
   connection is now registered and known the to the entire IRC network.
   The reply message MUST contain the full client identifier upon which
   it was registered.
*/

#include "../inc/Server.hpp"

void Server::execute(Client *client, const std::vector<std::string> &tokens, const std::string &message)
{
  std::string command = tokens[0];
  if (command == "PASS")
  {
    std::string msg = "You are already registered.\n";
    send(client->getClientfd(), msg.c_str(), msg.length(), MSG_DONTROUTE);
  }
  else if (command == "USER")
  {
    setUser(client, tokens);
  }
  else if (command == "NICK")
  {
    setNick(client, tokens);
  }
  else if (command == "PRIVMSG")
  {
    sendPrivateMessage(client, tokens, message);
  }
  else if (command == "OPER")
  {
    setOper(client, tokens);
  }
  else if (command == "JOIN")
  {
    joinChannel(client, tokens);
  }
  else if (command == "MODE")
  {
    setMode(client, tokens);
  }
  else if (command == "INVITE")
  {
    setInvite(client, tokens);
  }
  else if (command == "KICK")
  {
    kick(client, tokens);
  }
  else if (command == "TOPIC")
  {
    setTopic(client, tokens);
  }
  // else if (command == "QUIT")
  // {
  //   clientQuit(client, tokens);
  // }
  else if (command == "STATUS")
  {
    printStatus(client);
  }
  else
  {
    std::string msg = R;
    msg.append("Unknown command: " + command + "\n");
    msg.append(RESET);
    send(client->getClientfd(), msg.c_str(), msg.length(), MSG_DONTROUTE);
  }
}

void Server::printStatus(Client *client)
{
  if (client == NULL)
  {
    std::string msg = "Client is null\n";
    send(client->getClientfd(), msg.c_str(), msg.length(), MSG_DONTROUTE);
    return;
  }

  std::string msg;
  msg.append("Client Status:\n");
  msg.append("Username: " + client->getUsername() + "\n");
  msg.append("First Name: " + client->getFirstName() + "\n");
  msg.append("Last Name: " + client->getLastName() + "\n");
  msg.append("Nickname: " + client->getNickname() + "\n");
  msg.append("Logged In: " + std::string(client->isLoggedIn() ? "Yes" : "No") + "\n");
  msg.append("Registered: " + std::string(client->isRegistered() ? "Yes" : "No") + "\n");
  msg.append("Operator: " + std::string(client->getOperator() ? "Yes" : "No") + "\n");

  msg.append("Channels Joined:\n");
  for (std::vector<Channel*>::const_iterator it = channelList.begin(); it != channelList.end(); ++it)
  {
    if ((*it)->isUserInChannel(client))
    {
      msg.append(" - " + (*it)->getName() + "\n");
    }
  }

  send(client->getClientfd(), msg.c_str(), msg.length(), MSG_DONTROUTE);
}

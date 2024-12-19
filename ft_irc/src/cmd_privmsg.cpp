/*
Command: PRIVMSG
   Parameters: <msgtarget> <text to be sent>

   PRIVMSG is used to send private messages between users, as well as to
   send messages to channels.  <msgtarget> is usually the nickname of
   the recipient of the message, or a channel name.
*/

#include "../inc/Server.hpp"

void Server::sendPrivateMessage(Client* senderClient, const std::vector<std::string> &tokens)
{
  if (tokens.size() < 3)
  {
    std::string msg = "\033[0;31mError: Not enough parameters for PRIVMSG command.\033[0;0m\n";
    send(senderClient->getClientfd(), msg.c_str(), msg.length(), MSG_DONTROUTE);
    return;
  }

  std::string msgTarget = tokens[1];
  std::string message;
  for (size_t i = 2; i < tokens.size(); ++i)
  {
    message += tokens[i];
    if (i != tokens.size() - 1)
    {
      message += " ";
    }
  }

  Client* targetClient = findClient(msgTarget);
  if (!targetClient)
  {
    std::string msg = R;
    msg.append("Error: No such nick/username: " + msgTarget + "\n");
    msg.append(RESET);
    send(senderClient->getClientfd(), msg.c_str(), msg.length(), MSG_DONTROUTE);
    return;
  }
  std::string fullMessage = "From ";
  fullMessage.append(Y);
  fullMessage.append(senderClient->getUsername());
  fullMessage.append(RESET);
  fullMessage.append(": ");
  fullMessage.append(message);
  fullMessage.append("\n");
  send(targetClient->getClientfd(), fullMessage.c_str(), fullMessage.length(), MSG_DONTROUTE);
  
  // Server log
  log.out("Message sent from ", G);
  log.out(senderClient->getUsername(), Y);
  log.out(" to ", G);
  log.out(targetClient->getUsername(), Y);
  log.out(": ", G);
  log.nl(message, B);
}

Client* Server::findClient(const std::string &name)
{
  for (size_t i = 0; i < clientList.size(); ++i)
  {
    if (clientList[i]->getUsername() == name || clientList[i]->getNickname() == name)
    {
      return clientList[i];
    }
  }
  return NULL;
}

/*
Command: PRIVMSG
   Parameters: <msgtarget> <text to be sent>
*/

#include "../inc/Server.hpp"

// void Server::sendPrivateMessage(const std::string &src_string)
// {
//   std::cout << "Command: Send To User\n";
//   char delimiter = ' ';
//   size_t spacePos = src_string.find(delimiter);

//   std::string target_username = src_string.substr(0, spacePos);
//   std::string message = src_string.substr(spacePos + 1);

//   for (size_t i = 0; i < clientList.size(); i++)
//   {
//     if (clientList[i]->getUsername() == target_username)
//     {
//       send(clientList[i]->getClientfd(), message.c_str(), message.length(), MSG_DONTROUTE);
//       return;
//     }
//   }
//   std::cout << "No user with username: " << target_username << " found." << std::endl;
// }

void Server::sendPrivateMessage(Client* senderClient, const std::vector<std::string> &tokens)
{
  if (tokens.size() < 3)
  {
    std::string msg = "Error: Not enough parameters for PRIVMSG command.\n";
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
    std::string msg = "Error: No such nick/username: " + msgTarget + "\n";
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

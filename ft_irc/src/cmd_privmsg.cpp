/*
Command: PRIVMSG
   Parameters: <msgtarget> <text to be sent>
*/

#include "../inc/Command.hpp"

void Server::send_to_user(const std::string &src_string)
{
  std::cout << "Command: Send To User\n";
  char delimiter = ' ';
  size_t spacePos = src_string.find(delimiter);

  std::string target_username = src_string.substr(0, spacePos);
  std::string message = src_string.substr(spacePos + 1);

  for (size_t i = 0; i < clientList.size(); i++)
  {
    if (clientList[i]->getUsername() == target_username)
    {
      send(clientList[i]->getClientfd(), message.c_str(), message.length(), MSG_DONTROUTE);
      return;
    }
  }
  std::cout << "No user with username: " << target_username << " found." << std::endl;
}
/*
Command: PASS
    Parameters: <password>
*/

#include "../inc/Server.hpp"

bool Server::checkPassword(Client *client, const std::string &enteredPassword)
{
  if (enteredPassword == _password)
  {
    return true;
  }
  else
  {
    std::string errorMsg = "Incorrect password. Please try again.\n";
    send(client->getClientfd(), errorMsg.c_str(), errorMsg.length(), MSG_DONTROUTE);
    return false;
  }
}

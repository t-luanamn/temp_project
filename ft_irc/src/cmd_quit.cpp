/*
Command: QUIT
   Parameters: [ <Quit Message> ]

   A client session is terminated with a quit message.  The server
   acknowledges this by sending an ERROR message to the client.

   Numeric Replies:

           None.

   Example:

   QUIT :Gone to have lunch        ; Preferred message format.

   :syrk!kalt@millennium.stealth.net QUIT :Gone to have lunch ;
   User syrk has quit IRC to have lunch.
*/

#include "../inc/Server.hpp"

// zsh: segmentation fault
void Server::clientQuit(Client *client, const std::vector<std::string> &tokens)
{
  std::string quitMessage = "";

  if (tokens.size() > 1 )
  {
    if (tokens[1][0] == ':')
      quitMessage = tokens[1].substr(1); // Skip the colon
    for (size_t i = 2; i < tokens.size(); ++i)
    {
      quitMessage += " " + tokens[i];
    }
  }

  // Notify all channels the client is part of
  for (std::vector<Channel*>::iterator it = channelList.begin(); it != channelList.end(); ++it)
  {
    Channel *channel = *it;
    if (channel->isUserInChannel(client))
    {
      std::string msg = ":" + client->getNickname() + "!" + client->getUsername() + "@" + _servName + " QUIT :" + quitMessage + "\n";
      const std::set<Client*>& users = channel->getUsers();
      for (std::set<Client*>::const_iterator userIt = users.begin(); userIt != users.end(); ++userIt)
      {
        if (*userIt != client)
        {
          send((*userIt)->getClientfd(), msg.c_str(), msg.length(), MSG_DONTROUTE);
        }
      }
      channel->removeUser(client);
    }
  }

  // Send ERROR message to the client
  std::string errorMsg = "ERROR :Closing Link: " + client->getUsername() + " (" + quitMessage + ")\n";
  send(client->getClientfd(), errorMsg.c_str(), errorMsg.length(), MSG_DONTROUTE);

  // Server log
  log.out(client->getUsername(), B);
  log.out(" has quit: ", G);
  log.nl(quitMessage, Y);

  // Close the client connection
  close(client->getClientfd());

  // Remove the client from the server's client list
  removeClient(client);
}

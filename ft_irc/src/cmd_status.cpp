#include "../inc/Server.hpp"

void Server::print_status() const
{
  Log log;

  log.nl("Server Status:", G);
  log.nl("----------------------------------------", G);
  log.out("Server File Descriptor: ", G);
  log.nl(_serverfd, B);
  log.nl("Connected Clients:", G);

  for (size_t i = 0; i < clientList.size(); ++i)
  {
    Client *client = clientList[i];
    if (client)
    {
      log.out("Client ID: ", G);
      log.nl(client->getClientfd(), B);
      log.out("Username: ", G);
      log.nl(client->getUsername(), B);
      log.out("Logged In: ", G);
      log.nl(client->getLoginStatus() ? "Yes" : "No", B);
    }
  }
}

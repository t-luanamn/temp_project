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

/*
void Command::execute(Client *client, const std::vector<std::string> &tokens)
{
    if (command == "PASS")
    {
        checkPassword(client, password);
    }
    else if (message.compare(0, 12, "USER") == 0)
    {
        setUsername(client, message);
    }
    else if (message.compare(0, 6, "STATUS") == 0)
    {
        printStatus(client);
    }
    else if (message.compare(0, 12, "Send To User") == 0)
    {
        sendToUser(client, message);
    }
    else if (message.compare(0, 12, "Create Group") == 0)
    {
        createGroup(client, message);
    }
    else if (message.compare(0, 14, "Login To Group") == 0)
    {
        loginToGroup(client, message);
    }
    else if (message.compare(0, 13, "Send To Group") == 0)
    {
        sendToGroup(client, message);
    }
    else if (message.compare(0, 10, "JOIN") == 0)
    {
        joinGroup(client, message);
    }
    else if (message.compare(0, 6, "INVITE") == 0)
    {
        invite(client, message);
    }
    else if (message.compare(0, 4, "KICK") == 0)
    {
        kick(client, message);
    }
    else if (message.compare(0, 5, "TOPIC") == 0)
    {
        changeTopic(client, message);
    }
    else if (message.compare(0, 4, "MODE") == 0)
    {
        setMode(client, message);
    }
    else
    {
        std::cout << "message: " << message << std::endl;
    }
}
*/

void Server::execute(Client *client, const std::vector<std::string> &tokens)
{
  if (tokens.empty())
  {
    return;
  }

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
    sendPrivateMessage(client, tokens);
  }
  // else if (command == "STATUS")
  // {
  //   printStatus(client);
  // }
  else
  {
    std::string msg = R;
    msg.append("Unknown command: " + command + "\n");
    msg.append(RESET);
    send(client->getClientfd(), msg.c_str(), msg.length(), MSG_DONTROUTE);
  }
}



// void Server::printStatus(Client *client)
// {
//   (void)client; // Mark the parameter as unused)
//   print_status();
// }

// void Server::sendToUser(Client *client, const std::string &message)
// {
//   (void)client; // Mark the parameter as unused)
//   send_to_user(message.substr(13));
// }

/*
Internet Relay Chat: Server Protocol
https://datatracker.ietf.org/doc/html/rfc2813

*/

#include "../inc/Server.hpp"

Server::Server(const std::string &name, int port, const std::string &password)
    : _servName(name), _port(port), _password(password)
{
  log.nl("Server is created", G);
  log.out("Server listening on Port: ", G);
  log.nl(_port, B);

  _serverfd = socket(AF_INET, SOCK_STREAM, 0);
  if (_serverfd <= 0)
  {
    log.err("Socket creation error");
    exit(1);
  }

  int opt = 1;
  if (setsockopt(_serverfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
  {
    log.err("Set socket option error");
    close(_serverfd);
    exit(2);
  }

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(_port);
  if (inet_pton(AF_INET, IP_ADDR, &serverAddr.sin_addr) <= 0)
  {
    log.err("Invalid address / Address not supported");
    close(_serverfd);
    exit(3);
  }

  if (bind(_serverfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
  {
    log.err("Bind error");
    close(_serverfd);
    exit(4);
  }

  if (listen(_serverfd, MAX_CLIENTS) < 0)
  {
    log.err("Listen error");
    close(_serverfd);
    exit(5);
  }
}

Server::~Server()
{
  close(_serverfd);
  for (std::vector<Client *>::iterator it = clientList.begin(); it != clientList.end(); ++it)
  {
    delete *it;
  }
  clientList.clear();
  
  for (std::vector<Channel *>::iterator it = channelList.begin(); it != channelList.end(); ++it)
  {
    delete *it;
  }
  channelList.clear();
  
  log.nl("Server is destroyed", R);
}

/*
The select() function is used to monitor the server socket and client sockets for readability.
The read(), send() function is called only when select() indicates that there is data available to read on a socket.
The code handles new connections and client messages.
Non-blocking I/O operations.
*/
void Server::start()
{
  fd_set readfds;
  while (true)
  {
    FD_ZERO(&readfds);
    FD_SET(_serverfd, &readfds);
    int maxfd = _serverfd;

    // Add client sockets to fd_set:
    for (std::vector<Client *>::iterator it = clientList.begin(); it != clientList.end(); ++it)
    {
      int sd = (*it)->getClientfd();
      FD_SET(sd, &readfds);
      if (sd > maxfd)
      {
        maxfd = sd;
      }
    }

    // select() system call to monitor multiple file descriptors -- poll() alternative
    int activity = select(maxfd + 1, &readfds, NULL, NULL, NULL);
    if (activity < 0)
    {
      std::cerr << "select error\n";
      continue;
    }

    // Check for incoming connection
    if (FD_ISSET(_serverfd, &readfds))
    {
      int clientfd = accept(_serverfd, (struct sockaddr *)NULL, NULL);
      if (clientfd < 0)
      {
        std::cerr << "accept error\n";
        continue;
      }
      Client *new_client = new Client(clientfd);
      clientList.push_back(new_client);

      // Server log
      log.out("New client connected: ", G);
      log.out("client_fd ", Y);
      log.nl(clientfd, B);

      // Send password prompt to new client
      std::string msg = B;
      msg.append("\nWelcome to " + _servName + "\n\n");
      msg.append(Y);
      msg.append("Please enter password to continue.\nPASS <serv_pass>\n");
      msg.append(RESET);
      send(clientfd, msg.c_str(), msg.length(), MSG_DONTROUTE);
    }
    handleClientMessages(readfds);
  }
}

/*
Neet to handle when client disconnects.
what to do with the client object?
send dosconnect message to all clients? / server log?
*/
void Server::handleClientMessages(fd_set &readfds)
{
  char message[1024];
  for (std::vector<Client *>::iterator it = clientList.begin(); it != clientList.end(); ++it)
  {
    int sd = (*it)->getClientfd();
    if (FD_ISSET(sd, &readfds))
    {
      int valread = read(sd, message, 1024);
      if (valread == 0)
      {
        close(sd);
        clientList.erase(it);
        break;
      }
      else
      {
        message[valread] = '\0';
        if (!(*it)->isRegistered())
        {
          checkPassword(*it, message);
        }
        else
        {
          handleMessage(*it, message);
        }
      }
    }
  }
}

void Server::handleMessage(Client *client, const std::string &message)
{
    std::istringstream iss(message);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token)
    {
        tokens.push_back(token);
    }
    execute(client, tokens);
}

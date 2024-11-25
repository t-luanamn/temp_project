#include "../inc/Server.hpp"

bool isNumber(const std::string& str)
{
  for (std::string::const_iterator i = str.begin(); i != str.end(); ++i)
  {
    if (!std::isdigit(*i))
      return false;
  }
  return true;
}

bool validateInput(int ac, char **av)
{
  Log log;

  if (ac != 3)
  {
    log.nl("Usage: ./ircserv <port> <password>", R);
    return false;
  }
  if (!isNumber(av[1]))
  {
    log.nl("Port must be a number and be between 0 and 65535", R);
    return false;
  }
  int port = atoi(av[1]);
  if (port > 65535 || port < 0)
  {
    log.nl("Port must be a number and be between 0 and 65535", R);
    return false;
  }
  return true;
}

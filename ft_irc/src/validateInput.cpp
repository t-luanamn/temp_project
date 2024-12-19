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

bool isValidChannelName(const std::string& channelName)
{
  if (channelName.empty())
    return false;

  // Check if the first character is one of '&', '#', '+', '!'
  char firstChar = channelName[0];
  if (firstChar != '&' && firstChar != '#' && firstChar != '+' && firstChar != '!')
    return false;

  // Check the length of the channel name
  if (channelName.length() > 50)
    return false;

  // Check for invalid characters
  for (std::string::const_iterator it = channelName.begin() + 1; it != channelName.end(); ++it)
  {
    char c = *it;
    if (c == ' ' || c == '\x07' || c == ',')
      return false;
  }
  return true;
}

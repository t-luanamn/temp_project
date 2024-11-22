#include "../inc/Server.hpp"

bool isNumber(const std::string& str)
{
    for (std::string::const_iterator i = str.begin(); i != str.end(); ++i)
    {
        if (!std::isdigit(*i))
          return (false);
    }
    return (true);
}

int main(int ac, char **av)
{
  Log log;

  if (ac != 3)
  {
    log.nl("Usage: ./ircserv <port> <password>", R);
    return (1);
  }
  if (!isNumber(av[1]))
  {
    log.nl("Port must be a number", R);
    return (1);
  }

  Server server = Server(atoi(av[1]), av[2]);
	server.listen();
	return (0);
}

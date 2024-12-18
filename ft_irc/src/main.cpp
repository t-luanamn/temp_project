#include "../inc/Server.hpp"

/*
Servers are uniquely identified by their name which has a maximum
   length of sixty three (63) characters.  See the protocol grammar
   rules (section 3.3.1) for what may and may not be used in a server
   name.
*/

int main(int ac, char **av)
{
    if (!validateInput(ac, av))
    {
        return 1;
    }

    Server server("My_IRC_Serv", atoi(av[1]), av[2]);
    server.start();
    return 0;
}

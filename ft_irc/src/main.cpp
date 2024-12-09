#include "../inc/Server.hpp"

int main(int ac, char **av)
{
    if (!validateInput(ac, av))
    {
        return 1;
    }

    Server server = Server(atoi(av[1]), av[2]);
    server.start();
    return 0;
}

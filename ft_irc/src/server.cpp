#include "../inc/Server.hpp"

Server::Server(int port, std::string const &password):
	_port(port),
	_password(password)
{
    Log::nl("Server is created", G);
}

Server::~Server(void)
{
    Log::nl("Server is destroyed", R);
}

void Server::listen(void)
{
    Log::out("Server is listening on port ", G);
    Log::nl(_port);
}

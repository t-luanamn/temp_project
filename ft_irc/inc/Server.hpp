#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/select.h>
# include <sys/socket.h>
# include <unistd.h>
# include <vector>
# include <string.h>
# include <memory>
# include <sstream>
# include <cctype>
# include <algorithm>

# include "Log.hpp"

class Server: public Log
{
  public:
    Server(int port, std::string const &password);
    ~Server(void);

    // Server
    void        listen(void);

  private:
    const int   _port;
    std::string _password;
    //std::string _server_name;
    //std::string _start_time;
    //int         _server_socket;

};


// Utility functions
bool isNumber(const std::string& str);
bool validateInput(int ac, char **av);


#endif

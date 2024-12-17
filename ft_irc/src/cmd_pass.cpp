/*
Command: PASS
    Parameters: <password>
*/

#include "../inc/Command.hpp"

bool Command::checkPassword(Client *client, const std::string &enteredPassword)
{
    std::string correctPassword = "your_password"; // Replace with your actual password
    if (enteredPassword == correctPassword)
    {
        return true;
    }
    else
    {
        std::string errorMsg = "Incorrect password. Please try again.\n";
        send(client->getClientfd(), errorMsg.c_str(), errorMsg.length(), MSG_DONTROUTE);
        return false;
    }
}
/*
commands that are specific to channel operators:
∗ KICK - Eject a client from the channel
∗ INVITE - Invite a client to a channel
∗ TOPIC - Change or view the channel topic
∗ MODE - Change the channel’s mode:
· i: Set/remove Invite-only channel
· t: Set/remove the restrictions of the TOPIC command to channel operators
· k: Set/remove the channel key (password)
· o: Give/take channel operator privilege
· l: Set/remove the user limit to channel
*/

#include "../inc/Command.hpp"

Command::Command(Server *server) : server(server) {}

void Command::execute(Client *client, const std::string &message)
{
    if (message.compare(0, 12, "Set Username") == 0)
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
    else if (message.compare(0, 10, "Join Group") == 0)
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

void Command::setUsername(Client *client, const std::string &message)
{
    client->setUsername(message.substr(13));
    std::cout << "Client username set to: " << client->getUsername() << std::endl;
}

void Command::printStatus(Client *client)
{
  (void)client; // Mark the parameter as unused)
  server->print_status();
}

void Command::sendToUser(Client *client, const std::string &message)
{
  (void)client; // Mark the parameter as unused)
  server->send_to_user(message.substr(13));
}

void Command::createGroup(Client *client, const std::string &message)
{
    server->create_group(client, message.substr(13));
}

void Command::loginToGroup(Client *client, const std::string &message)
{
    server->login_to_group(message.substr(15), client);
}

void Command::sendToGroup(Client *client, const std::string &message)
{
    if (server->isClientValidForGroup(client, message.substr(14)))
    {
        server->find_and_send_to_group(message.substr(14));
    }
}

void Command::joinGroup(Client *client, const std::string &message)
{
    if (server->isClientValidForGroup(client, message.substr(11)))
    {
        server->join_group(message.substr(11), client);
    }
}

void Command::invite(Client *client, const std::string &message)
{
    if (server->isClientValidForGroup(client, message.substr(7)))
    {
        server->add_to_group(message.substr(7), client);
    }
}

void Command::kick(Client *client, const std::string &message)
{
    if (server->isClientValidForGroup(client, message.substr(5)))
    {
        server->kick_from_group(message.substr(5), client);
    }
}

void Command::changeTopic(Client *client, const std::string &message)
{
    if (server->isClientValidForGroup(client, message.substr(6)))
    {
        server->change_group_topic(message.substr(6), client);
    }
}

void Command::setMode(Client *client, const std::string &message)
{
    std::string new_temp = message.substr(5);
    if (server->isClientValidForGroup(client, new_temp))
    {
        if (new_temp[0] == 'i')
        {
            new_temp = new_temp.substr(2);
            server->set_remove_invite_only(new_temp, client);
        }
        else if (new_temp[0] == 't')
        {
            new_temp = new_temp.substr(2);
            server->set_remove_topic(new_temp, client);
        }
        else if (new_temp[0] == 'k')
        {
            new_temp = new_temp.substr(2);
            server->set_channel_password(new_temp, client);
        }
        else if (new_temp[0] == 'o')
        {
            new_temp = new_temp.substr(2);
            server->remove_operator_privilege(new_temp, client);
        }
        else if (new_temp[0] == 'l')
        {
            new_temp = new_temp.substr(2);
            server->set_user_limit(new_temp, client);
        }
    }
}
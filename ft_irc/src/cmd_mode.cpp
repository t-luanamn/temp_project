/*
Command: MODE
   Parameters: <nickname>
               *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )

   The user MODE's are typically changes which affect either how the
   client is seen by others or what 'extra' messages the client is sent.

   A user MODE command MUST only be accepted if both the sender of the
   message and the nickname given as a parameter are both the same.  If
   no other parameter is given, then the server will return the current
   settings for the nick.

      The available modes are as follows:

        a - user is flagged as away;
        i - marks a users as invisible;
        w - user receives wallops;
        r - restricted user connection;
        o - operator flag;
        O - local operator flag;
        s - marks a user for receipt of server notices.
   Additional modes may be available later on.
        · i: Set/remove Invite-only channel
        · t: Set/remove the restrictions of the TOPIC command to channel operators
        · k: Set/remove the channel key (password)
        · o: Give/take channel operator privilege
        · l: Set/remove the user limit to channel
*/

#include "../inc/Command.hpp"

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

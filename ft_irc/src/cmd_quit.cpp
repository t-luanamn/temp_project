/*
Command: QUIT
   Parameters: [ <Quit Message> ]

   A client session is terminated with a quit message.  The server
   acknowledges this by sending an ERROR message to the client.

   Numeric Replies:

           None.

   Example:

   QUIT :Gone to have lunch        ; Preferred message format.

   :syrk!kalt@millennium.stealth.net QUIT :Gone to have lunch ;
   User syrk has quit IRC to have lunch.
*/

#include "../inc/Server.hpp"


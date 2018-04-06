#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <list>

using namespace std;

class User
{

public:
  ServerSocket *socket;
  string name = "0";
};

int main(int argc, char *argv[])
{

  list<User *> socketList;

  if (argc != 2)
  {
    cout << "invalid number of arguments: call with `./server port`" << endl;
    return 1;
  }

  int port = atoi(argv[1]);

  cout << "running....\n";

  try
  {
    ServerSocket server(port);
    server.set_non_blocking(true);

    while (true)
    {

      // sleep(1);

      ServerSocket *new_sock = new ServerSocket();

      try
      {
        string data;
        server.accept(*new_sock);
        new_sock->set_non_blocking(true);
        User *user = new User();
        user->socket = new_sock;
        socketList.push_back(user);
      }
      catch (SocketException &e)
      {
        delete new_sock;
      }

      try
      {
        for (User *item : socketList)
        {
          string data = "";

          try
          {
            *item->socket >> data;

            if (item->name == "0")
            {
              item->name = data;
            }
            else
            {
              for (User *sendto : socketList)
              {
                *sendto->socket << data;
              }
            }
          }
          catch (SocketException &e)
          {
          }
        }
      }
      catch (SocketException &e)
      {
      }
    }
  }
  catch (SocketException &e)
  {
    cout << "Exception was caught:" << e.description() << "\nExiting" << endl;
  }

  return 0;
}

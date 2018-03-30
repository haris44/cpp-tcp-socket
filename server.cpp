#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <list>

using namespace std;

class User
{

  ServerSocket *socket;
  string name;
};

int main(int argc, char *argv[])
{

  list<ServerSocket *> socketList;

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
        *new_sock >> data;
        User user = new User();

        socketList.push_back(new_sock);
      }
      catch (SocketException &e)
      {
        delete new_sock;
      }

      try
      {
        for (ServerSocket *item : socketList)
        {
          string data = "";
          try
          {
            *item >> data;
            for (ServerSocket *sendto : socketList)
            {
              *sendto << data;
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

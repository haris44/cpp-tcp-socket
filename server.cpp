#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <list>

using namespace std;

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

    while (true)
    {

      ServerSocket new_sock;
      server.accept(new_sock);
      socketList.push_back(&new_sock);

      printf("%s \n", "accept new connexion");

      try
      {
        while (true)
        {
          for (ServerSocket *item : socketList)
          {
            string data;
            *item >> data;
            printf("%s \n", data.c_str());
            *item << data;
          }
        }
      }
      catch (SocketException &)
      {
        printf("%s \n", "exception");
      }
    }
  }
  catch (SocketException &e)
  {
    cout << "Exception was caught:" << e.description() << "\nExiting" << endl;
  }

  return 0;
}

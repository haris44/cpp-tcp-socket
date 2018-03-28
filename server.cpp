#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int main (int argc, char* argv[]) {
  if(argc !=2) {
    cout << "invalid number of arguments: call with `./server port`" << endl;
    return 1;
  }

  int port = atoi(argv[1]);

  cout << "running....\n";

  try {
    ServerSocket server ( port );

    while ( true ) {

      ServerSocket new_sock;
      server.accept ( new_sock );

      try {
        while ( true ) {
          string data;
          new_sock >> data;
          new_sock << data;
        }
      } catch ( SocketException& ) {}

    }
  } catch ( SocketException& e ) {
    cout << "Exception was caught:" << e.description() << "\nExiting" << endl;
  }

  return 0;
}

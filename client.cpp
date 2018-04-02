#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <vector>

using namespace std;

const int num_threads = 10;

void sendTo(ClientSocket &client_socket)
{
  string message;
  try
  {
    while (true)
    {
      cout << "Send : ";
      getline(std::cin, message);
      client_socket << message;
    }
  }
  catch (SocketException &)
  {
  }
}

void listenReply(ClientSocket &client_socket)
{
  string reply;
  try
  {
    while (true)
    {
      client_socket >> reply;
      cout << "We received this response from the server:\n\"" << reply << "\"\n";
    }
  }
  catch (SocketException &)
  {
  }
}

int main(int argc, char *argv[])
{

  string host = argv[1];
  int port = atoi(argv[2]);
  if (argc != 3)
  {
    cout << "invalid number of arguments: call with `./client IP port`" << endl;
    return 1;
  }

  string name;
  vector<thread> v(thread::hardware_concurrency());

  try
  {
    cout << "name ? : ";
    getline(std::cin, name);

    ClientSocket client_socket(host, port);

    client_socket << name;

    thread t1 = thread(listenReply, ref(client_socket));
    thread t2 = thread(sendTo, ref(client_socket));

    t1.join();
    t2.join();
  }
  catch (SocketException &e)
  {
    cout << "Exception was caught:" << e.description() << endl;
  }

  return 0;
}

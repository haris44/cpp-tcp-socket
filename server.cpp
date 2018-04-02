#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <vector>
#include <queue>
#include <chrono>
#include <condition_variable>
using namespace std;

class User
{

public:
  string name = "0";
  ServerSocket *socket;

  void say(string message)
  {
    *this->socket << message;
  }

  void broadcast(vector<User *> users, int index, string message)
  {
    for (int i = 0; i < users.size(); i++)
    {
      if (i != index)
      {
        users[i]->say(message);
      }
    }
  }
};

static vector<thread> pool;
static vector<User *> users;

void clients_thread(User *user, int index)
{
  try
  {
    while (true)
    {
      string data;
      *user->socket >> data;

      if (user->name != "0")
      {
        string message;
        message = user->name + " told us : " + data + " !";
        user->broadcast(users, index, message);
        *user->socket << "Message sent !";
      }
      else
      {
        cout << data << " have joined ! " << endl;
        user->name = data;
        *user->socket << "Successfully joined !";
      }
    }
  }
  catch (SocketException &e)
  {
    cout << "Exception was caught:" << e.description() << "\nExiting" << endl;
  }
}

int main(int argc, char *argv[])
{
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
      ServerSocket *new_sock = new ServerSocket();
      server.accept(*new_sock);
      User *user = new User();
      users.push_back(user);
      user->socket = new_sock;
      pool.push_back(thread(clients_thread, user, users.size() - 1));
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
  }

  catch (SocketException &e)
  {
    cout << "Exception was caught:" << e.description() << "\nExiting" << endl;
  }

  return 0;
}

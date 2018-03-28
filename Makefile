server_objects = ServerSocket.o Socket.o server.o
client_objects = ClientSocket.o Socket.o client.o


all : server client

server: $(server_objects)
	g++ -std=c++11 -lpthread -pthread -o server $(server_objects)


client: $(client_objects)
	g++ -std=c++11 -lpthread -pthread -o client $(client_objects)


Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
ClientSocket: ClientSocket.cpp
server: server.cpp
client: client.cpp


clean:
	rm -f *.o server client
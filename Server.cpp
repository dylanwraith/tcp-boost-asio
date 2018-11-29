#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace std;

int main() {

	//Starts up server
	boost::asio::io_context io_context;

	//Create server address variable - type v4 on port 1234
	boost::asio::ip::tcp::endpoint addr(boost::asio::ip::tcp::v4(), 1234);

	//Define which ipAddress will be hosting server (local ipAddress used)
	addr.address(boost::asio::ip::address::from_string("192.168.137.91"));

	//Create socket for server
	boost::asio::ip::tcp::socket sListen(io_context);

	//Open socket and bind serverIp to socket
	sListen.open(boost::asio::ip::tcp::v4());
	sListen.bind(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234));

	//Listen for incoming connections
	boost::asio::ip::tcp::acceptor acceptor(io_context, addr);
	acceptor.listen(sListen.max_listen_connections);

	//Create socket for new connection
	boost::asio::ip::tcp::socket clientSocket(io_context);

	//Accept incoming connection
	acceptor.accept(clientSocket);
	std::cout << "Client connected!\n\n";

	//Send message to client from the server
	char messageForClient[256] = "Hello Client!";
	clientSocket.send(boost::asio::buffer(messageForClient, sizeof(messageForClient)));
	
	//Recieve message from client to the server
	char incomingMessage[256];
	clientSocket.read_some(boost::asio::buffer(incomingMessage, sizeof(incomingMessage)));
	std::cout << "Message received: " << incomingMessage << std::endl << std::endl;

    return 0;
}


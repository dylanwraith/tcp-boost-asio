#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace std;

int main() {

	//Starts up server
	boost::asio::io_context io_context;

	//Create server address variable to connect to
	boost::asio::ip::tcp::endpoint addr(boost::asio::ip::tcp::v4(), 1234);
	
	//Defines which ipAddress will be hosting server (local ipAddress)
	addr.address(boost::asio::ip::address::from_string("192.168.1.71"));

	//Create socket to connect to server
	boost::asio::ip::tcp::socket Connection(io_context);

	//Connect to the server via the new socket
	Connection.connect(addr);

	//Receive message from the server
	char incomingMessage[256];
	Connection.read_some(boost::asio::buffer(incomingMessage, sizeof(incomingMessage)));
	cout << "Message received: " << incomingMessage << std::endl << std::endl;

	//Send a message to the server
	char messageForServer[256] = "Hello Server!";
	Connection.send(boost::asio::buffer(messageForServer, sizeof(messageForServer)));

	return 0;
}

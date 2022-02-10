//
// Created by ferun on 04.02.2022.
//

#include "IRC_Connection.hpp"

void IRC_Connection::EstablishConnection(std::string server_host,
									std::string server_port) {
	(void)server_host;
	(void)server_port;
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1)
		throw SoketExeption();
}

void IRC_Connection::SendIRC_Command(std::string &command) {
	std::string message = command + "\r\n";
	send(_socket, message.data(), message.size(), 0);
}

void IRC_Connection::GetMessage(IRC_Message &message_to_fill) {

}

const char *IRC_Connection::SoketExeption::what() const throw() {
	return ("Can't create socket for IRC connection!\n");
}

const char *IRC_Connection::ConnectExeption::what() const throw() {
	return ("Can't establish connection with such host and port!\n");
}

IRC_Connection::IRC_Connection() {

}

//
// Created by ferun on 04.02.2022.
//

#include "IRC_Connection.hpp"

void IRC_Connection::EstablishConnection(const char *server_host,
									const char *server_port) {
	_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket_fd == -1)
		throw SoketExeption();
	bzero (&this->_socket_info, sizeof (this->_socket_info));
	if (inet_aton(server_host, &this->_socket_info.sin_addr) != 0)
		throw ConnectExeption();
	this->_socket_info.sin_family = AF_INET;
	this->_socket_info.sin_port = atoi(server_port);
	if(connect(_socket_fd, (struct sockaddr*)&this->_socket_info, sizeof(this->_socket_info)))
		throw ConnectExeption();
}

void IRC_Connection::SendIRC_Command(std::string &command) {
	std::string message = command + "\r\n";
	send(_socket_fd, message.data(), message.size(), 0);
}

void IRC_Connection::GetMessage(IRC_Message &message_to_fill) {
	(void)message_to_fill;
}

const char *IRC_Connection::SoketExeption::what() const throw() {
	return ("Can't create socket for IRC connection!\n");
}

const char *IRC_Connection::ConnectExeption::what() const throw() {
	return ("Can't establish connection with such host and port!\n");
}

IRC_Connection::IRC_Connection() {

}

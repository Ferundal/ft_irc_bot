//
// Created by ferun on 04.02.2022.
//

#ifndef FT_IRC_BOT_IRC_CONNECTION_HPP
#define FT_IRC_BOT_IRC_CONNECTION_HPP
#include "IRC_Message.hpp"

#include "sys/socket.h"
#include "string"

class IRC_Connection {
private:
	int			_socket;
public:
	IRC_Connection();
	void EstablishConnection(std::string server_host, std::string server_port);
	void SendIRC_Command(std::string &command);
	void GetMessage(IRC_Message &message_to_fill);
	class SoketExeption : public std::exception {
		const char * what() const throw();
	};
	class ConnectExeption : public  std::exception {
		const char * what() const throw();
	};
};


#endif //FT_IRC_BOT_IRC_CONNECTION_HPP

//
// Created by ferun on 02.02.2022.
//

#include "Bot.hpp"

Bot::Bot(const char *bot_nick, const char *bot_password,
		 IRC_Connection &connection) : _bot_nick(bot_nick), _bot_password(bot_password), _connection(connection) {}

void Bot::Login(const char *server_password) {
	std::string command;
	if (server_password != NULL) {
		command = command + "PASS " + server_password;
		_connection.SendIRC_Command(command);
		command.clear();
	}
	command = command + "NICK " + _bot_nick;
	_connection.SendIRC_Command(command);
	command.clear();
	command = command + "USER user" + _bot_nick + " * * :" + _bot_nick + "Botov";
	_connection.SendIRC_Command(command);
	_connection.GetMessage(_message);
	if (!_message._is_correct || _message._command != CODE_TO_STRING(RPL_MOTDSTART))
		throw LoginExeption();
	_connection.GetMessage(_message);
	if (!_message._is_correct || _message._command != CODE_TO_STRING(RPL_MOTD))
		throw LoginExeption();
	_connection.GetMessage(_message);
	while (!_message._is_correct || _message._command != CODE_TO_STRING(RPL_MOTD))
		_connection.GetMessage(_message);
	if (!_message._is_correct || _message._command != CODE_TO_STRING(RPL_ENDOFMOTD))
		throw LoginExeption();
}

void Bot::Start() {
	std::string command;
	_connection.GetMessage(_message);
	while (_message._is_correct) {
		if (_message._command == "PRIVMSG")

				command = command + "PRIVMSG " + _message._sender + " :";
			}
		}
		this->_connection.GetMessage(_message);
	}
	throw UnknownMessageFormat();
}

const char *Bot::LoginExeption::what() const throw() {
	return ("Can't login to the IRC server!\n");
}

const char *Bot::UnknownMessageFormat::what() const throw() {
	return ("Server send message in unknown format!\n");
}
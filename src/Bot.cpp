//
// Created by ferun on 02.02.2022.
//

#include "Bot.hpp"

Bot::Bot(const char *bot_nick, const char *bot_password, IRC_Connection &connection) :
			_bot_nick(bot_nick),
			_connection(connection),
			_user_store(bot_password) {}

void Bot::Login(const char *server_password) {
	std::string command;
	if (server_password != NULL) {
		command = command + "PASS :" + server_password;
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
	while (!_message._is_correct || _message._command == CODE_TO_STRING(RPL_MOTD))
		_connection.GetMessage(_message);
	if (!_message._is_correct || _message._command != CODE_TO_STRING(RPL_ENDOFMOTD))
		throw LoginExeption();
}

void Bot::Start() {
	std::string		command;
	_connection.GetMessage(_message);
	int				status;
	while (_message._is_correct) {
		if (_message._command == "PRIVMSG") {
			std::cout << "Input->" <<_message << std::endl;
			status = this->_user_store.AddNewUser(_message);
			if (status == ERR_WRONG_BOT_PASS) {
				command += "PRIVMSG " + _message._sender + " :Wrong bot password";
				_connection.SendIRC_Command(command);
				command.clear();
			} else {
				command += "PRIVMSG " + _message._sender + " :" +
						   _message._sender + " can invite bot to channel";
				_connection.SendIRC_Command(command);
				command.clear();
			}
		} else if (_message._command == "INVITE") {
			std::cout << "Input->" <<_message << std::endl;
			status = this->_user_store.JoinChannel(_message);
			if (status == ERR_NOT_A_BOT_USER) {
				command += "PRIVMSG " + _message._sender + " :Not a bot user";
				_connection.SendIRC_Command(command);
				command.clear();
			} else if (status == ERR_ALREADY_ON_CHANNEL) {
				command += "PRIVMSG " + _message._sender + " :Bot already on channel";
				_connection.SendIRC_Command(command);
				command.clear();
			} else {
				command += "JOIN " + _message._args[1];
				_connection.SendIRC_Command(command);
				command.clear();
			}
		} else if (_message._command == "JOIN") {
			if (this->_user_store.IsTryGiveRights(_message)) {
				std::cout << "Input->" <<_message << std::endl;
				command += "MODE " + _message._args[0] + " +o " + _message._sender;
				_connection.SendIRC_Command(command);
				command.clear();
			}
		}
		_connection.GetMessage(_message);
	}
	throw UnknownMessageFormat();
}

const char *Bot::LoginExeption::what() const throw() {
	return ("Can't login to the IRC server!\n");
}

const char *Bot::UnknownMessageFormat::what() const throw() {
	return ("Server send message in unknown format!\n");
}
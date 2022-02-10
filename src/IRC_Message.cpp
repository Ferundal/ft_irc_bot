//
// Created by ferun on 04.02.2022.
//

#include "IRC_Message.hpp"

IRC_Message::IRC_Message() : _is_correct(false) {}

void IRC_Message::Parcer(std::string message) {
	_is_correct = false;
	if (message.size() < 5 || message.size() > 510)
		return;
	size_t position_begin = message.find(':');
	if (position_begin != 0)
		return;
	++position_begin;
	size_t position_end = message.find(' ', position_begin);
	if (position_end == std::string::npos)
		return;
	_sender = std::string(message, position_begin, position_end - position_begin);
	position_begin = position_end + 1;
	position_end = message.find(' ', position_begin);
	if (position_end == std::string::npos)
		return;
	_command = std::string(message, position_begin, position_end - position_begin);
	position_begin = position_end + 1;
	position_end = message.find(' ', position_begin);
	_args.clear();
	while (position_end != std::string::npos) {
		if (message[position_begin] == ':') {
			++position_begin;
			_tail_message = std::string(message, position_begin, message.size() - position_begin);
			_is_correct = true;
			return;
		}
		_args.push_back(std::string(message, position_begin, position_end - position_begin));
		position_begin = position_end + 1;
		position_end = message.find(' ', position_begin);
	}
	_args.push_back(std::string(message, position_begin, message.size() - position_begin));
	_is_correct = true;
}
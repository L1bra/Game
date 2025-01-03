#pragma once

#include "command.h"

#include <queue>

class CommandQueue
{
private:
	std::queue<Command> m_queue;
public:
	void push(const Command& command);
	Command pop();
	bool is_empty() const;
};
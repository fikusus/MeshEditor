#pragma once
#include "Command.h"
#include "Parser.h"
#include <vector>
#include <string.h>

class Application
{
public:
	void registerCommand(std::unique_ptr<Command> command);
	int execute(int argc, char *argv[]);
private:
	std::map<std::string, std::unique_ptr<Command>> commands;
};
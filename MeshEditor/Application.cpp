#include "Application.h"
void Application::registerCommand(std::unique_ptr<Command> command) {
	commands.insert(std::pair<std::string, std::unique_ptr<Command>>(command->getName(), move(command)));
}

int  Application::execute(int argc, char *argv[]) {
	std::map<std::string, std::string> p ;
	Parser::parce(argc, argv, p);
	return commands.at(argv[1])->execute(p);
}
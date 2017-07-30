#include "CommandParser.h"
#include <vector>

TextAdventureCommand ParseAdventureCommand()
{
	TextAdventureCommand retCommand = {};
	retCommand.CommandType = CommandType_NONE;

	const unsigned int INPUT_CHAR_LIMIT = 256;
	char inputStr[INPUT_CHAR_LIMIT];

	char* pRet = fgets(inputStr, INPUT_CHAR_LIMIT, stdin);

	std::vector<std::string> tokens;
	char* next_token = nullptr;
	char *token = strtok_s(inputStr, " \t\n", &next_token);
	while (token)
	{
		tokens.push_back(token);
		token = strtok_s(nullptr, " \t\n", &next_token);
	}

	if (tokens.size() >= 1)
	{
		std::string verbString = tokens[0];

		for (unsigned int i = 0; i < verbString.size(); ++i)
		{
			verbString[i] = tolower(verbString[i]);
		}

		if (verbString == "quit")
		{
			retCommand.CommandType = CommandType_QUIT;
		}
		else if (verbString == "north" || verbString == "n")
		{
			retCommand.CommandType = CommandType_NORTH;
		}
		else if (verbString == "south" || verbString == "s")
		{
			retCommand.CommandType = CommandType_SOUTH;
		}
		else if (verbString == "west" || verbString == "w")
		{
			retCommand.CommandType = CommandType_WEST;
		}
		else if (verbString == "east" || verbString == "e")
		{
			retCommand.CommandType = CommandType_EAST;
		}
		else if (verbString == "look")
		{
			retCommand.CommandType = CommandType_LOOK;
		}
		else if (verbString == "inventory" || verbString == "inv")
		{
			retCommand.CommandType = CommandType_INVENTORY;
		}
		else if (verbString == "get")
		{
			retCommand.CommandType = CommandType_GET;
		}
		else if (verbString == "help")
		{
			retCommand.CommandType = CommandType_HELP;
		}
	}

	return retCommand;
}
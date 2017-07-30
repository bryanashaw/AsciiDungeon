#pragma once
#include <string>

enum TextAdventureCommandType
{
	CommandType_NONE,

	CommandType_NORTH,
	CommandType_SOUTH,
	CommandType_WEST,
	CommandType_EAST,

	CommandType_QUIT,
	CommandType_LOOK,
	CommandType_INVENTORY,
	CommandType_GET,
	CommandType_HELP
};

struct TextAdventureCommand
{
	TextAdventureCommandType CommandType;
	std::string Parameter;
};

TextAdventureCommand ParseAdventureCommand();
#include "GameCore.h"
#include "CommandParser.h"
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>

namespace TextGame
{
	RoomData CreateRoom(const std::string& inName, const std::string& inDescription)
	{
		RoomData room = {};
		room.Name = inName;
		room.Description = inDescription;

		return room;
	}
	ItemData CreateItem(ItemType type, int xPosition, int yPosition)
	{
		ItemData item = {};
		item.Type = type;
		item.ItemPosition.X = xPosition;
		item.ItemPosition.Y = yPosition;
		item.Quantity = 1;

		return item;
	}
	LockedDoorData CreateLockedDoor(int xPosition, int yPosition)
	{
		LockedDoorData lockedDoor = {};
		lockedDoor.DoorPosition.X = xPosition;
		lockedDoor.DoorPosition.Y = yPosition;
		
		return lockedDoor;
	}

	void InitializeGame(PlayerState& playerState, WorldState& worldState)
	{
		printf("Welcome to Bryan Shaw's\n");
		printf("ExIsle: Text Adventure Edition\n\n");

		playerState.WantsDescription = true;
		playerState.CurrentRoomIndex = 0;
		playerState.CurrentPosition.X = playerState.NewPosition.X = 3;
		playerState.CurrentPosition.Y = playerState.NewPosition.Y = 2;

		worldState.Rooms.clear();

		// 0
		{
			RoomData room = CreateRoom("Beach", "The beach is beautiful but makes you feel empty because it is devoid of life.");

			room.RoomMapWidth = 8;
			room.RoomMap = 
				"###..###"
				"#......#"
				"#......#"
				"#......#"
				"########";
			room.RoomPosition.X = 0;
			room.RoomPosition.Y = 0;

			/*LockedDoorData lockedDoor = {};
			lockedDoor.DoorPosition.X = 2;
			lockedDoor.DoorPosition.Y = 3;*/

			worldState.Rooms.push_back(room);

		}

		// 1
		{
			RoomData room = CreateRoom("Forest", "Vegetation surrounds you. Bits of light pierce through the leaves.");

			room.RoomMapWidth = 8;
			room.RoomMap =
				"###==###"
				"#%.....#"
				"....%%.."
				"#.%..%.#"
				"###..###";
			room.RoomPosition.X = 0;
			room.RoomPosition.Y = -1;

			worldState.Rooms.push_back(room);
		}

		// 2
		{
			RoomData room = CreateRoom("Haunted House", "This house is a trap!");

			room.RoomMapWidth = 8;
			room.RoomMap =
				"########"
				"#%%%%%%#"
				"#..||..."
				"#......#"
				"########";
			room.RoomPosition.X = -1;
			room.RoomPosition.Y = -1;

			ItemData key = CreateItem(ItemType_KEY, 1, 2);
			room.Inventory.push_back(key);

			LockedDoorData lockedDoor = CreateLockedDoor(7, 2);
			room.LockedDoor.push_back(lockedDoor);

			worldState.Rooms.push_back(room);
		}
		// 3
		{
			RoomData room = CreateRoom("Forest ", "Vegetation surrounds you. Bits of light pierce through the leaves.");

			room.RoomMapWidth =8;
			room.RoomMap =
				"###..###"
				"#%%%...#"
				"..%%%%.#"
				"#......#"
				"########";
			room.RoomPosition.X = 1;
			room.RoomPosition.Y = -1;

			worldState.Rooms.push_back(room);
		}
		// 4
		{
			RoomData room = CreateRoom("Forest", "Vegetation surrounds you. Bits of light pierce through the leaves.");

			room.RoomMapWidth = 8;
			room.RoomMap =
				"###..###"
				"#......#"
				"#.%%%%.#"
				"#......#"
				"###..###";
			room.RoomPosition.X = 1;
			room.RoomPosition.Y = -2;

			ItemData item = CreateItem(ItemType_BOOK, 3, 1);
			room.Inventory.push_back(item);

			worldState.Rooms.push_back(room);
		}
		// 5
		{
			RoomData room = CreateRoom("Dark Forest", "It is very dark. It is as if you are slowly being consumed by the darkness. ");

			room.RoomMapWidth = 8;
			room.RoomMap =
				"########"
				"#%....%#"
				"...||..#"
				"#%....%#"
				"###..###";
			room.RoomPosition.X = 1;
			room.RoomPosition.Y = -3;

			ItemData item = CreateItem(ItemType_BOOK, 3, 1);
			room.Inventory.push_back(item);

			ItemData item2 = CreateItem(ItemType_COIN, 4, 1);
			room.Inventory.push_back(item2);

			worldState.Rooms.push_back(room);
		}
		// 6
		{
			RoomData room = CreateRoom("Boss Entrance", "You feel great danger ahead.");

			room.RoomMapWidth = 8;
			room.RoomMap =
				"########"
				"#%.....#"
				"#%%.%%.."
				"#%....%#"
				"###..###";
			room.RoomPosition.X = 0;
			room.RoomPosition.Y = -3;

			ItemData key = CreateItem(ItemType_KEY, 4, 3);
			room.Inventory.push_back(key);

			LockedDoorData lockedDoor = CreateLockedDoor(3, 4);
			room.LockedDoor.push_back(lockedDoor);
			LockedDoorData lockedDoor2 = CreateLockedDoor(4, 4);
			room.LockedDoor.push_back(lockedDoor2);

			worldState.Rooms.push_back(room);
		}
		// 7
		{
			RoomData room = CreateRoom("Boss Room", "CONGRATULATIONS! Type quit to exit the game.");

			room.RoomMapWidth = 8;
			room.RoomMap =
				"###==###"
				"#......#"
				"#......#"
				"#......#"
				"###==###";
			room.RoomPosition.X = 0;
			room.RoomPosition.Y = -2;


			ItemData item3 = CreateItem(ItemType_SWORD, 4, 3);
			room.Inventory.push_back(item3);

			worldState.Rooms.push_back(room);
		}
	}

	void GetInput(PlayerState& playerState, const WorldState& worldState)
	{
		playerState.WantsToExit = false;
		playerState.WantsDescription = false;
		playerState.WantsInventoryListed = false;
		playerState.WantsToGet = false;
		
		printf("What do you do?\n");
		printf("> ");
		TextAdventureCommand command = ParseAdventureCommand();

		if (command.CommandType == CommandType_QUIT)
		{
			playerState.WantsToExit = true;
		}
		else if (command.CommandType == CommandType_NORTH)
		{
			playerState.NewPosition.Y = playerState.CurrentPosition.Y - 1;
		}
		else if (command.CommandType == CommandType_SOUTH)
		{
			playerState.NewPosition.Y = playerState.CurrentPosition.Y + 1;
		}
		else if (command.CommandType == CommandType_WEST)
		{
			playerState.NewPosition.X = playerState.CurrentPosition.X - 1;
		}
		else if (command.CommandType == CommandType_EAST)
		{
			playerState.NewPosition.X = playerState.CurrentPosition.X + 1;
		}
		else if (command.CommandType == CommandType_LOOK)
		{
			playerState.WantsDescription = true;
		}
		else if (command.CommandType == CommandType_INVENTORY)
		{
			playerState.WantsInventoryListed = true;
		}
		else if (command.CommandType == CommandType_GET)
		{
			playerState.WantsToGet = true;
			
		}
		else if (command.CommandType == CommandType_HELP)
		{
			printf("Command List: look, quit, inventory, get, north, south, west, east\n");
			printf("Key:\n");
			printf("  @ - Player\n");
			printf("  A - Altar (Next Patch!)\n");
			printf("  B, C, S, K - Item\n");
			printf("  . - Floor\n");
			printf("  #, &, |, = - Wall\n");
			printf("  L - Door (Locked)\n");
		}

		if(command.CommandType == CommandType_NONE)
		{
			printf("I don't understand\n");
		}
		printf("\n");

	}

	void RenderGame(const PlayerState& playerState, const WorldState& worldState)
	{
		if (playerState.WantsDescription)
		{
			const RoomData& currRoom = worldState.Rooms[playerState.CurrentRoomIndex];
			printf("================================================\n");
			printf("LOCATION: %s\n", currRoom.Name.c_str());
			printf("%s\n\n", currRoom.Description.c_str());
		
			std::string mapString = "";
			unsigned int currentSpace = 0;
			while (currentSpace < currRoom.RoomMap.size())
			{
				char characterToDisplay = currRoom.RoomMap[currentSpace];

				//Inventory Rendering Code
				for (unsigned int i = 0; i < currRoom.Inventory.size(); i++)
				{
					const ItemData& currItem = currRoom.Inventory[i];
					if (currentSpace == PositionToIndex(currItem.ItemPosition, currRoom.RoomMapWidth))
					{
						characterToDisplay = GetItemIcon(currItem.Type);
					}
				}

				//Locked Door Rendering Code
				for (unsigned int i = 0; i < currRoom.LockedDoor.size(); i++)
				{
					const LockedDoorData& currDoor = currRoom.LockedDoor[i];
					if (currentSpace == PositionToIndex(currDoor.DoorPosition, currRoom.RoomMapWidth))
					{
						characterToDisplay = 'L';
					}
				}


				if (currentSpace == PositionToIndex(playerState.CurrentPosition, currRoom.RoomMapWidth))
				{
					characterToDisplay = '@';
				}

				mapString += characterToDisplay;
				
				if(currentSpace % currRoom.RoomMapWidth == (currRoom.RoomMapWidth - 1))
				{
					mapString += '\n';
				}

				currentSpace++;
			}
			printf("%s\n", mapString.c_str());

			printf("\n");
		}
		else if (playerState.WantsInventoryListed)
		{
			printf("================================================\n");
			printf("INVENTORY:\n");

			if (playerState.Inventory.size() == 0)
			{
				printf("You have nothing...\n");
			}
			else
			{
				for (unsigned int i = 0; i < playerState.Inventory.size(); i++)
				{
					const ItemData& currItem = playerState.Inventory[i];
					printf("%s (x%d)\n", GetItemName(currItem.Type).c_str(), currItem.Quantity);
				}
			}



			printf("\n");
		}
	}

	void UpdateGame(PlayerState& playerState, WorldState& worldState)
	{
		RoomData& currRoom = worldState.Rooms[playerState.CurrentRoomIndex];

		if (playerState.NewPosition != playerState.CurrentPosition)
		{

			TryToUnlockDoors(playerState, currRoom);

			if (IsSpaceOutsideMap(playerState.NewPosition, currRoom))
			{
				int newRoomIndex = 0;

				int playerExitType = 0;
				Position targetRoomPosition = currRoom.RoomPosition;
				if (playerState.NewPosition.X < 0)
				{
					//Exited West
					targetRoomPosition.X--;
					playerExitType = 1;
				}
				else if(playerState.NewPosition.X >= (int)currRoom.RoomMapWidth)
				{
					//Exited East
					targetRoomPosition.X++;
					playerExitType = 2;
				}
				else if (playerState.NewPosition.Y < 0)
				{
					//Exited North
					targetRoomPosition.Y--;
					playerExitType = 3;
				}
				else if (playerState.NewPosition.Y >= (int)(currRoom.RoomMap.size() / currRoom.RoomMapWidth))
				{
					//Exited South
					targetRoomPosition.Y++;
					playerExitType = 4;
				}

				bool foundNewRoom = false;
				for (unsigned int i = 0; i < worldState.Rooms.size(); ++i)
				{
					if (worldState.Rooms[i].RoomPosition == targetRoomPosition)
					{
						foundNewRoom = true;
						newRoomIndex = i;
						break;
					}
				}

				if (foundNewRoom)
				{
					playerState.CurrentRoomIndex = newRoomIndex;
					playerState.WantsDescription = true;

					switch (playerExitType)
					{
					case 1:
						playerState.CurrentPosition.X = worldState.Rooms[playerState.CurrentRoomIndex].RoomMapWidth - 1;
						break;
					case 2:
						playerState.CurrentPosition.X = 0;
						break;
					case 3:
						playerState.CurrentPosition.Y = (worldState.Rooms[playerState.CurrentRoomIndex].RoomMap.size() / worldState.Rooms[playerState.CurrentRoomIndex].RoomMapWidth) - 1;
						break;
					case 4:
						playerState.CurrentPosition.Y = 0;
						break;
					default:
						break;
					}
				}
				else
				{
					printf("There is nothing out there for you...\n");
					playerState.NewPosition = playerState.CurrentPosition;
				}
			}
			else if (IsSpaceOpenForMovement(playerState.NewPosition, currRoom))
			{
				playerState.CurrentPosition = playerState.NewPosition;
				playerState.WantsDescription = true;
			}
			else
			{
				printf("The path is blocked! Curses!\n");
				playerState.NewPosition = playerState.CurrentPosition;
			}
		}
		if (playerState.WantsToGet)
		{
			for (unsigned int i = 0; i < currRoom.Inventory.size(); i++)
			{ 
				const ItemData& currItem = currRoom.Inventory[i];
				if (currItem.ItemPosition == playerState.CurrentPosition)
				{
					printf("You got %s\n", GetItemName(currItem.Type).c_str());

					bool foundItemInPlayerInventory = false;
					for (unsigned int z = 0; z < playerState.Inventory.size(); z++)
					{
						ItemData& currPlayerItem = playerState.Inventory[z];
						if (currPlayerItem.Type == currItem.Type)
						{
							currPlayerItem.Quantity += currItem.Quantity;
							foundItemInPlayerInventory = true;
						}
					}

					if (!foundItemInPlayerInventory)
					{
						playerState.Inventory.push_back(currItem);
					}

					currRoom.Inventory.erase(currRoom.Inventory.begin() + i);
					break;
				}

			}
		}
	}

	void CleanupGame(PlayerState& playerState, WorldState& worldState)
	{
		worldState.Rooms.clear();
	}
	void TryToUnlockDoors(PlayerState&playerState, RoomData& currRoom)
	{
		for (unsigned int i = 0; i < currRoom.LockedDoor.size(); i++)
		{
			const LockedDoorData& currDoor = currRoom.LockedDoor[i];
			if (currDoor.DoorPosition == playerState.NewPosition)
			{
				for (unsigned int j = 0; j < playerState.Inventory.size(); j++)
				{
					ItemData& currItem = playerState.Inventory[j];
					if (currItem.Type == ItemType_KEY)
					{
						//Destroy the door
						currRoom.LockedDoor.erase(currRoom.LockedDoor.begin() + i);

						//Remove a key
						currItem.Quantity--;
						if (currItem.Quantity <= 0)
						{
							playerState.Inventory.erase(playerState.Inventory.begin() + j);
						}

						break;
					}
				}
			}
		}
	}


	int PositionToIndex(const Position& position, int roomWidth)
	{
		return position.Y * roomWidth + position.X;
	}

	bool IsSpaceOutsideMap(const Position& position, const RoomData& currRoom)
	{
		return position.Y < 0 ||
			position.X < 0 ||
			position.X >= (int)currRoom.RoomMapWidth ||
			position.Y >= (int)(currRoom.RoomMap.size() / currRoom.RoomMapWidth);
	}

	bool IsSpaceOpenForMovement(const Position& position, const RoomData& currRoom)
	{
		for (unsigned int i = 0; i < currRoom.LockedDoor.size(); i++)
		{
			const LockedDoorData& currDoor = currRoom.LockedDoor[i];
			if (position == currDoor.DoorPosition)
			{
				return false;
			}
		}
		int spaceIndex = PositionToIndex(position, currRoom.RoomMapWidth);
		char currentSpace = currRoom.RoomMap[spaceIndex];

		/*
		if(currentSpace == '.')
		{
			return true;
		}
		else
		{
			return false;
		}
		*/
		return currentSpace == '.';
	}
	char GetItemIcon(ItemType itemType)
	{
		switch (itemType)
		{
		case TextGame::ItemType_BOOK:
			return 'B';
			break;
		case TextGame::ItemType_COIN:
			return 'C';
			break;
		case TextGame::ItemType_SWORD:
			return 'S';
			break;
		case TextGame::ItemType_KEY:
			return 'K';
			break;
		default:
			break;
		}
		return 'i';
	}
	std::string GetItemName(ItemType itemType)
	{
		switch (itemType)
		{
		case TextGame::ItemType_BOOK:
			return "The Book of Loss";
			break;
		case TextGame::ItemType_COIN:
			return "Coin of Wealth";
			break;
		case TextGame::ItemType_SWORD:
			return "Sword of Slayers";
			break;
		case TextGame::ItemType_KEY:
			return "The Boss Key";
			break;
		default:
			break;
		}

		return "Unknown Item";
	}

}

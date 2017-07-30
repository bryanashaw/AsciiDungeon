#pragma once
#include <string>
#include <vector>

namespace TextGame
{
	struct Position
	{
		int X;
		int Y;

		bool operator==(const Position& otherPosition) const
		{
			return X == otherPosition.X && Y == otherPosition.Y;
		}

		bool operator!=(const Position& otherPosition) const
		{
			return !(*this == otherPosition);
		}
	};

	enum ItemType
	{
		ItemType_BOOK,
		ItemType_COIN,
		ItemType_SWORD,
		ItemType_KEY
	};

	struct ItemData
	{
		ItemType Type;
		Position ItemPosition;
		int Quantity;
		char Icon;
		std::string Name;
	};
	struct LockedDoorData
	{
		Position DoorPosition;
	};

	struct PlayerState
	{
		bool WantsToExit;
		bool WantsDescription;
		bool WantsInventoryListed;
		bool WantsToGet;
		
		int CurrentRoomIndex;

		Position CurrentPosition;
		Position NewPosition;

		std::vector<ItemData> Inventory;
	};

	struct RoomData
	{
		std::string Name;
		std::string Description;

		std::string RoomMap;
		unsigned int RoomMapWidth;

		Position RoomPosition;

		std::vector<ItemData> Inventory;
		std::vector<LockedDoorData> LockedDoor;
	};

	struct WorldState
	{
		std::vector<RoomData> Rooms;
	};

	void InitializeGame(PlayerState& playerState, WorldState& worldState);
	void GetInput(PlayerState& playerState, const WorldState& worldState);
	void RenderGame(const PlayerState& playerState, const WorldState& worldState);
	void UpdateGame(PlayerState& playerState, WorldState& worldState);
	void CleanupGame(PlayerState& playerState, WorldState& worldState);
	void TryToUnlockDoors(PlayerState&playerState, RoomData& currRoom);

	int PositionToIndex(const Position& position, int roomWidth);
	bool IsSpaceOutsideMap(const Position& position, const RoomData& currRoom);
	bool IsSpaceOpenForMovement(const Position& position, const RoomData& currRoom);
	char GetItemIcon(ItemType itemType);
	std::string GetItemName(ItemType itemType);

}
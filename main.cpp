#include <stdio.h>
#include "GameCore.h"

using namespace TextGame;

int main(int argc, char* argv[])
{
	PlayerState playerState = {};
	WorldState worldState = {};

	InitializeGame(playerState, worldState);

	while (!playerState.WantsToExit)
	{
		RenderGame(playerState, worldState);
		GetInput(playerState, worldState);
		UpdateGame(playerState, worldState);
	}

	CleanupGame(playerState, worldState);

	return 0;
}
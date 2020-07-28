# cock_iterate
Fast iterators for SA-MP

## Usage
Example script:
```pawn
#include <a_samp>
#include <cock_iterate>
new Iterator:Player<MAX_PLAYERS>;

public OnGameModeInit()
{
	Iter_Init(Player);
	
	new index = Iter_Free(Player);
	printf("Current index at Player Iterator: %d", index);
	return 1;
}

public OnPlayerConnect(playerid)
{
	Iter_Add(Player, playerid);
	
	foreach(player : Player)
	{
		printf("Iterator passed by playerid %d", player);
	}
	
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	Iter_Remove(Player, playerid);
	return 1;
}

public OnGameModeExit()
{
	Iter_Clear(Player);
	return 1;
}
```

## Installation
Place `cock_iterate.inc` in your `pawno/include` folder and include in your script.
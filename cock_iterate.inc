#if defined _cock_iterate
	#endinput
#endif
#define _cock_iterate

#define Iterator:%0<%1>		_cockIterator_%0[%1]
#define foreach(%0:%1)	for(new %0 = 0; %0 < sizeof(_cockIterator_%0); %0++)

#if !defined _cockIterator_Player
	new Iterator:Player<MAX_PLAYERS>;
#endif

#define Iter_Free(%0) Iter_Free(_cockIterator_%0)
stock Iter_Free(iter)
{
	for(new i = 0; i < sizeof(iter); i++)
	{
		if(iter[i] == 0 || iter[i] == '\0') return i;
	}

	return -1;
}

#define Iter_Add(%0, %1) Iter_Add(_cockIterator_%0, %1)

stock Iter_Add(iter, value)
{
	new index = Iter_Free(iter);
	if(index == -1)
	{
		// retarded shit with emit, just to reference my friend ysi. . . 
		static const err[] = "lol wtf increase your iterators";

		#emit push.c err
		#emit push.c 1
		#emit sysreq.c print
		#emit stack 12
		#emit retn

		return 0;
	}

	iter[index] = value;
	return 1;
}

#define Iter_Remove(%0, %1) Iter_Remove(_cockIterator_%0, %1)
#define Iter_RemoveSafe Iter_Remove
stock Iter_Remove(iter, value)
{
	new index = -1;
	for(new i = 0; i < sizeof(iter); i++)
	{
		if(iter[i] == value) index = i;
	}
	if(index == -1) return 0;

	iter[i] == '\0';
	return 1;
}

#define Iter_Init(%0) Iter_Init(_cockIterator_%0)
stock Iter_Init(iter)
{
	for(new uniqueIterLoop = 0; uniqueIterLoop < sizeof(iter); uniqueIterLoop++)
	{
		iter[uniqueIterLoop] = '\0';
	}

	return 1;
}

#define Iter_Clear(%0) Iter_Init(_cockIterator_%0)

public OnGameModeInit()
{
	Iter_Init(Player);

	#if defined CIter_OnGameModeInit
		return CIter_OnGameModeInit();
	#else
		return 1;
	#endif
}

public OnPlayerConnect(playerid)
{
	Iter_Add(Player, playerid);

	#if defined CIter_OnPlayerConnect
		return CIter_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

public OnPlayerDisconnect(playerid, reason)
{
	Iter_Remove(Player, playerid);

	#if defined CIter_OnPlayerDisconnect
		return CIter_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}

public OnGameModeExit()
{
	Iter_Clear(Player);

	#if defined CIter_OnGameModeExit
		return CIter_OnGameModeExit();
	#else
		return 1;
	#endif
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit CIter_OnGameModeInit
#if defined CIter_OnGameModeInit
	forward CIter_OnGameModeInit();
#endif

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect CIter_OnPlayerConnect
#if defined CIter_OnPlayerConnect
	forward CIter_OnPlayerConnect(playerid);
#endif

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect CIter_OnPlayerDisconnect
#if defined CIter_OnPlayerDisconnect
	forward CIter_OnPlayerDisconnect(playerid, reason);
#endif

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit CIter_OnGameModeExit
#if defined CIter_OnGameModeExit
	forward CIter_OnGameModeExit();
#endif
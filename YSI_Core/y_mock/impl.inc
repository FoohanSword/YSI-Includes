#define CRASH_VALUE cellmax

#define MAX_WEAPONS 13

enum E_MOCK_PLAYER
{
	bool:E_CONNECTED,
	E_USERNAME[MAX_PLAYER_NAME + 1],
	Float:E_POS[3],
	E_VIRTUAL_WORLD,
	E_INTERIOR,
	E_SKIN,
	E_SPECIAL_ACTION,
	E_SCORE,
	E_MONEY,
	E_STATE,
	E_VEHICLE_ID,
	E_SPECTATING_PLAYER,

	E_CURRENT_WEAPON,
	E_AMMO[MAX_WEAPONS],
	E_WEAPON[MAX_WEAPONS],
	E_WEAPON_STATE[MAX_WEAPONS],
	E_ANIMATION_INDEX,
	Float:E_ARMOUR,
	Float:E_CAMERA_ASPECT_RATIO,
	Float:E_CAMERA_FRONT_VECTOR[3],
	E_CAMERA_MODE,
	Float:E_CAMERA_POS[3],
	Float:E_CAMERA_UP_VECTOR[3],
	Float:E_CAMERA_ZOOM,
	E_COLOR,
	Float:E_DISTANCE_FROM_POINT,
	E_DRUNK_LEVEL,
	Float:E_FACING_ANGLE,
	Float:E_FIGHTING_STYLE,
	Float:E_HEALTH,
	E_KEYS,
	Float:E_LAST_SHOT_VECTORS[6],
	E_MENU,
	E_NETWORK_STATS,
	Float:E_OBJECT_POS[3],
	Float:E_OBJECT_ROT,
	E_SURFING_OBJECT_ID,
	E_SURFING_VEHICLE_ID,
	E_TEAM,
	E_TIME,
	E_VEHICLE_SEAT,
	Float:E_VELOCITY[3],
	E_WANTED_LEVEL,
	E_RCON_ADMIN,
	E_PLAYER_STATE
}

static 
	MockPlayer[MAX_PLAYERS][E_MOCK_PLAYER]
;

stock Y_MOCK_IsPlayerConnected(playerid)
{
	return MockPlayer[playerid][E_CONNECTED];
}

#if defined _ALS_IsPlayerConnected
	#undef IsPlayerConnected
#else
	#define _ALS_IsPlayerConnected
#endif

#define IsPlayerConnected Y_MOCK_IsPlayerConnected

stock Y_MOCK_SetPlayerName(playerid, const name[])
{
	if (!IsPlayerConnected(playerid)) {
		return 0;
	}

	if (isnull(name)) {
		return CRASH_VALUE;
	}

	if (!isnull(MockPlayer[playerid][E_USERNAME]) && !strcmp(MockPlayer[playerid][E_USERNAME], name)) {
		return 0;
	}

	if (strlen(name) > MAX_PLAYER_NAME) {
		return -1;
	}

	// Regex would be easier
	for (new i = 0; i != MAX_PLAYER_NAME + 1; ++i) {
		if (!
			('a' < name[i] < 'Z'
			|| '0' < name[i] < '9'
			|| name[i] != '['
			|| name[i] != ']'
			|| name[i] != '('
			|| name[i] != ')'
			|| name[i] != '$'
			|| name[i] != '@'
			|| name[i] != '['
			|| name[i] != '.'
			|| name[i] != '_'
			|| name[i] != '='
			)
		) {
			return -1;
		}
	}

	strcpy(MockPlayer[playerid][E_USERNAME], name);

	return 1;
}

#if defined _ALS_SetPlayerName
	#undef SetPlayerName
#else
	#define _ALS_SetPlayerName
#endif
#define SetPlayerName Y_MOCK_SetPlayerName

stock Y_MOCK_GetPlayerName(playerid, name[], len = sizeof name)
{
	if (!IsPlayerConnected(playerid)) return 0;

	strcpy(name, MockPlayer[playerid][E_USERNAME], len);

	return 1;
}

#if defined _ALS_GetPlayerName
	#undef GetPlayerName
#else
	#define _ALS_GetPlayerName
#endif
#define GetPlayerName Y_MOCK_GetPlayerName

stock Y_MOCK_SetPlayerPos(playerid, Float:x, Float:y, Float:z)
{
	if (!IsPlayerConnected(playerid)) return 0;

	new playerState = GetPlayerState(playerid);
	if (playerState == PLAYER_STATE_DRIVER || playerState == PLAYER_STATE_PASSENGER) {
		RemovePlayerFromVehicle(playerid);
	}

	MockPlayer[playerid][E_POS][0] = x;
	MockPlayer[playerid][E_POS][1] = y;
	MockPlayer[playerid][E_POS][2] = z;

	return 1;
}

#if defined _ALS_SetPlayerPos
	#undef SetPlayerPos
#else
	#define _ALS_SetPlayerPos
#endif
#define SetPlayerPos Y_MOCK_SetPlayerPos


stock Y_MOCK_GetPlayerPos(playerid, &Float:x, &Float:y, &Float:z)
{
	if (!IsPlayerConnected(playerid)) return 0;

	x = MockPlayer[playerid][E_POS][0];
	y = MockPlayer[playerid][E_POS][1];
	z = MockPlayer[playerid][E_POS][2];

	return 1;
}

#if defined _ALS_GetPlayerPos
	#undef GetPlayerPos
#else
	#define _ALS_GetPlayerPos
#endif
#define GetPlayerPos Y_MOCK_GetPlayerPos

stock Y_MOCK_GetPlayerVirtualWorld()
{
	return MockPlayer[playerid][E_VIRTUAL_WORLD];
}

#if defined _ALS_GetPlayerVirtualWorld
	#undef GetPlayerVirtualWorld
#else
	#define _ALS_GetPlayerVirtualWorld
#endif
#define GetPlayerVirtualWorld Y_MOCK_GetPlayerVirtualWorld

stock Y_MOCK_SetPlayerVirtualWorld(playerid, worldid)
{
	if (!IsPlayerConnected(playerid)) return 0;

	MockPlayer[playerid][E_VIRTUAL_WORLD] = worldid;

	return 1;
}

#if defined _ALS_SetPlayerVirtualWorld
	#undef SetPlayerVirtualWorld
#else
	#define _ALS_SetPlayerVirtualWorld
#endif
#define SetPlayerVirtualWorld Y_MOCK_SetPlayerVirtualWorld

stock Y_MOCK_GetPlayerInterior(playerid)
{
	return MockPlayer[playerid][E_INTERIOR];
}

#if defined _ALS_GetPlayerInterior
	#undef GetPlayerInterior
#else
	#define _ALS_GetPlayerInterior
#endif
#define GetPlayerInterior Y_MOCK_GetPlayerInterior

stock Y_MOCK_SetPlayerInterior(playerid, interiorid)
{
	if (!IsPlayerConnected(playerid)) return 0;

	MockPlayer[playerid][E_INTERIOR] = interiorid;

	return 1;
}

stock Y_MOCK_GetPlayerSkin()
{
	return MockPlayer[playerid][E_SKIN];
}

#if defined _ALS_GetPlayerSkin
	#undef GetPlayerSkin
#else
	#define _ALS_GetPlayerSkin
#endif
#define GetPlayerSkin Y_MOCK_GetPlayerSkin

stock Y_MOCK_SetPlayerSkin(playerid, skinid)
{
	if (!IsPlayerConnected(playerid)) return 0;

	if (0 < skinid <= 311 && skinid != 74) {
		MockPlayer[playerid][E_SKIN] = skinid;
	} else {
		MockPlayer[playerid][E_SKIN] = 0;
	}

	return 1;
}

#if defined _ALS_SetPlayerSkin
	#undef SetPlayerSkin
#else
	#define _ALS_SetPlayerSkin
#endif
#define SetPlayerSkin Y_MOCK_SetPlayerSkin

stock Y_MOCK_GetPlayerSpecialAction()
{
	return MockPlayer[playerid][E_SPECIAL_ACTION];
}

#if defined _ALS_GetPlayerSpecialAction
	#undef GetPlayerSpecialAction
#else
	#define _ALS_GetPlayerSpecialAction
#endif
#define GetPlayerSpecialAction Y_MOCK_GetPlayerSpecialAction

stock Y_MOCK_SetPlayerSpecialAction(playerid, actionid)
{
	if (!IsPlayerConnected(playerid)) return 0;

	if (0 < actionid <= 8 || 10 <= actionid <= 13 || 20 <= actionid <= 25) {
		MockPlayer[playerid][E_SPECIAL_ACTION] = actionid;
	} else {
		MockPlayer[playerid][E_SPECIAL_ACTION] = 0;
	}

	return 1;
}

#if defined _ALS_SetPlayerSpecialAction
	#undef SetPlayerSpecialAction
#else
	#define _ALS_SetPlayerSpecialAction
#endif
#define SetPlayerSpecialAction Y_MOCK_SetPlayerSpecialAction

stock Y_MOCK_GetPlayerScore()
{
	return MockPlayer[playerid][E_SCORE];
}

#if defined _ALS_GetPlayerScore
	#undef GetPlayerScore
#else
	#define _ALS_GetPlayerScore
#endif
#define GetPlayerScore Y_MOCK_GetPlayerScore

stock Y_MOCK_SetPlayerScore(playerid, score)
{
	if (!IsPlayerConnected(playerid)) return 0;

	MockPlayer[playerid][E_SCORE] = score;

	return 1;
}

#if defined _ALS_SetPlayerScore
	#undef SetPlayerScore
#else
	#define _ALS_SetPlayerScore
#endif
#define SetPlayerScore Y_MOCK_SetPlayerScore

stock Y_MOCK_GetPlayerMoney(playerid)
{
	return MockPlayer[playerid][E_MONEY];
}

#if defined _ALS_GetPlayerMoney
	#undef GetPlayerMoney
#else
	#define _ALS_GetPlayerMoney
#endif
#define GetPlayerMoney Y_MOCK_GetPlayerMoney

stock Y_MOCK_GivePlayerMoney(playerid, money)
{
	if (!IsPlayerConnected(playerid)) return 0;

	MockPlayer[playerid][E_MONEY] += money;

	return 1;
}

#if defined _ALS_GivePlayerMoney
	#undef GivePlayerMoney
#else
	#define _ALS_GivePlayerMoney
#endif
#define GivePlayerMoney Y_MOCK_GivePlayerMoney

stock Y_MOCK_GetPlayerState()
{
	return MockPlayer[playerid][E_STATE];
}

#if defined _ALS_GetPlayerState
	#undef GetPlayerState
#else
	#define _ALS_GetPlayerState
#endif
#define GetPlayerState Y_MOCK_GetPlayerState

stock Y_MOCK_SetPlayerState(playerid, stateid)
{
	if (!IsPlayerConnected(playerid)) return 0;

	if (0 < stateid <= 9) {
		MockPlayer[playerid][E_STATE] = stateid;
	}

	return 1;
}

#if defined _ALS_SetPlayerState
	#undef SetPlayerState
#else
	#define _ALS_SetPlayerState
#endif
#define SetPlayerState Y_MOCK_SetPlayerState

stock Y_MOCK_GetPlayerIp(playerid, dest[], len = sizeof dest)
{
	strcpy(dest, MockPlayer[playerid][E_IP], len);

	return 1;
}

#if defined _ALS_GetPlayerIp
	#undef GetPlayerIp
#else
	#define _ALS_GetPlayerIp
#endif
#define GetPlayerIp Y_MOCK_GetPlayerIp

stock Y_MOCK_SetPlayerIp(playerid, const ip[])
{
	if (!IsPlayerConnected(playerid)) return 0;

	strcpy(MockPlayer[playerid][E_IP], ip);

	return 1;
}

stock Y_MOCK_GetPlayerPing(playerid)
{
	return MockPlayer[playerid][E_PING];
}

#if defined _ALS_GetPlayerPing
	#undef GetPlayerPing
#else
	#define _ALS_GetPlayerPing
#endif
#define GetPlayerPing Y_MOCK_GetPlayerPing

stock Y_MOCK_SetPlayerPing(playerid, ping)
{
	if (!IsPlayerConnected(playerid)) return 0;

	MockPlayer[playerid][E_PING] = ping;

	return 1;
}

#if defined _ALS_SetPlayerPing
	#undef SetPlayerPing
#else
	#define _ALS_SetPlayerPing
#endif
#define SetPlayerPing Y_MOCK_SetPlayerPing

stock Y_MOCK_GetPlayerVersion(playerid, version[], len = sizeof version)
{
	strcpy(version, MockPlayer[playerid][E_VERSION], len);

	return 1;
}

#if defined _ALS_GetPlayerVersion
	#undef GetPlayerVersion
#else
	#define _ALS_GetPlayerVersion
#endif
#define GetPlayerVersion Y_MOCK_GetPlayerVersion

stock Y_MOCK_SetPlayerVersion(playerid, const version[])
{
	if (!IsPlayerConnected(playerid)) return 0;

	strcpy(MockPlayer[playerid][E_VERSION], version);

	return 1;
}

#if defined _ALS_SetPlayerVersion
	#undef SetPlayerVersion
#else
	#define _ALS_SetPlayerVersion
#endif
#define SetPlayerVersion Y_MOCK_SetPlayerVersion

stock Y_MOCK_GetPlayerAmmo(playerid)
{
	return MockPlayer[playerid][E_AMMO][MockPlayer[playerid][E_CURRENT_WEAPON]];
}

#if defined _ALS_GetPlayerAmmo
	#undef GetPlayerAmmo
#else
	#define _ALS_GetPlayerAmmo
#endif
#define GetPlayerAmmo Y_MOCK_GetPlayerAmmo

stock Y_MOCK_SetPlayerAmmo(playerid, weaponid, ammo)
{
	if (!IsPlayerConnected(playerid)) return 0;

	if (1 < weaponid <= 43 || weaponid == 46 || weaponid == 49 || 53 <= weaponid <= 54) {
		for (new i = 0; i != MAX_WEAPONS; ++i) {
			if (MockPlayer[playerid][E_WEAPON][i] == weaponid) {
				MockPlayer[playerid][E_WEAPON][i] = ammo;
			}
		}
	}

	return 1;
}

#if defined _ALS_SetPlayerAmmo
	#undef SetPlayerAmmo
#else
	#define _ALS_SetPlayerAmmo
#endif
#define SetPlayerAmmo Y_MOCK_SetPlayerAmmo

stock Y_MOCK_GetPlayerArmour(playerid, &Float:armour)
{
	armour = floatround(MockPlayer[playerid][E_ARMOUR]);

	return 1;
}

#if defined _ALS_GetPlayerArmour
	#undef GetPlayerArmour
#else
	#define _ALS_GetPlayerArmour
#endif
#define GetPlayerArmour Y_MOCK_GetPlayerArmour

stock Y_MOCK_SetPlayerArmour(playerid, Float:armour)
{
	if (!IsPlayerConnected(playerid)) return 0;

	return floatround(MockPlayer[playerid][E_ARMOUR]);
}

#if defined _ALS_SetPlayerArmour
	#undef SetPlayerArmour
#else
	#define _ALS_SetPlayerArmour
#endif
#define SetPlayerArmour Y_MOCK_SetPlayerArmour

stock Y_MOCK_GetPlayerColor(playerid)
{
	return MockPlayer[playerid][E_COLOR];
}

#if defined _ALS_GetPlayerColor
	#undef GetPlayerColor
#else
	#define _ALS_GetPlayerColor
#endif
#define GetPlayerColor Y_MOCK_GetPlayerColor

stock Y_MOCK_SetPlayerColor(playerid, color)
{
	if (!IsPlayerConnected(playerid)) return 0;

	MockPlayer[playerid][E_COLOR] = color;

	return 1;
}

#if defined _ALS_SetPlayerColor
	#undef SetPlayerColor
#else
	#define _ALS_SetPlayerColor
#endif
#define SetPlayerColor Y_MOCK_SetPlayerColor

stock Y_MOCK_GetPlayerVehicleID(playerid, vehicleid)
{
	return MockPlayer[playerid][E_VEHICLE_ID];
}

#if defined _ALS_GetPlayerVehicleID
	#undef GetPlayerVehicleID
#else
	#define _ALS_GetPlayerVehicleID
#endif
#define GetPlayerVehicleID Y_MOCK_GetPlayerVehicleID

stock Y_MOCK_GetPlayerTeam(playerid)
{
	return MockPlayer[playerid][E_TEAM];
}

#if defined _ALS_GetPlayerTeam
	#undef GetPlayerTeam
#else
	#define _ALS_GetPlayerTeam
#endif
#define GetPlayerTeam Y_MOCK_GetPlayerTeam

stock Y_MOCK_SetPlayerTeam(playerid, teamid)
{
	if (!IsPlayerConnected(playerid)) return 0;

	MockPlayer[playerid][E_TEAM] = teamid;

	return 1;
}

#if defined _ALS_SetPlayerTeam
	#undef SetPlayerTeam
#else
	#define _ALS_SetPlayerTeam
#endif
#define SetPlayerTeam Y_MOCK_SetPlayerTeam

stock Y_MOCK_GetPlayerVehicleSeat(playerid)
{
	if (!IsPlayerConnected(playerid)) return -1;

	if (MockPlayer[playerid][E_VEHICLE_ID] == INVALID_VEHICLE_ID) return -1;

	return MockPlayer[playerid][E_VEHICLE_SEAT];
}

#if defined _ALS_GetPlayerVehicleSeat
	#undef GetPlayerVehicleSeat
#else
	#define _ALS_GetPlayerVehicleSeat
#endif
#define GetPlayerVehicleSeat Y_MOCK_GetPlayerVehicleSeat

stock Y_MOCK_PutPlayerInVehicle(playerid, vehicleid, seatid)
{
	if (!IsPlayerConnected(playerid)) return 0;

	MockPlayer[playerid][E_VEHICLE_ID] = vehicleid;
	MockPlayer[playerid][E_VEHICLE_SEAT] = seatid;	

	if (seatid == 0) {
		MockPlayer[playerid][E_PLAYER_STATE] = PLAYER_STATE_DRIVER;
	} else {
		MockPlayer[playerid][E_PLAYER_STATE] = PLAYER_STATE_PASSENGER;		
	}

	return 1;
}

#if defined _ALS_PutPlayerInVehicle
	#undef PutPlayerInVehicle
#else
	#define _ALS_PutPlayerInVehicle
#endif
#define PutPlayerInVehicle Y_MOCK_PutPlayerInVehicle

stock Y_MOCK_GetPlayerHealth(playerid, &Float:health)
{
	health = floatround(MockPlayer[playerid][E_HEALTH]);

	return 1;
}

#if defined _ALS_GetPlayerHealth
	#undef GetPlayerHealth
#else
	#define _ALS_GetPlayerHealth
#endif
#define GetPlayerHealth Y_MOCK_GetPlayerHealth

stock Y_MOCK_SetPlayerHealth(playerid, Float:health)
{
	if (!IsPlayerConnected(playerid)) return 0;

	MockPlayer[playerid][E_HEALTH] = health;	

	return 1;
}

#if defined _ALS_SetPlayerHealth
	#undef SetPlayerHealth
#else
	#define _ALS_SetPlayerHealth
#endif
#define SetPlayerHealth Y_MOCK_SetPlayerHealth

stock Y_MOCK_GetPlayerWeapon(playerid)
{
	if (!IsPlayerConnected(playerid)) return -1;

	return MockPlayer[playerid][E_CURRENT_WEAPON];
}

#if defined _ALS_GetPlayerWeapon
	#undef GetPlayerWeapon
#else
	#define _ALS_GetPlayerWeapon
#endif
#define GetPlayerWeapon Y_MOCK_GetPlayerWeapon

stock Y_MOCK_SetPlayerArmedWeapon(playerid, weaponid)
{
	if (!IsPlayerConnected(playerid)) return 0;

	for (new i = 0; i != MAX_WEAPONS; ++i) {
		if (MockPlayer[playerid][E_WEAPON][i] == weaponid) {
			MockPlayer[playerid][E_CURRENT_WEAPON] = i;
		}
	}

	return 1;
}

#if defined _ALS_SetPlayerArmedWeapon
	#undef SetPlayerArmedWeapon
#else
	#define _ALS_SetPlayerArmedWeapon
#endif
#define SetPlayerArmedWeapon Y_MOCK_SetPlayerArmedWeapon

/*
#if defined _ALS_GetPlayerAnimationIndex
	#undef GetPlayerAnimationIndex
#else
	#define _ALS_GetPlayerAnimationIndex
#endif

#define GetPlayerAnimationIndex(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_ANIMATION_INDEX],%2)

#define GetPlayerCameraAspectRatio(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_CAMERA_ASPECT_RATIO],%2)

#if defined _ALS_GetPlayerCameraFrontVector
	#undef GetPlayerCameraFrontVector
#else
	#define _ALS_GetPlayerCameraFrontVector
#endif

#define GetPlayerCameraFrontVector(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_CAMERA_FRONT_VECTOR],%2)

#if defined _ALS_GetPlayerCameraMode
	#undef GetPlayerCameraMode
#else
	#define _ALS_GetPlayerCameraMode
#endif

#define GetPlayerCameraMode(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_CAMERA_MODE],%2)

#if defined _ALS_GetPlayerCameraPos
	#undef GetPlayerCameraPos
#else
	#define _ALS_GetPlayerCameraPos
#endif

#define GetPlayerCameraPos(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_CAMERA_POS],%2)

#if defined _ALS_GetPlayerCameraUpVector
	#undef GetPlayerCameraUpVector
#else
	#define _ALS_GetPlayerCameraUpVector
#endif

#define GetPlayerCameraUpVector(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_CAMERA_UP_VECTOR],%2)

#if defined _ALS_GetPlayerCameraZoom
	#undef GetPlayerCameraZoom
#else
	#define _ALS_GetPlayerCameraZoom
#endif

#define GetPlayerCameraZoom(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_CAMERA_ZOOM],%2)

#if defined _ALS_GetPlayerDistanceFromPoint
	#undef GetPlayerDistanceFromPoint
#else
	#define _ALS_GetPlayerDistanceFromPoint
#endif

#define GetPlayerDistanceFromPoint(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_DISTANCE_FROM_POINT],%2)

#if defined _ALS_GetPlayerDrunkLevel
	#undef GetPlayerDrunkLevel
#else
	#define _ALS_GetPlayerDrunkLevel
#endif

#define GetPlayerDrunkLevel(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_DRUNK_LEVEL],%2)

#if defined _ALS_GetPlayerFacingAngle
	#undef GetPlayerFacingAngle
#else
	#define _ALS_GetPlayerFacingAngle
#endif

#define GetPlayerFacingAngle(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_FACING_ANGLE],%2)

#if defined _ALS_GetPlayerFightingStyle
	#undef GetPlayerFightingStyle
#else
	#define _ALS_GetPlayerFightingStyle
#endif

#define GetPlayerFightingStyle(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_FIGHTING_STYLE],%2)

#if defined _ALS_GetPlayerIp
	#undef GetPlayerIp
#else
	#define _ALS_GetPlayerIp
#endif

#define GetPlayerKeys(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_KEYS],%2)

#if defined _ALS_GetPlayerLastShotVectors
	#undef GetPlayerLastShotVectors
#else
	#define _ALS_GetPlayerLastShotVectors
#endif

#define GetPlayerLastShotVectors(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_LAST_SHOT_VECTORS],%2)

#if defined _ALS_GetPlayerMenu
	#undef GetPlayerMenu
#else
	#define _ALS_GetPlayerMenu
#endif

#define GetPlayerMenu(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_MENU],%2)

#if defined _ALS_GetPlayerMoney
	#undef GetPlayerMoney
#else
	#define _ALS_GetPlayerMoney
#endif

#define GetPlayerNetworkStats(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_NETWORK_STATS],%2)

#if defined _ALS_GetPlayerObjectPos
	#undef GetPlayerObjectPos
#else
	#define _ALS_GetPlayerObjectPos
#endif

#define GetPlayerObjectPos(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_OBJECT_POS],%2)

#if defined _ALS_GetPlayerObjectRot
	#undef GetPlayerObjectRot
#else
	#define _ALS_GetPlayerObjectRot
#endif

#define GetPlayerObjectRot(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_OBJECT_ROT],%2)

#if defined _ALS_GetPlayerPing
	#undef GetPlayerPing
#else
	#define _ALS_GetPlayerPing
#endif


#define GetPlayerSurfingObjectID(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_SURFING_OBJECT_ID],%2)

#if defined _ALS_GetPlayerSurfingVehicleID
	#undef GetPlayerSurfingVehicleID
#else
	#define _ALS_GetPlayerSurfingVehicleID
#endif

#define GetPlayerSurfingVehicleID(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_SURFING_VEHICLE_ID],%2)

#if defined _ALS_GetPlayerTargetPlayer
	#undef GetPlayerTargetPlayer
#else
	#define _ALS_GetPlayerTargetPlayer
#endif

#define GetPlayerTargetPlayer(%0,%1,%2) INVALID_PLAYER_ID

#if defined _ALS_GetPlayerTime
	#undef GetPlayerTime
#else
	#define _ALS_GetPlayerTime
#endif

#define GetPlayerTime(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_TIME],%2)

#if defined _ALS_GetPlayerVelocity
	#undef GetPlayerVelocity
#else
	#define _ALS_GetPlayerVelocity
#endif

#define GetPlayerVelocity(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_VELOCITY],%2)

#if defined _ALS_GetPlayerWantedLevel
	#undef GetPlayerWantedLevel
#else
	#define _ALS_GetPlayerWantedLevel
#endif

#define GetPlayerWantedLevel(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_WANTED_LEVEL],%2)

#if defined _ALS_GetPlayerWeaponData
	#undef GetPlayerWeaponData
#else
	#define _ALS_GetPlayerWeaponData
#endif

#define GetPlayerWeaponData(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_WEAPON_DATA],%2)

#if defined _ALS_GetPlayerWeaponState
	#undef GetPlayerWeaponState
#else
	#define _ALS_GetPlayerWeaponState
#endif

#define GetPlayerWeaponState(%0,%1,%2) strcpy(%1, MockPlayer[playerid][E_WEAPON_STATE],%2)
*/

stock Y_MOCK_IsPlayerAdmin(playerid)
{
	if (!IsPlayerConnected(playerid)) return 0;

	return MockPlayer[playerid][E_RCON_ADMIN];
}

#if defined _ALS_IsPlayerAdmin
	#undef IsPlayerAdmin
#else
	#define _ALS_IsPlayerAdmin
#endif
#define IsPlayerAdmin Y_MOCK_IsPlayerAdmin

stock Y_MOCK_IsPlayerInAnyVehicle(playerid)
{
	if (!IsPlayerConnected(playerid)) return 0;

	return MockPlayer[playerid][E_VEHICLE_ID] != INVALID_VEHICLE_ID;
}

#if defined _ALS_IsPlayerInAnyVehicle
	#undef IsPlayerInAnyVehicle
#else
	#define _ALS_IsPlayerInAnyVehicle
#endif
#define IsPlayerInAnyVehicle Y_MOCK_IsPlayerInAnyVehicle

stock Y_MOCK_IsPlayerInVehicle(playerid, vehicleid)
{
	if (!IsPlayerConnected(playerid)) return 0;

	return MockPlayer[playerid][E_VEHICLE_ID] == vehicleid;
}

#if defined _ALS_IsPlayerInVehicle
	#undef IsPlayerInVehicle
#else
	#define _ALS_IsPlayerInVehicle
#endif
#define IsPlayerInVehicle Y_MOCK_IsPlayerInVehicle

stock Y_MOCK_RemovePlayerFromVehicle(playerid)
{
	if (!IsPlayerConnected(playerid)) return 0;

	MockPlayer[playerid][E_VEHICLE_ID] = INVALID_VEHICLE_ID;
	MockPlayer[playerid][E_PLAYER_STATE] = PLAYER_STATE_ONFOOT;

	return 1;
}

#if defined _ALS_RemovePlayerFromVehicle
	#undef RemovePlayerFromVehicle
#else
	#define _ALS_RemovePlayerFromVehicle
#endif
#define RemovePlayerFromVehicle Y_MOCK_RemovePlayerFromVehicle

stock CreatePlayer(playerid, const name[])
{
	memset(MockPlayer[playerid][E_MOCK_PLAYER:0], 0, _:E_MOCK_PLAYER);
	MockPlayer[playerid][E_CONNECTED] = true;
	MockPlayer[playerid][E_VEHICLE_ID] = INVALID_VEHICLE_ID;
	MockPlayer[playerid][E_SPECTATING_PLAYER] = INVALID_PLAYER_ID;
	MockPlayer[playerid][E_SKIN] = 1;
	MockPlayer[playerid][E_SURFING_OBJECT_ID] = INVALID_OBJECT_ID;
	MockPlayer[playerid][E_SURFING_VEHICLE_ID] = INVALID_VEHICLE_ID;
	MockPlayer[playerid][E_PLAYER_STATE] = PLAYER_STATE_ONFOOT;

	return SetPlayerName(playerid, name);
}

stock DeletePlayer(playerid)
{
	memset(MockPlayer[playerid][E_MOCK_PLAYER:0], 0, _:E_MOCK_PLAYER);
}

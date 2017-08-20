#define CONNECTED_USER_ID 		6
#define CONNECTED_USER_ID_2		13

TestBeforeEach:y_mock()
{
	CreatePlayer(CONNECTED_USER_ID, "TestUser");
	call OnPlayerConnect(CONNECTED_USER_ID);
	CreatePlayer(CONNECTED_USER_ID_2, "TestUser2");
	call OnPlayerConnect(CONNECTED_USER_ID_2);
}

TestAfterEach:y_mock()
{
	call OnPlayerDisconnect(CONNECTED_USER_ID, 0);
	DeletePlayer(CONNECTED_USER_ID);
	call OnPlayerDisconnect(CONNECTED_USER_ID_2, 0);
	DeletePlayer(CONNECTED_USER_ID_2);
}

Test:y_mock_PlayerCreation()
{
	ASSERT_TRUE(IsPlayerConnected(CONNECTED_USER_ID));

	new name[MAX_PLAYER_NAME + 1];
	GetPlayerName(CONNECTED_USER_ID, name, sizeof name);
	ASSERT_TRUE(!strcmp(name, "TestUser"));
}

Test:y_mock_PlayerSetName()
{
	new name[MAX_PLAYER_NAME + 1];
	SetPlayerName(CONNECTED_USER_ID, "ChangedName");
	GetPlayerName(CONNECTED_USER_ID, name, sizeof name);
	ASSERT_TRUE(!strcmp(name, "ChangedName"));
}

Test:y_mock_PlayerPosition()
{
	SetPlayerPos(CONNECTED_USER_ID, 300.0, 600.0, 11.0);
	new Float:pos[3];
	GetPlayerPos(CONNECTED_USER_ID, pos[0], pos[1], pos[2]);

	ASSERT_TRUE((pos[0] == 300.0 && pos[1] == 600.0 && pos[2] == 11.0));
}

Test:y_mock_PlayerHealth()
{
	SetPlayerHealth(CONNECTED_USER_ID, 50.4);
	new Float:health;
	GetPlayerHealth(CONNECTED_USER_ID, health);

	ASSERT(health == 50.0);
}

Test:y_mock_PlayerArmour()
{
	SetPlayerArmour(CONNECTED_USER_ID, 55.6);
	new Float:armour;
	GetPlayerArmour(CONNECTED_USER_ID, armour);

	ASSERT(armour == 56.0);
}

Test:y_mock_PlayerColor()
{
	SetPlayerColor(CONNECTED_USER_ID, 0xBADA55);
	ASSERT(GetPlayerColor(CONNECTED_USER_ID) == 0xBADA55);
}

Test:y_mock_PLayerVehicle()
{
	ASSERT(GetPlayerVehicleID(CONNECTED_USER_ID) == INVALID_VEHICLE_ID);
	ASSERT(GetPlayerVehicleSeat(CONNECTED_USER_ID) == -1);

	PutPlayerInVehicle(CONNECTED_USER_ID, 666, 1);

	ASSERT(GetPlayerVehicleID(CONNECTED_USER_ID) == 666);
	ASSERT(GetPlayerVehicleSeat(CONNECTED_USER_ID) == 1);
	ASSERT(GetPlayerState(CONNECTED_USER_ID) == PLAYER_STATE_PASSENGER);
	ASSERT_TRUE(IsPlayerInVehicle(CONNECTED_USER_ID, 666));
	ASSERT_TRUE(IsPlayerInAnyVehicle(CONNECTED_USER_ID));

	PutPlayerInVehicle(CONNECTED_USER_ID, 666, 0);

	ASSERT(GetPlayerVehicleID(CONNECTED_USER_ID) == 666);
	ASSERT(GetPlayerVehicleSeat(CONNECTED_USER_ID) == 0);
	ASSERT(GetPlayerState(CONNECTED_USER_ID) == PLAYER_STATE_DRIVER);

	RemovePlayerFromVehicle(CONNECTED_USER_ID);

	ASSERT(GetPlayerVehicleID(CONNECTED_USER_ID) == INVALID_VEHICLE_ID);
	ASSERT(GetPlayerVehicleSeat(CONNECTED_USER_ID) == -1);
	ASSERT(GetPlayerState(CONNECTED_USER_ID) == PLAYER_STATE_ONFOOT);
	ASSERT(!IsPlayerInVehicle(CONNECTED_USER_ID, 666));
	ASSERT_TRUE(!IsPlayerInAnyVehicle(CONNECTED_USER_ID));
}

Test:y_mock_PlayerDialog()
{
	ShowPlayerDialog(CONNECTED_USER_ID, 1000, DIALOG_STYLE_INPUT, "Welcome", "You are welcome here", "Thanks", "Go away");

	new
		dialogid, style, caption[64 + 1], info[4096 + 1], button1[32 + 1], button2[32 + 1]
	;

	GetPlayerDialog(CONNECTED_USER_ID, dialogid, style, caption, info, button1, button2);

	ASSERT(dialogid == 1000);
	ASSERT(style == DIALOG_STYLE_INPUT);
	ASSERT(!strcmp(caption, "Welcome"));
	ASSERT(!strcmp(info, "You are welcome here"));
	ASSERT(!strcmp(button1, "Thanks"));
	ASSERT(!strcmp(button2, "Go away"));

	call OnDialogResponse(CONNECTED_USER_ID, 1000, 1, 0, "\1");

	GetPlayerDialog(CONNECTED_USER_ID, dialogid, style, caption, info, button1, button2);

	ASSERT(dialogid == -1);
	ASSERT(style == -1);
	ASSERT(isnull(caption));
	ASSERT(isnull(info));
	ASSERT(isnull(button1));
	ASSERT(isnull(button1));
}

Test:y_mock_PlayerMoney()
{
	ASSERT(GetPlayerMoney(CONNECTED_USER_ID) == 0);

	GivePlayerMoney(CONNECTED_USER_ID, 1000);

	ASSERT(GetPlayerMoney(CONNECTED_USER_ID) == 1000);
}

Test:y_mock_PlayerVW()
{
	ASSERT(GetPlayerVirtualWorld(CONNECTED_USER_ID) == 0);

	SetPlayerVirtualWorld(CONNECTED_USER_ID, 11);

	ASSERT(GetPlayerVirtualWorld(CONNECTED_USER_ID) == 11);
}

Test:y_mock_PlayerTeam()
{
	ASSERT(GetPlayerTeam(CONNECTED_USER_ID) == 0);

	SetPlayerTeam(CONNECTED_USER_ID, 22);

	ASSERT(GetPlayerTeam(CONNECTED_USER_ID) == 22);
}

Test:y_mock_PlayerSkin()
{
	ASSERT(GetPlayerSkin(CONNECTED_USER_ID) == 0);

	SetPlayerSkin(CONNECTED_USER_ID, 33);

	ASSERT(GetPlayerSkin(CONNECTED_USER_ID) == 33);

	SetPlayerSkin(CONNECTED_USER_ID, 666);

	ASSERT(GetPlayerSkin(CONNECTED_USER_ID) == 0);
}

Test:y_mock_PlayerPing()
{
	ASSERT(GetPlayerPing(CONNECTED_USER_ID) == 0);

	SetPlayerPing(CONNECTED_USER_ID, 666);

	ASSERT(GetPlayerPing(CONNECTED_USER_ID) == 666);	
}

Test:y_mock_PlayerScore()
{
	ASSERT(GetPlayerScore(CONNECTED_USER_ID) == 0);

	SetPlayerScore(CONNECTED_USER_ID, 1337);

	ASSERT(GetPlayerScore(CONNECTED_USER_ID) == 1337);	
}

Test:y_mock_PlayerInterior()
{
	ASSERT(GetPlayerInterior(CONNECTED_USER_ID) == 0);

	SetPlayerInterior(CONNECTED_USER_ID, 321);

	ASSERT(GetPlayerInterior(CONNECTED_USER_ID) == 321);	
}

Test:y_mock_PlayerIP()
{
	new ip[16 + 1];
	GetPlayerIp(CONNECTED_USER_ID, ip, sizeof ip);
	ASSERT(!strcmp(ip, "127.0.0.1"));

	SetPlayerIp(CONNECTED_USER_ID, "255.255.255.255");
	GetPlayerIp(CONNECTED_USER_ID, ip, sizeof ip);

	ASSERT(!strcmp(ip, "255.255.255.255"));
}

Test:y_mock_PlayerVersion()
{
	new version[32 + 1];
	GetPlayerVersion(CONNECTED_USER_ID, version, sizeof version);
	ASSERT(isnull(version));

	SetPlayerVersion(CONNECTED_USER_ID, "0.3.7");
	GetPlayerVersion(CONNECTED_USER_ID, version, sizeof version);

	ASSERT(!strcmp(version, "0.3.7"));
}

Test:y_mock_PlayerAdmin()
{
	ASSERT_FALSE(IsPlayerAdmin(CONNECTED_USER_ID));

	TogglePlayerAdmin(CONNECTED_USER_ID, true);

	ASSERT_TRUE(IsPlayerAdmin(CONNECTED_USER_ID));
}

Test:y_mock_PlayerSpecialAction()
{
	ASSERT(GetPlayerSpecialAction(CONNECTED_USER_ID) == SPECIAL_ACTION_NONE);

	SetPlayerSpecialAction(CONNECTED_USER_ID, SPECIAL_ACTION_DANCE1);

	ASSERT(GetPlayerSpecialAction(CONNECTED_USER_ID) == SPECIAL_ACTION_DANCE1);

	SetPlayerSpecialAction(CONNECTED_USER_ID, 14);

	ASSERT(GetPlayerSpecialAction(CONNECTED_USER_ID) == SPECIAL_ACTION_NONE);
}

Test:y_mock_PlayerState()
{
	ASSERT(GetPlayerState(CONNECTED_USER_ID) == PLAYER_STATE_ONFOOT);

	SetPlayerState(CONNECTED_USER_ID, PLAYER_STATE_DRIVER);

	ASSERT(GetPlayerState(CONNECTED_USER_ID) == PLAYER_STATE_DRIVER);

	SetPlayerState(CONNECTED_USER_ID, 20);

	ASSERT(GetPlayerState(CONNECTED_USER_ID) == PLAYER_STATE_DRIVER);
}

Test:y_mock_PlayerWeapon()
{
	ASSERT(GetPlayerAmmo(CONNECTED_USER_ID) == 0);
	ASSERT(GetPlayerWeapon(CONNECTED_USER_ID) == 0);
	ASSERT(GetPlayerWeapon(INVALID_PLAYER_ID) == -1);

	GivePlayerWeapon(CONNECTED_USER_ID, 22, 150);
	SetPlayerArmedWeapon(CONNECTED_USER_ID, 22);

	ASSERT(GetPlayerAmmo(CONNECTED_USER_ID) == 150);
	ASSERT(GetPlayerWeapon(CONNECTED_USER_ID) == 22);

	SetPlayerAmmo(CONNECTED_USER_ID, 22, 200);

	ASSERT(GetPlayerAmmo(CONNECTED_USER_ID) == 200);
}
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

	PutPlayerInVehicle(CONNECTED_USER_ID, 666, 0);

	ASSERT(GetPlayerVehicleID(CONNECTED_USER_ID) == 666);
	ASSERT(GetPlayerVehicleSeat(CONNECTED_USER_ID) == 0);
	ASSERT(GetPlayerState(CONNECTED_USER_ID) == PLAYER_STATE_DRIVER);

	RemovePlayerFromVehicle(CONNECTED_USER_ID);

	ASSERT(GetPlayerVehicleID(CONNECTED_USER_ID) == INVALID_VEHICLE_ID);
	ASSERT(GetPlayerVehicleSeat(CONNECTED_USER_ID) == -1);
	ASSERT(GetPlayerState(CONNECTED_USER_ID) == PLAYER_STATE_ONFOOT);
}

Test:y_mock_PlayerDialog()
{
	print("Fail 0");
	ShowPlayerDialog(CONNECTED_USER_ID, 1000, DIALOG_STYLE_INPUT, "Welcome", "You are welcome here", "Thanks", "Go away");
	print("Fail 1");

	new
		dialogid, style, caption[64 + 1], info[4096 + 1], button1[32 + 1], button2[32 + 1]
	;
	print("Fail 2");

	GetPlayerDialog(CONNECTED_USER_ID, dialogid, style, caption, info, button1, button2);
	print("Fail 3");

	ASSERT(dialogid == 1000);
	ASSERT(style == DIALOG_STYLE_INPUT);
	ASSERT(!strcmp(caption, "Welcome"));
	ASSERT(!strcmp(info, "You are welcome here"));
	ASSERT(!strcmp(button1, "Thanks"));
	ASSERT(!strcmp(button1, "Go away"));
}
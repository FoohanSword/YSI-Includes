#define CONNECTED_USER_ID 6

TestInit:PlayerCreation()
{
	CreatePlayer(CONNECTED_USER_ID, "TestUser");
	call OnPlayerConnect(CONNECTED_USER_ID);
}

Test:PlayerCreation()
{
	ASSERT_TRUE(IsPlayerConnected(CONNECTED_USER_ID));

	new name[MAX_PLAYER_NAME + 1];
	GetPlayerName(CONNECTED_USER_ID, name, sizeof name);
	ASSERT_TRUE(!strcmp(name, "TestUser"));
}

TestClose:PlayerCreation()
{
	call OnPlayerDisconnect(CONNECTED_USER_ID, 0);
	DeletePlayer(CONNECTED_USER_ID);
}

TestInit:PlayerSetName()
{
	CreatePlayer(CONNECTED_USER_ID, "TestUser");
	call OnPlayerConnect(CONNECTED_USER_ID);
}

Test:PlayerSetName()
{
	new name[MAX_PLAYER_NAME + 1];
	SetPlayerName(CONNECTED_USER_ID, "ChangedName");
	GetPlayerName(CONNECTED_USER_ID, name, sizeof name);
	ASSERT_TRUE(!strcmp(name, "ChangedName"));
}

TestClose:PlayerSetName()
{
	call OnPlayerDisconnect(CONNECTED_USER_ID, 0);
	DeletePlayer(CONNECTED_USER_ID);
}

TestInit:PlayerPosition()
{
	CreatePlayer(CONNECTED_USER_ID, "TestUser");
	call OnPlayerConnect(CONNECTED_USER_ID);
}

Test:PlayerPosition()
{
	SetPlayerPos(CONNECTED_USER_ID, 300.0, 600.0, 11.0);
	new Float:pos[3];
	GetPlayerPos(CONNECTED_USER_ID, pos[0], pos[1], pos[2]);

	ASSERT_TRUE((pos[0] == 300.0 && pos[1] == 600.0 && pos[2] == 11.0));
}

TestClose:PlayerPosition()
{
	call OnPlayerDisconnect(CONNECTED_USER_ID, 0);
	DeletePlayer(CONNECTED_USER_ID);
}

TestInit:PlayerHealth()
{
	CreatePlayer(CONNECTED_USER_ID, "TestUser");
	call OnPlayerConnect(CONNECTED_USER_ID);
}

Test:PlayerHealth()
{
	SetPlayerHealth(CONNECTED_USER_ID, 50.4);
	new Float:health;
	GetPlayerHealth(CONNECTED_USER_ID, health);

	ASSERT(health == 50.0);
}

TestClose:PlayerHealth()
{
	call OnPlayerDisconnect(CONNECTED_USER_ID, 0);
	DeletePlayer(CONNECTED_USER_ID);
}
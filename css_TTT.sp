#include <sourcemod>
#include <sdktools>
#include <cstrike>

float g_timer_ttt;
bool g_Traidor[MAXPLAYERS+1] = {false, ...};
ConVar gcvar_timer_ttt;

public Plugin myinfo =
{
	name = "TTT CS:SOURCE",
	author = "Slash",
	description = "SET GAMEMODE TTT IN Cs:Source",
	version = PLUGIN_VERSION,
	url = "http://www.sourcemod.net/"
};

public void OnPluginStart()
{
    HookEvent("round_start", roundStartTTT);
    HookEvent("round_freeze_end", FreezeEndTTT);
	HookEvent("player_spawn", Event_PlayerSpawnTTT);
	gcvar_timer_ttt = CreateConVar("sm_ttt_timer", "30", "set timer after freeze to choose traitor.");
	g_timer_ttt = gcvar_timer_ttt.FloatValue;
	gcvar_timer_ttt.AddChangeHook(OnConVarChanged);
}

public void OnConVarChanged(ConVar convar, const char[] oldValue, const char[] newValue)
{
	if (convar == gcvar_timer_ttt)
	{
		g_timer_ttt = gcvar_timer_ttt.FloatValue;
	}
}
public void OnClientPostAdminCheck(int client)
{
	g_Traidor[client] = false;
}

public void roundStartTTT(Event event, const char[] name, bool dontBroadcast)
{
    ServerCommand("mp_tkpunish 0");
    ServerCommand("mp_friendlyfire 0");
{

public void FreezeEndTTT(Event event, const char[] name, bool dontBroadcast)
{
	CreateTimer(g_timer_ttt,SetTraidor)
}
public void Event_PlayerSpawnTTT(Event event, const char[] name, bool dontBroadcast)
{
	int client = GetClientOfUserId(event.GetInt("userid"));
	g_Traidor[client] = false;
}

public Action SetTraidor(Handle timer)
{

}


int RandomPlayer()
{
	int clients[MaxClients+1], clientCount;
	for (int i = 1; i <= MaxClients; i++)
	if (IsClientInGame(i) && IsPlayerAlive(i))
	clients[clientCount++] = i;
	return (clientCount == 0) ? -1 : clients[GetRandomInt(0, clientCount-1)];
}
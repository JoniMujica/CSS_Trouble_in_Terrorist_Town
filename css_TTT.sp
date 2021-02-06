#include <sourcemod>
#include <sdktools>
#include <cstrike>

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
}
public void OnClientPostAdminCheck(int client)
{
}

public void roundStartTTT(Event event, const char[] name, bool dontBroadcast)
{
    ServerCommand("mp_tkpunish 0");
    ServerCommand("mp_friendlyfire 0");
{

public void FreezeEndTTT(Event event, const char[] name, bool dontBroadcast)
{
}

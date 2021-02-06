#include <sourcemod>
#include <sdktools>
#include <cstrike>
#include <morecolors>
#define PLUGIN_VERSION "1.2"
float g_timer_ttt;
int maxt;
int Traitor = 0;
int max;
bool g_Traitor[MAXPLAYERS+1] = {false, ...};
ConVar gcvar_timer_ttt;
ConVar gcvar_max_traitor;

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
	HookEvent("player_death", EventPlayerDeathTTT);

	gcvar_timer_ttt = CreateConVar("sm_ttt_timer", "30", "set timer after freeze to choose traitor.");
	g_timer_ttt = gcvar_timer_ttt.FloatValue;
	gcvar_timer_ttt.AddChangeHook(OnConVarChanged);

	gcvar_max_traitor = CreateConVar("sm_ttt_max", "1", "set timer after freeze to choose traitor.");
	maxt = gcvar_max_traitor.IntValue;
	gcvar_max_traitor.AddChangeHook(OnConVarChanged);
}

public void roundStartTTT(Event event, const char[] name, bool dontBroadcast)
{
    ServerCommand("mp_tkpunish 0");
    ServerCommand("mp_friendlyfire 0");
}

public void FreezeEndTTT(Event event, const char[] name, bool dontBroadcast)
{
	CreateTimer(g_timer_ttt,SetTraidor);
}
public void Event_PlayerSpawnTTT(Event event, const char[] name, bool dontBroadcast)
{
	int client = GetClientOfUserId(event.GetInt("userid"));
	g_Traitor[client] = false;
}

public void EventPlayerDeathTTT(Event event, const char[] name, bool dontBroadcast)
{
    SetEventBroadcast(event, true);
} 


public void OnConVarChanged(ConVar convar, const char[] oldValue, const char[] newValue)
{
	if (convar == gcvar_timer_ttt)
		g_timer_ttt = gcvar_timer_ttt.FloatValue;
	if(convar == gcvar_max_traitor)
	maxt = gcvar_max_traitor.IntValue;
}
public void OnClientPostAdminCheck(int client)
{
	g_Traitor[client] = false;
}

public Action SetTraidor(Handle timer)
{
	max = maxTraitor();
	for(int i = 0; i<max;i++){
		Traitor = RandomPlayer();
		if(!g_Traitor[Traitor]){
			g_Traitor[Traitor] = true;
		}
	}
	PrintToChatTTT();
}

int RandomPlayer()
{
	int[] clients = new int[MaxClients + 1];
	int clientCount;
	for (int i = 1; i <= MaxClients; i++)
	if (IsClientInGame(i) && IsPlayerAlive(i))
	clients[clientCount++] = i;
	return (clientCount == 0) ? -1 : clients[GetRandomInt(0, clientCount-1)];
}

int maxTraitor(){
	int maxts = 0;
	for (int i = 1; i <= MaxClients; i++)
	{
		if(IsClientInGame(i) && IsPlayerAlive(i))
		{
			if(maxt == 1){
				return 1;
			}else if(i % maxt == 0){
				maxts++;
			}
		}
	}
	return maxts;
}


void PrintToChatTTT(){
	for (int i = 1; i <= MaxClients; i++)
	{
		if(IsClientInGame(i)){
			 if (g_Traitor[i])
			{        
				CPrintToChat(i, "{orangered}[☣️ToxiC☣️TTT] : {white}Sos el {darkred}traidor{white}, mata a tus compañeros sin que te descubran!");     
			}
			else
			{
				CPrintToChat(i, "{orangered}[☣️ToxiC☣️TTT] : {white}Sos {green}inocente{white}, vigila tu espalda!");
			}
		}
	}
	CPrintToChatAll("{orangered}[☣️ToxiC☣️TTT] : {white}El {red}traidor {white}ha sido elegido, el juego comienza");
}
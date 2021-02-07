#include <sourcemod>
#include <sdktools>
#include <cstrike>
#include <morecolors>
#include <sdkhooks>
#define PLUGIN_VERSION "1.3"
#define TK_TTT(%1,%2) (1 <= %1 <= MaxClients && 1 <= %2 <= MaxClients && %1 != %2 && GetClientTeam(%1) == GetClientTeam(%2))
float g_timer_ttt;
int maxt;
int Traitor = 0;
int max;
bool g_Traitor[MAXPLAYERS+1] = {false, ...};
ConVar gcvar_timer_ttt;
ConVar gcvar_max_traitor;
ConVar g_cvar_ff;


public Plugin myinfo =
{
	name = "TTT CS:SOURCE",
	author = "Slash & RMinks",
	description = "SET GAMEMODE TTT IN Cs:Source",
	version = PLUGIN_VERSION,
	url = "http://www.sourcemod.net/"
};

public void OnPluginStart()
{
	HookEvent("round_start", roundStartTTT);
	HookEvent("round_freeze_end", FreezeEndTTT);
	HookEvent("player_spawn", Event_PlayerSpawnTTT);
	HookEvent("player_death", EventPlayerDeathTTT,EventHookMode_Pre);

	g_cvar_ff = FindConVar("mp_friendlyfire");
	gcvar_timer_ttt = CreateConVar("sm_ttt_timer", "30", "set timer after freeze to choose traitor.");
	g_timer_ttt = gcvar_timer_ttt.FloatValue;
	gcvar_timer_ttt.AddChangeHook(OnConVarChanged);

	gcvar_max_traitor = CreateConVar("sm_ttt_max", "1", "set max traitor for alive players.");
	maxt = gcvar_max_traitor.IntValue;
	gcvar_max_traitor.AddChangeHook(OnConVarChanged);



	AutoExecConfig(true, "css_ttt");
}

public void OnConVarChanged(ConVar convar, const char[] oldValue, const char[] newValue)
{
	if (convar == gcvar_timer_ttt)
		g_timer_ttt = gcvar_timer_ttt.FloatValue;
	if(convar == gcvar_max_traitor)
		maxt = gcvar_max_traitor.IntValue;
}
public void roundStartTTT(Event event, const char[] name, bool dontBroadcast)
{
    ServerCommand("mp_tkpunish 0");
    g_cvar_ff.SetInt(0);
}

public void FreezeEndTTT(Event event, const char[] name, bool dontBroadcast)
{
	CreateTimer(g_timer_ttt,SetTraidor);
	int time = RoundFloat(g_timer_ttt);
	CPrintToChatAll("{orangered}[☣️ToxiC☣️TTT] : {white}El juego iniciará en {lightgreen}%i {white}segundos", time);
}
public void Event_PlayerSpawnTTT(Event event, const char[] name, bool dontBroadcast)
{
	int client = GetClientOfUserId(event.GetInt("userid"));
	g_Traitor[client] = false;
}

public Action:EventPlayerDeathTTT(Event event, const char[] name, bool dontBroadcast)
{
	new victim = GetClientOfUserId(GetEventInt(event, "userid"));
	new attacker = GetClientOfUserId(GetEventInt(event, "attacker"));

	if (TK_TTT(victim, attacker))
	{
		SetEntProp(attacker, Prop_Data, "m_iFrags", GetClientFrags(attacker) + 1);
	}
	return Plugin_Handled;
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
	g_cvar_ff.SetInt(1);
	PrintToChatTTT();
	TK_TTT_KILLMSG();
	HideRadarTTT();
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

stock TK_TTT_KILLMSG()
{
	HookUserMessage(GetUserMessageId("TextMsg"), Hook_TextMsg, true);
	HookUserMessage(GetUserMessageId("HintText"), Hook_HintText, true);
	
	for (new i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i))
		{
			SDKHook(i, SDKHook_OnTakeDamage, OnTakeDamage);
		}
	}
}

public Action:Hook_TextMsg(UserMsg msg_id, Handle bf, const players[], playersNum, bool reliable, bool init)
{
	decl String:msg[256];
	BfReadString(bf, msg, sizeof(msg));

	if (StrContains(msg, "teammate_attack") != -1)
	{
		return Plugin_Handled;
	}

	if (StrContains(msg, "Killed_Teammate") != -1)
	{
		return Plugin_Handled;
	}
		
	return Plugin_Continue;
}

public Action:Hook_HintText(UserMsg msg_id, Handle bf, const players[], playersNum, bool reliable, bool init)
{
	decl String:msg[256];
	BfReadString(bf, msg, sizeof(msg));
	
	if (StrContains(msg, "spotted_a_friend") != -1)
	{
		return Plugin_Handled;
	}

	if (StrContains(msg, "careful_around_teammates") != -1)
	{
		return Plugin_Handled;
	}
	
	if (StrContains(msg, "try_not_to_injure_teammates") != -1)
	{
		return Plugin_Handled;
	}

	return Plugin_Continue;
}

public Action:OnTakeDamage(victim, &attacker, &inflictor, &Float:damage, &damagetype)
{
	if (TK_TTT(victim, attacker) && inflictor == attacker)
	{
		damage /= 0.35;
		return Plugin_Changed;
	}

	return Plugin_Continue;
}

stock HideRadarTTT()
{
	for (new i = 1; i <= MaxClients; i++)
	{
		SetEntPropFloat(i, Prop_Send, "m_flFlashDuration", 3600.0);
		SetEntPropFloat(i, Prop_Send, "m_flFlashMaxAlpha", 0.5);
	}
}
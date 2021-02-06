#if defined _skins_weapons_included_
  #endinput
#endif
#define _skins_weapons_included_

native GetIDClient_SkinsWeapons(client);

native bool:AddWeapon_SkinsWeapons(client, const String:weapon[], const String:skin[], time);

native bool:DelWeapon_SkinsWeapons(client, const String:weapon[], const String:skin[]);

native bool:CheckSkinWeapon_SkinsWeapons(client, const String:weapon[], const String:skin[], bool:arg4);

native bool:CheckWeapon_SkinsWeapons(client, const String:weapon[], bool:arg3);

native bool:AddTime_SkinsWeapons(client, const String:weapon[], const String:skin[], time);

// status: 0 - on, 1 - off, 2 - get status
native bool:EnableWeapon_SkinsWeapons(client, status);

native bool:NewClient_SkinsWeapons(client);

native SetOnSequences_SkinsWeapons(client, bool:arg2);

public SharedPlugin:__pl_skins_weapons = 
{
	name = "skins_weapons",
	file = "PW_core_4.smx",
#if defined REQUIRE_PLUGIN
	required = 1,
#else
	required = 0,
#endif
};

#if !defined REQUIRE_PLUGIN
public void __pl_skins_weapons_SetNTVOptional()
{
	MarkNativeAsOptional("GetIDClient_SkinsWeapons");
	MarkNativeAsOptional("AddWeapon_SkinsWeapons");
	MarkNativeAsOptional("DelWeapon_SkinsWeapons");
	MarkNativeAsOptional("CheckSkinWeapon_SkinsWeapons");
	MarkNativeAsOptional("CheckWeapon_SkinsWeapons");
	MarkNativeAsOptional("AddTime_SkinsWeapons");
	MarkNativeAsOptional("EnableWeapon_SkinsWeapons");
	MarkNativeAsOptional("NewClient_SkinsWeapons");
	MarkNativeAsOptional("SetOnSequences_SkinsWeapons");
}
#endif

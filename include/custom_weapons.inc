#if defined _custom_weapons_included
  #endinput
#endif
#define _custom_weapons_included

functag public Action:CWWeapon_Think(client, weapon, predicted_viewmodel, old_sequence, &sequence);
functag public Action:CWWeapon_Switch(client, weapon, predicted_viewmodel, old_sequence, &sequence, bool:switched_from, &bool:custom_change);

native CW_RegisterWeapon(const String:sWeapon[], const String:sViewModel[] = "", const String:sWorldModel[] = "", const String:sDropModelCSGO[] = "", CWWeapon_Switch:OnWeaponSwitch = CWWeapon_Switch:INVALID_FUNCTION, CWWeapon_Think:OnWeaponThink = CWWeapon_Think:INVALID_FUNCTION);
native bool:CW_IsWeaponRegistered(const String:sWeapon[]);
native CW_UnregisterWeapon(const String:sWeapon[]);
native CW_UnregisterMe();
native CW_IsCurrentlyCustom(client);

stock CW_SetViewModelIndex(custom_viewmodel, index)
{
	SetEntProp(custom_viewmodel, Prop_Send, "m_nModelIndex", index);
}

stock CW_SetWorldModelIndex(weapon, index)
{
	SetEntProp(weapon, Prop_Send, "m_iWorldModelIndex", index);
	SetEntProp(weapon, Prop_Send, "m_PredictableID", index);
}


public SharedPlugin:__pl_custom_weapons = 
{
	name = "custom_weapons",
	file = "custom_weapons.smx",
#if defined REQUIRE_PLUGIN
	required = 1,
#else
	required = 0,
#endif
};

#if !defined REQUIRE_PLUGIN
public __pl_custom_weapons_SetNTVOptional()
{
	MarkNativeAsOptional("CW_RegisterWeapon");
	MarkNativeAsOptional("CW_IsWeaponRegistered");
	MarkNativeAsOptional("CW_UnregisterWeapon");
	MarkNativeAsOptional("CW_UnregisterMe");
	MarkNativeAsOptional("CW_IsCurrentlyCustom");
}
#endif
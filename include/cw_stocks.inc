#if !defined EF_DIMLIGHT
#define EF_DIMLIGHT 4
#endif

#if !defined EF_NODRAW
#define EF_NODRAW 32
#endif

// Addon bits
#define CSAddon_NONE            0
#define CSAddon_Flashbang1      (1<<0)
#define CSAddon_Flashbang2      (1<<1)
#define CSAddon_HEGrenade       (1<<2)
#define CSAddon_SmokeGrenade    (1<<3)
#define CSAddon_C4              (1<<4)
#define CSAddon_DefuseKit       (1<<5)
#define CSAddon_PrimaryWeapon   (1<<6)
#define CSAddon_SecondaryWeapon (1<<7)
#define CSAddon_Holster         (1<<8) 

enum CSWeaponBits
{
    CS_WEAPON_NONE,
    CS_WEAPON_P228,
    CS_WEAPON_GLOCK,
    CS_WEAPON_SCOUT,
    CS_WEAPON_HEGRENADE,
    CS_WEAPON_XM1014,
    CS_WEAPON_C4,
    CS_WEAPON_MAC10,
    CS_WEAPON_AUG,
    CS_WEAPON_SMOKEGRENADE,
    CS_WEAPON_ELITE,
    CS_WEAPON_FIVESEVEN,
    CS_WEAPON_UMP45,
    CS_WEAPON_SG550,
    CS_WEAPON_GALIL,
    CS_WEAPON_FAMAS,
    CS_WEAPON_USP,
    CS_WEAPON_AWP,
    CS_WEAPON_MP5NAVY,
    CS_WEAPON_M249,
    CS_WEAPON_M3,
    CS_WEAPON_M4A1,
    CS_WEAPON_TMP,
    CS_WEAPON_G3SG1,
    CS_WEAPON_FLASHBANG,
    CS_WEAPON_DEAGLE,
    CS_WEAPON_SG552,
    CS_WEAPON_AK47,
    CS_WEAPON_KNIFE,
    CS_WEAPON_P90,
    CS_WEAPON_SHIELD,
    CS_WEAPON_KEVLAR,
    CS_WEAPON_ASSAULTSUIT,
    CS_WEAPON_NIGHTVISION
}

enum CSGrenadeProjectile 
{
	iTeam,
	vec_Mins,
	vec_Maxs,
	iGrenOwner,
	iThrower,
	vec_Origin,
	vec_Velocity,
	vec_Angles,
	flElasticity
};

enum CSWeapon
{
	iClip,
	iClip2,
	iAmmoCount,
	PredictID,
	flNextPrimaryAttack,
	flNextSecondaryAttack
}

enum CSBasePlayer
{
	iActiveWeapon,
	iAddonBits,
	iPrimaryAddon,
	iSecondaryAddon,
	iProgressBar,
	flProgressBarStartTime,
	iObserverTarget
}

enum CSPredictedViewModel
{
	iSequence,
	fEffects,
	flPlaybackRate,
	iModelIndex,
	iViewModelIndex,
	iOwner,
	iWeapon
}

new CSGrenOffsets[CSGrenadeProjectile];
new CSWeaponOffsets[CSWeapon];
new CSPlayerOffsets[CSBasePlayer];
new CSViewModelOffsets[CSPredictedViewModel];

stock RegisterOffsets()
{
	CSPlayerOffsets[iActiveWeapon] = FindSendPropOffs("CCSPlayer", "m_hActiveWeapon");
	CSPlayerOffsets[iAddonBits] = FindSendPropOffs("CCSPlayer", "m_iAddonBits");
	CSPlayerOffsets[iPrimaryAddon] = FindSendPropOffs("CCSPlayer", "m_iPrimaryAddon");
	CSPlayerOffsets[iSecondaryAddon] = FindSendPropOffs("CCSPlayer", "m_iSecondaryAddon");
	CSPlayerOffsets[iProgressBar] = FindSendPropOffs("CCSPlayer", "m_iProgressBarDuration");
	CSPlayerOffsets[flProgressBarStartTime] = FindSendPropOffs("CCSPlayer", "m_flProgressBarStartTime");
	CSPlayerOffsets[iObserverTarget] = FindSendPropOffs("CCSPlayer", "m_hObserverTarget");
	
	CSGrenOffsets[iTeam] = FindSendPropOffs("CBaseCSGrenadeProjectile", "m_iTeamNum");
	CSGrenOffsets[vec_Mins] = FindSendPropOffs("CBaseCSGrenadeProjectile", "m_vecMins");
	CSGrenOffsets[vec_Maxs] = FindSendPropOffs("CBaseCSGrenadeProjectile", "m_vecMaxs");
	CSGrenOffsets[iGrenOwner] = FindSendPropOffs("CBaseCSGrenadeProjectile", "m_hOwnerEntity");
	CSGrenOffsets[iThrower] = FindSendPropOffs("CBaseCSGrenadeProjectile", "m_hThrower");
	CSGrenOffsets[vec_Origin] = FindSendPropOffs("CBaseCSGrenadeProjectile", "m_vecOrigin");
	CSGrenOffsets[vec_Velocity] = FindSendPropOffs("CBaseCSGrenadeProjectile", "m_vecVelocity");
	CSGrenOffsets[vec_Angles] = FindSendPropOffs("CBaseCSGrenadeProjectile", "m_angRotation");
	CSGrenOffsets[flElasticity] = FindSendPropOffs("CBaseCSGrenadeProjectile", "m_flElasticity");
	
	CSWeaponOffsets[iClip] = FindSendPropOffs("CBaseCombatWeapon", "m_iClip1");
	CSWeaponOffsets[iClip2] = FindSendPropOffs("CBaseCombatWeapon", "m_iClip2");
	CSWeaponOffsets[iAmmoCount] = FindSendPropInfo("CBaseCombatWeapon", "m_iPrimaryAmmoCount");
	CSWeaponOffsets[PredictID] = FindSendPropOffs("CBaseCombatWeapon", "m_PredictableID");
	CSWeaponOffsets[flNextPrimaryAttack] = FindSendPropOffs("CBaseCombatWeapon", "m_flNextPrimaryAttack");
	CSWeaponOffsets[flNextSecondaryAttack] = FindSendPropOffs("CBaseCombatWeapon", "m_flNextSecondaryAttack");
	
	CSViewModelOffsets[iSequence] = FindSendPropOffs("CPredictedViewModel", "m_nSequence");
	CSViewModelOffsets[fEffects] = FindSendPropOffs("CPredictedViewModel", "m_fEffects");
	CSViewModelOffsets[flPlaybackRate] = FindSendPropOffs("CPredictedViewModel", "m_flPlaybackRate");
	CSViewModelOffsets[iModelIndex] = FindSendPropOffs("CPredictedViewModel", "m_nModelIndex");
	CSViewModelOffsets[iViewModelIndex] = FindSendPropOffs("CPredictedViewModel", "m_nViewModelIndex");
	CSViewModelOffsets[iOwner] = FindSendPropOffs("CPredictedViewModel", "m_hOwner");
	CSViewModelOffsets[iWeapon] = FindSendPropOffs("CPredictedViewModel", "m_hWeapon");
}

stock CSPlayer_GetAddonBits(client)
{
	return GetEntData(client, CSPlayerOffsets[iAddonBits]);
}

stock CSPlayer_SetAddonBits(client, bits)
{
	SetEntData(client, CSPlayerOffsets[iAddonBits], bits, _, true);
}
stock CSPlayer_AddAddonBits(client, bit)
{
	new bits = CSPlayer_GetAddonBits(client);
	if (bits & bit)
	{
		return;
	}
	bits |= bit;
	CSPlayer_SetAddonBits(client, bits);
}

stock CSPlayer_RemoveAddonBits(client, bit)
{
	new bits = CSPlayer_GetAddonBits(client);
	if (!(bits & bit))
	{
		return;
	}
	bits &= ~bit;
	CSPlayer_SetAddonBits(client, bits);
}

stock CSWeaponBits:CSPlayer_GetPrimaryAddonBit(clien)
{
	return CSWeaponBits:GetEntData(client, CSPlayerOffsets[iPrimaryAddon]);
}

stock CSPlayer_SetPrimaryAddonBit(client, CSWeaponBits:bit)
{
	SetEntData(client, CSPlayerOffsets[iPrimaryAddon], _:bit, _, true);
}

stock CSWeaponBits:CSPlayer_GetSecondaryAddonBit(clien)
{
	return CSWeaponBits:GetEntData(client, CSPlayerOffsets[iSecondaryAddon]);
}

stock CSPlayer_SetSecondaryAddonBit(client, CSWeaponBits:bit)
{
	SetEntData(client, CSPlayerOffsets[iSecondaryAddon], _:bit, _, true);
}

stock CSPlayer_GetActiveWeapon(client)
{
	return GetEntDataEnt2(client, CSPlayerOffsets[iActiveWeapon]);
}

stock CSPlayer_SetActiveWeapon(client, weapon)
{
	SetEntDataEnt2(client, CSPlayerOffsets[iActiveWeapon], weapon, true);
}

stock CSPlayer_GetProgressBarDuration(client)
{
	return GetEntData(client, CSPlayerOffsets[iProgressBar]);
}

stock CSPlayer_SetProgressBarDuration(client, duration)
{
	SetEntData(client, CSPlayerOffsets[iProgressBar], duration, _, true);
}

stock Float:CSPlayer_GetProgressBarStartTime(client)
{
	return GetEntDataFloat(client, CSPlayerOffsets[flProgressBarStartTime]);
}

stock CSPlayer_SetProgressBarStartTime(client, Float:time)
{
	SetEntDataFloat(client, CSPlayerOffsets[flProgressBarStartTime], time, true);
}

stock CSPlayer_GetObserverTarget(client)
{
	return GetEntDataEnt2(client, CSPlayerOffsets[iObserverTarget]);
}

stock CSPlayer_SetObserverTarget(client, target)
{
	SetEntDataEnt2(client, CSPlayerOffsets[iObserverTarget], target, true);
}




stock CSWeapon_GetClip(weapon)
{
	return GetEntData(weapon, CSWeaponOffsets[iClip]);
}

stock CSWeapon_SetClip(weapon, clip)
{
	SetEntData(weapon, CSWeaponOffsets[iClip], clip, _, true);
}

stock CSWeapon_GetClip2(weapon)
{
	return GetEntData(weapon, CSWeaponOffsets[iClip2]);
}

stock CSWeapon_SetClip2(weapon, clip)
{
	SetEntData(weapon, CSWeaponOffsets[iClip2], clip, _, true);
}

stock CSWeapon_GetAmmoCount(weapon)
{
	//return GetEntData(weapon, CSWeaponOffsets[iAmmoCount]);
	return Weapon_GetPrimaryAmmoCount(weapon);
}

stock CSWeapon_SetAmmoCount(weapon, ammo)
{
	//SetEntData(weapon, CSWeaponOffsets[iAmmoCount], ammo, _, true);
	Weapon_SetPrimaryAmmoCount(weapon, ammo);
}

stock CSWeapon_GetPredictID(weapon)
{
	return GetEntData(weapon, CSWeaponOffsets[PredictID]);
}

stock CSWeapon_SetPredictID(weapon, id)
{
	SetEntData(weapon, CSWeaponOffsets[PredictID], id, _, true);
}

stock Float:CSWeapon_GetNextPrimaryAttack(weapon)
{
	return GetEntDataFloat(weapon, CSWeaponOffsets[flNextPrimaryAttack]);
}

stock CSWeapon_SetNextPrimaryAttack(weapon, Float:attack)
{
	SetEntDataFloat(weapon, CSWeaponOffsets[flNextPrimaryAttack], attack, true);
}

stock Float:CSWeapon_GetNextSecondaryAttack(weapon)
{
	return GetEntDataFloat(weapon, CSWeaponOffsets[flNextSecondaryAttack]);
}

stock CSWeapon_SetNextSecondaryAttack(weapon, Float:attack)
{
	SetEntDataFloat(weapon, CSWeaponOffsets[flNextSecondaryAttack], attack, true);
}




stock CSGrenadeProjectile_GetTeam(grenade)
{
	return GetEntData(grenade, CSGrenOffsets[iTeam]);
}

stock CSGrenadeProjectile_SetTeam(grenade, team)
{
	SetEntData(grenade, CSGrenOffsets[iTeam], team, _, true);
}

stock CSGrenadeProjectile_GetOwner(grenade)
{
	return GetEntDataEnt2(grenade, CSGrenOffsets[iGrenOwner]);
}

stock CSGrenadeProjectile_SetOwner(grenade, owner)
{
	SetEntDataEnt2(grenade, CSGrenOffsets[iGrenOwner], owner, true);
}

stock CSGrenadeProjectile_GetOwner2(grenade)
{
	return GetEntDataEnt2(grenade, CSGrenOffsets[iThrower]);
}

stock CSGrenadeProjectile_SetOwner2(grenade, owner)
{
	SetEntDataEnt2(grenade, CSGrenOffsets[iThrower], owner, true);
}

stock CSGrenadeProjectile_GetMins(grenade, Float:Mins[3])
{
	GetEntDataVector(grenade, CSGrenOffsets[vec_Mins], Mins);
}

stock CSGrenadeProjectile_SetMins(grenade, const Float:Mins[3])
{
	SetEntDataVector(grenade, CSGrenOffsets[vec_Mins], Mins);
}

stock CSGrenadeProjectile_GetMaxs(grenade, Float:Maxs[3])
{
	GetEntDataVector(grenade, CSGrenOffsets[vec_Maxs], Maxs);
}

stock CSGrenadeProjectile_SetMaxs(grenade, const Float:Maxs[3])
{
	SetEntDataVector(grenade, CSGrenOffsets[vec_Maxs], Maxs);
}

stock CSGrenadeProjectile_GetOrigin(grenade, Float:Origin[3])
{
	GetEntDataVector(grenade, CSGrenOffsets[vec_Origin], Origin);
}

stock CSGrenadeProjectile_SetOrigin(grenade, const Float:Origin[3])
{
	SetEntDataVector(grenade, CSGrenOffsets[vec_Origin], Origin);
}

stock CSGrenadeProjectile_GetVelocity(grenade, Float:Velocity[3])
{
	GetEntDataVector(grenade, CSGrenOffsets[vec_Velocity], Velocity);
}

stock CSGrenadeProjectile_SetVelocity(grenade, const Float:Velocity[3])
{
	SetEntDataVector(grenade, CSGrenOffsets[vec_Velocity], Velocity);
}

stock CSGrenadeProjectile_GetAngles(grenade, Float:Angles[3])
{
	GetEntDataVector(grenade, CSGrenOffsets[vec_Angles], Angles);
}

stock CSGrenadeProjectile_SetAngles(grenade, const Float:Angles[3])
{
	SetEntDataVector(grenade, CSGrenOffsets[vec_Angles], Angles);
}

stock Float:CSGrenadeProjectile_GetElasticity(grenade)
{
	return GetEntDataFloat(grenade, CSGrenOffsets[flElasticity]);
}

stock CSGrenadeProjectile_SetElasticity(grenade, Float:elasticity)
{
	SetEntDataFloat(grenade, CSGrenOffsets[flElasticity], elasticity, true);
}








stock CSViewModel_GetSequence(entity)
{
	return GetEntData(entity, CSViewModelOffsets[iSequence]);
}

stock CSViewModel_SetSequence(entity, sequence)
{
	SetEntData(entity, CSViewModelOffsets[iSequence], sequence, _, true);
}

stock Float:CSViewModel_GetCycle(entity)
{
	new offset = FindDataMapOffs(entity, "m_flCycle");
	if (offset != -1)
	{
		return GetEntDataFloat(entity, offset);
	}
	return -1.0;
}

stock CSViewModel_SetCycle(entity, Float:cycle)
{
	new offset = FindDataMapOffs(entity, "m_flCycle");
	if (offset != -1)
	{
		SetEntDataFloat(entity, offset, cycle, true);
	}
}

stock CSViewModel_GetEffects(entity)
{
	return GetEntData(entity, CSViewModelOffsets[fEffects]);
}

stock CSViewModel_SetEffects(entity, effects)
{
	SetEntData(entity, CSViewModelOffsets[fEffects], effects, _, true);
}

stock CSViewModel_AddEffects(entity, effect)
{
	new effects = CSViewModel_GetEffects(entity);
	if (effects & effect)
	{
		return;
	}
	effects |= effect;
	CSViewModel_SetEffects(entity, effects);
}

stock CSViewModel_RemoveEffects(entity, effect)
{
	new effects = CSViewModel_GetEffects(entity);
	if (!(effects & effect))
	{
		return;
	}
	effects &= ~effect;
	CSViewModel_SetEffects(entity, effects);
}

stock Float:CSViewModel_GetPlaybackRate(entity)
{
	return GetEntDataFloat(entity, CSViewModelOffsets[flPlaybackRate]);
}

stock CSViewModel_SetPlaybackRate(entity, Float:rate)
{
	SetEntDataFloat(entity, CSViewModelOffsets[flPlaybackRate], rate, true);
}

stock CSViewModel_GetModelIndex(entity)
{
	return GetEntData(entity, CSViewModelOffsets[iModelIndex]);
}

stock CSViewModel_SetModelIndex(entity, index)
{
	SetEntData(entity, CSViewModelOffsets[iModelIndex], index, _, true);
}

stock CSViewModel_GetViewModelIndex(entity)
{
	return GetEntData(entity, CSViewModelOffsets[iViewModelIndex]);
}

stock CSViewModel_SetViewModelIndex(entity, index)
{
	SetEntData(entity, CSViewModelOffsets[iViewModelIndex], index, _, true);
}

stock CSViewModel_GetOwner(entity)
{
	return GetEntDataEnt2(entity, CSViewModelOffsets[iOwner]);
}

stock CSViewModel_SetOwner(entity, owner)
{
	SetEntDataEnt2(entity, CSViewModelOffsets[iOwner], owner, true);
}

stock CSViewModel_GetWeapon(entity)
{
	return GetEntDataEnt2(entity, CSViewModelOffsets[iWeapon]);
}

stock CSViewModel_SetWeapon(entity, weapon)
{
	SetEntDataEnt2(entity, CSViewModelOffsets[iWeapon], weapon, true);
}
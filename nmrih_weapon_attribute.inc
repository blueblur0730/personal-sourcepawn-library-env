/** Double-include prevention */
#if defined _nmrih_weapon_attribute_included
    #endinput
#endif
#define _nmrih_weapon_attribute_included

#define ITEM_FLAG_SELECTONEMPTY		(1<<0)
#define ITEM_FLAG_NOAUTORELOAD		(1<<1)
#define ITEM_FLAG_LIMITINWORLD		(1<<3)
#define ITEM_FLAG_EXHAUSTIBLE		(1<<4)	// A player can totally exhaust their ammo supply and lose this weapon
#define ITEM_FLAG_DOHITLOCATIONDMG	(1<<5)	// This weapon take hit location into account when applying damage
#define ITEM_FLAG_NOAMMOPICKUPS		(1<<6)	// Don't draw ammo pickup sprites/sounds when ammo is received
#define ITEM_FLAG_NOITEMPICKUP		(1<<7)	// Don't draw weapon pickup when this weapon is picked up by the player

// nmrih specific flags.
#define ITEM_FLAG_SKILLSHOT			(1<<8)	// This weapon can perform a skillshot, charging when aim downsight.
#define ITEM_FLAG_PENETRATION		(1<<9)	// This weapon can penetrate multiple enemies at once.

native int GetNumWeaponInfoSlots();
native int LookupWeaponInfoSlot(const char[] szWeaponName);
native void GetWeaponInfoName(int iWeaponInfoSlot, char[] szWeaponName, int iBufferSize);

// all these dataes are effective globally, not for a single weapon entity.
// restart the map after editing the values.
// the values you changed will remain all the time until the ruleset is reloaded.
methodmap CSDKWeaponInfo {

    public static native CSDKWeaponInfo FromIndex(int iWeaponInfoSlot);

    // the name is their classname.
    public static native CSDKWeaponInfo FromName(const char[] szWeaponName);

    property bool bParsedScript {
        public native get();
        public native set(bool value);
    }

    property bool bLoadedHudElements {
        public native get();
        public native set(bool value);
    }

    property int iSlot {
        public native get();
        public native set(int value);
    }

    property int iPosition {
        public native get();
        public native set(int value);
    }

    property int iMaxClip1 {
        public native get();
        public native set(int value);
    }

    property int iMaxClip2 {
        public native get();
        public native set(int value);
    }

    property int iDefaultClip1 {
        public native get();
        public native set(int value);
    }

    property int iDefaultClip2 {
        public native get();
        public native set(int value);
    }

    property int iWeight {
        public native get();
        public native set(int value);
    }

    property int iMaxThrowForce {
        public native get();
        public native set(int value);
    }

    property int iRumbleEffect {
        public native get();
        public native set(int value);
    }

    property bool bAutoSwitchTo {
        public native get();
        public native set(bool value);
    }

    property bool bAutoSwitchFrom {
        public native get();
        public native set(bool value);
    }

    property int iFlags {
        public native get();
        public native set(int value);
    }

    property int iAmmoType {
        public native get();
        public native set(int value);
    }

    property int iAmmo2Type {
        public native get();
        public native set(int value);
    }

    property bool bMeleeWeapon {
        public native get();
        public native set(bool value);
    }

    property bool bBuiltRightHanded {
        public native get();
        public native set(bool value);
    }

    property bool bAllowFlipping {
        public native get();
        public native set(bool value);
    }

    property int m_iNumClips {
        public native get();
        public native set(int value);
    }

    property int m_iDamage {
        public native get();
        public native set(int value);
    }

    property int m_iBullets {
        public native get();
        public native set(int value);
    }

    property float m_flCycleTime {
        public native get();
        public native set(float value);
    }
    
    property float m_flCycleTimeBurst {
        public native get();
        public native set(float value);
    }

    property int m_iHeadShotDamage {
        public native get();
        public native set(int value);
    }

    property float m_flQuickAttackStaminaCost {
        public native get();
        public native set(float value);
    }

    property int m_iHafAmmoThreshold {
        public native get();
        public native set(int value);
    }

    property int m_iOverHalfAmmoThreshold {
        public native get();
        public native set(int value);
    }

    property int m_iAlmostFullAmmoThreshold {
        public native get();
        public native set(int value);
    }

    property int m_iFullAmmoThreshold {
        public native get();
        public native set(int value);
    }

    property int m_iMuzzelSmokeCount {
        public native get();
        public native set(int value);
    }

    property float m_flMuzzleSmokeTime {
        public native get();
        public native set(float value);
    }

    property bool m_bAllowSuicide {
        public native get();
        public native set(bool value);
    }

    property int m_iDamageType {
        public native get();
        public native set(int value);
    }

    property float m_flFOV {
        public native get();
        public native set(float value);
    }

    // the length are defined.
    public native void GetClassName(char[] szBuffer, int iBufferSize = 80);
    public native void GetPrintName(char[] szBuffer, int iBufferSize = 80);
    public native void GetViewModel(char[] szBuffer, int iBufferSize = 80);
    public native void GetWorldModel(char[] szBuffer, int iBufferSize = 80);
    public native void GetNPCModel(char[] szBuffer, int iBufferSize = 80);
    public native void GetAnimationPrefix(char[] szBuffer, int iMaxLen = 80);
    public native void GetAmmo1(char[] szBuffer, int iBufferSize = 80);
    public native void GetAmmo2(char[] szBuffer, int iBufferSize = 80);
    //public native void GetShotSounds(char[][] szBuffer, int iNumShotSoundTypes = 16, int iBufferSize = 80);
    public native void GetAnimationExtension(char[] szBuffer, int iBufferSize = 16);
    public native void GetMuzzleFlash(char[] szBuffer, int iBufferSize = 32);
    public native void GetSwingTrailParticleName(char[] szBuffer, int iBufferSize = 32);
    public native void GetSuicideParticle(char[] szBuffer, int iBufferSize = 32);

    public native void SetClassName(const char[] szClassName);
    public native void SetPrintName(const char[] szPrintName);
    public native void SetViewModel(const char[] szViewModel);
    public native void SetWorldModel(const char[] szWorldModel);
    public native void SetNPCModel(const char[] szNPCModel);
    public native void SetAnimationPrefix(const char[] szAnimationPrefix);
    public native void SetAmmo1(const char[] szAmmo1);
    public native void SetAmmo2(const char[] szAmmo2);
    //public native void SetShotSounds(const char[][] szShotSounds, int iNumShotSoundTypes = 16, int iBufferSize = 80);
    public native void SetAnimationExtension(const char[] szAnimationExtension);
    public native void SetMuzzleFlash(const char[] szMuzzleFlash);
    public native void SetSwingTrailParticleName(const char[] szSwingTrailParticleName);
    public native void SetSuicideParticle(const char[] szSuicideParticle);
}

/**
 * Do not edit below this line!
 */
public SharedPlugin __pl_nmrih_weapopn_attribute =
{
    name = "NMRiH Weapon Attribute",
    file = "nmrih_weapon_attribute.smx",
#if defined REQUIRE_PLUGIN
    required = 1,
#else
    required = 0,
#endif
};


#if !defined REQUIRE_PLUGIN
public void __pl_nmrih_weapopn_attribute_SetNTVOptional()
{
    MarkNativeAsOptional("GetNumWeaponInfoSlots");
    MarkNativeAsOptional("LookupWeaponInfoSlot");
    MarkNativeAsOptional("GetWeaponInfoName"); 
    MarkNativeAsOptional("CSDKWeaponInfo.FromIndex");
    MarkNativeAsOptional("CSDKWeaponInfo.FromName");
    MarkNativeAsOptional("CSDKWeaponInfo.bParsedScript.get");
    MarkNativeAsOptional("CSDKWeaponInfo.bParsedScript.set");
    MarkNativeAsOptional("CSDKWeaponInfo.bLoadedHudElements.get");
    MarkNativeAsOptional("CSDKWeaponInfo.bLoadedHudElements.set");
    MarkNativeAsOptional("CSDKWeaponInfo.iDefaultClip1.get");
    MarkNativeAsOptional("CSDKWeaponInfo.iDefaultClip1.set");
    MarkNativeAsOptional("CSDKWeaponInfo.iDefaultClip2.get");
    MarkNativeAsOptional("CSDKWeaponInfo.iDefaultClip2.set");
    MarkNativeAsOptional("CSDKWeaponInfo.iWeight.get");
    MarkNativeAsOptional("CSDKWeaponInfo.iWeight.set");
    MarkNativeAsOptional("CSDKWeaponInfo.iMaxThrowForce.get");
    MarkNativeAsOptional("CSDKWeaponInfo.iMaxThrowForce.set");
    MarkNativeAsOptional("CSDKWeaponInfo.iRumbleEffect.get");
    MarkNativeAsOptional("CSDKWeaponInfo.iRumbleEffect.set");
    MarkNativeAsOptional("CSDKWeaponInfo.bAutoSwitchTo.get");
    MarkNativeAsOptional("CSDKWeaponInfo.bAutoSwitchTo.set");
    MarkNativeAsOptional("CSDKWeaponInfo.bAutoSwitchFrom.get");
    MarkNativeAsOptional("CSDKWeaponInfo.bAutoSwitchFrom.set");
    MarkNativeAsOptional("CSDKWeaponInfo.iFlags.get");
    MarkNativeAsOptional("CSDKWeaponInfo.iFlags.set");
    MarkNativeAsOptional("CSDKWeaponInfo.iAmmoType.get");
    MarkNativeAsOptional("CSDKWeaponInfo.iAmmoType.set");
    MarkNativeAsOptional("CSDKWeaponInfo.iAmmo2Type.get");
    MarkNativeAsOptional("CSDKWeaponInfo.iAmmo2Type.set");
    MarkNativeAsOptional("CSDKWeaponInfo.bMeleeWeapon.get");
    MarkNativeAsOptional("CSDKWeaponInfo.bMeleeWeapon.set");
    MarkNativeAsOptional("CSDKWeaponInfo.bBuiltRightHanded.get");
    MarkNativeAsOptional("CSDKWeaponInfo.bBuiltRightHanded.set");
    MarkNativeAsOptional("CSDKWeaponInfo.bAllowFlipping.get");
    MarkNativeAsOptional("CSDKWeaponInfo.bAllowFlipping.set");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iNumClips.get");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iNumClips.set");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iDamage.get");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iDamage.set");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iBullets.get");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iBullets.set");
    MarkNativeAsOptional("CSDKWeaponInfo.m_flCycleTime.get");
    MarkNativeAsOptional("CSDKWeaponInfo.m_flCycleTime.set");
    MarkNativeAsOptional("CSDKWeaponInfo.m_flCycleTimeBurst.get");
    MarkNativeAsOptional("CSDKWeaponInfo.m_flCycleTimeBurst.set");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iHeadShotDamage.get");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iHeadShotDamage.set");
    MarkNativeAsOptional("CSDKWeaponInfo.m_flQuickAttackStaminaCost.get");
    MarkNativeAsOptional("CSDKWeaponInfo.m_flQuickAttackStaminaCost.set");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iHafAmmoThreshold.get");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iHafAmmoThreshold.set");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iOverHalfAmmoThreshold.get");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iOverHalfAmmoThreshold.set");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iAlmostFullAmmoThreshold.get");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iAlmostFullAmmoThreshold.set");
    MarkNativeAsOptional("CSDKWeaponInfo.m_bAllowSuicide.get");
    MarkNativeAsOptional("CSDKWeaponInfo.m_bAllowSuicide.set");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iFullAmmoThreshold.get");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iFullAmmoThreshold.set");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iMuzzelSmokeCount.get");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iMuzzelSmokeCount.set");
    MarkNativeAsOptional("CSDKWeaponInfo.m_flMuzzleSmokeTime.get");
    MarkNativeAsOptional("CSDKWeaponInfo.m_flMuzzleSmokeTime.set");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iDamageType.get");
    MarkNativeAsOptional("CSDKWeaponInfo.m_iDamageType.set");
    MarkNativeAsOptional("CSDKWeaponInfo.m_flFOV.get");
    MarkNativeAsOptional("CSDKWeaponInfo.m_flFOV.set");

    MarkNativeAsOptional("CSDKWeaponInfo.GetClassName");
    MarkNativeAsOptional("CSDKWeaponInfo.SetClassName");
    MarkNativeAsOptional("CSDKWeaponInfo.GetPrintName");
    MarkNativeAsOptional("CSDKWeaponInfo.SetPrintName");
    MarkNativeAsOptional("CSDKWeaponInfo.GetViewModel");
    MarkNativeAsOptional("CSDKWeaponInfo.SetViewModel");
    MarkNativeAsOptional("CSDKWeaponInfo.GetWorldModel");
    MarkNativeAsOptional("CSDKWeaponInfo.SetWorldModel");
    MarkNativeAsOptional("CSDKWeaponInfo.GetNPCModel");
    MarkNativeAsOptional("CSDKWeaponInfo.SetNPCModel");
    MarkNativeAsOptional("CSDKWeaponInfo.GetAnimationPrefix");
    MarkNativeAsOptional("CSDKWeaponInfo.SetAnimationPrefix");
    MarkNativeAsOptional("CSDKWeaponInfo.GetAmmo1");
    MarkNativeAsOptional("CSDKWeaponInfo.SetAmmo1");
    MarkNativeAsOptional("CSDKWeaponInfo.GetAmmo2");
    MarkNativeAsOptional("CSDKWeaponInfo.SetAmmo2");
    //MarkNativeAsOptional("CSDKWeaponInfo.GetShotSounds");
    //MarkNativeAsOptional("CSDKWeaponInfo.SetShotSounds");
    MarkNativeAsOptional("CSDKWeaponInfo.GetAnimationExtension");
    MarkNativeAsOptional("CSDKWeaponInfo.SetAnimationExtension");
    MarkNativeAsOptional("CSDKWeaponInfo.GetMuzzleFlash");
    MarkNativeAsOptional("CSDKWeaponInfo.SetMuzzleFlash");
    MarkNativeAsOptional("CSDKWeaponInfo.GetSwingTrailParticleName");
    MarkNativeAsOptional("CSDKWeaponInfo.SetSwingTrailParticleName");
    MarkNativeAsOptional("CSDKWeaponInfo.GetSuicideParticle");
    MarkNativeAsOptional("CSDKWeaponInfo.SetSuicideParticle");
}
#endif
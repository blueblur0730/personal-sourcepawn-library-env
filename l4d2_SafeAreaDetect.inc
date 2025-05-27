#pragma semicolon 1
#pragma newdecls required

forward void OnPlayerEnterSafeAreaPost(int client);

forward void OnPlayerLeftSafeAreaPost(int client);

native bool l4d2_IsClientInSafeArea(int client);

public SharedPlugin l4d2_SafeAreaDetect = 
{
	name = "l4d2_SafeAreaDetect", file = "l4d2_SafeAreaDetect.smx",
#if defined REQUIRE_PLUGIN
	required = 1,
#else
	required = 0,
#endif
};
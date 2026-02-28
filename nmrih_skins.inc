#if defined _nmrih_skins_included_
 #endinput
#endif
#define _nmrih_skins_included_

/**
 * Retrive the choosed model from this plugin.
 * 
 * @param client        Player index.
 * @param model         Buffer to store the player's model name.
 * @param maxlength     Maximum length of the model name.
 * 
 * @noreturn
*/
native void Skins_GetPlayerModel(int client, char[] model, int maxlength);

/**
 * Retrive the choosed turned model from this plugin.
 * 
 * @param client        Player index.
 * @param model         Buffer to store the player's model name.
 * @param maxlength     Maximum length of the model name.
 * 
 * @noreturn
*/
native void Skins_GetPlayerTurnedModel(int client, char[] model, int maxlength);

public SharedPlugin __pl_nmrih_skins = 
{
	name = "nmrih_skins",
	file = "nmrih_skins.smx",
#if defined REQUIRE_PLUGIN
	required = 1,
#else
	required = 0,
#endif
};
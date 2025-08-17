#include <YSI_Coding\y_hooks>

#define CP_ARMS (CP_JOBS_BEGIN) + JOB_TYPE_ARMS
#define ARMS_MATS (1000)

enum {
	MATS_OFFER_PLAYER, MATS_OFFER_PRICE, MATS_OFFER_AMOUNT
}

new
	materialSell[MAX_PLAYERS][3]; // 0 = MatsOffer[id] = playerid; 1 = MatsPrice[id] = price; MatsAmmo[id] = mats;

enum {
	GUN_OFFER_PLAYER, GUN_OFFER_PRICE, GUN_OFFER_GID
}

new
	weaponSell[MAX_PLAYERS][4];

cancel_arms_work(playerid)
{
	if(job_data[playerid][jobDuty] != JOB_TYPE_ARMS)
		return 1;
	// functia anpulea
	return 1;
}

reset_mats_vars(playerid)
{
	materialSell[playerid][MATS_OFFER_PLAYER] = INVALID_PLAYER_ID;
	materialSell[playerid][MATS_OFFER_AMOUNT] = 0;
	materialSell[playerid][MATS_OFFER_PRICE] = 0;
}

reset_gun_vars(playerid)
{
	weaponSell[playerid][GUN_OFFER_PLAYER] = INVALID_PLAYER_ID;
	weaponSell[playerid][GUN_OFFER_PRICE] = 0;
	weaponSell[playerid][GUN_OFFER_GID] = 0;
}

arms_returnGunAmmo(gunId)
{
	switch(gunId)
	{
		case 23: return 100;
		case 24: return 100;
		case 25: return 50;
		case 29: return 150;
		case 30: return 250;
		case 31: return 250;
		case 33: return 25;
	}
	return 0;
}

arms_returnGunCost(gunId)
{
	switch(gunId)
	{
		case 23: return 100;
		case 24: return 100;
		case 25: return 150;
		case 29: return 300;
		case 30: return 350;
		case 31: return 400;
		case 33: return 600;
	}
	return 0;
}

YCMD:matsinfo(playerid, params[], help)
{

	if(job_data[playerid][playerJob] != JOB_TYPE_ARMS)
		return SCM(playerid, -1, "You are not an Arms Dealer.");

	format(gString, sizeof gString, "Materials: [%d]", PlayerInfo[playerid][pMats]);
    Dialog_Show(playerid, DIALOG_MATSINSO, DIALOG_STYLE_MSGBOX, "Materials Information:", gString, "Close", "");
    return 1;
}

YCMD:getmats(playerid, params[], help)
{ 
	if(job_data[playerid][playerJob] != JOB_TYPE_ARMS)
		return SCM(playerid, -1, "You are not an Arms Dealer.");

    if(s_PlayerInfo[playerid][pSCP])
        return SCM(playerid, -1, "You can't use this command while you've an active checkpoint.");

    if(!IsPlayerInRangeOfPoint(playerid, 2.0, jobWorkLocations[JOB_TYPE_ARMS][0], jobWorkLocations[JOB_TYPE_ARMS][1], jobWorkLocations[JOB_TYPE_ARMS][2]))
    {
	    SCM(playerid, -1, "Mergi la checkpoint pentru a colecta materialele.");
	    
	    SetPlayerCheckpoint(playerid, jobWorkLocations[JOB_TYPE_ARMS][0], jobWorkLocations[JOB_TYPE_ARMS][1], jobWorkLocations[JOB_TYPE_ARMS][2], 10.0);
	    s_PlayerInfo[playerid][pSCP] = CP_ARMS;
	    return 1;
    }

    if(GetPlayerMoney(playerid) < 500)
    	return SCM(playerid, -1, "Nu ai $500.");

    SCM(playerid, -1, "Mergi la checkpoint pentru a colecta materialele.");
    GivePlayerMoney(playerid, -500);

    SetPlayerCheckpoint(playerid, 1713.1602, 916.2577, 10.8203, 2.0);
    s_PlayerInfo[playerid][pSCP] = CP_ARMS;

	WhenPlayerStartWorking(playerid);
	return 1;
}

YCMD:sellmaterials(playerid, params[], help)
{
	if(job_data[playerid][playerJob] != JOB_TYPE_ARMS)
		return SCM(playerid, -1, "You are not an Arms Dealer.");

	new
		targetid, iMats, iPrice;

    if(sscanf(params, "uii", targetid, iMats, iPrice))
    	return sendSyntax(playerid, "/sellmaterials <Name/Playerid> <Materials> <Price>");

	if(!IsPlayerConnected(targetid))
		return SCM(playerid, COLOR_GREY, "Player not connected.");

	if(iPrice < 1 || iPrice > 150000)
		return SCM(playerid, -1, "Price not lower then $1, or above $150,000.");

	if(playerid == targetid)
		return SCM(playerid, -1, "You can not sell yourself materials.");

	if(!IsPlayerInRangeOfPlayer(playerid, targetid, 5.0))
		return SCM(playerid, -1, "This player is not near you.");
	
	if(iMats < 1 || iMats > 50000)
		return SCM(playerid, -1, "Wrong materials ammount (1-50000).");
 
    if(iMats > PlayerInfo[playerid][pMats])
    	return SCM(playerid, -1, "You don't have so many materials to sell.");

	SCMF(playerid, -1, "{B8FFDB}* You offerd %s, %d materials for %s$.", GetName(targetid), iMats, FormatNumber(iPrice));
	SCMF(targetid, -1, "{B8FFDB}* %s offered you %d materials for %s$, (type /accept materials %d) to accept.", GetName(playerid), iMats, FormatNumber(iPrice), playerid);

	materialSell[targetid][MATS_OFFER_PLAYER] = playerid;
	materialSell[targetid][MATS_OFFER_AMOUNT] = iMats;
	materialSell[targetid][MATS_OFFER_PRICE] = iPrice;

    return 1;
}

accept_materials(playerid, targetid)
{
    if(materialSell[playerid][MATS_OFFER_PLAYER] == INVALID_PLAYER_ID)
        return SCM(playerid, -1, "No-one offerd you materials.");

    if(materialSell[playerid][MATS_OFFER_PLAYER] != targetid)
        return SCM(playerid, -1, "This player has not offered you materials.");
    
	if(!IsPlayerInRangeOfPlayer(playerid, targetid, 5.0))
		return SCM(playerid, -1, "This player is not near you.");

    if(GetPlayerMoney(playerid) < materialSell[playerid][MATS_OFFER_PRICE])
    	return SCM(playerid,-1,"You don't have money needed.");

    PlayerInfo[playerid][pMats] += materialSell[playerid][MATS_OFFER_AMOUNT];
    PlayerInfo[targetid][pMats] -= materialSell[playerid][MATS_OFFER_AMOUNT];

    GetPlayerMoney(playerid, -materialSell[playerid][MATS_OFFER_PRICE]);
    GetPlayerMoney(targetid, materialSell[playerid][MATS_OFFER_PRICE]);

    SCMF(playerid, -1, "{B8FFDB}You buy %d materials for $%s from %s.", materialSell[playerid][MATS_OFFER_AMOUNT], FormatNumber(materialSell[playerid][MATS_OFFER_PRICE]), GetName(targetid));
    SCMF(targetid, -1, "{B8FFDB}%s bought your materials for $%s.", GetName(playerid), FormatNumber(materialSell[playerid][MATS_OFFER_PRICE]));
     
	mysql_format(SQL, gString, sizeof gString, "update `users` set `Materials` = '%d' where `id` = '%d';", PlayerInfo[playerid][pMats], PlayerInfo[playerid][pSQLID]);
	mysql_tquery(SQL, gString, "", "");

	mysql_format(SQL, gString, sizeof gString, "update `users` set `Materials` = '%d' where `id` = '%d';", PlayerInfo[targetid][pMats], PlayerInfo[targetid][pSQLID]);
	mysql_tquery(SQL, gString, "", "");

	reset_mats_vars(playerid);

	return 1;
}

YCMD:sellgun(playerid, params[], help)
{
	if(job_data[playerid][playerJob] != JOB_TYPE_ARMS)
		return SCM(playerid, -1, "You are not an Arms Dealer.");

	new
		sellWeapon[12], weaponPrice, targetid;
	
	if(sscanf(params, "us[12]i", targetid, sellWeapon, weaponPrice))
	{
		sendSyntax(playerid, "/sellgun <Name/Playerid> <Gun Name> <Price>");
		SCM(playerid, -1, "*** Sell Guns ***");
		SCM(playerid, -1, "{B8DBFF}Weapons:{FFFFFF} SDPistol(100) Deagle(150)");
		SCM(playerid, -1, "{B8DBFF}Weapons:{FFFFFF} MP5(200) Shotgun(300)");
		SCM(playerid, -1, "{B8DBFF}Weapons:{FFFFFF} AK47(350) M4(400) Rifle(600)");
		return 1;
	}

	if(playerid == targetid)
		return SCM(playerid, -1, "You can not sell yourself weapons.");

	if(!IsPlayerConnected(targetid))
		return SCM(playerid, COLOR_GREY, "Player not connected.");

	if(PlayerInfo[targetid][pJailed] > 0)
		return SCM(playerid, -1, "This player is in jail.");

	if(PlayerInfo[targetid][pGunLic] == 0)
		return SCM(playerid, -1, "This player does not have arms license.");

	if(weaponPrice < 1 || weaponPrice > 100000)
		return SCM(playerid, -1, "{B8DBFF}Price must be between $1 and $100,000.");

	if(GetPlayerMoney(targetid) < weaponPrice)
		return SCM(playerid, -1, "{FFB870}This player don't have money needed.");

	if(strcmp(sellWeapon, "sdpistol", true) == 0)
	{
	    if(PlayerInfo[playerid][pMats] < 100)
	    	return SCM(playerid, -1, "Not enough Materials for that Weapon.");

	    weaponSell[targetid][GUN_OFFER_GID] = 23;
	}
	else if(strcmp(sellWeapon, "deagle", true) == 0)
	{
	    if(PlayerInfo[playerid][pMats] < 150)
	    	return SCM(playerid, -1, "Not enough Materials for that Weapon.");

	    weaponSell[targetid][GUN_OFFER_GID] = 24;
	}
	else if(strcmp(sellWeapon, "mp5", true) == 0)
	{
	    if(PlayerInfo[playerid][pMats] < 200)
	    	return SCM(playerid, -1, "Not enough Materials for that Weapon.");

	    weaponSell[targetid][GUN_OFFER_GID] = 29;
	}
	else if(strcmp(sellWeapon, "shotgun", true) == 0)
	{
	    if(PlayerInfo[playerid][pMats] < 300)
	    	return SCM(playerid, -1, "Not enough Materials for that Weapon.");

	    weaponSell[targetid][GUN_OFFER_GID] = 25;
	}
	else if(strcmp(sellWeapon, "ak47", true) == 0)
	{
	    if(PlayerInfo[playerid][pMats] < 350)
	    	return SCM(playerid, -1, "Not enough Materials for that Weapon.");

	    weaponSell[targetid][GUN_OFFER_GID] = 30;
	}
	else if(strcmp(sellWeapon, "m4", true) == 0)
	{
	    if(PlayerInfo[playerid][pMats] < 400)
	    	return SCM(playerid, -1, "Not enough Materials for that Weapon.");

	    weaponSell[targetid][GUN_OFFER_GID] = 31;
	}
	else if(strcmp(sellWeapon, "rifle", true) == 0)
	{
	    if(PlayerInfo[playerid][pMats] < 600)
	    	return SCM(playerid, -1, "Not enough Materials for that Weapon.");

	    weaponSell[targetid][GUN_OFFER_GID] = 33;
	}
	else return SCM(playerid, -1, "{B8DBFF}Invalid weapon name.");

	if(!IsPlayerInRangeOfPlayer(playerid, targetid, 5.0))
		return SCM(playerid, -1, "{FFFFCC}This player is not near you.");

    if(s_PlayerInfo[targetid][pSPlayerSpec] == playerid)
    	return SCM(playerid, -1, "{FFFFCC}This player is not near you.");

	SCMF(playerid, -1, "{B8FFDB}* You offerd %s %s for %s$.", GetName(targetid), GetWeaponNameID(weaponSell[targetid][GUN_OFFER_GID]), FormatNumber(weaponPrice));
	SCMF(targetid, -1, "{B8FFDB}* %s offered you %s for %s$, (type /accept gun %d) to accept.", GetName(playerid), GetWeaponNameID(weaponSell[targetid][GUN_OFFER_GID]), FormatNumber(weaponPrice), playerid);
    
    weaponSell[targetid][GUN_OFFER_PLAYER] = playerid;
    weaponSell[targetid][GUN_OFFER_PRICE] = weaponPrice;

	return 1;
}

accept_gun(playerid, targetid)
{
    if(weaponSell[playerid][GUN_OFFER_PLAYER] == INVALID_PLAYER_ID)
        return SCM(playerid, -1, "No-one offerd you gun.");

    if(weaponSell[playerid][GUN_OFFER_PLAYER] != targetid)
    	return SCM(playerid, -1, "This player has not offered you gun.");

	if(!IsPlayerInRangeOfPlayer(playerid, targetid, 5.0))
		return SCM(playerid, -1, "This player is not near you.");

    if(GetPlayerMoney(playerid) < weaponSell[playerid][GUN_OFFER_PRICE])
    	return SCM(playerid, -1, "You don't have money needed.");

    PlayerInfo[targetid][pMats] -= arms_returnGunCost(weaponSell[playerid][GUN_OFFER_GID]);

	GetPlayerMoney(playerid, -weaponSell[playerid][GUN_OFFER_PRICE]);
	GetPlayerMoney(targetid, weaponSell[playerid][GUN_OFFER_PRICE]);

	SCMF(playerid, COLOR_GREY, "You have recieved a %s with %d ammo from %s.", GetWeaponNameID(weaponSell[playerid][GUN_OFFER_GID]), arms_returnGunAmmo(weaponSell[playerid][GUN_OFFER_GID]), GetName(targetid));
	SCMF(targetid, COLOR_GREY, "You have given %s, a %s with %d ammo, for %d materials.", GetName(playerid), GetWeaponNameID(weaponSell[playerid][GUN_OFFER_GID]), arms_returnGunAmmo(weaponSell[playerid][GUN_OFFER_GID]), arms_returnGunCost(weaponSell[playerid][GUN_OFFER_GID]));

	format(gString, sizeof gString, "* %s created a gun from materials, and hands it to %s.", GetName(targetid), GetName(playerid));
	ProxDetector(30.0, playerid, gString, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

	GivePlayerWeaponEx(playerid, weaponSell[playerid][GUN_OFFER_GID], arms_returnGunAmmo(weaponSell[playerid][GUN_OFFER_GID]));

	mysql_format(SQL, gString, sizeof gString, "update `users` set `Materials` = '%d' where `id` = '%d';", PlayerInfo[targetid][pMats], PlayerInfo[targetid][pSQLID]);
	mysql_tquery(SQL, gString, "", "");

	reset_gun_vars(playerid);

	return 1;
}

hook OnPlayerSpawn(playerid)
{
	if(materialSell[playerid][MATS_OFFER_PLAYER] != INVALID_PLAYER_ID)
		reset_mats_vars(playerid);

	if(weaponSell[playerid][GUN_OFFER_PLAYER] != INVALID_PLAYER_ID)
		reset_gun_vars(playerid);

	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerConnect(playerid)
{
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnGameModeInit()
{
	Command_AddAltNamed("sellmaterials", "sellmats");
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterCheckpoint(playerid)
{
	if(s_PlayerInfo[playerid][pSCP] == CP_ARMS)
	{
		s_PlayerInfo[playerid][pSCP] = 0;
		DisablePlayerCheckpoint(playerid);

		if(job_data[playerid][jobDuty] == JOB_TYPE_NONE)
		{
			s_PlayerInfo[playerid][pSCP] = 0;
		    DisablePlayerCheckpoint(playerid);

		    SCM(playerid, COLOR_YELLOW, "Foloseste /getmats aici pentru a colecta materiale.");
		}
		else
		{
			new
				job_mats = (ARMS_MATS) + (job::returnPlayerSkill(playerid, JOB_TYPE_ARMS) * 100 + RandomEx((job::returnPlayerSkill(playerid, JOB_TYPE_ARMS) * 100), (job::returnPlayerSkill(playerid, JOB_TYPE_ARMS) * 100) + 100));
			
			SCMF(playerid, -1, "Ai colectat %s materiale.", FormatNumber(job_mats));

			PlayerInfo[playerid][pMats] += job_mats;
			job::updateJobSkill(playerid, JOB_TYPE_ARMS);

			DailyQuestCheck(playerid, QUEST_TYPE_MATS, job_mats);

			mysql_format(SQL, gString, sizeof gString, "update `users` set `Materials` = '%d' where `id` = '%d';", PlayerInfo[playerid][pMats], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(SQL, gString, "", "");
			
			stop_job_work(playerid);
		}
	} 
	return Y_HOOKS_CONTINUE_RETURN_1;
}
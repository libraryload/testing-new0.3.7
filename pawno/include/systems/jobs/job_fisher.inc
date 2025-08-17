#include <YSI_Coding\y_hooks>

enum e_fisher {
	playerHaveFish, playerFishType, playerFishPrice, playerFishTimer
};
new fish_data[MAX_PLAYERS][e_fisher];

hook OnPlayerConnect(playerid)
{
	fish_data[playerid][playerHaveFish] = 0;
	fish_data[playerid][playerFishType] = 0;
	fish_data[playerid][playerFishPrice] = 0;

	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(fish_data[playerid][playerHaveFish])
	{
		SCM(playerid, COLOR_GREEN, "Deoarece ai murit ai pierdut pestele pe care il aveai in inventar.");
		reset_fish_vars(playerid);
	}
}

YCMD:fish(playerid, params[], help)
{
	if(job_data[playerid][playerJob] != JOB_TYPE_FISHER) 
		return SCM(playerid, -1, "You are not a fisherman.");
	
	if(!IsPlayerInRangeOfPoint(playerid, 3.5, jobWorkLocations[JOB_TYPE_FISHER][0], jobWorkLocations[JOB_TYPE_FISHER][1], jobWorkLocations[JOB_TYPE_FISHER][2]) || IsPlayerInAnyVehicle(playerid))
		return SCM(playerid, -1, "You are not in the fishing zone. [/jobs > Fisherman]");

    if(fish_data[playerid][playerHaveFish])
    	return SCM(playerid, -1, "Mergi la un magazin 24/7 pentru a vinde pestele prins inainte de a pescui din nou.");

	if(job_data[playerid][jobDuty] == JOB_TYPE_FISHER)
		return SCM(playerid, -1, "You are already fishing.");

	TogglePlayerControllable(playerid, 0);
	SetPlayerAttachedObject(playerid, JOB_INDEX, 18632, 5, 0.217000, 0.089999, -0.139999, -34.000007, 5.899998, -61.399993);
	ApplyAnimation(playerid, "SAMP", "FishingIdle", 4.0, 0, 1, 1, 1, 0, 1);

	WhenPlayerStartWorking(playerid);

	SCM(playerid, -1, "You're now fishing. It will take a few seconds to reel your fish in.");
	GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~w~FISHING...", 10000, 5);

	fish_data[playerid][playerFishTimer] = SetTimerEx("catch_fish", 10000, 0, "d", playerid);
	return 1;
}

reset_fish_vars(playerid)
{
	fish_data[playerid][playerHaveFish] = 0;
	fish_data[playerid][playerFishType] = 0;
	fish_data[playerid][playerFishPrice] = 0;
	fish_data[playerid][playerFishTimer] = 0; 
}

cancel_fish_work(playerid)
{
	if(job_data[playerid][playerJob] != JOB_TYPE_FISHER)
		return 1;

	reset_fish_vars(playerid);

	return 1;
}

returnFishName(playerid, fish_type, action)
{
 	new
 		fishString[24];

 	if(action == 1)
 	{
	 	switch(fish_type)
	 	{
	 		case 1:
	 		{
	 			if(PlayerInfo[playerid][pLanguage] == 1)
	 				fishString = "common";
	 			else if(PlayerInfo[playerid][pLanguage] == 2)
	 				fishString = "obisnuit";
	 		}
	 		case 2:
	 		{
	 			if(PlayerInfo[playerid][pLanguage] == 1)
	 				fishString = "rare";
	 			else if(PlayerInfo[playerid][pLanguage] == 2)
	 				fishString = "rar";
	 		} 
	 		case 3:
	 		{
	 			#if !defined HOLIDAY_ACTIVE
		 			if(PlayerInfo[playerid][pLanguage] == 1)
		 				fishString = "very rare";
		 			else if(PlayerInfo[playerid][pLanguage] == 2)
		 				fishString = "foarte rar";
		 		#else
		 			if(PlayerInfo[playerid][pLanguage] == 1)
		 				fishString = "special christmas";
		 			else if(PlayerInfo[playerid][pLanguage] == 2)
		 				fishString = "special de Craciun";
		 		#endif
	 		}
	 	}
	}
	else if(action == 2)
	{
	 	switch(fish_type)
	 	{
	 		case 1: fishString = "common";
	 		case 2: fishString = "rare";
	 		case 3:
	 		{
	 			#if !defined HOLIDAY_ACTIVE
		 			fishString = "very rare";
		 		#else
		 			fishString = "special christmas";
		 		#endif
	 		}
	 	}
	}
 	return fishString;
}

returnFishPrice(fish_type)
{
	new
		fish_value=0;

	switch(fish_type)
	{
		case 1: fish_value = 10000 + RandomEx(100, 15000);
		case 2: fish_value = 30000 + RandomEx(100, 10000);
		case 3:
		{
			#if !defined HOLIDAY_ACTIVE
				fish_value = 100000 + RandomEx(100, 100000);
			#else
				fish_value = 500000 + RandomEx(100, 500000);
			#endif
		}
	}
	return fish_value;
}

function catch_fish(playerid)
{
	if(job_data[playerid][jobDuty] == JOB_TYPE_FISHER)
	{
		TogglePlayerControllable(playerid, 1);
		stop_job_work(playerid);

		give_fish_money(playerid);
	}
	return 1;
}

give_fish_money(playerid)
{
 	new
 		random_fish = random(99);

 	switch(job_data[playerid][playerJobSkill][JOB_TYPE_FISHER])
 	{
 		case 1: {
			if(random_fish >= 0 && random_fish <= 87) fish_data[playerid][playerFishType] = 1;
			else if(random_fish >= 88 && random_fish <= 98) fish_data[playerid][playerFishType] = 2;
			else if(random_fish >= 99) fish_data[playerid][playerFishType] = 3;
 		}
 		case 2: {
			if(random_fish >= 0 && random_fish <= 83) fish_data[playerid][playerFishType] = 1;
			else if(random_fish >= 84 && random_fish <= 97) fish_data[playerid][playerFishType] = 2;
			else if(random_fish >= 98) fish_data[playerid][playerFishType] = 3;
 		}
 		case 3: {
			if(random_fish >= 0 && random_fish <= 79) fish_data[playerid][playerFishType] = 1;
			else if(random_fish >= 80 && random_fish <= 96) fish_data[playerid][playerFishType] = 2;
			else if(random_fish >= 97) fish_data[playerid][playerFishType] = 3;
 		}
 		case 4: {
			if(random_fish >= 0 && random_fish <= 75) fish_data[playerid][playerFishType] = 1;
			else if(random_fish >= 76 && random_fish <= 95) fish_data[playerid][playerFishType] = 2;
			else if(random_fish >= 96) fish_data[playerid][playerFishType] = 3;
 		}
 		case 5: {
			if(random_fish >= 0 && random_fish <= 71) fish_data[playerid][playerFishType] = 1;
			else if(random_fish >= 72 && random_fish <= 94) fish_data[playerid][playerFishType] = 2;
			else if(random_fish >= 95) fish_data[playerid][playerFishType] = 3;
 		}
 		case 6: {
			if(random_fish >= 0 && random_fish <= 67) fish_data[playerid][playerFishType] = 1;
			else if(random_fish >= 68 && random_fish <= 93) fish_data[playerid][playerFishType] = 2;
			else if(random_fish >= 94) fish_data[playerid][playerFishType] = 3;
 		}
 	}
 	fish_data[playerid][playerHaveFish] = 1;
 	fish_data[playerid][playerFishPrice] = returnFishPrice(fish_data[playerid][playerFishType]);

 	format(gString, sizeof gString, (PlayerInfo[playerid][pLanguage] == 1 ? ("You caught a %s fish!") : ("Ai prins un peste %s!")), returnFishName(playerid, fish_data[playerid][playerFishType], 1));
 	SCM(playerid, -1, gString);

 	format(gString, sizeof gString, (PlayerInfo[playerid][pLanguage] == 1 ? ("The value of the fish you caught is $%s!") : ("Pestele prins de tine valoreaza $%s!")), FormatNumber(fish_data[playerid][playerFishPrice]));
 	SCM(playerid, -1, gString);

 	SS(playerid, -1, "Pentru a vinde pestele, mergi la un magazin 24/7.", "To sell the fish, go to a 24/7 store.");

 	sendNearbyMessage(playerid, COLOR_YELLOW, "* %s caught a %s fish that can be sold for about $%s.", GetName(playerid), returnFishName(playerid, fish_data[playerid][playerFishType], 2), FormatNumber(fish_data[playerid][playerFishPrice]));

	return 1;
}

sell_fish(playerid)
{
	// se apeleaza in bussineses.inc
	if(fish_data[playerid][playerHaveFish])
		Dialog_Show(playerid, DIALOG_SELLFISH, DIALOG_STYLE_MSGBOX, "Sell fish", "Do you want to sell the fish you are carying?", "Yes", "No");
	return 1;
}

Dialog:DIALOG_SELLFISH(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	SCMF(playerid, COLOR_GREEN, "Ai vandut pestele pentru $%s.", FormatNumber(fish_data[playerid][playerFishPrice]));
	GivePlayerMoney(playerid, fish_data[playerid][playerFishPrice]);

	job::updateJobSkill(playerid, JOB_TYPE_FISHER);
	DailyQuestCheck(playerid, QUEST_TYPE_FISH, 1);

	reset_fish_vars(playerid);
	return 1;
}
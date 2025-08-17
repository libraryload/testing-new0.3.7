#include <YSI_Coding\y_hooks>


new PhoneOnline[MAX_PLAYERS],PhoneOnlineCalls[MAX_PLAYERS], Mobile[MAX_PLAYERS], CellTime[MAX_PLAYERS], LastPlayer[MAX_PLAYERS];


stock NumberUsed(playerid)
{
	new string[256];
	format(string, sizeof(string),"SELECT * FROM `users` WHERE `PhoneNr` = '%d'",PlayerInfo[playerid][pPnumber]);
	new Cache: result = mysql_query(SQL, string);
	if(cache_get_row_count() > 0)
	{
		cache_delete(result);
		return 1;
	}
	cache_delete(result);
	return 0;
}

YCMD:call(playerid, params[], help)
{
	
	new number,sendername[30],string[256],giveplayer[25];
	if(sscanf(params, "i",number)) return sendSyntax(playerid, "/call [number]");
	if(PlayerInfo[playerid][pPnumber] == 0) return SendClientMessage(playerid, -1, "You dont't have a phone.");
	if(!Iter_Contains(PhoneOnline, playerid)) return SendClientMessage(playerid, -1, "Your phone is turned off.");

	GetPlayerName(playerid, sendername, sizeof(sendername));
	/*if(number == 112)
	{
	    if(IsACop(playerid)) return SendClientMessage(playerid,COLOR_WHITE,"You are a cop.");
	    if(WantedReason[playerid] != 999)
	    {
	    	if(PlayerInfo[WantedID[playerid]][pJailTime] > 0) return SendClientMessage(playerid, -1, "This player is already in jail.");
	        new killerid = WantedID[playerid];
			if(killerid == INVALID_PLAYER_ID) return SendClientMessage(playerid, COLOR_WHITE, "Player not connected.");
            if(PlayerInfo[killerid][pWantedLevel] >= 6) return SendClientMessage(playerid, -1, "This player has got already maximum of wanted stars.");
			else WantedPoints[killerid] += 2;
            if(WantedPoints[killerid] > 13) WantedPoints[killerid] = 13;
			format(string,sizeof(string),"You reported %s for a crime.",GetName(killerid));
			SendClientMessage(playerid,COLOR_LIGHTBLUE,string);
			if(WantedReason[playerid] != 49) SetPlayerCriminal(killerid,playerid, "first degree murder");
			else if(WantedReason[playerid] == 49) SetPlayerCriminal(killerid,playerid, "hit and run");
			ClearWanted(playerid);
			return 1;
	    }
	}*/
	if(number == PlayerInfo[playerid][pPnumber]) return SendClientMessage(playerid, -1, "You can't call yourself.");
	if(Mobile[playerid] != -1) return SendClientMessage(playerid, -1, "You are already on a call.");
	foreach(new i : Player)
	{
		if(IsPlayerConnected(i))
		{
			if(PlayerInfo[i][pPnumber] == number && number != 0)
			{
				new giveplayerid = i;
				if(giveplayerid != INVALID_PLAYER_ID)
				{
				    if(PhoneOnline[giveplayerid] > 0) return SendClientMessage(playerid, -1, "That player phone is offline.");
					if(PhoneOnlineCalls[giveplayerid] > 0) return SendClientMessage(playerid, -1, "That player phone is offline for calls.");
					//if(PlayerInfo[giveplayerid][pPhoneBlocked][playerid] == 1) return SS(playerid, -1, "Playerul pe care incerci sa-l suni ti-a blocat numarul de telefon.", "The player you are trying to call has blocked your number. You can't contact him/her.");
					if(Mobile[giveplayerid] == -1)
					{
						Mobile[playerid] = giveplayerid;
						format(string, sizeof(string), "%s takes out their cellphone, and dials in a number.", sendername);
						ProxDetector(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
						PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);
						PlayerPlaySound(giveplayerid, 20600, 0.0, 0.0, 0.0);
						format(string, sizeof(string), "%s is calling you. Use /p(ickup) to answer your phone.", sendername);
						SendClientMessage(giveplayerid, COLOR_YELLOW, string);
						GetPlayerName(giveplayerid,giveplayer,sizeof(giveplayer));
						if(PlayerInfo[playerid][pPhone] == 0)
							SetPlayerAttachedObject(playerid,9,330,6, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000);
						else if(PlayerInfo[playerid][pPhone] == 1)
							SetPlayerAttachedObject(playerid, 9, 18865, 6, 0.086043, 0.027719, 0.003817, 95.232246, 178.651031, 1.691840, 1.002077, 1.000000, 1.000000); // MobilePhone1 - phone1
						if(PlayerInfo[giveplayerid][pPhone] == 0) format(string, sizeof(string), "%s's cellphone starts to ring...", giveplayer);
						else if(PlayerInfo[giveplayerid][pPhone] == 1) format(string, sizeof(string), "%s's iPhone starts to ring...", giveplayer);
						ProxDetector(20.0, giveplayerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
						CellTime[playerid] = 1;
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
						return 1;
					}
				}
			}
		}
	}
	SendClientMessage(playerid, COLOR_GRAD2, "(cellphone) *busy tone*");
	return 1; }


YCMD:sms(playerid, params[], help)
{
	new 
		iNumber, sMessage[254], targetID;
    
	checkPlayerMuteStatus(playerid);

	if(PlayerInfo[playerid][pPnumber] == 0) 
		return sendError(playerid, "You dont't have a cellphone.");

	if(!Iter_Contains(PhoneOnline, playerid)) 
		return sendError(playerid, "Your phone is turned off.");

	if(sscanf(params, "is[254]", iNumber, sMessage)) 
		return sendSyntax(playerid, "/sms <iNumber> <sMessage>");
	
	if(PlayerInfo[playerid][pPnumber] == iNumber)
		return sendError(playerid, "You can't send yourself an SMS.");

	foreach(new i : PhoneOnline)
	{
		if(PlayerInfo[i][pPnumber] == iNumber && iNumber != 0)
		{
			if(targetID == INVALID_PLAYER_ID)
				return sendError(playerid, "Disconnected user phone number.");

			targetID = i;

		    if(!Iter_Contains(PhoneOnline, targetID))
		    	return sendError(playerid, "The other player phone's turned off.");

		    //if(PlayerInfo[targetID][pPhoneBlocked][playerid] == 1) 
		    ///	return sendError(playerid, "Playerul caruia incerci sa ii trimiti SMS ti-a blocat numarul de telefon.");
			
			if(PlayerInfo[targetID][pAdmin] < 1) 
				format(gString, sizeof gString, "SMS from %s (%d): %s", GetName(playerid), PlayerInfo[playerid][pPnumber], sMessage);
			else 
				format(gString, sizeof gString, "SMS from %s (%d): %s", GetName(playerid), playerid, sMessage);
			
			SendSplitMessage(i, COLOR_YELLOW, gString);

			format(gString, sizeof gString, "SMS sent to %s (%d): %s", GetName(targetID), PlayerInfo[targetID][pPnumber], sMessage);
			SendSplitMessage(playerid, COLOR_TEAL, gString);

			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			PlayerPlaySound(targetID, 1139, 0.0, 0.0, 0.0);
			
			LastPlayer[targetID] = playerid;
		}
	}

	format(gString, sizeof(gString), "SMS from %s (%d) to %s (%d): %s", GetName(playerid), playerid, GetName(targetID), targetID, sMessage);
	//foreach(new i : Admins)
	//{
	//	if(BigEar[i])
	//		SendSplitMessage(i, COLOR_TEAL, gString);
	//}

	mysql_format(SQL, gString, sizeof gString, "insert into chat_logs (`playerid`, `text`, `where`) values ('%d', '[SMS] %s to %s: %s', 'sms')", PlayerInfo[playerid][pSQLID], GetName(playerid), GetName(targetID), sMessage);
	mysql_tquery(SQL, gString, "", "");
	return 1; 
}

YCMD:reply(playerid, params[], help)
{
    if(PlayerInfo[playerid][pPhone] != 1)
    	return sendError(playerid, "You don't have an iPhone!");

    if(LastPlayer[playerid] == -1)
    	return sendError(playerid, "Nobody has sent you an SMS!");
	
    new 
    	messageString[128];

	if(sscanf(params, "s[128]", messageString)) 
		return sendSyntax(playerid, "/reply <Text>");

	if(PhoneOnline[LastPlayer[playerid]] > 0) 
		return sendError(playerid, "This player have his phone turned off.");

	// if(PlayerInfo[LastPlayer[playerid]][pPhoneBlocked][playerid] == 1) 
		// return sendError(playerid, "Playerul caruia incerci sa ii trimiti SMS ti-a blocat numarul de telefon.");

	LastPlayer[LastPlayer[playerid]] = playerid;
	if(PlayerInfo[LastPlayer[playerid]][pAdmin] < 1 || PlayerInfo[playerid][pVIPAccount] < 1) 
		SCMF(LastPlayer[playerid], COLOR_YELLOW, "SMS from %s (%d): %s", GetName(playerid), PlayerInfo[playerid][pPnumber], messageString);
	else 
		SCMF(LastPlayer[playerid], COLOR_YELLOW, "SMS from %s (%d): %s", GetName(playerid), playerid, messageString);

	SCMF(playerid, COLOR_SMS, "SMS sent to %s (%d): %s", GetName(LastPlayer[playerid]), PlayerInfo[LastPlayer[playerid]][pPnumber], messageString);
	
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	PlayerPlaySound(LastPlayer[playerid], 1139, 0.0, 0.0, 0.0);

	mysql_format(SQL, gString, sizeof gString, "insert into `chat_logs` (`playerid`, `text`, `where`) values ('%d', '[SMS] %s to %s: %s', 'sms')", PlayerInfo[playerid][pSQLID], GetName(playerid), GetName(LastPlayer[playerid]), params);
	mysql_tquery(SQL, gString, "", "");

	// foreach(new i : Admins)
	// {
		// if(BigEar[i])
			// SCMF(i, COLOR_SMS, "{63969C}SMS from %s (%d) to %s (%d): %s", GetName(playerid), playerid, GetName(LastPlayer[playerid]), LastPlayer[playerid], messageString);
	// }
	return 1;
}

YCMD:speaker(playerid, params[], help)
{
	if(PlayerInfo[playerid][pPnumber] == 0)
		return sendError(playerid, "You don't have a phone.");

	if(Mobile[playerid] == -1 || Mobile[playerid] == -2 || Mobile[playerid] == -3 || Mobile[playerid] == -4)
		return 1;

	SCMF(playerid, -1, "Speaker is %s.", PlayerInfo[playerid][pSpeaker] == 0 ? "on" : "off");

	PlayerInfo[playerid][pSpeaker] = PlayerInfo[playerid][pSpeaker] == 1 ? 0 : 1;

	return 1;
}


YCMD:number(playerid, params[], help) 
{
	if(PlayerInfo[playerid][pPhoneBook] != 1)
		return sendError(playerid, "You do not have a phonebook.");

	new 
		targetID;

	if(sscanf(params, "u", targetID)) 
		return sendSyntax(playerid, "/number <Name/PlayerID>");

	if(!IsPlayerConnected(targetID))
		return sendError(playerid, "Invalid or unlogged player.");

	switch(PlayerInfo[targetID][pPnumber]) {
		case 0: SCMF(playerid, -1, "%s (%d) doesn't have a phone.", GetName(targetID), targetID);
		default: SCMF(playerid, -1, "%s (%d)'s phone number is {FF0000}%d{FFFFFF}", GetName(targetID), targetID, PlayerInfo[targetID][pPnumber]);
	}
	return 1; }

YCMD:pickup(playerid, params[], help)
{
	if(Mobile[playerid] != -1) 
		return sendError(playerid, "You are already on a call...");

	foreach(new i : PhoneOnline)
	{
		if(Mobile[i] == playerid)
		{
			SCM(i, -1, "The other person has answered the call.");
            SCM(playerid, -1, "You have answered your phone.");

			Mobile[playerid] = i;

			if(PlayerInfo[playerid][pPhone] == 0)
				SetPlayerAttachedObject(playerid,9,330,6, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000);
			else if(PlayerInfo[playerid][pPhone] == 1)
				SetPlayerAttachedObject(playerid, 9, 18865, 6, 0.086043, 0.027719, 0.003817, 95.232246, 178.651031, 1.691840, 1.002077, 1.000000, 1.000000);

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
			return 1;
		}
	}
	return 1; 
}

YCMD:hangup(playerid, params[], help)
{
	if(Mobile[playerid] != -1 && Mobile[playerid] != -2 && Mobile[playerid] != -3 && Mobile[playerid] != -4)
	{
		SCM(playerid, COLOR_WHITE, "You have terminated the current call.");
		if(Iter_Contains(PhoneOnline, Mobile[playerid]))
			SCM(Mobile[playerid], -1, "Your call has been terminated by the other party.");

		CellTime[Mobile[playerid]] = 0;
		CellTime[playerid] = 0;
		
		if(PlayerInfo[playerid][pSpeaker]) PlayerInfo[playerid][pSpeaker] = 0;

		SetPlayerSpecialAction(Mobile[playerid], SPECIAL_ACTION_STOPUSECELLPHONE);
		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
		
		RemovePlayerAttachedObject(Mobile[playerid], 9);
		RemovePlayerAttachedObject(playerid, 9);
		
		if(PlayerInfo[playerid][pPet] != 0 && PlayerInfo[playerid][pPetStatus] != 0)
			AttachPet(playerid);
		
		if(PlayerInfo[Mobile[playerid]][pPet] != 0 && PlayerInfo[Mobile[playerid]][pPetStatus] != 0)
			AttachPet(Mobile[playerid]);
		
		Mobile[Mobile[playerid]] = -1;
		Mobile[playerid] = -1;
		CellTime[playerid] = 0;
	}
	else
	{
		SCM(playerid, COLOR_WHITE, "You have terminated the current call.");
		
		RemovePlayerAttachedObject(playerid, 9);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
		
		Mobile[playerid] = -1;
		CellTime[playerid] = 0;
		PlayerInfo[playerid][pSpeaker] = 0;

		if(PlayerInfo[playerid][pPet] != 0 && PlayerInfo[playerid][pPetStatus] != 0)
			AttachPet(playerid);
	}
	return 1; 
}
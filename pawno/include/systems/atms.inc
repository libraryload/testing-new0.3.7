#include <YSI_Coding\y_hooks>

#define MAX_ATMS (30 + 1)

enum E_ATM_INFO
{
	idATM, Float: fATMPos[3], Float: fATMPosRot[3], rObjectId[3], ATMHealth, Text3D: ATMLabel, ATMRepairTime
};
new AtmInfo[MAX_ATMS][E_ATM_INFO], Iterator: destroyedATM<MAX_ATMS>, returnServerATMS;

GetATMHealthColor(health)
{
	new colorString[24];
	switch(health)
	{
		case 0..19: colorString = "ad0303";
		case 20..59: colorString = "f0a316";
		case 60..100: colorString = "498e04";
	}
	return colorString;
}

function LoadATMs()
{
	if(!cache_num_rows())
		return printf("ATMs Loaded (total: %d)", cache_num_rows());

	for(new i = 1; i <= cache_num_rows(); ++i)
	{
		AtmInfo[i][idATM] = cache_get_field_content_int(i - 1, "atmId");

		AtmInfo[i][fATMPos][0] = cache_get_field_content_float(i - 1, "atmPosX");
		AtmInfo[i][fATMPos][1] = cache_get_field_content_float(i - 1, "atmPosY");
		AtmInfo[i][fATMPos][2] = cache_get_field_content_float(i - 1, "atmPosZ");
		
		AtmInfo[i][fATMPosRot][0] = cache_get_field_content_float(i - 1, "atmPosRotX");
		AtmInfo[i][fATMPosRot][1] = cache_get_field_content_float(i - 1, "atmPosRotY");
		AtmInfo[i][fATMPosRot][2] = cache_get_field_content_float(i - 1, "atmPosRotZ");

		AtmInfo[i][ATMHealth] = 100;

		new
			Float: x = AtmInfo[i][fATMPos][0], Float: y = AtmInfo[i][fATMPos][1], Float: a = AtmInfo[i][fATMPosRot][2],
			Float: distance = -0.60;

		x += (distance * floatsin(-a, degrees));
		y += (distance * floatcos(-a, degrees));

		AtmInfo[i][rObjectId][0] = CreateDynamicObject(19324, AtmInfo[i][fATMPos][0], AtmInfo[i][fATMPos][1], AtmInfo[i][fATMPos][2], AtmInfo[i][fATMPosRot][0], AtmInfo[i][fATMPosRot][1], AtmInfo[i][fATMPosRot][2], -1, -1, -1, 500.0);
		AtmInfo[i][rObjectId][1] = CreateDynamicPickup(1239, 23, x, y, AtmInfo[i][fATMPos][2], -1, -1, -1, 60);

		format(gString, sizeof gString, "ATM %d\nWithdraw your cash here!\nPress F to use this ATM.\nATM Health: {%s}%d", i, GetATMHealthColor(AtmInfo[i][ATMHealth]), AtmInfo[i][ATMHealth]);
		AtmInfo[i][ATMLabel] = CreateDynamic3DTextLabel(gString, -1, AtmInfo[i][fATMPos][0], AtmInfo[i][fATMPos][1], AtmInfo[i][fATMPos][2], 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1);
	}
	returnServerATMS = cache_num_rows();
	return printf("ATMs Loaded (total: %d)", returnServerATMS);
}

UpdateATMLabel(ATMId)
{
	if(AtmInfo[ATMId][ATMHealth] >= 1)
		format(gString, sizeof gString, "ATM %d\nWithdraw your cash here!\nPress F to use this ATM.\nATM Health: {%s}%d", ATMId, GetATMHealthColor(AtmInfo[ATMId][ATMHealth]), AtmInfo[ATMId][ATMHealth]);

	else
		format(gString, sizeof gString, "ATM %d\nOut of service\nRepair in {498e04}%d{FFFFFF} seconds.", ATMId, AtmInfo[ATMId][ATMRepairTime] - gettime());

	UpdateDynamic3DTextLabelText(AtmInfo[ATMId][ATMLabel], -1, gString);
	return 1;
}

Dialog:DIALOG_ATM_MENU(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

	if(!listitem)
	{
		format(gString, sizeof gString, "Your bank account balance is currently standing at $%s.", GetPlayerBank(playerid));
		Dialog_Show(playerid, 0, DIALOG_STYLE_MSGBOX, "SERVER: Automated Teller Machine", gString, "OK", "");
	}
	else if(listitem)
		Dialog_Show(playerid, DIALOG_ATM_WITHDRAW, DIALOG_STYLE_INPUT, "SERVER: ATM", "Please specify the amount of money that you'd like to withdraw.\n\nYou can withdraw up to $10,000 from this ATM.\n\nNote: This ATM charges $2 from any withdrawals you make.", "OK", "Cancel");

	return 1;
}

Dialog:DIALOG_ATM_WITHDRAW(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new atmMoney = strval(inputtext);

    if(atmMoney < 2 || atmMoney > 10000)
    	return SCM(playerid, COLOR_GREY, "You can't withdraw this amount of money."), Dialog_Show(playerid, DIALOG_ATM_WITHDRAW, DIALOG_STYLE_INPUT, "SERVER: ATM", "Please specify the amount of money that you'd like to withdraw.\n\nYou can withdraw up to $10,000 from this ATM.\n\nNote: This ATM charges $2 from any withdrawals you make.", "OK", "Cancel");

    /*if(GetPlayerBank(playerid) < atmMoney + 2)
    	SCM(playerid, COLOR_GREY, "You do not have enough money to withdraw this amount."), Dialog_Show(playerid, DIALOG_ATM_WITHDRAW, DIALOG_STYLE_INPUT, "SERVER: ATM", "Please specify the amount of money that you'd like to withdraw.\n\nYou can withdraw up to $10,000 from this ATM.\n\nNote: This ATM charges $2 from any withdrawals you make.", "OK", "Cancel");
	*/
    GivePlayerCash(playerid, atmMoney);
   // GivePlayerBank(playerid, -atmMoney + 2);
    GivePlayerBank(playerid, 0, -atmMoney + 2);

    Dialog_Show(playerid, 0, DIALOG_STYLE_MSGBOX, "SERVER: Automated Teller Machine", "Your money has been withdrawn.\n\nThank you for using our ATM today!", "OK", "");
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys == KEY_SECONDARY_ATTACK)
	{
		for(new i; i < MAX_ATMS; i++)
		{
			if(!IsPlayerInRangeOfPoint(playerid, 2.0, AtmInfo[i][fATMPos][0], AtmInfo[i][fATMPos][1], AtmInfo[i][fATMPos][2]))
				continue;
			
			if(AtmInfo[i][ATMHealth] < 1)
				return SCM(playerid, -1, "Acest bancomat este stricat! Asteapta cateva secunde!");

			Dialog_Show(playerid, DIALOG_ATM_MENU, DIALOG_STYLE_LIST, "SERVER: Automated Teller Machine", "Check Balance\nWithdraw", "OK", "Cancel");
			break;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerShootDynObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z)
{
	for(new i; i < MAX_ATMS; i++)
	{
		if(objectid == AtmInfo[i][rObjectId][0])
		{
			if(AtmInfo[i][ATMHealth] < 1 || IsACop(playerid))
				break;

			if(PlayerInfo[playerid][pWantedLevel] > 4)
				return SCMF(playerid, -1, "Nu poti jefui un bancomat daca ai wanted mai mare de 4.");

			new dmgAmount = RandomEx(5, 10);
			AtmInfo[i][ATMHealth] -= dmgAmount;

			if(AtmInfo[i][ATMHealth] < 1)
			{
				new atmMoney = RandomEx(50000, 60000);

				SCMF(playerid, -1, "Ai primit $%s pentru distrugerea acestui bancomat.", FormatNumber(atmMoney));
				GivePlayerCash(playerid, atmMoney);

				SetPlayerCriminal(playerid, -1, 2, "ATM robbery*");

				DestroyDynamicObject(AtmInfo[i][rObjectId][0]);
				AtmInfo[i][rObjectId][0] = CreateDynamicObject(2943, AtmInfo[i][fATMPos][0], AtmInfo[i][fATMPos][1], AtmInfo[i][fATMPos][2], AtmInfo[i][fATMPosRot][0], AtmInfo[i][fATMPosRot][1], AtmInfo[i][fATMPosRot][2], -1, -1, -1, 500.0);
				AtmInfo[i][ATMRepairTime] = gettime() + 65;

				Iter_Add(destroyedATM, i);
				//Streamer_Update(playerid);

				DailyQuestCheck(playerid, QUEST_TYPE_ATMROB, 1);
			}
			
			UpdateATMLabel(i);
			break;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

function WhenATMGotRepaired()
{
	if(!Iter_Count(destroyedATM))
		return 1;

	foreach(new i : destroyedATM)
	{
		if(AtmInfo[i][ATMHealth] >= 1 && AtmInfo[i][ATMRepairTime] == -1)
			continue;

		UpdateATMLabel(i);

		if(AtmInfo[i][ATMRepairTime] <= gettime())
		{	
			AtmInfo[i][ATMHealth] = 100;
			AtmInfo[i][ATMRepairTime] = -1;

			DestroyDynamicObject(AtmInfo[i][rObjectId][0]);
			AtmInfo[i][rObjectId][0] = CreateDynamicObject(19324, AtmInfo[i][fATMPos][0], AtmInfo[i][fATMPos][1], AtmInfo[i][fATMPos][2], AtmInfo[i][fATMPosRot][0], AtmInfo[i][fATMPosRot][1], AtmInfo[i][fATMPosRot][2], -1, -1, -1, 500.0);
			
			foreach(new playerid : Player)
				Streamer_Update(playerid);

			Iter_Remove(destroyedATM, i);
			UpdateATMLabel(i);
			break;
		}
	}
	return 1;
}

YCMD:gotoatm(playerid, params[], help)
{
	new returnATM;
	if(sscanf(params, "i", returnATM))
		return sendSyntax(playerid, "/gotoatm [id]");

	check_admin

	if(returnATM > MAX_ATMS)
		return SCM(playerid, -1, "Invalid ATM.");

	SetPlayerPos(playerid, AtmInfo[returnATM][fATMPos][0], AtmInfo[returnATM][fATMPos][1], AtmInfo[returnATM][fATMPos][2]);
	SCM(playerid, -1, "You have been teleported.");

	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerInterior(playerid, 0);
	return 1;
}
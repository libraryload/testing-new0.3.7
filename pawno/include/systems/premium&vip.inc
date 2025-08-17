#include <YSI_Coding\y_hooks>

new Text3D:accountLabel[MAX_PLAYERS];
returnAccountPrice(accType, subType)
{
	new 
		accPrice;

	if(accType == 1) 
	{
		switch(subType) {
			case 1: accPrice = 100;
			case 2: accPrice = 200;
			case 3: accPrice = 350;
			case 4: accPrice = 500;
		}
	}
	else if(accType == 2) {
		switch(subType) {
			case 1: accPrice = 200;
			case 2: accPrice = 400;
			case 3: accPrice = 700;
			case 4: accPrice = 1000;
		}
	}

	return accPrice;
}

returnAccountDays(subType)
{
	new
		accDays;

	switch(subType) {
		case 1: accDays = 30;
		case 2: accDays = 90;
		case 3: accDays = 180;
		case 4: accDays = 365;
	}

	return accDays;
}

stock returnPlayerCrystals(playerid) return PlayerInfo[playerid][pPremiumPoints];

returnAccountDiscount(subType)
{
	new
		accDiscount[24];

	switch(subType) {
		case 1: accDiscount = "{FF0000}(25% discount)";
		case 2: accDiscount = "{FF0000}(33% discount)";
		case 3: accDiscount = "{FF0000}(41% discount)";
	}	

	return accDiscount;
}

returnConvertion(playerid) return PlayerInfo[playerid][pPremiumAccountDays] * returnAccountPrice(2, PlayerInfo[playerid][pPremiumAccount]) / returnAccountDays(PlayerInfo[playerid][pPremiumAccount]);

hook OnPlayerConnect(playerid)
{
	Delete3DTextLabel(accountLabel[playerid]);
	accountLabel[playerid] = CreateDynamic3DTextLabel("", -1, 0.0, 0.0, 0.0, 10.0, 0, 0);
	return true;
}

hook OnPlayerDisconnect(playerid, reason)
{
	Delete3DTextLabel(accountLabel[playerid]);
	return true;
}

hook OnPlayerSpawn(playerid) 
{
   	if(PlayerInfo[playerid][pPremiumAccount] != 0)
   	{
	  	UpdateDynamic3DTextLabelText(accountLabel[playerid], 0x9D72FFFF, "Premium Account");
	    Attach3DTextLabelToPlayer(accountLabel[playerid], playerid, 0.0, 0.0, 0.4);
	}
	else if(PlayerInfo[playerid][pVIPAccount] != 0)
	{
	  	UpdateDynamic3DTextLabelText(accountLabel[playerid], 0x9D72FFFF, "VIP Account");
	    Attach3DTextLabelToPlayer(accountLabel[playerid], playerid, 0.0, 0.0, 0.4);
	}
	return true;
}
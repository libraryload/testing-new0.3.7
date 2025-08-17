#include <YSI_Coding\y_hooks>

#define MAX_BUSINESSES 100
#define STREAMER_BEGIN_BUSINESS (STREAMER_BEGIN_GARAGE + 100)
#define STREAMER_BEGIN_BUSINESS_SPHERE (STREAMER_BEGIN_BUSINESS + 100)

enum ENUM_BUSINESS_INFROMATIONS
{
	bID, bOwner, bType, bStatic, Float: bPosition[6], bOwnerName[MAX_PLAYER_NAME], bSafe,
	bSphere, Text3D: bLabel, bPickup, bIcon, bLocked, bMessage[16], bSecSphere, Text3D: bLabelSec, bPickupSec, bMoney
};
new
	BizInfo[MAX_BUSINESSES][ENUM_BUSINESS_INFROMATIONS], SERVER_BUSINESSES;

function LoadBizz()
{
	SERVER_BUSINESSES = cache_num_rows();
	for(new i = 1; i <= cache_num_rows(); i++)
	{
		BizInfo[i][bID] = cache_get_field_content_int(i - 1, "ID");
		BizInfo[i][bOwner] = cache_get_field_content_int(i - 1, "OwnerSQL");
		BizInfo[i][bType] = cache_get_field_content_int(i - 1, "Type");
		BizInfo[i][bStatic] = cache_get_field_content_int(i - 1, "Static");
		BizInfo[i][bSafe] = cache_get_field_content_int(i - 1, "Safe");

		BizInfo[i][bPosition][0] = cache_get_field_content_float(i - 1, "PosX");
		BizInfo[i][bPosition][1] = cache_get_field_content_float(i - 1, "PosY");
		BizInfo[i][bPosition][2] = cache_get_field_content_float(i - 1, "PosZ");

		BizInfo[i][bPosition][3] = cache_get_field_content_float(i - 1, "secPosX");
		BizInfo[i][bPosition][4] = cache_get_field_content_float(i - 1, "secPosY");
		BizInfo[i][bPosition][5] = cache_get_field_content_float(i - 1, "secPosZ");

		cache_get_field_content(i - 1, "OwnerName", BizInfo[i][bOwnerName], SQL, MAX_PLAYER_NAME);
		cache_get_field_content(i - 1, "Message", BizInfo[i][bMessage], SQL, 16);

		WhenBusinessGotUpdated(i);
	}
	printf("Businesses Loaded (total: %d)", SERVER_BUSINESSES);
	return true;
}

hook loadServerSystems()
{
	mysql_tquery(SQL, "select * from `bizz`", "loadBusinessesFromInclude", "");
	return Y_HOOKS_CONTINUE_RETURN_1;
}

forward public WhenBusinessGotUpdated(const business);
public WhenBusinessGotUpdated(const business)
{
	new bizLabelString[256];
	format(bizLabelString, sizeof bizLabelString, "{909CE7}%s{ffffff}\nBusiness  {909CE7}#%d{ffffff}%sOwner:  {909CE7}%s{ffffff}\nFee:  {909CE7}$5.000{ffffff}\n\
		Level:  {909CE7}7{ffffff}\n%s", BizInfo[business][bMessage], business, (!BizInfo[business][bOwner] ? ("\n{909CE7}This Business will be auctioned{ffffff}\n") : ("\n")), BizInfo[business][bOwnerName], (BizInfo[business][bLocked] == 0 ? ("") : ("{909CE7}(locked)")));

	BizInfo[business][bLabel] = CreateDynamic3DTextLabel(bizLabelString, -1, BizInfo[business][bPosition][0], BizInfo[business][bPosition][1], BizInfo[business][bPosition][2], 25, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, false, 0);
	BizInfo[business][bPickup] = CreateDynamicPickup(1239, 23, BizInfo[business][bPosition][0], BizInfo[business][bPosition][1], BizInfo[business][bPosition][2], -1, -1, -1, 60);
	
	if(BizInfo[business][bType] != 11 && BizInfo[business][bType] != 13)
		BizInfo[business][bIcon] = CreateDynamicMapIcon(BizInfo[business][bPosition][0], BizInfo[business][bPosition][1], BizInfo[business][bPosition][2], biz_icon(BizInfo[business][bType]), 0, -1, -1, -1, 200.0, MAPICON_GLOBAL);

	BizInfo[business][bSphere] = CreateDynamicSphere(BizInfo[business][bPosition][0], BizInfo[business][bPosition][1], BizInfo[business][bPosition][2], BizInfo[business][bType] >= 10 && BizInfo[business][bType] <= 12 ? 25.0 : 1.5, 0, 0, -1);	
	Streamer_SetIntData(STREAMER_TYPE_AREA, BizInfo[business][bSphere], E_STREAMER_EXTRA_ID, (business + STREAMER_BEGIN_BUSINESS));

	if(BizInfo[business][bType] == 10 || BizInfo[business][bType] == 11 || BizInfo[business][bType] == 14)
	{
		BizInfo[business][bSecSphere] = CreateDynamicSphere(BizInfo[business][bPosition][3], BizInfo[business][bPosition][4], BizInfo[business][bPosition][5], 4.75, 0, -1, -1);
		Streamer_SetIntData(STREAMER_TYPE_AREA, BizInfo[business][bSecSphere], E_STREAMER_EXTRA_ID, (business + STREAMER_BEGIN_BUSINESS_SPHERE));

		if(BizInfo[business][bType] == 14)
		{
			BizInfo[business][bLabelSec] = CreateDynamic3DTextLabel("{909CE7}Rent Car{ffffff}\n\nType /rentveh\nto rent a vehicle", -1, BizInfo[business][bPosition][3], BizInfo[business][bPosition][4], BizInfo[business][bPosition][5], 40, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, false, 0);
			BizInfo[business][bPickupSec] = CreateDynamicPickup(1239, 23, BizInfo[business][bPosition][3], BizInfo[business][bPosition][4], BizInfo[business][bPosition][5], -1, -1, -1, 60);
		}
	}
	if(BizInfo[business][bType] == 2)
	{
		CreateDynamicActor(179, 294.3559, -40.2153, 1001.5156, 1.6557, true, 100, business, 1);
		CreateDynamic3DTextLabel("{909CE7}[GUN SHOP]{ffffff}\nPress {909CE7}Y{ffffff} if you want to buy a gun.", -1, 294.3383, -38.5148, 1001.5156, 30.0);
	}

	if(BizInfo[business][bType] == 4)
	{
		CreateDynamicActor(194, -23.5991, -57.3145, 1003.5469, 356.0751, true, 100, business, 6);
		CreateDynamic3DTextLabel("{909CE7}[SHOP]{ffffff}\nPress {909CE7}Y{ffffff} if you want to buy something.", -1, -22.2731, -55.6953, 1003.5469, 30.0);
	}
	return true;
}

hook OnPlayerEnterDynArea(playerid, areaid)
{
	new business = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID) - STREAMER_BEGIN_BUSINESS;
	if(SERVER_BUSINESSES < business)
		return true;

	SetPVarInt(playerid, "streamer_biz_areaid", business);
	/*if(BizInfo[business][bType] == 10 || BizInfo[business][bType] == 11)
		DisableRemoteVehicleCollisions(playerid, true);*/

	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerLeaveDynArea(playerid, areaid)
{	
	if(GetPVarInt(playerid, "streamer_biz_areaid") > 0)
		DisableRemoteVehicleCollisions(playerid, false);
	
	DeletePVar(playerid, "streamer_biz_areaid");
	return Y_HOOKS_CONTINUE_RETURN_1;
}

biz_icon(const biz_type)
{
	switch(biz_type)
	{
		case 1: return 52;
		case 2: return 18;
		case 3: return 49;
		case 4: return 17;
		case 5: return 10;
		case 6: return 54;
		case 7: return 14;
		case 8: return 45;
		case 9: return 25;
		case 10: return 63;
		case 11: return false;
		case 12: return 27;
		case 13: return false; //16
		case 14: return 51;
		default: return false;
	}
	return true;
}

business_name(const business_id)
{
	new bizString[32];
	switch(business_id)
	{
		case 1: bizString = "Bank";
		case 2: bizString = "Gun Shop";
		case 3: bizString = "Bar";
		case 4: bizString = "24/7 Store";
		case 5: bizString = "Burger Shot";
		case 6: bizString = "Gym";
		case 7: bizString = "Cluckin' Bell";
		case 8: bizString = "Clothing Store";
		case 9: bizString = "Casino";

		case 10: bizString = "Pay N'Spray";
		case 11: bizString = "Tunning";
		case 12: bizString = "Gas Station";
		case 13: bizString = "CNN";
		case 14: bizString = "Rent Car";

		default: bizString = "Unknown";
	}
	return bizString;
}

new business_int[] =
{
	0, 1, 11, 6, 10, 7, 9, 18, 10
};
new Float:business_coords[][] =
{
	{2305.0430, -16.1294, 26.7422},
	{285.4405, -41.5128, 1001.5156},
	{501.8960, -68.0889, 998.7578},
	{-27.2393, -58.1129, 1003.5469},
	{363.1238, -75.1133, 1001.5078},
	{773.9741, -78.6282, 1000.6625},
	{364.9500, -11.5759, 1001.8516},
	{161.4328, -96.5507, 1001.8047},
	{2018.6392, 1017.8764, 996.8085}
};

put_player_in_business(const playerid, const type, const business)
{
	SetPlayerPos(playerid, business_coords[type - 1][0], business_coords[type - 1][1], business_coords[type - 1][2]);
	SetPlayerInterior(playerid, business_int[type - 1]);
	SetPlayerVirtualWorld(playerid, business);
	sell_fish(playerid);
	business_message(playerid, type);
	return true;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	switch(newkeys)
	{
		case KEY_SECONDARY_ATTACK:
		{
			if(IsPlayerInAnyDynamicArea(playerid) && GetPVarInt(playerid, "streamer_biz_areaid") > 0 && GetPVarInt(playerid, "streamer_biz_areaid") <= SERVER_BUSINESSES)
			{
				if(BizInfo[GetPVarInt(playerid, "streamer_biz_areaid")][bStatic] == 1)
					return true;

				if(GetPlayerMoney(playerid) < 5000)
					return GameTextForPlayer(playerid, "~r~~h~You dont have the cash", 5000, 1);
	
				if(GetPVarInt(playerid, "enter_building_deelay") > gettime())
					return SCMF(playerid, COLOR_GREY, "[Anti-Abuz] Nu poti intra intr-o cladire timp de %d secunde.", GetPVarInt(playerid, "enter_building_deelay") - gettime());

				if(BizInfo[GetPVarInt(playerid, "streamer_biz_areaid")][bLocked] == 1)
					return GameTextForPlayer(playerid, "~r~~h~Closed", 5000, 1);

				put_player_in_business(playerid, BizInfo[GetPVarInt(playerid, "streamer_biz_areaid")][bType], GetPVarInt(playerid, "streamer_biz_areaid"));				
				s_PlayerInfo[playerid][pSInBusiness] = GetPVarInt(playerid, "streamer_biz_areaid");
				
				if(GetPVarInt(playerid, "last_biz_enter_time") < gettime() && GetPVarInt(playerid, "last_biz_id") != GetPVarInt(playerid, "streamer_biz_areaid"))
				{
					GivePlayerMoney(playerid, -5000);
					BizInfo[GetPVarInt(playerid, "streamer_biz_areaid")][bMoney] += 5000;

					GameTextForPlayer(playerid, "~r~-$5000", 5000, 1);
					SetPVarInt(playerid, "last_biz_enter_time", gettime() + 30);

					mysql_format(SQL, gString, sizeof gString, "update `bizz` set `bizMoney` = '%d' where `ID` = '%d';", BizInfo[GetPVarInt(playerid, "streamer_biz_areaid")][bMoney], GetPVarInt(playerid, "streamer_biz_areaid"));
					mysql_tquery(SQL, gString, "", "");
				}

				SetPVarInt(playerid, "last_biz_id", GetPVarInt(playerid, "streamer_biz_areaid"));
				return true;
			}
			if(GetPlayerVirtualWorld(playerid) <= SERVER_BUSINESSES && s_PlayerInfo[playerid][pSInBusiness] > 0 && IsPlayerInRangeOfPoint(playerid, 1.5, business_coords[BizInfo[GetPlayerVirtualWorld(playerid)][bType] - 1][0], business_coords[BizInfo[GetPlayerVirtualWorld(playerid)][bType] - 1][1], business_coords[BizInfo[GetPlayerVirtualWorld(playerid)][bType] - 1][2])) 
			{
				SetPlayerPos(playerid, BizInfo[GetPlayerVirtualWorld(playerid)][bPosition][0], BizInfo[GetPlayerVirtualWorld(playerid)][bPosition][1], BizInfo[GetPlayerVirtualWorld(playerid)][bPosition][2]);
				SetPVarInt(playerid, "streamer_biz_areaid", 0), SetPlayerVirtualWorld(playerid, 0), SetPlayerInterior(playerid, 0);

				SetPVarInt(playerid, "enter_building_deelay", gettime() + 5);
				s_PlayerInfo[playerid][pSInBusiness] = 0;
				return true;
			}
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

YCMD:findbiz(playerid, params[], help)
{
	if(s_PlayerInfo[playerid][pSCP])
		return showActiveCheckpointDialog(playerid);

	new bizId;
	if(sscanf(params, "i", bizId))
		return sendSyntax(playerid, "/findbiz [biz id]");

	if(bizId < 1 || bizId > SERVER_BUSINESSES)
		return SCM(playerid, COLOR_GREY, "Invalid bizz ID.");

	SCM(playerid, -1, "I have placed a checkpoint at that location. Please follow it.");
	s_PlayerInfo[playerid][pSCP] = 1;

	return SetPlayerCheckpoint(playerid, BizInfo[bizId][bPosition][0], BizInfo[bizId][bPosition][1], BizInfo[bizId][bPosition][2], 5.0);
}
YCMD:buy(playerid, params[], help) 
{
	Dialog_Show(playerid, DIALOG_24_2, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: 24/7","#\tStore Type\tInfo\n1.\tUtilities\tphone, phonebook etc...\n2.\tLicenses\tgun, fly etc...","Select","Exit");
    return 1; 
}
YCMD:createbiz(playerid, params[], help)
{
	if(PlayerInfo[playerid][pAdmin] < 6)
		return sendAcces(playerid);

	new returnType, returnStaticBiz;
	if(sscanf(params, "i", returnType))
	{
		sendSyntax(playerid, "/createbusiness [type]");
		SCM(playerid, COLOR_GREY, "(1) Bank | (2) Gun Shop | (3) Bar | (4) 24/7 Store | (5) Burger Shot | (6) Gym");
		SCM(playerid, COLOR_GREY, "(7) Cluckin' Bell | (8) Clothing Store | (9) Casino | (10) Pay N'Spray | (11) Tunning");
		SCM(playerid, COLOR_GREY, "(12) Gas Station | (13) CNN | (14) Rent Car");
		return true;
	}

	new Float:returnPos[3];
	GetPlayerPos(playerid, returnPos[0], returnPos[1], returnPos[2]);

	if(check_if_is_static_biz(returnType) == 1)
		returnStaticBiz = 1;

	mysql_format(SQL, gString, sizeof gString, "insert into `bizz` (`Type`, `PosX`, `PosY`, `PosZ`, `Static`) values ('%d', '%f', '%f', '%f');",  returnType, returnPos[0], returnPos[1], returnPos[2], returnStaticBiz);
	mysql_tquery(SQL, gString, "WhenBusinessIsCreated", "ifffi", returnType, returnPos[0], returnPos[1], returnPos[2], playerid);

	return SCM(playerid, COLOR_GREY, "Solicitarea ta de a fost trimisa catre baza de date.");
}

YCMD:movebiz(playerid, params[], help)
{
	if(PlayerInfo[playerid][pAdmin] < 6)
		return sendAcces(playerid);


	new returnBusiness;
	if(sscanf(params, "i", returnBusiness))
		return sendSyntax(playerid, "/movebusiness [business id]");

	new Float:returnPos[3];
	GetPlayerPos(playerid, returnPos[0], returnPos[1], returnPos[2]);

	ABroadCast(COLOR_RED, 1, "%s moved business %d. [%f %f %f]", GetName(playerid), returnBusiness, returnPos[0], returnPos[1], returnPos[2]);

	BizInfo[returnBusiness][bPosition][0] = returnPos[0];
	BizInfo[returnBusiness][bPosition][1] = returnPos[1];
	BizInfo[returnBusiness][bPosition][2] = returnPos[2];

	WhenBusinessGotUpdated(returnBusiness);

	mysql_format(SQL, gString, sizeof gString, "update `bizz` set `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f' where `ID` = '%d';", returnPos[0], returnPos[1], returnPos[2], returnBusiness);
	mysql_tquery(SQL, gString, "", "");
	return true;
}

check_if_is_static_biz(const type)
{
	switch(type)
	{
		case 1..9: return false;
		case 10..14: return true;
	}
	return true;
}

forward public WhenBusinessIsCreated(const type, Float:X, Float:Y, Float:Z, const requester);
public WhenBusinessIsCreated(const type, Float:X, Float:Y, Float:Z, const requester)
{
	if(MAX_BUSINESSES <= SERVER_BUSINESSES + 1)
		return SCM(requester, -1, "You can't create a business because there are too many on server.");

	SERVER_BUSINESSES ++;
	new i = SERVER_BUSINESSES;

	BizInfo[i][bID] = cache_insert_id();
	BizInfo[i][bOwner] = 0;

	format(BizInfo[i][bOwnerName], 8, "AdmBot");
	format(BizInfo[i][bMessage], 16, "replay.ro");

	if(check_if_is_static_biz(type) == 1)
		BizInfo[i][bStatic] = 1;
	
	BizInfo[i][bPosition][0] = X;
	BizInfo[i][bPosition][1] = Y;
	BizInfo[i][bPosition][2] = Z;

	BizInfo[i][bType] = type;
	if(type == 10 || type == 11 || type == 14)
	{
		new choseLocation[64];
		switch(type)
		{
			case 10: choseLocation = "for the PNS to repair vehicles - sphere";
			case 11: choseLocation = "for the tunning - sphere";
			case 14: choseLocation = "for the players to rent vehicles - label + pickup + sphere";
		}

		new bizString[256];
		format(bizString, sizeof bizString, "Because you seleted to create a static business in the next 20 seconds you need to chose another location\n\
			Business type: %s (the location will be used %s)", business_name(BizInfo[i][bType]), choseLocation);
		
		Dialog_Show(requester, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "Create business:", bizString, "Ok", "");
		SCM(requester, COLOR_GREY, "Waiting for server... [labels will apear after the sphere is placed]");
		
		SetTimerEx("business_create_2nd_step", 20000, false, "iii", requester, type, i);
		return true;
	}

	WhenBusinessGotUpdated(i);

	ABroadCast(COLOR_RED, 1, "%s created a new business.", GetName(requester));
	return true;
}
forward public business_create_2nd_step(const playerid, const type, const biz);
public business_create_2nd_step(const playerid, const type, const biz)
{
	Dialog_Show(playerid, DIALOG_CHOSE_LOCATION, DIALOG_STYLE_MSGBOX, "Create business:", "Confirm:\nAre you sure if you want to chose this position for the business action place.\nIf you aren't sure press 'No' button and then wait again 30 seconds.", "Yes", "No");
	
	SetPVarInt(playerid, "business_type", type);
	SetPVarInt(playerid, "business_id", biz);
	return true;
}
Dialog:DIALOG_CHOSE_LOCATION(playerid, response, listitem, inputtext[])
{
	if(!response)
		return SCM(playerid, COLOR_GREY, "Waiting another 20 seconds.."), SetTimerEx("business_create_2nd_step", 20000, false, "iii", playerid, GetPVarInt(playerid, "business_type"), GetPVarInt(playerid, "business_id")), SCM(playerid, COLOR_GREY, "Waiting another 30 seconds for repositioning...");

	new Float:X, Float:Y, Float:Z;
	GetPlayerPos(playerid, X, Y, Z);

	new i = GetPVarInt(playerid, "business_id");

	BizInfo[i][bPosition][3] = X;
	BizInfo[i][bPosition][4] = Y;
	BizInfo[i][bPosition][5] = Z;

	SCM(playerid, COLOR_GREY, "Business sphere for action was updated.");
	WhenBusinessGotUpdated(i);

	mysql_format(SQL, gString, sizeof gString, "update `bizz` set `secPosX` = '%f', `secPosY` = '%f', `secPosZ` = '%f' where `ID` = '%d';", X, Y, Z, i);
	mysql_tquery(SQL, gString, "", "");

	DeletePVar(playerid, "business_id");
	DeletePVar(playerid, "business_type");
	return true;
}

YCMD:bizmenu(playerid, params[], help)
{

	if(PlayerInfo[playerid][pBusiness] == 0)
		return SCM(playerid, -1, "You don't have a business.");

	if(PlayerInfo[playerid][pSQLID] != BizInfo[PlayerInfo[playerid][pBusiness]][bOwner])
		return SCM(playerid, -1, "You aren't a business owner.");

	Dialog_Show(playerid, DIALOG_BUSINESS, DIALOG_STYLE_LIST, "Business menu:", "Withdraw money", "Select", "Exit");
	return 1;
}
Dialog:DIALOG_BUSINESS(playerid, response, listitem, inputtext[])
{
	if(!response)
		return true;

	if(PlayerInfo[playerid][pBusiness] == 0)
		return true;

	switch(listitem)
	{
		case 0:
		{
			SCMF(playerid, -1, "You have withdrawn $%s from your business safe.", FormatNumber(BizInfo[PlayerInfo[playerid][pBusiness]][bMoney]));

			GivePlayerMoney(playerid, BizInfo[PlayerInfo[playerid][pBusiness]][bMoney]);
			BizInfo[PlayerInfo[playerid][pBusiness]][bMoney] = 0;

			mysql_format(SQL, gString, sizeof gString, "update `bizz` set `Safe` = '0' where `ID` = '%d';", PlayerInfo[playerid][pBusiness]);
			mysql_tquery(SQL, gString, "", "");
		}
	}
	return true;
}

YCMD:bowner(playerid, params[], help)
{
	if(PlayerInfo[playerid][pAdmin] < 6)
		return sendAcces(playerid);

	new returnName[MAX_PLAYER_NAME], returnBusiness;
	if(sscanf(params, "s[24]d", returnName, returnBusiness))
		return sendSyntax(playerid, "/bowner [full name] [business]");

	format(gString, sizeof gString, "select `ID` from `users` where `name` = '%s';", returnName);
	new Cache: check_if_player_exist = mysql_query(SQL, gString);
	
	if(!cache_num_rows())
	{
		cache_delete(check_if_player_exist);
		SCM(playerid, -1, "Invalid player.");
		return true;
	}
	else
	{
		SetPVarInt(playerid, "biz_give_id", returnBusiness);
		SetPVarInt(playerid, "biz_give_player", cache_get_field_content_int(0, "ID"));

		SetPVarString(playerid, "biz_give_name", returnName);
	}
	cache_delete(check_if_player_exist);

	new dialogString[256];
	format(dialogString, sizeof dialogString, "Esti sigur ca vrei sa-i dai lui %s afacerea %d?\nDaca afacerea este detinuta de cineva, acesta va ramane fara aceasta.\nAbuzul de aceasta comanda duce la pierderea functiei!", returnName, returnBusiness);

	Dialog_Show(playerid, DIALOG_BOWNER, DIALOG_STYLE_MSGBOX, "Esti sigur?", dialogString, "Da", "Nu");
	return true;
}

Dialog:DIALOG_BOWNER(playerid, response, listitem, inputtext[])
{
	if(!response)
		return DeletePVar(playerid, "biz_give_player"), DeletePVar(playerid, "biz_give_id"), DeletePVar(playerid, "biz_give_name");

	new ownerName[MAX_PLAYER_NAME];
	GetPVarString(playerid, "biz_give_name", ownerName, sizeof ownerName);

	BizInfo[GetPVarInt(playerid, "biz_give_id")][bOwner] = GetPVarInt(playerid, "biz_give_player");
	format(BizInfo[GetPVarInt(playerid, "biz_give_id")][bOwnerName], MAX_PLAYER_NAME, "%s", ownerName);

	mysql_format(SQL, gString, sizeof gString, "update `users` set `Business` = '0' where `Business` = '%d';", GetPVarInt(playerid, "biz_give_id"));
	mysql_tquery(SQL, gString, "", "");

	mysql_format(SQL, gString, sizeof gString, "update `users` set `Business` = '%d' where `ID` = '%d';", GetPVarInt(playerid, "biz_give_id"), GetPVarInt(playerid, "biz_give_player"));
	mysql_tquery(SQL, gString, "", "");

	mysql_format(SQL, gString, sizeof gString, "update `bizz` set `OwnerSQL` = '%d', `OwnerName` = '%s' where `ID` = '%d';", GetPVarInt(playerid, "biz_give_player"), ownerName, GetPVarInt(playerid, "biz_give_id"));
	mysql_tquery(SQL, gString, "", "");

	ABroadCast(COLOR_RED, 1, "Administrator %s[admin:%d] has set %s[user:%d] owner for business %d.", GetDBName(playerid), PlayerInfo[playerid][pSQLID], ownerName, PlayerInfo[GetPVarInt(playerid, "biz_give_player")][pSQLID], GetPVarInt(playerid, "biz_give_player"));
	WhenBusinessGotUpdated(GetPVarInt(playerid, "biz_give_id"));

	foreach(new i : Player)
	{
		if(!s_PlayerInfo[i][pSLoggedIn])
			continue;

		PlayerInfo[i][pBusiness] = GetPVarInt(playerid, "biz_give_id");
		SCMF(i, COLOR_GREY, "Administrator %s has set you owner for business %d.", GetName(playerid), GetPVarInt(playerid, "biz_give_id"));
		break;
	}

	DeletePVar(playerid, "biz_give_player"), DeletePVar(playerid, "biz_give_id"), DeletePVar(playerid, "biz_give_name");
	return true;
}

function business_message(const playerid, const type)
{
	//Welcome to Bank. The available commands for this business are /withdraw, /transfer, /deposit
	switch(type)
	{
		case 1:
		{
			SCM(playerid, COLOR_GREEN, "Inselatoriile (tepele) nu sunt permise pe server. Pentru orice incercare de a insela un player cu bunuri/bani puteti primi ban permanent.");
			SCM(playerid, COLOR_GREEN, "Imprumuturile de orice fel (inclusiv datoriile) se fac pe proprie raspundere. Nu ai nicio garantie ca ii vei recupera.");
			SCM(playerid, COLOR_GREEN, "Afacerile cu bani reali nu sunt permise. Se pedepseste cu ban 7-14 zile la prima abatere si ban permanent la urmatoarea abatere.");
			SCM(playerid, -1, "Welcome! The commands of this business are as follows: /withdraw, /transfer, /deposit");
		}
		case 2:
		{
			SCM(playerid, COLOR_GREEN, "DM-ul este interzis. Puteti face DM doar pe politisti dar o sa primiti wanted fara a avea drept de predare.");
			SCM(playerid, COLOR_GREEN, "DM-ul pe un jucator se poate sanctiona cu jail 10 minute.");
			SCM(playerid, -1, "Welcome to the Gun Shop. You can buy guns by pressing Y in the front of the NPC.");
		}
		case 3: SCM(playerid, -1, "Welcome! The commands of this business are as follows: /buydrink");
		case 4: SCM(playerid, -1, "Welcome to the 24/7 Store. You can buy items by pressing Y in the front of the NPC.");
		case 5: SCM(playerid, -1, "Welcome! The commands of this business are as follows: /heal");
		case 6: SCM(playerid, -1, "Welcome! The commands of this business are as follows: /buyfightstyle");
		case 7: SCM(playerid, -1, "Welcome! The commands of this business are as follows: /heal");
		case 8: SCM(playerid, -1, "Welcome! The commands of this business are as follows: /clothes");
		case 9:
		{
			SCM(playerid, -1, "Welcome! The commands of this business are as follows: /dice. You can also play at slots machine.");
		}
		default: return true;
	}
	return true;
}
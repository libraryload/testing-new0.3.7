#include <YSI_Coding\y_hooks>

#define MAX_HOUSES (100)

#define STREAMER_BEGIN_HOUSE (0)
#define STREAMER_BEGIN_GARAGE (STREAMER_BEGIN_HOUSE + 100)

#define MAX_FURNITURE_CATEGORY (4)
#define MAX_HOUSE_OBJECTS (500)

enum ENUM_HOUSE_INFROMATIONS
{
	hID, hOwner, hType, hInteriorVar, Float: hExterior[3], Float: hInterior[3], hSphere, Text3D: hLabel,
	hPickup, hIcon, hLocked, hRent, hRentable, hSafe, hRadio, hLevel, hSpecial, hObjects,
	hOwnerName[MAX_PLAYER_NAME], hDescription[24]
};
new
	HouseInfo[MAX_HOUSES][ENUM_HOUSE_INFROMATIONS], Iterator: houseRenters<MAX_HOUSES, MAX_PLAYERS>, SERVER_HOUSES;

enum ENUM_FURNITURE_INFORMATIONS
{
	mappingModel[MAX_HOUSES], mappingType[MAX_HOUSES], mappingGameModel[MAX_HOUSES], mappingID[MAX_HOUSES]
};
new
	mappingInfo[MAX_HOUSE_OBJECTS][ENUM_FURNITURE_INFORMATIONS], Float:mappingPos[MAX_HOUSE_OBJECTS][6][MAX_HOUSES],
	returnTotalObjects;

new houseFurnitures[MAX_FURNITURE_CATEGORY][] =
{
	{1518, 14772, 19786, 19787, 19318, 19317, 19610, 2232, 2231, 19609, 19424, 1954},
	{1767, 1765, 1762, 1820, 1822, 1823, 1814, 1742, 1769, 2291, 2235, 1727, 1969, 1811, 1720, 2311, 2185, 2800, 2725, 1417, 2126, 11717, 2109, 2111, 2164, 1712, 1706, 11720, 1760, 2357, 14866, 2603, 2302, 1794, 11690, 2748, 2724, 1806, 1729},
	{2255, 2254, 2256, 2257, 2259, 2258, 2260, 2261, 2263, 2266, 2267, 2268, 2272, 2273, 2276, 2277, 2281, 2282, 2284, 19172, 19173, 2270, 2286, 3111},
	{2970, 19875, 2924, 2955, 3109, 2873, 2877, 2878, 2875, 2879, 2876, 2946, 1522, 1493, 1491, 1567, 1492, 2949, 1498, 1536, 2959, 1535, 1495, 1532, 1496, 1497, 1523, 1569, 1538, 1557, 1504, 1501, 1499, 1505, 1506, 1507, 1502, 19858, 19859, 19802, 1533, 1566}
};

hook OnPlayerDisconnect(playerid, reason)
{
	if(PlayerInfo[playerid][pHouse] != 0)
	{
		new
			houseId = PlayerInfo[playerid][pHouse];

		if(Iter_Contains(houseRenters<houseId>, playerid))
		{
			Iter_Remove(houseRenters<houseId>, playerid);
			UpdateHouseLabel(houseId);
		}
	}

	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynArea(playerid, areaid)
{
	new
		houseId = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID) - STREAMER_BEGIN_HOUSE;
	
	if(SERVER_HOUSES < houseId)
		return 1;

	SetPVarInt(playerid, "streamer_house_areaid", houseId);
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerLeaveDynArea(playerid, areaid)
{
    SetPVarInt(playerid, "streamer_house_areaid", 0);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys == KEY_SECONDARY_ATTACK)
	{
		if(IsPlayerInAnyDynamicArea(playerid) && GetPVarInt(playerid, "streamer_house_areaid") > 0)
		{
			if(GetPVarInt(playerid, "enter_building_deelay") > gettime())
				return SCMF(playerid, COLOR_GREY, "[Anti abuz]: Nu poti intra intr-o cladire timp de %d secunde.", GetPVarInt(playerid, "enter_building_deelay") - gettime());
			
			new
				houseAreaId = GetPVarInt(playerid, "streamer_house_areaid");

			if(HouseInfo[houseAreaId][hLocked] == 1 && PlayerInfo[playerid][pHouse] != houseAreaId)
				return GameTextForPlayer(playerid, "~r~~h~Locked", 5000, 1);

			SetPlayerPos(playerid, HouseInfo[houseAreaId][hInterior][0], HouseInfo[houseAreaId][hInterior][1], HouseInfo[houseAreaId][hInterior][2]);
			
			SetPlayerInterior(playerid, HouseInfo[houseAreaId][hInteriorVar]);
			SetPlayerVirtualWorld(playerid, houseAreaId);
			
			if(HouseInfo[houseAreaId][hRadio])
			{
				StopAudioStreamForPlayer(playerid);
				PlayAudioStreamForPlayer(playerid, RadioLinks[HouseInfo[houseAreaId][hRadio]]);
			}

			return s_PlayerInfo[playerid][pSInHouse] = houseAreaId;
		}
		if(s_PlayerInfo[playerid][pSInHouse] > 0 && GetPlayerVirtualWorld(playerid) > 0 && GetPlayerVirtualWorld(playerid) <= SERVER_HOUSES && IsPlayerInRangeOfPoint(playerid, 1.5, HouseInfo[GetPlayerVirtualWorld(playerid)][hInterior][0], HouseInfo[GetPlayerVirtualWorld(playerid)][hInterior][1], HouseInfo[GetPlayerVirtualWorld(playerid)][hInterior][2]))
		{
			new houseAreaId = GetPlayerVirtualWorld(playerid);
			SetPlayerPos(playerid, HouseInfo[houseAreaId][hExterior][0], HouseInfo[houseAreaId][hExterior][1], HouseInfo[houseAreaId][hExterior][2]);

			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);
			
			StopAudioStreamForPlayer(playerid);
			s_PlayerInfo[playerid][pSInHouse] = -1;

			return SetPVarInt(playerid, "enter_building_deelay", gettime() + 5);
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook WhenPlayerLoggedIn(playerid)
{
	if(cache_num_rows())
	{
		PlayerInfo[playerid][pSQLID] = cache_get_field_content_int(0, "id");
		PlayerInfo[playerid][pHouse] = cache_get_field_content_int(0, "House");

		if(PlayerInfo[playerid][pSQLID] != HouseInfo[PlayerInfo[playerid][pHouse]][hOwner] && PlayerInfo[playerid][pHouse])
		{
			Iter_Add(houseRenters<PlayerInfo[playerid][pHouse]>, playerid);
			UpdateHouseLabel(PlayerInfo[playerid][pHouse]);
		}
	}
}

hook OnPlayerSelectDynObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)
{
	new Float:retPos[3];
	GetDynamicObjectPos(objectid, retPos[0], retPos[1], retPos[2]);
	
	if(!IsPlayerInRangeOfPoint(playerid, 50.0, retPos[0], retPos[1], retPos[2]))
		return SCM(playerid, -1, "Anti abuz: editarea a luat sfarsit.");

	if(GetPVarInt(playerid, "house_repos_object") == 1)
		EditDynamicObject(playerid, objectid);

	else if(GetPVarInt(playerid, "house_delete_object") == 1)
	{
		SCMF(playerid, -1, "Obiectul #%d a fost sters.", modelid);
		for(new i; i < returnTotalObjects + 1; i++)
		{
			if(mappingInfo[i][mappingGameModel][PlayerInfo[playerid][pHouse]] == objectid)
			{
				mysql_format(SQL, gString, sizeof gString, "delete from `house_mapping` where `ID` = '%d';", mappingInfo[i][mappingID][PlayerInfo[playerid][pHouse]]);
				mysql_tquery(SQL, gString, "", "");
				break;
			}
		}
		returnTotalObjects --;
		DestroyDynamicObject(objectid);
	}
	return 1;
}

hook OnPlayerEditDynObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(response == EDIT_RESPONSE_FINAL)
	{
		SCM(playerid, -1, "Pozitia item-ului a fost modificata.");
		for(new i; i < returnTotalObjects + 1; i++)
		{
			if(mappingInfo[i][mappingGameModel][PlayerInfo[playerid][pHouse]] == objectid)
			{
				mappingPos[i][0][PlayerInfo[playerid][pHouse]] = x;
				mappingPos[i][1][PlayerInfo[playerid][pHouse]] = y;
				mappingPos[i][2][PlayerInfo[playerid][pHouse]] = z;

				mappingPos[i][3][PlayerInfo[playerid][pHouse]] = rx;
				mappingPos[i][4][PlayerInfo[playerid][pHouse]] = ry;
				mappingPos[i][5][PlayerInfo[playerid][pHouse]] = rz;

				DestroyDynamicObject(mappingInfo[i][mappingGameModel][PlayerInfo[playerid][pHouse]]);		
				mappingInfo[i][mappingGameModel][PlayerInfo[playerid][pHouse]] = CreateDynamicObject(mappingInfo[i][mappingModel][PlayerInfo[playerid][pHouse]], mappingPos[i][0][PlayerInfo[playerid][pHouse]], mappingPos[i][1][PlayerInfo[playerid][pHouse]], mappingPos[i][2][PlayerInfo[playerid][pHouse]], mappingPos[i][3][PlayerInfo[playerid][pHouse]], mappingPos[i][4][PlayerInfo[playerid][pHouse]], mappingPos[i][5][PlayerInfo[playerid][pHouse]], PlayerInfo[playerid][pHouse], HouseInfo[PlayerInfo[playerid][pHouse]][hInteriorVar]);

				mysql_format(SQL, gString, sizeof gString, "update `house_mapping` set `X` = '%f', `Y` = '%f', `Z` = '%f', `RotX` = '%f', `RotY` = '%f', `RotZ` = '%f' where `ID` = '%d';", x, y, z, rx, ry, rz, mappingInfo[i][mappingID][PlayerInfo[playerid][pHouse]]);
				mysql_tquery(SQL, gString, "", "");
				break;
			}
		}
	}
	if(response == EDIT_RESPONSE_CANCEL)
	{
		SCM(playerid, -1, "Pozitia item-ului a revenit la cea initiala.");
		for(new i; i < returnTotalObjects + 1; i++)
		{
			if(mappingInfo[i][mappingGameModel][PlayerInfo[playerid][pHouse]] == objectid)
			{
				DestroyDynamicObject(mappingInfo[i][mappingGameModel][PlayerInfo[playerid][pHouse]]);
				mappingInfo[i][mappingGameModel][PlayerInfo[playerid][pHouse]] = CreateDynamicObject(mappingInfo[i][mappingModel][PlayerInfo[playerid][pHouse]], mappingPos[i][0][PlayerInfo[playerid][pHouse]], mappingPos[i][1][PlayerInfo[playerid][pHouse]], mappingPos[i][2][PlayerInfo[playerid][pHouse]], mappingPos[i][3][PlayerInfo[playerid][pHouse]], mappingPos[i][4][PlayerInfo[playerid][pHouse]], mappingPos[i][5][PlayerInfo[playerid][pHouse]], PlayerInfo[playerid][pHouse], HouseInfo[PlayerInfo[playerid][pHouse]][hInteriorVar]);
				break;
			}
		}
	}
	return 1;
}

public OnPlayerModelSelectionEx(playerid, response, extraid, modelid)
{
	if(!response)
		return 1;

	if(PlayerInfo[playerid][pHouse] != 0 && HouseInfo[PlayerInfo[playerid][pHouse]][hOwner] == PlayerInfo[playerid][pSQLID])
	{
		new Float:retPos[3]; GetPlayerPos(playerid, retPos[0], retPos[1], retPos[2]);

		SCMF(playerid, -1, "Ai platit $%s si ai achizitionat item-ul #%d (categorie: %s)", "20.000", modelid, returnCategory(GetPVarInt(playerid, "furniture_category")));

		mysql_format(SQL, gString, sizeof gString, "insert into `house_mapping` (`Model`, `X`, `Y`, `Z`, `House`, `Type`) values ('%d', '%f', '%f', '%f', '%d', '%d');", modelid, retPos[0], retPos[1], retPos[2], PlayerInfo[playerid][pHouse], GetPVarInt(playerid, "furniture_category"));
		mysql_tquery(SQL, gString, "request_creating_mapping", "ifffii", modelid, retPos[0], retPos[1], retPos[2], PlayerInfo[playerid][pHouse], GetPVarInt(playerid, "furniture_category"));
	}
	return 1;
}

function request_creating_mapping(const model, Float:X, Float:Y, Float:Z, const house, const type)
{
	returnTotalObjects ++;
	new
		i = returnTotalObjects-1, h = house;

	mappingInfo[i][mappingID][h] = cache_insert_id();
	mappingInfo[i][mappingModel][h] = model;
	mappingPos[i][0][h] = X;
	mappingPos[i][1][h] = Y;
	mappingPos[i][2][h] = Z;

	mappingPos[i][3][h] = 0;
	mappingPos[i][4][h] = 0;
	mappingPos[i][5][h] = 0;
	
	if(mappingInfo[i][mappingGameModel][h] != INVALID_OBJECT_ID)
		DestroyDynamicObject(mappingInfo[i][mappingGameModel][h]);

	mappingInfo[i][mappingGameModel][h] = CreateDynamicObject(model, X, Y, Z, 0, 0, 0, h, HouseInfo[house][hInteriorVar]);
	return true;
}

function LoadHouses()
{
	if(!cache_num_rows())
		return 1;

	SERVER_HOUSES = cache_num_rows();

	for(new i = 1; i <= cache_num_rows(); i++)
	{
		HouseInfo[i][hID] = cache_get_field_content_int(i-1, "ID");
		HouseInfo[i][hType] = cache_get_field_content_int(i-1, "Type");
		HouseInfo[i][hOwner] = cache_get_field_content_int(i-1, "OwnerSQL");
		HouseInfo[i][hInteriorVar] = cache_get_field_content_int(i-1, "Interior");
		HouseInfo[i][hLocked] = cache_get_field_content_int(i-1, "Locked");
		HouseInfo[i][hRent] = cache_get_field_content_int(i-1, "Rent");
		HouseInfo[i][hRentable] = cache_get_field_content_int(i-1, "Rentable");
		HouseInfo[i][hSafe] = cache_get_field_content_int(i-1, "Safe");
		HouseInfo[i][hRadio] = cache_get_field_content_int(i-1, "Radio");
		HouseInfo[i][hLevel] = cache_get_field_content_int(i-1, "Level");
		HouseInfo[i][hSpecial] = cache_get_field_content_int(i-1, "Special");

		HouseInfo[i][hExterior][0] = cache_get_field_content_float(i-1, "ExteriorX");
		HouseInfo[i][hExterior][1] = cache_get_field_content_float(i-1, "ExteriorY");
		HouseInfo[i][hExterior][2] = cache_get_field_content_float(i-1, "ExteriorZ");

		HouseInfo[i][hInterior][0] = cache_get_field_content_float(i-1, "InteriorX");
		HouseInfo[i][hInterior][1] = cache_get_field_content_float(i-1, "InteriorY");
		HouseInfo[i][hInterior][2] = cache_get_field_content_float(i-1, "InteriorZ");

		/*mysql_format(SQL, gString, sizeof gString, "update `houses` SET `OwnerName` = (select `Name` from `users` where `ID` = '%d') where `OwnerSQL` = '%d';", HouseInfo[i][hOwner], HouseInfo[i][hOwner]);
		mysql_query(SQL, gString);*/

		cache_get_field_content(i-1, "OwnerName", HouseInfo[i][hOwnerName], SQL, MAX_PLAYER_NAME);
		cache_get_field_content(i-1, "Description", HouseInfo[i][hDescription], SQL, 24);
		
		UpdateHouseLabel(i);

		send_mapping_query(i);
	}

	return printf("Houses Loaded (total: %d)", cache_num_rows());
}

send_mapping_query(const house)
{
	mysql_format(SQL, gString, sizeof gString, "select * from `house_mapping` where `House` = '%d';", house);
	mysql_tquery(SQL, gString, "createHouseFurniture", "i", house);
}

returnCategory(const category)
{
	new stringCategory[32];
	switch(category)
	{
		case 0: stringCategory = "TV, Audio, Video";
		case 1: stringCategory = "Fitting";
		case 2: stringCategory = "Paintings";
		case 3: stringCategory = "Doors";
	}
	return stringCategory;
}

returnSize(house)
{
	new returnHouseSize[10];
	switch(house)
	{
		case 0: returnHouseSize = "big";
		case 1: returnHouseSize = "medium";
		case 2: returnHouseSize = "small";
		default: returnHouseSize = "unknown";
	}
	return returnHouseSize;
}

function createHouseFurniture(const house)
{
	if(!cache_num_rows())
		return 1;

	new h = house;

	for(new i; i < cache_num_rows(); i++)
	{
		mappingInfo[i][mappingID][h] 	= 	cache_get_field_content_int(i, "ID");
		mappingInfo[i][mappingModel][h] = 	cache_get_field_content_int(i, "Model");
		mappingInfo[i][mappingType][h] 	= 	cache_get_field_content_int(i, "Type");
		
		mappingPos[i][0][h] = cache_get_field_content_float(i, "X");
		mappingPos[i][1][h] = cache_get_field_content_float(i, "Y");
		mappingPos[i][2][h] = cache_get_field_content_float(i, "Z");
		mappingPos[i][3][h] = cache_get_field_content_float(i, "RotX");
		mappingPos[i][4][h] = cache_get_field_content_float(i, "RotY");
		mappingPos[i][5][h] = cache_get_field_content_float(i, "RotZ");
		
		if(mappingInfo[i][mappingGameModel][h] != INVALID_OBJECT_ID)
			DestroyDynamicObject(mappingInfo[i][mappingGameModel][h]);

		mappingInfo[i][mappingGameModel][h] = CreateDynamicObject(mappingInfo[i][mappingModel][h], mappingPos[i][0][h], mappingPos[i][1][h], mappingPos[i][2][h], mappingPos[i][3][h], mappingPos[i][4][h], mappingPos[i][5][h], h, HouseInfo[house][hInteriorVar]);
		returnTotalObjects ++;
	}
	return 1;
}
UpdateHouseLabel(house)
{
	DestroyDynamicPickup(HouseInfo[house][hPickup]); DestroyDynamicMapIcon(HouseInfo[house][hIcon]);
	DestroyDynamic3DTextLabel(HouseInfo[house][hLabel]); DestroyDynamicArea(HouseInfo[house][hSphere]);

	if(!HouseInfo[house][hRentable])
		format(gString, sizeof gString, "House {909CE7}%d{ffffff}\n{909CE7}%s{FFFFFF}\nOwner: {909CE7}%s{ffffff}\nSize: {909CE7}%s{ffffff}\nTenants: {909CE7}%d{ffffff}\nLevel: {909CE7}%d{ffffff}\n%s", house, HouseInfo[house][hDescription], HouseInfo[house][hOwnerName], returnSize(HouseInfo[house][hType]), Iter_Count(houseRenters<house>), HouseInfo[house][hLevel], (HouseInfo[house][hSpecial] ? ("{909CE7}(VIP House)") : ("")));
	else
		format(gString, sizeof gString, "House {909CE7}%d{ffffff}\n{909CE7}%s{FFFFFF}\nOwner: {909CE7}%s{ffffff}\nSize: {909CE7}%s{ffffff}\nTenants: {909CE7}%d{ffffff}\nRent: {909CE7}$%s{FFFFFF}\nLevel: {909CE7}%d{ffffff}\n{909CE7}To rent a room type /rentroom\n%s", house, HouseInfo[house][hDescription], HouseInfo[house][hOwnerName], returnSize(HouseInfo[house][hType]), Iter_Count(houseRenters<house>), FormatNumber(HouseInfo[house][hRent]), HouseInfo[house][hLevel], (HouseInfo[house][hSpecial] ? ("{909CE7}(VIP House)") : ("")));

	HouseInfo[house][hLabel] 	= 	CreateDynamic3DTextLabel(gString, -1, HouseInfo[house][hExterior][0], HouseInfo[house][hExterior][1] + 0.1, HouseInfo[house][hExterior][2], 40);
	HouseInfo[house][hPickup] 	= 	CreateDynamicPickup(1272, 23, HouseInfo[house][hExterior][0], HouseInfo[house][hExterior][1], HouseInfo[house][hExterior][2], 0, 0, -1, 60);
	HouseInfo[house][hIcon] 	= 	CreateDynamicMapIcon(HouseInfo[house][hExterior][0], HouseInfo[house][hExterior][1], HouseInfo[house][hExterior][2], 31, 0, -1, -1, -1, 500.0, MAPICON_LOCAL);
	HouseInfo[house][hSphere] 	= 	CreateDynamicSphere(HouseInfo[house][hExterior][0], HouseInfo[house][hExterior][1], HouseInfo[house][hExterior][2], 1.5, 0, 0, -1);

	return Streamer_SetIntData(STREAMER_TYPE_AREA, HouseInfo[house][hSphere], E_STREAMER_EXTRA_ID, (house + STREAMER_BEGIN_HOUSE));
}

new
	Float: hInteriorCoords[9][3] = { {140.17, 1366.07, 1083.65}, {225.68, 1021.45, 1084.02}, {-2636.68, 1402.55, 906.46}, {2807.48, -1174.76, 1025.57}, {377.15, 1417.41, 1081.33}, {446.99, 1397.07, 1084.30}, {387.22, 1471.70, 1080.19}, {2237.59, -1081.64, 1049.02}, {-68.81, 1351.21, 1080.21} },
	hInteriorID[9] = { 5, 7, 3, 8, 15, 2, 15, 2, 6 };	

YCMD:debughouse(playerid, params[], help)
{
	if(PlayerInfo[playerid][pAdmin] < 7)
		return 1;

	SCM(playerid, COLOR_GRAD2, "debug started on stage #1");
	mysql_tquery(SQL, "SELECT * FROM `houses`", "LoadServerHouses", "");
	
	SCM(playerid, COLOR_GRAD2, "loop stopped on stage #1 .... continuing with stage #2");
	for(new i; i < SERVER_HOUSES; i++)
	{
		UpdateHouseLabel(i);
		SCM(playerid, COLOR_GRAD2, "debugging house #%d..");
	}
	return SCMF(playerid, -1, "loop succesfully stopped ... %d houses were affected!", SERVER_HOUSES);
}

YCMD:movehouse(playerid, params[], help)
{
	if(PlayerInfo[playerid][pAdmin] < 7)
		return sendAcces(playerid);

	new
		houseId;

	if(sscanf(params, "i", houseId))
		return sendSyntax(playerid, "/movehouse <house id>");

	if(houseId < 1 || houseId > SERVER_HOUSES)
		return SCMF(playerid, COLOR_WHITE, "Invalid house id. (1 - %d)", SERVER_HOUSES);

	new
		Float: hPos[3];

	GetPlayerPos(playerid, hPos[0], hPos[1], hPos[2]);

	SCMF(playerid, -1, "You successfully moved the house #%d.", houseId);

	HouseInfo[houseId][hExterior][0] = hPos[0];
	HouseInfo[houseId][hExterior][1] = hPos[1];
	HouseInfo[houseId][hExterior][2] = hPos[2];

	mysql_format(SQL, gString, sizeof gString, "update `houses` set `ExteriorX` = '%f', `ExteriorY` = '%f', `ExteriorZ` = '%f' where `ID` = '%d';", HouseInfo[houseId][hExterior][0], HouseInfo[houseId][hExterior][1], HouseInfo[houseId][hExterior][2], houseId);
	mysql_tquery(SQL, gString, "", "");

	return UpdateHouseLabel(houseId);
}

YCMD:createhouse(playerid, params[], help)
{	
	if(PlayerInfo[playerid][pAdmin] < 6)
		return sendAcces(playerid);

	new returnType;
	if(sscanf(params, "i", returnType))
		return sendSyntax(playerid, "/createhouse [0 - big | 1 - medium | 2 - small]");

	if(returnType < 0 || returnType > 2)
		return SCM(playerid, -1, "Invalid type.");

	if(MAX_HOUSES <= SERVER_HOUSES + 1)
		return SCM(playerid, -1, "You can't create a house because there are too many on server.");

	new Float:playerPos[3], globalVar;
	GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);

	switch(returnType)
	{
		case 0: globalVar = RandomEx(0, 2);
		case 1: globalVar = RandomEx(3, 5);
		case 2: globalVar = RandomEx(6, 9);
	}
	mysql_format(SQL, gString, sizeof gString, "insert into `houses` (`Interior`, `OwnerSQL`, `Type`, `ExteriorX`, `ExteriorY`, `ExteriorZ`, `InteriorX`, `InteriorY`, `InteriorZ`) values ('%d', '0', '%d', '%f', '%f', '%f', '%f', '%f', '%f');",
		hInteriorID[globalVar], returnType, playerPos[0], playerPos[1], playerPos[2], hInteriorCoords[globalVar][0], hInteriorCoords[globalVar][1], hInteriorCoords[globalVar][2]);
	mysql_tquery(SQL, gString, "WhenHouseIsCreated", "iffffffii", returnType, playerPos[0], playerPos[1], playerPos[2], hInteriorCoords[globalVar][0], hInteriorCoords[globalVar][1], hInteriorCoords[globalVar][2], hInteriorID[globalVar], playerid);

	return SCM(playerid, COLOR_GREY, "Solicitarea ta de a fost trimisa catre baza de date.");
}


forward public WhenHouseIsCreated(const type, Float:X, Float:Y, Float:Z, Float:iX, Float:iY, Float:iZ, interior, const requester);
public WhenHouseIsCreated(const type, Float:X, Float:Y, Float:Z, Float:iX, Float:iY, Float:iZ, interior, const requester)
{
	SERVER_HOUSES ++;
	new i = SERVER_HOUSES;

	HouseInfo[i][hID] = cache_insert_id();
	HouseInfo[i][hType] = type;

	HouseInfo[i][hOwner] = 0;
	format(HouseInfo[i][hOwnerName], 8, "AdmBot");

	HouseInfo[i][hExterior][0] = X;
	HouseInfo[i][hExterior][1] = Y;
	HouseInfo[i][hExterior][2] = Z;

	HouseInfo[i][hInterior][0] = iX;
	HouseInfo[i][hInterior][1] = iY;
	HouseInfo[i][hInterior][2] = iZ;

	HouseInfo[i][hInteriorVar] = interior;
	UpdateHouseLabel(i);

	return ABroadCast(COLOR_ADMCHAT, 1, "[Admin] %s: a creat o noua casa ID %d", GetName(requester), HouseInfo[i][hID]);
}

YCMD:rentroom(playerid, params[], help)
{
	if(PlayerInfo[playerid][pHouse])
		return SCM(playerid, COLOR_GREY, "You already rented a room somewhere. Type /unrentroom before rent a room.");

	new
		houseAreaId = GetPVarInt(playerid, "streamer_house_areaid");		

	if(houseAreaId < 1 || houseAreaId > SERVER_HOUSES)
		return 1;

	if(HouseInfo[houseAreaId][hLocked] == 1 || HouseInfo[houseAreaId][hRentable] != 1)
		return SCM(playerid, -1, "You cannot rent this house because it's locked by the owner.");

    SCM(playerid, COLOR_WHITE, "Congratulations, You can enter and exit here anytime.");
    SCM(playerid, COLOR_WHITE, "Type /help to review the new property help section.");

    GameTextForPlayer(playerid, "~w~Welcome Home~n~You can exit at any time by moving to this door and press enter", 5000, 3);

	PlayerInfo[playerid][pHouse] = houseAreaId;
	Iter_Add(houseRenters<houseAreaId>, playerid);

	houseAreaId = PlayerInfo[playerid][pHouse];

	SetPlayerPos(playerid, HouseInfo[houseAreaId][hInterior][0], HouseInfo[houseAreaId][hInterior][1], HouseInfo[houseAreaId][hInterior][2]);
	SetPlayerInterior(playerid, HouseInfo[houseAreaId][hInteriorVar]);
	SetPlayerVirtualWorld(playerid, houseAreaId);
	
    if(HouseInfo[houseAreaId][hRadio])
    {
        StopAudioStreamForPlayer(playerid);
        PlayAudioStreamForPlayer(playerid, RadioLinks[HouseInfo[houseAreaId][hRadio]]);
    }

    s_PlayerInfo[playerid][pSInHouse] = houseAreaId;
    PlayerInfo[playerid][pSpawnChange] = 1;

	mysql_format(SQL, gString, sizeof gString, "update `users` set `House` = '%d', `SpawnChange` = '1' where `id` = '%d';", PlayerInfo[playerid][pHouse], PlayerInfo[playerid][pSQLID]);
	mysql_tquery(SQL, gString, "", "");

	return UpdateHouseLabel(PlayerInfo[playerid][pHouse]);
}

YCMD:unrentroom(playerid, params[], help)
{
	if(PlayerInfo[playerid][pHouse] == 0)
		return SCM(playerid, -1, "You don't have a rented house.");

	new
		houseId = PlayerInfo[playerid][pHouse];		

	if(HouseInfo[houseId][hOwner] == PlayerInfo[playerid][pSQLID])
		return SCM(playerid, -1, "You can't use this command because you are the house owner.");

	SCM(playerid, -1, "{B8FFDB}You are now homeless.");

	Iter_Remove(houseRenters<houseId>, playerid);
	UpdateHouseLabel(houseId);

	PlayerInfo[playerid][pHouse] = 0;
	PlayerInfo[playerid][pSpawnChange] = 0;
	
	mysql_format(SQL, gString, sizeof gString, "update `users` set `House` = '0', `SpawnChange` = '0' where `id` = '%d';", PlayerInfo[playerid][pSQLID]);
	mysql_tquery(SQL, gString, "", "");
	return 1;
}

YCMD:findhouse(playerid, params[], help)
{
	if(s_PlayerInfo[playerid][pSCP])
		return SCM(playerid, -1, "You can't use this command while you have an active checkpoint.");

	new
		houseId;

	if(sscanf(params, "i", houseId))
		return sendSyntax(playerid, "/findhouse <House ID>");

	if(houseId < 1 || houseId > SERVER_HOUSES)
		return SCMF(playerid, COLOR_WHITE, "Invalid house id. (1 - %d)", SERVER_HOUSES);

	SCMF(playerid, -1, "I have placed a checkpoint at house #%d. Please follow it.", houseId);
	s_PlayerInfo[playerid][pSCP] = 1;

	return SetPlayerCheckpoint(playerid, HouseInfo[houseId][hExterior][0], HouseInfo[houseId][hExterior][1], HouseInfo[houseId][hExterior][2], 2.0);
}

YCMD:housemenu(playerid, params[], help)
{
	new
		houseId = PlayerInfo[playerid][pHouse];

	if(HouseInfo[houseId][hOwner] != PlayerInfo[playerid][pSQLID] || !houseId)
		return SCM(playerid, -1, "Only house owners can use this commands.");

	format(gString, sizeof gString, "Lock/Unlock House\nChange house description\nShow tenants\nModify house rent\nManage safe\nSell house to state\nHouse music\nHouse upgrades\n%s", HouseInfo[houseId][hSpecial] ? ("House furniture") : (""));
	Dialog_Show(playerid, DIALOG_HOUSE, DIALOG_STYLE_LIST, "House menu:", gString, "Select", "Exit");

	return 1;
}

YCMD:renters(playerid, params[], help)
{
	if(!PlayerInfo[playerid][pHouse])
		return SCM(playerid, -1, "You don't have house or you don't have rentroom.");

	new houseId = PlayerInfo[playerid][pHouse];

	if(!Iter_Count(houseRenters<houseId>))
		return SCM(playerid, -1, "* There are no renters online.");

	foreach(new i : houseRenters<houseId>)
		SCMF(playerid, -1, "* %s (%d)", GetName(i), i);

	return SCMF(playerid, -1, "* There are %d renters online.", Iter_Count(houseRenters<houseId>));
}

YCMD:home(playerid, params[], help)
{
	if(!PlayerInfo[playerid][pHouse])
		return SCM(playerid, -1, "You don't have house or you don't have rentroom.");

	if(s_PlayerInfo[playerid][pSCP])
		return SCM(playerid, -1, "You can't use this command while you have an active checkpoint.");

	new
		houseId = PlayerInfo[playerid][pHouse];
	
	SCM(playerid, COLOR_WHITE, "A checkpoint has been set to your house.");

	SetPlayerCheckpoint(playerid, HouseInfo[houseId][hExterior][0], HouseInfo[houseId][hExterior][1], HouseInfo[houseId][hExterior][2], 2.0);
	s_PlayerInfo[playerid][pSCP] = 1;
	
	return 1;
}

function showHouseFurniture(const playerid)
{
    new returnObjectModel, returnObjectType;
    format(gString, sizeof gString, "Item\tCategory\nBuy a new item (%d/25)\nEdit items position\nDelete item\nDelete all furniture items\n", cache_num_rows());

    if(!cache_num_rows())
        Dialog_Show(playerid, DIALOG_FURNITURE, DIALOG_STYLE_TABLIST_HEADERS, "House furniture:", gString, "Select", "Exit");

    HouseInfo[PlayerInfo[playerid][pHouse]][hObjects] = cache_num_rows();
    for(new i; i < cache_num_rows(); i++)
    {
        returnObjectModel = cache_get_field_content_int(i, "Model");
        returnObjectType = cache_get_field_content_int(i, "Type");

        format(gString, sizeof gString, "%s\n%d\t%s\n", gString, returnObjectModel, returnCategory(returnObjectType));
    }
    Dialog_Show(playerid, DIALOG_FURNITURE, DIALOG_STYLE_TABLIST_HEADERS, "House furniture:", gString, "Select", "Exit");
    return 1;
}

Dialog:DIALOG_FURNITURE(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    switch(listitem)
    {
        case 0:
        {
            if(returnTotalObjects >= MAX_HOUSE_OBJECTS)
                return SCMF(playerid, -1, "[objects] MAX_HOUSE_OBJECTS size is highest than %d. You can't create objects!", MAX_HOUSE_OBJECTS);

            if(HouseInfo[PlayerInfo[playerid][pHouse]][hObjects] >= 25)
                return SCM(playerid, -1, "Ai prea multe obiecte cumparate. Le poti sterge folosind comanda /housemenu.");

            Dialog_Show(playerid, DIALOG_FURNITURE_BUY, DIALOG_STYLE_TABLIST_HEADERS, "House furniture:", "Category\tItem Price\nTV, Audio, Video\t$20.000\nFitting\t$20.000\nPaintings\t$20.000\nDoors\t$20.000", "Select", "Exit");
        }
        case 1:
        {
            SCM(playerid, -1, "Foloseste mouseul pentru a selecta un obiect din mobilier apoi meniul pentru a il repozitiona."), SelectObject(playerid);
            SetPVarInt(playerid, "house_delete_object", 0), SetPVarInt(playerid, "house_repos_object", 1);
        }
        case 2:
        {
            SCM(playerid, -1, "Foloseste mouseul pentru a selecta un obiect din mobilier apoi meniul pentru a il sterge."), SelectObject(playerid);
            SetPVarInt(playerid, "house_delete_object", 1), SetPVarInt(playerid, "house_repos_object", 0);
        }
        case 3: Dialog_Show(playerid, DIALOG_DEL_ITEMS, DIALOG_STYLE_MSGBOX, "House furniture:", "Esti sigur ca vrei sa stergi toate obiectele din casa?\nOdata ce ai facut acest lucru, casa ta o sa ramana fara obiecte.", "Select", "Exit");
    }
    return 1;
}

Dialog:DIALOG_DEL_ITEMS(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    SCM(playerid, -1, "Toate itemele din casa ta au fost sterse.");
    
    for(new i; i < returnTotalObjects; i++)
        DestroyDynamicObject(mappingInfo[i][mappingGameModel][PlayerInfo[playerid][pHouse]]);

    mysql_format(SQL, gString, sizeof gString, "delete from `house_mapping` where `House` = '%d';", PlayerInfo[playerid][pHouse]);
    mysql_tquery(SQL, gString, "", "");
    return 1;
}

returnTotalItems(const listitem)
{
    switch(listitem)
    {
        case 0: return 12;
        case 1: return 39;
        case 2: return 23;
        case 3: return 42;
        default: return 0;
    }
    return 0;
}

Dialog:DIALOG_FURNITURE_BUY(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    ShowModelSelectionMenuEx(playerid, houseFurnitures[listitem], returnTotalItems(listitem), returnCategory(listitem), -1, 0.0, 0.0, 0.0, 2.0, 0x4A5A6BBB, 0x88888899 , 0xFFFF00AA);
    SetPVarInt(playerid, "furniture_category", listitem);
    return 1;
}

Dialog:DIALOG_HOUSE(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	switch(listitem)
	{
		case 0:
		{
			new
				houseId = PlayerInfo[playerid][pHouse];

			SCMF(playerid, -1, "Usa casei tale a fost %s.", HouseInfo[houseId][hLocked] ? ("descuiata") : ("incuiata"));
			
			HouseInfo[houseId][hLocked] = HouseInfo[houseId][hLocked] ? (0) : (1);

			mysql_format(SQL, gString, sizeof gString, "update `houses` set `Locked` = '%d' where `ID` = '%d';", HouseInfo[houseId][hLocked], houseId);
			mysql_tquery(SQL, gString, "", "");
		}
		case 1:
		{
			Dialog_Show(playerid, DIALOG_HOUSEDESCRIPTION, DIALOG_STYLE_INPUT, "House menu:", "Please insert here your desired house description:", "Set", "Exit");
		}
		case 2:
		{
			new
				houseId = PlayerInfo[playerid][pHouse];

			if(!Iter_Count(houseRenters<houseId>))
				return SCM(playerid, -1, "* There are no renters online.");

			foreach(new i : houseRenters<houseId>)
				SCMF(playerid, -1, "* %s (%d)", GetName(i), i);

			return SCMF(playerid, -1, "* There are %d renters online.", Iter_Count(houseRenters<houseId>));
		}
		case 3:
		{
			Dialog_Show(playerid, DIALOG_HOUSERENT, DIALOG_STYLE_LIST, "House menu:", "Set rentable\nRemove rent", "Select", "Exit");
		}
		case 4:
		{
			format(gString, sizeof gString, "Safe status: $%s\nWithdraw money", FormatNumber(HouseInfo[PlayerInfo[playerid][pHouse]][hSafe]));
			Dialog_Show(playerid, DIALOG_HOUSESAFE, DIALOG_STYLE_LIST, "House menu:", gString, "Select", "Exit");
		}
		case 5:
		{

		}
		case 6:
		{
			new
				radioString[512];

			for(new i; i < sizeof RadioNames; i++)
			{
				format(radioString, sizeof radioString, "%s%s\n", radioString, RadioNames[i]);
			}
			Dialog_Show(playerid, DIALOG_HOUSERADIO, DIALOG_STYLE_LIST, "House radio:", radioString, "Select", "Exit");
		}
		case 7:
		{
			Dialog_Show(playerid, DIALOG_HOUSEUPGRADES, DIALOG_STYLE_TABLIST_HEADERS, "House menu:", "Upgrade Type\tUpgrade Price\nSpecial House\t{FFF000}200 premium points", "Select", "Exit");
		}
		case 8:
		{
			if(!s_PlayerInfo[playerid][pSInHouse] || s_PlayerInfo[playerid][pSInHouse] != PlayerInfo[playerid][pHouse])
				return SCM(playerid, -1, "You need to be in your house in order to acces this category.");

            mysql_format(SQL, gString, sizeof gString, "select * from `house_mapping` where `House` = '%d';", PlayerInfo[playerid][pHouse]);
            mysql_tquery(SQL, gString, "showHouseFurniture", "i", playerid);
		}
	}	
	return 1;
}

Dialog:DIALOG_HOUSEDESCRIPTION(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	if(isnull(inputtext) || strlen(inputtext) > 24)
		return Dialog_Show(playerid, DIALOG_HOUSEDESCRIPTION, DIALOG_STYLE_INPUT, "House menu:", "Please insert here your desired house description:", "Set", "Exit");
	
	SCMF(playerid, -1, "House name set to: {B8DBFF}%s", inputtext);

	new
		houseId = PlayerInfo[playerid][pHouse];

	format(HouseInfo[houseId][hDescription], 24, inputtext);

	mysql_format(SQL, gString, sizeof gString, "update `houses` set `Description` = '%s' where `ID` = '%d';", inputtext, houseId);
	mysql_tquery(SQL, gString, "", "");
	
	return UpdateHouseLabel(houseId);
}

Dialog:DIALOG_HOUSETENANTS(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	new houseId = PlayerInfo[playerid][pHouse];

	if(!Iter_Count(houseRenters<houseId>))
		return SCM(playerid, -1, "* There are no renters online.");

	foreach(new i : houseRenters<houseId>)
		SCMF(playerid, -1, "* %s (%d)", GetName(i), i);

	return SCMF(playerid, -1, "* There are %d renters online.", Iter_Count(houseRenters<houseId>));

		/*case 1:
		{
			new
				houseId = PlayerInfo[playerid][pHouse];
		
			if(Iter_Count(houseRenters<houseId>))
				UpdateHouseLabel(houseId);

			foreach(new i : houseRenters<houseId>)
			{
				SCMF(i, -1, "You will be spawned at default location, because the owner of the house #%d evicted you out.", houseId);
				
				PlayerInfo[i][pHouse] = 0;
				PlayerInfo[i][pSpawnChange] = 0;
				Iter_SafeRemove(houseRenters<houseId>, i, i);
			}
			SCM(playerid, -1, "If your house had tenants, they were successfully evicted.");
		
			mysql_format(SQL, gString, sizeof gString, "update `users` set `House` = '0', `SpawnChange` = '0' where `House` = '%d' and `id` != '%d';", PlayerInfo[playerid][pHouse], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(SQL, gString, "", "");
		}*/
}

Dialog:DIALOG_HOUSERENT(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	new houseId = PlayerInfo[playerid][pHouse];

	switch(listitem)
	{
		case 0:
		{
			SCM(playerid, -1, "Jucatorii pot sta cu chirie in casa ta.");
			HouseInfo[houseId][hRentable] = 1;
		}
		case 1:
		{
			SCM(playerid, -1, "Jucatorii nu mai pot sta cu chirie in casa ta.");
			HouseInfo[houseId][hRentable] = 0;
		}
	}
	mysql_format(SQL, gString, sizeof gString, "update `houses` set `Rentable` = '%d' where `ID` = '%d';", HouseInfo[houseId][hRentable], houseId);
	mysql_tquery(SQL, gString, "", "");

	return UpdateHouseLabel(houseId);
}

Dialog:DIALOG_HOUSESAFE(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	new
		houseId = PlayerInfo[playerid][pHouse];

	if(!HouseInfo[houseId][hSafe])
		return 1;

	if(listitem == 1)
	{
		SCMF(playerid, -1, "{B8FFDB}You have withdrawn $%s from your cashbox.", FormatNumber(HouseInfo[houseId][hSafe]));

		GivePlayerMoney(playerid, HouseInfo[houseId][hSafe]);
		HouseInfo[houseId][hSafe] = 0;

		mysql_format(SQL, gString, sizeof gString, "update `houses` set `Safe` = '0' where `ID` = '%d';", houseId);
		mysql_tquery(SQL, gString, "", "");
	}
	return 1;
}

Dialog:DIALOG_HOUSERADIO(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	new
		houseId = PlayerInfo[playerid][pHouse];

	HouseInfo[houseId][hRadio] = listitem;

	SCMF(playerid, COLOR_GREY, "House audio stream changed to: %s", HouseInfo[houseId][hRadio] ? (RadioNames[listitem]) : ("off"));

	StopAudioStreamForPlayer(playerid);

	if(listitem > 0)
	{
		if(s_PlayerInfo[playerid][pSInHouse] == houseId)
			PlayAudioStreamForPlayer(playerid, RadioLinks[listitem]);
	}

	foreach(new i : houseRenters<houseId>)
	{
		if(s_PlayerInfo[playerid][pSInHouse] == houseId)
		{
			StopAudioStreamForPlayer(i);

			if(listitem > 0)
				PlayAudioStreamForPlayer(i, RadioLinks[listitem]);
		}
	}

	mysql_format(SQL, gString, sizeof gString, "update `houses` set `Radio` = '%d' where `ID` = '%d';", listitem, houseId);
	return mysql_tquery(SQL, gString, "", "");
}

Dialog:DIALOG_HOUSEUPGRADES(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	switch(listitem)
	{
		case 0:
		{
			//if(PlayerInfo[playerid][pPremiumPoints] < 200)
			//	return SCM(playerid, -1, "Nu poti face acest lucru, deoarece nu detii 200 de puncte premium.");

			new houseId = PlayerInfo[playerid][pHouse];
			
			if(HouseInfo[houseId][hSpecial])
				return SCM(playerid, -1, "Casa ta dispune deja de acest upgrade.");

			SCM(playerid, -1, "Ai achizitionat upgradeul 'Special House' si ai platit 200 puncte premium.");

			HouseInfo[houseId][hSpecial] = 1;
			//PlayerInfo[playerid][pPremiumPoints] -= 200;

			UpdateHouseLabel(houseId);

			mysql_format(SQL, gString, sizeof gString, "update `houses` set `Special` = '1' where `ID` = '%d';", houseId);
			mysql_tquery(SQL, gString, "", "");
		}
	}

	return 1;
}
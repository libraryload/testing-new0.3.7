#include <YSI_Coding\y_hooks>
#define MAX_DEALER_VEHICLES 150

enum dealerInfo {
	dealer_vModel, dealer_vPrice, dealer_vStock
};
new
	dealerData[MAX_DEALER_VEHICLES][dealerInfo], Iterator:dealerVehicles<MAX_DEALER_VEHICLES>,
	Text: DealerTD[8], PlayerText: DealerPTD[MAX_PLAYERS][3];

function loadServerDealership()
{
	if(!cache_num_rows())
		return print("[MYSQL] Your `dealer_cars` table is empty!");

	Iter_Clear(dealerVehicles);
	for(new i=0; i < cache_num_rows(); ++i)
	{
		new
			stockId = cache_get_field_content_int(i, "ds_Id");

		if(stockId > sizeof dealerData)
			break;

		Iter_Add(dealerVehicles, stockId);

		dealerData[stockId][dealer_vModel]		=		cache_get_field_content_int(i, "ds_vModel");
		dealerData[stockId][dealer_vPrice]		=		cache_get_field_content_int(i, "ds_vPrice");
		dealerData[stockId][dealer_vStock]		=		cache_get_field_content_int(i, "ds_vStock");
	}
	return printf("Dealership Loaded (total: %d)", cache_num_rows());
}

YCMD:sellcar(playerid, params[], help) return SCM(playerid, -1, "Optiune invechita. Vehiculele pot fi vandute din meniul (/cars) accesand optiunea 'Sell vehicle (to Dealership)'");

insertPlayerVehicle(playerid, playerVehicleModel, km, vip, special)
{
    new Float:carParkPosition[4];

    carParkPosition[0] = 2156.0837;
    carParkPosition[1] = -1143.1023;
    carParkPosition[2] = 24.6675;
    carParkPosition[3] = 0.0;

    mysql_format(SQL, gString, sizeof gString, "insert into `cars` (`Model`, `Description`, `Owner`, `BuyTime`, `Locationx`, `Locationy`, `Locationz`, `Angle`, `Insurancecar`, `KM`, `VIP`, `Special`, `Lockk`) values ('%d', '%e', '%e', '%d', '%f', '%f', '%f', '%f', '4', '%d', '%d', '%d', '1')", playerVehicleModel, aVehicleNames[playerVehicleModel - 400], PlayerInfo[playerid][pNormalName], gettime(), carParkPosition[0], carParkPosition[1], carParkPosition[2], carParkPosition[3], km, vip, special);
    mysql_tquery(SQL, gString, "onVehicleInserted", "dd", playerid, playerVehicleModel);
    return 1;
}

function onVehicleInserted(playerid, playerVehicleModel)
{
	new
		stockId = GetPVarInt(playerid, "dealer_carId");

	format(gString, sizeof gString, "%s [user:%d] bought a %s [car:%d] for $%s.", GetName(playerid), PlayerInfo[playerid][pSQLID], aVehicleNames[playerVehicleModel - 400], cache_insert_id(), FormatNumber(dealerData[stockId][dealer_vPrice]));
	ABroadCast(COLOR_RED, 1, gString);

	mysql_format(SQL, gString, sizeof gString, "select * from `cars` where `ID` = '%d';", cache_insert_id());
    mysql_tquery(SQL, gString, "LoadPlayerVehicles", "");

    return 1;
}
	/*
	new
		vehicleDBId = cache_insert_id(), Float: carParkPosition[4];

    carParkPosition[0] = 2156.0837;
    carParkPosition[1] = -1143.1023;
    carParkPosition[2] = 24.6675;
    carParkPosition[3] = 0.0;

    CarInfo[vehicleDBId][cID] = vehicleDBId;
    CarInfo[vehicleDBId][cModel] = playerVehicleModel;
   	
    CarInfo[vehicleDBId][cBuyTime] = gettime();

   	format(CarInfo[vehicleDBId][cLicense], 24, "NewCar");
    format(CarInfo[vehicleDBId][cOwner], MAX_PLAYER_NAME, PlayerInfo[playerid][pNormalName]);
    format(CarInfo[vehicleDBId][cDescription], 32, aVehicleNames[playerVehicleModel - 400]);

    CarInfo[vehicleDBId][cKM] = 0.0;
    CarInfo[vehicleDBId][cLock] = 1;
    CarInfo[vehicleDBId][cFuel] = 100;
    CarInfo[vehicleDBId][cInsurancecar] = 4;
    CarInfo[vehicleDBId][cInscarprice] = 5000;

    CarInfo[vehicleDBId][cHealth] = 1000.0;

    CarInfo[vehicleDBId][cDamageStatus][0] = 0; CarInfo[vehicleDBId][cDamageStatus][1] = 0;
    CarInfo[vehicleDBId][cDamageStatus][2] = 0; CarInfo[vehicleDBId][cDamageStatus][3] = 0;

    CarInfo[vehicleDBId][cLocationx] = carParkPosition[0]; CarInfo[vehicleDBId][cLastLocationx] = carParkPosition[0];
    CarInfo[vehicleDBId][cLocationy] = carParkPosition[1]; CarInfo[vehicleDBId][cLastLocationy] = carParkPosition[1];
    CarInfo[vehicleDBId][cLocationz] = carParkPosition[2]; CarInfo[vehicleDBId][cLastLocationz] = carParkPosition[2];

    CarInfo[vehicleDBId][cAngle] = carParkPosition[3];
    CarInfo[vehicleDBId][cLastAngle] = carParkPosition[3];
	
	new
    	vehicleGameID = CreateVehicle(CarInfo[vehicleDBId][cModel], CarInfo[vehicleDBId][cLocationx], CarInfo[vehicleDBId][cLocationy], CarInfo[vehicleDBId][cLocationz], 0, 1, 1, -1);

    VehicleSQL[vehicleGameID] = vehicleDBId;
    Gas[vehicleGameID] = CarInfo[vehicleDBId][cFuel];

    CarInfo[vehicleDBId][cSpawnTime] = gettime() + MAX_VEHICLE_SPAWN_TIME;
	Iter_Add(spawnedVehicles, vehicleGameID);
    SetVehicleNumberPlate(vehicleGameID, CarInfo[vehicleDBId][cLicense]);
	return 1;
}*/

OnShowDealership(playerid, bool: hide = false)
{
	if(hide == true)
	{
		for(new i; i < sizeof DealerTD; ++i)
			TextDrawHideForPlayer(playerid, DealerTD[i]);

		for(new i; i < 3; ++i) // sizeof DealerPTD
			PlayerTextDrawHide(playerid, DealerPTD[playerid][i]);

		CancelSelectTextDraw(playerid);

		DeletePVar(playerid, "in_dealer");
		DeletePVar(playerid, "dealer_carId");
		return 1;
	}
	for(new i; i < sizeof DealerTD; ++i)
		TextDrawShowForPlayer(playerid, DealerTD[i]);

	for(new i; i < 3; ++i) // sizeof DealerPTD
		PlayerTextDrawShow(playerid, DealerPTD[playerid][i]);

	SelectTextDraw(playerid, 0x0C4999AA);

	SetPVarInt(playerid, "in_dealer", 1);
	SetPVarInt(playerid, "dealer_carId", 1);

	return OnDealerTextDrawUpdate(playerid);
}

OnDealerTextDrawUpdate(playerid)
{
	new
		ds_vStockId = GetPVarInt(playerid, "dealer_carId");

	PlayerTextDrawSetPreviewModel(playerid, DealerPTD[playerid][0], dealerData[ds_vStockId][dealer_vModel]);
	PlayerTextDrawShow(playerid, DealerPTD[playerid][0]);

	format(gString, sizeof gString, "%s", aVehicleNames[dealerData[ds_vStockId][dealer_vModel] - 400]);
	PlayerTextDrawSetString(playerid, DealerPTD[playerid][1], gString);

	format(gString, sizeof gString, "Price: ~G~$%s~W~~H~~N~Stock: ~R~%d~W~~H~~N~Max Speed: ~R~%dKM/H", FormatNumber(dealerData[ds_vStockId][dealer_vPrice]), dealerData[ds_vStockId][dealer_vStock], GetVehicleMaxSpeed(dealerData[ds_vStockId][dealer_vModel]));
	PlayerTextDrawSetString(playerid, DealerPTD[playerid][2], gString);

	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(clickedid == Text: INVALID_TEXT_DRAW)
	{
		if(GetPVarInt(playerid, "in_dealer"))
			return OnShowDealership(playerid, true);
	}

	if(clickedid == DealerTD[1])
	{
		if(GetPVarInt(playerid, "dealer_carId") == 1)
			SetPVarInt(playerid, "dealer_carId", Iter_Count(dealerVehicles) + 1);
		
		SetPVarInt(playerid, "dealer_carId", GetPVarInt(playerid, "dealer_carId") - 1);

		return OnDealerTextDrawUpdate(playerid);
	}
	if(clickedid == DealerTD[2])
	{
		if(GetPVarInt(playerid, "dealer_carId") == Iter_Count(dealerVehicles))
			SetPVarInt(playerid, "dealer_carId", 0);
		
		SetPVarInt(playerid, "dealer_carId", GetPVarInt(playerid, "dealer_carId") + 1);

		return OnDealerTextDrawUpdate(playerid);
	}
	if(clickedid == DealerTD[6])
	{
		//new
		//	stockId = GetPVarInt(playerid, "dealer_carId");

		//if(dealerData[stockId][dealer_vStock] == 0)
		//	return SCM(playerid, -1, "Acest vehicul nu se afla in stock.");

		//if(PlayerInfo[playerid][pAccount] < dealerData[stockId][dealer_vPrice])
		//	return SCMF(playerid, -1, "Nu detii suma de $%s pentru a putea achizitiona acest vehicul.", FormatNumber(dealerData[stockId][dealer_vPrice]));

		SetPVarInt(playerid, "dealer_dialog", 1);

		new
			codeString[36];

	    new chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	    for(new i = 0 ; i < 5; i++)
	        codeString[i] = chars[random(36)];

		SetPVarString(playerid, "dealer_code", codeString);

		format(gString, sizeof gString, "Are you sure you want to buy this vehicle?\nIf yes please type the code in the box bellow: %s", codeString);

		return Dialog_Show(playerid, DIALOG_BUY_VEHICLE, DIALOG_STYLE_INPUT, "Buy car", gString, "Buy vehicle", "Cancel");
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

Dialog:DIALOG_BUY_VEHICLE(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new codeString[6];
    GetPVarString(playerid, "dealer_code", codeString, sizeof codeString);

   	if(strcmp(inputtext, codeString, true) == 0)
   	{
   		new 
   			stockId = GetPVarInt(playerid, "dealer_carId");

   		insertPlayerVehicle(playerid, dealerData[stockId][dealer_vModel], 0, 0, 0);
   		
   		return SCMF(playerid, -1, "Vehicul achizitionat. Ai platit $%s. Vehiculul poate fi localizat folosind comanda </findcar>.", FormatNumber(dealerData[stockId][dealer_vPrice]));
   	}
   	else
   	{
   		DeletePVar(playerid, "dealer_code");
   		DeletePVar(playerid, "dealer_dialog");

   		return SCM(playerid, -1, "Codul introdus nu este corect.");
   	}
}

hook OnGameModeInit()
{
	DealerTD[0] = TextDrawCreate(319.866424, 316.933319, "box");
	TextDrawLetterSize(DealerTD[0], 0.000000, 9.213327);
	TextDrawTextSize(DealerTD[0], 0.000000, 229.800018);
	TextDrawAlignment(DealerTD[0], 2);
	TextDrawColor(DealerTD[0], -1);
	TextDrawUseBox(DealerTD[0], 1);
	TextDrawBoxColor(DealerTD[0], 80);
	TextDrawSetShadow(DealerTD[0], 0);
	TextDrawSetOutline(DealerTD[0], 0);
	TextDrawBackgroundColor(DealerTD[0], 255);
	TextDrawFont(DealerTD[0], 1);
	TextDrawSetProportional(DealerTD[0], 1);
	TextDrawSetShadow(DealerTD[0], 0);
 
	DealerTD[1] = TextDrawCreate(214.333358, 349.288909, "<");
	TextDrawLetterSize(DealerTD[1], 0.314999, 1.450000);
	TextDrawTextSize(DealerTD[1], 10.000000, 15.000000);
	TextDrawAlignment(DealerTD[1], 2);
	TextDrawColor(DealerTD[1], -1);
	TextDrawUseBox(DealerTD[1], 0);
	TextDrawBoxColor(DealerTD[1], 255);
	TextDrawSetShadow(DealerTD[1], 1);
	TextDrawSetOutline(DealerTD[1], 0);
	TextDrawBackgroundColor(DealerTD[1], 255);
	TextDrawFont(DealerTD[1], 1);
	TextDrawSetProportional(DealerTD[1], 1);
	TextDrawSetShadow(DealerTD[1], 1);
	TextDrawSetSelectable(DealerTD[1], true);
	 
	DealerTD[2] = TextDrawCreate(282.333374, 349.288909, ">");
	TextDrawLetterSize(DealerTD[2], 0.314999, 1.450000);
	TextDrawTextSize(DealerTD[2], 10.000000, 15.000000);
	TextDrawAlignment(DealerTD[2], 2);
	TextDrawColor(DealerTD[2], -1);
	TextDrawUseBox(DealerTD[2], 0);
	TextDrawBoxColor(DealerTD[2], 255);
	TextDrawSetShadow(DealerTD[2], 1);
	TextDrawSetOutline(DealerTD[2], 0);
	TextDrawBackgroundColor(DealerTD[2], 255);
	TextDrawFont(DealerTD[2], 1);
	TextDrawSetProportional(DealerTD[2], 1);
	TextDrawSetShadow(DealerTD[2], 1);
	TextDrawSetSelectable(DealerTD[2], true);
	 
	DealerTD[3] = TextDrawCreate(319.866424, 316.933319, "box");
	TextDrawLetterSize(DealerTD[3], 0.000000, -0.126672);
	TextDrawTextSize(DealerTD[3], 0.000000, 229.800018);
	TextDrawAlignment(DealerTD[3], 2);
	TextDrawColor(DealerTD[3], -1);
	TextDrawUseBox(DealerTD[3], 1);
	TextDrawBoxColor(DealerTD[3], 80);
	TextDrawSetShadow(DealerTD[3], 0);
	TextDrawSetOutline(DealerTD[3], 0);
	TextDrawBackgroundColor(DealerTD[3], 255);
	TextDrawFont(DealerTD[3], 1);
	TextDrawSetProportional(DealerTD[3], 1);
	TextDrawSetShadow(DealerTD[3], 0);
	 
	DealerTD[4] = TextDrawCreate(319.866424, 400.934173, "box");
	TextDrawLetterSize(DealerTD[4], 0.000000, -0.126672);
	TextDrawTextSize(DealerTD[4], 0.000000, 229.800018);
	TextDrawAlignment(DealerTD[4], 2);
	TextDrawColor(DealerTD[4], -1);
	TextDrawUseBox(DealerTD[4], 1);
	TextDrawBoxColor(DealerTD[4], 80);
	TextDrawSetShadow(DealerTD[4], 0);
	TextDrawSetOutline(DealerTD[4], 0);
	TextDrawBackgroundColor(DealerTD[4], 255);
	TextDrawFont(DealerTD[4], 1);
	TextDrawSetProportional(DealerTD[4], 1);
	TextDrawSetShadow(DealerTD[4], 0);
	 
	DealerTD[5] = TextDrawCreate(297.966735, 317.403625, "box");
	TextDrawLetterSize(DealerTD[5], 0.000000, 9.128344);
	TextDrawTextSize(DealerTD[5], 0.000000, -1.900001);
	TextDrawAlignment(DealerTD[5], 2);
	TextDrawColor(DealerTD[5], -1);
	TextDrawUseBox(DealerTD[5], 1);
	TextDrawBoxColor(DealerTD[5], 150);
	TextDrawSetShadow(DealerTD[5], 0);
	TextDrawSetOutline(DealerTD[5], 0);
	TextDrawBackgroundColor(DealerTD[5], 255);
	TextDrawFont(DealerTD[5], 1);
	TextDrawSetProportional(DealerTD[5], 1);
	TextDrawSetShadow(DealerTD[5], 0);
	 
	DealerTD[6] = TextDrawCreate(367.399353, 391.519683, "BUY");
	TextDrawLetterSize(DealerTD[6], 0.209666, 0.893408);
	TextDrawTextSize(DealerTD[6], 5.000000, 134.830642);
	TextDrawAlignment(DealerTD[6], 2);
	TextDrawColor(DealerTD[6], -1);
	TextDrawUseBox(DealerTD[6], 1);
	TextDrawBoxColor(DealerTD[6], -2147483393);
	TextDrawSetShadow(DealerTD[6], 0);
	TextDrawSetOutline(DealerTD[6], 0);
	TextDrawBackgroundColor(DealerTD[6], 255);
	TextDrawFont(DealerTD[6], 1);
	TextDrawSetProportional(DealerTD[6], 1);
	TextDrawSetShadow(DealerTD[6], 0);
	TextDrawSetSelectable(DealerTD[6], true);
	 
	DealerTD[7] = TextDrawCreate(367.399353, 379.118927, "TEST DRIVE");
	TextDrawLetterSize(DealerTD[7], 0.209666, 0.893408);
	TextDrawTextSize(DealerTD[7], 5.000000, 134.830642);
	TextDrawAlignment(DealerTD[7], 2);
	TextDrawColor(DealerTD[7], -1);
	TextDrawUseBox(DealerTD[7], 1);
	TextDrawBoxColor(DealerTD[7], -2139094785);
	TextDrawSetShadow(DealerTD[7], 0);
	TextDrawSetOutline(DealerTD[7], 0);
	TextDrawBackgroundColor(DealerTD[7], 255);
	TextDrawFont(DealerTD[7], 1);
	TextDrawSetProportional(DealerTD[7], 1);
	TextDrawSetShadow(DealerTD[7], 0);
	TextDrawSetSelectable(DealerTD[7], true);
}

hook OnPlayerConnect(playerid)
{
	DealerPTD[playerid][0] = CreatePlayerTextDraw(playerid, 202.666656, 307.948120, "");
	PlayerTextDrawLetterSize(playerid, DealerPTD[playerid][0], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, DealerPTD[playerid][0], 90.000000, 90.000000);
	PlayerTextDrawAlignment(playerid, DealerPTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, DealerPTD[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, DealerPTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, DealerPTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, DealerPTD[playerid][0], 0);
	PlayerTextDrawFont(playerid, DealerPTD[playerid][0], 5);
	PlayerTextDrawSetProportional(playerid, DealerPTD[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, DealerPTD[playerid][0], 0);
	PlayerTextDrawSetPreviewModel(playerid, DealerPTD[playerid][0], 509);
	PlayerTextDrawSetPreviewRot(playerid, DealerPTD[playerid][0], 0.000000, 0.000000, 0.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, DealerPTD[playerid][0], 1, 1);
	 
	DealerPTD[playerid][1] = CreatePlayerTextDraw(playerid, 248.666641, 372.933349, "Monster Truck A");
	PlayerTextDrawLetterSize(playerid, DealerPTD[playerid][1], 0.303000, 1.289999);
	PlayerTextDrawAlignment(playerid, DealerPTD[playerid][1], 2);
	PlayerTextDrawColor(playerid, DealerPTD[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, DealerPTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, DealerPTD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, DealerPTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, DealerPTD[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, DealerPTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, DealerPTD[playerid][1], 0);
	 
	DealerPTD[playerid][2] = CreatePlayerTextDraw(playerid, 303.866882, 320.830047, "Price: ~G~$400.000~W~~H~~N~Stock: ~R~250~W~~H~~N~Max Speed: ~R~120KM/H");
	PlayerTextDrawLetterSize(playerid, DealerPTD[playerid][2], 0.179500, 1.240000);
	PlayerTextDrawAlignment(playerid, DealerPTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, DealerPTD[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, DealerPTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, DealerPTD[playerid][2], 1);
	PlayerTextDrawBackgroundColor(playerid, DealerPTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, DealerPTD[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, DealerPTD[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, DealerPTD[playerid][2], 0);

	return Y_HOOKS_CONTINUE_RETURN_1;
}

YCMD:buycar(playerid, params[], help) return OnShowDealership(playerid), SCM(playerid, -1, "Press 'ESC' if you want to exit from this menu.");
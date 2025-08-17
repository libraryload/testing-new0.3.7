#include <YSI\y_hooks>

new Float: cowFarmPos[][] = 
{
	{-1136.46, -1141.54, 128.21},
	{-1141.41, -1127.65, 128.21},
	{-1143.26, -1133.93, 128.21},
	{-1139.76, -1146.62, 128.21},
	{-1142.28, -1139.69, 128.21},
	{-1147.30, -1129.48, 128.21},
	{-1148.48, -1140.16, 128.21},
	{-1151.40, -1133.02, 128.21},
	{-1154.07, -1127.67, 128.21},
	{-1150.47, -1146.71, 128.22},
	{-1155.64, -1135.26, 128.21},
	{-1154.59, -1141.31, 128.21},
	{-1159.22, -1129.83, 128.21},
	{-1156.78, -1147.03, 128.21},
	{-1161.49, -1134.57, 128.21},
	{-1160.16, -1140.75, 128.21},
	{-1165.26, -1128.76, 128.21},
	{-1166.00, -1134.44, 128.21},
	{-1164.11, -1145.69, 128.21},
	{-1132.70, -1147.22, 128.21},
	{-1136.98, -1136.09, 128.21},
	{-1133.56, -1133.35, 128.21}
};	

new Float:plantLocations[][] = 
{
	{-1170.6111, -1053.4626, 128.2464},
	{-1136.1948, -1053.4626, 128.2464},
	{-1102.8138, -1053.4626, 128.2464},
	{-1066.1144, -1053.4626, 128.2464},
	{-1035.8484, -1053.4626, 128.2464},
	{-1010.3168, -1053.4626, 128.2464},
	{-1010.0392, -1028.0167, 128.2464},
	{-1035.4930, -1028.0167, 128.2464},
	{-1066.0507, -1028.0167, 128.2464},
	{-1102.9086, -1028.0167, 128.2464},
	{-1136.2974, -1028.0167, 128.2464},
	{-1170.4524, -1028.0167, 128.2464},
	{-1170.1217, -999.8287, 128.2464},
	{-1136.6233, -999.8287, 128.2464},
	{-1103.1042, -999.8287, 128.2464},
	{-1066.1823, -999.9033, 128.2464},
	{-1035.9216, -999.9159, 128.2464},
	{-1010.5126, -999.7432, 128.2464},
	{-1010.9666, -974.2419, 128.2464},
	{-1036.3076, -974.2419, 128.2464},
	{-1065.9288, -974.2419, 128.2464},
	{-1103.3986, -974.2419, 128.2464},
	{-1136.2715, -974.2419, 128.2464},
	{-1170.0562, -974.2419, 128.2464},
	{-1169.9341, -946.6530, 128.2464},
	{-1136.7085, -946.6530, 128.2464},
	{-1103.7400, -946.6530, 128.2464},
	{-1066.2085, -946.6530, 128.2464},
	{-1036.2300, -946.6530, 128.2464},
	{-1011.1919, -946.6530, 128.2464},
	{-1011.1691, -922.2166, 128.2464},
	{-1036.2404, -922.2166, 128.2464},
	{-1065.9659, -922.2166, 128.2464},
	{-1103.8033, -922.2166, 128.2464},
	{-1136.5439, -922.2166, 128.2464},
	{-1168.4576, -922.2166, 128.2464}
};

new Float:treeLocations[][] = 
{
	{-1041.00, -1101.00, 124.21},
	{-1051.00, -1101.00, 124.21},
	{-1061.00, -1101.00, 124.21},
	{-1071.00, -1101.00, 124.21},
	{-1081.00, -1101.00, 124.21},
	{-1091.00, -1101.00, 124.21},
	{-1041.00, -1091.00, 124.21},
	{-1101.00, -1101.00, 124.21},
	{-1051.00, -1091.00, 124.21},
	{-1061.00, -1091.00, 124.21},
	{-1111.00, -1101.00, 124.21},
	{-1071.00, -1091.00, 124.21},
	{-1081.00, -1091.00, 124.21},
	{-1091.00, -1091.00, 124.21},
	{-1041.00, -1081.00, 124.21},
	{-1101.00, -1091.00, 124.21},
	{-1051.00, -1081.00, 124.21},
	{-1111.00, -1091.00, 124.21},
	{-1061.00, -1081.00, 124.21},
	{-1071.00, -1081.00, 124.21},
	{-1081.04, -1080.99, 124.21},
	{-1091.00, -1081.00, 124.21},
	{-1101.00, -1081.00, 124.21},
	{-1111.00, -1081.00, 124.21},
	{-1041.00, -1071.00, 124.21},
	{-1051.00, -1071.00, 124.21},
	{-1061.00, -1071.00, 124.21},
	{-1071.00, -1071.00, 124.21},
	{-1081.00, -1071.00, 124.21},
	{-1091.00, -1071.00, 124.21},
	{-1101.00, -1071.00, 124.21},
	{-1111.00, -1071.00, 124.21}
};

new
	PlayerText: farmerTD[MAX_PLAYERS][3], playerGrowObjects[MAX_PLAYERS][36], 
	PlayerText: progressTD[MAX_PLAYERS][2], farmTimer[MAX_PLAYERS], treeCase[MAX_PLAYERS];

hook OnGameModeInit()
{
	CreateStreamed3DTextLabel("ID: {9D72FF}4\n{FFFFFF}Job: {9D72FF}Farmer\n{FFFFFF}Use {9D72FF}/getjob {FFFFFF}to get the job.", -1, -1061.6108, -1195.3967, 129.8281, 100.0, 0, 1);
	
	// VACAR
	CreateStreamed3DTextLabel("Job: {9D72FF}Farmer\n{FFFFFF}Press {9D72FF}'Y'{FFFFFF} to start job activity.", -1, -1148.2969, -1080.4213, 129.2188, 100.0, 0, 1);
	CreateDynamicPickup(1239, 23, -1148.2969, -1080.4213, 129.2188, -1, -1, -1, 100.0);

	// AGRICULTOR
	CreateStreamed3DTextLabel("Job: {9D72FF}Farmer\n{FFFFFF}Type {9D72FF}/plantseeds{FFFFFF} to get seeds and plant them.", -1, -1110.1179, -1246.7355, 129.2188, 100.0, 0, 1);
	CreateDynamicPickup(862, 23, -1110.1179, -1246.7355, 128.8000, -1, -1, -1, 100.0);

	// AGRICULTOR 2
	CreateStreamed3DTextLabel("Job: {9D72FF}Farmer\n{FFFFFF}Type {9D72FF}/harvest{FFFFFF} to get seeds and plant them.", -1, -1005.7664, -1123.6711, 129.2126, 100.0, 0, 1);
	CreateDynamicPickup(862, 23, -1005.7664, -1123.6711, 128.6126, -1, -1, -1, 100.0);

	// POMICULTOR
	CreateStreamed3DTextLabel("Job: {9D72FF}Farmer\n{FFFFFF}Press {9D72FF}'Y'{FFFFFF} to start job activity.", -1, -1008.5446, -1083.2526, 129.2188, 100.0, 0, 1);
	CreateDynamicPickup(1239, 23, -1008.5446, -1083.2526, 129.2188, -1, -1, -1, 100.0);

	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{

	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	switch(newkeys) {
		case KEY_YES: {
			if(PlayerInfo[playerid][pJob] == 4)
			{
				if(IsPlayerInRangeOfPoint(playerid, 2.0, -1148.2969, -1080.4213, 129.2188))
				{
					if(JobWorking[playerid] != 0)
						return SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Efectuezi deja o sarcina a acestui job.");

					if(CP[playerid] > 1)
						return SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Nu poti utiliza aceasta actiune cat timp ai un checkpoint activ.");

					SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Ai nevoie de un balot de fan pentru a hrani bovinele.");

					createFarmTD(playerid);

					JobWorking[playerid] = 1;
					PlayerTextDrawShow(playerid, farmerTD[playerid][0]);
					PlayerTextDrawSetString(playerid, farmerTD[playerid][1], "Get food.");
					PlayerTextDrawShow(playerid, farmerTD[playerid][1]);

					SetPlayerCheckpoint(playerid, -1172.5581, -1140.4045, 129.2188, 2.0); 
					SetPVarInt(playerid, "cp_farm", 1);

					return false;
				}
				if(IsPlayerInRangeOfPoint(playerid, 2.0, -1008.5446, -1083.2526, 129.2188))
				{
					if(JobWorking[playerid] != 0)
						return SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Efectuezi deja o sarcina a acestui job.");

					if(CP[playerid] > 1)
						return SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Nu poti utiliza aceasta actiune cat timp ai un checkpoint activ.");

					SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Pomii sunt uscati. Mergi la statia de irigatie pentru a ii iriga.");

					JobWorking[playerid] = 1;
					
					createFarmTD(playerid);

					PlayerTextDrawShow(playerid, farmerTD[playerid][0]);
					PlayerTextDrawSetString(playerid, farmerTD[playerid][1], "Irrigate the trees.");
					PlayerTextDrawShow(playerid, farmerTD[playerid][1]);

					SetPlayerCheckpoint(playerid, -1125.1448, -1081.8401, 129.4119, 2.0); 
					SetPVarInt(playerid, "cp_farm", 8);

					return false;
				}
			}
		}

	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	RemovePlayerAttachedObject(playerid, 6);
	SetPlayerSpecialAction(playerid, 0);

	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerConnect(playerid)
{
	farmerTD[playerid][2] = CreatePlayerTextDraw(playerid, 88.000000, 424.929596, "plants grow in ~p~60:00~w~");
	PlayerTextDrawLetterSize(playerid, farmerTD[playerid][2], 0.154164, 0.941479);
	PlayerTextDrawAlignment(playerid, farmerTD[playerid][2], 2);
	PlayerTextDrawColor(playerid, farmerTD[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, farmerTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, farmerTD[playerid][2], 1);
	PlayerTextDrawBackgroundColor(playerid, farmerTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, farmerTD[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, farmerTD[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, farmerTD[playerid][2], 0);

	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerSpawn(playerid)
{
	RemovePlayerAttachedObject(playerid, 6);
	SetPlayerSpecialAction(playerid, 0);
	
	if(GetPVarInt(playerid, "cp_farm") != 0) DeletePVar(playerid, "cp_farm");
	if(GetPVarInt(playerid, "cow_farm") != 0) DeletePVar(playerid, "cow_farm");
	if(GetPVarInt(playerid, "cp_grow_farm") != 0) DeletePVar(playerid, "cp_grow_farm");
	if(GetPVarInt(playerid, "grow_farm") != 0) DeletePVar(playerid, "grow_farm");
	if(GetPVarInt(playerid, "grow_farm_time") != 0) DeletePVar(playerid, "grow_farm_time");
	if(GetPVarInt(playerid, "progress_farm") != 0) DeletePVar(playerid, "progress_farm");
	if(GetPVarInt(playerid, "tree_apple") != 0) DeletePVar(playerid, "tree_apple");
	if(GetPVarInt(playerid, "tree_total") != 0) DeletePVar(playerid, "tree_total");
	if(GetPVarInt(playerid, "tree_number") != 0) DeletePVar(playerid, "tree_number");
	if(GetPVarInt(playerid, "collision_farm") != 0) DeletePVar(playerid, "collision_farm"), DisableRemoteVehicleCollisions(playerid, 0);
	if(farmTimer[playerid]) KillTimer(farmTimer[playerid]);
	if(treeCase[playerid]) DestroyPlayerObject(playerid, treeCase[playerid]);

	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterCheckpoint(playerid)
{
	switch(GetPVarInt(playerid, "cp_farm"))
	{
		case 1: {
			PlayerTextDrawSetString(playerid, farmerTD[playerid][1], "Feed the cow.");

			ClearAnimations(playerid);

	        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
			SetPlayerAttachedObject(playerid, 6, 1453, 1, 0.299822, 0.563485, 0.000000, 184.311355, 0.000000, 0.000000, 0.800000, 0.800000, 1.000000);
			
			DisablePlayerCheckpoint(playerid);

			new 
				cowFarm = random(sizeof(cowFarmPos));

			SetPlayerCheckpoint(playerid, cowFarmPos[cowFarm][0], cowFarmPos[cowFarm][1], cowFarmPos[cowFarm][2], 2.0);
			SetPVarInt(playerid, "cow_farm", cowFarm);

			SetPVarInt(playerid, "cp_farm", 2);
		}
		case 2: {
			SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Vacuta ta este satula insa acum ii este sete.");
			SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Urmareste checkpointul de pe minimap pentru a lua o galeata cu apa.");

			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpoint(playerid, -1135.7656, -1093.9677, 129.2188, 2.0);

			PlayerTextDrawSetString(playerid, farmerTD[playerid][1], "Take a bucket of water.");

			ClearAnimations(playerid);
			SetPlayerSpecialAction(playerid, 0);
			ApplyAnimation(playerid, "CARRY", "PUTDWN", 4.1, 0, 0, 0, 0, 0);
			RemovePlayerAttachedObject(playerid, 6);

			SetPVarInt(playerid, "cp_farm", 3);
		}
		case 3: {
			SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Adapa vaca marcata pe minimap cu un checkpoint.");

			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpoint(playerid, cowFarmPos[GetPVarInt(playerid, "cow_farm")][0], cowFarmPos[GetPVarInt(playerid, "cow_farm")][1], cowFarmPos[GetPVarInt(playerid, "cow_farm")][2], 2.0);

			SetPlayerSpecialAction(playerid, 0);
			SetPlayerAttachedObject(playerid, 6, 19468, 5, 0.222060, -0.054934, 0.000000, 341.632995, 271.088043, 0.000000, 0.974783, 1.000000, 0.738034);

			SetPVarInt(playerid, "cp_farm", 4);
		}
		case 4: {
			SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}In continuare ai nevoie de o galeata goala pentru a mulge vaca.");
			SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Mergi in hambarul marcat pe minimap pentru a obtine o galeata.");

			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpoint(playerid, -1144.4302, -1087.0819, 129.2188, 2.0);

			PlayerTextDrawSetString(playerid, farmerTD[playerid][1], "Take an empty bucket.");

			ClearAnimations(playerid);
			SetPlayerSpecialAction(playerid, 0);
			ApplyAnimation(playerid, "CARRY", "PUTDWN", 4.1, 0, 0, 0, 0, 0);
			RemovePlayerAttachedObject(playerid, 6);
			
			SetPVarInt(playerid, "cp_farm", 5);
		}
		case 5: {
			SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Mulge vaca marcata pe minimap cu un checkpoint.");

			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpoint(playerid, cowFarmPos[GetPVarInt(playerid, "cow_farm")][0], cowFarmPos[GetPVarInt(playerid, "cow_farm")][1], cowFarmPos[GetPVarInt(playerid, "cow_farm")][2], 2.0);
		
			PlayerTextDrawSetString(playerid, farmerTD[playerid][1], "Milk the cow.");

			SetPlayerAttachedObject(playerid, 6, 19468, 5, 0.222060, -0.054934, 0.000000, 341.632995, 271.088043, 0.000000, 0.974783, 1.000000, 0.738034);

			SetPVarInt(playerid, "cp_farm", 6);
		}
		case 6: {
			DisablePlayerCheckpoint(playerid);
			ClearAnimations(playerid);
			SetPlayerSpecialAction(playerid, 0);
			ApplyAnimation(playerid, "BOMBER", "BOM_PLANT_LOOP", 4.1, 1, 0, 0, 0, 0);

			SetTimerEx("vacarWait", 10000, false, "i", playerid);
		}
		case 7: {
			DisablePlayerCheckpoint(playerid);
			destroyFarmTD(playerid);

			DeletePVar(playerid, "cp_farm"); DeletePVar(playerid, "cow_farm");

			RemovePlayerAttachedObject(playerid, 6);
			SetPlayerSpecialAction(playerid, 0);

			JobWorking[playerid] = 0;

			giveFarmMoney(playerid, 1);
			finishDailyQuest(playerid, 5);
		}
		case 8: {
			DisablePlayerCheckpoint(playerid);
			TogglePlayerControllable(playerid, 0);

			PlayerTextDrawSetString(playerid, farmerTD[playerid][1], "Please wait...");

			createProgressFarm(playerid);

			SetPVarInt(playerid, "progress_farm", 1);
			farmTimer[playerid] = SetTimerEx("updateFarmProgress", 2000, true, "i", playerid);
		}
		case 9: {
			SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Culege fructele din 5 pomi. Pomii iti vor fi marcati prin checkpoint-uri.");

			DisablePlayerCheckpoint(playerid);

			ApplyAnimation(playerid, "CARRY", "PUTDWN", 4.1, 0, 0, 0, 0, 0);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

			SetPlayerAttachedObject(playerid, 6, 19587, 1, -0.010000, 0.563485, 0.000000, 0.000000, 88.000000, 0.000000, 0.800000, 0.800000, 1.000000);
			
			new 
				treeFarm = random(sizeof(treeLocations));

			SetPlayerCheckpoint(playerid, treeLocations[treeFarm][0] + 2, treeLocations[treeFarm][1], treeLocations[treeFarm][2] + 5, 1.0);
			
			SetPVarInt(playerid, "cp_farm", 10);
			SetPVarInt(playerid, "tree_number", treeFarm);

			playerTextDrawSetString(playerid, farmerTD[playerid][1], "Reap the fruits (%d/5 trees)", GetPVarInt(playerid, "tree_total"));
		}
		case 10: {
			DisablePlayerCheckpoint(playerid);
			treeCase[playerid] = CreatePlayerObject(playerid, 19587, treeLocations[GetPVarInt(playerid, "tree_number")][0], treeLocations[GetPVarInt(playerid, "tree_number")][1] + 2.5, treeLocations[GetPVarInt(playerid, "tree_number")][2] + 4.050000, 0.000000, 0.000000, 88.000000, 100);
			
			RemovePlayerAttachedObject(playerid, 6);
			SetPlayerSpecialAction(playerid, 0);

			SetPVarInt(playerid, "cp_farm", 11); SetPVarInt(playerid, "tree_apple", 1);
			
			giveTreeCheckpoint(playerid);
			
			if(GetPVarInt(playerid, "tree_total") < 1) 
				ApplyAnimation(playerid, "BSKTBALL", "BBALL_JUMP_SHOT", 4.1, 0, 0, 0, 0, 0), ClearAnimations(playerid);
		}
		case 11: {
			ApplyAnimation(playerid, "BSKTBALL", "BBALL_JUMP_SHOT", 4.1, 0, 0, 0, 0, 0);

			DisablePlayerCheckpoint(playerid);

			SetPVarInt(playerid, "tree_apple", GetPVarInt(playerid, "tree_apple") + 1);

			new 
				Float: oPos[3];

			GetPlayerObjectPos(playerid, treeCase[playerid], oPos[0], oPos[1], oPos[2]);
			SetPlayerCheckpoint(playerid, oPos[0], oPos[1], oPos[2] + 1, 1.0);
			SetPVarInt(playerid, "cp_farm", 12);

			SetPlayerAttachedObject(playerid, 6, 19576, 5, 0.109946, 0.028172, 0.001308, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000);
		}
		case 12: {
			DisablePlayerCheckpoint(playerid);
			RemovePlayerAttachedObject(playerid, 6);

			ApplyAnimation(playerid, "CARRY", "PUTDWN", 4.1, 0, 0, 0, 0, 0);

			if(GetPVarInt(playerid, "tree_apple") < 5)
				return giveTreeCheckpoint(playerid), SetPVarInt(playerid, "cp_farm", 11);

			DeletePVar(playerid, "tree_apple");
			
			SetPVarInt(playerid, "tree_total", GetPVarInt(playerid, "tree_total") + 1);

			if(GetPVarInt(playerid, "tree_total") == 5)
			{
				SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Ai terminat de cules cei 5 pomi. Plaseaza fructele in hambar.");
				
				PlayerTextDrawSetString(playerid, farmerTD[playerid][1], "Return the box to the barn.");
				
				DestroyPlayerObject(playerid, treeCase[playerid]);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
				
				SetPlayerAttachedObject(playerid, 6, 19637, 1, -0.010000, 0.563485, 0.000000, 0.000000, 88.000000, 88.000000, 0.800000, 0.800000, 1.000000);
				SetPlayerCheckpoint(playerid, -1005.2391, -1080.0825, 129.2188, 1.0);

				SetPVarInt(playerid, "cp_farm", 13);
				return true;
			}
			ClearAnimations(playerid);

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
			ApplyAnimation(playerid, "CARRY", "PUTDWN", 4.1, 0, 0, 0, 0, 0);

			DestroyPlayerObject(playerid, treeCase[playerid]);
			SetPlayerAttachedObject(playerid, 6, 19587, 1, -0.010000, 0.563485, 0.000000, 0.000000, 88.000000, 0.000000, 0.800000, 0.800000, 1.000000);
			
			new 
				treeFarm = random(sizeof(treeLocations));

			if(GetPVarInt(playerid, "tree_number") == treeFarm)
				treeFarm = random(sizeof(treeLocations));

			SetPlayerCheckpoint(playerid, treeLocations[treeFarm][0] + 2, treeLocations[treeFarm][1], treeLocations[treeFarm][2] + 5, 1.0);
			
			SetPVarInt(playerid, "cp_farm", 10);
			SetPVarInt(playerid, "tree_number", treeFarm);

			playerTextDrawSetString(playerid, farmerTD[playerid][1], "Reap the fruits (%d/5 trees)", GetPVarInt(playerid, "tree_total"));
		}
		case 13: {
			DisablePlayerCheckpoint(playerid);

			destroyFarmTD(playerid);
			
			DeletePVar(playerid, "cp_farm"); 
			DeletePVar(playerid, "tree_number");
			DeletePVar(playerid, "tree_apple"); 
			DeletePVar(playerid, "tree_total");
			JobWorking[playerid] = 0;

			SetPlayerSpecialAction(playerid, 0);
			RemovePlayerAttachedObject(playerid, 6);

			giveFarmMoney(playerid, 2);
			finishDailyQuest(playerid, 5);
		}
	}

	switch(GetPVarInt(playerid, "cp_grow_farm"))
	{
		case 1: {
	        if(GetPVarInt(playerid, "grow_farm") < sizeof(plantLocations))
	        {
	            if(!IsPlayerInVehicle(playerid, PlayerInfo[playerid][pJobVehicle]))
	                return true;

	            playerGrowObjects[playerid][GetPVarInt(playerid, "grow_farm") - 1] = CreatePlayerObject(playerid, 860, plantLocations[GetPVarInt(playerid, "grow_farm") - 1][0], plantLocations[GetPVarInt(playerid, "grow_farm") - 1][1], plantLocations[GetPVarInt(playerid, "grow_farm") - 1][2], 0.0, 0.0, 0.0, 100.0);
	            SetPVarInt(playerid, "grow_farm", GetPVarInt(playerid, "grow_farm") + 1);

	            DisablePlayerCheckpoint(playerid); 
	            SetPlayerCheckpoint(playerid, plantLocations[GetPVarInt(playerid, "grow_farm") - 1][0], plantLocations[GetPVarInt(playerid, "grow_farm") - 1][1], plantLocations[GetPVarInt(playerid, "grow_farm") - 1][2], 3.0); 
	        }
	        else if(GetPVarInt(playerid, "grow_farm") == sizeof(plantLocations))
	        {
	            if(!IsPlayerInVehicle(playerid, PlayerInfo[playerid][pJobVehicle]))
	                return true;

	            playerGrowObjects[playerid][GetPVarInt(playerid, "grow_farm") - 1] = CreatePlayerObject(playerid, 860, plantLocations[GetPVarInt(playerid, "grow_farm") - 1][0], plantLocations[GetPVarInt(playerid, "grow_farm") - 1][1], plantLocations[GetPVarInt(playerid, "grow_farm") - 1][2], 0.0, 0.0, 0.0, 100.0);

	            PlayerTextDrawSetString(playerid, farmerTD[playerid][1], "Please return the tractor."); 
	            SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Returneaza tractorul in locatia marcata pe minimap.");

	            DisablePlayerCheckpoint(playerid);
	            SetPlayerCheckpoint(playerid, -1129.4894, -1211.3784, 129.2188, 2.0); 

	            SetPVarInt(playerid, "cp_grow_farm", 2);
	        }
		}
		case 2: {
			if(!IsPlayerInVehicle(playerid, PlayerInfo[playerid][pJobVehicle]))
				return true;

			DisablePlayerCheckpoint(playerid);
			DestroyJobVeh(playerid);

			PlayerInfo[playerid][pGrowWaitTime] = GetPVarInt(playerid, "grow_farm_time") - 90;
			pUpdateInt(playerid, "GrowWaitTime", PlayerInfo[playerid][pGrowWaitTime]);

			DeletePVar(playerid, "cp_grow_farm");
			DeletePVar(playerid, "grow_farm");
			DeletePVar(playerid, "grow_farm_time");

			PlayerTextDrawHide(playerid, farmerTD[playerid][0]);
			PlayerTextDrawHide(playerid, farmerTD[playerid][1]);

			PlayerTextDrawShow(playerid, farmerTD[playerid][2]);

			JobWorking[playerid] = 0;
			giveFarmMoney(playerid, 3);
			finishDailyQuest(playerid, 5);

			if(GetPVarInt(playerid, "collision_farm") == 1)
				DisableRemoteVehicleCollisions(playerid, 0);

			DeletePVar(playerid, "collision_farm");
		}
		case 3: {
	        if(GetPVarInt(playerid, "grow_farm") < sizeof(plantLocations))
	        {
	            if(!IsPlayerInVehicle(playerid, PlayerInfo[playerid][pJobVehicle]))
	                return true;

	            DestroyPlayerObject(playerid, playerGrowObjects[playerid][GetPVarInt(playerid, "grow_farm") - 1]);
	            SetPVarInt(playerid, "grow_farm", GetPVarInt(playerid, "grow_farm") + 1);

	            DisablePlayerCheckpoint(playerid); 
	            SetPlayerCheckpoint(playerid, plantLocations[GetPVarInt(playerid, "grow_farm") - 1][0], plantLocations[GetPVarInt(playerid, "grow_farm") - 1][1], plantLocations[GetPVarInt(playerid, "grow_farm") - 1][2], 3.0); 
	        }
	        else if(GetPVarInt(playerid, "grow_farm") == sizeof(plantLocations))
	        {
	            if(!IsPlayerInVehicle(playerid, PlayerInfo[playerid][pJobVehicle]))
	                return true;

	           	DestroyPlayerObject(playerid, playerGrowObjects[playerid][GetPVarInt(playerid, "grow_farm") - 1]);

				PlayerTextDrawSetString(playerid, farmerTD[playerid][1], "Please return the Mower."); 
				SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Returneaza Mower-ul in locatia marcata pe minimap.");

	            DisablePlayerCheckpoint(playerid);
	           	SetPlayerCheckpoint(playerid, -1200.0137, -1177.2585, 128.7987, 2.0);

	            SetPVarInt(playerid, "cp_grow_farm", 4);
	        }
		}	
		case 4: {
			vehEngine[GetPlayerVehicleID(playerid)] = 0; 
			SetPVarInt(playerid, "Engine", 0);
			
			new 
				engine, lights, alarm, doors, bonnet, boot, objective;

			GetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective);
	        SetVehicleParamsEx(GetPlayerVehicleID(playerid), VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);

			DeletePVar(playerid, "grow_farm");

			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpoint(playerid, -1195.7078, -1177.5156, 129.2188, 2.0);

			SetPVarInt(playerid, "cp_grow_farm", 5);

			SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Ia sacul de grane din spatele vehiculului si du-l in hambar.");
			PlayerTextDrawSetString(playerid, farmerTD[playerid][1], "Take the bag from vehicle back.");
		}
		case 5: {
			DestroyJobVeh(playerid);

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
			SetPlayerAttachedObject(playerid, 6, 2060, 1, 0.299822, 0.563485, 0.000000, 100.311355, 0.000000, 0.000000, 0.800000, 0.800000, 1.000000);
			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpoint(playerid, -1207.3368, -1209.5778, 129.2188, 2.0);

			SetPVarInt(playerid, "cp_grow_farm", 6);

			SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Livreaza sacul cu grane in hambar.");
			PlayerTextDrawSetString(playerid, farmerTD[playerid][1], "Take the bag to the barn.");
		}
		case 6: {
			SetPlayerSpecialAction(playerid, 0);
			RemovePlayerAttachedObject(playerid, 6);

			DisablePlayerCheckpoint(playerid);
			DeletePVar(playerid, "cp_grow_farm");

			PlayerInfo[playerid][pGrowWaitTime] = -1;
			pUpdateInt(playerid, "GrowWaitTime", PlayerInfo[playerid][pGrowWaitTime]);

			destroyFarmTD(playerid);

			PlayerTextDrawHide(playerid, farmerTD[playerid][2]);

			giveFarmMoney(playerid, 4);
			finishDailyQuest(playerid, 5);

			if(GetPVarInt(playerid, "collision_farm") == 1)
				DisableRemoteVehicleCollisions(playerid, 0);

			DeletePVar(playerid, "collision_farm");
			JobWorking[playerid] = 0;
		}
	}
	return true;
}

forward public vacarWait(playerid);
public vacarWait(playerid)
{
	SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Livreaza laptele in butoaiele din hambar.");

	SetPlayerSpecialAction(playerid, 0);
	TogglePlayerControllable(playerid, 1);
	SetPlayerCheckpoint(playerid, -1144.4302, -1087.0819, 129.2188, 3.0);
	
	PlayerTextDrawSetString(playerid, farmerTD[playerid][1], "Deliver the milk.");

	SetPVarInt(playerid, "cp_farm", 7);
	return true;
}

giveTreeCheckpoint(playerid)
{
	switch(GetPVarInt(playerid, "tree_apple"))
	{
		case 1: SetPlayerCheckpoint(playerid, treeLocations[GetPVarInt(playerid, "tree_number")][0], treeLocations[GetPVarInt(playerid, "tree_number")][1] - 0.5, treeLocations[GetPVarInt(playerid, "tree_number")][2] + 5, 1.0);
		case 2: SetPlayerCheckpoint(playerid, treeLocations[GetPVarInt(playerid, "tree_number")][0], treeLocations[GetPVarInt(playerid, "tree_number")][1] + 0.5, treeLocations[GetPVarInt(playerid, "tree_number")][2] + 5, 1.0);
		case 3: SetPlayerCheckpoint(playerid, treeLocations[GetPVarInt(playerid, "tree_number")][0] + 0.5, treeLocations[GetPVarInt(playerid, "tree_number")][1], treeLocations[GetPVarInt(playerid, "tree_number")][2] + 5, 1.0);
		case 4: SetPlayerCheckpoint(playerid, treeLocations[GetPVarInt(playerid, "tree_number")][0] - 0.5, treeLocations[GetPVarInt(playerid, "tree_number")][1], treeLocations[GetPVarInt(playerid, "tree_number")][2] + 5, 1.0);
	}

	return true;
}

destroyFarmTD(playerid)
{
	for(new i; i < 2; i++)
		if(farmerTD[playerid][i] != PlayerText: INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, farmerTD[playerid][i]);

	return true;
}

createFarmTD(playerid)
{
	farmerTD[playerid][0] = CreatePlayerTextDraw(playerid, 320.000000, 327.812500, "FARMER");
	PlayerTextDrawLetterSize(playerid, farmerTD[playerid][0], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, farmerTD[playerid][0], 2);
	PlayerTextDrawColor(playerid, farmerTD[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, farmerTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, farmerTD[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, farmerTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, farmerTD[playerid][0], 3);
	PlayerTextDrawSetProportional(playerid, farmerTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, farmerTD[playerid][0], 0);

	farmerTD[playerid][1] = CreatePlayerTextDraw(playerid, 320.000000, 341.812500, "Get_food.");
	PlayerTextDrawLetterSize(playerid, farmerTD[playerid][1], 0.240500, 1.210625);
	PlayerTextDrawAlignment(playerid, farmerTD[playerid][1], 2);
	PlayerTextDrawColor(playerid, farmerTD[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, farmerTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, farmerTD[playerid][1], 1);
	PlayerTextDrawBackgroundColor(playerid, farmerTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, farmerTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, farmerTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, farmerTD[playerid][1], 0);

	return true;
}

returnFarmTimes(skill)
{
	new 
		farmTimes;

	switch(skill)
	{
		case 1: farmTimes = 30;
		case 2: farmTimes = 90;
		case 3: farmTimes = 120;
		case 4: farmTimes = 150;
	}

	return farmTimes;
}

updateFarmSkill(playerid, type)
{
	switch(type) {
		case 1: {
			PlayerInfo[playerid][pVacarTimes] ++;
			if(returnFarmTimes(PlayerInfo[playerid][pVacarSkill]) == PlayerInfo[playerid][pVacarTimes])
			{
				PlayerInfo[playerid][pVacarSkill] ++;
				pUpdateInt(playerid, "VacarSkill", PlayerInfo[playerid][pVacarSkill]);

				SCMF(playerid, COLOR_SV_PURPLE, "JOB >> {FFFFFF}Acum ai skill %d pentru jobul vacar.", PlayerInfo[playerid][pVacarSkill]);
			}
			pUpdateInt(playerid, "VacarTimes", PlayerInfo[playerid][pVacarTimes]);
		}
		case 2: {
			PlayerInfo[playerid][pPomicultorTimes] ++;
			if(returnFarmTimes(PlayerInfo[playerid][pPomicultorSkill]) == PlayerInfo[playerid][pPomicultorTimes])
			{
				PlayerInfo[playerid][pPomicultorSkill] ++;
				pUpdateInt(playerid, "PomicultorSkill", PlayerInfo[playerid][pPomicultorSkill]);

				SCMF(playerid, COLOR_SV_PURPLE, "JOB >> {FFFFFF}Acum ai skill %d pentru jobul pomicultor.", PlayerInfo[playerid][pPomicultorSkill]);
			}
			pUpdateInt(playerid, "VacarTimes", PlayerInfo[playerid][pPomicultorTimes]);
		}
		case 3: {
			PlayerInfo[playerid][pGrowTimes] ++;
			if(returnFarmTimes(PlayerInfo[playerid][pGrowSkill]) == PlayerInfo[playerid][pGrowTimes])
			{
				PlayerInfo[playerid][pGrowSkill] ++;
				pUpdateInt(playerid, "GrowSkill", PlayerInfo[playerid][pGrowSkill]);

				SCMF(playerid, COLOR_SV_PURPLE, "JOB >> {FFFFFF}Acum ai skill %d pentru jobul agricultor.", PlayerInfo[playerid][pGrowSkill]);
			}
			pUpdateInt(playerid, "GrowTimes", PlayerInfo[playerid][pGrowTimes]);
		}
	}
	return true;
}

updateClanMoney(playerid, money)
{
	if(PlayerInfo[playerid][pClan] == 0)
		return true;

	SCMF(playerid, -1, "{9D72FF}JOB >> {FFFFFF}After your work %s$ was added in clan safe.", FormatNumber(money / 10));
    
	ClanInfo[PlayerInfo[playerid][pClan]][cClanSeif] += money / 10;
	ClanUpdate(PlayerInfo[playerid][pClan], ClanSafex);
	
	PlayerInfo[playerid][pClanDep] += money / 10;
	Update(playerid, pClanDepx);

	return true;
}

giveFarmMoney(playerid, type)
{
	switch(type)
	{
		case 1: {
			new
				money = PlayerInfo[playerid][pVacarSkill] * 10000 + RandomEx(1000, 5000);

			SCMF(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Ai primit {339D2A}$%s{FFFFFF} pentru munca prestata ca vacar.", FormatNumber(money));
			randomJobExp(playerid);

			GivePlayerCash(playerid, money);
			dailyjob_money(playerid, money);
			giveSubscriptionBoost(playerid, money);
			updateClanMoney(playerid, money);

			UpdateJobGoal(money);
			updateFarmSkill(playerid, 1);
		}
		case 2: {
			new
				money = PlayerInfo[playerid][pPomicultorSkill] * 30000 + RandomEx(5000, 8000);

			SCMF(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Ai primit {339D2A}$%s{FFFFFF} pentru munca prestata ca pomicultor.", FormatNumber(money));
			randomJobExp(playerid);

			GivePlayerCash(playerid, money);
			dailyjob_money(playerid, money);
			giveSubscriptionBoost(playerid, money);
			updateClanMoney(playerid, money);

			UpdateJobGoal(money);
			updateFarmSkill(playerid, 2);
		}
		case 3: {
			new
				money = PlayerInfo[playerid][pGrowSkill] * 100000;
			
			SCMF(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Ai returnat tractorul si ai fost rasplatit cu {339D2A}$%s{FFFFFF}.", FormatNumber(money));
			SCMF(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Plantele tale vor atinge perioada optima de recoltare in %s.", CalculateTime(PlayerInfo[playerid][pGrowWaitTime]));
			giveSubscriptionBoost(playerid, money);
			GivePlayerCash(playerid, money);
			dailyjob_money(playerid, money);
			randomJobExp(playerid);
		}
		case 4: {
			new
				money = PlayerInfo[playerid][pGrowSkill] * 120000, 
				growKG = 3000 + RandomEx(300, 1000), growMoney = 50 * growKG;
			
			SCMF(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Ai returnat Mower-ul si ai fost rasplatit cu {339D2A}$%s{FFFFFF}.", FormatNumber(money));
			SCMF(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Ai castigat {339D2A}$%s{FFFFFF} pentru %d kg de grane.", FormatNumber(growMoney), growKG);
			GivePlayerCash(playerid, money);
			dailyjob_money(playerid, money);
			GivePlayerCash(playerid, growMoney);
			giveSubscriptionBoost(playerid, growMoney);
			updateClanMoney(playerid, money);

			UpdateJobGoal(money);
			
			giveExp(playerid, RandomEx(20, 60));
		
			updateFarmSkill(playerid, 3);
		}
	}

	return true;
}

giveSubscriptionBoost(playerid, money)
{
	if(Iter_Contains(Premiums, playerid) && !Iter_Contains(Vips, playerid))
	{
		SCMF(playerid, -1, "{9D72FF}JOB >> {339D2A}+$%s{FFFFFF} from your PREMIUM Account.", FormatNumber(money * 30 / 100));
		GivePlayerCash(playerid, money * 30 / 100);
	}
	else if(Iter_Contains(Vips, playerid))
	{
		SCMF(playerid, -1, "{9D72FF}JOB >> {339D2A}+$%s{FFFFFF} from your VIP Account.", FormatNumber(money * 50 / 100));
		GivePlayerCash(playerid, money * 50 / 100);
	}
	return true;
}

returnFarmCalculation(skill, times) return returnFarmTimes(skill) - times;

createProgressFarm(playerid) 
{
	progressTD[playerid][0] = CreatePlayerTextDraw(playerid, 289.062988, 386.500122, "box");
	PlayerTextDrawLetterSize(playerid, progressTD[playerid][0], 0.000000, 0.489021);
	PlayerTextDrawTextSize(playerid, progressTD[playerid][0], 347.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, progressTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, progressTD[playerid][0], -71);
	PlayerTextDrawUseBox(playerid, progressTD[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, progressTD[playerid][0], 92);
	PlayerTextDrawSetShadow(playerid, progressTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, progressTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, progressTD[playerid][0], 60);
	PlayerTextDrawFont(playerid, progressTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, progressTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, progressTD[playerid][0], 0);

	progressTD[playerid][1] = CreatePlayerTextDraw(playerid, 289.062988, 386.500122, "box");
	PlayerTextDrawLetterSize(playerid, progressTD[playerid][1], 0.000000, 0.489021);
	PlayerTextDrawTextSize(playerid, progressTD[playerid][1], 297.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, progressTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, progressTD[playerid][1], -71);
	PlayerTextDrawUseBox(playerid, progressTD[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, progressTD[playerid][1], 184);
	PlayerTextDrawSetShadow(playerid, progressTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, progressTD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, progressTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, progressTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, progressTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, progressTD[playerid][1], 0);
 	
	PlayerTextDrawShow(playerid, progressTD[playerid][0]);
	PlayerTextDrawShow(playerid, progressTD[playerid][1]);

	return true; 
}
 
function updateFarmProgress(playerid) 
{
	switch(GetPVarInt(playerid, "progress_farm")) {
		case 1: 
			PlayerTextDrawTextSize(playerid, progressTD[playerid][1], 307.000000, 0.000000);
		case 2: 
			PlayerTextDrawTextSize(playerid, progressTD[playerid][1], 317.000000, 0.000000);
		case 3: 
			PlayerTextDrawTextSize(playerid, progressTD[playerid][1], 327.000000, 0.000000);
		case 4: 
			PlayerTextDrawTextSize(playerid, progressTD[playerid][1], 337.000000, 0.000000);
		case 5: {
			PlayerTextDrawTextSize(playerid, progressTD[playerid][1], 347.000000, 0.000000);
			if(GetPVarInt(playerid, "grow_farm_time") != 0)
			{
				for(new i; i < 2; i++)
					PlayerTextDrawDestroy(playerid, progressTD[playerid][i]);

				KillTimer(farmTimer[playerid]);
				DeletePVar(playerid, "progress_farm");

				new 
					engine, lights, alarm, doors, bonnet, boot, objective;

				GetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective);
			    SetVehicleParamsEx(GetPlayerVehicleID(playerid), VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);

				SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Planteaza semintele in locatiile marcate pe ecranul tau.");

				TogglePlayerControllable(playerid, 1);

				SetPVarInt(playerid, "grow_farm", 1);
				SetPVarInt(playerid, "cp_grow_farm", 1);

				SetPlayerCheckpoint(playerid, plantLocations[GetPVarInt(playerid, "grow_farm") - 1][0], plantLocations[GetPVarInt(playerid, "grow_farm") - 1][1], plantLocations[GetPVarInt(playerid, "grow_farm") - 1][2], 3.0);

				PlayerTextDrawSetString(playerid, farmerTD[playerid][1], "Plant seeds in the market spots.");

				return true;
			}
			else 
			{
				for(new i; i < 2; i++)
					PlayerTextDrawDestroy(playerid, progressTD[playerid][i]);

				KillTimer(farmTimer[playerid]);
				DeletePVar(playerid, "progress_farm");

				DisablePlayerCheckpoint(playerid);
				TogglePlayerControllable(playerid, 1);

				SetPlayerCheckpoint(playerid, -1006.1122, -1086.8851, 129.2188 , 1.0);
				SetPVarInt(playerid, "cp_farm", 9);

				SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Pomii au fost irigati. Ai nevoie de o lada din hambar pentru a culege fructele.");
				PlayerTextDrawSetString(playerid, farmerTD[playerid][1], "Take the box from the barn.");
			}
		}
	}

	PlayerTextDrawShow(playerid, progressTD[playerid][1]);
	SetPVarInt(playerid, "progress_farm", GetPVarInt(playerid, "progress_farm") + 1);
	return true; }

seedsName(seedid) 
{
	new 
		returnString[18];

	switch(seedid) {
		case 1: returnString = "Barley";
		case 2: returnString = "Rye";
		case 3: returnString = "Corn";
		case 4: returnString = "Wheat";
		case 5: returnString = "Rice";
	}
	return returnString; }

seedsGrowTime(seedid)
{
	new 
		gorwTime;

	switch(seedid) {
		case 1: gorwTime = 600;
		case 2: gorwTime = 1200;
		case 3: gorwTime = 1800;
		case 4: gorwTime = 2400;
		case 5: gorwTime = 3000;
	}
	return gorwTime;
}

YCMD:plantseeds(playerid, params[], help)
{
	if(PlayerInfo[playerid][pJob] != 4)
		return SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Nu ai jobul Farmer.");

	if(CP[playerid] > 1)
		return SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Nu poti utiliza aceasta comanda cat timp ai un checkpoint activ.");

	if(!IsPlayerInRangeOfPoint(playerid, 2.0, -1110.1179, -1246.7355, 129.2188))
		return SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Nu te aflii in locatia potrivita.");

	if(PlayerInfo[playerid][pGrowWaitTime] != -1)
		return SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Ai deja o recolta plantata. Nu poti planta alta");

	if(JobWorking[playerid] != 0)
		return SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Efectuezi deja o sarcina a acestui job.");

	gString[0] = EOS;
	gString = "Seeds\tGrow Time\tStatus\n";
	for(new i = 1; i < 5; i++)
		format(gString, sizeof gString, "%s%s\t%s\t%s\n", gString, seedsName(i), CalculateTime(seedsGrowTime(i)), (PlayerInfo[playerid][pGrowSkill] < i) ? ("{FF0000}locked") : ("{26b309}unlocked"));

	ShowPlayerDialogEx(playerid, DIALOG_PLANTSEEDS, DIALOG_STYLE_TABLIST_HEADERS, "Select seeds", gString, "Select", "Cancel");

	return true;
}

YCMD:setgrowtime(playerid, params[], help)
{
	if(!AdminAcces(playerid))
		return sendAcces(playerid);

	new
		targetID, stringTime;

	if(sscanf(params, "ud", targetID, stringTime))
		return sendSyntax(playerid, "/setgrowtime <Name/PlayerID> <Time>");

	if(!IsPlayerConnected(playerid))
		return sendError(playerid, "Invalid or unlogged player.");

	PlayerInfo[targetID][pGrowWaitTime] = stringTime;
	pUpdateInt(playerid, "GrowWaitTime", PlayerInfo[targetID][pGrowWaitTime]);

	return true;
}

YCMD:harvest(playerid, params[], help)
{
	if(PlayerInfo[playerid][pJob] != 4)
		return SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Nu ai jobul Farmer.");

	if(CP[playerid] > 1)
		return SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Nu poti utiliza aceasta comanda cat timp ai un checkpoint activ.");

	if(!IsPlayerInRangeOfPoint(playerid, 2.0, -1005.7664, -1123.6711, 129.2126))
		return SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Nu te aflii in locatia potrivita.");

	if(PlayerInfo[playerid][pGrowWaitTime] == -1)
		return SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Nu ai nimic de recoltat.");

	if(JobWorking[playerid] != 0)
		return SCM(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Efectuezi deja o sarcina a acestui job.");

	if(PlayerInfo[playerid][pGrowWaitTime] != 0)
		return SCMF(playerid, COLOR_SV_PURPLE, "FARMER >> {FFFFFF}Vei putea culege recolta peste {FF0000}%s{FFFFFF}.", CalculateTime(PlayerInfo[playerid][pGrowWaitTime]));

	GiveJobVeh(playerid, 572);

	SetPVarInt(playerid, "grow_farm", 1);
	SetPVarInt(playerid, "cp_grow_farm", 3);
	JobWorking[playerid] = 1;

	SetPlayerCheckpoint(playerid, plantLocations[GetPVarInt(playerid, "grow_farm") - 1][0], plantLocations[GetPVarInt(playerid, "grow_farm") - 1][1], plantLocations[GetPVarInt(playerid, "grow_farm") - 1][2], 3.0);

	createFarmTD(playerid);

	PlayerTextDrawShow(playerid, farmerTD[playerid][0]);
	PlayerTextDrawSetString(playerid, farmerTD[playerid][1], "Harvest the plants marked on your screen.");
	PlayerTextDrawShow(playerid, farmerTD[playerid][1]);

	SetPVarInt(playerid, "collision_farm", 1);
	DisableRemoteVehicleCollisions(playerid, 1);

	return true;
}
#include <YSI_Coding\y_hooks>

#define CP_GARBAGE (CP_JOBS_BEGIN) + JOB_TYPE_GARBAGE
#define MAX_VEHICLE_GARBAGE (30)
#define GARBAGE_MONEY (100000)

enum e_garbage
{
	garbageId, garbageInVehicle, garbageCollected
}

new garbage_data[MAX_PLAYERS][e_garbage];

new Float: garbage_cps[][] ={
	{2780.736572, 2199.797607, 10.537600},
	{2196.996338, 942.116394, 10.450410},
	{1115.288330, 1795.998657, 10.691500},
	{2667.481934, 1208.429810, 10.673500},
	{1729.918335, 967.724915, 10.929690},
	{2524.743652, 1497.332520, 10.601470},
	{1628.782837, 663.968384, 10.929690},
	{2206.853516, 748.919006, 11.195310},
	{2207.637939, 668.993164, 11.203130},
	{2064.958008, 637.574402, 11.203130},
	{2381.729980, 1639.489502, 10.556840},
	{1934.537842, 2681.559814, 10.535700},
	{2069.969238, 2683.821533, 10.509890},
	{2590.812012, 1400.744995, 10.761710},
	{948.076111, 1993.424927, 10.550840},
	{1030.046143, 2040.658569, 11.182460},
	{1461.112915, 2549.287598, 10.489030},
	{1680.078369, 2629.321777, 10.548870},
	{1647.638916, 2782.135742, 10.549510},
	{2322.396484, 668.422974, 11.180000},
	{2369.049316, 677.380615, 11.195310},
	{2463.143066, 709.301758, 11.195310},
	{1971.266846, 712.686340, 10.562500},
	{1834.187744, 653.108276, 11.183470},
	{2328.343018, 2786.105957, 11.007810}
};

hook OnGameModeInit()
{
	// unload
	CreateDynamicObject(10984, 2518.947021, 2814.800049, 9.801200, 0.000000, 0.000000, 207.000000);
	CreateDynamicObject(10984, 2517.073242, 2820.527832, 9.801200, 0.000000, 0.000000, 136.000000);
	CreateDynamicObject(10984, 2523.507080, 2811.987305, 9.801200, 0.000000, 0.000000, 171.000000);
	CreateDynamicObject(10984, 2516.580078, 2825.704834, 9.801200, 0.000000, 0.000000, 136.000000);
	CreateDynamicObject(10984, 2530.241455, 2811.834717, 9.801200, 0.000000, 0.000000, 302.000000);
	CreateDynamicObject(10984, 2524.044434, 2824.798828, 9.801200, 0.000000, 0.000000, 196.000000);
	CreateDynamicObject(10984, 2529.811768, 2817.409668, 9.801200, 0.000000, 0.000000, 136.000000);
	CreateDynamicObject(10984, 2521.479492, 2830.711670, 9.801200, 0.000000, 0.000000, 178.000000);
	CreateDynamicObject(10984, 2531.680176, 2826.327881, 9.801200, 0.000000, 0.000000, 360.000000);

	CreateDynamicObject(1227, 2780.736572, 2199.797607, 10.537600, 0.000000, 0.000000, 98.000000, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1331, 2196.996338, 942.116394, 10.450410, 0.000000, 0.000000, 0.000000, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1331, 1115.288330, 1795.998657, 10.691500, 0.000000, 0.000000, 270.000000, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1331, 2667.481934, 1208.429810, 10.673500, 0.000000, 0.000000, 90.420242, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1334, 1729.918335, 967.724915, 10.929690, 356.858398, 0.000000, 3.141590, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1334, 2524.743652, 1497.332520, 10.601470, 0.000000, 0.000000, 0.000000, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1334, 1628.782837, 663.968384, 10.929690, 356.858398, 0.000000, 3.141590, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 2206.853516, 748.919006, 11.195310, 356.858398, 0.000000, 0.000000, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 2207.637939, 668.993164, 11.203130, 356.858398, 0.000000, 0.000000, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 2064.958008, 637.574402, 11.203130, 3.141590, 0.000000, 3.141590, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 2381.729980, 1639.489502, 10.556840, 0.000000, 0.000000, -270.959534, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 1934.537842, 2681.559814, 10.535700, 0.000000, 0.000000, 267.000000, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 2069.969238, 2683.821533, 10.509890, 0.000000, 0.000000, 179.879059, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 2590.812012, 1400.744995, 10.761710, 0.000000, 0.000000, 0.000000, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 948.076111, 1993.424927, 10.550840, 0.000000, 0.000000, 0.000000, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 1030.046143, 2040.658569, 11.182460, 0.000000, 0.000000, -90.059860, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 1461.112915, 2549.287598, 10.489030, 0.000000, 0.000000, -1.559930, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 1680.078369, 2629.321777, 10.548870, 0.000000, 0.000000, 180.419571, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 1647.638916, 2782.135742, 10.549510, 0.000000, 0.000000, 1.080000, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 2322.396484, 668.422974, 11.180000, 0.000000, 0.000000, 179.578903, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 2369.049316, 677.380615, 11.195310, 3.141590, 0.000000, 3.141590, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 2463.143066, 709.301758, 11.195310, 3.141590, 0.000000, 1.570800, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 1971.266846, 712.686340, 10.562500, 356.858398, 0.000000, 3.141590, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1343, 1834.187744, 653.108276, 11.183470, 0.000000, 0.000000, -91.379982, -1, -1, -1, 400.000000, 400.000000);
	CreateDynamicObject(1358, 2328.343018, 2786.105957, 11.007810, 356.858398, 0.000000, -1.640490, -1, -1, -1, 400.000000, 400.000000);

	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerConnect(playerid)
{
	RemoveBuildingForPlayer(playerid, 1334, 1632.015625, 663.984375, 10.929700, 0.250000);
	RemoveBuildingForPlayer(playerid, 1334, 1732.742188, 967.835876, 10.929700, 0.250000);

	RemoveBuildingForPlayer(playerid, 1343, 2065.734375, 637.578125, 11.203100, 0.250000);
	RemoveBuildingForPlayer(playerid, 1343, 2205.664063, 748.914124, 11.195300, 0.250000);

	RemoveBuildingForPlayer(playerid, 1370, 1358.484375, 483.656311, 19.695299, 0.250000);
	RemoveBuildingForPlayer(playerid, 1370, 1373.171875, 471.101593, 19.695299, 0.250000);
	RemoveBuildingForPlayer(playerid, 1370, 1373.453125, 469.968811, 19.695299, 0.250000);
	return Y_HOOKS_CONTINUE_RETURN_1;
}

reset_garbage_vars(playerid)
{
	garbage_data[playerid][garbageId] = -1;
	garbage_data[playerid][garbageCollected] = 0;
	garbage_data[playerid][garbageInVehicle] = 0;
	return 1;
}

start_garbage_work(playerid)
{
	job::createJobVehicle(playerid, 408, 2522.9998, 2774.9202, 11.3710, 90.0, 120);
	return give_garbage_cp(playerid);
}

cancel_garbage_work(playerid)
{
    if(job_data[playerid][jobDuty] != JOB_TYPE_GARBAGE)
        return 1;

    return reset_garbage_vars(playerid);
}

give_garbage_cp(playerid)
{
	new
		cp_random = random(sizeof garbage_cps);

	if(cp_random == garbage_data[playerid][garbageId] && garbage_data[playerid][garbageId] != 0)
		return give_garbage_cp(playerid);

	DisablePlayerCheckpoint(playerid);
	SetJobCheckpoint(playerid, garbage_cps[cp_random][0], garbage_cps[cp_random][1], garbage_cps[cp_random][2], 2.0);
	
	garbage_data[playerid][garbageId] = cp_random;

	SCMF(playerid, COLOR_YELLOW, "Mergi la checkpoint pentru a incepe colectarea gunoiului. Distanta: %.2fm.", GetPlayerDistanceFromPoint(playerid, garbage_cps[cp_random][0], garbage_cps[cp_random][1], garbage_cps[cp_random][2]));
	s_PlayerInfo[playerid][pSCP] = CP_GARBAGE;
	return 1;
}

give_garbage_money(playerid)
{
    new
        job_money = (GARBAGE_MONEY) + (job::returnPlayerSkill(playerid, JOB_TYPE_GARBAGE) * 10000 + RandomEx((job::returnPlayerSkill(playerid, JOB_TYPE_GARBAGE) * 5000), (job::returnPlayerSkill(playerid, JOB_TYPE_GARBAGE) * 5000) + 5000));
    
    SCMF(playerid, -1, "{909CE7}(Job): {FFFFFF}Ai descarcat 30 KG de gunoi si ai primit $%s.", FormatNumber(job_money));

    DailyQuestCheck(playerid, QUEST_TYPE_GARBAGE , 30);

    GivePlayerMoney(playerid, job_money);
    return job::updateJobSkill(playerid, JOB_TYPE_GARBAGE);
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys == KEY_WALK)
	{
		if(job_data[playerid][jobDuty] == JOB_TYPE_GARBAGE)
		{
			if(!IsPlayerAttachedObjectSlotUsed(playerid, JOB_INDEX))
			{
				if(!IsPlayerInRangeOfPoint(playerid, 2.0, garbage_cps[garbage_data[playerid][garbageId]][0], garbage_cps[garbage_data[playerid][garbageId]][1], garbage_cps[garbage_data[playerid][garbageId]][2]))
					return 1;

				GameTextForPlayer(playerid, "~w~DU-TE IN SPATELE MASINII DE GUNOI~n~SI APASA ALT PENTRU A INCARCA~n~GUNOIUL", 2000, 3);

				DisablePlayerCheckpoint(playerid);
				SetPlayerAttachedObject(playerid, JOB_INDEX, 1265, 6, 0.28, -0.04, -0.11, -42.99, -85.60, -13.30, 0.56, 0.76, 1.06);
			}
			else if(IsPlayerAttachedObjectSlotUsed(playerid, JOB_INDEX))
			{
				new
					Float: x, Float: y, Float: z, Float: rot;

				GetVehiclePos(job_data[playerid][jobVehicle], x, y, z);
				GetVehicleZAngle(job_data[playerid][jobVehicle], rot);

				rot = 360-rot;

				x = floatsin(rot,degrees)*-4.0 + floatcos(rot,degrees)*0.0 + x;
				y = floatcos(rot,degrees)*-4.0 - floatsin(rot,degrees)*0.0 + y;
				z = 0.0 + z;

				if(IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z))
				{
					RemovePlayerAttachedObject(playerid, JOB_INDEX);

					new
						garbage_collected = RandomEx(5, 10);

					garbage_data[playerid][garbageInVehicle] = (garbage_data[playerid][garbageInVehicle] + garbage_collected >= MAX_VEHICLE_GARBAGE) ? (30) : (garbage_data[playerid][garbageInVehicle] + garbage_collected);

					format(gString, sizeof gString, "~w~AI INCARCAT PANA ACUM~n~~r~%d~w~/%d KG DE GUNOI", garbage_data[playerid][garbageInVehicle], MAX_VEHICLE_GARBAGE);
					GameTextForPlayer(playerid, gString, 3000, 3);

					if(garbage_data[playerid][garbageInVehicle] >= MAX_VEHICLE_GARBAGE)
					{
						SCM(playerid, -1, "Now your Trashmaster is full, you need to unload the trash.");
						SCM(playerid, COLOR_YELLOW, "Tasteaza comanda /unloadtrash odata ajuns la groapa de gunoi pentru a fi platit.");
						return 1;
					}
					give_garbage_cp(playerid);
				}
			}
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterCheckpoint(playerid)
{
	if(s_PlayerInfo[playerid][pSCP] == CP_GARBAGE && job_data[playerid][jobDuty] == JOB_TYPE_GARBAGE)
	{
		DisablePlayerCheckpoint(playerid);
		GameTextForPlayer(playerid, "~w~COLECTEAZA GUNOIUL APASAND~n~TASTA ~r~ALT~w~ APOI DEPOZITEAZA-L IN~n~TRASHMASTER", 1000, 3);
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

YCMD:unloadtrash(playerid, params[], help)
{
	if(!IsPlayerInVehicle(playerid, job_data[playerid][jobVehicle]))
		return SCM(playerid, COLOR_GREY, "You aren't in a TrashMaster.");

	if(garbage_data[playerid][garbageInVehicle] != MAX_VEHICLE_GARBAGE)
		return SCM(playerid, COLOR_GREY, "Masina de gunoi nu este incarcata complet.");

	if(!IsPlayerInRangeOfPoint(playerid, 5.0, 2523.5754, 2814.1118, 11.7786))
	{
		SetPlayerCheckpoint(playerid, 2523.5754, 2814.1118, 11.7786, 3.0);
		s_PlayerInfo[playerid][pSCP] = 1;
		return 1;
	}
	give_garbage_money(playerid);
	give_garbage_cp(playerid);

	return 1;
}
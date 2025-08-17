#include <YSI_Coding\y_hooks>

#define job:: job_
#define SERVER_JOBS (17+1)
#define CP_JOBS_BEGIN (100)
#define JOB_INDEX (1)
enum
{
	JOB_TYPE_NONE, JOB_TYPE_DETECTIVE, JOB_TYPE_DRUGS, JOB_TYPE_PIZZA, JOB_TYPE_BUS, JOB_TYPE_ARMS, JOB_TYPE_GARBAGE, JOB_TYPE_FISHER,
	JOB_TYPE_TRUCKER, JOB_TYPE_FARM, JOB_TYPE_QUARRY, JOB_TYPE_SECURITY, JOB_TYPE_AIR, JOB_TYPE_COURIER, JOB_TYPE_FIREMAN, JOB_TYPE_BEEHIVE,
	JOB_TYPE_NEWS, JOB_TYPE_SWEEAPER
};

enum jobs_e {
	playerJob, playerJobSkill[SERVER_JOBS], playerJobTimes[SERVER_JOBS], playerJobRem[SERVER_JOBS],
	jobDuty, jobVehicle, jobPassedTime, jobMaxPassSeconds
};
new
	job_data[MAX_PLAYERS][jobs_e], jobLeftTime[MAX_PLAYERS], Iterator: jobPlayers<SERVER_JOBS, MAX_PLAYERS>;

new Float: jobPositions[][] =
{
	{0.0, 0.0, 0.0}, // civil
	{607.3777, -1439.4473, 14.0741}, // detective
	{-1109.7118, -1654.2681, 76.4047}, // drugs dealer
	{2122.9788, -1788.8132, 13.5547}, // pizza boy
	{1653.2920, -2237.8301, 13.5192}, // bus driver
	{1365.8931, -1289.0779, 13.5469}, // arms dealer
	{2503.0554, 2778.5754, 10.8203}, // garbage man
	{2000.5967, 1568.3157, 15.3672}, // fisher
	{-49.8452, -269.3628, 6.6332} // trucker
};

new Float: jobWorkLocations[][] =
{
	{0.0, 0.0, 0.0}, // civil
	{0.0, 0.0, 0.0}, // detective
	{-1120.0229, -1621.1617, 76.3672}, // drugs dealer
	{2119.7063, -1789.2145, 13.5547}, // pizza boy
	{1679.7556, -2249.9177, 13.4049}, // bus driver
	{597.5396, -1246.9562, 18.2512}, // arms dealer
	{2523.6685, 2775.4744, 10.8203}, // garbage man
	{2000.5967, 1568.3157, 15.3672}, // fisher
	{-16.0897, -290.5156, 5.4297} // trucker
};

new pointsForSkilling[][] =
{
	{}, // civil
	{}, // detective
	{0, 50, 100, 150}, // drugs dealer
	{0, 26, 34, 49, 89, 99}, // pizza boy 
	{0, 26, 34, 49, 89, 99, 119}, // bus driver
	{0, 100, 200, 300}, // arms dealer
	{0, 26, 34, 49, 89, 99, 119}, // garbage man
	{0, 26, 34, 49, 89, 99, 119}, // fisherman
	{0, 26, 34, 49, 89, 99, 119}, // trucker
	{0, 26, 34, 49, 89, 99, 119}, // farmer
	{0, 100, 125, 150, 175}, // quarry worker
	{0, 26, 34, 49, 89, 99, 119}, // security transporter
	{0, 26, 34, 49, 89, 99, 119}, // air transporter
	{0, 26, 34, 49, 89, 99, 119}, // courier
	{0, 75, 100, 125}, // fireman
	{}, // beehive bekeeper
	{0, 100, 125, 150, 175, 200, 225}, // newsman
	{0, 80, 100, 120, 140, 160} // street seeaper
};

job::returnJobName(jobId)
{
	new
		jobString[24];

	switch(jobId)
	{
		case 1: jobString = "Detective";
		case 2: jobString = "Drugs Dealer";
		case 3: jobString = "Pizza Boy";
		case 4: jobString = "Bus Driver";
		case 5: jobString = "Arms Dealer";
		case 6: jobString = "Garbage Man";
		case 7: jobString = "Fisherman";
		case 8: jobString = "Trucker";
		case 9: jobString = "Farmer";
		case 10: jobString = "Quarry Worker";
		case 11: jobString = "Security Transporter";
		case 12: jobString = "Air Transporter";
		case 13: jobString = "Courier";
		case 14: jobString = "Fireman";
		case 15: jobString = "Beehive Beekeper";
		case 16: jobString = "Newsman";
		case 17: jobString = "Street Sweeaper";
	}
	return jobString;
}

job::getCommandName(jobId)
{
	new jobString[24];
	switch(jobId)
	{
		case JOB_TYPE_DETECTIVE:
			jobString = "/find";
		case JOB_TYPE_DRUGS:
			jobString = "/getseeds";
		case JOB_TYPE_ARMS:
			jobString = "/getmats";
		case JOB_TYPE_FISHER:
			jobString = "/fish";
		default:
			jobString = "/work";
	}
	return jobString;
}

hook OnGameModeInit()
{
	for(new i = 1; i < 9; ++i)
	{
		format(gString, sizeof gString, "ID: {909CE7}%d\n{FFFFFF}Job: {909CE7}%s\n{FFFFFF}Use {909CE7}/getjob{FFFFFF} to get the job.", i, job::returnJobName(i));
		CreateDynamic3DTextLabel(gString, -1, jobPositions[i][0], jobPositions[i][1], jobPositions[i][2], 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1);
		AddStaticPickup(1275, 23, jobPositions[i][0], jobPositions[i][1], jobPositions[i][2]);

		switch(i)
		{
			case JOB_TYPE_DRUGS:
				gString = "{909CE7}Drugs Dealer{ffffff}\nType {909CE7}/getseeds{ffffff} to buy seeds\nType {909CE7}/buydrugs{FFFFFF} to buy drugs {909CE7}(skill 3+) only{FFFFFF}";
			case JOB_TYPE_PIZZA:
				gString = "{FFFFFF}Job: {909CE7}Pizza Boy\n{FFFFFF}Type {909CE7}/work{FFFFFF} to get a scooter.";	
			case JOB_TYPE_ARMS:
				gString = "{0E7BE9}Materials Pickup!\n\nType /getmats as an Arms Dealer\nto collect materials";
			default:
				format(gString, sizeof gString, "{FFFFFF}Job: {909CE7}%s\n{FFFFFF}Type {909CE7}/work{FFFFFF} to start working.", job::returnJobName(i));
		}
		if(i != JOB_TYPE_DETECTIVE && i != JOB_TYPE_FISHER && i != JOB_TYPE_BUS)
			CreateDynamic3DTextLabel(gString, -1, jobWorkLocations[i][0], jobWorkLocations[i][1], jobWorkLocations[i][2], 60.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1);
	}
	Command_AddAltNamed("skill", "skills");
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerSpawn(playerid)
{
	stop_job_work(playerid);

    if(IsPlayerAttachedObjectSlotUsed(playerid, JOB_INDEX))
        RemovePlayerAttachedObject(playerid, JOB_INDEX);
    
    if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_NONE)
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerConnect(playerid)
{
	jobLeftTime[playerid] = -1;
	reset_fish_vars(playerid);
	reset_gun_vars(playerid);
	reset_mats_vars(playerid);
	reset_drugs_vars(playerid);
	reset_pizza_vars(playerid);
	reset_garbage_vars(playerid);
	reset_truck_vars(playerid);
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(job_data[playerid][jobDuty] != JOB_TYPE_NONE)
	{
		if(IsValidVehicle(job_data[playerid][jobVehicle]))
		{
			DestroyVehicle(job_data[playerid][jobVehicle]);
			job_data[playerid][jobVehicle] = INVALID_VEHICLE_ID;
		}
	}
	if(Iter_Contains(jobPlayers<job_data[playerid][playerJob]>, playerid)) Iter_Remove(jobPlayers<job_data[playerid][playerJob]>, playerid);

	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER)
    {
        if(job_data[playerid][jobVehicle] == s_PlayerInfo[playerid][pSLastVehicle] && job_data[playerid][jobVehicle] && job_data[playerid][jobDuty] != JOB_TYPE_NONE)
        {
        	if(job_data[playerid][playerJob] != JOB_TYPE_BUS && job_data[playerid][playerJob] != JOB_TYPE_TRUCKER)
            	SCMF(playerid, COLOR_GREY, "You have %d seconds to get back into the car, or you will lose the job.", jobLeftTime[playerid]);
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterCheckpoint(playerid)
{
	if(job_data[playerid][jobDuty] != JOB_TYPE_NONE)
	{
	    if(job_data[playerid][jobPassedTime] + job_data[playerid][jobMaxPassSeconds] > gettime())
	    {
	        ABroadCast(COLOR_RED, 1, "%s (%d, level %d) might be using teleport-hack on job %s (%d seconds passed)", GetName(playerid), playerid, PlayerInfo[playerid][pLevel], job::returnJobName(job_data[playerid][playerJob]), gettime() - job_data[playerid][jobPassedTime]);
	    }
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterRaceCP(playerid)
{
	if(job_data[playerid][jobDuty] != JOB_TYPE_NONE)
	{
	    if(job_data[playerid][jobPassedTime] + job_data[playerid][jobMaxPassSeconds] > gettime())
	    {
	        ABroadCast(COLOR_RED, 1, "%s (%d, level %d) might be using teleport-hack on job %s (%d seconds passed)", GetName(playerid), playerid, PlayerInfo[playerid][pLevel], job::returnJobName(job_data[playerid][playerJob]), gettime() - job_data[playerid][jobPassedTime]);
	    }
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnVehicleSpawn(vehicleid)
{
	foreach(new i : All(jobPlayers<>))
	{
		if(job_data[i][jobDuty] != JOB_TYPE_NONE && job_data[i][jobVehicle] == vehicleid)
		{
			SCM(i, COLOR_GREY, "You've lost the job!");
			return stop_job_work(i);
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

job::returnJobMAXSkill(jobId)
{
	switch(jobId)
	{
		case 0: return -1;
		case 1: return -1;
		case 2: return 3;
		case 3: return 5;
		case 4: return 6;
		case 5: return 3;
		case 6: return 6;
		case 7: return 6;
		case 8: return 6;
		case 9: return 6;
		case 10: return 4;
		case 11: return 6;
		case 12: return 6;
		case 13: return 6;
		case 14: return 3;
		case 15: return -1;
		case 16: return 6;
		case 17: return 5;
	}
	return -1;
}

job::createJobVehicle(playerid, modelId, Float: vPosX, Float: vPoxY, Float: vPosZ, Float: vAngle = 0.0, vreSpawn)
{
	if(IsValidVehicle(job_data[playerid][jobVehicle]))
		return 1;

	job_data[playerid][jobVehicle] = AddStaticVehicleEx(modelId, vPosX, vPoxY, vPosZ, vAngle, 1, 1, vreSpawn, 0, VEH_TYPE_JOB);
	PutPlayerInVehicle(playerid, job_data[playerid][jobVehicle], 0);

	if(vreSpawn)
		jobLeftTime[playerid] = vreSpawn;

	new
		jobVehId = job_data[playerid][jobVehicle];

	VehicleInfo[jobVehId][vehFuel] = 100;
	VehicleInfo[jobVehId][vehLocked] = 1;

	format(gString, sizeof gString, "B %02d RPL", job_data[playerid][jobVehicle]);
	SetVehicleNumberPlate(job_data[playerid][jobVehicle], gString);

	return 1;
}

job::returnPlayerSkill(playerid, jobId) return job_data[playerid][playerJobSkill][jobId];

job::updateJobSkill(playerid, jobId)
{
	job_data[playerid][playerJobTimes][jobId] ++;
	if(job_data[playerid][playerJobSkill][jobId] != job::returnJobMAXSkill(jobId))
	{
		job_data[playerid][playerJobRem][jobId] --;

		if(!job_data[playerid][playerJobRem][jobId])
		{
			job_data[playerid][playerJobSkill][jobId] ++;
			job_data[playerid][playerJobRem][jobId] = pointsForSkilling[jobId][job_data[playerid][playerJobSkill][jobId]];

			SCMF(playerid, COLOR_YELLOW, "Felicitari! Ai acum skill %d pentru acest job!", job_data[playerid][playerJobSkill][jobId]);
		}
	}
	mysql_format(SQL, gString, sizeof gString, "update `users` set `JobSkill` = '%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d', `JobTimes` = '%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d', `JobRem` = '%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d' where `id` = '%d';",
		job_data[playerid][playerJobSkill][0], job_data[playerid][playerJobSkill][1], job_data[playerid][playerJobSkill][2], job_data[playerid][playerJobSkill][3], job_data[playerid][playerJobSkill][4], job_data[playerid][playerJobSkill][5], job_data[playerid][playerJobSkill][6], job_data[playerid][playerJobSkill][7], job_data[playerid][playerJobSkill][8], job_data[playerid][playerJobSkill][9], job_data[playerid][playerJobSkill][10], job_data[playerid][playerJobSkill][11], job_data[playerid][playerJobSkill][12], job_data[playerid][playerJobSkill][13], job_data[playerid][playerJobSkill][14], job_data[playerid][playerJobSkill][15], job_data[playerid][playerJobSkill][16], job_data[playerid][playerJobSkill][17],
		job_data[playerid][playerJobTimes][0], job_data[playerid][playerJobTimes][1], job_data[playerid][playerJobTimes][2], job_data[playerid][playerJobTimes][3], job_data[playerid][playerJobTimes][4], job_data[playerid][playerJobTimes][5], job_data[playerid][playerJobTimes][6], job_data[playerid][playerJobTimes][7], job_data[playerid][playerJobTimes][8], job_data[playerid][playerJobTimes][9], job_data[playerid][playerJobTimes][10], job_data[playerid][playerJobTimes][11], job_data[playerid][playerJobTimes][12], job_data[playerid][playerJobTimes][13], job_data[playerid][playerJobTimes][14], job_data[playerid][playerJobTimes][15], job_data[playerid][playerJobTimes][16], job_data[playerid][playerJobTimes][17],
		job_data[playerid][playerJobRem][0], job_data[playerid][playerJobRem][1], job_data[playerid][playerJobRem][2], job_data[playerid][playerJobRem][3], job_data[playerid][playerJobRem][4], job_data[playerid][playerJobRem][5], job_data[playerid][playerJobRem][6], job_data[playerid][playerJobRem][7], job_data[playerid][playerJobRem][8], job_data[playerid][playerJobRem][9], job_data[playerid][playerJobRem][10], job_data[playerid][playerJobRem][11], job_data[playerid][playerJobRem][12], job_data[playerid][playerJobRem][13], job_data[playerid][playerJobRem][14], job_data[playerid][playerJobRem][15], job_data[playerid][playerJobRem][16], job_data[playerid][playerJobRem][17], PlayerInfo[playerid][pSQLID]);
	return mysql_tquery(SQL, gString, "", "");
}

stock SetJobCheckpoint(playerid, Float: x, Float: y, Float: z, Float: size, max_time=10)
{
	if(GetPlayerDistanceFromPoint(playerid, x, y, z) < 100.0)
		max_time -= 2;

	job_data[playerid][jobPassedTime] = gettime();
	job_data[playerid][jobMaxPassSeconds] = max_time;

	return SetPlayerCheckpoint(playerid, x, y, z, size);
}

stock SetJobRaceCheckpoint(playerid, type, Float: x, Float: y, Float: z, Float: nextx, Float: nexty, Float: nextz, Float: size, max_time=10)
{
	job_data[playerid][jobPassedTime] = gettime();
	job_data[playerid][jobMaxPassSeconds] = max_time;

	return SetPlayerRaceCheckpoint(playerid, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size);
}

IsPlayerInJobVehicle(playerid)
{
	if(!IsValidVehicle(job_data[playerid][jobVehicle]))
		return 0;

	return IsPlayerInVehicle(playerid, job_data[playerid][jobVehicle]) ? (1) : (0);
}

IsAJobVehicle(vehicleid)
{
	return Iter_Contains(VehicleType<VEH_TYPE_JOB>, vehicleid) ? (1) : (0);
}	

hook WhenPlayerLoggedIn(playerid)
{
	if(cache_num_rows())
	{
		job_data[playerid][playerJob] = cache_get_field_content_int(0, "Job");

		new
			loadString[128];

        cache_get_field_content(0, "JobSkill", loadString, SQL, sizeof loadString);
        sscanf(loadString, "a<i>[18]", job_data[playerid][playerJobSkill]);

        cache_get_field_content(0, "JobTimes", loadString, SQL, sizeof loadString);
        sscanf(loadString, "a<i>[18]", job_data[playerid][playerJobTimes]);

        cache_get_field_content(0, "JobRem", loadString, SQL, sizeof loadString);
        sscanf(loadString, "a<i>[18]", job_data[playerid][playerJobRem]);
	}
}

YCMD:jobs(playerid, params[], help)
{
    if(HavePlayerCheckpoint(playerid))
        return showActiveCheckpointDialog(playerid);

    new
    	jobs=1, jobString[256];
    
    while(jobs < SERVER_JOBS)
    {
    	format(jobString, sizeof jobString, "%s%s\n", jobString, job::returnJobName(jobs));
    	jobs++;
    }

	Dialog_Show(playerid, DIALOG_JOBS, DIALOG_STYLE_LIST, "Jobs:", jobString, "Select", "Close");
	return 1;
}

Dialog:DIALOG_JOBS(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	SetPlayerCheckpoint(playerid, jobPositions[listitem+1][0], jobPositions[listitem+1][1], jobPositions[listitem+1][2], 2.0);
	s_PlayerInfo[playerid][pSCP] = 1;
	return SCM(playerid, COLOR_YELLOW, "Mergi la checkpoint-ul marcat pe harta pentru a ajunge la locatia jobului.");
}

job::returnSkillName(playerid, jobId)
{
	new
		jobString[24];

	switch(jobId)
	{
		case JOB_TYPE_DRUGS: format(jobString, sizeof jobString, "%d planted seeds", job_data[playerid][playerJobTimes][jobId]);
		case JOB_TYPE_PIZZA: format(jobString, sizeof jobString, "delivered %d pizzas", job_data[playerid][playerJobTimes][jobId]);
		case JOB_TYPE_BUS: format(jobString, sizeof jobString, "%d shifts completed", job_data[playerid][playerJobTimes][jobId]);
		case JOB_TYPE_ARMS: format(jobString, sizeof jobString, "delivered materials %d times", job_data[playerid][playerJobTimes][jobId]);
		case JOB_TYPE_GARBAGE: format(jobString, sizeof jobString, "%d shifts completed", job_data[playerid][playerJobTimes][jobId]);
		case JOB_TYPE_FISHER: format(jobString, sizeof jobString, "%d fish caught", job_data[playerid][playerJobTimes][jobId]);
		case JOB_TYPE_TRUCKER: format(jobString, sizeof jobString, "%d trailers delivered", job_data[playerid][playerJobTimes][jobId]);
		case JOB_TYPE_FARM: format(jobString, sizeof jobString, "%d bags of flour sold", job_data[playerid][playerJobTimes][jobId]);
		case JOB_TYPE_QUARRY: format(jobString, sizeof jobString, "%d shifts completed", job_data[playerid][playerJobTimes][jobId]);
		case JOB_TYPE_SECURITY: format(jobString, sizeof jobString, "%d shifts completed", job_data[playerid][playerJobTimes][jobId]);
		case JOB_TYPE_AIR: format(jobString, sizeof jobString, "%d packages successfully dropped", job_data[playerid][playerJobTimes][jobId]);
		case JOB_TYPE_COURIER: format(jobString, sizeof jobString, "%d parcels delivered", job_data[playerid][playerJobTimes][jobId]);
		case JOB_TYPE_FIREMAN: format(jobString, sizeof jobString, "%d extinguished fires", job_data[playerid][playerJobTimes][jobId]);
		case JOB_TYPE_NEWS: format(jobString, sizeof jobString, "%d newspapers sold", job_data[playerid][playerJobTimes][jobId]);
		case JOB_TYPE_SWEEAPER: format(jobString, sizeof jobString, "%d shifts completed", job_data[playerid][playerJobTimes][jobId]);
	}
	return jobString;
}

YCMD:skill(playerid, params[], help)
{
	if(!PlayerInfo[playerid][pHUD][6])
	{
		for(new i=1; i < SERVER_JOBS; ++i)
		{
			if(i == JOB_TYPE_DETECTIVE || i == JOB_TYPE_BEEHIVE)
				continue;

			if(job_data[playerid][playerJobSkill][i] != job::returnJobMAXSkill(i))
				SCMF(playerid, -1, "%s skill: %d/%d (%s) | Needed for next skill level: %d", job::returnJobName(i), job::returnPlayerSkill(playerid, i), job::returnJobMAXSkill(i), job::returnSkillName(playerid, i), job_data[playerid][playerJobRem][i]);
			else
				SCMF(playerid, -1, "%s skill: %d/%d (%s)", job::returnJobName(i), job::returnPlayerSkill(playerid, i), job::returnJobMAXSkill(i), job::returnSkillName(playerid, i));
		}
	}
	else
	{
		new commandString[sizeof gString];
		for(new i=1; i < SERVER_JOBS; ++i)
		{
			if(i == JOB_TYPE_DETECTIVE || i == JOB_TYPE_BEEHIVE)
				continue;

			if(job_data[playerid][playerJobSkill][i] != job::returnJobMAXSkill(i))
				format(commandString, sizeof commandString, "%s{FFFFFF}%s skill: %d/%d (%s) | Needed for next skill level: %d\n", commandString, job::returnJobName(i), job::returnPlayerSkill(playerid, i), job::returnJobMAXSkill(i), job::returnSkillName(playerid, i), job_data[playerid][playerJobRem][i]);
			else
				format(commandString, sizeof commandString, "%s{FFFFFF}%s skill: %d/%d (%s)\n", commandString, job::returnJobName(i), job::returnPlayerSkill(playerid, i), job::returnJobMAXSkill(i), job::returnSkillName(playerid, i));
		}
		Dialog_Show(playerid, DOALOG_SKILLS, DIALOG_STYLE_MSGBOX, "Skills", commandString, "Ok", "");
	}
	return 1;
}

/*
YCMD:skill(playerid, params[], help)
{
	if(!PlayerInfo[playerid][pHUD][6])
	{
		SCM(playerid, -1, "---- Skills: ----");
	
		SCM(playerid, -1, "Rob skill: 1/6 (0 robs) | Needed for next skill level: 60");
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_DRUGS] != job::returnJobMAXSkill(JOB_TYPE_DRUGS))
			SCMF(playerid, -1, "Drugs Dealer skill: %d/%d (%d planted seeds) | Needed for next skill level: %d", job::returnPlayerSkill(playerid, JOB_TYPE_DRUGS), job::returnJobMAXSkill(JOB_TYPE_DRUGS), job_data[playerid][playerJobTimes][JOB_TYPE_DRUGS], job_data[playerid][playerJobRem][JOB_TYPE_DRUGS]);
		else
			SCMF(playerid, -1, "Drugs Dealer skill: %d/%d (%d planted seeds)", job::returnPlayerSkill(playerid, JOB_TYPE_DRUGS), job::returnJobMAXSkill(JOB_TYPE_DRUGS), job_data[playerid][playerJobTimes][JOB_TYPE_DRUGS]);
		
		if(job_data[playerid][playerJobSkill][JOB_TYPE_PIZZA] != job::returnJobMAXSkill(JOB_TYPE_PIZZA))
			SCMF(playerid, -1, "Pizza Boy skill: %d/%d (delivered %d pizzas) | Needed for next skill level: %d", job::returnPlayerSkill(playerid, JOB_TYPE_PIZZA), job::returnJobMAXSkill(JOB_TYPE_PIZZA), job_data[playerid][playerJobTimes][JOB_TYPE_PIZZA], job_data[playerid][playerJobRem][JOB_TYPE_PIZZA]);
		else
			SCMF(playerid, -1, "Pizza Boy skill: %d/%d (delivered %d pizzas)", job::returnPlayerSkill(playerid, JOB_TYPE_PIZZA), job::returnJobMAXSkill(JOB_TYPE_PIZZA), job_data[playerid][playerJobTimes][JOB_TYPE_PIZZA]);
		
		if(job_data[playerid][playerJobSkill][JOB_TYPE_BUS] != job::returnJobMAXSkill(JOB_TYPE_BUS))
			SCMF(playerid, -1, "Bus Driver skill: %d/%d (%d shifts completed) | Needed for next skill level: %d", job::returnPlayerSkill(playerid, JOB_TYPE_BUS), job::returnJobMAXSkill(JOB_TYPE_BUS), job_data[playerid][playerJobTimes][JOB_TYPE_BUS], job_data[playerid][playerJobRem][JOB_TYPE_BUS]);
		else
			SCMF(playerid, -1, "Bus Driver skill: %d/%d (%d shifts completed)", job::returnPlayerSkill(playerid, JOB_TYPE_BUS), job::returnJobMAXSkill(JOB_TYPE_BUS), job_data[playerid][playerJobTimes][JOB_TYPE_BUS]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_ARMS] != job::returnJobMAXSkill(JOB_TYPE_ARMS))
			SCMF(playerid, -1, "Arms Dealer skill: %d/%d (delivered materials %d times) | Needed for next skill level: %d", job::returnPlayerSkill(playerid, JOB_TYPE_ARMS), job::returnJobMAXSkill(JOB_TYPE_ARMS), job_data[playerid][playerJobTimes][JOB_TYPE_ARMS], job_data[playerid][playerJobRem][JOB_TYPE_ARMS]);
		else
			SCMF(playerid, -1, "Arms Dealer skill: %d/%d (delivered materials %d times)", job::returnPlayerSkill(playerid, JOB_TYPE_ARMS), job::returnJobMAXSkill(JOB_TYPE_ARMS), job_data[playerid][playerJobTimes][JOB_TYPE_ARMS]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_GARBAGE] != job::returnJobMAXSkill(JOB_TYPE_GARBAGE))
			SCMF(playerid, -1, "Garbage Man skill: %d/%d (%d shifts completed) | Needed for next skill level: %d", job::returnPlayerSkill(playerid, JOB_TYPE_GARBAGE), job::returnJobMAXSkill(JOB_TYPE_GARBAGE), job_data[playerid][playerJobTimes][JOB_TYPE_GARBAGE], job_data[playerid][playerJobRem][JOB_TYPE_GARBAGE]);
		else
			SCMF(playerid, -1, "Garbage Man skill: %d/%d (%d shifts completed)", job::returnPlayerSkill(playerid, JOB_TYPE_GARBAGE), job::returnJobMAXSkill(JOB_TYPE_GARBAGE), job_data[playerid][playerJobTimes][JOB_TYPE_GARBAGE]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_FISHER] != job::returnJobMAXSkill(JOB_TYPE_FISHER))
			SCMF(playerid, -1, "Fisherman skill: %d/%d (%d fish caught) | Needed for next skill level: %d", job::returnPlayerSkill(playerid, JOB_TYPE_FISHER), job::returnJobMAXSkill(JOB_TYPE_FISHER), job_data[playerid][playerJobTimes][JOB_TYPE_FISHER], job_data[playerid][playerJobRem][JOB_TYPE_FISHER]);
		else
			SCMF(playerid, -1, "Fisherman skill: %d/%d (%d fish caught)", job::returnPlayerSkill(playerid, JOB_TYPE_FISHER), job::returnJobMAXSkill(JOB_TYPE_FISHER), job_data[playerid][playerJobTimes][JOB_TYPE_FISHER]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_TRUCKER] != job::returnJobMAXSkill(JOB_TYPE_TRUCKER))
			SCMF(playerid, -1, "Trucker skill: %d/%d (%d trailers delivered) | Needed for next skill level: %d", job::returnPlayerSkill(playerid, JOB_TYPE_TRUCKER), job::returnJobMAXSkill(JOB_TYPE_TRUCKER), job_data[playerid][playerJobTimes][JOB_TYPE_TRUCKER], job_data[playerid][playerJobRem][JOB_TYPE_TRUCKER]);
		else
			SCMF(playerid, -1, "Trucker skill: %d/%d (%d trailers delivered)", job::returnPlayerSkill(playerid, JOB_TYPE_TRUCKER), job::returnJobMAXSkill(JOB_TYPE_TRUCKER), job_data[playerid][playerJobTimes][JOB_TYPE_TRUCKER]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_FARM] != job::returnJobMAXSkill(JOB_TYPE_FARM))
			SCMF(playerid, -1, "Farmer skill: %d/%d (%d bags of flour sold) | Needed for next skill level: %d", job::returnPlayerSkill(playerid, JOB_TYPE_FARM), job::returnJobMAXSkill(JOB_TYPE_FARM), job_data[playerid][playerJobTimes][JOB_TYPE_FARM], job_data[playerid][playerJobRem][JOB_TYPE_FARM]);
		else
			SCMF(playerid, -1, "Farmer skill: %d/%d (%d bags of flour sold)", job::returnPlayerSkill(playerid, JOB_TYPE_FARM), job::returnJobMAXSkill(JOB_TYPE_FARM), job_data[playerid][playerJobTimes][JOB_TYPE_FARM]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_QUARRY] != job::returnJobMAXSkill(JOB_TYPE_QUARRY))
			SCMF(playerid, -1, "Quarry Worker skill: %d/%d (%d shifts completed) | Needed for next skill level: %d", job::returnPlayerSkill(playerid, JOB_TYPE_QUARRY), job::returnJobMAXSkill(JOB_TYPE_QUARRY), job_data[playerid][playerJobTimes][JOB_TYPE_QUARRY], job_data[playerid][playerJobRem][JOB_TYPE_QUARRY]);
		else
			SCMF(playerid, -1, "Quarry Worker skill: %d/%d (%d shifts completed)", job::returnPlayerSkill(playerid, JOB_TYPE_QUARRY), job::returnJobMAXSkill(JOB_TYPE_QUARRY), job_data[playerid][playerJobTimes][JOB_TYPE_QUARRY]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_SECURITY] != job::returnJobMAXSkill(JOB_TYPE_SECURITY))
			SCMF(playerid, -1, "Security Transporter skill: %d/%d (%d shifts completed) | Needed for next skill level: %d", job::returnPlayerSkill(playerid, JOB_TYPE_SECURITY), job::returnJobMAXSkill(JOB_TYPE_SECURITY), job_data[playerid][playerJobTimes][JOB_TYPE_SECURITY], job_data[playerid][playerJobRem][JOB_TYPE_SECURITY]);
		else
			SCMF(playerid, -1, "Security Transporter skill: %d/%d (%d shifts completed)", job::returnPlayerSkill(playerid, JOB_TYPE_SECURITY), job::returnJobMAXSkill(JOB_TYPE_SECURITY), job_data[playerid][playerJobTimes][JOB_TYPE_SECURITY]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_AIR] != job::returnJobMAXSkill(JOB_TYPE_AIR))
			SCMF(playerid, -1, "Air Transporter skill: %d/%d (%d packages successfully dropped) | Needed for next skill level: %d", job::returnPlayerSkill(playerid, JOB_TYPE_AIR), job::returnJobMAXSkill(JOB_TYPE_AIR), job_data[playerid][playerJobTimes][JOB_TYPE_AIR], job_data[playerid][playerJobRem][JOB_TYPE_AIR]);
		else
			SCMF(playerid, -1, "Air Transporter skill: %d/%d (%d packages successfully dropped)", job::returnPlayerSkill(playerid, JOB_TYPE_AIR), job::returnJobMAXSkill(JOB_TYPE_AIR), job_data[playerid][playerJobTimes][JOB_TYPE_AIR]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_COURIER] != job::returnJobMAXSkill(JOB_TYPE_COURIER))
			SCMF(playerid, -1, "Courier skill: %d/%d (%d parcels delivered) | Needed for next skill level: %d", job::returnPlayerSkill(playerid, JOB_TYPE_COURIER), job::returnJobMAXSkill(JOB_TYPE_COURIER), job_data[playerid][playerJobTimes][JOB_TYPE_COURIER], job_data[playerid][playerJobRem][JOB_TYPE_COURIER]);
		else
			SCMF(playerid, -1, "Courier skill: %d/%d (%d parcels delivered)", job::returnPlayerSkill(playerid, JOB_TYPE_COURIER), job::returnJobMAXSkill(JOB_TYPE_COURIER), job_data[playerid][playerJobTimes][JOB_TYPE_COURIER]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_FIREMAN] != job::returnJobMAXSkill(JOB_TYPE_FIREMAN))
			SCMF(playerid, -1, "Fireman skill: %d/%d (%d extinguished fires) | Needed next for skill level: %d", job::returnPlayerSkill(playerid, JOB_TYPE_FIREMAN), job::returnJobMAXSkill(JOB_TYPE_FIREMAN), job_data[playerid][playerJobTimes][JOB_TYPE_FIREMAN], job_data[playerid][playerJobRem][JOB_TYPE_FIREMAN]);
		else
			SCMF(playerid, -1, "Fireman skill: %d/%d (%d extinguished fires)", job::returnPlayerSkill(playerid, JOB_TYPE_FIREMAN), job::returnJobMAXSkill(JOB_TYPE_FIREMAN), job_data[playerid][playerJobTimes][JOB_TYPE_FIREMAN]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_NEWS] != job::returnJobMAXSkill(JOB_TYPE_NEWS))
			SCMF(playerid, -1, "Newsman: %d/%d (%d newspapers sold) | Needed next for skill level: %d", job::returnPlayerSkill(playerid, JOB_TYPE_NEWS), job::returnJobMAXSkill(JOB_TYPE_NEWS), job_data[playerid][playerJobTimes][JOB_TYPE_NEWS], job_data[playerid][playerJobRem][JOB_TYPE_NEWS]);
		else
			SCMF(playerid, -1, "Newsman: %d/%d (%d newspapers sold)", job::returnPlayerSkill(playerid, JOB_TYPE_NEWS), job::returnJobMAXSkill(JOB_TYPE_NEWS), job_data[playerid][playerJobTimes][JOB_TYPE_NEWS]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_SWEEAPER] != job::returnJobMAXSkill(JOB_TYPE_SWEEAPER))
			SCMF(playerid, -1, "Street Sweeper: %d/%d (%d shifts completed) | Needed for next skill level: %d", job::returnPlayerSkill(playerid, JOB_TYPE_SWEEAPER), job::returnJobMAXSkill(JOB_TYPE_SWEEAPER), job_data[playerid][playerJobTimes][JOB_TYPE_SWEEAPER], job_data[playerid][playerJobRem][JOB_TYPE_SWEEAPER]);
		else
			SCMF(playerid, -1, "Street Sweeper: %d/%d (%d shifts completed)", job::returnPlayerSkill(playerid, JOB_TYPE_SWEEAPER), job::returnJobMAXSkill(JOB_TYPE_SWEEAPER), job_data[playerid][playerJobTimes][JOB_TYPE_SWEEAPER]);
	}
	else
	{
		format(gString, sizeof gString, "%s{FFFFFF}Rob skill: 1/6 (0 robs) | Needed for next skill level: 60\n");
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_DRUGS] != job::returnJobMAXSkill(JOB_TYPE_DRUGS))
			format(gString, sizeof gString, "%s{FFFFFF}Drugs Dealer skill: %d/%d (%d planted seeds) | Needed for next skill level: %d\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_DRUGS), job::returnJobMAXSkill(JOB_TYPE_DRUGS), job_data[playerid][playerJobTimes][JOB_TYPE_DRUGS], job_data[playerid][playerJobRem][JOB_TYPE_DRUGS]);
		else
			format(gString, sizeof gString, "%s{FFFFFF}Drugs Dealer skill: %d/%d (%d planted seeds)\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_DRUGS), job::returnJobMAXSkill(JOB_TYPE_DRUGS), job_data[playerid][playerJobTimes][JOB_TYPE_DRUGS]);
		
		if(job_data[playerid][playerJobSkill][JOB_TYPE_PIZZA] != job::returnJobMAXSkill(JOB_TYPE_PIZZA))
			format(gString, sizeof gString, "%s{FFFFFF}Pizza Boy skill: %d/%d (delivered %d pizzas) | Needed for next skill level: %d\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_PIZZA), job::returnJobMAXSkill(JOB_TYPE_PIZZA), job_data[playerid][playerJobTimes][JOB_TYPE_PIZZA], job_data[playerid][playerJobRem][JOB_TYPE_PIZZA]);
		else
			format(gString, sizeof gString, "%s{FFFFFF}Pizza Boy skill: %d/%d (delivered %d pizzas)\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_PIZZA), job::returnJobMAXSkill(JOB_TYPE_PIZZA), job_data[playerid][playerJobTimes][JOB_TYPE_PIZZA]);
		
		if(job_data[playerid][playerJobSkill][JOB_TYPE_BUS] != job::returnJobMAXSkill(JOB_TYPE_BUS))
			format(gString, sizeof gString, "%s{FFFFFF}Bus Driver skill: %d/%d (%d shifts completed) | Needed for next skill level: %d\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_BUS), job::returnJobMAXSkill(JOB_TYPE_BUS), job_data[playerid][playerJobTimes][JOB_TYPE_BUS], job_data[playerid][playerJobRem][JOB_TYPE_BUS]);
		else
			format(gString, sizeof gString, "%s{FFFFFF}Bus Driver skill: %d/%d (%d shifts completed)\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_BUS), job::returnJobMAXSkill(JOB_TYPE_BUS), job_data[playerid][playerJobTimes][JOB_TYPE_BUS]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_ARMS] != job::returnJobMAXSkill(JOB_TYPE_ARMS))
			format(gString, sizeof gString, "%s{FFFFFF}Arms Dealer skill: %d/%d (delivered materials %d times) | Needed for next skill level: %d\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_ARMS), job::returnJobMAXSkill(JOB_TYPE_ARMS), job_data[playerid][playerJobTimes][JOB_TYPE_ARMS], job_data[playerid][playerJobRem][JOB_TYPE_ARMS]);
		else
			format(gString, sizeof gString, "%s{FFFFFF}Arms Dealer skill: %d/%d (delivered materials %d times)\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_ARMS), job::returnJobMAXSkill(JOB_TYPE_ARMS), job_data[playerid][playerJobTimes][JOB_TYPE_ARMS]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_GARBAGE] != job::returnJobMAXSkill(JOB_TYPE_GARBAGE))
			format(gString, sizeof gString, "%s{FFFFFF}Garbage Man skill: %d/%d (%d shifts completed) | Needed for next skill level: %d\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_GARBAGE), job::returnJobMAXSkill(JOB_TYPE_GARBAGE), job_data[playerid][playerJobTimes][JOB_TYPE_GARBAGE], job_data[playerid][playerJobRem][JOB_TYPE_GARBAGE]);
		else
			format(gString, sizeof gString, "%s{FFFFFF}Garbage Man skill: %d/%d (%d shifts completed)\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_GARBAGE), job::returnJobMAXSkill(JOB_TYPE_GARBAGE), job_data[playerid][playerJobTimes][JOB_TYPE_GARBAGE]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_FISHER] != job::returnJobMAXSkill(JOB_TYPE_FISHER))
			format(gString, sizeof gString, "%s{FFFFFF}Fisherman skill: %d/%d (%d fish caught) | Needed for next skill level: %d\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_FISHER), job::returnJobMAXSkill(JOB_TYPE_FISHER), job_data[playerid][playerJobTimes][JOB_TYPE_FISHER], job_data[playerid][playerJobRem][JOB_TYPE_FISHER]);
		else
			format(gString, sizeof gString, "%s{FFFFFF}Fisherman skill: %d/%d (%d fish caught)\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_FISHER), job::returnJobMAXSkill(JOB_TYPE_FISHER), job_data[playerid][playerJobTimes][JOB_TYPE_FISHER]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_TRUCKER] != job::returnJobMAXSkill(JOB_TYPE_TRUCKER))
			format(gString, sizeof gString, "%s{FFFFFF}Trucker skill: %d/%d (%d trailers delivered) | Needed for next skill level: %d\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_TRUCKER), job::returnJobMAXSkill(JOB_TYPE_TRUCKER), job_data[playerid][playerJobTimes][JOB_TYPE_TRUCKER], job_data[playerid][playerJobRem][JOB_TYPE_TRUCKER]);
		else
			format(gString, sizeof gString, "%s{FFFFFF}Trucker skill: %d/%d (%d trailers delivered)\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_TRUCKER), job::returnJobMAXSkill(JOB_TYPE_TRUCKER), job_data[playerid][playerJobTimes][JOB_TYPE_TRUCKER]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_FARM] != job::returnJobMAXSkill(JOB_TYPE_FARM))
			format(gString, sizeof gString, "%s{FFFFFF}Farmer skill: %d/%d (%d bags of flour sold) | Needed for next skill level: %d\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_FARM), job::returnJobMAXSkill(JOB_TYPE_FARM), job_data[playerid][playerJobTimes][JOB_TYPE_FARM], job_data[playerid][playerJobRem][JOB_TYPE_FARM]);
		else
			format(gString, sizeof gString, "%s{FFFFFF}Farmer skill: %d/%d (%d bags of flour sold)\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_FARM), job::returnJobMAXSkill(JOB_TYPE_FARM), job_data[playerid][playerJobTimes][JOB_TYPE_FARM]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_QUARRY] != job::returnJobMAXSkill(JOB_TYPE_QUARRY))
			format(gString, sizeof gString, "%s{FFFFFF}Quarry Worker skill: %d/%d (%d shifts completed) | Needed for next skill level: %d\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_QUARRY), job::returnJobMAXSkill(JOB_TYPE_QUARRY), job_data[playerid][playerJobTimes][JOB_TYPE_QUARRY], job_data[playerid][playerJobRem][JOB_TYPE_QUARRY]);
		else
			format(gString, sizeof gString, "%s{FFFFFF}Quarry Worker skill: %d/%d (%d shifts completed)\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_QUARRY), job::returnJobMAXSkill(JOB_TYPE_QUARRY), job_data[playerid][playerJobTimes][JOB_TYPE_QUARRY]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_SECURITY] != job::returnJobMAXSkill(JOB_TYPE_SECURITY))
			format(gString, sizeof gString, "%s{FFFFFF}Security Transporter skill: %d/%d (%d shifts completed) | Needed for next skill level: %d\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_SECURITY), job::returnJobMAXSkill(JOB_TYPE_SECURITY), job_data[playerid][playerJobTimes][JOB_TYPE_SECURITY], job_data[playerid][playerJobRem][JOB_TYPE_SECURITY]);
		else
			format(gString, sizeof gString, "%s{FFFFFF}Security Transporter skill: %d/%d (%d shifts completed)\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_SECURITY), job::returnJobMAXSkill(JOB_TYPE_SECURITY), job_data[playerid][playerJobTimes][JOB_TYPE_SECURITY]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_AIR] != job::returnJobMAXSkill(JOB_TYPE_AIR))
			format(gString, sizeof gString, "%s{FFFFFF}Air Transporter skill: %d/%d (%d packages successfully dropped) | Needed for next skill level: %d\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_AIR), job::returnJobMAXSkill(JOB_TYPE_AIR), job_data[playerid][playerJobTimes][JOB_TYPE_AIR], job_data[playerid][playerJobRem][JOB_TYPE_AIR]);
		else
			format(gString, sizeof gString, "%s{FFFFFF}Air Transporter skill: %d/%d (%d packages successfully dropped)\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_AIR), job::returnJobMAXSkill(JOB_TYPE_AIR), job_data[playerid][playerJobTimes][JOB_TYPE_AIR]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_COURIER] != job::returnJobMAXSkill(JOB_TYPE_COURIER))
			format(gString, sizeof gString, "%s{FFFFFF}Courier skill: %d/%d (%d parcels delivered) | Needed for next skill level: %d\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_COURIER), job::returnJobMAXSkill(JOB_TYPE_COURIER), job_data[playerid][playerJobTimes][JOB_TYPE_COURIER], job_data[playerid][playerJobRem][JOB_TYPE_COURIER]);
		else
			format(gString, sizeof gString, "%s{FFFFFF}Courier skill: %d/%d (%d parcels delivered)\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_COURIER), job::returnJobMAXSkill(JOB_TYPE_COURIER), job_data[playerid][playerJobTimes][JOB_TYPE_COURIER]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_FIREMAN] != job::returnJobMAXSkill(JOB_TYPE_FIREMAN))
			format(gString, sizeof gString, "%s{FFFFFF}Fireman skill: %d/%d (%d extinguished fires) | Needed next for skill level: %d\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_FIREMAN), job::returnJobMAXSkill(JOB_TYPE_FIREMAN), job_data[playerid][playerJobTimes][JOB_TYPE_FIREMAN], job_data[playerid][playerJobRem][JOB_TYPE_FIREMAN]);
		else
			format(gString, sizeof gString, "%s{FFFFFF}Fireman skill: %d/%d (%d extinguished fires)\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_FIREMAN), job::returnJobMAXSkill(JOB_TYPE_FIREMAN), job_data[playerid][playerJobTimes][JOB_TYPE_FIREMAN]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_NEWS] != job::returnJobMAXSkill(JOB_TYPE_NEWS))
			format(gString, sizeof gString, "%s{FFFFFF}Newsman: %d/%d (%d newspapers sold) | Needed next for skill level: %d\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_NEWS), job::returnJobMAXSkill(JOB_TYPE_NEWS), job_data[playerid][playerJobTimes][JOB_TYPE_NEWS], job_data[playerid][playerJobRem][JOB_TYPE_NEWS]);
		else
			format(gString, sizeof gString, "%s{FFFFFF}Newsman: %d/%d (%d newspapers sold)\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_NEWS), job::returnJobMAXSkill(JOB_TYPE_NEWS), job_data[playerid][playerJobTimes][JOB_TYPE_NEWS]);
	
		if(job_data[playerid][playerJobSkill][JOB_TYPE_SWEEAPER] != job::returnJobMAXSkill(JOB_TYPE_SWEEAPER))
			format(gString, sizeof gString, "%s{FFFFFF}Street Sweeper: %d/%d (%d shifts completed) | Needed for next skill level: %d\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_SWEEAPER), job::returnJobMAXSkill(JOB_TYPE_SWEEAPER), job_data[playerid][playerJobTimes][JOB_TYPE_SWEEAPER], job_data[playerid][playerJobRem][JOB_TYPE_SWEEAPER]);
		else
			format(gString, sizeof gString, "%s{FFFFFF}Newsman: %d/%d (%d newspapers sold)\n", gString, job::returnPlayerSkill(playerid, JOB_TYPE_SWEEAPER), job::returnJobMAXSkill(JOB_TYPE_SWEEAPER), job_data[playerid][playerJobTimes][JOB_TYPE_SWEEAPER]);
	
		Dialog_Show(playerid, DOALOG_SKILLS, DIALOG_STYLE_MSGBOX, "Skills", gString, "Ok", "");
	}
	return 1;
}
*/
YCMD:work(playerid, params[], help)
{
	if(!job_data[playerid][playerJob] || job_data[playerid][playerJob] == JOB_TYPE_DETECTIVE || job_data[playerid][playerJob] == JOB_TYPE_DRUGS || job_data[playerid][playerJob] == JOB_TYPE_ARMS || job_data[playerid][playerJob] == JOB_TYPE_FISHER)
		return SCM(playerid, -1, "Nu ai un job sau jobul detinut de tine nu beneficiaza de aceasta comanda!");

	if(GetPVarInt(playerid, "delay_work") > gettime())
		return SCMF(playerid, COLOR_GREY, "Vei putea folosi aceasta comanda peste %d secunde.", GetPVarInt(playerid, "delay_work") - gettime());

	if(s_PlayerInfo[playerid][pSCP])
		return SCM(playerid, COLOR_GREY, "Nu poti folosi aceasta comanda cat timp ai un checkpoint activ!");

	if(job_data[playerid][jobDuty] != JOB_TYPE_NONE)
		return 1;

	new
		jobId = job_data[playerid][playerJob];

	if(!IsPlayerInRangeOfPoint(playerid, 2.0, jobWorkLocations[jobId][0], jobWorkLocations[jobId][1], jobWorkLocations[jobId][2]))
	{
		SetPlayerCheckpoint(playerid, jobWorkLocations[jobId][0], jobWorkLocations[jobId][1], jobWorkLocations[jobId][2], 5.0);
		s_PlayerInfo[playerid][pSCP] = 1;

		return SCM(playerid, -1, "{909CE7}(Job):{FFFFFF} Nu esti in locatia potrivita! Ti-a fost setat un checkpoint!");
	}
	#if !defined SV_TESTE
		SetPVarInt(playerid, "delay_work", gettime() + 50);
	#endif

	return WhenPlayerStartWorking(playerid);
}

YCMD:getjob(playerid, params[], help)
{
	if(job_data[playerid][playerJob])
		return SCM(playerid, -1, "You already have a Job, use /quitjob first.");

	for(new i = 1; i < SERVER_JOBS; ++i)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.0, jobPositions[i][0], jobPositions[i][1], jobPositions[i][2]))
		{
			job_data[playerid][playerJob] = i;

			SCMF(playerid, COLOR_LIGHTBLUE, "Jobul tau este acum %s.", job::returnJobName(i));
			SCMF(playerid, COLOR_LIGHTBLUE, "Pentru a incepe lucrul foloseste comanda %s.", job::getCommandName(i));
			break;
		}
	}
	mysql_format(SQL, gString, sizeof gString, "update `users` set `Job` = '%d' where `id` = '%d';", job_data[playerid][playerJob], PlayerInfo[playerid][pSQLID]);
	mysql_tquery(SQL, gString, "", "");
	return 1;
}

YCMD:quitjob(playerid, params[], help)
{
	if(!job_data[playerid][playerJob])
		return SCM(playerid, COLOR_WHITE, "You don't have a job.");

	if(IsPlayerInAnyVehicle(playerid))
		return SCM(playerid, COLOR_GREY, "You can't use this while you are in an vehicle!");

	if(HavePlayerCheckpoint(playerid))
		SetInvalidCheckpoint(playerid);

	stop_job_work(playerid);

	mysql_format(SQL, gString, sizeof gString, "update `users` set `Job` = '0' where `id` = '%d';", PlayerInfo[playerid][pSQLID]);
	mysql_tquery(SQL, gString, "", "");

	job_data[playerid][playerJob] = 0;

	return SCM(playerid, COLOR_GREY, "You have quit your job!");
}

#include </systems/jobs/job_drugs.inc>
#include </systems/jobs/job_pizza.inc>
#include </systems/jobs/job_bus.inc>
#include </systems/jobs/job_arms.inc>
#include </systems/jobs/job_garbage.inc>
#include </systems/jobs/job_fisher.inc>
#include </systems/jobs/job_trucker.inc>

function stop_job_work(playerid)
{
	if(job_data[playerid][jobDuty] == JOB_TYPE_NONE)
		return 1;

	if(s_PlayerInfo[playerid][pSCP])
		s_PlayerInfo[playerid][pSCP] = 0, DisablePlayerCheckpoint(playerid), DisablePlayerRaceCheckpoint(playerid);

	if(IsValidVehicle(job_data[playerid][jobVehicle]))
	{
		jobLeftTime[playerid] = -1;
		DestroyVehicle(job_data[playerid][jobVehicle]);
		job_data[playerid][jobVehicle] = INVALID_VEHICLE_ID;
	}

	if(Iter_Contains(jobPlayers<job_data[playerid][playerJob]>, playerid))
		Iter_Remove(jobPlayers<job_data[playerid][playerJob]>, playerid);

    if(IsPlayerAttachedObjectSlotUsed(playerid, JOB_INDEX))
        RemovePlayerAttachedObject(playerid, JOB_INDEX);
    
    if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_NONE)
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

	cancel_drugs_work(playerid);
	cancel_pizza_work(playerid);
	cancel_bus_work(playerid);
	cancel_arms_work(playerid);
	cancel_garbage_work(playerid);
	cancel_fish_work(playerid);
	cancel_truck_work(playerid);

	job_data[playerid][jobDuty] = JOB_TYPE_NONE;
	return 1;
}

function WhenPlayerStartWorking(playerid)
{
	switch(job_data[playerid][playerJob])
	{
		case JOB_TYPE_NONE: { }
		case JOB_TYPE_DETECTIVE: { }
		case JOB_TYPE_DRUGS: { }
		case JOB_TYPE_PIZZA: start_pizza_work(playerid);
		case JOB_TYPE_BUS: start_bus_work(playerid);
		case JOB_TYPE_ARMS: { }
		case JOB_TYPE_GARBAGE: start_garbage_work(playerid);
		case JOB_TYPE_FISHER: { }
		case JOB_TYPE_TRUCKER: start_trucker_work(playerid);
	}
	Iter_Add(jobPlayers<job_data[playerid][playerJob]>, playerid);

	job_data[playerid][jobDuty] = job_data[playerid][playerJob];
	return 1;
}
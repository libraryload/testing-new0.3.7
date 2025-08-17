#include <YSI_Coding\y_hooks>
new examcar[MAX_PLAYERS], TakingLesson[MAX_PLAYERS];
new PlayerText:DMVcheck[MAX_PLAYERS], PlayerText:DMVexam[MAX_PLAYERS];
// OnPlayerEnterRaceCheckpoint
hook OnPlayerDisconnect(playerid, reason) {
	if(TakingLesson[playerid] == 1 || examcar[playerid] != -1)
	{
		PlayerTextDrawHide(playerid, DMVexam[playerid]); PlayerTextDrawHide(playerid, DMVcheck[playerid]);
		DestroyVehicle(examcar[playerid]); DisableRemoteVehicleCollisions(playerid, 0);
		examcar[playerid] = -1; TakingLesson[playerid] = 0; DisablePlayerRaceCheckpoint(playerid);
	}
	return 1;
}
hook OnPlayerExitVehicle(playerid, vehicleid)
{
    StopAudioStreamForPlayer(playerid);
    if(TakingLesson[playerid] == 1 || IsPlayerInVehicle(playerid, examcar[playerid]))
    {
        PlayerTextDrawHide(playerid, DMVexam[playerid]);
        PlayerTextDrawHide(playerid, DMVcheck[playerid]);
        TakingLesson[playerid] = 0;
        DisablePlayerRaceCheckpoint(playerid);
        DestroyVehicle(examcar[playerid]);
        DisableRemoteVehicleCollisions(playerid, 0);
        examcar[playerid] = -1;
        SCM(playerid, COLOR_WHITE, "Ai picat examenul pentru ca ai coborat din vehicul.");
    }
    return 1; }

YCMD:exam(playerid, params[], help) {
	if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_WHITE, "You can't use this command when you are in a car.");
    if(PlayerToPoint(5.0, playerid, 1219.3429,-1812.7673,16.5938))
    {
		new string[144];
    	if(PlayerInfo[playerid][pCarLic] == 0)
     	{
			if(PlayerInfo[playerid][pCarLicSuspend] > 0)
			{
				format(string,sizeof(string),"Your driving license was suspended recently. You can take the exam after %d hours.",PlayerInfo[playerid][pCarLicSuspend]);
				SendClientMessage(playerid, COLOR_WHITE, string);
				return 1;
			}
   			DisablePlayerRaceCheckpoint(playerid);
  			DisablePlayerCheckpoint(playerid);
      		if(TakingLesson[playerid] == 0)
        	{
				ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
        		ClearAnimations(playerid); 
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		    	TakingLesson[playerid] = 1;
       			examcar[playerid] = AddStaticVehicle(560, 1213.4567,-1828.3865,13.1352,179.1712, -1, -1);
       			SetVehicleVirtualWorld(examcar[playerid], GetPlayerVirtualWorld(playerid));
				PutPlayerInVehicleEx(playerid, examcar[playerid], 0);
				DisableRemoteVehicleCollisions(playerid, 1);
				SS(playerid, COLOR_WHITE, "Examenul practic a inceput. Mergi la checkpoint.", "The practical exam has begun. Go to the checkpoint.");
				SS(playerid, COLOR_WHITE, "Scrie /engine sau apasa tasta 2 pentru a porni motorul masinii.", "Type /engine or press key 2 to start the engine.");
			    s_PlayerInfo[playerid][pSCP] = 100;
			    PlayerTextDrawShow(playerid, DMVexam[playerid]);
				format(string, sizeof(string), "~w~CHECKPOINTS: ~r~0~w~/~r~10");
				PlayerTextDrawSetString(playerid, DMVcheck[playerid], string);
				PlayerTextDrawShow(playerid, DMVcheck[playerid]);
				SetPlayerRaceCheckpoint(playerid, 0, 1195.6389,-1852.1279,13.1234, 1135.4073,-1851.3762,13.1100, 4.0);
			}
   			else return SendClientMessage(playerid, COLOR_WHITE, "You already have an exam.");
      	}
       	else return SendClientMessage(playerid, COLOR_WHITE, "You already have a driver license.");
    }
   	else return SendClientMessage(playerid, COLOR_WHITE, "You are not at the DMV.");
	return 1; }

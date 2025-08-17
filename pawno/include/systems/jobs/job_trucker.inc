#include <YSI_Coding\y_hooks>

#define CP_TRUCKER (CP_JOBS_BEGIN) + JOB_TYPE_TRUCKER

#define TOTAL_ROUTES (15)

enum e_truck {
	truckSelectedRoute, truckTrailer
}

new trucker_data[MAX_PLAYERS][e_truck];

new Float: trucker_routes[][] =
{
	{0.0, 0.0, 0.0}, // ruta 0
	{1359.6993, 476.1964, 20.8873}, // ruta 1
	{587.0830, 1204.7422, 12.4163}, // ruta 2
	{-861.3798, 1559.3412, 24.7372}, // ruta 3
	{-1018.9788, -662.1734, 32.4966}, // ruta 4
	{1364.0338, 1079.2935, 11.3182}, // ruta 5
	{-422.4915, -1727.6918, 9.2781}, // ruta 6
	{1691.2383, 723.0962, 11.3759}, // ruta 7
	{374.0982, 2540.0125, 17.0444}, // ruta 8
	{2851.9336, 916.6110, 10.7500}, // ruta 9
	{-1298.5750, 2703.1086, 50.5617}, // ruta 10
	{1617.0159, 2329.4446, 11.4968}, // ruta 11
	{-219.1298, 2737.5425, 63.3700}, // ruta 12
	{-2099.9321, -2242.8779, 31.3065}, // ruta 13
	{2251.8481, 2753.2100, 11.5664}, // ruta 14
	{2522.1228, -2484.3025, 14.3169} // ruta 15
};	

getRouteName(routeId)
{
	new
		routeString[48];

	switch(routeId)
	{
		case 1: routeString = "Abandoned stations";
		case 2: routeString = "Desert factory";
		case 3: routeString = "Smoked beef grill";
		case 4: routeString = "Chemicals factory";
		case 5: routeString = "Firearm parts";
		case 6: routeString = "Farmer deliver";
		case 7: routeString = "Cargo station";
		case 8: routeString = "Airplane parts";
		case 9: routeString = "Whitney post office";
		case 10: routeString = "Gas station";
		case 11: routeString = "Big depot";
		case 12: routeString = "Pecker's feed & seed";
		case 13: routeString = "Old deposit";
		case 14: routeString = "North abattoir";
		case 15: routeString = "Industrial deposit";
	}
	return routeString;
}

reset_truck_vars(playerid)
{
	trucker_data[playerid][truckSelectedRoute] = 0;
	trucker_data[playerid][truckTrailer] = INVALID_VEHICLE_ID;
}

start_trucker_work(playerid)
{
	SCM(playerid, -1, "{909CE7}(Job):{FFFFFF} Alege din dialogul de mai jos marfa pe care doresti sa o transporti.");

	gString = "Name\tDeliver Zone\tDistance\n";

	new routes=1;
	while(routes <= TOTAL_ROUTES)
	{
		format(gString, sizeof gString, "%s\t%s\t%s\t%.2f km\n", gString, getRouteName(routes), GetMapZoneName(trucker_routes[routes][0], trucker_routes[routes][1], trucker_routes[routes][2]), GetPlayerDistanceFromPoint(playerid, trucker_routes[routes][0], trucker_routes[routes][1], trucker_routes[routes][2]) / 1000);
		++routes;
	}
	Dialog_Show(playerid, DIALOG_SELECTROUTE, DIALOG_STYLE_TABLIST_HEADERS, "Select route:", gString, "Select", "Close");
	
	new
		Float: vPos[4], vehicle, job_skill = job::returnPlayerSkill(playerid, JOB_TYPE_TRUCKER);
	
	vehicle = (job_skill < 2 ? (403) : job_skill > 2 && job_skill < 4 ? (514) : (515));

	GetPlayerPos(playerid, vPos[0], vPos[1], vPos[2]);
	GetPlayerFacingAngle(playerid, vPos[3]);

	job::createJobVehicle(playerid, vehicle, vPos[0], vPos[1], vPos[2], vPos[3], 0);
	return 1;
}

cancel_truck_work(playerid)
{
	if(job_data[playerid][jobDuty] != JOB_TYPE_TRUCKER)
		return 1;

	reset_truck_vars(playerid);

	if(IsValidVehicle(trucker_data[playerid][truckTrailer]))
	{
		DestroyVehicle(trucker_data[playerid][truckTrailer]);
		trucker_data[playerid][truckTrailer] = INVALID_VEHICLE_ID;
	}
	return 1;
}

Dialog:DIALOG_SELECTROUTE(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SCM(playerid, -1, "{909CE7}(Job):{FFFFFF} Ai pierdut cursa curenta deoarece ai inchis dialogul.");
		stop_job_work(playerid);
	}
	return 1;
}
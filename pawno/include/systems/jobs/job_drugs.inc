#include <YSI_Coding\y_hooks>

#define CP_DRUGS (CP_JOBS_BEGIN) + JOB_TYPE_DRUGS

enum {
    DRUGS_OFFER_PLAYER, DRUGS_OFFER_PRICE, DRUGS_OFFER_AMOUNT
}

new
	PlayerText: drugs_td[MAX_PLAYERS], drugs_object[MAX_PLAYERS], drug_timer[MAX_PLAYERS], drugSell[MAX_PLAYERS][3];

hook OnGameModeInit()
{
	CreateDynamicActor(29, -1120.0229, -1621.1617, 76.3672, 265.9845, 1, 100.0, 0, 0, -1); // actor job

	//mapping
    CreateDynamicObject(956, 662.419983, -552.159973, 15.710000, 0.000000, 0.000000, 180.000000);
    CreateDynamicObject(3242, -1113.094116, -1656.713013, 77.193802, 0.000000, 0.000000, 91.000000);
    CreateDynamicObject(1348, -1098.521240, -1627.182129, 76.129501, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(1348, -1100.272949, -1627.182129, 76.129501, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(1348, -1102.000732, -1627.182129, 76.129501, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(1348, -1103.803345, -1627.182129, 76.129501, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(9093, -1097.155762, -1622.884277, 77.090698, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(1348, -1105.574219, -1627.182129, 76.129501, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(9093, -1097.145752, -1622.884277, 79.130699, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(988, -1097.220215, -1620.462036, 76.413200, 0.000000, 0.000000, 89.099998);
    CreateDynamicObject(929, -1108.567261, -1626.933960, 76.286499, 0.000000, 0.000000, 89.499901);
    CreateDynamicObject(929, -1112.929810, -1626.944214, 76.286499, 0.000000, 0.000000, -89.999901);
    CreateDynamicObject(1575, -1098.049805, -1614.511841, 75.431900, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(1580, -1098.074951, -1614.562256, 75.738503, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(2463, -1098.741333, -1614.410400, 75.351303, 0.000000, 0.000000, 0.099800);
    CreateDynamicObject(1575, -1098.900635, -1614.511841, 75.431900, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(1575, -1098.069824, -1614.421753, 76.101799, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(1580, -1098.885742, -1614.562256, 75.738503, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(1580, -1098.074951, -1614.562256, 76.448502, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(1575, -1098.920654, -1614.421753, 76.101799, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(1575, -1098.069824, -1614.421753, 76.811897, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(1580, -1098.874146, -1614.562256, 76.448502, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(1580, -1098.063354, -1614.562256, 77.178497, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(1575, -1098.880615, -1614.421753, 76.801903, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(1580, -1098.874146, -1614.562256, 77.178497, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(3632, -1101.215210, -1614.725342, 75.822701, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(3632, -1101.897949, -1614.723022, 75.822701, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(3632, -1102.567139, -1614.746460, 75.822701, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(925, -1104.636475, -1615.261108, 76.378601, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(3577, -1118.899414, -1625.733643, 76.080299, 0.000000, 0.000000, 0.000000);
    CreateDynamicObject(2345, -1107.707153, -1614.716553, 76.821297, 9.900000, -0.100000, 2.800000);
    CreateDynamicObject(2926, -1118.633301, -1622.481201, 76.129303, 0.000000, 0.000000, -89.799896);
    CreateDynamicObject(2060, -1118.667358, -1622.517334, 76.233498, 0.000000, -0.299900, 91.399803);
    CreateDynamicObject(18648, -1107.402954, -1614.669556, 78.057800, 0.000000, 0.000000, 90.900002);
    CreateDynamicObject(19087, -1108.798706, -1614.652832, 76.946999, -0.299900, -89.800003, -0.100000);
    CreateDynamicObject(2357, -1118.682251, -1621.217529, 75.754097, 0.000000, 0.000000, 89.699898);
    CreateDynamicObject(18648, -1109.394653, -1614.700317, 78.057800, 0.000000, 0.000000, 90.900002);
    CreateDynamicObject(2345, -1110.804565, -1614.660400, 76.851997, 9.900000, -0.100000, 0.700000);
    CreateDynamicObject(19087, -1111.219727, -1614.650513, 76.955399, -0.299900, -89.800003, -0.100000);
    CreateDynamicObject(2295, -1118.721069, -1619.905762, 75.946404, -2.600100, 2.400000, -3.600100);
    CreateDynamicObject(2926, -1118.662109, -1619.832764, 76.149300, 0.000000, 0.000000, -89.999901);
    CreateDynamicObject(18648, -1111.356445, -1614.731567, 78.057800, 0.000000, 0.000000, 90.900002);
    CreateDynamicObject(19087, -1113.641724, -1614.648560, 76.963799, -0.299900, -89.800003, -0.100000);
    CreateDynamicObject(2345, -1113.819824, -1614.683960, 76.837799, 9.900000, -0.100000, 0.000000);
    CreateDynamicObject(18648, -1113.438354, -1614.723267, 78.055496, -0.099900, 3.300000, 89.699997);
    CreateDynamicObject(19087, -1116.034058, -1614.646729, 76.972099, -0.299900, -89.800003, -0.100000);
    CreateDynamicObject(18648, -1115.420166, -1614.712769, 78.052002, -0.099900, 3.300000, 89.699997);
    CreateDynamicObject(2345, -1116.697754, -1614.697021, 76.864998, 9.900000, -0.100000, 2.800000);
    CreateDynamicObject(18648, -1117.411865, -1614.702026, 78.048500, -0.099900, 3.300000, 89.699997);
    CreateDynamicObject(19087, -1118.446411, -1614.645264, 76.980598, -0.299900, -89.800003, -0.100000);
    CreateDynamicObject(2345, -1119.454468, -1614.831665, 76.860100, 9.900000, -0.100000, 2.800000);
    CreateDynamicObject(18648, -1119.362305, -1614.692749, 78.045097, -0.099900, 3.300000, 89.699997);
    CreateDynamicObject(18648, -1119.892822, -1614.692261, 78.044296, -0.099900, 3.300000, 89.699997);
    CreateDynamicObject(19087, -1120.887329, -1614.641235, 76.988998, -0.299900, -89.800003, -0.100000);
    CreateDynamicObject(905, -1101.036743, -1549.046265, 76.801903, 0.000000, -185.000000, -62.000000);
    CreateDynamicObject(18795, -453.482086, -1272.580811, 48.633301, -1.700000, -15.000000, 138.679901);
    CreateDynamicObject(18788, -475.302887, -1239.981934, 55.536201, 2.380000, -5.000000, 124.039803);
    CreateDynamicObject(3330, -480.272034, -1231.831299, 44.872669, 0.000000, 0.000000, 29.999929);
    CreateDynamicObject(3330, -438.002899, -1285.715454, 31.589800, 5.000000, 0.000000, 44.759899);
    CreateDynamicObject(18795, -497.288208, -1206.908081, 57.256901, 2.380000, 0.000000, 123.419998);
    CreateDynamicObject(18794, -423.964813, -1298.094360, 38.283501, -1.790000, 0.000000, 138.679901);
    CreateDynamicObject(3330, -507.715973, -1173.923218, 44.872669, 0.000000, 0.000000, 13.259920);
    CreateDynamicObject(3330, -402.681061, -1317.518677, 27.211590, 0.000000, 0.000000, 48.719940);
    CreateDynamicObject(18795, -509.670013, -1168.906860, 57.044300, 2.380000, 0.000000, 107.519997);
    CreateDynamicObject(18788, -394.012939, -1324.414673, 38.273602, -1.780000, 0.000000, 138.679901);
    CreateDynamicObject(3330, -367.157867, -1348.287476, 26.748171, 0.000000, 0.000000, 56.879929);
    CreateDynamicObject(18788, -364.146393, -1350.680420, 38.273602, -1.780000, 0.000000, 138.679901);
    CreateDynamicObject(18795, -511.991913, -1129.452637, 56.824299, 2.380000, 0.000000, 94.080002);
    CreateDynamicObject(3330, -334.209412, -1377.765381, 23.319790, 8.000000, 0.000000, 52.559898);
    CreateDynamicObject(18788, -334.416687, -1376.676147, 34.826401, -1.780000, -10.000000, 138.679901);
    CreateDynamicObject(18794, -304.616638, -1402.500122, 26.151171, -1.790000, 0.000000, 138.679901);
    CreateDynamicObject(3330, -503.867310, -1093.456055, 44.872669, 0.000000, 0.000000, -13.020080);
    CreateDynamicObject(18795, -504.490601, -1089.988892, 56.604301, 2.380000, 0.000000, 79.259903);
    CreateDynamicObject(3330, -290.439758, -1415.346802, 15.040200, 0.000000, 0.000000, 52.559910);
    CreateDynamicObject(18788, -274.531189, -1428.626953, 26.134600, 1.790000, 0.000000, -40.619999);
    CreateDynamicObject(18788, -244.279694, -1454.565674, 26.134600, 1.790000, 0.000000, -40.619999);
    CreateDynamicObject(3330, -241.097519, -1457.535889, 15.040200, 0.000000, 0.000000, 52.559910);
    CreateDynamicObject(18788, -487.512604, -1053.725342, 56.405102, 2.300000, 0.000000, 65.419899);
    CreateDynamicObject(18788, -213.929993, -1480.587891, 26.134600, 1.790000, 0.000000, -40.619999);
    CreateDynamicObject(3330, -476.051727, -1028.095093, 44.872669, 0.000000, 0.000000, -21.900070);
    CreateDynamicObject(3330, -198.398270, -1494.408081, 15.040200, 0.000000, 0.000000, 52.559910);
    CreateDynamicObject(18788, -470.905304, -1017.412781, 56.405102, 2.300000, 0.000000, 65.419899);
    CreateDynamicObject(18788, -183.748047, -1506.461304, 26.134600, 1.790000, 0.000000, -40.620022);
    CreateDynamicObject(3330, -162.269135, -1527.171387, 15.040200, 0.000000, 0.000000, 42.959900);
    CreateDynamicObject(18795, -156.042404, -1533.251343, 26.139400, 1.790000, 0.000000, -48.000000);
    CreateDynamicObject(3330, -142.502197, -1559.285034, 14.606200, 0.000000, 0.000000, 28.619900);
    CreateDynamicObject(18788, -138.161102, -1569.003052, 24.940300, 1.790000, 3.000000, -64.080002);
    CreateDynamicObject(18788, -454.374176, -981.306396, 56.405102, 2.300000, 0.000000, 65.419899);
    CreateDynamicObject(3330, -449.988678, -973.968628, 45.076950, 0.000000, 0.000000, 20.699869);
    CreateDynamicObject(3330, -123.318901, -1600.193115, 9.056270, 10.000000, 0.000000, 27.419901);
    CreateDynamicObject(18788, -120.830704, -1604.325684, 19.773899, 1.790000, 12.000000, -64.080002);
    CreateDynamicObject(18794, -103.506401, -1639.578247, 10.435800, -1.800000, 0.000000, 115.620003);
    CreateDynamicObject(3330, -101.218803, -1644.685791, 0.631800, 0.000000, 0.000000, 25.379910);
    CreateDynamicObject(18795, -437.658813, -944.925903, 56.197899, -2.300000, 0.000000, -99.900002);
    CreateDynamicObject(3330, -74.019180, -1687.761475, -0.589100, 0.000000, 0.000000, 44.219952);
    CreateDynamicObject(18791, -72.136002, -1689.918579, 10.745590, 1.900000, 0.000000, -43.680000);
    CreateDynamicObject(18795, -1328.362793, -727.251465, 56.418369, 1.200000, 1.800000, -520.499329);
    CreateDynamicObject(3330, -1336.791260, -727.449951, 45.521980, 0.000000, 0.000000, 103.199951);
    CreateDynamicObject(18795, -1290.651978, -714.578552, 56.498890, 1.200000, -1.800000, -507.359406);
    CreateDynamicObject(3330, -1290.584106, -713.347473, 46.924370, 0.000000, 0.000000, 128.339935);
    CreateDynamicObject(905, -981.438599, -1973.728760, 75.666496, 0.000000, 0.000000, 0.000000);

	return Y_HOOKS_CONTINUE_RETURN_1;
}

function DrugEffectGone(playerid)
{
    if(!GetPVarInt(playerid, "using_drugs"))
        return 1;

    TogglePlayerControllable(playerid, 1);

    DeletePVar(playerid, "using_drugs");
    SetPVarInt(playerid, "delay_drugs", gettime() + 300);

    ClearAnimations(playerid);
    KillTimer(drug_timer[playerid]);
    SetPlayerDrunkLevel(playerid, 0);
    SetPlayerHealth(playerid, 100);

    return SCM(playerid, -1, "Drogurile si-au facut efectul.");
}

reset_drugs_vars(playerid)
{
    drugSell[playerid][DRUGS_OFFER_PLAYER] = INVALID_PLAYER_ID;
    drugSell[playerid][DRUGS_OFFER_AMOUNT] = 0;
    drugSell[playerid][DRUGS_OFFER_PRICE] = 0;
}

create_drugs_td(playerid)
{
	drugs_td[playerid] = CreatePlayerTextDraw(playerid, 316.100250, 415.531036, "drugs dealer~n~status: ~r~planting seeds");
	PlayerTextDrawLetterSize(playerid, drugs_td[playerid], 0.094333, 0.695778);
	PlayerTextDrawTextSize(playerid, drugs_td[playerid], 0.000000, 132.000000);
	PlayerTextDrawAlignment(playerid, drugs_td[playerid], 2);
	PlayerTextDrawColor(playerid, drugs_td[playerid], 0xFFFFFFFF);
	PlayerTextDrawUseBox(playerid, drugs_td[playerid], 1);
	PlayerTextDrawBoxColor(playerid, drugs_td[playerid], 0x000000FF);
	PlayerTextDrawSetShadow(playerid, drugs_td[playerid], 0);
	PlayerTextDrawSetOutline(playerid, drugs_td[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, drugs_td[playerid], 0x000000FF);
	PlayerTextDrawFont(playerid, drugs_td[playerid], 2);
	PlayerTextDrawSetProportional(playerid, drugs_td[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, drugs_td[playerid], 0);

	return PlayerTextDrawShow(playerid, drugs_td[playerid]);
}

destroy_drugs_td(playerid)
{
	return (drugs_td[playerid] != PlayerText: INVALID_TEXT_DRAW) ? (PlayerTextDrawDestroy(playerid, drugs_td[playerid])) : (0);
}

cancel_drugs_work(playerid)
{
	if(job_data[playerid][jobDuty] != JOB_TYPE_DRUGS)
		return 1;

    destroy_drugs_td(playerid);
    DeletePVar(playerid, "drugs_step");
    reset_drugs_vars(playerid);

    if(IsValidDynamicObject(drugs_object[playerid]))
        DestroyDynamicObject(drugs_object[playerid]);

    return 1;
}

YCMD:usedrugs(playerid, params[], help)
{
    if(GetPVarInt(playerid, "using_drugs") == 1)
        return SCM(playerid, -1, "You are already taking drugs.");

    if(!PlayerInfo[playerid][pDrugs])
        return SCM(playerid, -1, "You don't have drugs.");

    if(GetPVarInt(playerid, "delay_drugs") > gettime())
        return SCMF(playerid, -1, "Poti folosi droguri peste %d secunde.", GetPVarInt(playerid, "delay_drugs")-gettime());

    SCM(playerid, -1, "Stai nemiscat 10 de secunde pentru ca drogurile sa-si faca efectul.");

    sendNearbyMessage(playerid, COLOR_PURPLE, "* %s took some drugs out of his pocket.", GetName(playerid));

    PlayerInfo[playerid][pDrugs] -= 1;
    SetPVarInt(playerid, "using_drugs", 1);

    TogglePlayerControllable(playerid, 0);

    ApplyAnimation(playerid, "SMOKING", "M_smk_in", 4.0, 0, 0, 0, 0, 0);
    drug_timer[playerid] = SetTimerEx("DrugEffectGone", 10000, false, "d", playerid);

    DailyQuestCheck(playerid, QUEST_TYPE_DRUGS, 1);

    mysql_format(SQL, gString, sizeof gString, "update `users` set `Drugs` = '%d' where `id` = '%d';", PlayerInfo[playerid][pDrugs], PlayerInfo[playerid][pSQLID]);
    return mysql_tquery(SQL, gString, "", "");
}

YCMD:getseeds(playerid, params[], help)
{
	if(job_data[playerid][playerJob] != JOB_TYPE_DRUGS)
		return SCM(playerid, -1, "Invalid job! You are not a Drugs Dealer.");

	if(job_data[playerid][jobDuty] == JOB_TYPE_DRUGS)
		return SCM(playerid, -1, "Nu poti folosi aceasta comanda acum deoarece te afli deja in procesul de a crea un drog.");

	if(!IsPlayerInRangeOfPoint(playerid, 2.0, jobWorkLocations[JOB_TYPE_DRUGS][0]+2.5, jobWorkLocations[JOB_TYPE_DRUGS][1], jobWorkLocations[JOB_TYPE_DRUGS][2]))
	{
		SetPlayerCheckpoint(playerid, jobWorkLocations[JOB_TYPE_DRUGS][0]+2.5, jobWorkLocations[JOB_TYPE_DRUGS][1], jobWorkLocations[JOB_TYPE_DRUGS][2], 2.0);
		s_PlayerInfo[playerid][pSCP] = 1;
		return SCM(playerid, -1, "You are not in right place to get seeds.");
	}

	SCM(playerid, -1, "{909CE7}(Job):{FFFFFF} Go to the marked location on your map to plant your seeds.");

    SetPVarInt(playerid, "drugs_step", 1);
    WhenPlayerStartWorking(playerid);
    create_drugs_td(playerid);

    switch(random(3))
    {
        case 0: SetPlayerCheckpoint(playerid, -1068.9921, -1632.8057, 76.3747, 2.0);
        case 1: SetPlayerCheckpoint(playerid, -1078.4031, -1667.0356, 76.4110, 2.0);
        case 2: SetPlayerCheckpoint(playerid, -1054.3735, -1677.7054, 76.9012, 2.0);
    }

	s_PlayerInfo[playerid][pSCP] = CP_DRUGS;
    return 1;
}

YCMD:selldrugs(playerid, params[], help)
{
    if(job_data[playerid][playerJob] != JOB_TYPE_DRUGS)
        return SCM(playerid, -1, "You are not a Drugs Dealer.");

    new
        targetid, iDrugs, iPrice;

    if(sscanf(params, "uii", targetid, iDrugs, iPrice))
        return sendSyntax(playerid, "/selldrugs <Name/Playerid> <Drugs> <Price>");

    if(!IsPlayerConnected(targetid))
        return SCM(playerid, COLOR_GREY, "Player not connected.");

    if(iPrice < 1 || iPrice > 150000)
        return SCM(playerid, -1, "Price not lower then 1$, or above 150,000$.");

    if(playerid == targetid)
        return SCM(playerid, -1, "You can not sell yourself drugs.");

    if(!IsPlayerInRangeOfPlayer(playerid, targetid, 5.0))
        return SCM(playerid, -1, "This player is not near you.");
    
    if(iDrugs < 1 || iDrugs > 50)
        return SCM(playerid, -1, "Grams not lower then 1, or above 50.");
 
    if(iDrugs > PlayerInfo[playerid][pDrugs])
        return SCM(playerid, -1, "You dont have that much Drugs with you.");

    SCMF(playerid, -1, "{B8FFDB}* You offerd %s to buy %d gram of drugs for $%s.", GetName(targetid), iDrugs, FormatNumber(iPrice));
    SCMF(targetid, -1, "{B8FFDB}* Drug Dealer %s wants to sell you %d gram for $%s, (type /accept drugs %d) to buy.", GetName(playerid), iDrugs, FormatNumber(iPrice), playerid);

    drugSell[targetid][DRUGS_OFFER_PLAYER] = playerid;
    drugSell[targetid][DRUGS_OFFER_AMOUNT] = iDrugs;
    drugSell[targetid][DRUGS_OFFER_PRICE] = iPrice;

    return 1;
}

accept_drugs(playerid, targetid)
{
    if(drugSell[playerid][DRUGS_OFFER_PLAYER] == INVALID_PLAYER_ID)
        return SCM(playerid, -1, "No-one offerd you any drugs.");

    if(drugSell[playerid][DRUGS_OFFER_PLAYER] != targetid)
        return SCM(playerid, -1, "This player has not offered you drugs.");
    
    if(!IsPlayerInRangeOfPlayer(playerid, targetid, 5.0))
        return SCM(playerid, -1, "This player is not near you.");

    if(GetPlayerCash(playerid) < drugSell[playerid][DRUGS_OFFER_PRICE])
        return SCM(playerid,-1,"You can't afford those drugs.");

    PlayerInfo[playerid][pDrugs] += drugSell[playerid][DRUGS_OFFER_AMOUNT];
    PlayerInfo[targetid][pDrugs] -= drugSell[playerid][DRUGS_OFFER_AMOUNT];

    GivePlayerCash(playerid, -drugSell[playerid][DRUGS_OFFER_PRICE]);
    GivePlayerCash(targetid, drugSell[playerid][DRUGS_OFFER_PRICE]);

    SCMF(playerid, -1, "{B8FFDB}* You bought %d gram for $%s from Drug Dealer %s.", drugSell[playerid][DRUGS_OFFER_AMOUNT], FormatNumber(drugSell[playerid][DRUGS_OFFER_PRICE]), GetName(targetid));
    SCMF(targetid, -1, "{B8FFDB}* %s has bought your %d gram, the $%s was added to your PayCheck.", GetName(playerid), drugSell[playerid][DRUGS_OFFER_AMOUNT], FormatNumber(drugSell[playerid][DRUGS_OFFER_PRICE]));
     
    mysql_format(SQL, gString, sizeof gString, "update `users` set `Drugs` = '%d' where `id` = '%d';", PlayerInfo[playerid][pDrugs], PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString, "", "");

    mysql_format(SQL, gString, sizeof gString, "update `users` set `Drugs` = '%d' where `id` = '%d';", PlayerInfo[targetid][pDrugs], PlayerInfo[targetid][pSQLID]);
    mysql_tquery(SQL, gString, "", "");

    reset_drugs_vars(playerid);

    return 1;
}

Dialog:DIALOG_GETSEEDS(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

    SCM(playerid, -1, "{909CE7}(Job):{FFFFFF} Go to the marked location on your map to plant your seeds.");

	SetPVarInt(playerid, "drugs_step", 1);

	create_drugs_td(playerid);
	WhenPlayerStartWorking(playerid);

	switch(random(3))
	{
		case 0: SetPlayerCheckpoint(playerid, -1068.9921, -1632.8057, 76.3747, 2.0);
		case 1: SetPlayerCheckpoint(playerid, -1078.4031, -1667.0356, 76.4110, 2.0);
		case 2: SetPlayerCheckpoint(playerid, -1054.3735, -1677.7054, 76.9012, 2.0);
	}
	return s_PlayerInfo[playerid][pSCP] = CP_DRUGS;
}

function collect_seeds(playerid, step)
{
	if(step == 1)
	{
		SCM(playerid, -1, "{909CE7}(Job):{FFFFFF} Go to the checkpoint and dry these leaves to get good drugs to use. Drying process takes a few seconds.");

		PlayerTextDrawSetString(playerid, drugs_td[playerid], "drugs dealer~n~status: ~r~drying leaves");
		PlayerTextDrawShow(playerid, drugs_td[playerid]);

		TogglePlayerControllable(playerid, 1);
		SetPVarInt(playerid, "drugs_step", 2);

		SetPlayerCheckpoint(playerid, -1107.8488, -1615.2081, 76.3739, 1.0), s_PlayerInfo[playerid][pSCP] = CP_DRUGS;
		DestroyDynamicObject(drugs_object[playerid]);
	}
	else if(step == 2)
	{
		new
			final_drugs = 1 + random(6);

		SCMF(playerid, -1, "{909CE7}(Job):{FFFFFF} You received %d grams of drugs by following the process.", final_drugs);
		
		TogglePlayerControllable(playerid, 1);

        PlayerInfo[playerid][pDrugs] += final_drugs;
		job_data[playerid][jobDuty] = JOB_TYPE_NONE;
		job::updateJobSkill(playerid, JOB_TYPE_DRUGS);

		destroy_drugs_td(playerid);

        mysql_format(SQL, gString, sizeof gString, "update `users` set `Drugs` = '%d' where `id` = '%d';", PlayerInfo[playerid][pDrugs], PlayerInfo[playerid][pSQLID]);
        mysql_tquery(SQL, gString, "", "");
	}
	return 1;
}

hook OnPlayerEnterCheckpoint(playerid)
{
	if(s_PlayerInfo[playerid][pSCP] == CP_DRUGS && job_data[playerid][jobDuty] == JOB_TYPE_DRUGS)
	{
		if(GetPVarInt(playerid, "drugs_step") == 1)
		{
			DisablePlayerCheckpoint(playerid), s_PlayerInfo[playerid][pSCP] = 0;

			PlayerTextDrawSetString(playerid, drugs_td[playerid], "drugs dealer~n~status: ~r~growing up plant");
			PlayerTextDrawShow(playerid, drugs_td[playerid]);

			new Float: actualPos[3];
			GetPlayerPos(playerid, actualPos[0], actualPos[1], actualPos[2]);

			actualPos[2] = actualPos[2] - 2;

			drugs_object[playerid] = CreateDynamicObject(862, actualPos[0], actualPos[1], actualPos[2], 0.0, 0.0, 0.0, 0, 0, playerid);
			MoveDynamicObject(drugs_object[playerid], actualPos[0], actualPos[1], actualPos[2]+1, 0.1, 0.0, 0.0, 0.0);

			ClearAnimations(playerid);
			TogglePlayerControllable(playerid, 0);
			OnePlayAnim(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);

			return SetTimerEx("collect_seeds", 10000, false, "dd", playerid, 1);
		}
		else if(GetPVarInt(playerid, "drugs_step") == 2)
		{
			DisablePlayerCheckpoint(playerid), s_PlayerInfo[playerid][pSCP] = 0;
			
			TogglePlayerControllable(playerid, 0);

			return SetTimerEx("collect_seeds", 5000, false, "dd", playerid, 2);
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}
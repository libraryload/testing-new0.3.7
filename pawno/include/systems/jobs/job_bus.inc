#include <YSI_Coding\y_hooks>

#define CP_BUS (CP_JOBS_BEGIN) + JOB_TYPE_BUS
#define BUS_MONEY (1500)

new
    PlayerText: bus_td[MAX_PLAYERS][2];

new Float: bus_cps[][] = {
	{1693.2972, -2197.6602, 13.4714, 1941.3706, -2169.2083, 13.4851},
    {1941.3706, -2169.2083, 13.4851, 1964.6262, -1899.2827, 13.4838},
    {1964.6262, -1899.2827, 13.4838, 1921.6910, -1749.1346, 13.4828},
    {1921.6910, -1749.1346, 13.4828, 1819.4100, -1814.2385, 13.5056},
    {1819.4100, -1814.2385, 13.5056, 1692.2909, -1764.9092, 13.4875},
    {1692.2909, -1764.9092, 13.4875, 1395.2542, -1729.2012, 13.4901},
    {1395.2542, -1729.2012, 13.4901, 1315.4188, -1631.5197, 13.4827},
    {1315.4188, -1631.5197, 13.4827, 1325.5859, -1392.4742, 13.4741},
    {1325.5859, -1392.4742, 13.4741, 1209.0767, -1324.8274, 13.5002},
    {1209.0767, -1324.8274, 13.5002, 1082.8730, -1277.8145, 13.5019},
    {1082.8730, -1277.8145, 13.5019, 966.0933, -1218.3807, 16.8770},
    {966.0933, -1218.3807, 16.8770, 818.9665, -1137.8669, 23.8506},
    {818.9665, -1137.8669, 23.8506, 794.1818, -1301.3213, 13.4795},
    {794.1818, -1301.3213, 13.4795, 678.5087, -1392.8485, 13.5081},
    {678.5087, -1392.8485, 13.5081, 380.8662, -1492.7212, 32.2020},
    {380.8662, -1492.7212, 32.2020, 258.5574, -1537.6969, 32.3608},
    {258.5574, -1537.6969, 32.3608, 484.7990, -1357.7792, 17.9893},
    {484.7990, -1357.7792, 17.9893, 588.3983, -1232.8560, 17.8009},
    {588.3983, -1232.8560, 17.8009, 774.5882, -1058.5305, 24.5938},
    {774.5882, -1058.5305, 24.5938, 1209.5120, -948.5093, 42.8005},
    {1209.5120, -948.5093, 42.8005, 1566.5400, -997.7548, 45.7116},
    {1566.5400, -997.7548, 45.7116, 1709.9061, -733.8804, 50.0985},
    {1709.9061, -733.8804, 50.0985, 1658.8318, -43.4300, 36.4876},
    {1658.8318, -43.4300, 36.4876, 1772.3663, 581.9141, 23.7034},
    {1772.3663, 581.9141, 23.7034, 1841.4648, 829.6874, 9.9861},
    {1841.4648, 829.6874, 9.9861, 2187.5762, 806.9039, 7.2061},
    {2187.5762, 806.9039, 7.2061, 2290.9165, 841.0883, 13.9592},
    {2290.9165, 841.0883, 13.9592, 2350.4082, 1025.8792, 10.7723},
    {2350.4082, 1025.8792, 10.7723, 2570.7004, 1070.5811, 10.7773},
    {2570.7004, 1070.5811, 10.7773, 2613.5254, 1315.6500, 10.7696},
    {2613.5254, 1315.6500, 10.7696, 2476.1697, 1476.3761, 10.7715},
    {2476.1697, 1476.3761, 10.7715, 2401.2478, 1616.5609, 10.7727},
    {2401.2478, 1616.5609, 10.7727, 2291.8828, 1775.9521, 10.7812},
    {2291.8828, 1775.9521, 10.7812, 2154.7061, 1996.3882, 10.7744},
    {2154.7061, 1996.3882, 10.7744, 2228.1877, 2386.0630, 10.7777},
    {2228.1877, 2386.0630, 10.7777, 2086.0520, 2456.9954, 10.8048},
    {2086.0520, 2456.9954, 10.8048, 1948.1777, 2396.3440, 10.7688},
    {1948.1777, 2396.3440, 10.7688, 1922.7677, 2317.8069, 10.8393},
    {1922.7677, 2317.8069, 10.8393, 1922.8735, 2117.9375, 10.8652},
    {1922.8735, 2117.9375, 10.8652, 2093.9612, 2017.9711, 10.8407},
    {2093.9612, 2017.9711, 10.8407, 2039.7142, 1522.0779, 10.7595},
    {2039.7142, 1522.0779, 10.7595, 2040.6129, 1169.0469, 10.7807},
    {2040.6129, 1169.0469, 10.7807, 2038.9994, 878.8145, 7.1755},
    {2038.9994, 878.8145, 7.1755, 1755.5402, 619.8901, 21.3552},
    {1755.5402, 619.8901, 21.3552, 1619.3414, 186.8276, 33.5024},
    {1619.3414, 186.8276, 33.5024, 1659.4628, -329.5979, 40.4135},
    {1659.4628, -329.5979, 40.4135, 1688.2992, -728.0701, 49.8404},
    {1688.2992, -728.0701, 49.8404, 1412.3439, -937.3050, 35.6120},
    {1412.3439, -937.3050, 35.6120, 1432.5333, -1037.7094, 23.7933},
    {1432.5333, -1037.7094, 23.7933, 1574.0338, -1138.6904, 23.6757},
    {1574.0338, -1138.6904, 23.6757, 1711.5553, -1263.2328, 13.4910},
    {1711.5553, -1263.2328, 13.4910, 1590.8885, -1437.7626, 13.4817},
    {1590.8885, -1437.7626, 13.4817, 1428.2323, -1567.3893, 13.4529},
    {1428.2323, -1567.3893, 13.4529, 1446.8442, -1735.5527, 13.4789},
    {1446.8442, -1735.5527, 13.4789, 1580.1357, -1874.8420, 13.4791},
    {1580.1357, -1874.8420, 13.4791, 1818.1030, -1904.3914, 13.5025},
    {1818.1030, -1904.3914, 13.5025, 1958.2472, -1999.3572, 13.4949},
    {1958.2472, -1999.3572, 13.4949, 1936.2253, -2163.5068, 13.4765}
};

hook OnGameModeInit()
{
    //Statii autobuz
    CreateDynamicObject(1257, 1692.89929, -2200.77808, 13.64870,   0.00000, 0.00000, -90.12000);
    CreateDynamicObject(1257, 1941.19080, -2172.63159, 13.76920,   0.00000, 0.00000, -90.36000);
    CreateDynamicObject(1257, 1967.80859, -1900.26184, 13.77870,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1257, 1921.87402, -1746.02295, 13.76840,   0.00000, 0.00000, 90.06000);
    CreateDynamicObject(1257, 1815.46008, -1815.05981, 13.80990,   0.00000, 0.00000, -179.63989);
    CreateDynamicObject(1257, 1695.64038, -1766.75049, 13.78830,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1257, 1392.64221, -1726.04602, 13.65910,   0.00000, 0.00000, 89.46000);
    CreateDynamicObject(1257, 1318.69714, -1633.10010, 13.76780,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1257, 1325.55969, -1389.08057, 13.76010,   0.00000, 0.00000, 90.24000);
    CreateDynamicObject(1257, 1212.34741, -1326.52954, 13.68430,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1257, 1083.02100, -1274.54492, 13.60720,   0.00000, 0.00000, 90.24000);
    CreateDynamicObject(1257, 964.63733, -1214.54919, 17.02340,   0.00000, 0.00000, 89.58000);
    CreateDynamicObject(1257, 818.55078, -1134.44849, 23.90680,   0.00000, 0.00000, 88.50000);
    CreateDynamicObject(1257, 791.28119, -1301.22681, 13.56870,   0.00000, 0.00000, -179.51990);
    CreateDynamicObject(1257, 679.34332, -1388.95630, 13.72830,   0.00000, 0.00000, 90.12000);
    CreateDynamicObject(1257, 378.06552, -1489.50562, 32.17630,   0.00000, 0.00000, 128.28003);
    CreateDynamicObject(1257, 261.02219, -1539.33704, 32.41950,   0.00000, 0.00000, -34.38000);
    CreateDynamicObject(1257, 485.92880, -1361.02576, 18.19000,   -4.00000, 4.00000, -65.24000);
    CreateDynamicObject(1257, 589.19830, -1236.84290, 17.97730,   0.00000, 0.00000, -67.92000);
    CreateDynamicObject(1257, 775.53870, -1062.00525, 24.75130,   0.00000, 0.00000, -77.69999);
    CreateDynamicObject(1257, 1209.70325, -952.07233, 43.01140,   0.00000, 0.00000, -79.26000);
    CreateDynamicObject(1257, 1713.93640, -736.80762, 50.49150,   -2.94000, 0.00000, -2.00000);
    CreateDynamicObject(1257, 1775.73401, 579.77661, 23.77970,   0.00000, 0.00000, -11.76000);
    CreateDynamicObject(1257, 1839.89514, 825.05157, 10.16840,   0.06000, 0.00000, 270.66010);
    CreateDynamicObject(1257, 2184.53564, 801.95203, 7.33030,   0.00000, 0.00000, -125.22000);
    CreateDynamicObject(1257, 2293.69141, 841.77661, 14.11820,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1257, 2353.69604, 1025.47546, 10.84100,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1257, 2570.79736, 1066.87720, 10.84120,   0.00000, 0.00000, -90.24001);
    CreateDynamicObject(1257, 2613.71777, 1319.62097, 10.86020,   0.00000, 0.00000, 90.36000);
    CreateDynamicObject(1257, 2476.20508, 1479.59375, 10.86030,   0.00000, 0.00000, 89.94000);
    CreateDynamicObject(1257, 2401.10645, 1619.55835, 10.89970,   0.00000, 0.00000, 89.88000);
    CreateDynamicObject(1257, 2293.08325, 1779.52710, 10.80020,   0.00000, 0.00000, 89.70000);
    CreateDynamicObject(1257, 2158.93481, 1995.43042, 10.87960,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1257, 2231.25317, 2383.93506, 10.86030,   0.00000, 0.00000, -12.60000);
    CreateDynamicObject(1257, 2085.77344, 2459.35864, 10.88090,   0.00000, 0.00000, 90.00000);
    CreateDynamicObject(1257, 1948.35791, 2399.46997, 10.92060,   0.00000, 0.00000, 89.64000);
    CreateDynamicObject(1257, 1920.80237, 2315.90601, 10.88100,   0.00000, 0.00000, -179.69991);
    CreateDynamicObject(1257, 1921.41638, 2117.40479, 10.94120,   0.00000, 0.00000, -179.70000);
    CreateDynamicObject(1257, 2093.48389, 2015.85571, 10.90140,   0.00000, 0.00000, -90.18000);
    CreateDynamicObject(1257, 2035.99133, 1521.35413, 10.90060,   0.00000, 0.00000, -180.05991);
    CreateDynamicObject(1257, 2036.35254, 1168.23950, 10.82070,   0.00000, 0.00000, -179.75990);
    CreateDynamicObject(1257, 2034.95715, 878.28998, 7.36150,   0.00000, 0.00000, -179.40010);
    CreateDynamicObject(1257, 1752.35156, 621.24127, 21.25890,   4.00000, 0.00000, 165.00000);
    CreateDynamicObject(1257, 1614.87988, 186.35570, 33.65740,   4.00000, 0.00000, -192.00000);
    CreateDynamicObject(1257, 1657.21387, -331.40521, 40.28030,   0.00000, 0.00000, -174.59990);
    CreateDynamicObject(1257, 1684.78406, -727.13708, 49.88370,   4.00000, 0.00000, -190.80000);
    CreateDynamicObject(1257, 1412.48633, -934.33838, 35.80170,   0.00000, 0.00000, 80.46000);
    CreateDynamicObject(1257, 1431.33862, -1040.25464, 23.92800,   0.00000, 0.00000, -89.94000);
    CreateDynamicObject(1257, 1571.46692, -1139.13977, 23.71380,   0.00000, 0.00000, -180.60001);
    CreateDynamicObject(1257, 1708.46350, -1263.24890, 13.60880,   0.00000, 0.00000, -179.16000);
    CreateDynamicObject(1257, 1590.66150, -1434.45093, 13.52840,   0.00000, 0.00000, 90.06000);
    CreateDynamicObject(1257, 1423.55896, -1568.12500, 13.62870,   0.00000, 0.00000, 173.27989);
    CreateDynamicObject(1257, 1446.39136, -1738.46875, 13.68900,   0.00000, 0.00000, -89.58000);
    CreateDynamicObject(1257, 1579.74524, -1878.48059, 13.62880,   0.00000, 0.00000, -90.06000);
    CreateDynamicObject(1257, 1815.37183, -1904.30969, 13.65310,   0.00000, 0.00000, -180.65990);
    CreateDynamicObject(1257, 1955.44678, -1998.47595, 13.60910,   0.00000, 0.00000, -179.52000);
    CreateDynamicObject(1257, 1935.31299, -2160.26001, 13.66810,   0.00000, 0.00000, 89.82000);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

destroy_bus_td(playerid)
{
    for(new i; i < 2; ++i)
    {
        if(bus_td[playerid][i] != PlayerText: INVALID_TEXT_DRAW)
            PlayerTextDrawDestroy(playerid, bus_td[playerid][i]);
    }
    return 1;
}

start_bus_work(playerid)
{
	bus_td[playerid][0] = CreatePlayerTextDraw(playerid, 260.999969, 382.459259, " ");
	PlayerTextDrawLetterSize(playerid, bus_td[playerid][0], 0.281666, 1.989928);
	PlayerTextDrawAlignment(playerid, bus_td[playerid][0], 1);
	PlayerTextDrawColor(playerid, bus_td[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, bus_td[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, bus_td[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, bus_td[playerid][0], 255);
	PlayerTextDrawFont(playerid, bus_td[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, bus_td[playerid][0], 1);

    bus_td[playerid][1] = CreatePlayerTextDraw(playerid, 260.999847, 367.526092, "~y~BUS DRIVER JOB");
    PlayerTextDrawLetterSize(playerid, bus_td[playerid][1], 0.350333, 1.815703);
    PlayerTextDrawAlignment(playerid, bus_td[playerid][1], 1);
    PlayerTextDrawColor(playerid, bus_td[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, bus_td[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, bus_td[playerid][1], 1);
    PlayerTextDrawBackgroundColor(playerid, bus_td[playerid][1], 255);
    PlayerTextDrawFont(playerid, bus_td[playerid][1], 2);
    PlayerTextDrawSetProportional(playerid, bus_td[playerid][1], 1);

    format(gString, sizeof gString, "~w~CHECKPOINTS: ~r~0~w~/~r~59");
    PlayerTextDrawSetString(playerid, bus_td[playerid][0], gString);
    
    PlayerTextDrawShow(playerid, bus_td[playerid][0]);
    PlayerTextDrawShow(playerid, bus_td[playerid][1]);

	SCM(playerid, -1, "Mergi la checkpoint.");

	job::createJobVehicle(playerid, 431, 1675.2267, -2248.7644, 13.6295, 89.9309, 0);

    SetPVarInt(playerid, "bus_cp_step", 0);

    s_PlayerInfo[playerid][pSCP] = CP_BUS;
    return SetJobRaceCheckpoint(playerid, 0, bus_cps[GetPVarInt(playerid, "bus_cp_step")][0], bus_cps[GetPVarInt(playerid, "bus_cp_step")][1], bus_cps[GetPVarInt(playerid, "bus_cp_step")][2], bus_cps[GetPVarInt(playerid, "bus_cp_step")][3], bus_cps[GetPVarInt(playerid, "bus_cp_step")][4], bus_cps[GetPVarInt(playerid, "bus_cp_step")][5], 4.0, 8);
}

cancel_bus_work(playerid)
{
    if(job_data[playerid][jobDuty] != JOB_TYPE_BUS)
        return 1;

    DeletePVar(playerid, "bus_shift_step");
    DeletePVar(playerid, "bus_cp_step");

    destroy_bus_td(playerid);

    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER)
    {
        if(job_data[playerid][jobVehicle] == s_PlayerInfo[playerid][pSLastVehicle] && job_data[playerid][jobVehicle] && job_data[playerid][jobDuty] == JOB_TYPE_BUS)
        {
            SCM(playerid, COLOR_GREEN, "(-) Ai platit $2.000 companiei de autobuze pentru taxe.");
            GivePlayerMoney(playerid, -2000);

            stop_job_work(playerid);
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterRaceCP(playerid)
{
    if(s_PlayerInfo[playerid][pSCP] == CP_BUS && job_data[playerid][jobDuty] == JOB_TYPE_BUS && IsPlayerInJobVehicle(playerid))
    {
        SCM(playerid, -1, "{909CE7}(Job):{FFFFFF} Opreste autobuzul in checkpoint-ul rosu.");
        TogglePlayerControllable(playerid, 0);

        SetTimerEx("BusDriverCheck", 3000, 0, "d", playerid);
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

function BusDriverCheck(playerid)
{
    new
        job_money = (BUS_MONEY) + (job::returnPlayerSkill(playerid, JOB_TYPE_BUS) * 100 + RandomEx((job::returnPlayerSkill(playerid, JOB_TYPE_BUS) * 100), (job::returnPlayerSkill(playerid, JOB_TYPE_BUS) * 100) + 500));

    SCMF(playerid, -1, "{909CE7}(Job):{FFFFFF} Ai primit $%s. Mergi la urmatorul checkpoint.", FormatNumber(job_money));
    GivePlayerMoney(playerid, job_money);

    DisablePlayerRaceCheckpoint(playerid);
    TogglePlayerControllable(playerid, 1);

    SetPVarInt(playerid, "bus_cp_step", GetPVarInt(playerid, "bus_cp_step")+1);
    SetPVarInt(playerid, "bus_shift_step", GetPVarInt(playerid, "bus_shift_step")+1);

    if(GetPVarInt(playerid, "bus_shift_step") >= 10)
    {
        DeletePVar(playerid, "bus_shift_step");
        job::updateJobSkill(playerid, JOB_TYPE_BUS);
    }

    format(gString, sizeof gString, "~w~CHECKPOINTS: ~r~%d~w~/~r~59", GetPVarInt(playerid, "bus_cp_step"));
    PlayerTextDrawSetString(playerid, bus_td[playerid][0], gString);

    if(GetPVarInt(playerid, "bus_cp_step") == 58)
        SetPVarInt(playerid, "bus_cp_step", 0);

    return SetJobRaceCheckpoint(playerid, 0, bus_cps[GetPVarInt(playerid, "bus_cp_step")][0], bus_cps[GetPVarInt(playerid, "bus_cp_step")][1], bus_cps[GetPVarInt(playerid, "bus_cp_step")][2], bus_cps[GetPVarInt(playerid, "bus_cp_step")][3], bus_cps[GetPVarInt(playerid, "bus_cp_step")][4], bus_cps[GetPVarInt(playerid, "bus_cp_step")][5], 4.0, 8);
}
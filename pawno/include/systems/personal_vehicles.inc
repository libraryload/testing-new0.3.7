#include <YSI_Coding\y_hooks>

#define MAX_VEHICLE_SPAWN_TIME (300)

enum cInfo
{
    cID, cModel, cVIP, cSpecial, Float: cLocationx, Float: cLocationy, Float: cLocationz, Float: cAngle,
    Float: cLastLocationx, Float: cLastLocationy, Float: cLastLocationz, Float: cLastAngle, Float: cVIPPos[6],
    cVIPText[MAX_PLAYER_NAME], cVIPColor[12], cFuelTank, cNeon, cMod[17], cSpoiler,
    cColorOne, cColorTwo, cFuel, cOwner[MAX_PLAYER_NAME], cDescription[128], cValue, cLicense[64], cOwned,
    cLock, cInscarprice, cInsurancecar, Float: cHealth, Float:cKM, cSell, cPaintJ, cBuyTime, cSpawnTime,
    cDamageStatus[4]
};

new CarInfo[MAX_VEHICLES][cInfo], VehicleSQL[MAX_VEHICLES], masinacars[MAX_PLAYERS][99],
    tospawn[MAX_PLAYERS], VIPObject[MAX_VEHICLES], NeonObject[2][MAX_VEHICLES], SpoilerObject[MAX_VEHICLES];

new vehicleNeonName[][] =
{
    {"None"},
    {"Red"},
    {"Yellow"},
    {"Blue"},
    {"Green"},
    {"Purple"},
    {"White"}
};

new unstuckLocName[][] =
{ 
    {"The Emerald Isle, Las Venturas"},
    {"The Emerald Isle, Las Venturas"},
    {"Santa Maria Beach, Los Santos"},
    {"Las Venturas Airport, Las Venturas"},
    {"Last Dime Motel, Las Venturas"},
    {"Conference Center, Los Santos"},
    {"Come-A-Lot, Las Venturas"},
    {"Come-A-Lot, Las Venturas"},
    {"Fort Carson, Las Venturas"}
};

new Float: unstuckLocPos[][] =
{ 
    {2139.1489, 2468.4971, 10.8381},
    {2065.6536, 2479.7402, 10.8300},
    {331.1922, -1788.7651, 4.6058},
    {1660.3026, 1297.8322, 10.8447},
    {1910.0438, 708.5315, 10.9120},
    {1062.7190, -1743.2092, 13.5567},
    {2132.9595, 1009.7474, 10.9092},
    {2172.0205, 1012.7982, 10.9081},
    {-83.9809, 1076.7527, 19.8237}
};

new Float: unstuckLVParkPos[][] =
{
    {2353.6509, 1405.0918, 42.8423},
    {2353.5913, 1408.5909, 42.8426},
    {2352.9756, 1412.2689, 42.8405},
    {2352.4397, 1415.8331, 42.8459},
    {2353.3921, 1419.3680, 42.8409},
    {2353.4089, 1422.8971, 42.8403},
    {2353.6487, 1426.5477, 42.8383},
    {2353.5398, 1430.0055, 42.8417},
    {2353.3728, 1433.5975, 42.8374},
    {2353.5349, 1437.2021, 42.8356},
    {2353.7461, 1440.7115, 42.8403},
    {2353.2708, 1444.2145, 42.8399},
    {2353.1926, 1447.9227, 42.8332},
    {2353.0476, 1451.5658, 42.8416},
    {2353.3591, 1454.9374, 42.8438},
    {2353.6365, 1458.6809, 42.8399},
    {2353.3337, 1462.3218, 42.8436},
    {2353.4094, 1465.7025, 42.8432},
    {2353.3950, 1469.3606, 42.8384},
    {2353.4414, 1472.8353, 42.8459},
    {2353.7180, 1476.3926, 42.8382},
    {2353.6704, 1479.9454, 42.8448},
    {2353.9360, 1483.6187, 42.8465},
    {2353.9302, 1486.8604, 42.8462},
    {2353.7505, 1490.6283, 42.8411},
    {2353.6050, 1494.1986, 42.8411},
    {2352.9153, 1497.9969, 42.8390}
};

new spoiler[20][0] =
{
    {1000}, {1001}, {1002}, {1003}, {1014}, {1015}, {1016}, {1023}, {1058}, {1060}, {1049}, {1050}, {1138}, {1139}, {1146}, {1147}, {1158}, {1162}, {1163}, {1164}
};

new nitro[3][0] = {
    {1008}, {1009}, {1010}
};

new fbumper[23][0] = {
    {1117}, {1152}, {1153}, {1155}, {1157}, {1160}, {1165}, {1167}, {1169}, {1170}, {1171}, {1172}, {1173}, {1174}, {1175}, {1179}, {1181}, {1182}, {1185}, {1188}, {1189}, {1192}, {1193}
};

new rbumper[22][0] = {
    {1140}, {1141}, {1148}, {1149}, {1150}, {1151}, {1154}, {1156}, {1159}, {1161}, {1166}, {1168}, {1176}, {1177}, {1178}, {1180}, {1183}, {1184}, {1186}, {1187}, {1190}, {1191}
};

new exhaust[28][0] = {
    {1018}, {1019}, {1020}, {1021}, {1022}, {1028}, {1029}, {1037}, {1043}, {1044}, {1045}, {1046}, {1059}, {1064}, {1065}, {1066}, {1089}, {1092}, {1104}, {1105}, {1113}, {1114}, {1126}, {1127}, {1129}, {1132}, {1135}, {1136}
};

new bventr[2][0] = {
    {1142}, {1144}
};

new bventl[2][0] = {
    {1143}, {1145}
};

new bscoop[4][0] = {
    {1004}, {1005}, {1011}, {1012}
};

new rscoop[17][0] = {
    {1006}, {1032}, {1033}, {1035}, {1038}, {1053}, {1054}, {1055}, {1061}, {1067}, {1068}, {1088}, {1091}, {1103}, {1128}, {1130}, {1131}
};

new lskirt[21][0] = {
    {1007}, {1026}, {1031}, {1036}, {1039}, {1042}, {1047}, {1048}, {1056}, {1057}, {1069}, {1070}, {1090}, {1093}, {1106}, {1108}, {1118}, {1119}, {1133}, {1122}, {1134}
};

new rskirt[21][0] = {
    {1017}, {1027}, {1030}, {1040}, {1041}, {1051}, {1052}, {1062}, {1063}, {1071}, {1072}, {1094}, {1095}, {1099}, {1101}, {1102}, {1107}, {1120}, {1121}, {1124}, {1137}
};

new hydraulics[1][0] = {
    {1087}
};

new vbase[1][0] = {
    {1086}
};

new rbbars[4][0] = {
    {1109}, {1110}, {1123}, {1125}
};

new fbbars[2][0] = {
    {1115}, {1116}
};

new wheels[17][0] = {
    {1025}, {1073}, {1074}, {1075}, {1076}, {1077}, {1078}, {1079}, {1080}, {1081}, {1082}, {1083}, {1084}, {1085}, {1096}, {1097}, {1098}
};

new vlights[2][0] = {
    {1013}, {1024}
};

function LoadPlayerVehicles()
{
    for(new v; v < cache_num_rows(); v++)
    {
        new
            vehicleDBId = cache_get_field_content_int(v, "ID");

        cache_get_field_content(v, "Owner", CarInfo[vehicleDBId][cOwner], SQL, MAX_PLAYER_NAME);
        cache_get_field_content(v, "License", CarInfo[vehicleDBId][cLicense], SQL, 130);
        cache_get_field_content(v, "Description", CarInfo[vehicleDBId][cDescription], SQL, 130);
        cache_get_field_content(v, "VIPText", CarInfo[vehicleDBId][cVIPText], SQL, MAX_PLAYER_NAME);
        cache_get_field_content(v, "VIPColor", CarInfo[vehicleDBId][cVIPColor], SQL, 12);

        CarInfo[vehicleDBId][cID]                  =         cache_get_field_content_int(v, "ID");
        CarInfo[vehicleDBId][cModel]               =         cache_get_field_content_int(v, "Model");
        CarInfo[vehicleDBId][cLocationx]           =         cache_get_field_content_float(v, "Locationx");
        CarInfo[vehicleDBId][cLocationy]           =         cache_get_field_content_float(v, "Locationy");
        CarInfo[vehicleDBId][cLocationz]           =         cache_get_field_content_float(v, "Locationz");
        CarInfo[vehicleDBId][cAngle]               =         cache_get_field_content_float(v, "Angle");
        CarInfo[vehicleDBId][cLastLocationx]       =         cache_get_field_content_float(v, "LastLocationx");
        CarInfo[vehicleDBId][cLastLocationy]       =         cache_get_field_content_float(v, "LastLocationy");
        CarInfo[vehicleDBId][cLastLocationz]       =         cache_get_field_content_float(v, "LastLocationz");
        CarInfo[vehicleDBId][cLastAngle]           =         cache_get_field_content_float(v, "LastAngle");
        CarInfo[vehicleDBId][cVIP]                 =         cache_get_field_content_int(v, "VIP");
        CarInfo[vehicleDBId][cSpecial]             =         cache_get_field_content_int(v, "Special");
        CarInfo[vehicleDBId][cSpoiler]             =         cache_get_field_content_int(v, "Spoiler");
        CarInfo[vehicleDBId][cFuelTank]            =         cache_get_field_content_int(v, "FuelTank");
        CarInfo[vehicleDBId][cNeon]                =         cache_get_field_content_int(v, "Neon");
        CarInfo[vehicleDBId][cColorOne]            =         cache_get_field_content_int(v, "ColorOne");
        CarInfo[vehicleDBId][cColorTwo]            =         cache_get_field_content_int(v, "ColorTwo");
        CarInfo[vehicleDBId][cValue]               =         cache_get_field_content_int(v, "Value");
        CarInfo[vehicleDBId][cLock]                =         cache_get_field_content_int(v, "Lockk");
        CarInfo[vehicleDBId][cInscarprice]         =         cache_get_field_content_int(v, "Inscarprice");
        CarInfo[vehicleDBId][cInsurancecar]        =         cache_get_field_content_int(v, "Insurancecar");
        CarInfo[vehicleDBId][cKM]                  =         cache_get_field_content_float(v, "KM");
        CarInfo[vehicleDBId][cFuel]                =         cache_get_field_content_int(v, "Fuel");
        CarInfo[vehicleDBId][cOwned]               =         cache_get_field_content_int(v, "Owned");
        CarInfo[vehicleDBId][cSell]                =         cache_get_field_content_int(v, "Sell");
        CarInfo[vehicleDBId][cPaintJ]              =         cache_get_field_content_int(v, "PaintJ");
        CarInfo[vehicleDBId][cBuyTime]             =         cache_get_field_content_int(v, "BuyTime");
        CarInfo[vehicleDBId][cHealth]              =         cache_get_field_content_int(v, "Health");
        new
            loadString[72];
        
        cache_get_field_content(v, "DamageStatus", loadString, SQL, 32);
        sscanf(loadString, "a<i>[4]", CarInfo[vehicleDBId][cDamageStatus]);

        cache_get_field_content(v, "VIPPos", loadString, SQL, sizeof loadString);
        sscanf(loadString, "a<f>[6]", CarInfo[vehicleDBId][cVIPPos]);

        cache_get_field_content(v, "Mod", loadString, SQL, sizeof loadString);
        sscanf(loadString, "a<i>[17]", CarInfo[vehicleDBId][cMod]);
    }
    return 1;
}

hook OnPlayerEditDynObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    if(response == EDIT_RESPONSE_FINAL)
    {
        if(GetPVarInt(playerid, "edit_object_vip"))
        {
            new vehicleGameID = GetPlayerVehicleID(playerid), vehicleDBId = VehicleSQL[vehicleGameID];

            GetVehicleObjectPositionOffset(GetPlayerVehicleID(playerid), x, y, z, rx, ry, rz, CarInfo[vehicleDBId][cVIPPos][0], CarInfo[vehicleDBId][cVIPPos][1], CarInfo[vehicleDBId][cVIPPos][2], CarInfo[vehicleDBId][cVIPPos][3], CarInfo[vehicleDBId][cVIPPos][4], CarInfo[vehicleDBId][cVIPPos][5]);
            AttachDynamicObjectToVehicle(objectid, vehicleGameID, CarInfo[vehicleDBId][cVIPPos][0], CarInfo[vehicleDBId][cVIPPos][1], CarInfo[vehicleDBId][cVIPPos][2], CarInfo[vehicleDBId][cVIPPos][3], CarInfo[vehicleDBId][cVIPPos][4], CarInfo[vehicleDBId][cVIPPos][5]);

            TogglePlayerControllable(playerid, 1);

            mysql_format(SQL, gString, sizeof gString, "update `cars` set `VIPPos` = '%f %f %f %f %f %f' where `ID` = '%d';", CarInfo[vehicleDBId][cVIPPos][0], CarInfo[vehicleDBId][cVIPPos][1], CarInfo[vehicleDBId][cVIPPos][2], CarInfo[vehicleDBId][cVIPPos][3], CarInfo[vehicleDBId][cVIPPos][4], CarInfo[vehicleDBId][cVIPPos][5], vehicleDBId);
            mysql_tquery(SQL, gString, "", "");

            DeletePVar(playerid, "edit_object_vip");
        }
    }
    else if(response == EDIT_RESPONSE_CANCEL)
    {
        if(GetPVarInt(playerid, "edit_object_vip"))
        {
            new
                vehicleGameID = GetPlayerVehicleID(playerid);

            AttachTextToVehicle(vehicleGameID);
            TogglePlayerControllable(playerid, 1);

            DeletePVar(playerid, "edit_object_vip");
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnVehicleStreamIn(vehicleid, forplayerid)
{
    new
        vehicleDBId = VehicleSQL[vehicleid];

    if(VehicleSQL[vehicleid])
    {
        new
            engine, lights, alarm, doors, bonnet, boot, objective;
        
        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
        SetVehicleParamsEx(vehicleid, engine, lights, alarm, CarInfo[vehicleDBId][cLock], bonnet, boot, objective);

        if(strmatch(PlayerInfo[forplayerid][pNormalName], CarInfo[vehicleDBId][cOwner]) || s_PlayerInfo[forplayerid][pSHireCar] == VehicleSQL[vehicleid])
        {
            SetVehicleParamsForPlayer(vehicleid, forplayerid, 0, 0);
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnVehDamageStatusUpdate(vehicleid, playerid)
{
    new
        vehicleDBId = VehicleSQL[vehicleid];

    if(vehicleDBId)
    {
        new
            Float:vHealth;
        
        GetVehicleHealth(vehicleid, vHealth);
        CarInfo[vehicleDBId][cHealth] = vHealth;
        GetVehicleDamageStatus(vehicleid, CarInfo[vehicleDBId][cDamageStatus][0], CarInfo[vehicleDBId][cDamageStatus][1], CarInfo[vehicleDBId][cDamageStatus][2], CarInfo[vehicleDBId][cDamageStatus][3]);
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnVehicleMod(playerid, vehicleid, componentid)
{
    if(VehicleSQL[vehicleid] != 0)
    {
        SaveComponent(vehicleid, componentid);
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
    if(VehicleSQL[vehicleid])
    {
        CarInfo[VehicleSQL[vehicleid]][cPaintJ] = paintjobid;

        mysql_format(SQL, gString, sizeof gString, "update `cars` set `PaintJ` = '%d' where `ID` = '%d';", CarInfo[VehicleSQL[vehicleid]][cPaintJ], VehicleSQL[vehicleid]);
        mysql_tquery(SQL, gString, "", "");
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnVehicleSpawn(vehicleid)
{
    if(!VehicleSQL[vehicleid])
        VehicleInfo[vehicleid][vehFuel] = 100;
    else
    {
        new
            engine, lights, alarm, doors, bonnet, boot, objective;

        new
            vehicleDBId = VehicleSQL[vehicleid];

        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
        SetVehicleParamsEx(vehicleid, engine, lights, alarm, CarInfo[vehicleDBId][cLock] ? 0 : 1, bonnet, boot, objective);

        ModVehicle(vehicleid);

        ChangeVehiclePaintjob(vehicleid, CarInfo[vehicleDBId][cPaintJ]);
        SetVehicleNumberPlate(vehicleid,CarInfo[vehicleDBId][cLicense]);
        
        SetVehiclePos(vehicleid, CarInfo[vehicleDBId][cLocationx], CarInfo[vehicleDBId][cLocationy], CarInfo[vehicleDBId][cLocationz]);
        
        ChangeVehicleColor(vehicleid, CarInfo[VehicleSQL[vehicleid]][cColorOne], CarInfo[VehicleSQL[vehicleid]][cColorTwo]);

        VehicleInfo[vehicleid][vehFuel] = CarInfo[vehicleDBId][cFuel];
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnVehicleDeath(vehicleid)
{
    new
        engine, lights, alarm, doors, bonnet, boot, objective;
    
    VehicleInfo[vehicleid][vehEngine] = 0;
    
    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);

    foreach(new v : VehicleType<VEH_TYPE_PERSONAL>)
    {
        if(v == vehicleid)
        {
            new vehicleDBId = VehicleSQL[vehicleid];

            if(CarInfo[vehicleDBId][cInsurancecar] != 0)
            {
                CarInfo[vehicleDBId][cHealth] = 1000.0;

                CarInfo[vehicleDBId][cDamageStatus][0] = 0; CarInfo[vehicleDBId][cDamageStatus][1] = 0;
                CarInfo[vehicleDBId][cDamageStatus][2] = 0; CarInfo[vehicleDBId][cDamageStatus][3] = 0;

                CarInfo[vehicleDBId][cLastLocationx] = 0;
                CarInfo[vehicleDBId][cLastLocationy] = 0;
                CarInfo[vehicleDBId][cLastLocationz] = 0;

                UpdateVehicleDamageStatus(vehicleid, CarInfo[vehicleDBId][cDamageStatus][0], CarInfo[vehicleDBId][cDamageStatus][1], CarInfo[vehicleDBId][cDamageStatus][2], CarInfo[vehicleDBId][cDamageStatus][3]);

                CarInfo[vehicleDBId][cInsurancecar] --;
                CarInfo[vehicleDBId][cInscarprice] += 150;

                mysql_format(SQL, gString, sizeof gString, "update `cars` set `KM` = '%f', `Fuel` = '%d', `Health` = '%f', `DamageStatus` = '%d %d %d %d', `Inscarprice` = '%d', `Insurancecar` = '%d', `Locationx` = '%f', `Locationy` = '%f', `Locationz` = '%f', `Angle` = '%f', `LastLocationx` = '%f', `LastLocationy` = '%f', `LastLocationz` = '%f', `LastAngle` = '%f' where `ID` = '%d';", CarInfo[vehicleDBId][cKM], CarInfo[vehicleDBId][cFuel], CarInfo[vehicleDBId][cHealth], CarInfo[vehicleDBId][cDamageStatus][0], CarInfo[vehicleDBId][cDamageStatus][1], CarInfo[vehicleDBId][cDamageStatus][2], CarInfo[vehicleDBId][cDamageStatus][3], CarInfo[vehicleDBId][cInscarprice], CarInfo[vehicleDBId][cInsurancecar], CarInfo[vehicleDBId][cLocationx], CarInfo[vehicleDBId][cLocationy], CarInfo[vehicleDBId][cLocationz], CarInfo[vehicleDBId][cAngle], CarInfo[vehicleDBId][cLastLocationx], CarInfo[vehicleDBId][cLastLocationy], CarInfo[vehicleDBId][cLastLocationz], CarInfo[vehicleDBId][cLastAngle], vehicleDBId);
                mysql_tquery(SQL, gString, "", "");
            }
        }
    }

    StopAudioStreamForPlayersInCar(vehicleid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    switch(newstate)
    {
        case PLAYER_STATE_DRIVER:
        {
            new
                vehicleDBId = VehicleSQL[GetPlayerVehicleID(playerid)];
            
            if(vehicleDBId)
            {
                format(gString, sizeof gString, "This %s (ID %d) is owned by %s | Age: %d days | Odometer: %.0f km | Insurance: $%s (%d points) | Colors: %d, %d%s%s%s", CarInfo[vehicleDBId][cDescription], vehicleDBId, CarInfo[vehicleDBId][cOwner], TSToDays(CarInfo[vehicleDBId][cBuyTime]), CarInfo[vehicleDBId][cKM], FormatNumber(CarInfo[vehicleDBId][cInscarprice]), CarInfo[vehicleDBId][cInsurancecar], CarInfo[vehicleDBId][cColorOne], CarInfo[vehicleDBId][cColorTwo], CarInfo[vehicleDBId][cVIP] ? (" {FFFF00}[VIP]") : (""), CarInfo[vehicleDBId][cSpecial] ? (" {ffd700}[GOLD]") : (""), CarInfo[vehicleDBId][cSpoiler] ? (" {008080}[SPOILER]") : (""));
                sendLongMessage(playerid, COLOR_WHITE, gString);

                if(CarInfo[vehicleDBId][cInsurancecar] == 0)
                {
                    if(strcmp(PlayerInfo[playerid][pNormalName], CarInfo[vehicleDBId][cOwner], true) == 0)
                    {
                        format(gString, sizeof gString, "Your vehicle ran out of insurance points.\n\nWould you wish to buy one? (one is $%s)", FormatNumber(CarInfo[vehicleDBId][cInscarprice]));
                        Dialog_Show(playerid, DIALOG_PAYCARINS, DIALOG_STYLE_MSGBOX, "Vehicle Insurance", gString, "Ok", "Cancel");
                    }
                    else
                    {
                        SCM(playerid, COLOR_GREY, "Nu puteti conduce acest vehicul deoarece proprietarul acestuia nu i-a platit asigurarea.");
                        RemovePlayerFromVehicle(playerid);
                    }
                }
            }
        }
        case PLAYER_STATE_ONFOOT:
        {
            new
                vehicleDBId = VehicleSQL[s_PlayerInfo[playerid][pSLastVehicle]];
            
            if(vehicleDBId && IsValidVehicle(s_PlayerInfo[playerid][pSLastVehicle]))
            {
                if(strcmp(PlayerInfo[playerid][pNormalName], CarInfo[vehicleDBId][cOwner], true) == 0)
                    SetVehicleParamsForPlayer(s_PlayerInfo[playerid][pSLastVehicle], playerid, 0, 0);

                CarInfo[vehicleDBId][cSpawnTime] = gettime() + MAX_VEHICLE_SPAWN_TIME;
            }
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerExitVehicle(playerid, vehicleid)
{
    new
        vehicleDBId = VehicleSQL[vehicleid];

    if(vehicleDBId)
    {
        if(strmatch(PlayerInfo[playerid][pNormalName], CarInfo[vehicleDBId][cOwner]) || s_PlayerInfo[playerid][pSHireCar] == vehicleDBId)
            SetVehicleParamsForPlayer(vehicleid, playerid, 0, 0);

        GetVehiclePos(vehicleid, CarInfo[vehicleDBId][cLastLocationx], CarInfo[vehicleDBId][cLastLocationy], CarInfo[vehicleDBId][cLastLocationz]);
        GetVehicleZAngle(vehicleid, CarInfo[vehicleDBId][cLastAngle]);

        CarInfo[vehicleDBId][cSpawnTime] = gettime() + MAX_VEHICLE_SPAWN_TIME;

        mysql_format(SQL, gString, sizeof gString, "update `cars` set `KM` = '%f', `Fuel` = '%d', `Health` = '%f', `DamageStatus` = '%d %d %d %d', `Inscarprice` = '%d', `Insurancecar` = '%d', `Locationx` = '%f', `Locationy` = '%f', `Locationz` = '%f', `Angle` = '%f', `LastLocationx` = '%f', `LastLocationy` = '%f', `LastLocationz` = '%f', `LastAngle` = '%f' where `ID` = '%d';", CarInfo[vehicleDBId][cKM], CarInfo[vehicleDBId][cFuel], CarInfo[vehicleDBId][cHealth], CarInfo[vehicleDBId][cDamageStatus][0], CarInfo[vehicleDBId][cDamageStatus][1], CarInfo[vehicleDBId][cDamageStatus][2], CarInfo[vehicleDBId][cDamageStatus][3], CarInfo[vehicleDBId][cInscarprice], CarInfo[vehicleDBId][cInsurancecar], CarInfo[vehicleDBId][cLocationx], CarInfo[vehicleDBId][cLocationy], CarInfo[vehicleDBId][cLocationz], CarInfo[vehicleDBId][cAngle], CarInfo[vehicleDBId][cLastLocationx], CarInfo[vehicleDBId][cLastLocationy], CarInfo[vehicleDBId][cLastLocationz], CarInfo[vehicleDBId][cLastAngle], vehicleDBId);
        mysql_tquery(SQL, gString, "", "");
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

static stock Float:GetDistanceBetweenPoints(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2)
{
    return floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
}

stock GetPCars(playerid)
{
    new
        Cache: localQuery;
    
    mysql_format(SQL, gQuery, sizeof gQuery, "select * from `cars` where `Owner` = '%e';", PlayerInfo[playerid][pNormalName]);
    localQuery = mysql_query(SQL, gQuery);
    
    new totalCars = cache_num_rows();
    cache_delete(localQuery);
    return totalCars;
}

stock invalidKMVehicle(vehicle)
{
    if(IsAPlane(vehicle) || IsABoat(vehicle) || IsABike(vehicle))
        return 1;

    return 0;
}

stock GetCurrentVehSpeed(playerid,mode = 1)
{
    new Float:Velocity [3];
    GetVehicleVelocity ( GetPlayerVehicleID ( playerid ) , Velocity [ 0 ] , Velocity [ 1 ] , Velocity [ 2 ] ) ;
    return IsPlayerInAnyVehicle ( playerid ) ? floatround ( ( ( floatsqroot ( ( ( Velocity [ 0 ] * Velocity [ 0 ] ) + ( Velocity [ 1 ] * Velocity [ 1 ] ) + ( Velocity [ 2 ] * Velocity [ 2 ] ) ) ) * ( !mode ? 105.0 : 180.0 ) ) ) * 1 ) : 0;
}

function checkInfoAboutVehicle()
{
    foreach(new i : PlayersInVehicle)
    {
        if(!PlayerInfo[i][pHUD][10])
            return 1;

        new
            vehicleId = GetPlayerVehicleID(i), vehicleDBId = VehicleSQL[vehicleId];

        if(!PlayerInfo[i][pHUD][7])
        {
            format(gString, sizeof gString, "SPEED: ~g~%d ~w~~h~KM/H~n~", GetCurrentVehSpeed(i));

            if(!invalidKMVehicle(vehicleId))
                format(gString, sizeof gString, "%sFUEL: ~g~%d~n~", gString, VehicleInfo[vehicleId][vehFuel]);

            format(gString, sizeof gString, "%s~w~~h~RADIO: ~g~None~n~", gString);

            if(vehicleDBId)
            {
                if(!IsAPlane(vehicleId))
                    format(gString, sizeof gString, "%s~w~~h~ODOMETER: ~g~%.0fKM~n~", gString, CarInfo[vehicleDBId][cKM]);
                
                format(gString, sizeof gString, "%s%s", gString, CarInfo[vehicleDBId][cLock] ? ("~g~LOCKED") : ("~w~~h~UNLOCKED"));
            }

            PlayerTextDrawSetString(i, veh_speedo[i], gString);
            PlayerTextDrawShow(i, veh_speedo[i]);
        }
        else
        {
            format(gString, sizeof gString, "%d", GetCurrentVehSpeed(i));
            PlayerTextDrawSetString(i, Speedo[i][0], gString);

            gString[0] = (EOS); // PULA MEA SAMP

            PlayerTextDrawShow(i, Speedo[i][0]);
            PlayerTextDrawShow(i, Speedo[i][1]);

            if(!invalidKMVehicle(vehicleId))
                format(gString, sizeof gString, "~w~~h~FUEL: ~b~~h~~h~%d~n~", VehicleInfo[vehicleId][vehFuel]);

            if(vehicleDBId)
            {
                if(!IsAPlane(vehicleId))
                    format(gString, sizeof gString, "%s~w~~h~KM: ~b~~h~~h~%.0f~n~", gString, CarInfo[vehicleDBId][cKM]);
                
                format(gString, sizeof gString, "%s%s", gString, CarInfo[vehicleDBId][cLock] ? ("~b~~h~~h~LOCKED") : ("~w~~h~UNLOCKED"));
            }

            PlayerTextDrawSetString(i, Speedo[i][2], gString);
            PlayerTextDrawShow(i, Speedo[i][2]);
        }
    }
    return 1;
}

task CheckGas[30000]()
{   
    foreach(new i : PlayersInVehicle)
    {
        if(GetPlayerState(i) != PLAYER_STATE_DRIVER)
            return 1;

        new
            vehicleid = GetPlayerVehicleID(i);

        if(VehicleInfo[vehicleid][vehFuel] >= 1)
        {
            if(!VehicleInfo[vehicleid][vehEngine])
                return 1;

            if(!invalidKMVehicle(vehicleid) && !IsAJobVehicle(vehicleid))
                VehicleInfo[vehicleid][vehFuel] --;

            new
                vehicleDBId = VehicleSQL[vehicleid];

            if(vehicleDBId)
            {
                CarInfo[vehicleDBId][cFuel] = VehicleInfo[vehicleid][vehFuel];

                if(GetCurrentVehSpeed(i) > 14 && GetPlayerState(i) == PLAYER_STATE_DRIVER && GetPlayerVehicleID(i) == vehicleid && !s_PlayerInfo[i][pSAFK])
                {
                    if(IsABoat(vehicleid) || IsAPlane(vehicleid))
                        return 1;

                    CarInfo[vehicleDBId][cKM] += 1;
                    //DailyQuestCheck(i, QUEST_TYPE_VEHKM, 1);
                }
            }
        }
        else
        {
            TogglePlayerControllable(i, 0);
            GameTextForPlayer(i,"~w~~n~~n~~n~~n~~n~~n~~n~~n~No fuel in vehicle.",1500,3);
            
            VehicleInfo[vehicleid][vehEngine] = 0;

            new
                engine, lights, alarm, doors, bonnet, boot, objective;

            GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
            SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
        }
    }
    return 1;
}

function GetVehicleGameID(dbid)
{
    foreach(new vehicleid : VehicleType<VEH_TYPE_PERSONAL>)
    {
        if(VehicleSQL[vehicleid] == dbid) return vehicleid;
    }
    return 0;
}

function GetVehicleSpawnedState(idmasina)
{
    foreach(new vehicleid : VehicleType<VEH_TYPE_PERSONAL>)
    {
        if(VehicleSQL[vehicleid] == idmasina)
            return 1;
    }
    return 0;
}

function SaveComponent(vehicleid, componentid)
{
    new
        vehicleDBId = VehicleSQL[vehicleid];

    for(new x; x < 20; ++x)
    {
        if(componentid == spoiler[x][0])
            CarInfo[vehicleDBId][cMod][0] = componentid;
    }
    for(new x; x < 3; ++x)
    {
        if(componentid == nitro[x][0])
            CarInfo[vehicleDBId][cMod][1] = componentid;
    }
    for(new x; x < 23; ++x)
    {
        if(componentid == fbumper[x][0])
            CarInfo[vehicleDBId][cMod][2] = componentid;
    }
    for(new x; x < 22; ++x)
    {
        if(componentid == rbumper[x][0])
            CarInfo[vehicleDBId][cMod][3] = componentid;
    }
    for(new x; x < 28; ++x)
    {
        if(componentid == exhaust[x][0])
            CarInfo[vehicleDBId][cMod][4] = componentid;
    }
    for(new x; x < 2; ++x)
    {
        if(componentid == bventr[x][0])
            CarInfo[vehicleDBId][cMod][5] = componentid;
    }
    for(new x; x < 2; ++x)
    {
        if(componentid == bventl[x][0])
            CarInfo[vehicleDBId][cMod][6] = componentid;
    }
    for(new x; x < 4; ++x)
    {
        if(componentid == bscoop[x][0])
            CarInfo[vehicleDBId][cMod][7] = componentid;
    }
    for(new x; x < 17; ++x)
    {
        if(componentid == rscoop[x][0])
            CarInfo[vehicleDBId][cMod][8] = componentid;
    }
    for(new x; x < 21; ++x)
    {
        if(componentid == lskirt[x][0])
            CarInfo[vehicleDBId][cMod][9] = componentid;
    }
    for(new x; x < 21; ++x)
    {
        if(componentid == rskirt[x][0])
            CarInfo[vehicleDBId][cMod][10] = componentid;
    }
    for(new x; x < 1; ++x)
    {
        if(componentid == hydraulics[x][0])
            CarInfo[vehicleDBId][cMod][11] = componentid;
    }
    for(new x; x < 1; ++x)
    {
        if(componentid == vbase[x][0])
            CarInfo[vehicleDBId][cMod][12] = componentid;
    }
    for(new x; x < 4; ++x)
    {
        if(componentid == rbbars[x][0])
            CarInfo[vehicleDBId][cMod][13] = componentid;
    }
    for(new x; x < 2; ++x)
    {
        if(componentid == fbbars[x][0])
            CarInfo[vehicleDBId][cMod][14] = componentid;
    }
    for(new x; x < 17; ++x)
    {
        if(componentid == wheels[x][0])
            CarInfo[vehicleDBId][cMod][15] = componentid;
    }
    for(new x; x < 2; ++x)
    {
        if(componentid == vlights[x][0])
            CarInfo[vehicleDBId][cMod][16] = componentid;
    }
    mysql_format(SQL, gString, sizeof gString, "update `cars` set `Mod` = '%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d' where `ID` = '%d';", CarInfo[vehicleDBId][cMod][0], CarInfo[vehicleDBId][cMod][1], CarInfo[vehicleDBId][cMod][2], CarInfo[vehicleDBId][cMod][3], CarInfo[vehicleDBId][cMod][4], CarInfo[vehicleDBId][cMod][5], CarInfo[vehicleDBId][cMod][6], CarInfo[vehicleDBId][cMod][7], CarInfo[vehicleDBId][cMod][8], CarInfo[vehicleDBId][cMod][9], CarInfo[vehicleDBId][cMod][10], CarInfo[vehicleDBId][cMod][11], CarInfo[vehicleDBId][cMod][12], CarInfo[vehicleDBId][cMod][13], CarInfo[vehicleDBId][cMod][14], CarInfo[vehicleDBId][cMod][15], CarInfo[vehicleDBId][cMod][16], vehicleDBId);
    mysql_tquery(SQL, gString, "", "");
    return 1;
}

function ModVehicle(vehicleid)
{
    new
        vehicleDBId = VehicleSQL[vehicleid];
    
    for(new x; x < 17; ++x)
    {
        if(CarInfo[vehicleDBId][cMod][x])
            AddVehicleComponent(vehicleid, CarInfo[vehicleDBId][cMod][x]);
    }
    return 1;
}

function SpawnPlayerVehicle(playerid, vehicleDBId)
{
    if(!GetVehicleSpawnedState(vehicleDBId))
    {
        new
            vehicleGameID = AddStaticVehicleEx(CarInfo[vehicleDBId][cModel], CarInfo[vehicleDBId][cLocationx], CarInfo[vehicleDBId][cLocationy], CarInfo[vehicleDBId][cLocationz], CarInfo[vehicleDBId][cAngle], CarInfo[vehicleDBId][cColorOne], CarInfo[vehicleDBId][cColorTwo], -1, 0, VEH_TYPE_PERSONAL);

        Iter_Add(VehicleType<VEH_TYPE_PERSONAL>, vehicleGameID);
        VehicleSQL[vehicleGameID] = vehicleDBId;

        ChangeVehiclePaintjob(vehicleGameID, CarInfo[vehicleDBId][cPaintJ]);
        SetVehicleNumberPlate(vehicleGameID, CarInfo[vehicleDBId][cLicense]);
        
        SetVehicleHealth(vehicleGameID, CarInfo[vehicleDBId][cHealth] <= 300 ? 1000.0 : CarInfo[vehicleDBId][cHealth]);

        if(CarInfo[vehicleDBId][cHealth] <= 300)
            UpdateVehicleDamageStatus(vehicleGameID, 0, 0, 0, 0);
        else
            UpdateVehicleDamageStatus(vehicleGameID, CarInfo[vehicleDBId][cDamageStatus][0], CarInfo[vehicleDBId][cDamageStatus][1], CarInfo[vehicleDBId][cDamageStatus][2], CarInfo[vehicleDBId][cDamageStatus][3]);

        SetVehicleParamsForPlayer(vehicleGameID, playerid, 0, 0);

        CarInfo[vehicleDBId][cSpawnTime] = gettime() + MAX_VEHICLE_SPAWN_TIME;

        ModVehicle(vehicleGameID);

        AttachTextToVehicle(vehicleGameID);
        AttachNeonToVehicle(vehicleGameID);
        AttachSpoilerToVehicle(vehicleGameID);
    }
    else
    {
        new
            vehicleGameID = GetVehicleGameID(vehicleDBId);

        if(IsVehicleOccupied(vehicleGameID))
            return SCM(playerid, -1, "Your car is in use!");
        
        SetVehicleToRespawn(vehicleGameID);

        SetVehicleHealth(vehicleGameID, CarInfo[vehicleDBId][cHealth] <= 300 ? 1000.0 : CarInfo[vehicleDBId][cHealth]);

        if(CarInfo[vehicleDBId][cHealth] <= 300)
            UpdateVehicleDamageStatus(vehicleGameID, 0, 0, 0, 0);
        else
            UpdateVehicleDamageStatus(vehicleGameID, CarInfo[vehicleDBId][cDamageStatus][0], CarInfo[vehicleDBId][cDamageStatus][1], CarInfo[vehicleDBId][cDamageStatus][2], CarInfo[vehicleDBId][cDamageStatus][3]);

        SetVehicleParamsForPlayer(vehicleGameID, playerid, 0, 0);

        VehicleInfo[vehicleGameID][vehEngine] = 0;

        CarInfo[vehicleDBId][cSpawnTime] = gettime() + MAX_VEHICLE_SPAWN_TIME;

        SCMF(playerid, COLOR_GREY, "Vehiculul tau: model - %s (ID: %d) a fost respawnat.", aVehicleNames[CarInfo[vehicleDBId][cModel] - 400], vehicleGameID);
    }
    return 1;
}

function DestroyPlayerVehicle(vehicleGameID, vehicleDBId)
{
    mysql_format(SQL, gString, sizeof gString, "update `cars` set `KM` = '%f', `Fuel` = '%d', `Health` = '%f', `DamageStatus` = '%d %d %d %d', `Inscarprice` = '%d', `Insurancecar` = '%d', `Locationx` = '%f', `Locationy` = '%f', `Locationz` = '%f', `Angle` = '%f', `LastLocationx` = '%f', `LastLocationy` = '%f', `LastLocationz` = '%f', `LastAngle` = '%f' where `ID` = '%d';", CarInfo[vehicleDBId][cKM], CarInfo[vehicleDBId][cFuel], CarInfo[vehicleDBId][cHealth], CarInfo[vehicleDBId][cDamageStatus][0], CarInfo[vehicleDBId][cDamageStatus][1], CarInfo[vehicleDBId][cDamageStatus][2], CarInfo[vehicleDBId][cDamageStatus][3], CarInfo[vehicleDBId][cInscarprice], CarInfo[vehicleDBId][cInsurancecar], CarInfo[vehicleDBId][cLocationx], CarInfo[vehicleDBId][cLocationy], CarInfo[vehicleDBId][cLocationz], CarInfo[vehicleDBId][cAngle], CarInfo[vehicleDBId][cLastLocationx], CarInfo[vehicleDBId][cLastLocationy], CarInfo[vehicleDBId][cLastLocationz], CarInfo[vehicleDBId][cLastAngle], vehicleDBId);
    mysql_tquery(SQL, gString, "", "");

    VehicleSQL[vehicleGameID] = 0;
    DestroyVehicleEx(vehicleGameID);

    if(IsValidDynamicObject(VIPObject[vehicleGameID]))
        DestroyDynamicObject(VIPObject[vehicleGameID]);

    if(IsValidDynamicObject(NeonObject[0][vehicleGameID]) && IsValidDynamicObject(NeonObject[1][vehicleGameID]))
        DestroyDynamicObject(NeonObject[0][vehicleGameID]), DestroyDynamicObject(NeonObject[1][vehicleGameID]);

    if(IsValidDynamicObject(SpoilerObject[vehicleGameID]))
        DestroyDynamicObject(SpoilerObject[vehicleGameID]);

    return 1;
}

function WhenVehicleParked(playerid, vehicleDBId, vehicleGameID)
{
    DestroyPlayerVehicle(vehicleGameID, vehicleDBId);
    return SpawnPlayerVehicle(playerid, vehicleDBId);
}

YCMD:towcar(playerid, params[], help)
{
    mysql_format(SQL, gString, sizeof gString, "select * from `cars` where `Owner` = '%e';", PlayerInfo[playerid][pNormalName]);
    mysql_tquery(SQL, gString, "OnShowTowCar", "d", playerid);
    return 1;
}

function OnShowTowCar(playerid)
{
    if(!cache_num_rows())
        return SCM(playerid, COLOR_GREY, "You don't have any personal vehicles.");
    
    new i;

    gString = "";

    while(i < cache_num_rows())
    {
        new
            vehicleDBModel = cache_get_field_content_int(i, "Model"),
            vehicleDBId = cache_get_field_content_int(i, "ID");

        format(gString, sizeof gString, "%s%s%s\n", gString, aVehicleNames[vehicleDBModel - 400], GetVehicleSpawnedState(vehicleDBId) != 0 ? ("{0C370A}(spawned)") : ("{ff0000}(despawned)"));

        masinacars[playerid][i] = vehicleDBId;
        ++i;
    }
    Dialog_Show(playerid, DIALOG_TOWCAR, DIALOG_STYLE_LIST, "Personal Vehicles", gString, "Select", "Exit");

    tospawn[playerid] = 0;
    return 1;
}

Dialog:DIALOG_TOWCAR(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new
        vehicleDBId = masinacars[playerid][listitem];

    SpawnPlayerVehicle(playerid, vehicleDBId);
    return 1;
}

YCMD:findcar(playerid, params[], help)
{
    mysql_format(SQL, gString, sizeof gString, "select * from `cars` where `Owner` = '%e';", PlayerInfo[playerid][pNormalName]);
    mysql_tquery(SQL, gString, "OnShowFindCar", "d", playerid);
    return 1;
}

function OnShowFindCar(playerid)
{
    if(!cache_num_rows())
        return SCM(playerid, COLOR_GREY, "You don't have any personal vehicles.");
    
    new i;

    gString = "";

    while(i < cache_num_rows())
    {
        new
            vehicleDBModel = cache_get_field_content_int(i, "Model"),
            vehicleDBId = cache_get_field_content_int(i, "ID"),
            carId[12] = "";

        if(GetVehicleGameID(vehicleDBId))
            format(carId, 12, "(%d)", GetVehicleGameID(vehicleDBId));

        format(gString, sizeof gString, "%s%s {FFFFFF}%s %s\n", gString, GetVehicleSpawnedState(vehicleDBId) != 0 ? ("{0C370A}[spawned]") : ("{ff0000}[despawned]"), aVehicleNames[vehicleDBModel - 400], carId);

        masinacars[playerid][i] = vehicleDBId;
        ++i;
    }
    return Dialog_Show(playerid, DIALOG_CARFIND, DIALOG_STYLE_LIST, "Find Vehicles", gString, "Select", "Exit");
}

Dialog:DIALOG_CARFIND(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new
        vehicleDBId = masinacars[playerid][listitem],
        vehicleGameID = GetVehicleGameID(vehicleDBId);

    if(!GetVehicleSpawnedState(vehicleDBId))
        return SCM(playerid, COLOR_GREY, "This vehicle isn't spawned!");

    if(s_PlayerInfo[playerid][pSCP])
        return SCM(playerid, -1, "Detii deja un checkpoint activ!");

    new
        Float: vPos[3];
    
    s_PlayerInfo[playerid][pSCP] = 1;
    GetVehiclePos(vehicleGameID, vPos[0], vPos[1], vPos[2]);
    return SetPlayerCheckpoint(playerid, vPos[0], vPos[1], vPos[2], 4);
}

YCMD:v(playerid, params[], help)
{
    mysql_format(SQL, gString, sizeof gString, "select * from `cars` where `Owner` = '%e' order by `id` asc;", PlayerInfo[playerid][pNormalName]);
    mysql_tquery(SQL, gString, "OnShowCars", "d", playerid);
    return 1;
}

function OnShowCars(playerid)
{
    if(!cache_num_rows())
        return SCM(playerid, COLOR_GREY, "You don't have any personal vehicles.");
    
    new
        vehicles, carid[12];

    tospawn[playerid] = 0;
    
    gString = "Vehicul\tStatus\tID\tTimp despawnare\n";
    while(vehicles < cache_num_rows())
    {
        new
            vehicleDBModel = cache_get_field_content_int(vehicles, "Model"),
            vehicleDBId = cache_get_field_content_int(vehicles, "ID"),
            vehicleGameID = GetVehicleGameID(vehicleDBId);

        // ne bagam pl in samp si in complicatii
        if(!strmatch(CarInfo[vehicleDBId][cOwner], PlayerInfo[playerid][pNormalName]))
            format(CarInfo[vehicleDBId][cOwner], MAX_PLAYER_NAME, PlayerInfo[playerid][pNormalName]);

        format(carid, sizeof carid, vehicleGameID ? ("%d") : ("not spawned"), vehicleGameID);
        format(gString, sizeof gString, "%s%s\t%s\t%s\t%s\n", gString, aVehicleNames[vehicleDBModel - 400], GetVehicleSpawnedState(vehicleDBId) != 0 ? ("{0C370A}spawned") : ("{ff0000}despawned"), carid, vehicleGameID == 0 ? ("not spawned") : IsVehicleOccupied(vehicleGameID) ? ("in use") : CarInfo[vehicleDBId][cSpawnTime] - gettime() <= 20 ? ("soon") : CalculeazaTimp2(CarInfo[vehicleDBId][cSpawnTime] - gettime()));

        masinacars[playerid][vehicles] = vehicleDBId;

        ++vehicles;
    }
    return Dialog_Show(playerid, DIALOG_CARMANAGE, DIALOG_STYLE_TABLIST_HEADERS, "Vehicles", gString, "Select", "Exit");
}

Dialog:DIALOG_CARMANAGE(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    tospawn[playerid] = masinacars[playerid][listitem];
    
    Dialog_Show(playerid, DIALOG_CARPANEL, DIALOG_STYLE_LIST, "Vehicle menu", "{FFFFFF}Vehicle info\nTow vehicle (park location)\nTow vehicle (last known location)\nChange plate\nLocate vehicle\nDebug vehicle (unstuck)\nReissue insurance\nVehicle upgrades\nSell vehicle (to Dealership)\nDespawn Vehicle", "Select", "Cancel");
    return 1;
}

Dialog:DIALOG_CARPANEL(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new
        vehicleDBId = tospawn[playerid];

    switch(listitem)
    {
        case 0:
        {
            format(gString, sizeof gString, "Vehicle Model: %s\nDistance Traveled: %.0f kilometers\nVehicle Age: %d days\nVehicle Fuel Tank: %d\nVehicle VIP: %s\nTop speed: %d km/h", aVehicleNames[CarInfo[vehicleDBId][cModel] - 400], CarInfo[vehicleDBId][cKM], TSToDays(CarInfo[vehicleDBId][cBuyTime]), CarInfo[vehicleDBId][cFuelTank], CarInfo[vehicleDBId][cVIP] ? ("Yes") : ("No"), GetVehicleMaxSpeed(CarInfo[vehicleDBId][cModel]));
            Dialog_Show(playerid, 0, DIALOG_STYLE_MSGBOX, "{909CE7}your personal cars", gString, "Ok", "");
        }
        case 1:
        {
            SpawnPlayerVehicle(playerid, vehicleDBId);
            SCM(playerid, COLOR_GREY, "Vehiculul tau a fost spawnat cu succes.");
        }
        case 2:
        {
            if(!GetVehicleSpawnedState(vehicleDBId))
            {
                new
                    vehicleGameID;
                
                if(!CarInfo[vehicleDBId][cLastLocationx] && !CarInfo[vehicleDBId][cLastLocationy] && !CarInfo[vehicleDBId][cLastLocationz])
                {
                    SCM(playerid, COLOR_GREY, "[ANTI ABUZ] Vehiculul tau a fost spawnat la locatia sa nativa, deoarece acesta a explodat.");
                
                    vehicleGameID = AddStaticVehicleEx(CarInfo[vehicleDBId][cModel], CarInfo[vehicleDBId][cLocationx], CarInfo[vehicleDBId][cLocationy], CarInfo[vehicleDBId][cLocationz], CarInfo[vehicleDBId][cAngle], CarInfo[vehicleDBId][cColorOne], CarInfo[vehicleDBId][cColorTwo], -1, 0, VEH_TYPE_PERSONAL);
                }
                else
                    vehicleGameID = AddStaticVehicleEx(CarInfo[vehicleDBId][cModel], CarInfo[vehicleDBId][cLastLocationx], CarInfo[vehicleDBId][cLastLocationy], CarInfo[vehicleDBId][cLastLocationz], CarInfo[vehicleDBId][cLastAngle], CarInfo[vehicleDBId][cColorOne], CarInfo[vehicleDBId][cColorTwo], -1, 0, VEH_TYPE_PERSONAL);

                VehicleSQL[vehicleGameID] = vehicleDBId;

                ChangeVehiclePaintjob(vehicleGameID, CarInfo[vehicleDBId][cPaintJ]);
                SetVehicleNumberPlate(vehicleGameID, CarInfo[vehicleDBId][cLicense]);
                
                SetVehicleHealth(vehicleGameID, CarInfo[vehicleDBId][cHealth] <= 300 ? 1000.0 : CarInfo[vehicleDBId][cHealth]);

                if(CarInfo[vehicleDBId][cHealth] <= 300)
                    UpdateVehicleDamageStatus(vehicleGameID, 0, 0, 0, 0);
                else
                    UpdateVehicleDamageStatus(vehicleGameID, CarInfo[vehicleDBId][cDamageStatus][0], CarInfo[vehicleDBId][cDamageStatus][1], CarInfo[vehicleDBId][cDamageStatus][2], CarInfo[vehicleDBId][cDamageStatus][3]);

                SetVehicleParamsForPlayer(vehicleGameID, playerid, 0, 0);

                CarInfo[vehicleDBId][cSpawnTime] = gettime() + MAX_VEHICLE_SPAWN_TIME;
                VehicleInfo[vehicleGameID][vehFuel] = CarInfo[vehicleDBId][cFuel];

                ModVehicle(vehicleGameID);

                AttachTextToVehicle(vehicleGameID);
                AttachNeonToVehicle(vehicleGameID);
                AttachSpoilerToVehicle(vehicleGameID);
            }
            else
            {
                new
                    vehicleGameID = GetVehicleGameID(vehicleDBId);

                if(IsVehicleOccupied(vehicleGameID))
                    return SCM(playerid, -1, "Your car is in use!");
                
                SetVehicleToRespawn(vehicleGameID);

                SetVehicleHealth(vehicleGameID, CarInfo[vehicleDBId][cHealth] <= 300 ? 1000.0 : CarInfo[vehicleDBId][cHealth]);

                if(!CarInfo[vehicleDBId][cLastLocationx] && !CarInfo[vehicleDBId][cLastLocationy] && !CarInfo[vehicleDBId][cLastLocationz])
                {
                    SCM(playerid, COLOR_GREY, "[ANTI ABUZ] Vehiculul tau a fost spawnat la locatia sa nativa, deoarece acesta a explodat.");
                
                    SetVehiclePos(vehicleGameID, CarInfo[vehicleDBId][cLocationx], CarInfo[vehicleDBId][cLocationy], CarInfo[vehicleDBId][cLocationz]);
                }
                else
                {
                    SCMF(playerid, COLOR_WHITE, "Vehiculul tau: model - %s (ID: %d) a fost respawnat in ultima locatie cunoscuta.", aVehicleNames[CarInfo[vehicleDBId][cModel] - 400], vehicleGameID);
                    
                    SetVehiclePos(vehicleGameID, CarInfo[vehicleDBId][cLastLocationx], CarInfo[vehicleDBId][cLastLocationy], CarInfo[vehicleDBId][cLastLocationz]);
                }

                if(CarInfo[vehicleDBId][cHealth] <= 300)
                    UpdateVehicleDamageStatus(vehicleGameID, 0, 0, 0, 0);
                else
                    UpdateVehicleDamageStatus(vehicleGameID, CarInfo[vehicleDBId][cDamageStatus][0], CarInfo[vehicleDBId][cDamageStatus][1], CarInfo[vehicleDBId][cDamageStatus][2], CarInfo[vehicleDBId][cDamageStatus][3]);

                SetVehicleParamsForPlayer(vehicleGameID, playerid, 0, 0);

                VehicleInfo[vehicleGameID][vehEngine] = 0;
                CarInfo[vehicleDBId][cSpawnTime] = gettime() + MAX_VEHICLE_SPAWN_TIME;
                VehicleInfo[vehicleGameID][vehFuel] = CarInfo[vehicleDBId][cFuel];
            }
        }
        case 3:
        {
            if(!GetVehicleSpawnedState(vehicleDBId))
                return SCM(playerid, COLOR_GREY, "Vehiculul tau nu este spawnat!");

            Dialog_Show(playerid, DIALOG_CARPLATE, DIALOG_STYLE_INPUT, "{FFFFFF}Car Plate", "{FFFFFF}Introduceti numarul de inmatriculare dorit:", "Introdu", "Anuleaza");
        }
        case 4:
        {
            if(!GetVehicleSpawnedState(vehicleDBId))
                return SCM(playerid, COLOR_GREY, "Vehiculul tau nu este spawnat!");

            if(s_PlayerInfo[playerid][pSCP])
                return showActiveCheckpointDialog(playerid);

            new
                Float: vPos[3];
            
            GetVehiclePos(GetVehicleGameID(vehicleDBId), vPos[0], vPos[1], vPos[2]);
            SetPlayerCheckpoint(playerid, vPos[0], vPos[1], vPos[2], 4);

            s_PlayerInfo[playerid][pSCP] = 1;
        }
        case 5:
        {
            new
                vehicleGameID = GetVehicleGameID(vehicleDBId);

            if(IsVehicleOccupied(vehicleGameID))
                return SCM(playerid, -1, "Your car is in use!");

            Dialog_Show(playerid, DIALOG_CARUNSTUCK, DIALOG_STYLE_MSGBOX, "Unstuck vehicle", "Aceasta optiune a fost creata pentru cei ce nu-si pot gasi vehiculul folosind </findcar> sau nu il pot accesa fiindca este spawnat gresit.\nVehiculul tau va fi mutat intr-o locatie facila.\n\nEsti sigur ca doresti asta?", "Da", "Nu");
        }
        case 6:
        {
            if(!GetVehicleSpawnedState(vehicleDBId))
                return SCM(playerid, -1, "Your vehicle isn't spawned.");

            if(CarInfo[vehicleDBId][cInsurancecar] == 5)
                return SCM(playerid, COLOR_GREY, "Masina ta deja are 5 puncte de asigurare!");

            format(gString, sizeof gString, "Introdu cate puncte de asigurare doresti sa cumperi in casuta de mai jos.\nUn punct de asigurare costa $%s.\nUn vehicul poate avea maxim 5 puncte de asigurare.\nVehiculul tau are %d/5 puncte de asigurare.", FormatNumber(CarInfo[vehicleDBId][cInscarprice]), CarInfo[vehicleDBId][cInsurancecar]);
            Dialog_Show(playerid, DIALOG_BUYCARINS, DIALOG_STYLE_INPUT, "Plateste Asigurarea", gString, "Ok", "Cancel");
        }
        case 7:
        {
            if(!GetVehicleSpawnedState(vehicleDBId))
                return SCM(playerid, -1, "Your vehicle needs to be spawned to use this menu option.");
        }
        case 8:
        {
            if(!GetVehicleSpawnedState(vehicleDBId))
                return SCM(playerid, -1, "Your vehicle needs to be spawned to use this menu option.");
        
            mysql_format(SQL, gString, sizeof gString, "select * from `dealer_cars` where `ds_vModel` = '%d';", CarInfo[vehicleDBId][cModel]);
            mysql_tquery(SQL, gString, "WhenPlayerSellVehicleToDS", "dd", playerid, vehicleDBId);
        }
        case 9:
        {
            if(!GetVehicleSpawnedState(vehicleDBId))
                return SCM(playerid, -1, "Vehiculul tau nu este spawnat pe server.");

            new
                vehicleGameID = GetVehicleGameID(vehicleDBId);

            if(IsVehicleOccupied(vehicleGameID))
                return SCM(playerid, -1, "Your car is in use!");

            if(CarInfo[vehicleDBId][cSpawnTime] - gettime() >= MAX_VEHICLE_SPAWN_TIME-60)
                return SCM(playerid, -1, "Vehiculul tau nu poate fi despawnat deoarece a fost utilizat in ultimul minut.");

            SCMF(playerid, -1, "Your vehicle %s (model: %d) was despawned.", aVehicleNames[CarInfo[vehicleDBId][cModel] - 400], CarInfo[vehicleDBId][cModel]);
            DestroyPlayerVehicle(vehicleGameID, vehicleDBId);
        }
    }
    return 1;
}

function WhenPlayerSellVehicleToDS(playerid, vehicleDBId)
{
    new
        carValue = 0;

    if(cache_num_rows())
        carValue = cache_get_field_content_int(0, "ds_vPrice")/2;

    SetPVarInt(playerid, "vehicle_sell_value", carValue);

    format(gString, sizeof gString, "Esti sigur ca vrei sa-ti vinzi vehiculul %s (model:%d) cu %d zile, %.0f KM%s%s?\nVei primi suma de $%s pentru vehiculul tau.", aVehicleNames[CarInfo[vehicleDBId][cModel] - 400], CarInfo[vehicleDBId][cModel], TSToDays(CarInfo[vehicleDBId][cBuyTime]), CarInfo[vehicleDBId][cKM], CarInfo[vehicleDBId][cVIP] ? (", cu VIP") : (""), CarInfo[vehicleDBId][cNeon] ? (" si Neon") : (""), FormatNumber(carValue));
    Dialog_Show(playerid, DIALOG_SELLCAR_TODS, DIALOG_STYLE_MSGBOX, "Sell vehicle", gString, "Sell", "Cancel");
    return 1;
}

Dialog:DIALOG_SELLCAR_TODS(playerid, response, listitem, inputtext[])
{
    if(!response)
        return DeletePVar(playerid, "vehicle_sell_value");

    new
        vehicleDBId = tospawn[playerid];

    new
        carValue = GetPVarInt(playerid, "vehicle_sell_value");

    SCMF(playerid, -1, "You sold your car %s to the Dealership for $%s!", aVehicleNames[CarInfo[vehicleDBId][cModel] - 400], FormatNumber(carValue));
    //PlayerInfo[playerid][pAccount] += carValue;
    GivePlayerCash(playerid, carValue);
    // de facut
    //insertPlayerLog(playerid, 0, "%s [userid: %d] sold vehicle %s [carid: %d] to Dealership for $%s.", PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID], aVehicleNames[CarInfo[vehicleDBId][cModel] - 400], vehicleDBId, FormatNumber(carValue));
    ////insertVehicleLog(vehicleDBId, playerid, "%s sold vehicle %s [carid: %d] to Dealership for $%s.", PlayerInfo[playerid][pNormalName], aVehicleNames[CarInfo[vehicleDBId][cModel] - 400], vehicleDBId, FormatNumber(carValue));

    DestroyPlayerVehicle(GetVehicleGameID(vehicleDBId), vehicleDBId);

    mysql_format(SQL, gString, sizeof gString, "delete from `cars` where `ID` = '%d';", vehicleDBId);
    mysql_tquery(SQL, gString, "", "");

    return 1;
}

Dialog:DIALOG_NEONMENU(playerid, response, listitem, inputtext[])
{
    if(!response)
        return DeletePVar(playerid, "neon_action");

    new
        vehicleDBId = tospawn[playerid];

    switch(listitem)
    {
        case 0:
        {
            if(!CarInfo[vehicleDBId][cNeon])
                return 1;

            Dialog_Show(playerid, DIALOG_NEONMENU_ACTION, DIALOG_STYLE_MSGBOX, "Neon remove", "Do you want to remove currently neon from this car?\nThe action is irreversible.", "Yes", "No");
            SetPVarInt(playerid, "neon_action", 1);
        }
        case 1:
        {
            new
                neonString[144];

            neonString = "Color\tAvailable\n";

            for(new i = 1; i < 7; ++i)
                format(neonString, sizeof neonString, "%s%s\t%d\n", neonString, vehicleNeonName[i], PlayerInfo[playerid][pNeons][i-1]);

            Dialog_Show(playerid, DIALOG_NEONMENU_ACTION, DIALOG_STYLE_TABLIST_HEADERS, "Neon", neonString, "Apply", "Cancel");
            SetPVarInt(playerid, "neon_action", 2);
        }
    }
    return 1;
}

Dialog:DIALOG_NEONMENU_ACTION(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new
        vehicleDBId = tospawn[playerid], vehicleGameID = GetVehicleGameID(vehicleDBId);

    switch(GetPVarInt(playerid, "neon_action"))
    {
        case 1:
        {
            if(IsValidDynamicObject(NeonObject[0][vehicleGameID]) && IsValidDynamicObject(NeonObject[1][vehicleGameID]))
                DestroyDynamicObject(NeonObject[0][vehicleGameID]), DestroyDynamicObject(NeonObject[1][vehicleGameID]);

            //insertVehicleLog(vehicleDBId, playerid, "%s removed vehicle %s [carid: %d] neon %s.", PlayerInfo[playerid][pNormalName], aVehicleNames[CarInfo[vehicleDBId][cModel] - 400], vehicleDBId, vehicleNeonName[CarInfo[vehicleDBId][cNeon]]);

            SCM(playerid, -1, "You successfully removed the neon from this vehicle.");

            CarInfo[vehicleDBId][cNeon] = 0;
        }
        case 2:
        {
            if(CarInfo[vehicleDBId][cNeon])
                return SCM(playerid, -1, "You already have an attached neon on this vehicle.");

            if(!PlayerInfo[playerid][pNeons][listitem])
                return SCM(playerid, -1, "You don't own this kind of neon.");

            SCMF(playerid, -1, "You attached a %s Neon on this car.", vehicleNeonName[listitem+1]);

            CarInfo[vehicleDBId][cNeon] = listitem+1;
            AttachNeonToVehicle(vehicleGameID);

            //insertVehicleLog(vehicleDBId, playerid, "%s attached to vehicle %s [carid: %d] neon %s.", PlayerInfo[playerid][pNormalName], aVehicleNames[CarInfo[vehicleDBId][cModel] - 400], vehicleDBId, vehicleNeonName[listitem+1]);
        }
    }
    mysql_format(SQL, gString, sizeof gString, "update `users` set `Neons` = '%d %d %d %d %d %d' where `id` = '%d';", PlayerInfo[playerid][pNeons][0],PlayerInfo[playerid][pNeons][1], PlayerInfo[playerid][pNeons][2], PlayerInfo[playerid][pNeons][3], PlayerInfo[playerid][pNeons][4], PlayerInfo[playerid][pNeons][5], PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString, "", "");

    mysql_format(SQL, gString, sizeof gString, "update `cars` set `Neon` = '%d' where `ID` = '%d';", CarInfo[vehicleDBId][cNeon], vehicleDBId);
    mysql_tquery(SQL, gString, "", "");

    return DeletePVar(playerid, "neon_action");
}


Dialog:DIALOG_CARUNSTUCK(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new
        vehicleDBId = tospawn[playerid];

    if(!GetVehicleSpawnedState(vehicleDBId))
    {
        SCM(playerid, COLOR_YELLOW, "Masina ta a fost mutata intr-o parcare din LV. Pentru a o gasi utilizeaza functia de localizare.");

        new
            carParkPosition = RandomEx(0, sizeof unstuckLVParkPos);

        CarInfo[vehicleDBId][cLocationx] = unstuckLVParkPos[carParkPosition][0];
        CarInfo[vehicleDBId][cLocationy] = unstuckLVParkPos[carParkPosition][1];
        CarInfo[vehicleDBId][cLocationz] = unstuckLVParkPos[carParkPosition][2];
        CarInfo[vehicleDBId][cAngle] = 91.4375;
    }
    else
    {
        new
            Float: playerPosition[3], carParkPosition = RandomEx(0, sizeof unstuckLocPos), Float: distance;

        GetPlayerPos(playerid, playerPosition[0], playerPosition[1], playerPosition[2]);
        distance = GetDistanceBetweenPoints(playerPosition[0], playerPosition[1], playerPosition[2], unstuckLocPos[carParkPosition][0], unstuckLocPos[carParkPosition][1], unstuckLocPos[carParkPosition][2]);

        CarInfo[vehicleDBId][cLocationx] = unstuckLocPos[carParkPosition][0];
        CarInfo[vehicleDBId][cLocationy] = unstuckLocPos[carParkPosition][1];
        CarInfo[vehicleDBId][cLocationz] = unstuckLocPos[carParkPosition][2];

        SCMF(playerid, COLOR_YELLOW, "Vehicle unstucked. (new location: %s). Distance: %.0fm.", unstuckLocName[carParkPosition], distance);
        SCM(playerid, COLOR_YELLOW, "Follow the red dot on your minimap to get to your vehicle.");

        SetVehiclePos(GetVehicleGameID(vehicleDBId), unstuckLocPos[carParkPosition][0], unstuckLocPos[carParkPosition][1], unstuckLocPos[carParkPosition][2]);
        SetPlayerCheckpoint(playerid, unstuckLocPos[carParkPosition][0], unstuckLocPos[carParkPosition][1], unstuckLocPos[carParkPosition][2], 4.0);
        
        s_PlayerInfo[playerid][pSCP] = 1;
    }
    mysql_format(SQL, gString, sizeof gString, "update `cars` set `Locationx` = '%f', `Locationy` = '%f', `Locationz` = '%f', `Angle` = '%f' where `ID` = '%d';", CarInfo[vehicleDBId][cLocationx], CarInfo[vehicleDBId][cLocationy], CarInfo[vehicleDBId][cLocationz], CarInfo[vehicleDBId][cAngle], vehicleDBId);
    mysql_tquery(SQL, gString, "", "");
    return 1;
}

Dialog:DIALOG_CARPLATE(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    if(strlen(inputtext) > 12)
        return SCM(playerid, -1, "Invalid carplate size.");

    new
        vehicleDBId = tospawn[playerid],
        vehicleGameID = GetVehicleGameID(vehicleDBId);

    GivePlayerMoney(playerid, -10000);
    GameTextForPlayer(playerid, "~b~~h~~h~-10000", 5000, 1);

    strmid(CarInfo[vehicleDBId][cLicense], inputtext, 0, strlen(inputtext), 999);
    SetVehicleNumberPlate(vehicleGameID, inputtext);

    mysql_format(SQL, gString, sizeof gString, "update `cars` set `License` = '%s' where `ID` = '%d';", CarInfo[vehicleDBId][cLicense], vehicleDBId);
    mysql_tquery(SQL, gString, "", "");

    return 1;
}

Dialog:DIALOG_BUYCARINS(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new
        carins = strval(inputtext), vehicleDBId = tospawn[playerid];

    if(carins <= 0)
        return 1;

    if(CarInfo[vehicleDBId][cInsurancecar] + carins > 5)
        return SCM(playerid, COLOR_GREY, "Nu puteti cumpara atatea puncte de asigurare! Un vehicul poate avea maxim 5 puncte de asigurare.");

    SCMF(playerid, -1, "You have bought %d insurance points for your vehicle.", carins);

    CarInfo[vehicleDBId][cInsurancecar] += carins;
    GivePlayerMoney(playerid, -carins * CarInfo[vehicleDBId][cInscarprice]);

    return 1;
}

Dialog:DIALOG_PAYCARINS(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        SCM(playerid, COLOR_GREY, "Nu puteti conduce acest vehicul fara a ii plati asigurarea.");
        return RemovePlayerFromVehicle(playerid);
    }

    new vehicleDBId = VehicleSQL[GetPlayerVehicleID(playerid)];

    SCMF(playerid, -1, "You have bought an insurance point for your vehicle. You have paid $%s.", FormatNumber(CarInfo[vehicleDBId][cInscarprice]));

    CarInfo[vehicleDBId][cInsurancecar] += 1;
    GivePlayerMoney(playerid, -CarInfo[vehicleDBId][cInscarprice]);

    return 1;
}

function EditVIPVehicleText(playerid, vehicleGameID)
{
    new
        vehicleDBId = VehicleSQL[vehicleGameID], Float:newpos[6];

    GetVehicleObjectPositionWorld(GetPlayerVehicleID(playerid), CarInfo[vehicleDBId][cVIPPos][0], CarInfo[vehicleDBId][cVIPPos][1], CarInfo[vehicleDBId][cVIPPos][2], CarInfo[vehicleDBId][cVIPPos][3], CarInfo[vehicleDBId][cVIPPos][4], CarInfo[vehicleDBId][cVIPPos][5], newpos[0], newpos[1], newpos[2], newpos[3], newpos[4], newpos[5]);

    DestroyDynamicObject(VIPObject[vehicleGameID]);

    VIPObject[vehicleGameID] = CreateDynamicObject(19327, newpos[0], newpos[1], newpos[2], newpos[3], newpos[4], newpos[5]);
    
    format(gString, sizeof gString, "{%s}%s", CarInfo[vehicleDBId][cVIPColor], CarInfo[vehicleDBId][cVIPText]);
    
    SetDynamicObjectMaterialText(VIPObject[vehicleGameID], 0, gString, 140, "Arial", 65, 0, -1, 0, 1);
    EditDynamicObject(playerid, VIPObject[vehicleGameID]);

    TogglePlayerControllable(playerid, 0);

    return SetPVarInt(playerid, "edit_object_vip", 1);
}

function AttachTextToVehicle(vehicleGameID)
{
    new
        vehicleDBId = VehicleSQL[vehicleGameID];

    if(!CarInfo[vehicleDBId][cVIP])
        return 1;

    format(gString, sizeof gString, "{%s}%s", CarInfo[vehicleDBId][cVIPColor], CarInfo[vehicleDBId][cVIPText]);

    if(!IsValidDynamicObject(VIPObject[vehicleGameID]))
        VIPObject[vehicleGameID] = CreateDynamicObject(19327, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    
    SetDynamicObjectMaterialText(VIPObject[vehicleGameID], 0, gString, 140, "Arial", 65, 0, -1, 0, 1);
    AttachDynamicObjectToVehicle(VIPObject[vehicleGameID], vehicleGameID, CarInfo[vehicleDBId][cVIPPos][0], CarInfo[vehicleDBId][cVIPPos][1], CarInfo[vehicleDBId][cVIPPos][2], CarInfo[vehicleDBId][cVIPPos][3], CarInfo[vehicleDBId][cVIPPos][4], CarInfo[vehicleDBId][cVIPPos][5]);  
    return 1;
}

function AttachNeonToVehicle(vehicleGameID)
{
    new
        vehicleDBId = VehicleSQL[vehicleGameID];

    if(!CarInfo[vehicleDBId][cNeon])
        return 1;

    if(!IsValidDynamicObject(NeonObject[0][vehicleGameID]) && !IsValidDynamicObject(NeonObject[1][vehicleGameID]))
    {
        new
            neonTypeId;

        switch(CarInfo[vehicleDBId][cNeon])
        {
            case 1: neonTypeId = 18647;
            case 2: neonTypeId = 18650;
            case 3: neonTypeId = 18648;
            case 4: neonTypeId = 18649;
            case 5: neonTypeId = 18651;
            case 6: neonTypeId = 18652;
        }
        NeonObject[0][vehicleGameID] = CreateDynamicObject(neonTypeId, 0, 0, 0, 0, 0, 0);
        NeonObject[1][vehicleGameID] = CreateDynamicObject(neonTypeId, 0, 0, 0, 0, 0, 0);

        AttachDynamicObjectToVehicle(NeonObject[0][vehicleGameID], vehicleGameID, -0.8, 0.0, -0.50, 0.0, 0.0, 0.0);
        AttachDynamicObjectToVehicle(NeonObject[1][vehicleGameID], vehicleGameID, 0.8, 0.0, -0.50, 0.0, 0.0, 0.0);
    }
    return 1;
}

function AttachSpoilerToVehicle(vehicleGameID)
{
    new
        vehicleDBId = VehicleSQL[vehicleGameID];

    if(!CarInfo[vehicleDBId][cSpoiler])
        return 1;

    format(gString, sizeof gString, "{%s}%s", CarInfo[vehicleDBId][cVIPColor], CarInfo[vehicleDBId][cVIPText]);

    if(!IsValidDynamicObject(SpoilerObject[vehicleGameID]))
        SpoilerObject[vehicleGameID] = CreateDynamicObject(1002, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    
    AttachDynamicObjectToVehicle(SpoilerObject[vehicleGameID], vehicleGameID, 0.000000, -2.299999, 0.300000, 0.000000, 0.000000, 0.000000); // infernus
    return 1;
}

// == COMMANDS ==
YCMD:vipwheels(playerid, params[], help)
{
    if(!IsPlayerInAnyVehicle(playerid))
        return SCM(playerid, -1, "Nu te afli intr-un vehicul.");

    new
        vehicleGameID = GetPlayerVehicleID(playerid);

    if(!VehicleSQL[GetPlayerVehicleID(playerid)])
        return SCM(playerid, COLOR_GREY, "Nu te afli intr-un vehicul personal.");

    if(!strmatch(PlayerInfo[playerid][pNormalName], CarInfo[VehicleSQL[vehicleGameID]][cOwner]))
        return SCM(playerid, COLOR_GREY, "Nu sunteti proprietarul vehiculului.");

    if(!CarInfo[VehicleSQL[vehicleGameID]][cVIP])
        return SCM(playerid, -1, "Acest vehicul nu este unul de tip VIP!");

    new
        wheelType[12];

    if(sscanf(params, "s[12]", wheelType))
    {
        sendSyntax(playerid, "/vipwheels [wheel type]");
        return SCM(playerid, COLOR_GREY, "Wheels: Switch, Dollar, Trance");
    }

    if(strcmp(wheelType, "switch", true) == 0)
    {
        AddVehicleComponent(vehicleGameID, 1080);
        SaveComponent(vehicleGameID, 1080);
    }
    else if(strcmp(wheelType, "dollar", true) == 0)
    {
        AddVehicleComponent(vehicleGameID, 1083);
        SaveComponent(vehicleGameID, 1083);
    }
    else if(strcmp(wheelType, "trance", true) == 0)
    {
        AddVehicleComponent(vehicleGameID, 1084);
        SaveComponent(vehicleGameID, 1084);
    }
    else return SCM(playerid, -1, "Acest model de roti este necunoscut!");

    SCM(playerid, -1, "Rotile vehiculului tau au fost schimbate cu succes!");

    return 1;
}

YCMD:vipname(playerid, params[], help)
{
    if(!IsPlayerInAnyVehicle(playerid))
        return SCM(playerid, -1, "You can't use this command because you're not in your vehicle.");

    new
        vehicleid = GetPlayerVehicleID(playerid);

    if(strcmp(PlayerInfo[playerid][pNormalName], CarInfo[VehicleSQL[vehicleid]][cOwner], false) == 1 || strcmp(PlayerInfo[playerid][pNormalName], CarInfo[VehicleSQL[vehicleid]][cOwner], true) == 0 && CarInfo[VehicleSQL[vehicleid]][cVIP] < 1)
        return SendSplitMessage(playerid, -1, "Nu poti folosi aceasta comanda deoarece nu te afli intr-un vehicul personal detinut de tine sau acest vehicul nu este unul de tip VIP.");

    if(VehicleInfo[vehicleid][vehEngine])
        return SCM(playerid, COLOR_GREY, "Motorul vehiculului tau trebuie sa fie oprit pentru accesarea acestei comenzi.");

    new
        vehicleDBId = VehicleSQL[vehicleid];

    format(gString, sizeof gString, "Option\tInfo\nText color\tcurrent: {%s}%s\nText\tcurrent: %s\nText position\nReset to default", CarInfo[vehicleDBId][cVIPColor], CarInfo[vehicleDBId][cVIPColor], CarInfo[vehicleDBId][cVIPText]);

    Dialog_Show(playerid, DIALOG_VIPMENU, DIALOG_STYLE_TABLIST_HEADERS, "VIP Menu:", gString, "Select", "Close");

    return 1;
}

Dialog:DIALOG_VIPMENU(playerid, response, listitem, inputtext[])
{
    if(!response)
        return DeletePVar(playerid, "vip_menu_selected");

    switch(listitem)
    {
        case 0:
            Dialog_Show(playerid, DIALOG_VIPMENU_ASSETS, DIALOG_STYLE_INPUT, "VIP Text Color:", "Please enter the HTML code for the text color (default FFFFFF):", "Change", "Cancel");
        case 1:
            Dialog_Show(playerid, DIALOG_VIPMENU_ASSETS, DIALOG_STYLE_INPUT, "VIP Text:", "Please enter your desired text (1-12 characters):", "Change", "Cancel");
        case 2:
        {
            SCM(playerid, -1, "You started to edit your vehicle text offsets. Use your mouse to do it.");
            EditVIPVehicleText(playerid, GetPlayerVehicleID(playerid));
        }
        case 3:
        {
            Dialog_Show(playerid, DIALOG_VIPMENU_ASSETS, DIALOG_STYLE_MSGBOX, "VIP Text:", "Are you sure you want to restore your vehicle's text to default settings?", "Yes", "No");
        }
    }
    if(listitem == 0 || listitem == 1 || listitem == 3)
        SetPVarInt(playerid, "vip_menu_selected", listitem);

    return 1;
}

Dialog:DIALOG_VIPMENU_ASSETS(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    if(!IsPlayerInAnyVehicle(playerid))
        return 1;

    new
        vehicleGameID = GetPlayerVehicleID(playerid), vehicleDBId = VehicleSQL[GetPlayerVehicleID(playerid)];

    switch(GetPVarInt(playerid, "vip_menu_selected"))
    {
        case 0:
        {
            if(strlen(inputtext) < 6 || strlen(inputtext) > 6)
                return SCM(playerid, -1, "Invalid color.");

            for(new i; i < strlen(inputtext); ++i)
            {
                if((inputtext[i] >= 'A' && inputtext[i] <= 'F') || (inputtext[i] >= 'a' && inputtext[i] <= 'f') || (inputtext[i] >= '0' && inputtext[i] <= '9'))
                {
                    SCMF(playerid, -1, "Server: You changed your vehicle vip text color to: {%s}%s", inputtext, inputtext);
                    format(CarInfo[vehicleDBId][cVIPColor], 12, inputtext);
                    break;
                }
                else return SCM(playerid, -1, "Cod de culoare invalid!");
            }
            format(gString, sizeof gString, "{%s}%s", CarInfo[vehicleDBId][cVIPColor], CarInfo[vehicleDBId][cVIPText]);
            SetDynamicObjectMaterialText(VIPObject[vehicleGameID], 0, gString, 140, "Arial", 65, 0, -1, 0, 1);
        }
        case 1:
        {
            if(strlen(inputtext) < 1 || strlen(inputtext) > 12)
                return SCM(playerid, -1, "Invalid text.");

            SCMF(playerid, COLOR_GREY, "Your vehicle text have been change in: {FFFFFF}%s", inputtext);
            format(CarInfo[vehicleDBId][cVIPText], 14, inputtext);

            format(gString, sizeof gString, "{%s}%s", CarInfo[vehicleDBId][cVIPColor], CarInfo[vehicleDBId][cVIPText]);
            SetDynamicObjectMaterialText(VIPObject[vehicleGameID], 0, gString, 140, "Arial", 65, 0, -1, 0, 1);
        }
        case 3:
        {
            SCM(playerid, -1, "Your vehicle text have been reseted.");

            new
                Float: x, Float:y, Float:z;

            GetVehiclePos(vehicleGameID, x, y, z);
            GetVehicleObjectPositionOffset(GetPlayerVehicleID(playerid), x, y, z, 0.0, 0.0, 0.0, CarInfo[vehicleDBId][cVIPPos][0], CarInfo[vehicleDBId][cVIPPos][1], CarInfo[vehicleDBId][cVIPPos][2], CarInfo[vehicleDBId][cVIPPos][3], CarInfo[vehicleDBId][cVIPPos][4], CarInfo[vehicleDBId][cVIPPos][5]);

            format(gString, sizeof gString, "{%s}%s", CarInfo[vehicleDBId][cVIPColor], CarInfo[vehicleDBId][cVIPText]);
            SetDynamicObjectMaterialText(VIPObject[vehicleGameID], 0, gString, 140, "Arial", 65, 0, -1, 0, 1);

            // reseting rotation

            CarInfo[vehicleDBId][cVIPPos][3] = 0.0;
            CarInfo[vehicleDBId][cVIPPos][4] = 0.0;
            CarInfo[vehicleDBId][cVIPPos][5] = 0.0;
            
            AttachDynamicObjectToVehicle(VIPObject[vehicleGameID], vehicleGameID, CarInfo[vehicleDBId][cVIPPos][0], CarInfo[vehicleDBId][cVIPPos][1], CarInfo[vehicleDBId][cVIPPos][2], CarInfo[vehicleDBId][cVIPPos][3], CarInfo[vehicleDBId][cVIPPos][4], CarInfo[vehicleDBId][cVIPPos][5]);  
        }
    }
    mysql_format(SQL, gString, sizeof gString, "update `cars` set `VIPText` = '%s', `VIPColor` = '%s', `VIPPos` = '%f %f %f %f %f %f' where `ID` = '%d';", CarInfo[vehicleDBId][cVIPText], CarInfo[vehicleDBId][cVIPColor], CarInfo[vehicleDBId][cVIPPos][0], CarInfo[vehicleDBId][cVIPPos][1], CarInfo[vehicleDBId][cVIPPos][2], CarInfo[vehicleDBId][cVIPPos][3], CarInfo[vehicleDBId][cVIPPos][4], CarInfo[vehicleDBId][cVIPPos][5], vehicleDBId);
    mysql_tquery(SQL, gString, "", "");

    return DeletePVar(playerid, "vip_menu_selected");
}

YCMD:carplate(playerid, params[], help)
{
    if(!IsPlayerInAnyVehicle(playerid))
        return SCM(playerid, -1, "Nu te aflii intr-un vehicul.");

    new
        vehicleid = GetPlayerVehicleID(playerid);

    if(!VehicleSQL[vehicleid])
        return SCM(playerid, -1, "Acest vehicul nu este unul personal.");

    if(GetPlayerMoney(playerid) < 5000)
        return SCMF(playerid, -1, "You do not have the money.");

    new
        plateString[24];

    if(sscanf(params, "s[24]", plateString))
        return sendSyntax(playerid, "/carplate [text]");

    SCMF(playerid, -1, "You changed your vehicle plate text to: %s", plateString);

    strmid(CarInfo[VehicleSQL[vehicleid]][cLicense], plateString, 0, strlen(plateString), 999);
    SetVehicleNumberPlate(vehicleid, plateString);

    GivePlayerMoney(playerid, -10000);

    mysql_format(SQL, gString, sizeof gString, "update `cars` set `License` = '%s' where `ID` = '%d';", CarInfo[VehicleSQL[vehicleid]][cLicense], VehicleSQL[vehicleid]);
    mysql_tquery(SQL, gString, "", "");

    return 1;
}

YCMD:park(playerid, params[], help)
{
    // Nu poti parca un vehicul intr-o zona protejata!
    if(!IsPlayerInAnyVehicle(playerid))
        return SCM(playerid, -1, "Nu te aflii intr-un vehicul.");
    
    new
        vehicleid = GetPlayerVehicleID(playerid);
    
    if(!VehicleSQL[vehicleid])
        return SCM(playerid, -1, "Acest vehicul nu este unul personal.");
    
    if(VehicleInfo[vehicleid][vehEngine])
        return SCM(playerid, -1, "Nu poti face asta cu motorul pornit.");

    if(strcmp(PlayerInfo[playerid][pNormalName], CarInfo[VehicleSQL[vehicleid]][cOwner], false) == 1)
        return SCM(playerid, COLOR_GREY, "Nu te aflii intr-un vehicul personal.");

    new
        Float: vHealth, Float: vAngle, Float: vPos[3],
        vehicleDBId = VehicleSQL[vehicleid];

    GetVehicleHealth(vehicleid, vHealth);
    
    if(vHealth < 750.0)
        return SCM(playerid, -1, "Vehiculul este defect. Mergi la un PNS pentru a-l repara.");

    GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
    GetVehicleZAngle(vehicleid, vAngle);

    CarInfo[vehicleDBId][cLocationx] = vPos[0];
    CarInfo[vehicleDBId][cLocationy] = vPos[1];
    CarInfo[vehicleDBId][cLocationz] = vPos[2];
    CarInfo[vehicleDBId][cAngle] = vAngle;
    
    SCM(playerid, -1, "Vehiculul a fost parcat!");

    return WhenVehicleParked(playerid, vehicleDBId, vehicleid);
}

YCMD:lock(playerid, params[], help)
{
    new
        engine, lights, alarm, doors, bonnet, boot, objective,
        vehicleid = (!IsPlayerInAnyVehicle(playerid) ? GetClosestVehicle(playerid, 5.0) : GetPlayerVehicleID(playerid));

    if(!IsValidVehicle(vehicleid))
        return 1;

    new
        vehicleDBId = VehicleSQL[vehicleid];
    
    if(!vehicleDBId)
        return 1;

    if(strcmp(PlayerInfo[playerid][pNormalName], CarInfo[vehicleDBId][cOwner], true) == 0 || s_PlayerInfo[playerid][pSHireCar] == vehicleDBId)
    {
        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
        SetVehicleParamsEx(vehicleid, engine, lights, alarm, (CarInfo[vehicleDBId][cLock]) ? (0) : (1), bonnet, boot, objective);
        
        format(gString, sizeof gString, "~h~%s~n~%s", CarInfo[vehicleDBId][cDescription], (CarInfo[vehicleDBId][cLock]) ? ("~g~Unlocked") : ("~r~Locked"));
        GameTextForPlayer(playerid, gString, 4000, 4);

        CarInfo[vehicleDBId][cLock] = CarInfo[vehicleDBId][cLock] ? (0) : (1);
        VehicleInfo[vehicleid][vehLocked] = VehicleInfo[vehicleid][vehLocked] ? (0) : (1); 
        
        return SetVehicleParamsForPlayer(vehicleid, playerid, 0, 0);
    }
    return 1;
}

YCMD:givekey(playerid, params[], help)
{
    if(!IsPlayerInAnyVehicle(playerid))
        return SCM(playerid, -1, "Nu te afli intr-un vehicul.");
    new
        targetId, vehicleGameID = GetPlayerVehicleID(playerid);
    
    if(sscanf(params, "u", targetId))
        return sendSyntax(playerid, "/givekey [name/playerid]");

    if(!Iter_Contains(VehicleType<VEH_TYPE_PERSONAL>, vehicleGameID))
        return SCM(playerid, -1, "Acest vehicul nu este unul personal.");

    if(!strmatch(PlayerInfo[playerid][pNormalName], CarInfo[VehicleSQL[vehicleGameID]][cOwner]))
        return SCM(playerid, -1, "Acest vehicul personal nu iti apartine.");

    if(!IsPlayerConnected(targetId))
        return SCM(playerid, -1, "Player not connected.");

    if(!IsPlayerInRangeOfPlayer(playerid, targetId, 10))
        return SCM(playerid, -1, "Nu te afli langa acest player.");

    if(s_PlayerInfo[targetId][pSHireCar])
        return SCM(playerid, -1, "Acest jucator are deja cheile unui alt vehicul personal. Acesta trebuie sa le arunce(/throwkey).");

    s_PlayerInfo[targetId][pSHireCar] = VehicleSQL[vehicleGameID];
    SCMF(playerid, COLOR_GREY, "I-ai oferit cheile vehicului tau jucatorului %s.", GetName(targetId));
    SCMF(targetId, COLOR_GREY, "%s ti-a oferit cheile vehicului sau %s.", GetName(playerid), aVehicleNames[GetVehicleModel(vehicleGameID) - 400]);
    
    SetVehicleParamsForPlayer(vehicleGameID, targetId, 0, 0);

    return 1;
}

YCMD:cw(playerid, params[], help)
{
    if(!IsPlayerInAnyVehicle(playerid))
        return SCM(playerid, -1, "You need to be in vehicle.");

    new
        stringMessage[144];

    if(sscanf(params, "s[144]", stringMessage))
        return sendSyntax(playerid, "/cw <Message>");

    foreach(new i : PlayersInVehicle)
    {
        if(IsPlayerInVehicle(i, GetPlayerVehicleID(playerid)))
        {
            SCMF(i, COLOR_YELLOW, "(Car Whisper) %s: %s", GetName(playerid), stringMessage);
        }
    }
    return 1;
}
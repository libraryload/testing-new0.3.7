#include <YSI_Coding\y_hooks>

#define MAX_SLOTS 10
#define LINES_PRICE 33750
new Text:slotsTD[13],
	PlayerText:slotsPTD[MAX_PLAYERS][16],
	SlotsReward[6],
	SlotsLines[MAX_PLAYERS],Slotsbet[MAX_PLAYERS],Slotsmoney[MAX_PLAYERS],SlotsTimer[MAX_PLAYERS];


static win[MAX_PLAYERS];

hook OnGameModeInit() {
    SlotsReward[0] = 55500;
    SlotsReward[1] = 70500;
    SlotsReward[2] = 92500;
    SlotsReward[3] = 152500;
    SlotsReward[4] = 185500;
    SlotsReward[5] = 200000;
	slotsTD[0] = TextDrawCreate(308.000000, 160.000000, "_");
	TextDrawFont(slotsTD[0], 0);
	TextDrawLetterSize(slotsTD[0], 0.970831, 14.899993);
	TextDrawTextSize(slotsTD[0], 263.500000, 147.000000);
	TextDrawSetOutline(slotsTD[0], 1);
	TextDrawSetShadow(slotsTD[0], 0);
	TextDrawAlignment(slotsTD[0], 2);
	TextDrawColor(slotsTD[0], -1);
	TextDrawBackgroundColor(slotsTD[0], 255);
	TextDrawBoxColor(slotsTD[0], 255);
	TextDrawUseBox(slotsTD[0], 1);
	TextDrawSetProportional(slotsTD[0], 1);
	TextDrawSetSelectable(slotsTD[0], 0);

	slotsTD[1] = TextDrawCreate(432.000000, 160.000000, "_");
	TextDrawFont(slotsTD[1], 0);
	TextDrawLetterSize(slotsTD[1], 0.970831, 14.899993);
	TextDrawTextSize(slotsTD[1], 263.500000, 85.000000);
	TextDrawSetOutline(slotsTD[1], 1);
	TextDrawSetShadow(slotsTD[1], 0);
	TextDrawAlignment(slotsTD[1], 2);
	TextDrawColor(slotsTD[1], -1);
	TextDrawBackgroundColor(slotsTD[1], 255);
	TextDrawBoxColor(slotsTD[1], 255);
	TextDrawUseBox(slotsTD[1], 1);
	TextDrawSetProportional(slotsTD[1], 1);
	TextDrawSetSelectable(slotsTD[1], 0);

	slotsTD[2] = TextDrawCreate(432.000000, 264.000000, "SET Bet");
	TextDrawFont(slotsTD[2], 2);
	TextDrawLetterSize(slotsTD[2], 0.195833, 1.050000);
	TextDrawTextSize(slotsTD[2], 16.500000, 72.500000);
	TextDrawSetOutline(slotsTD[2], 1);
	TextDrawSetShadow(slotsTD[2], 0);
	TextDrawAlignment(slotsTD[2], 2);
	TextDrawColor(slotsTD[2], -1);
	TextDrawBackgroundColor(slotsTD[2], 255);
	TextDrawBoxColor(slotsTD[2], 16711935);
	TextDrawUseBox(slotsTD[2], 1);
	TextDrawSetProportional(slotsTD[2], 1);
	TextDrawSetSelectable(slotsTD[2], 1);

	slotsTD[3] = TextDrawCreate(432.000000, 279.000000, "spin");
	TextDrawFont(slotsTD[3], 2);
	TextDrawLetterSize(slotsTD[3], 0.199999, 0.950000);
	TextDrawTextSize(slotsTD[3], 16.500000, 72.500000);
	TextDrawSetOutline(slotsTD[3], 1);
	TextDrawSetShadow(slotsTD[3], 0);
	TextDrawAlignment(slotsTD[3], 2);
	TextDrawColor(slotsTD[3], -1);
	TextDrawBackgroundColor(slotsTD[3], 255);
	TextDrawBoxColor(slotsTD[3], -16776961);
	TextDrawUseBox(slotsTD[3], 1);
	TextDrawSetProportional(slotsTD[3], 1);
	TextDrawSetSelectable(slotsTD[3], 1);

	slotsTD[4] = TextDrawCreate(433.000000, 175.000000, "BET INFORMATION");
	TextDrawFont(slotsTD[4], 2);
	TextDrawLetterSize(slotsTD[4], 0.150000, 1.000001);
	TextDrawTextSize(slotsTD[4], 400.000000, 172.000000);
	TextDrawSetOutline(slotsTD[4], 1);
	TextDrawSetShadow(slotsTD[4], 0);
	TextDrawAlignment(slotsTD[4], 2);
	TextDrawColor(slotsTD[4], -1);
	TextDrawBackgroundColor(slotsTD[4], 255);
	TextDrawBoxColor(slotsTD[4], 50);
	TextDrawUseBox(slotsTD[4], 0);
	TextDrawSetProportional(slotsTD[4], 1);
	TextDrawSetSelectable(slotsTD[4], 0);

	slotsTD[5] = TextDrawCreate(432.000000, 211.000000, "double");
	TextDrawFont(slotsTD[5], 2);
	TextDrawLetterSize(slotsTD[5], 0.195833, 1.050000);
	TextDrawTextSize(slotsTD[5], 16.500000, 72.500000);
	TextDrawSetOutline(slotsTD[5], 1);
	TextDrawSetShadow(slotsTD[5], 0);
	TextDrawAlignment(slotsTD[5], 2);
	TextDrawColor(slotsTD[5], -1);
	TextDrawBackgroundColor(slotsTD[5], 255);
	TextDrawBoxColor(slotsTD[5], 1296911871);
	TextDrawUseBox(slotsTD[5], 1);
	TextDrawSetProportional(slotsTD[5], 1);
	TextDrawSetSelectable(slotsTD[5], 1);

	slotsTD[6] = TextDrawCreate(268.000000, 148.000000, "slots machine");
	TextDrawFont(slotsTD[6], 3);
	TextDrawLetterSize(slotsTD[6], 0.200000, 1.000001);
	TextDrawTextSize(slotsTD[6], 400.000000, 172.000000);
	TextDrawSetOutline(slotsTD[6], 1);
	TextDrawSetShadow(slotsTD[6], 0);
	TextDrawAlignment(slotsTD[6], 2);
	TextDrawColor(slotsTD[6], -1);
	TextDrawBackgroundColor(slotsTD[6], 255);
	TextDrawBoxColor(slotsTD[6], 50);
	TextDrawUseBox(slotsTD[6], 0);
	TextDrawSetProportional(slotsTD[6], 1);
	TextDrawSetSelectable(slotsTD[6], 0);

	slotsTD[7] = TextDrawCreate(356.000000, 148.000000, "POWER ] STARS");
	TextDrawFont(slotsTD[7], 2);
	TextDrawLetterSize(slotsTD[7], 0.150000, 1.000001);
	TextDrawTextSize(slotsTD[7], 400.000000, 172.000000);
	TextDrawSetOutline(slotsTD[7], 1);
	TextDrawSetShadow(slotsTD[7], 0);
	TextDrawAlignment(slotsTD[7], 2);
	TextDrawColor(slotsTD[7], -1);
	TextDrawBackgroundColor(slotsTD[7], 255);
	TextDrawBoxColor(slotsTD[7], 50);
	TextDrawUseBox(slotsTD[7], 0);
	TextDrawSetProportional(slotsTD[7], 1);
	TextDrawSetSelectable(slotsTD[7], 0);


	slotsTD[8] = TextDrawCreate(261.000000, 264.000000, "red");
	TextDrawFont(slotsTD[8], 2);
	TextDrawLetterSize(slotsTD[8], 0.195833, 1.100000);
	TextDrawTextSize(slotsTD[8], 16.500000, 41.000000);
	TextDrawSetOutline(slotsTD[8], 1);
	TextDrawSetShadow(slotsTD[8], 0);
	TextDrawAlignment(slotsTD[8], 2);
	TextDrawColor(slotsTD[8], -1);
	TextDrawBackgroundColor(slotsTD[8], 255);
	TextDrawBoxColor(slotsTD[8], -1962934017);
	TextDrawUseBox(slotsTD[8], 1);
	TextDrawSetProportional(slotsTD[8], 1);
	TextDrawSetSelectable(slotsTD[8], 1);

	slotsTD[9] = TextDrawCreate(432.000000, 211.000000, "double");
	TextDrawFont(slotsTD[9], 2);
	TextDrawLetterSize(slotsTD[9], 0.195833, 1.050000);
	TextDrawTextSize(slotsTD[9], 16.500000, 72.500000);
	TextDrawSetOutline(slotsTD[9], 1);
	TextDrawSetShadow(slotsTD[9], 0);
	TextDrawAlignment(slotsTD[9], 2);
	TextDrawColor(slotsTD[9], -1);
	TextDrawBackgroundColor(slotsTD[9], 255);
	TextDrawBoxColor(slotsTD[9], 1296911871);
	TextDrawUseBox(slotsTD[9], 1);
	TextDrawSetProportional(slotsTD[9], 1);
	TextDrawSetSelectable(slotsTD[9], 1);

	slotsTD[10] = TextDrawCreate(261.000000, 280.000000, "black");
	TextDrawFont(slotsTD[10], 2);
	TextDrawLetterSize(slotsTD[10], 0.195832, 1.100000);
	TextDrawTextSize(slotsTD[10], 16.500000, 41.000000);
	TextDrawSetOutline(slotsTD[10], 1);
	TextDrawSetShadow(slotsTD[10], 0);
	TextDrawAlignment(slotsTD[10], 2);
	TextDrawColor(slotsTD[10], -1);
	TextDrawBackgroundColor(slotsTD[10], 255);
	TextDrawBoxColor(slotsTD[10], 1296911871);
	TextDrawUseBox(slotsTD[10], 1);
	TextDrawSetProportional(slotsTD[10], 1);
	TextDrawSetSelectable(slotsTD[10], 1);

	slotsTD[11] = TextDrawCreate(404.000000, 230.000000, "<");
	TextDrawFont(slotsTD[11], 2);
	TextDrawLetterSize(slotsTD[11], 0.245833, 1.299999);
	TextDrawTextSize(slotsTD[11], 400.000000, 172.000000);
	TextDrawSetOutline(slotsTD[11], 1);
	TextDrawSetShadow(slotsTD[11], 0);
	TextDrawAlignment(slotsTD[11], 2);
	TextDrawColor(slotsTD[11], -1);
	TextDrawBackgroundColor(slotsTD[11], 255);
	TextDrawBoxColor(slotsTD[11], 50);
	TextDrawUseBox(slotsTD[11], 0);
	TextDrawSetProportional(slotsTD[11], 1);
	TextDrawSetSelectable(slotsTD[11], 1);

	slotsTD[12] = TextDrawCreate(462.000000, 230.000000, ">");
	TextDrawFont(slotsTD[12], 2);
	TextDrawLetterSize(slotsTD[12], 0.245833, 1.299999);
	TextDrawTextSize(slotsTD[12], 400.000000, 172.000000);
	TextDrawSetOutline(slotsTD[12], 1);
	TextDrawSetShadow(slotsTD[12], 0);
	TextDrawAlignment(slotsTD[12], 2);
	TextDrawColor(slotsTD[12], -1);
	TextDrawBackgroundColor(slotsTD[12], 255);
	TextDrawBoxColor(slotsTD[12], 50);
	TextDrawUseBox(slotsTD[12], 0);
	TextDrawSetProportional(slotsTD[12], 1);
	TextDrawSetSelectable(slotsTD[12], 1);
	return true;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid) {
    if(clickedid == slotsTD[11]) {
        if(GetPVarInt(playerid, "SlotDeschis") == 1) return SCM(playerid,-1,"Nu poti modifica liniile acum.");
        if(SlotsLines[playerid] > 1 && SlotsLines[playerid] <= 5) {
            switch(SlotsLines[playerid]) { case 2: SlotsLines[playerid] = 1; case 3: SlotsLines[playerid] = 2; case 5: SlotsLines[playerid] = 3;}
            format(gString,15,"%d lines",SlotsLines[playerid]);
            PlayerTextDrawSetString(playerid, slotsPTD[playerid][15], gString);
            PlayerTextDrawShow(playerid, slotsPTD[playerid][15]);
            va_SendClientMessage(playerid, -1, "%d lines", SlotsLines[playerid]);
        }
    }
    if(clickedid == slotsTD[12]) {
        if(GetPVarInt(playerid, "SlotDeschis") == 1) return SCM(playerid,-1,"Nu poti modifica liniile acum.");
        if(SlotsLines[playerid] >= 1 && SlotsLines[playerid] < 5) {
            switch(SlotsLines[playerid]) { case 1: SlotsLines[playerid] = 2; case 2: SlotsLines[playerid] = 3; case 3: SlotsLines[playerid] = 5;}
            format(gString,15,"%d lines",SlotsLines[playerid]);
            PlayerTextDrawSetString(playerid, slotsPTD[playerid][15], gString);
            PlayerTextDrawShow(playerid, slotsPTD[playerid][15]);
            va_SendClientMessage(playerid, -1, "%d lines", SlotsLines[playerid]);
        }
    }
    if(clickedid == slotsTD[3]) {
        if(!Slotsbet[playerid]) return SCM(playerid,-1,"Trebui sa introduci o suma mai intai!");
        if(GetPVarInt(playerid, "SlotDeschis") == 1) return 1;
        if(GetPlayerCash(playerid) < Slotsbet[playerid]) return SCM(playerid,-1,"Nu ai destui bani!");
        GivePlayerCash(playerid, -Slotsbet[playerid]);
        new string[180];
        format(gString,64,"BET: ~G~%s",FormatNumber(GetPlayerCash(playerid)));
        PlayerTextDrawSetString(playerid, slotsPTD[playerid][10], string);
        SetPVarInt(playerid, "SlotsOpened", 0);
        KillTimer(SlotsTimer[playerid]);
        SetPVarInt(playerid, "SlotDeschis", 1);
        SlotsTimer[playerid] = SetTimerEx("StartSlots", 300, 1, "i", playerid);
    }
    if(clickedid == slotsTD[2]) {
        if(GetPVarInt(playerid, "SlotDeschis") == 1) return SCM(playerid,-1,"Nu poti modifica betul acum.");
        Dialog_Show(playerid, DIALOG_SLOTSBET, DIALOG_STYLE_INPUT, "Slots:", "Introdu in casuta de mai jos suma pe care doresti sa o pariezi\nSuma trebuie nu poate fi mai mica de $%s deoarece joci pe %d linii", "Bet", "Cancel", FormatNumber(LINES_PRICE*SlotsLines[playerid]),SlotsLines[playerid]);
    }	
    if(clickedid == slotsTD[5]) {
        SetTimerEx("SlotsDouble", 2000, 0, "i", playerid),SetPVarInt(playerid, "SlotCastig", 1);
    }	
    if(clickedid == slotsTD[10] && GetPVarInt(playerid, "SlotCastig") == 1) {
        if(GetPVarInt(playerid, "SlotsCarte") == 1) PlayerTextDrawSetString(playerid, slotsPTD[playerid][12], "ld_card:cd1h");
        else PlayerTextDrawSetString(playerid, slotsPTD[playerid][12], "ld_card:cd1c");
        if(GetPVarInt(playerid, "SlotsCarte") == 0) {
            SetPVarInt(playerid, "SlotsCarte", random(2));
            Slotsmoney[playerid] = Slotsmoney[playerid]*2;
            va_SendClientMessage(playerid,-1,"Correct! New prize: $%s.",FormatNumber(Slotsmoney[playerid]));
            SelectTextDraw(playerid, 0xFFFFFFFFF);
            PlayerTextDrawShow(playerid, slotsPTD[playerid][12]);
            PlayerTextDrawShow(playerid, slotsPTD[playerid][13]);
            PlayerTextDrawShow(playerid, slotsPTD[playerid][14]);
            TextDrawShowForPlayer(playerid, slotsTD[8]);
            TextDrawShowForPlayer(playerid, slotsTD[9]);
        }
        else if( GetPVarInt(playerid, "SlotsCarte") == 1){
            SetPVarInt(playerid, "SlotCastig", 0);
            va_SendClientMessage(playerid,-1,"Incorrect! You lose all money wins.");
            SetTimerEx("Slotslose", 1000, 0, "i", playerid);
        }
    }
    if(clickedid == slotsTD[8] && GetPVarInt(playerid, "SlotCastig") == 1) {
        if(GetPVarInt(playerid, "SlotsCarte") == 1) PlayerTextDrawSetString(playerid, slotsPTD[playerid][12], "ld_card:cd1h");
        else PlayerTextDrawSetString(playerid, slotsPTD[playerid][12], "ld_card:cd1c");
        if(GetPVarInt(playerid, "SlotsCarte") == 1) {
            SetPVarInt(playerid, "SlotsCarte", random(2));
            Slotsmoney[playerid] = Slotsmoney[playerid]*2;
            va_SendClientMessage(playerid,-1,"Correct! New prize: $%s.",FormatNumber(Slotsmoney[playerid]));
            SelectTextDraw(playerid, 0xFFFFFFFFF);
            PlayerTextDrawShow(playerid, slotsPTD[playerid][12]);
            PlayerTextDrawShow(playerid, slotsPTD[playerid][13]);
            PlayerTextDrawShow(playerid, slotsPTD[playerid][14]);
            TextDrawShowForPlayer(playerid, slotsTD[8]);
            TextDrawShowForPlayer(playerid, slotsTD[9]);
        }
        else if( GetPVarInt(playerid, "SlotsCarte") == 0){
            va_SendClientMessage(playerid,-1,"Incorrect! You lose all money wins.");
            SetTimerEx("Slotslose", 1000, 0, "i", playerid);
            SetPVarInt(playerid, "SlotCastig", 0);
        }
    }
    if(GetPVarInt(playerid, "SlotActiv") == 1) 
    {
        if(GetPVarInt(playerid, "SlotCastig") == 1) {
            va_SendClientMessage(playerid,-1,"Ai dat cashout! Ai castigat in total $%s.",FormatNumber(Slotsmoney[playerid]));
            GivePlayerCash(playerid, Slotsmoney[playerid]);
            Slotsmoney[playerid]=0;
            SetPVarInt(playerid, "SlotCastig", 0);

            PlayerTextDrawHide(playerid, slotsPTD[playerid][12]);
            PlayerTextDrawHide(playerid, slotsPTD[playerid][13]);
            PlayerTextDrawHide(playerid, slotsPTD[playerid][14]);
            TextDrawHideForPlayer(playerid, slotsTD[8]);
            TextDrawHideForPlayer(playerid, slotsTD[9]);

            SelectTextDraw(playerid, 0xFFFFFFFFF);
            TogglePlayerControllable(playerid, 0);

            format(gString,15,"%d lines",SlotsLines[playerid]);
            PlayerTextDrawSetString(playerid, slotsPTD[playerid][15], gString);

            format(gString,64,"BET: ~G~%s",FormatNumber(Slotsbet[playerid]));
            PlayerTextDrawSetString(playerid, slotsPTD[playerid][9], gString);

            format(gString,64,"~G~money $%s",FormatNumber(GetPlayerCash(playerid)));
            PlayerTextDrawSetString(playerid, slotsPTD[playerid][10], gString);
            for(new x = 0; x < 12; x++) TextDrawShowForPlayer(playerid, slotsTD[x]);
            for(new x = 0; x <= 8; x ++) PlayerTextDrawShow(playerid, slotsPTD[playerid][x]);
           	PlayerTextDrawShow(playerid, slotsPTD[playerid][15]);
            TextDrawShowForPlayer(playerid, slotsTD[11]);
            TextDrawShowForPlayer(playerid, slotsTD[12]);
            return 1;
        }
        if(GetPVarInt(playerid, "SlotDeschis") == 1) {
            SelectTextDraw(playerid, 0xFFFFFFFFF);
            TogglePlayerControllable(playerid, 0);
            format(gString,15,"%d lines",SlotsLines[playerid]);
            PlayerTextDrawSetString(playerid, slotsPTD[playerid][15], gString);

            format(gString,64,"BET: ~G~%s",FormatNumber(Slotsbet[playerid]));
            PlayerTextDrawSetString(playerid, slotsPTD[playerid][9], gString);

            format(gString,64,"~G~money $%s",FormatNumber(GetPlayerCash(playerid)));
            PlayerTextDrawSetString(playerid, slotsPTD[playerid][10], gString);

            for(new x = 0; x <= 8; x ++) PlayerTextDrawShow(playerid, slotsPTD[playerid][x]);
           	PlayerTextDrawShow(playerid, slotsPTD[playerid][15]);
            TextDrawShowForPlayer(playerid, slotsTD[11]);
            TextDrawShowForPlayer(playerid, slotsTD[12]);
            return 1;
        }
        SetPVarInt(playerid, "SlotActiv", 0);
        TogglePlayerControllable(playerid, 1);
        CancelSelectTextDraw(playerid);
        for(new x = 0; x < 16; x++) PlayerTextDrawHide(playerid, slotsPTD[playerid][x]);
        for(new x = 0; x < 13; x++) TextDrawHideForPlayer(playerid, slotsTD[x]);
        return 1;
	}
	return true;
}

hook OnPlayerConnect(playerid) {
	SlotsLines[playerid] = 1;
    Slotsbet[playerid] = 0;
    Slotsmoney[playerid] = 0;

    return true;
}

Dialog:DIALOG_SLOTSBET(playerid, response, listitem, inputtext[]) {
    if(!response)
        return true;

    new val = strval(inputtext);
    if(val > GetPlayerCash(playerid)) return SCM(playerid,-1,"Nu ai destui bani!");
    if(val < (LINES_PRICE*SlotsLines[playerid])) return SCM(playerid,-1,"Suma este prea mica.");
    if(val > 1000000) return SCM(playerid,-1,"Suma este prea mare, maxim 1.000.000$.");
    Slotsbet[playerid] = val;
    format(gString,64,"BET: ~g~$%s",FormatNumber(Slotsbet[playerid]));
    PlayerTextDrawSetString(playerid, slotsPTD[playerid][9], gString);
    va_SendClientMessage(playerid,-1,"Bet amount set to: {cb7aff}$%s",FormatNumber(Slotsbet[playerid]));
	return true;
}

YCMD:gamble(playerid, params[], help) {

    SetPVarInt(playerid, "SlotActiv", 1);
    SelectTextDraw(playerid, 0xFFFFFFFFF);
    TogglePlayerControllable(playerid, 0);
    createSlotsUI(playerid);

    format(gString,15,"%d lines",SlotsLines[playerid]);
    PlayerTextDrawSetString(playerid, slotsPTD[playerid][15], gString);

    format(gString,64,"BET: ~g~$%s",FormatNumber(Slotsbet[playerid]));
    PlayerTextDrawSetString(playerid, slotsPTD[playerid][9], gString);
    format(gString,64,"~g~money: $%s",FormatNumber(GetPlayerCash(playerid)));
    PlayerTextDrawSetString(playerid, slotsPTD[playerid][10], gString);
	showSlotsUI(playerid);
	return true;
}

function showSlotsUI(playerid) {
    for(new x = 0; x < 4; x++) TextDrawShowForPlayer(playerid, slotsTD[x]);
    for(new x = 0; x <= 8; x ++) PlayerTextDrawShow(playerid, slotsPTD[playerid][x]);
    TextDrawShowForPlayer(playerid, slotsTD[6]);
	TextDrawShowForPlayer(playerid, slotsTD[7]);
	TextDrawShowForPlayer(playerid, slotsTD[4]);
	PlayerTextDrawShow(playerid, slotsPTD[playerid][9]);
	PlayerTextDrawShow(playerid, slotsPTD[playerid][10]);
   	PlayerTextDrawShow(playerid, slotsPTD[playerid][15]);
    TextDrawShowForPlayer(playerid, slotsTD[11]);
    TextDrawShowForPlayer(playerid, slotsTD[12]);
	return true;
}

function StartSlots(playerid) {
    new SlotType[9];
    if(GetPVarInt(playerid, "SlotsOpened") <= 10) {
        SetPVarInt(playerid, "SlotsOpened", GetPVarInt(playerid, "SlotsOpened") + 1);
        for(new i = 0; i < 9; i++) {
            SlotType[i] = random(6);
            switch(SlotType[i]) {
                case 0: PlayerTextDrawSetString(playerid, slotsPTD[playerid][i], "ld_slot:r_69"),PlayerTextDrawShow(playerid, slotsPTD[playerid][i]);
                case 1: PlayerTextDrawSetString(playerid, slotsPTD[playerid][i], "ld_slot:grapes"),PlayerTextDrawShow(playerid, slotsPTD[playerid][i]);
                case 2: PlayerTextDrawSetString(playerid, slotsPTD[playerid][i], "ld_slot:cherry"),PlayerTextDrawShow(playerid, slotsPTD[playerid][i]);
                case 3: PlayerTextDrawSetString(playerid, slotsPTD[playerid][i], "ld_slot:bell"),PlayerTextDrawShow(playerid, slotsPTD[playerid][i]);
                case 4: PlayerTextDrawSetString(playerid, slotsPTD[playerid][i], "ld_slot:bar1_o"),PlayerTextDrawShow(playerid, slotsPTD[playerid][i]);
                case 5: PlayerTextDrawSetString(playerid, slotsPTD[playerid][i], "ld_slot:bar2_o"),PlayerTextDrawShow(playerid, slotsPTD[playerid][i]);
            }
        }
    }
    if(GetPVarInt(playerid, "SlotsOpened") == 10) {
        KillTimer(SlotsTimer[playerid]);
        switch(SlotsLines[playerid]) {
            case 1: {
                if(SlotType[0] == SlotType[1] && SlotType[1] == SlotType[2]) {
                    va_SendClientMessage(playerid,-1,">> 3x %s. + %s",SlotsName(SlotType[0]),FormatNumber(SlotsLines[playerid] * SlotsReward[SlotType[0]] + Slotsbet[playerid]));
                    Slotsmoney[playerid] += SlotsLines[playerid] * SlotsReward[SlotType[0]] + Slotsbet[playerid];
                    win[playerid]++;
                }
            }
            case 2: {
                if(SlotType[0] == SlotType[1] && SlotType[1] == SlotType[2]) {
                    va_SendClientMessage(playerid,-1,">> 3x %s. + %s",SlotsName(SlotType[0]),FormatNumber(SlotsLines[playerid] * SlotsReward[SlotType[0]] + Slotsbet[playerid]));
                    Slotsmoney[playerid] += SlotsLines[playerid] * SlotsReward[SlotType[0]] + Slotsbet[playerid];
                    win[playerid]++;
                }
                if(SlotType[3] == SlotType[4] && SlotType[4] == SlotType[5]) {
                    va_SendClientMessage(playerid,-1,">> 3x %s. + %s",SlotsName(SlotType[3]),FormatNumber(SlotsLines[playerid] * SlotsReward[SlotType[3]] + Slotsbet[playerid]));
                    Slotsmoney[playerid] += SlotsLines[playerid] * SlotsReward[SlotType[3]] + Slotsbet[playerid];
                    win[playerid]++;
                }

            }
            case 3: {
                if(SlotType[0] == SlotType[1] && SlotType[1] == SlotType[2]) {
                    va_SendClientMessage(playerid,-1,">> 3x %s. + %s",SlotsName(SlotType[0]),FormatNumber(SlotsLines[playerid] * SlotsReward[SlotType[0]] + Slotsbet[playerid]));
                    Slotsmoney[playerid] += SlotsLines[playerid] * SlotsReward[SlotType[0]] + Slotsbet[playerid];
                    win[playerid]++;
                }
                if(SlotType[3] == SlotType[4] && SlotType[4] == SlotType[5]) {
                    va_SendClientMessage(playerid,-1,">> 3x %s. + %s",SlotsName(SlotType[3]),FormatNumber(SlotsLines[playerid] * SlotsReward[SlotType[3]] + Slotsbet[playerid]));
                    Slotsmoney[playerid] += SlotsLines[playerid] * SlotsReward[SlotType[3]] + Slotsbet[playerid];
                    win[playerid]++;
                }
                if(SlotType[6] == SlotType[7] && SlotType[7] == SlotType[8]) {
                    va_SendClientMessage(playerid,-1,">> 3x %s. + %s",SlotsName(SlotType[6]),FormatNumber(SlotsLines[playerid] * SlotsReward[SlotType[6]] + Slotsbet[playerid]));
                    Slotsmoney[playerid] += SlotsLines[playerid] * SlotsReward[SlotType[6]] + Slotsbet[playerid];
                    win[playerid]++;
                }
            }
            case 5: {
                if(SlotType[0] == SlotType[1] && SlotType[1] == SlotType[2]) {
                    va_SendClientMessage(playerid,-1,">> 3x %s. + %s",SlotsName(SlotType[0]),FormatNumber(SlotsLines[playerid] * SlotsReward[SlotType[0]] + Slotsbet[playerid]));
                    Slotsmoney[playerid] += SlotsLines[playerid] * SlotsReward[SlotType[0]] + Slotsbet[playerid];
                    win[playerid]++;
                }
                if(SlotType[3] == SlotType[4] && SlotType[4] == SlotType[5]) {
                    va_SendClientMessage(playerid,-1,">> 3x %s. + %s",SlotsName(SlotType[3]),FormatNumber(SlotsLines[playerid] * SlotsReward[SlotType[3]] + Slotsbet[playerid]));
                    Slotsmoney[playerid] += SlotsLines[playerid] * SlotsReward[SlotType[3]] + Slotsbet[playerid];
                    win[playerid]++;
                }
                if(SlotType[6] == SlotType[7] && SlotType[7] == SlotType[8]) {
                    va_SendClientMessage(playerid,-1,">> 3x %s. + %s",SlotsName(SlotType[6]),FormatNumber(SlotsLines[playerid] * SlotsReward[SlotType[6]] + Slotsbet[playerid]));
                    Slotsmoney[playerid] += SlotsLines[playerid] * SlotsReward[SlotType[6]] + Slotsbet[playerid];
                    win[playerid]++;
                }
                if(SlotType[0] == SlotType[4] && SlotType[4] == SlotType[8]) {
                    va_SendClientMessage(playerid,-1,">> 3x %s. + %s | diagonala",SlotsName(SlotType[0]),FormatNumber(SlotsLines[playerid] * SlotsReward[SlotType[0]] + Slotsbet[playerid]));
                    Slotsmoney[playerid] += SlotsLines[playerid] * SlotsReward[SlotType[0]] + Slotsbet[playerid];
                    win[playerid]++;
                }
                if(SlotType[2] == SlotType[4] && SlotType[4] == SlotType[6]) {
                    va_SendClientMessage(playerid,-1,">> 3x %s. + %s | diagonala",SlotsName(SlotType[2]),FormatNumber(SlotsLines[playerid] * SlotsReward[SlotType[2]] + Slotsbet[playerid]));
                    Slotsmoney[playerid] += SlotsLines[playerid] * SlotsReward[SlotType[2]] + Slotsbet[playerid];
                    win[playerid]++;
                }
            }
        }
        if(win[playerid]) 
        {
            SendClientMessage(playerid, -1, "You win! You can try your luck and double it, or continue");
            TextDrawShowForPlayer(playerid, slotsTD[5]);
        }
        else SetPVarInt(playerid, "SlotDeschis", 0);
    }
    return 1;
}
stock SlotsName(type) {
    new name[15];
    switch(type) {
        case 0: name="number 7";
        case 1: name="grapes";
        case 2: name="cherry";
        case 3: name="bell";
        case 4: name="gold bar";
        case 5: name="big gold bar";
    }
    return name;
}

function SlotsDouble(playerid) {
    SetPVarInt(playerid, "SlotDeschis", 0);
    for(new x = 0; x <=  8; x ++) PlayerTextDrawHide(playerid, slotsPTD[playerid][x]);

    PlayerTextDrawSetString(playerid, slotsPTD[playerid][12], "ld_card:cdback");
    PlayerTextDrawShow(playerid, slotsPTD[playerid][12]);
    PlayerTextDrawShow(playerid, slotsPTD[playerid][13]);
    PlayerTextDrawShow(playerid, slotsPTD[playerid][14]);
    TextDrawShowForPlayer(playerid, slotsTD[8]);
    TextDrawShowForPlayer(playerid, slotsTD[9]);
    SetPVarInt(playerid, "SlotsCarte", random(2));
    return 1;
}

function Slotslose(playerid) {
    new string[180];
    Slotsmoney[playerid] = 0;
    SetPVarInt(playerid, "SlotDeschis", 0);
    SetPVarInt(playerid, "SlotCastig", 0);

    PlayerTextDrawHide(playerid, slotsPTD[playerid][12]);
    PlayerTextDrawHide(playerid, slotsPTD[playerid][13]);
    PlayerTextDrawHide(playerid, slotsPTD[playerid][14]);
    TextDrawHideForPlayer(playerid, slotsTD[8]);
    TextDrawHideForPlayer(playerid, slotsTD[9]);

    SelectTextDraw(playerid, 0xFFFFFFFFF);
    format(gString,15,"%d lines",SlotsLines[playerid]);
    PlayerTextDrawSetString(playerid, slotsPTD[playerid][15], string);

    format(gString,64,"BET: ~G~%s",FormatNumber(Slotsbet[playerid]));
    PlayerTextDrawSetString(playerid, slotsPTD[playerid][9], string);

    format(gString,64,"~g~ money %s",FormatNumber(GetPlayerCash(playerid)));
    PlayerTextDrawSetString(playerid, slotsPTD[playerid][10], string);
	for(new x = 0; x <= 8; x ++) PlayerTextDrawShow(playerid, slotsPTD[playerid][x]);
    return 1;
}


function createSlotsUI(playerid) {
	slotsPTD[playerid][0] = CreatePlayerTextDraw(playerid, 234.000000, 159.000000, "ld_slot:bell");
	PlayerTextDrawFont(playerid, slotsPTD[playerid][0], 4);
	PlayerTextDrawLetterSize(playerid, slotsPTD[playerid][0], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, slotsPTD[playerid][0], 49.500000, 61.500000);
	PlayerTextDrawSetOutline(playerid, slotsPTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, slotsPTD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, slotsPTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, slotsPTD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, slotsPTD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, slotsPTD[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, slotsPTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, slotsPTD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, slotsPTD[playerid][0], 0);

	slotsPTD[playerid][1] = CreatePlayerTextDraw(playerid, 234.000000, 204.000000, "ld_slot:bell");
	PlayerTextDrawFont(playerid, slotsPTD[playerid][1], 4);
	PlayerTextDrawLetterSize(playerid, slotsPTD[playerid][1], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, slotsPTD[playerid][1], 49.500000, 61.500000);
	PlayerTextDrawSetOutline(playerid, slotsPTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, slotsPTD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, slotsPTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, slotsPTD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, slotsPTD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, slotsPTD[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, slotsPTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, slotsPTD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, slotsPTD[playerid][1], 0);

	slotsPTD[playerid][2] = CreatePlayerTextDraw(playerid, 234.000000, 249.000000, "ld_slot:bell");
	PlayerTextDrawFont(playerid, slotsPTD[playerid][2], 4);
	PlayerTextDrawLetterSize(playerid, slotsPTD[playerid][2], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, slotsPTD[playerid][2], 49.500000, 61.500000);
	PlayerTextDrawSetOutline(playerid, slotsPTD[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, slotsPTD[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, slotsPTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, slotsPTD[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, slotsPTD[playerid][2], 255);
	PlayerTextDrawBoxColor(playerid, slotsPTD[playerid][2], 50);
	PlayerTextDrawUseBox(playerid, slotsPTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, slotsPTD[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, slotsPTD[playerid][2], 0);

	slotsPTD[playerid][3] = CreatePlayerTextDraw(playerid, 283.000000, 159.000000, "ld_slot:bell");
	PlayerTextDrawFont(playerid, slotsPTD[playerid][3], 4);
	PlayerTextDrawLetterSize(playerid, slotsPTD[playerid][3], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, slotsPTD[playerid][3], 49.500000, 61.500000);
	PlayerTextDrawSetOutline(playerid, slotsPTD[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, slotsPTD[playerid][3], 0);
	PlayerTextDrawAlignment(playerid, slotsPTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, slotsPTD[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, slotsPTD[playerid][3], 255);
	PlayerTextDrawBoxColor(playerid, slotsPTD[playerid][3], 50);
	PlayerTextDrawUseBox(playerid, slotsPTD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, slotsPTD[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, slotsPTD[playerid][3], 0);

	slotsPTD[playerid][4] = CreatePlayerTextDraw(playerid, 283.000000, 204.000000, "ld_slot:bell");
	PlayerTextDrawFont(playerid, slotsPTD[playerid][4], 4);
	PlayerTextDrawLetterSize(playerid, slotsPTD[playerid][4], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, slotsPTD[playerid][4], 49.500000, 61.500000);
	PlayerTextDrawSetOutline(playerid, slotsPTD[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, slotsPTD[playerid][4], 0);
	PlayerTextDrawAlignment(playerid, slotsPTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, slotsPTD[playerid][4], -1);
	PlayerTextDrawBackgroundColor(playerid, slotsPTD[playerid][4], 255);
	PlayerTextDrawBoxColor(playerid, slotsPTD[playerid][4], 50);
	PlayerTextDrawUseBox(playerid, slotsPTD[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, slotsPTD[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid, slotsPTD[playerid][4], 0);

	slotsPTD[playerid][5] = CreatePlayerTextDraw(playerid, 283.000000, 249.000000, "ld_slot:bell");
	PlayerTextDrawFont(playerid, slotsPTD[playerid][5], 4);
	PlayerTextDrawLetterSize(playerid, slotsPTD[playerid][5], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, slotsPTD[playerid][5], 49.500000, 61.500000);
	PlayerTextDrawSetOutline(playerid, slotsPTD[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, slotsPTD[playerid][5], 0);
	PlayerTextDrawAlignment(playerid, slotsPTD[playerid][5], 1);
	PlayerTextDrawColor(playerid, slotsPTD[playerid][5], -1);
	PlayerTextDrawBackgroundColor(playerid, slotsPTD[playerid][5], 255);
	PlayerTextDrawBoxColor(playerid, slotsPTD[playerid][5], 50);
	PlayerTextDrawUseBox(playerid, slotsPTD[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, slotsPTD[playerid][5], 1);
	PlayerTextDrawSetSelectable(playerid, slotsPTD[playerid][5], 0);

	slotsPTD[playerid][6] = CreatePlayerTextDraw(playerid, 332.000000, 159.000000, "ld_slot:bell");
	PlayerTextDrawFont(playerid, slotsPTD[playerid][6], 4);
	PlayerTextDrawLetterSize(playerid, slotsPTD[playerid][6], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, slotsPTD[playerid][6], 49.500000, 61.500000);
	PlayerTextDrawSetOutline(playerid, slotsPTD[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, slotsPTD[playerid][6], 0);
	PlayerTextDrawAlignment(playerid, slotsPTD[playerid][6], 1);
	PlayerTextDrawColor(playerid, slotsPTD[playerid][6], -1);
	PlayerTextDrawBackgroundColor(playerid, slotsPTD[playerid][6], 255);
	PlayerTextDrawBoxColor(playerid, slotsPTD[playerid][6], 50);
	PlayerTextDrawUseBox(playerid, slotsPTD[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, slotsPTD[playerid][6], 1);
	PlayerTextDrawSetSelectable(playerid, slotsPTD[playerid][6], 0);

	slotsPTD[playerid][7] = CreatePlayerTextDraw(playerid, 332.000000, 204.000000, "ld_slot:bell");
	PlayerTextDrawFont(playerid, slotsPTD[playerid][7], 4);
	PlayerTextDrawLetterSize(playerid, slotsPTD[playerid][7], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, slotsPTD[playerid][7], 49.500000, 61.500000);
	PlayerTextDrawSetOutline(playerid, slotsPTD[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, slotsPTD[playerid][7], 0);
	PlayerTextDrawAlignment(playerid, slotsPTD[playerid][7], 1);
	PlayerTextDrawColor(playerid, slotsPTD[playerid][7], -1);
	PlayerTextDrawBackgroundColor(playerid, slotsPTD[playerid][7], 255);
	PlayerTextDrawBoxColor(playerid, slotsPTD[playerid][7], 50);
	PlayerTextDrawUseBox(playerid, slotsPTD[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, slotsPTD[playerid][7], 1);
	PlayerTextDrawSetSelectable(playerid, slotsPTD[playerid][7], 0);

	slotsPTD[playerid][8] = CreatePlayerTextDraw(playerid, 332.000000, 249.000000, "ld_slot:bell");
	PlayerTextDrawFont(playerid, slotsPTD[playerid][8], 4);
	PlayerTextDrawLetterSize(playerid, slotsPTD[playerid][8], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, slotsPTD[playerid][8], 49.500000, 61.500000);
	PlayerTextDrawSetOutline(playerid, slotsPTD[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, slotsPTD[playerid][8], 0);
	PlayerTextDrawAlignment(playerid, slotsPTD[playerid][8], 1);
	PlayerTextDrawColor(playerid, slotsPTD[playerid][8], -1);
	PlayerTextDrawBackgroundColor(playerid, slotsPTD[playerid][8], 255);
	PlayerTextDrawBoxColor(playerid, slotsPTD[playerid][8], 50);
	PlayerTextDrawUseBox(playerid, slotsPTD[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, slotsPTD[playerid][8], 1);
	PlayerTextDrawSetSelectable(playerid, slotsPTD[playerid][8], 0);

	slotsPTD[playerid][9] = CreatePlayerTextDraw(playerid, 433.000000, 189.000000, "BET: ~G~$1.000.000");
	PlayerTextDrawFont(playerid, slotsPTD[playerid][9], 2);
	PlayerTextDrawLetterSize(playerid, slotsPTD[playerid][9], 0.150000, 1.000001);
	PlayerTextDrawTextSize(playerid, slotsPTD[playerid][9], 400.000000, 172.000000);
	PlayerTextDrawSetOutline(playerid, slotsPTD[playerid][9], 1);
	PlayerTextDrawSetShadow(playerid, slotsPTD[playerid][9], 0);
	PlayerTextDrawAlignment(playerid, slotsPTD[playerid][9], 2);
	PlayerTextDrawColor(playerid, slotsPTD[playerid][9], -1);
	PlayerTextDrawBackgroundColor(playerid, slotsPTD[playerid][9], 255);
	PlayerTextDrawBoxColor(playerid, slotsPTD[playerid][9], 50);
	PlayerTextDrawUseBox(playerid, slotsPTD[playerid][9], 0);
	PlayerTextDrawSetProportional(playerid, slotsPTD[playerid][9], 1);
	PlayerTextDrawSetSelectable(playerid, slotsPTD[playerid][9], 0);

	slotsPTD[playerid][10] = CreatePlayerTextDraw(playerid, 433.000000, 160.000000, "~G~bank $12.582.056.617");
	PlayerTextDrawFont(playerid, slotsPTD[playerid][10], 3);
	PlayerTextDrawLetterSize(playerid, slotsPTD[playerid][10], 0.200000, 1.000001);
	PlayerTextDrawTextSize(playerid, slotsPTD[playerid][10], 400.000000, 172.000000);
	PlayerTextDrawSetOutline(playerid, slotsPTD[playerid][10], 1);
	PlayerTextDrawSetShadow(playerid, slotsPTD[playerid][10], 0);
	PlayerTextDrawAlignment(playerid, slotsPTD[playerid][10], 2);
	PlayerTextDrawColor(playerid, slotsPTD[playerid][10], -1);
	PlayerTextDrawBackgroundColor(playerid, slotsPTD[playerid][10], 255);
	PlayerTextDrawBoxColor(playerid, slotsPTD[playerid][10], 50);
	PlayerTextDrawUseBox(playerid, slotsPTD[playerid][10], 0);
	PlayerTextDrawSetProportional(playerid, slotsPTD[playerid][10], 1);
	PlayerTextDrawSetSelectable(playerid, slotsPTD[playerid][10], 0);

	slotsPTD[playerid][11] = CreatePlayerTextDraw(playerid, 433.000000, 198.000000, "win: ~g~$55.003.000");
	PlayerTextDrawFont(playerid, slotsPTD[playerid][11], 2);
	PlayerTextDrawLetterSize(playerid, slotsPTD[playerid][11], 0.150000, 1.000001);
	PlayerTextDrawTextSize(playerid, slotsPTD[playerid][11], 400.000000, 172.000000);
	PlayerTextDrawSetOutline(playerid, slotsPTD[playerid][11], 1);
	PlayerTextDrawSetShadow(playerid, slotsPTD[playerid][11], 0);
	PlayerTextDrawAlignment(playerid, slotsPTD[playerid][11], 2);
	PlayerTextDrawColor(playerid, slotsPTD[playerid][11], -1);
	PlayerTextDrawBackgroundColor(playerid, slotsPTD[playerid][11], 255);
	PlayerTextDrawBoxColor(playerid, slotsPTD[playerid][11], 50);
	PlayerTextDrawUseBox(playerid, slotsPTD[playerid][11], 0);
	PlayerTextDrawSetProportional(playerid, slotsPTD[playerid][11], 1);
	PlayerTextDrawSetSelectable(playerid, slotsPTD[playerid][11], 0);

	slotsPTD[playerid][12] = CreatePlayerTextDraw(playerid, 238.000000, 163.000000, "ld_card:cdback");
	PlayerTextDrawFont(playerid, slotsPTD[playerid][12], 4);
	PlayerTextDrawLetterSize(playerid, slotsPTD[playerid][12], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, slotsPTD[playerid][12], 48.000000, 81.500000);
	PlayerTextDrawSetOutline(playerid, slotsPTD[playerid][12], 1);
	PlayerTextDrawSetShadow(playerid, slotsPTD[playerid][12], 0);
	PlayerTextDrawAlignment(playerid, slotsPTD[playerid][12], 1);
	PlayerTextDrawColor(playerid, slotsPTD[playerid][12], -1);
	PlayerTextDrawBackgroundColor(playerid, slotsPTD[playerid][12], 255);
	PlayerTextDrawBoxColor(playerid, slotsPTD[playerid][12], 50);
	PlayerTextDrawUseBox(playerid, slotsPTD[playerid][12], 1);
	PlayerTextDrawSetProportional(playerid, slotsPTD[playerid][12], 1);
	PlayerTextDrawSetSelectable(playerid, slotsPTD[playerid][12], 0);

	slotsPTD[playerid][13] = CreatePlayerTextDraw(playerid, 332.000000, 206.000000, "gamble to win:~n~~g~$100.100.100");
	PlayerTextDrawFont(playerid, slotsPTD[playerid][13], 2);
	PlayerTextDrawLetterSize(playerid, slotsPTD[playerid][13], 0.150000, 1.000001);
	PlayerTextDrawTextSize(playerid, slotsPTD[playerid][13], 400.000000, 172.000000);
	PlayerTextDrawSetOutline(playerid, slotsPTD[playerid][13], 1);
	PlayerTextDrawSetShadow(playerid, slotsPTD[playerid][13], 0);
	PlayerTextDrawAlignment(playerid, slotsPTD[playerid][13], 2);
	PlayerTextDrawColor(playerid, slotsPTD[playerid][13], -1);
	PlayerTextDrawBackgroundColor(playerid, slotsPTD[playerid][13], 255);
	PlayerTextDrawBoxColor(playerid, slotsPTD[playerid][13], 50);
	PlayerTextDrawUseBox(playerid, slotsPTD[playerid][13], 0);
	PlayerTextDrawSetProportional(playerid, slotsPTD[playerid][13], 1);
	PlayerTextDrawSetSelectable(playerid, slotsPTD[playerid][13], 0);

	slotsPTD[playerid][14]  = CreatePlayerTextDraw(playerid, 332.000000, 167.000000, "gamble amount:~n~~g~$1.000.000");
	PlayerTextDrawFont(playerid, slotsPTD[playerid][14] , 2);
	PlayerTextDrawLetterSize(playerid, slotsPTD[playerid][14] , 0.150000, 1.000001);
	PlayerTextDrawTextSize(playerid, slotsPTD[playerid][14] , 400.000000, 172.000000);
	PlayerTextDrawSetOutline(playerid, slotsPTD[playerid][14] , 1);
	PlayerTextDrawSetShadow(playerid, slotsPTD[playerid][14] , 0);
	PlayerTextDrawAlignment(playerid, slotsPTD[playerid][14] , 2);
	PlayerTextDrawColor(playerid, slotsPTD[playerid][14] , -1);
	PlayerTextDrawBackgroundColor(playerid, slotsPTD[playerid][14] , 255);
	PlayerTextDrawBoxColor(playerid, slotsPTD[playerid][14] , 50);
	PlayerTextDrawUseBox(playerid, slotsPTD[playerid][14] , 0);
	PlayerTextDrawSetProportional(playerid, slotsPTD[playerid][14] , 1);
	PlayerTextDrawSetSelectable(playerid, slotsPTD[playerid][14] , 0);
	
	slotsPTD[playerid][15] = CreatePlayerTextDraw(playerid, 433.000000, 237.000000, "3_lines");
	PlayerTextDrawFont(playerid, slotsPTD[playerid][15], 2);
	PlayerTextDrawLetterSize(playerid, slotsPTD[playerid][15], 0.125000, 0.900000);
	PlayerTextDrawTextSize(playerid, slotsPTD[playerid][15], 400.000000, 172.000000);
	PlayerTextDrawSetOutline(playerid, slotsPTD[playerid][15], 1);
	PlayerTextDrawSetShadow(playerid, slotsPTD[playerid][15], 0);
	PlayerTextDrawAlignment(playerid, slotsPTD[playerid][15], 2);
	PlayerTextDrawColor(playerid, slotsPTD[playerid][15], -1);
	PlayerTextDrawBackgroundColor(playerid, slotsPTD[playerid][15], 255);
	PlayerTextDrawBoxColor(playerid, slotsPTD[playerid][15], 50);
	PlayerTextDrawUseBox(playerid, slotsPTD[playerid][15], 0);
	PlayerTextDrawSetProportional(playerid, slotsPTD[playerid][15], 1);
	PlayerTextDrawSetSelectable(playerid, slotsPTD[playerid][15], 0);
	return true;
}
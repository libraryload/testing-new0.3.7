#include <YSI_Coding\y_hooks>

#define MAX_HELPER_QUESTIONS (30)

enum helperData
{
    questionSender, questionMessage[144], questionHelper
};
new newbieQuestions[MAX_HELPER_QUESTIONS][helperData], playerNewbieQuestion[MAX_PLAYERS], helperAssignedQuestion[MAX_PLAYERS];

new
    Iterator: helperQuestions<MAX_HELPER_QUESTIONS>,
    Iterator: helperAQuestions<MAX_HELPER_QUESTIONS>,
    Iterator: helpersOnDuty<MAX_PLAYERS>,
    Iterator: helpersWithQuestion<MAX_PLAYERS>;

hook OnPlayerConnect(playerid)
{
	helperAssignedQuestion[playerid] = -1;
	playerNewbieQuestion[playerid] = -1;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    new
        questionId = playerNewbieQuestion[playerid],
        questionHelperId = helperAssignedQuestion[playerid];

    if(questionId != -1)
    {
        SCM(newbieQuestions[questionId][questionHelper], COLOR_YELLOW, "Jucatorul ce a pus intrebarea a parasit serverul!");

        Iter_Remove(helperQuestions, questionId);
        Iter_Remove(helperAQuestions, questionId);

        DeletePVar(newbieQuestions[questionId][questionHelper], "newbieQuestionAnswer");

        playerNewbieQuestion[playerid] = -1;
        newbieQuestions[questionId][questionSender] = -1;
        newbieQuestions[questionId][questionHelper] = -1;
        format(newbieQuestions[questionId][questionMessage], 144, "");
    }

    if(questionHelperId != -1)
    {
        Iter_Remove(helperAQuestions, questionId);
        Iter_Remove(helpersWithQuestion, playerid);

        helperAssignedQuestion[playerid] = -1;
    }

    if(Iter_Contains(helpersWithQuestion, playerid))
    	Iter_Remove(helpersWithQuestion, playerid);

    if(Iter_Contains(helpersOnDuty, playerid))
    	Iter_Remove(helpersOnDuty, playerid);

	return Y_HOOKS_CONTINUE_RETURN_1;
}

function initiateServerQuestions()
{
	if(Iter_Count(helperQuestions) != 0 && Iter_Count(helpersOnDuty))
    {
        new
            questionId = Iter_Random(helperQuestions);

        if(newbieQuestions[questionId][questionHelper] == -1)
        {
            new 
                helperid = Iter_Random(helpersOnDuty);

            Iter_Add(helpersWithQuestion, helperid);
            Iter_Add(helperAQuestions, questionId);

            helperAssignedQuestion[helperid] = questionId;
            newbieQuestions[questionId][questionHelper] = helperid;

            SCMF(helperid, COLOR_YELLOW, "** Question from %s (%d, level %d) **", GetName(newbieQuestions[questionId][questionSender]), newbieQuestions[questionId][questionSender], PlayerInfo[newbieQuestions[questionId][questionSender]][pLevel]);
            SCMF(helperid, COLOR_YELLOW, newbieQuestions[questionId][questionMessage]);
        }
    }
    return 1;
}

function afk_helper_check(playerid)
{
    if(Iter_Contains(helpersOnDuty, playerid) && s_PlayerInfo[playerid][pSAFK] >= 60)
    {
        SCM(playerid, COLOR_LIGHTRED, "Ai fost trecut ca si helper OFF DUTY deoarece ai fost AFK peste 120 secunde.");

        Iter_Remove(helpersOnDuty, playerid);

        new
            questionId = helperAssignedQuestion[playerid];

        if(questionId != -1)
        {
            Iter_Remove(helperAQuestions, questionId);
            Iter_Remove(helpersWithQuestion, playerid);
            newbieQuestions[questionId][questionHelper] = -1;
        }   
    }
    return 1;
}

YCMD:nqueue(playerid, params[], help)
{
    if(PlayerInfo[playerid][pHelper] < 1 && PlayerInfo[playerid][pAdmin] < 1)
        return sendAcces(playerid);

    return SCMF(playerid, COLOR_YELLOW, "There are %d pending questions and %d on-duty helpers.", Iter_Count(helperQuestions) - Iter_Count(helperAQuestions), Iter_Count(helpersOnDuty));
}

YCMD:myquestion(playerid, params[], help)
{
    if(playerNewbieQuestion[playerid] == -1)
        return SCM(playerid, COLOR_NEWBIE, "Nu ai nicio intrebare pusa pe chatul incepatorilor!");

    return SCMF(playerid, COLOR_NEWBIE, "[N] Intrebarea ta: %s", newbieQuestions[playerNewbieQuestion[playerid]][questionMessage]);
}

YCMD:ncurrent(playerid, params[], help)
{
    if(PlayerInfo[playerid][pHelper] < 1 && PlayerInfo[playerid][pAdmin] < 1 || helperAssignedQuestion[playerid] == -1)
        return SCM(playerid, COLOR_LIGHTRED, "Nu esti helper/admin sau nu ai o intrebare activa!");

    new
        questionId = helperAssignedQuestion[playerid];

    SCMF(playerid, COLOR_YELLOW, "** Question from %s (%d, level %d) **", GetName(newbieQuestions[questionId][questionSender]), newbieQuestions[questionId][questionSender], PlayerInfo[newbieQuestions[questionId][questionSender]][pLevel]);
    SCMF(playerid, COLOR_YELLOW, newbieQuestions[questionId][questionMessage]);
    return 1;
}

YCMD:newbie(playerid, params[], help)
{
    if(!PlayerInfo[playerid][pHelper] && !PlayerInfo[playerid][pAdmin])
    {
        new
            questionText[144];

        if(sscanf(params, "s[144]", questionText))
            return SCM(playerid, COLOR_NEWBIE, "Syntax: /n(ewbiechat) <text>");

        if(!s_PlayerInfo[playerid][pSNewbieEnabled])
            return SCM(playerid, -1, "Nu poti trimite mesaje deoarece ai oprit acest chat.");

        if(playerNewbieQuestion[playerid] != -1)
            return SCMF(playerid, COLOR_NEWBIE, "Deja ai o intrebare pusa! Foloseste /myquestion pentru a-ti vedea intrebarea. Aceasta va expira in %d secunde.", GetPVarInt(playerid, "questionDelay") - gettime());
    
        if(strlen(questionText) < 10)
            return SCM(playerid, COLOR_NEWBIE, "[N] Intrebarea ta trebuie sa contina macar 10 caractere!");

        if(!Iter_Count(helpersOnDuty))
            return SCM(playerid, COLOR_NEWBIE, "[N] Ne pare rau dar nu sunt helperi/administratori on-duty pentru a iti prelua intrebarea!");

        SCM(playerid, COLOR_NEWBIE, "Intrebarea ta a fost trimisa cu succes!");

        playerNewbieQuestion[playerid] = Iter_Count(helperQuestions) + 1;
    
        new
            questionId = playerNewbieQuestion[playerid];
        
        Iter_Add(helperQuestions, questionId);

        newbieQuestions[questionId][questionSender] = playerid;
        newbieQuestions[questionId][questionHelper] = -1;

        format(newbieQuestions[questionId][questionMessage], 144, questionText);
    }   
    else
    {
        if(helperAssignedQuestion[playerid] == -1)
            return SCM(playerid, -1, "Nu ai o intrebare activa!");
        
        new
            questionAddQuest[144], questionAnswer[512];
        
        if(sscanf(params, "s[144]", questionAddQuest))
            return SCM(playerid, -1, "Syntax: /n [raspuns]");

        GetPVarString(playerid, "newbieQuestionAnswer", questionAnswer, sizeof questionAnswer);

        if(strlen(questionAnswer) + strlen(questionAddQuest) >= 510)
        {
            SCM(playerid, -1, "Nu pot adauga input-ul curent raspunului tau deoarece acesta depaseste limita maxima admisa (512). Incearca sa scrii mai putin.");
            return SCMF(playerid, COLOR_GREY, "Raspunsul tau pana acum:%s", questionAnswer);
        }

        format(questionAnswer, 512, "%s %s", questionAnswer, questionAddQuest);

        SetPVarString(playerid, "newbieQuestionAnswer", questionAnswer);
        return SCMF(playerid, COLOR_GREY, "Raspunsul tau pana acum:%s", questionAnswer);
    }
    return 1;
}

YCMD:nreport(playerid, params[], help)
{
    if(PlayerInfo[playerid][pHelper] < 1 && !PlayerInfo[playerid][pAdmin] || helperAssignedQuestion[playerid] == -1 && !PlayerInfo[playerid][pAdmin])
        return SCM(playerid, COLOR_LIGHTRED, "Nu esti helper/admin sau nu ai o intrebare activa!");

    new
        questionId = helperAssignedQuestion[playerid];

    if(PlayerInfo[playerid][pAdmin])
    {
        new id;
        if(sscanf(params, "u", id)) return SCM(playerid, COLOR_GREY, "Syntax: {FFFFFF}/nreport [playername/playerid]");
    
        if(!IsPlayerConnected(id))
            return SCM(playerid, COLOR_GREY, "Player not connected.");

        questionId = PlayerInfo[playerid][pHelper] ? helperAssignedQuestion[playerid] : playerNewbieQuestion[id];

        if(playerNewbieQuestion[id] == -1 || newbieQuestions[questionId][questionSender] == id && newbieQuestions[questionId][questionHelper] != -1)
            return SCMF(playerid, COLOR_GREY, "Jucatorul %s nu are o intrebare activa sau nealocata unui helper.", GetName(id));
    }
    sendStaffMessage(COLOR_ORANGE, "%s marked %s (%d) question as report: %s", GetName(playerid), GetName(newbieQuestions[questionId][questionSender]), newbieQuestions[questionId][questionSender], newbieQuestions[questionId][questionMessage]);
    SCMF(newbieQuestions[questionId][questionSender], COLOR_LIGHTRED, "(!) Intrebarea ta a fost marcata drept report de catre helperul/administratorul %s.", GetName(playerid));

    SetPVarString(newbieQuestions[questionId][questionSender], "o_report_reason", newbieQuestions[questionId][questionMessage]);
    SetPVarInt(newbieQuestions[questionId][questionSender], "o_report_time", gettime());
    SetPVarInt(newbieQuestions[questionId][questionSender], "o_report_type", REPORT_TYPE_OTHER);

    if(!Iter_Contains(sendReport, newbieQuestions[questionId][questionSender]))
        Iter_Add(sendReport, newbieQuestions[questionId][questionSender]);

    Iter_Remove(helperQuestions, questionId);
    Iter_Remove(helperAQuestions, questionId);
    
    if(Iter_Contains(helpersWithQuestion, playerid))
        Iter_Remove(helpersWithQuestion, playerid);

    playerNewbieQuestion[newbieQuestions[questionId][questionSender]] = -1;
    format(newbieQuestions[questionId][questionMessage], 144, "");

    DeletePVar(playerid, "newbieQuestionAnswer");

    newbieQuestions[questionId][questionSender] = -1;
    newbieQuestions[questionId][questionHelper] = -1;
    helperAssignedQuestion[playerid] = -1;
    return 1;
}

YCMD:nsend(playerid, params[], help)
{
    if(PlayerInfo[playerid][pHelper] < 1 && PlayerInfo[playerid][pAdmin] < 1 || helperAssignedQuestion[playerid] == -1)
        return SCM(playerid, COLOR_LIGHTRED, "Nu esti helper/admin sau nu ai o intrebare activa!");

    new
        questionAnswer[512];

    GetPVarString(playerid, "newbieQuestionAnswer", questionAnswer, sizeof questionAnswer);

    if(!strlen(questionAnswer))
        return SCM(playerid, -1, "Nu ai raspuns intrebarii.");

    new
        questionId = helperAssignedQuestion[playerid];

    foreach(new i : Player)
    {
        format(gString, 144, "* Newbie %s: %s", GetName(newbieQuestions[questionId][questionSender]), newbieQuestions[questionId][questionMessage]);
        sendLongMessage(i, COLOR_NEWBIE, gString);

        format(gString, sizeof gString, "* Helper %s:%s", GetName(playerid), questionAnswer);
        if(i != newbieQuestions[questionId][questionSender])
            sendLongMessage(i, COLOR_NEWBIE, gString);
    }
    sendLongMessage(newbieQuestions[questionId][questionSender], COLOR_YELLOW, gString);

    Iter_Remove(helperQuestions, questionId);
    Iter_Remove(helperAQuestions, questionId);
    Iter_Remove(helpersWithQuestion, playerid);

    playerNewbieQuestion[newbieQuestions[questionId][questionSender]] = -1;
    format(newbieQuestions[questionId][questionMessage], 144, "");

    DeletePVar(playerid, "newbieQuestionAnswer");

    newbieQuestions[questionId][questionSender] = -1;
    newbieQuestions[questionId][questionHelper] = -1;
    helperAssignedQuestion[playerid] = -1;
    return 1;
}

YCMD:ndelete(playerid, params[], help)
{
    if(PlayerInfo[playerid][pHelper] < 1 && PlayerInfo[playerid][pAdmin] < 1 || helperAssignedQuestion[playerid] == -1)
        return SCM(playerid, COLOR_LIGHTRED, "Nu esti helper/admin sau nu ai o intrebare activa!");

    new
        questionAnswer[144];

    if(sscanf(params, "s[144]", questionAnswer))
        return SCM(playerid, COLOR_GREY, "Syntax: {FFFFFF}/ndelete [reason]");

    new
        questionId = helperAssignedQuestion[playerid];

    format(gString, 144, "* Newbie %s: %s", GetName(newbieQuestions[questionId][questionSender]), newbieQuestions[questionId][questionMessage]);
    sendLongMessage(newbieQuestions[questionId][questionSender], COLOR_NEWBIE, gString);

    foreach(new i : Admins)
    {
        sendLongMessage(i, COLOR_NEWBIE, gString);

        format(gString, 144, "(/nd) * Helper %s: %s", GetName(playerid), questionAnswer);
        sendLongMessage(i, COLOR_NEWBIE, gString);
    }

    foreach(new i : Helpers)
    {
        sendLongMessage(i, COLOR_NEWBIE, gString);

        format(gString, 144, "(/nd) * Helper %s: %s", GetName(playerid), questionAnswer);
        sendLongMessage(i, COLOR_NEWBIE, gString);
    }
    sendLongMessage(newbieQuestions[questionId][questionSender], COLOR_YELLOW, gString);

    Iter_Remove(helperQuestions, questionId);
    Iter_Remove(helperAQuestions, questionId);
    Iter_Remove(helpersWithQuestion, playerid);

    playerNewbieQuestion[newbieQuestions[questionId][questionSender]] = -1;
    format(newbieQuestions[questionId][questionMessage], 144, "");

    DeletePVar(playerid, "newbieQuestionAnswer");

    newbieQuestions[questionId][questionSender] = -1;
    newbieQuestions[questionId][questionHelper] = -1;
    helperAssignedQuestion[playerid] = -1;
    return 1;
}

YCMD:nskip(playerid, params[], help)
{
    if(PlayerInfo[playerid][pHelper] < 1 && PlayerInfo[playerid][pAdmin] < 1 || helperAssignedQuestion[playerid] == -1)
        return SCM(playerid, COLOR_LIGHTRED, "Nu esti helper/admin sau nu ai o intrebare activa!");

    SCM(playerid, COLOR_YELLOW, "Ai sarit peste aceasta intrebare!");
    SCM(playerid, -1, "Daca nu sunt alte intrebari este posibil sa primesti tot aceasta intrebare.");
    SCM(playerid, COLOR_NEWBIE, "Getting a new question...");

    new
        questionId = helperAssignedQuestion[playerid];

    DeletePVar(playerid, "newbieQuestionAnswer");

    Iter_Remove(helperAQuestions, questionId);
    Iter_Remove(helpersWithQuestion, playerid);
    newbieQuestions[questionId][questionHelper] = -1;

    helperAssignedQuestion[playerid] = -1;

    return 1;
}

YCMD:nnext(playerid, params[], help)
{
    if(PlayerInfo[playerid][pHelper] < 1 && PlayerInfo[playerid][pAdmin] < 1 || helperAssignedQuestion[playerid] != -1)
        return SCM(playerid, COLOR_LIGHTRED, "Nu esti helper/admin sau ai o intrebare activa!");

    if(!Iter_Contains(helpersOnDuty, playerid))
        return SCM(playerid, COLOR_GREY, "Pentru a folosi aceasta comanda trebuie sa fii on duty ca si helper.");

    if(!Iter_Count(helperQuestions))
        return SCM(playerid, -1, "Nu exista intrebari care sa poata fi alocate.");

    if(Iter_Count(helperQuestions) >= Iter_Count(helpersOnDuty))
    {
        new
            questionId = Iter_Random(helperQuestions);

        if(newbieQuestions[questionId][questionHelper] == -1)
        {
            Iter_Add(helpersWithQuestion, playerid);
            Iter_Add(helperAQuestions, questionId);

            helperAssignedQuestion[playerid] = questionId;
            newbieQuestions[questionId][questionHelper] = playerid;

            SCMF(playerid, COLOR_YELLOW, "** Question from %s (%d, level %d) **", GetName(newbieQuestions[questionId][questionSender]), newbieQuestions[questionId][questionSender], PlayerInfo[newbieQuestions[questionId][questionSender]][pLevel]);
            SCMF(playerid, COLOR_YELLOW, newbieQuestions[questionId][questionMessage]);
        }
    }
    else
        SCM(playerid, COLOR_GREY, "Nu poti folosi aceasta comanda in acest moment deoarece sunt mai putine intrebari in asteptare decat helperi on-duty!");
    
    return 1;
}

YCMD:hquestions(playerid, params[], help)
{
    if(PlayerInfo[playerid][pHelper] < 0 && PlayerInfo[playerid][pAdmin] < 0)
        return sendAcces(playerid);

    foreach(new questionId : helperQuestions)
    {
        if(newbieQuestions[questionId][questionHelper] == -1)
            SCMF(playerid, COLOR_NEWBIE, "Question: '%s' by %s (%d).", newbieQuestions[questionId][questionMessage], GetName(newbieQuestions[questionId][questionSender]), newbieQuestions[questionId][questionSender]);
        else
            SCMF(playerid, COLOR_NEWBIE, "Question: '%s' by %s (%d) - assigned to %s (%d).", newbieQuestions[questionId][questionMessage], GetName(newbieQuestions[questionId][questionSender]), newbieQuestions[questionId][questionSender], GetName(newbieQuestions[questionId][questionHelper]), newbieQuestions[questionId][questionHelper]);
    }
    return SCMF(playerid, COLOR_NEWBIE, "Total newbie questions: %d (%d assigned to helpers). Total helpers on-duty: %d", Iter_Count(helperQuestions), Iter_Count(helperAQuestions), Iter_Count(helpersOnDuty));
}

YCMD:hduty(playerid, params[], help)
{
    if(PlayerInfo[playerid][pHelper] < 0 && PlayerInfo[playerid][pAdmin] < 0)
        return sendAcces(playerid);

    if(!Iter_Contains(helpersOnDuty, playerid))
    {
        SCM(playerid, COLOR_YELLOW, "Acum esti on-duty ca helper.");
        Iter_Add(helpersOnDuty, playerid);
    }
    else
    {
        SCM(playerid, COLOR_YELLOW, "Nu mai esti duty on ca helper.");
        Iter_Remove(helpersOnDuty, playerid);

        new
            questionId = helperAssignedQuestion[playerid];

        if(questionId != -1)
        {
            DeletePVar(playerid, "newbieQuestionAnswer");

            Iter_Remove(helperAQuestions, questionId);
            Iter_Remove(helpersWithQuestion, playerid);
            newbieQuestions[questionId][questionHelper] = -1;
        }
    }
    return 1;
}

YCMD:togn(playerid, params[], help)
{
    SCMF(playerid, -1, "You will %s see newbie chat.", s_PlayerInfo[playerid][pSNewbieEnabled] ? ("no longer") : ("now see"));
    
    s_PlayerInfo[playerid][pSNewbieEnabled] = s_PlayerInfo[playerid][pSNewbieEnabled] ? 0 : 1;
    return 1;
}

YCMD:hre(playerid, params[], help)
{
    if(PlayerInfo[playerid][pAdmin] < 1 && PlayerInfo[playerid][pHelper] < 1)
        return SCM(playerid, -1, "{5CAD5C}Error: Your admin/helper level isn't high enough to use this command.");

    new
        id, sMessage[128];

    if(sscanf(params, "us[128]", id, sMessage))
        return sendSyntax(playerid, "/hre [name/playerid] [text]");

    if(!IsPlayerConnected(id))
        return SCM(playerid, COLOR_GREY, "Player not connected.");

    if(playerid == id)
        return SCM(playerid, -1, "You can't use this command on yourself'.");

    sendStaffMessage(COLOR_YELLOW, "/hre: %s->%s: %s", GetName(playerid), GetName(id), sMessage);
    SCMF(id, COLOR_YELLOW, "> PM from %s: %s", GetName(playerid), sMessage);

    PlayerPlaySound(id, 1139, 0.0, 0.0, 0.0);
    return 1;
}
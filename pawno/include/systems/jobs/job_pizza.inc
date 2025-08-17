#include <YSI_Coding\y_hooks>

#define CP_PIZZA (CP_JOBS_BEGIN) + JOB_TYPE_PIZZA
#define PIZZA_MONEY (20000)

enum {
    PIZZA_TOTAL_BOXES, PIZZA_HOUSE_ID 
}

new
    pizza_data[MAX_PLAYERS][2], pizza_object[MAX_PLAYERS][5];

reset_pizza_vars(playerid)
{
    pizza_data[playerid][PIZZA_TOTAL_BOXES] = 0;
    pizza_data[playerid][PIZZA_HOUSE_ID] = 0;
}

cancel_pizza_work(playerid)
{
    if(job_data[playerid][jobDuty] != JOB_TYPE_PIZZA)
        return 1;

    for(new i; i < job::returnPlayerSkill(playerid, JOB_TYPE_PIZZA); ++i)
    {
        if(IsValidDynamicObject(pizza_object[playerid][i]))
            DestroyDynamicObject(pizza_object[playerid][i]);
    }// distrugere obiecte pizza 
    
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    reset_pizza_vars(playerid);

    return 1;
}

start_pizza_work(playerid)
{
    SCM(playerid, -1, "{909CE7}(Job):{FFFFFF} Mergi la checkpoint si livreza o cutie de pizza pentru a fi platit.");

    if(!IsValidVehicle(job_data[playerid][jobVehicle]))
    {
        new
            Float: vPos[3];

        GetPlayerPos(playerid, vPos[0], vPos[1], vPos[2]);
        job::createJobVehicle(playerid, 448, vPos[0], vPos[1], vPos[2], 90.0, 120);
    }

    for(new i; i < job::returnPlayerSkill(playerid, JOB_TYPE_PIZZA); ++i)
    {
        pizza_object[playerid][i] = CreateDynamicObject(1582, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000);
        AttachDynamicObjectToVehicle(pizza_object[playerid][i], job_data[playerid][jobVehicle], -0.005000, -0.899999, 0.499999+i*0.0705, 0.000000, 0.000000, 0.000000);
    }
    pizza_data[playerid][PIZZA_TOTAL_BOXES] = job::returnPlayerSkill(playerid, JOB_TYPE_PIZZA);

    return give_pizza_cp(playerid);
}

give_pizza_cp(playerid)
{    
    new
        house = RandomEx(1, 46);
    
    if(house == pizza_data[playerid][PIZZA_HOUSE_ID] && pizza_data[playerid][PIZZA_HOUSE_ID] != 0)
        return give_pizza_cp(playerid);

    DisablePlayerCheckpoint(playerid);
    SetJobCheckpoint(playerid, HouseInfo[house][hExterior][0], HouseInfo[house][hExterior][1], HouseInfo[house][hExterior][2], 2.0);
    
    pizza_data[playerid][PIZZA_HOUSE_ID] = house;
    
    s_PlayerInfo[playerid][pSCP] = CP_PIZZA;
    return 1;
}

give_pizza_money(playerid)
{
    new
        job_money = (PIZZA_MONEY) + (job::returnPlayerSkill(playerid, JOB_TYPE_PIZZA) * 1000 + RandomEx((job::returnPlayerSkill(playerid, JOB_TYPE_PIZZA) * 1000), (job::returnPlayerSkill(playerid, JOB_TYPE_PIZZA) * 1000) + 2000));
    
    SCMF(playerid, -1, "{909CE7}(Job):{FFFFFF} Ai primit $%s pentru aceasta pizza livrata.", FormatNumber(job_money));
    GivePlayerMoney(playerid, job_money);
    return job::updateJobSkill(playerid, JOB_TYPE_PIZZA);
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(job_data[playerid][jobDuty] == JOB_TYPE_PIZZA)
    {
        for(new i; i < job::returnPlayerSkill(playerid, JOB_TYPE_PIZZA); ++i)
        {
            if(IsValidDynamicObject(pizza_object[playerid][i]))
                DestroyDynamicObject(pizza_object[playerid][i]);
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == KEY_WALK)
    {
        if(job_data[playerid][jobDuty] == JOB_TYPE_PIZZA)
        {
            new
                house = pizza_data[playerid][PIZZA_HOUSE_ID];
            
            if(!IsPlayerInRangeOfPoint(playerid, 25.0, HouseInfo[house][hExterior][0], HouseInfo[house][hExterior][1], HouseInfo[house][hExterior][2]))
                return 1;

            if(!IsPlayerNearVehicle(playerid, job_data[playerid][jobVehicle], 2.0))
                return 1;

            if(IsPlayerAttachedObjectSlotUsed(playerid, JOB_INDEX))
                return 1;

            if(pizza_data[playerid][PIZZA_TOTAL_BOXES] != 0)
                pizza_data[playerid][PIZZA_TOTAL_BOXES] --;

            if(IsValidDynamicObject(pizza_object[playerid][pizza_data[playerid][PIZZA_TOTAL_BOXES]]))
                DestroyDynamicObject(pizza_object[playerid][pizza_data[playerid][PIZZA_TOTAL_BOXES]]);

            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
            SetPlayerAttachedObject(playerid, JOB_INDEX, 1582, 1, 0.002953, 0.469660, -0.009797, 269.851104, 88.443557, 0.000000, 0.804894, 1.000000, 0.822361);
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterCheckpoint(playerid)
{
    if(s_PlayerInfo[playerid][pSCP] == CP_PIZZA && job_data[playerid][jobDuty] == JOB_TYPE_PIZZA)
    {
        if(!pizza_data[playerid][PIZZA_HOUSE_ID])
        {
            if(!IsPlayerInVehicle(playerid, job_data[playerid][jobVehicle]))
                return 1;

            return start_pizza_work(playerid);
        }
        else
        {
            if(!IsPlayerAttachedObjectSlotUsed(playerid, JOB_INDEX))
                return SCM(playerid, -1, "{909CE7}(Job):{FFFFFF} Nu ai nicio cutie de pizza pentru a o livra.");

            ApplyAnimation(playerid, "CARRY", "LIFTUP05", 4.1, 0, 0, 0, 0, 0);

            if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CARRY)
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            if(IsPlayerAttachedObjectSlotUsed(playerid, JOB_INDEX))
                RemovePlayerAttachedObject(playerid, JOB_INDEX);

            give_pizza_money(playerid);

            if(pizza_data[playerid][PIZZA_TOTAL_BOXES] == 0)
            {
                SCM(playerid, -1, "{909CE7}(Job):{FFFFFF} Ai livrat toate cutiile de pizza. Pentru a realimenta mergi la checkpoint-ul marcat pe minimap.");
                DailyQuestCheck(playerid, QUEST_TYPE_PIZZA, 1); //2nd check

                reset_pizza_vars(playerid);

                s_PlayerInfo[playerid][pSCP] = CP_PIZZA;
                return SetJobCheckpoint(playerid, jobWorkLocations[JOB_TYPE_PIZZA][0], jobWorkLocations[JOB_TYPE_PIZZA][1], jobWorkLocations[JOB_TYPE_PIZZA][2], 4.0);
            }
            SCMF(playerid, -1, "{909CE7}(Job):{FFFFFF} Mai ai %d cutii de pizza. Mergi la checkpoint pentru a continua munca.", pizza_data[playerid][PIZZA_TOTAL_BOXES]);

            DailyQuestCheck(playerid, QUEST_TYPE_PIZZA, 1);
            give_pizza_cp(playerid);
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER)
    {
        if(job_data[playerid][jobVehicle] == s_PlayerInfo[playerid][pSLastVehicle] && job_data[playerid][jobVehicle] && job_data[playerid][jobDuty] == JOB_TYPE_PIZZA)
        {
            SCM(playerid, -1, "{909CE7}(Job):{FFFFFF} Pentru a lua o pizza de pe vehicul apasa ALT in spatele acestuia.");
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}
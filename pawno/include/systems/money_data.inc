/*  =============================================================================

		Credits: ionchyAdv
		Help & Others: iReplay
	
		FormatIntNumberLY - can be used to format a number less than 2.147.483.647
		CreateLocalLY - separates the string (money amount) into two variables as prefix and suffix
		GivePlayerCash - give money specific player (extra money over limit [999.999.999] will be added in bank)
		GivePlayerBank - adding money to bank using prefix and suffix
		OperatorBankCheck - check if player have enough money in bank compared to prefix and suffix

    ============================================================================== */

//new localString[128];

#define MAX_LY_LENGHT (10)
#define MAX_LY_STRING (30)

#define MAX_LY_PREFIX (999999999)

enum {
	COMPARE_RESULT_NULL,
	COMPARE_RESULT_FIRST,
	COMPARE_RESULT_SECOND,
	COMPARE_RESULT_EQUAL
};


function CreateLocalLY(&varPrefix, &varSuffix, amountString[])
{
	new
		varPrefixStr[MAX_LY_STRING], varSuffixStr[MAX_LY_STRING];

	if(strlen(amountString) >= MAX_LY_LENGHT)
	{
		strmid(varPrefixStr, amountString, 0, strlen(amountString)+1 - MAX_LY_LENGHT);

		strdel(amountString, 0, strlen(amountString)+1 - MAX_LY_LENGHT);
	}
	format(varSuffixStr, MAX_LY_STRING, amountString); // setting remaining money as Suffix

	varPrefix = strval(varPrefixStr);
	varSuffix = strval(varSuffixStr);

	return 1;
}

forward public GivePlayerCash(playerid, moneyAmount);
public GivePlayerCash(playerid, moneyAmount)
{
	PlayerInfo[playerid][pCash] += moneyAmount;

    if(PlayerInfo[playerid][pCash] > MAX_LY_PREFIX && moneyAmount)
    {
    	new
    		newBankMoney = PlayerInfo[playerid][pCash] - MAX_LY_PREFIX;

    	PlayerInfo[playerid][pAccount] += newBankMoney;
    	PlayerInfo[playerid][pCash] -= newBankMoney;

        if(PlayerInfo[playerid][pAccount] >= MAX_LY_PREFIX)
        {
            PlayerInfo[playerid][pAccount] -= MAX_LY_PREFIX;
            PlayerInfo[playerid][pAccountLY] ++;
        }
 		/* update pe viitor
        mysql_format(SQL, gString, 256, "UPDATE `users` SET `Bank` = '%d' WHERE `id` = '%d' LIMIT 1", PlayerInfo[playerid][pAccount], PlayerInfo[playerid][pSQLID]);
        mysql_tquery(SQL, gString);*/

        SendClientMessage(playerid, 0xFF8080FF, "[money update]: money limit reached! the extra money was added into the bank.");
    }
    
    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);
    /*
    mysql_format(SQL, gString, 256, "UPDATE `users` SET `Money` = '%d' WHERE `id` = '%d' LIMIT 1", GetPlayerCash(playerid), PlayerInfo[playerid][pSQLID]);
    mysql_tquery(SQL, gString);*/
    return true;
}

forward public GivePlayerBank(playerid, moneyPrefix, moneySuffix);
public GivePlayerBank(playerid, moneyPrefix, moneySuffix)
{
	PlayerInfo[playerid][pAccount] += moneySuffix;

    if(PlayerInfo[playerid][pAccount] >= MAX_LY_PREFIX)
    {
        PlayerInfo[playerid][pAccount] -= MAX_LY_PREFIX;
        PlayerInfo[playerid][pAccountLY] ++;
    }

    PlayerInfo[playerid][pAccountLY] += moneyPrefix;
    return 1;
}

stock GetPlayerBank(playerid)
{
	new stringMoney[64];
	string_FromatValue(PlayerInfo[playerid][pAccountLY], PlayerInfo[playerid][pAccount], stringMoney);
	format(stringMoney, 64, FormatNumberLY(stringMoney));

	return stringMoney;
}

// ================================================================================================= //

stock string_FromatValue(&prefix, &suffix, const value[])
{
	if(!prefix)
		format(value, 128, "#%d", suffix);
	else
		format(value, 128, "#%d%09d", prefix, suffix);
}

stock FormatNumberLY(...)
{
	new
		stringNumber[128], int_str = 0, firstchar[4];

	format(firstchar, sizeof firstchar, "%s", getarg(0, 0));

	if(strfind(firstchar, "#", true) == 0)
	{
		int_str = 1;
		
		new
			nr = 0;
		
		for(new i = 0; i < 128; i++)
		{
			stringNumber[nr] = getarg(0, i); 
			nr++;
		}
	}	
	if(int_str == 1)
	{
		strdel(stringNumber, 0, 1); 
		for(new i = strlen(stringNumber) - 3; i > 0; i -= 3)
			strins(stringNumber, ",", i);
	}

	if(int_str == 0)
		format(stringNumber, sizeof stringNumber, "%s", FormatIntNumberLY(getarg(0)));

	return stringNumber;
}

stock FormatIntNumberLY(intNumber, const delimitator[] = ",")
{
    new
    	formatNumber[16], bool: negativeNumber = false;

    if(intNumber < 0)
        intNumber *= -1, negativeNumber = true;

    format(formatNumber, sizeof formatNumber, "%i", intNumber);

    for(new i = strlen(formatNumber) - 3; i > 0; i -= 3)
        strins(formatNumber, delimitator, i);

    if(negativeNumber == true)
        strins(formatNumber, "", 0);
	
    return formatNumber;
}

stock GetPlayerCash(playerid) return PlayerInfo[playerid][pCash];
stock ResetPlayerCash(playerid) return PlayerInfo[playerid][pCash] = 0;

stock CompareBigInt(var_store1, var_add1, var_store2, var_add2)
{
	if(var_store2 > var_store1 || (var_store1 == var_store2 && var_add2 > var_add1)) return COMPARE_RESULT_SECOND;
	else if(var_store1 > var_store2 || (var_store1 == var_store2 && var_add1 > var_add2)) return COMPARE_RESULT_FIRST;
	else return COMPARE_RESULT_EQUAL;
}

/*
	pentru prostii ca rifla si concy.
	
	nu o sa folosim niciodata formatintnumber e un simplu formatnumber
*/
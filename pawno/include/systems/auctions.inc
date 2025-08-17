#include <YSI_Coding\y_hooks>

enum ENUM_BID_INFORMATIONS
{
	bidStatus, bidType, bidProprety, bidPlayerSQLId, bidPlayerGameId, bidMoney, bidPlayerName[MAX_PLAYER_NAME]
}
new bidInfo[ENUM_BID_INFORMATIONS];
static const resetBid[ENUM_BID_INFORMATIONS];

new Timer:bid_timer, bidTime, bidAttempt;

function StartBid(type)
{
	if(!cache_num_rows())
		return true;

	bidTime = 60000;
	bidInfo = resetBid;
	bidInfo[bidPlayerSQLId] = -1;
	bidInfo[bidPlayerGameId] = INVALID_PLAYER_ID;

	new auctionPropriety;
	auctionPropriety = cache_get_field_content_int(0, "ID");

	new auctionString[144];
	switch(type)
	{
		case 0: format(auctionString, sizeof auctionString, "Casa cu id %d a fost scoasa la licitatie, licitatia nu va porni pana nu este facuta o oferta!", auctionPropriety);
		case 1: format(auctionString, sizeof auctionString, "Afacerea cu id %d a fost scoasa la licitatie, licitatia nu va porni pana nu este facuta o oferta!", auctionPropriety);
		case 2: format(auctionString, sizeof auctionString, "Apartamentul cu id %d aflat la etajul %d a fost scos la licitatie.", auctionPropriety, 1);
	}

	SendClientMessageToAll(COLOR_SERVER, auctionString);
	SendClientMessageToAll(COLOR_SERVER, "(Licitatii):{ffffff} Daca nu va licita nimeni in 60 secunde aceasta licitatie va fi amanata!");
		
	bidInfo[bidProprety] = auctionPropriety;
	bidInfo[bidType] = type;

	return bidInfo[bidStatus] = 1;
}

YCMD:togbids(playerid, params[], help)
{
	mysql_tquery(SQL, "select `ID` from `houses` where `OwnerSQL` = '0';", "StartBid", "i", 0);
	return true;
}

timer update_bid[bidTime]()
{
	if(bidTime == 30000 && bidAttempt == 2)
	{
		va_SendClientMessageToAll(COLOR_SERVER, "(Licitatii):{ffffff}  Jucatorul %s a castigat licitatia cu $%s.000.000.", bidInfo[bidPlayerName], FormatNumber(bidInfo[bidMoney]));
	
		// update in baza
	}
	else
	{
		va_SendClientMessageToAll(COLOR_SERVER, "(Licitatii):{ffffff} Daca in %d secunde nu liciteaza altcineva %s va castiga %s %d cu $%s.000.000.", (bidTime / 1000), bidInfo[bidPlayerName], (!bidInfo[bidType] ? ("casa") : ("afacerea")), bidInfo[bidProprety], FormatNumber(bidInfo[bidMoney]));
		bidTime = 30000;
		
		bid_timer = defer update_bid();
	}

	bidAttempt ++;
	return true;
}

YCMD:bid(playerid, params[], help)
{
	//Pentru a putea cumpara un bun personal [casa, afacere, apartament] trebuie sa ai 10 ore jucate in ultimele 30 zile.

	new bidMoneySuffix, bidMoneyPrefix;

	if(!bidInfo[bidProprety])
		return SCM(playerid, -1, "Nu este nicio licitatie in desfasurare. Urmatoarea licitatie va incepe in 00:00 daca mai sunt bunuri de licitat.");

	new returnMoney;
	if(sscanf(params, "i", returnMoney))
		return SCM(playerid, -1, "Foloseste: /bid <milioane>");

	if(returnMoney<bidInfo[bidMoney]+1)
		return va_SendClientMessage(playerid, -1, "Trebuie sa licitezi mai mult de $%s.000.000. Tu ai licitat $%s.000.000.", FormatNumber(bidInfo[bidMoney]), FormatNumber(returnMoney));

	new
		moneyString[32];

	format(moneyString, sizeof moneyString, "%d000000", returnMoney);
    CreateLocalLY(bidMoneyPrefix, bidMoneySuffix, moneyString);

    if(PlayerInfo[playerid][pAccountLY] < bidMoneyPrefix || PlayerInfo[playerid][pAccount] < bidMoneySuffix && !PlayerInfo[playerid][pAccountLY])
        return SCM(playerid, -1, "Nu ai bani si muie ireplay!");

    if(bidInfo[bidPlayerSQLId] != -1)
    {		
		format(moneyString, sizeof moneyString, "%d000000", bidInfo[bidMoney]);
	    CreateLocalLY(bidMoneyPrefix, bidMoneySuffix, moneyString);

	    if(strmatch(bidInfo[bidPlayerName], GetName(bidInfo[bidPlayerGameId])) && bidInfo[bidPlayerGameId] != INVALID_PLAYER_ID && s_PlayerInfo[bidInfo[bidPlayerGameId]][pSLoggedIn])
	    {
	    	new
	    		oldBidder = bidInfo[bidPlayerGameId];

	    	SCM(oldBidder, -1, "Cineva a licitat mai mult ca tine, ti-ai primit banii inapoi.");

		    PlayerInfo[oldBidder][pAccountLY] += bidMoneyPrefix;
		    PlayerInfo[oldBidder][pAccount] += bidMoneySuffix;

	    	mysql_format(SQL, gString, sizeof gString, "update `users` set `BankLY` = '%d' and `Bank` = '%d' where `id` = '%d';", PlayerInfo[oldBidder][pAccountLY], PlayerInfo[oldBidder][pAccount], PlayerInfo[oldBidder][pSQLID]);
	    	mysql_tquery(SQL, gString, "", "");
	    }
	    else
	    {
			insertPlayerMail(bidInfo[bidPlayerSQLId], gettime(), "Licitatii: Suma de $%s.000.000 ti-a fost returnata inapoi deoarece cineva a licitat mai mult decat tine.", FormatNumber(bidInfo[bidMoney]));
	    	mysql_format(SQL, gString, sizeof gString, "update `users` set `BankLY` += '%d' and `Bank` += '%d' where `id` = '%d';", bidMoneyPrefix, bidMoneySuffix, bidInfo[bidPlayerSQLId]);
	    	mysql_tquery(SQL, gString, "", "");
	    }
    }

	format(moneyString, sizeof moneyString, "%d000000", returnMoney);
    CreateLocalLY(bidMoneyPrefix, bidMoneySuffix, moneyString);
	
    PlayerInfo[playerid][pAccountLY] -= bidMoneyPrefix;

    if(PlayerInfo[playerid][pAccount] - bidMoneySuffix < 0)
    {
        if(!PlayerInfo[playerid][pAccountLY])
            return SCM(playerid, COLOR_RED, "An error has occurred. Please contact the STAFF members!");

        PlayerInfo[playerid][pAccount] += 1000000000 - PlayerInfo[playerid][pAccount] - bidMoneySuffix;
        
        PlayerInfo[playerid][pAccountLY] --;
    }
    else
        PlayerInfo[playerid][pAccount] -= bidMoneySuffix;

	va_SendClientMessageToAll(COLOR_SERVER, "(Licitatii):{ffffff} Jucatorul %s a licitat suma de $%s.000.000 si conduce licitatia!", PlayerInfo[playerid][pNormalName], FormatNumber(returnMoney));
	
	bidInfo[bidMoney] = returnMoney;

	format(bidInfo[bidPlayerName], MAX_PLAYER_NAME, PlayerInfo[playerid][pNormalName]);
	bidInfo[bidPlayerSQLId] = PlayerInfo[playerid][pSQLID];
	bidInfo[bidPlayerGameId] = playerid;

	bidTime = 60000;

	stop bid_timer;
	bid_timer = defer update_bid();
	return true;
}
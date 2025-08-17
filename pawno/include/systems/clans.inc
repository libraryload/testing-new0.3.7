#include <YSI_Coding\y_hooks>
#define pClanu            	1337
#define pClanRanku          1338


#define pExpx               1339
#define pConnectTimex       1340
enum clanInfo
{
	cName[64],
	cTag[16],
	cSlots,
	cMembers,
};
new 
	cTagPos[MAX_PLAYERS], NumeSelectat[MAX_PLAYERS];
#define MAX_CLANS 1000
new ClanInfo[ MAX_CLANS ][ clanInfo ];
new CRank[ MAX_CLANS ][ 8 ][ 32 ];

//YCMD:clan(playerid, params[], help) return cmd_cpanel( playerid, params );
function Update(playerid, type)
{
	if(IsPlayerConnected(playerid))
	{
		new var[356];
		{
			switch(type)
			{
				case pClanu:
				{
				    mysql_format(SQL, var, sizeof(var), "UPDATE `users` SET `Clan`= '%d' WHERE `name`='%e'",PlayerInfo[ playerid ][ pClan ], PlayerInfo[ playerid ][ pNormalName ]);
					mysql_tquery(SQL, var,"","");
				}
				case pClanRanku:
				{
				    mysql_format(SQL, var, sizeof(var), "UPDATE `users` SET `ClanRank`= '%d' WHERE `name`='%e'",PlayerInfo[ playerid ][ pClanRank ], PlayerInfo[ playerid ][ pNormalName ]);
					mysql_tquery(SQL, var,"","");
				}
                case pConnectTimex:
                {
                    mysql_format(SQL, var, sizeof(var), "UPDATE `users` SET `ConnectTime`='%f' WHERE `name`='%s'",PlayerInfo[playerid][pConnectTime], PlayerInfo[playerid][pNormalName]);
                    mysql_tquery(SQL,var,"","");
                }
			}
		}
	}
	return 1;
}
YCMD:quitclan(playerid, params[], help)
{
	if( PlayerInfo[ playerid ][ pClan ] )
	{
	    format( gString, sizeof( gString ), "!%s(%d) a parasit clanul.", GetName( playerid ), playerid );
		ClanBroadCast( PlayerInfo[ playerid ][ pClan ], 0x2ACC9CFF, gString );
	    PlayerInfo[ playerid ][ pClan ] = 0;
	    PlayerInfo[ playerid ][ pClanRank ] = 0;
		Update( playerid, pClanu );
		Update( playerid, pClanRanku );
		SetPlayerName( playerid, PlayerInfo[ playerid ][ pNormalName ] );
	}
	else return SendClientMessage( playerid,COLOR_LIGHTRED, "Nu faci parte dintr-un clan" );
	return 1;
}

YCMD:cpanel(playerid, params[], help)
{
	if(!PlayerInfo[playerid][pClan]) return SendClientMessage( playerid, -1, "Nu esti intr-un clan." );
    Dialog_Show(playerid, DIALOG_CPANEL, DIALOG_STYLE_LIST, "{909CE7}LocalHost:{FFFFFF} Clan Panel", "{909CE7}1.{a9c4e4} Membrii\n{909CE7}2.{a9c4e4} Rankuri\n{909CE7}3.{a9c4e4} Activeaza / Dezactiveaza tag\n{909CE7}4.{a9c4e4} Schimba numele clanului\n{909CE7}5.{a9c4e4} Schimba tag-ul\n","Select","Exit");
	return 1;
}

YCMD:c(playerid, params[], help)
{
	if( !PlayerInfo[playerid][pClan] ) return SendClientMessage( playerid,COLOR_LIGHTRED, "Nu faci parte dintr-un clan" );
	new msj[ 64 ], string[128];
	if( sscanf( params, "s[64]", msj ) ) return SendClientMessage( playerid, COLOR_LIGHTBLUE, "{B8DBFF}Synthax:/c <Message>" );
	if(PlayerInfo[playerid][pMuted] != 0)
	{
	    SendClientMessage(playerid, COLOR_LIGHTRED, "* Inca esti redus la tacere, nu poti vorbi.");
	    return 1;
	}
	switch(PlayerInfo[playerid][pClanRank])
	{
		case 1:	format(string, sizeof(string), "** (( %s %s: %s )) **", CRank[ PlayerInfo[ playerid ][ pClan ]][1], GetName(playerid), params);
		case 2:	format(string, sizeof(string), "** (( %s %s: %s )) **", CRank[ PlayerInfo[ playerid ][ pClan ]][2], GetName(playerid), params);
		case 3:	format(string, sizeof(string), "** (( %s %s: %s )) **.", CRank[ PlayerInfo[ playerid ][ pClan ]][3], GetName(playerid), params);
		case 4:	format(string, sizeof(string), "** (( %s %s: %s )) **", CRank[ PlayerInfo[ playerid ][ pClan ]][4], GetName(playerid), params);
		case 5:	format(string, sizeof(string), "** (( %s %s: %s )) **", CRank[ PlayerInfo[ playerid ][ pClan ]][5], GetName(playerid), params);
		case 6:	format(string, sizeof(string), "** (( %s %s: %s )) **", CRank[ PlayerInfo[ playerid ][ pClan ]][6], GetName(playerid), params);
		case 7:	format(string, sizeof(string), "** (( %s %s: %s )) **", CRank[ PlayerInfo[ playerid ][ pClan ]][7], GetName(playerid), params);
		default: format(string, sizeof(string), "** (( %s %s: %s )) **", CRank[ PlayerInfo[ playerid ][ pClan ]][1], GetName(playerid), params);
	}
	ClanBroadCast( PlayerInfo[ playerid ][ pClan ], 0x2ACC9CFF, string );
	return 1;
}


YCMD:cinvite(playerid, params[], help)
{
    if(!PlayerInfo[playerid][pClan]) return SendClientMessage( playerid, -1, "LocalHost: Nu esti intr-un clan." );
    if(PlayerInfo[playerid][pClanRank] < 6 ) return SendClientMessage( playerid, -1, "Nu detii Rank 6+." );
    new id;
    if( sscanf( params, "u", id ) ) return SendClientMessage( playerid, -1, "LocalHost: /cinvite <username/playerid>" );
    if(PlayerInfo[id][pClan]) return SendClientMessage( playerid, -1, "{909CE7}LocalHost{FFFFFF}:Acel player face parte dintr-un clan." );
    SetPVarInt( id, "IdClanBoSSKsenon", PlayerInfo[ playerid ][ pClan ] );
    SetPVarInt( id, "IdProstINVCLan", playerid );
	gString[ 0 ] = ( EOS );
	format( gString, sizeof( gString ), "{909CE7}LocalHost{FFFFFF}: L-ai invitat pe %s in clanul tau!", GetName( id ) );
	SCM( playerid, -1, gString );
	format( gString, sizeof( gString ), "{909CE7}Playerul %s te-a invitat in clanul sau.\n{909CE7}Alege actiunea dorita:", GetName( playerid ) );
	Dialog_Show( id , DIALOG_CINVITE, DIALOG_STYLE_MSGBOX, "{909CE7}LocalHost{FFFFFF}Clan", gString,"Accepta","Refuza" );
	return 1;
}
Dialog:DIALOG_CPANEL9(playerid, response, listitem, inputtext[])
{
    if( !response ) return 1;
	cTagPos[ playerid ] = listitem;
	new var[ 256 ];
	mysql_format( SQL, var, sizeof(var), "UPDATE `users` SET `TagPos`='%d' WHERE `name`='%s'", cTagPos[ playerid ] , PlayerInfo[ playerid ][ pNormalName ] );
	mysql_tquery( SQL,var,"","" );
	AddTagToName( playerid );
	SCM( playerid, COLOR_LIGHTRED, "Ti-ai schimbat numele" );
    return 1;
}

Dialog:DIALOG_CPANEL2(playerid, response, listitem, inputtext[])
{
    if(response)
	{
		if(listitem >= 1)
		{
			new item = listitem;
			format( NumeSelectat[ playerid ], 24, Selected[ item ][ Numele ]  );
			Dialog_Show(playerid, DIALOG_CPANEL3 , DIALOG_STYLE_LIST, "{909CE7}LocalHost: {FFFFFF}CPanel", "Da afara din clan\nSchimba Rank", "Go", "Cancel");
		}
		else
		{
			return SendClientMessage(playerid, -1, "You can't click on this item.");
		}
	}
		else return 1;
    return 1;
}
Dialog:DIALOG_CPANEL3(playerid, response, listitem, inputtext[])
{
    if( !response ) SendClientMessage(playerid, -1, "Actions dialog canceled.");
	switch( listitem )
	{
	    case 0: //uninvite
	    {
			new string[ 512 ];
        	mysql_format(SQL, string, sizeof( string ), "SELECT * FROM `users` WHERE `name` = '%e';", NumeSelectat[ playerid ] );
			new idpl = GetIDClan( NumeSelectat[ playerid ] );
			if( idpl != INVALID_PLAYER_ID )
            {
                PlayerInfo[ idpl ][ pClan ] = 0;
                Update( idpl, pClanu );
				PlayerInfo[ idpl ][ pClanRank ] = 0;
				Update( idpl, pClanRanku );
				SendClientMessage( idpl, COLOR_LIGHTBLUE, "Info: Ai fost dat afara din clan de catre liderul tau!" );
				return 1;
			}
            else
            {
				mysql_format(SQL, string, sizeof( string ), "UPDATE `users` SET `Clan` = '0', `ClanRank` = '0' WHERE `name` = '%e'", NumeSelectat[ playerid ] );
				mysql_query( SQL, string);
            }
            SendClientMessage( playerid, -1, "(!) Jucatorul a fost dat din clan.");
	    }
	    case 1:
	    {
            Dialog_Show(playerid, DIALOG_CPANEL4 , DIALOG_STYLE_INPUT, "{909CE7}LocalHost: {FFFFFF}Rank", "Introdu rankul dorit [ 1-6 ]", "Ok", "Exit");
			return 1;
		}
	}
    return 1;
}

Dialog:DIALOG_CPANEL4(playerid, response, listitem, inputtext[])
{
    if( !response ) return 1;
    if( strlen( inputtext ) > 1 ) return 1;
	new rank = strval( inputtext );
//		new string[256];
	if( rank > 6 || rank < 1 ) return 1;
	new idpl = GetIDClan( NumeSelectat[ playerid ] );
	if( idpl != INVALID_PLAYER_ID )
    {
        new clanid = PlayerInfo[playerid][pClan];
        PlayerInfo[ idpl ][ pClanRank ] = rank;
		Update( idpl, pClanRanku );
		format(gString, sizeof(gString), "* (C): Ai fost avansat la rank %d de catre %s.",rank,GetName(playerid));
		SCM( idpl, -1, gString );
		format(gString, sizeof(gString), "Clan News: %s a fost avansat la rank %d.",GetName(idpl),rank);
		ClanBroadCast(clanid, COLOR_LIGHTRED, gString);
    }
    else
    {
    	new clanstring[256];
        new clanid = PlayerInfo[playerid][pClan];
        mysql_format(SQL, clanstring, sizeof( clanstring ), "UPDATE `users` SET `ClanRank` = '%d'  WHERE `name` = '%e'", rank, NumeSelectat[ playerid ] );
		mysql_query( SQL, clanstring);
		format(gString, sizeof(gString), "Clan News: %s a fost avansat offline la rank %d.",NumeSelectat[ playerid ], rank );
		ClanBroadCast(clanid, COLOR_LIGHTRED, gString);
    }
	SendClientMessage( playerid, -1, "Clan Info: Rank acordat.");
    return 1;
}
Dialog:DIALOG_CPANEL5(playerid, response, listitem, inputtext[])
{
    if( !response ) return 1;
 	rankidsel[ playerid ] = listitem + 1;
 	Dialog_Show(playerid, DIALOG_CPANEL6 , DIALOG_STYLE_INPUT, "{909CE7}LocalHost: {FFFFFF}Rank Name", "Introdu numele dorit:", "Seteaza", "Exit");
    return 1;
}

Dialog:DIALOG_CPANEL6(playerid, response, listitem, inputtext[])
{
    if( !response ) return 1;
    new rankname[ 32 ];
	new string[256];
	mysql_escape_string( inputtext , rankname );
	format( CRank[ PlayerInfo[ playerid ][ pClan ]][ rankidsel[ playerid ]], 64, rankname );
	format( string, sizeof( string ), "{909CE7}Info: {FFFFFF}Ai setat numele rankului %d in %s", rankidsel[ playerid ], rankname );
	SendClientMessage( playerid, -1, string );
	gString[ 0 ] = ( EOS );

	new fid = PlayerInfo[ playerid ][ pClan ];
	mysql_format( SQL, string, sizeof( string ), "UPDATE `clans` SET `R1` = '%e', `R2` = '%e', `R3`= '%e', `R4` = '%e', `R5` = '%e', `R6` = '%e', `R7` = '%e' WHERE `ID` = %d",
	CRank[ fid ][ 1 ],CRank[ fid ][ 2 ],CRank[ fid ][ 3 ],CRank[ fid ][ 4 ],CRank[ fid ][ 5 ],CRank[ fid ][ 6 ],CRank[ fid ][ 7 ], fid );
	mysql_tquery( SQL, string , "", "" );
	return 1;
}
Dialog:DIALOG_CPANEL7(playerid, response, listitem, inputtext[])
{
    if( !response ) return SCM( playerid, -1, "Nu mai doresti sa schimbi numele clanului." );
    if( PlayerInfo[playerid][pPremiumPoints] < 15 ) return SCM(playerid,COLOR_WHITE,"{909CE7}Info: You don't have 15 crystals.");
	if(PlayerInfo[playerid][pClanRank] < 7) return SCM(playerid,COLOR_WHITE,"{909CE7}Info: {FFFFFF}Nu detii rank 7.");
    new fannname[ 128 ];
	mysql_escape_string( inputtext , fannname );
	format(ClanInfo[PlayerInfo[playerid][pClan]][cName], 128, fannname);
	new string2[256], string10[100];
	format(string10,sizeof(string10),"** Clan News: Noul nume al clanului este: %s",ClanInfo[PlayerInfo[playerid][pClan]][cName]);
	ClanBroadCast(PlayerInfo[playerid][pClan],COLOR_LIGHTRED, string10);
	mysql_format( SQL, string2, sizeof( string2 ), "UPDATE `clans` SET `Name` = '%e' WHERE `ID` = %d", fannname, PlayerInfo[playerid][pClan] );
	mysql_tquery( SQL, string2 , "", "" );

	return 1;
}
Dialog:DIALOG_CPANEL8(playerid, response, listitem, inputtext[])
{
    if( !response ) return SCM( playerid, -1, "Nu mai doresti sa schimbi tagul clanului." );
    if( PlayerInfo[playerid][pPremiumPoints] < 15 ) return SCM(playerid,COLOR_WHITE,"{909CE7}Info: You don't have 15 crystals.");
	if(PlayerInfo[playerid][pClanRank] < 7) return SCM(playerid,COLOR_WHITE,"{909CE7}Info: {FFFFFF}Nu detii rank 7.");
    new fannname[ 128 ];
	mysql_escape_string( inputtext , fannname );
	format(ClanInfo[PlayerInfo[playerid][pClan]][cTag], 32, fannname);
	new string2[256], string10[100];
	format(string10,sizeof(string10),"** Clan News: Noul TAG al clanului este: %s",ClanInfo[PlayerInfo[playerid][pClan]][cTag]);
	ClanBroadCast(PlayerInfo[playerid][pClan],COLOR_LIGHTRED, string10);
	mysql_format( SQL, string2, sizeof( string2 ), "UPDATE `clans` SET `Tag` = '%e' WHERE `ID` = %d", fannname, PlayerInfo[playerid][pClan] );
	mysql_tquery( SQL, string2 , "", "" );

	return 1;
}
Dialog:DIALOG_CPANEL(playerid, response, listitem, inputtext[])
{
    if( !response ) return SendClientMessage( playerid, -1, "{909CE7}Info: {FFFFFF}Ai anulat");
	switch( listitem )
	{
	    case 0:
	    {
	        if( PlayerInfo[ playerid ][ pClanRank ] < 6 ) return SendClientMessage( playerid, -1, "Nu esti Lider/Co lider");
			new stringg[256], pName2[MAX_PLAYER_NAME], pRankul[ MAX_PLAYERS ], pLastLog[ 128 ];
			mysql_format(SQL, stringg, sizeof(stringg), "SELECT * FROM `users` WHERE `Clan` = '%d' ORDER BY `ClanRank` DESC", PlayerInfo[ playerid ][ pClan ]);
			new Cache: result12 = mysql_query( SQL, stringg );
			gString[ 0 ] = ( EOS );

			for ( new i, j = cache_get_row_count ( ); i != j; ++i )
			{
				cache_get_field_content(i, "name", pName2 );
				format(Selected[ i ][ Numele ],24, pName2 );
				pRankul[i] = cache_get_field_content_int( i, "ClanRank" );
				cache_get_field_content(i, "lastOn", pLastLog );

				new id = GetIDClan( Selected[ i ][ Numele ] );
				if(id != INVALID_PLAYER_ID)
				{
				    format(gString , sizeof(gString), "%s%s - Rank: %d  - online - \n",gString, pName2, pRankul[i] );
				}
				else
				{
	                format(gString , sizeof(gString), "%s%s - Rank: %d  - offline - Ultimul Login %s \n",gString, pName2, pRankul[i], pLastLog );
				}
			}
			cache_delete(result12);
			Dialog_Show(playerid,DIALOG_CPANEL2 ,DIALOG_STYLE_LIST,"{909CE7}LocalHost: {FFFFFF}Members",gString,"Select","Cancel");
	    }
	    case 1:
	    {
	        if( PlayerInfo[ playerid ][ pClanRank ] != 7 ) return SendClientMessage( playerid, -1, "Nu esti lider");
	        new fid = PlayerInfo[ playerid ][ pClan ];
			format( gString, sizeof( gString ), "Rank 1 - %s\nRank 2 - %s\nRank 3 - %s\nRank 4 - %s\nRank 5 - %s\nRank 6 - %s\nRank 7 - %s", CRank[ fid ][ 1 ],CRank[ fid ][ 2 ],CRank[ fid ][ 3 ],CRank[ fid ][ 4 ],CRank[ fid ][ 5 ],CRank[ fid ][ 6 ],CRank[ fid ][ 7 ] );
			Dialog_Show(playerid, DIALOG_CPANEL5 ,DIALOG_STYLE_LIST ,"{909CE7}LocalHost: {FFFFFF}Clan Panel", gString ,"Select","Exit");
	    }
	    case 2:
	    {
			new stringg[ 512 ];
			format( stringg, sizeof( stringg ), "Fara Tag[ %s ]\nIn fata numelui [%s%s]\nDupa nume [%s%s]", PlayerInfo[ playerid ][ pNormalName ], ClanInfo[PlayerInfo[playerid][pClan]][cTag],PlayerInfo[playerid][pNormalName],PlayerInfo[playerid][pNormalName], ClanInfo[PlayerInfo[playerid][pClan]][cTag] );
            Dialog_Show(playerid, DIALOG_CPANEL9,DIALOG_STYLE_LIST ,"{909CE7}LocalHost: {FFFFFF}Clan Panel", stringg ,"OK","Exit");
		}
		case 3:
	    {
	        if( PlayerInfo[ playerid ][ pClanRank ] != 7 ) return SendClientMessage( playerid, -1, "Nu esti Lider");
			Dialog_Show(playerid, DIALOG_CPANEL7,DIALOG_STYLE_INPUT ,"{909CE7}LocalHost: {FFFFFF}Clan Panel", "Schimbarea va costa 15 PP.\n\nIntrodu numele clanului:" ,"OK","Exit");
	    }
	    case 4:
	    {
	        if( PlayerInfo[ playerid ][ pClanRank ] != 7 ) return SendClientMessage( playerid, -1, "Nu esti Lider");
			Dialog_Show(playerid, DIALOG_CPANEL8,DIALOG_STYLE_INPUT ,"{909CE7}LocalHost: {FFFFFF}Clan Panel", "Schimbarea va costa 15 PP.\n\nIntrodu TAG-ul clanului:" ,"OK","Exit");
	    }
	}
    return 1;
}
Dialog:DIALOG_CINVITE(playerid, response, listitem, inputtext[])
{
    if( !response )
	{
		SCM( playerid, COLOR_WHITE, "{909CE7}LocalHost: {FFFFFF}Ai anulat cererea.");
		new idtigan = GetPVarInt(playerid, "IdProstINVCLan" );
		SCM( idtigan, -1, "{909CE7}LocalHost: {FFFFFF}Nu a acceptat cererea de intrare in clan!{FFFFFF}!");
		DeletePVar(playerid, "IdProstINVCLan");
		DeletePVar(playerid, "IdClanBoSSKsenon");
		return 1;
	}
	else
	{
	    SCM( playerid, COLOR_WHITE, "{909CE7}LocalHost: {FFFFFF}Ai anulat cererea.");
		new idclan = GetPVarInt(playerid, "IdClanBoSSKsenon" );
		PlayerInfo[ playerid ][ pClan ] = idclan;
		Update( playerid, pClanu );
		PlayerInfo[ playerid ][ pClanRank ] = 1;
		Update( playerid, pClanRanku );
		gString[ 0 ] = ( EOS );
		format( gString, sizeof( gString ), "Playerul {FFFFFF}%s {2ACC9C}a intrat in clanul nostru!", PlayerInfo[ playerid ][ pNormalName ] );
		ClanBroadCast( PlayerInfo[ playerid ][ pClan ], 0x2ACC9CFF, gString );
		DeletePVar(playerid, "IdProstINVCLan");
		DeletePVar(playerid, "IdClanBoSSKsenon");
		cTagPos[ playerid ] = 0;
	}
    return 1;
}
Dialog:DIALOG_SHOP_CLAN(playerid, response, listitem, inputtext[])
{
    if(!response) return SCM( playerid, -1, "{909CE7}LocalHost: {FFFFFF}Ai renuntat sa creezi un clan!");
	if( PlayerInfo[ playerid ][ pPremiumPoints ] < 300 ) return SCM( playerid, -1, "{909CE7}LocalHost: {FFFFFF}Nu ai 300 crystals!");
	if( strlen( inputtext ) < 5 || strlen( inputtext ) > 15 ) return SCM( playerid, -1, "{909CE7}LocalHost: {FFFFFF}Numele clanului trebuie sa contina intre 5 si 15 caractere!");
	SetPVarString(playerid,"NumeClan", inputtext );
	Dialog_Show(playerid, DIALOG_SHOP_CLAN2, DIALOG_STYLE_INPUT, "{909CE7}LocalHost: {FFFFFF}Clan", "{FFFFFF}Introduceti tag'ul clanului:", "Introdu", "Anuleaza");
    return 1;
}

Dialog:DIALOG_SHOP_CLAN2(playerid, response, listitem, inputtext[])
{
	if(!response) return SCM( playerid, -1, "{909CE7}LocalHost: {FFFFFF}Ai renuntat sa creezi un clan!");
	if( PlayerInfo[ playerid ][ pPremiumPoints ] < 300 ) return SCM( playerid, -1, "{909CE7}LocalHost: {FFFFFF}Pentru a crea un clan ai nevoie de minimum 300 de crystals!");
	if( strlen( inputtext ) < 3 || strlen( inputtext ) > 5 ) return SCM( playerid, -1, "{909CE7}LocalHost: {FFFFFF}Tagul clanului trebuie sa contina intre 3 si 5 caractere!");
	gString[ 0 ] = ( EOS );
	mysql_format( SQL,gString, sizeof( gString ), "SELECT ID FROM `clans` WHERE `Tag` = '%e'", inputtext );
	new Cache:query = mysql_query( SQL, gString );
	if( cache_num_rows( ) ) return Dialog_Show(playerid, DIALOG_SHOP_CLAN2, DIALOG_STYLE_INPUT, "{909CE7}LocalHost: {FFFFFF}Clan", "{FF0000}Tag folosit deja de alt clan!\n{FFFFFF}Introduceti tag'ul clanului:", "Introdu", "Anuleaza");
	cache_delete( query );
	new numeclan[ 15 ];
	GetPVarString(playerid, "NumeClan", numeclan, sizeof(numeclan));
	mysql_format( SQL, gString, sizeof( gString ), "INSERT INTO `clans` ( `Name`, `Tag` ) VALUES ( '%e', '%e' )", numeclan, inputtext );
	new Cache:queryvaloros = mysql_query( SQL, gString );
	new id = cache_insert_id( );
	cache_delete( queryvaloros );
	PlayerInfo[ playerid ][ pClan ] = id;
	PlayerInfo[ playerid ][ pClanRank ] = 7;
	pUpdateInt(playerid, "Clan", PlayerInfo[playerid][pClan]);
	Update( playerid, pClanu );
	Update( playerid, pClanRanku );
	//pp
	PlayerInfo[ playerid ][ pPremiumPoints ] -= 300;
	pUpdateInt(playerid, "PremiumPoints", PlayerInfo[playerid][pPremiumPoints]);
	format( gString, sizeof( gString ), "{909CE7}LocalHost: {FFFFFF}Ai creat cu succes clanul %s cu TAG-ul %s", numeclan, inputtext );
	SCM( playerid, -1, gString );
	mysql_tquery(SQL, "SELECT * FROM `clans`", "LoadClans", "" );
    return 1;
}

stock AddTagToName( playerid )
{
	new newName[ MAX_PLAYER_NAME ], ccID = PlayerInfo[ playerid ][ pClan ];
	switch( cTagPos[ playerid ] )
	{
	    case 0: format( newName, MAX_PLAYER_NAME, "%s", PlayerInfo[ playerid ][ pNormalName ] );
	    case 1: format( newName, MAX_PLAYER_NAME, "%s%s", ClanInfo[ ccID ][ cTag ], PlayerInfo[ playerid ][ pNormalName ] );
	    case 2: format( newName, MAX_PLAYER_NAME, "%s%s",  PlayerInfo[ playerid ][ pNormalName ], ClanInfo[ ccID ][ cTag ] );
	}
	SetPlayerName( playerid, newName );
	return 1;
}
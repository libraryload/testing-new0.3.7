#include <YSI_Coding\y_hooks>
#include <gmenu>

YCMD:gmenu(playerid, params[], help) {

    ShowPlayerMenu(playerid, opulamare, "Test");
    AddPlayerMenuItem(playerid, "Test", "this is just a test item.");
    SendClientMessage(playerid, -1, "Use 'Y' to select and 'N' to exit.");

    return true;
}

Menu:opulamare(playerid, response, listitem)
{
    if (response == MENU_RESPONSE_SELECT)
    {
        switch (listitem)
        {
            case 0:
            {
                SendClientMessage(playerid, -1, "The test item is here!");
            }
        }
    }
    return 1;
} 
#include "ScriptPCH.h"

uint32 allowed[] = { 0 };
uint32 unallowed[] = { 12947, 18970, 2586, 11508, 12064 };
uint32 id;

bool CanRequest(Player* player, Creature* creature, uint32 item)
{
    ItemTemplate const* proto = sObjectMgr->GetItemTemplate(item);

    if (!proto)
    {
        creature->Whisper("Item id doesn't exist.", LANG_UNIVERSAL, player);
        return false;
    }

    for (int i = 0; i < sizeof(allowed); i++)
    {
        if (item == allowed[i])
            return true;
    }

    for (int i = 0; i < sizeof(unallowed); i++)
    {
        if (item == unallowed[i])
            return false;
    }

    if (proto->Flags2 & ITEM_FLAGS_EXTRA_HORDE_ONLY && player->GetTeam() == ALLIANCE)
    {
        creature->Whisper("This item is only avaible for the horde.", LANG_UNIVERSAL, player);
        return false;
    }

    if (proto->Flags2 & ITEM_FLAGS_EXTRA_ALLIANCE_ONLY && player->GetTeam() == HORDE)
    {
        creature->Whisper("This item is only avaible for the alliance.", LANG_UNIVERSAL, player);
        return false;
    }

    if (proto->ItemLevel > 245)
    {
        creature->Whisper("The item level is too high.", LANG_UNIVERSAL, player);
        return false;
    }

    switch (proto->InventoryType)
    {
    case INVTYPE_HEAD:
    case INVTYPE_SHOULDERS:
    case INVTYPE_BODY:
    case INVTYPE_CHEST:
    case INVTYPE_WAIST:
    case INVTYPE_LEGS:
    case INVTYPE_FEET:
    case INVTYPE_WRISTS:
    case INVTYPE_HANDS:
    case INVTYPE_WEAPON:
    case INVTYPE_SHIELD:
    case INVTYPE_RANGED:
    case INVTYPE_CLOAK:
    case INVTYPE_2HWEAPON:
    case INVTYPE_ROBE:
    case INVTYPE_WEAPONMAINHAND:
    case INVTYPE_WEAPONOFFHAND:
    case INVTYPE_HOLDABLE:
    case INVTYPE_THROWN:
    case INVTYPE_RANGEDRIGHT:
        break;
    default:
        creature->Whisper("Item has invalid inventory type.", LANG_UNIVERSAL, player);
        return false;
        break;
    }

    if (proto->Class != ITEM_CLASS_WEAPON && proto->Class != ITEM_CLASS_ARMOR)
        return false;

    return true;
};

class npc_item_requester : public CreatureScript
{
public:
    npc_item_requester() : CreatureScript("npc_item_requester") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_INTERACT_1, "Type an item id here.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1, "", 0, true);
        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_INTERACT_1, "Search by item name. (Don't use, crashes server.)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2, "", 0, true);
        player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        if (!CanRequest(player, creature, action))
            OnGossipHello(player, creature);
        else
        {
            player->AddItem(action, 1);
            OnGossipHello(player, creature);
        }

        return true;
    }

    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, char const* code)
    {
        player->PlayerTalkClass->ClearMenus();

        if (sender == GOSSIP_SENDER_MAIN)
        {
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                if (strlen(code) > 5)
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("Invalid ItemId");
                    player->PlayerTalkClass->SendCloseGossip();
                    return false;
                }

                id = atoi(code);

                if (!CanRequest(player, creature, id))
                    OnGossipHello(player, creature);
                else
                {
                    player->AddItem(id, 1);
                    OnGossipHello(player, creature);
                }
                break;

            case GOSSIP_ACTION_INFO_DEF + 2:
                std::string name = code;
                static const char* allowedcharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz _.,'1234567890";
                if (!name.length() || name.find_first_not_of(allowedcharacters) != std::string::npos)
                {
                    creature->Whisper("Invalid text entered.", LANG_UNIVERSAL, player);
                    OnGossipHello(player, creature);
                    break;
                }

                QueryResult result = WorldDatabase.PQuery("SELECT * FROM `item_template` WHERE name LIKE CONCAT('%', '%s', '%') LIMIT 20", name.c_str());
                if (!result)
                {
                    creature->Whisper("No results found.", LANG_UNIVERSAL, player);
                    OnGossipHello(player, creature);
                    break;
                }

                Field* field = result->Fetch();

                if (result)
                {
                    do
                    {
                        id = field[0].GetUInt32();
                        std::string _name = field[4].GetString();
                        if (CanRequest(player, creature, id))
                            player->ADD_GOSSIP_ITEM(5, _name.c_str(), GOSSIP_SENDER_MAIN, id);
                    } while (result->NextRow());
                    player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
                }
                break;
            }
        }
        return true;
    }
};

void AddSC_npc_item_requester()
{
    new npc_item_requester();
}

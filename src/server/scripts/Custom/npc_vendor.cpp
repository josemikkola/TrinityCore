class npc_vendor : public CreatureScript
{
public:
    npc_vendor() : CreatureScript("npc_vendor") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        switch (creature->GetEntry())
        {
        case 100060: // Gems.
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_Jewelcrafting_ShadowSpirit_02:20|t Meta & Prismatic", GOSSIP_SENDER_MAIN, 100010);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_JEWELCRAFTING_GEM_37:20|t Red", GOSSIP_SENDER_MAIN, 100011);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_JEWELCRAFTING_GEM_42:20|t Blue", GOSSIP_SENDER_MAIN, 100012);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_JEWELCRAFTING_GEM_38:20|t Yellow", GOSSIP_SENDER_MAIN, 100013);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_JEWELCRAFTING_GEM_40:20|t Purple", GOSSIP_SENDER_MAIN, 100014);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_JEWELCRAFTING_GEM_39:20|t Orange", GOSSIP_SENDER_MAIN, 100015);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_JEWELCRAFTING_GEM_41:20|t Green", GOSSIP_SENDER_MAIN, 100016);
            player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
            break;
        case 100061: // starter pve.
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_Shoulder_73:20|t Mainset", GOSSIP_SENDER_MAIN, 100040);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_Belt_49C:20|t Offset", GOSSIP_SENDER_MAIN, 100041);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_Jewelry_Ring_61:20|t Jewelry", GOSSIP_SENDER_MAIN, 100042);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_Axe_104:20|t Weapons", GOSSIP_SENDER_MAIN, 100043);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_Shoulder_35:20|t T9.5", GOSSIP_SENDER_MAIN, 100044);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_Relics_LibramofHope:20|t Librams, Relics & Sigils", GOSSIP_SENDER_MAIN, 100045);
            player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
            break;
        case 100062: // 264-277 pve.
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_Shoulder_130:20|t Mainset", GOSSIP_SENDER_MAIN, 100050);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_Belt_63:20|t Offset", GOSSIP_SENDER_MAIN, 100051);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/Item_icecrownringa:20|t Jewelry", GOSSIP_SENDER_MAIN, 100052);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_Axe_113:20|t Weapons", GOSSIP_SENDER_MAIN, 100053);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_Shoulder_116Black:20|t T10.5", GOSSIP_SENDER_MAIN, 100054);
            player->ADD_GOSSIP_ITEM(5, "|TInterface/ICONS/INV_Scroll_15:20|t Librams, Relics & Sigils", GOSSIP_SENDER_MAIN, 100055);
            player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
            break;
        case 100065:
            player->ADD_GOSSIP_ITEM(5, "Classic.", GOSSIP_SENDER_MAIN, 110000);
            player->ADD_GOSSIP_ITEM(5, "The Burning Crusade.", GOSSIP_SENDER_MAIN, 110001);
            player->ADD_GOSSIP_ITEM(5, "Wrath of the Lich King", GOSSIP_SENDER_MAIN, 110002);
            player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
            break;

        default:
            creature->Whisper("multivendor missing options for this entry id", LANG_UNIVERSAL, player);
            break;
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
		player->GetSession()->SendListInventory(creature->GetGUID(), action);
		return true;
    }
};

void AddSC_npc_vendor()
{
    new npc_vendor();
}
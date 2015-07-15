#include "Teleporter_NPC.h"

class Teleporter_NPC : public CreatureScript
{
public:
    Teleporter_NPC() : CreatureScript("Teleporter_NPC") { }
    
    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(4, "Mall.", GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(4, "Duel Zone.", GOSSIP_SENDER_MAIN, 2);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Queue Area(s) - Alone.", GOSSIP_SENDER_MAIN, 10);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Queue Area(s) - As Group.", GOSSIP_SENDER_MAIN, 11);
        player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        
        if (player->IsInCombat())
        {
            creature->Whisper("You are in Combat!", LANG_UNIVERSAL, player);
            player->PlayerTalkClass->SendCloseGossip();
            return true;
        }

        if (sender == GOSSIP_SENDER_MAIN)
        {
            switch (action)
            {
            case 1:
                player->SaveRecallPosition();
                player->TeleportTo(530, -2963.494629f, 3999.315186f, 1.381815f, 1.078750f);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 2:
                player->SaveRecallPosition();
                player->TeleportTo(571, 4788.649902f, -3841.679932f, 333.998993f, 0.048377f);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 10:
            case 11:
                switch (urand(1, 3))
                {
                case 1:
                case 2:
                case 3:
                    if (action == 11)
                        SendSummonRequestToParty(player, 1, 3518, -1739.005493f, 8485.892578f, 199.261383f, 2.288175f);
                    player->TeleportTo(1, -1739.005493f, 8485.892578f, 199.261383f, 2.288175f);
                    break;
                }
            }
        }
        return true;
    }
};

void AddSC_Teleporter_NPC()
{
    new Teleporter_NPC();
}

#include "Language.h"
class npc_professions_trainer : public CreatureScript
{
public:
    npc_professions_trainer() : CreatureScript("npc_professions_trainer") { }
    
    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Trade_Alchemy:20|t Alchemy.", GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Trade_BlackSmithing:20|t Blacksmithing.", GOSSIP_SENDER_MAIN, 2);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/INV_Misc_ArmorKit_17:20|t Leatherworking.", GOSSIP_SENDER_MAIN, 3);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Trade_Tailoring:20|t Tailoring.", GOSSIP_SENDER_MAIN, 4);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Trade_Engineering:20|t Engineering.", GOSSIP_SENDER_MAIN, 5);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Trade_Engraving:20|t Enchanting.", GOSSIP_SENDER_MAIN, 6);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/INV_Misc_Gem_02:20|t Jewelcrafting.", GOSSIP_SENDER_MAIN, 7);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/INV_Inscription_Tradeskill01:20|t Inscription.", GOSSIP_SENDER_MAIN, 8);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Trade_Herbalism:20|t Herbalism.", GOSSIP_SENDER_MAIN, 9);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/INV_Misc_Pelt_Wolf_01:20|t Skinning.", GOSSIP_SENDER_MAIN, 10);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Trade_Mining:20|t Mining.", GOSSIP_SENDER_MAIN, 11);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Trade_Fishing:20|t Fishing.", GOSSIP_SENDER_MAIN, 12);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/Spell_Holy_SealOfSacrifice:20|t First Aid.", GOSSIP_SENDER_MAIN, 13);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface/ICONS/INV_Misc_Food_15:20|t Cooking.", GOSSIP_SENDER_MAIN, 14);
        player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
        return true;
    }

    bool Maximum(Player* player)
    {
        uint32 count = 0;
        if (player->HasSkill(SKILL_BLACKSMITHING))
            count++;
        if (player->HasSkill(SKILL_LEATHERWORKING))
            count++;
        if (player->HasSkill(SKILL_TAILORING))
            count++;
        if (player->HasSkill(SKILL_ENGINEERING))
            count++;
        if (player->HasSkill(SKILL_ENCHANTING))
            count++;
        if (player->HasSkill(SKILL_JEWELCRAFTING))
            count++;
        if (player->HasSkill(SKILL_INSCRIPTION))
            count++;
        if (player->HasSkill(SKILL_HERBALISM))
            count++;
        if (player->HasSkill(SKILL_MINING))
            count++;
        if (count >= 2)
            return true;
        else
            return false;
    }

    void LearnProfession(Player* player, Creature *creature, SkillType skill)
    {
        if (Maximum(player) && skill != SKILL_COOKING && skill != SKILL_FIRST_AID && skill != SKILL_FISHING)
            creature->Whisper("You can only have two professions simultaneously.", LANG_UNIVERSAL, player);
        else
        {
            char* name;
            SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill);
            name = SkillInfo->name[ChatHandler(player->GetSession()).GetSessionDbcLocale()];

            for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
            {
                SkillLineAbilityEntry const *line = sSkillLineAbilityStore.LookupEntry(j);
                if (!line)
                    continue;

                if (line->skillId != skill)
                    continue;

                if (line->forward_spellid)
                    continue;

                if (line->racemask != 0)
                    continue;

                if (line->classmask && (line->classmask & player->getClassMask()) == 0)
                    continue;

                SpellInfo const * info = sSpellMgr->GetSpellInfo(line->spellId);
                if (!info || !SpellMgr::IsSpellValid(info, player, false))
                    continue;

                player->LearnSpell(line->spellId, false);
            }
            player->SetSkill(SkillInfo->id, player->GetSkillStep(SkillInfo->id), 450, 450);
            ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_LEARN_ALL_RECIPES, name);
        }
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        
        if (sender == GOSSIP_SENDER_MAIN)
        {
            switch (action)
            {
            case 1:
                if (!player->HasSkill(SKILL_ALCHEMY))
                    LearnProfession(player, creature, SKILL_ALCHEMY);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 2:
                if (!player->HasSkill(SKILL_BLACKSMITHING))
                    LearnProfession(player, creature, SKILL_BLACKSMITHING);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 3:
                if (!player->HasSkill(SKILL_LEATHERWORKING))
                    LearnProfession(player, creature, SKILL_LEATHERWORKING);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 4:
                if (!player->HasSkill(SKILL_TAILORING))
                    LearnProfession(player, creature, SKILL_TAILORING);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 5:
                if (!player->HasSkill(SKILL_ENGINEERING))
                    LearnProfession(player, creature, SKILL_ENGINEERING);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 6:
                if (!player->HasSkill(SKILL_ENCHANTING))
                    LearnProfession(player, creature, SKILL_ENCHANTING);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 7:
                if (!player->HasSkill(SKILL_JEWELCRAFTING))
                    LearnProfession(player, creature, SKILL_JEWELCRAFTING);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 8:
                if (!player->HasSkill(SKILL_INSCRIPTION))
                    LearnProfession(player, creature, SKILL_INSCRIPTION);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 9:
                if (!player->HasSkill(SKILL_HERBALISM))
                    LearnProfession(player, creature, SKILL_HERBALISM);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 10:
                if (!player->HasSkill(SKILL_SKINNING))
                    LearnProfession(player, creature, SKILL_SKINNING);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 11:
                if (!player->HasSkill(SKILL_MINING))
                    LearnProfession(player, creature, SKILL_MINING);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 12:
                if (!player->HasSkill(SKILL_FISHING))
                    LearnProfession(player, creature, SKILL_FISHING);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 13:
                if (!player->HasSkill(SKILL_FIRST_AID))
                    LearnProfession(player, creature, SKILL_FIRST_AID);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            case 14:
                if (!player->HasSkill(SKILL_COOKING))
                    LearnProfession(player, creature, SKILL_COOKING);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            }
        }
        return true;
    }
};

void AddSC_npc_professions_trainer()
{
    new npc_professions_trainer();
}

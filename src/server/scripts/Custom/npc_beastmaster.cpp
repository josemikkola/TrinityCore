#include "Pet.h"

class npc_beastmaster : public CreatureScript
{
public:
    npc_beastmaster() : CreatureScript("npc_beastmaster") { }

    bool OnGossipHello(Player * player, Creature * creature)
    {
        if (player->getClass() != CLASS_HUNTER)
            return true;
        else
        {
            player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_BeastTaming:20|t Normal Pet.", GOSSIP_SENDER_MAIN, 1);
            player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_BeastMastery:20|t Exotic Pet.", GOSSIP_SENDER_MAIN, 2);
            player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/INV_Box_PetCarrier_01:20|t Stable.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_BeastTraining:20|t Pet Food.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
            return true;
        }
    }

    bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        if (sender == GOSSIP_SENDER_MAIN)
        {
            switch (action)
            {
            case 1:
                player->ADD_GOSSIP_ITEM(4, "[CUNNING]:", GOSSIP_SENDER_MAIN, 3);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Bat:20|t Bat.", GOSSIP_SENDER_MAIN, 100);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Owl:20|t Bird of Prey.", GOSSIP_SENDER_MAIN, 101);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_DragonHawk:20|t Dragonhawk.", GOSSIP_SENDER_MAIN, 102);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_NetherRay:20|t Nether Ray.", GOSSIP_SENDER_MAIN, 103);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Ravager:20|t Ravager.", GOSSIP_SENDER_MAIN, 104);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Spell_Nature_GuardianWard:20|t Serpent.", GOSSIP_SENDER_MAIN, 105);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Spider:20|t Spider.", GOSSIP_SENDER_MAIN, 106);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Sporebat:20|t Sporebat.", GOSSIP_SENDER_MAIN, 107);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_WindSerpent:20|t Wind Serpent.", GOSSIP_SENDER_MAIN, 108);
                player->ADD_GOSSIP_ITEM(4, "[FEROCITY]:", GOSSIP_SENDER_MAIN, 3);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Vulture:20|t Carrion Bird.", GOSSIP_SENDER_MAIN, 200);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Cat:20|t Cat.", GOSSIP_SENDER_MAIN, 201);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Hyena:20|t Hyena.", GOSSIP_SENDER_MAIN, 202);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Moth:20|t Moth.", GOSSIP_SENDER_MAIN, 203);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Raptor:20|t Raptor.", GOSSIP_SENDER_MAIN, 204);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_TallStrider:20|t Tallstrider.", GOSSIP_SENDER_MAIN, 205);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Wasp:20|t Wasp.", GOSSIP_SENDER_MAIN, 206);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Wolf:20|t Wolf.", GOSSIP_SENDER_MAIN, 207);
                player->ADD_GOSSIP_ITEM(4, "[TENACITY]:", GOSSIP_SENDER_MAIN, 3);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Bear:20|t Bear.", GOSSIP_SENDER_MAIN, 300);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Boar:20|t Boar.", GOSSIP_SENDER_MAIN, 301);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Crab:20|t Crab.", GOSSIP_SENDER_MAIN, 302);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Crocolisk:20|t Crocolisk.", GOSSIP_SENDER_MAIN, 303);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Gorilla:20|t Gorilla.", GOSSIP_SENDER_MAIN, 304);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Scorpid:20|t Scorpid.", GOSSIP_SENDER_MAIN, 305);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Turtle:20|t Turtle.", GOSSIP_SENDER_MAIN, 306);
                player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_WarpStalker:20|t Warp Stalker.", GOSSIP_SENDER_MAIN, 307);
                player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
                break;

            case 2:
                if (!player->ToPlayer()->CanTameExoticPets())
                {
                    creature->Whisper("Exotic pets require |cff4e96f7|Htalent:2139:4|h[Beast Mastery]|h|r from Beast Mastery talent tree.", LANG_UNIVERSAL, player);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                }
                else
                {
                    player->ADD_GOSSIP_ITEM(4, "[CUNNING]:", GOSSIP_SENDER_MAIN, 3);
                    player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Chimera:20|t Chimaera.", GOSSIP_SENDER_MAIN, 109);
                    player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Silithid:20|t Silithid.", GOSSIP_SENDER_MAIN, 110);
                    player->ADD_GOSSIP_ITEM(4, "[FEROCITY]:", GOSSIP_SENDER_MAIN, 3);
                    player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_CoreHound:20|t Core Hound.", GOSSIP_SENDER_MAIN, 208);
                    player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Druid_PrimalPrecision:20|t Spirit Beast.", GOSSIP_SENDER_MAIN, 209);
                    player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Devilsaur:20|t Devilsaur.", GOSSIP_SENDER_MAIN, 210);
                    player->ADD_GOSSIP_ITEM(4, "[TENACITY]:", GOSSIP_SENDER_MAIN, 3);
                    player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Rhino:20|t Rhino.", GOSSIP_SENDER_MAIN, 308);
                    player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Ability_Hunter_Pet_Worm:20|t Worm.", GOSSIP_SENDER_MAIN, 309);
                    player->PlayerTalkClass->SendGossipMenu(creature->GetEntry(), creature->GetGUID());
                    break;
                }

            case 3:
                player->PlayerTalkClass->SendCloseGossip();
                break;

            case GOSSIP_ACTION_INFO_DEF + 1:
                player->GetSession()->SendStablePet(creature->GetGUID());
                break;

            case GOSSIP_ACTION_INFO_DEF + 2:
                player->GetSession()->SendListInventory(creature->GetGUID());
                break;

            case 100: // Bat.
                TamePetFamily(player, creature, 24);
                break;
            case 101: // Bird of Prey.
                TamePetFamily(player, creature, 7);
                break;
            case 102: // Dragonhawk.
                TamePetFamily(player, creature, 30);
                break;
            case 103: // Nether Ray.
                TamePetFamily(player, creature, 34);
                break;
            case 104: // Ravager.
                TamePetFamily(player, creature, 31);
                break;
            case 105: // Serpent.
                TamePetFamily(player, creature, 35);
                break;
            case 106: // Spider.
                TamePetFamily(player, creature, 3);
                break;
            case 107: // Sporebat.
                TamePetFamily(player, creature, 33);
                break;
            case 108: // Wind Serpent.
                TamePetFamily(player, creature, 27);
                break;
            case 109: // Chimaera.
                TamePetFamily(player, creature, 38);
                break;
            case 110: // Silithid.
                TamePetFamily(player, creature, 41);
                break;

            case 200: // Carrion Bird.
                TamePetFamily(player, creature, 7);
                break;
            case 201: // Cat.
                TamePetFamily(player, creature, 2);
                break;
            case 202: // Hyena.
                TamePetFamily(player, creature, 25);
                break;
            case 203: // Moth.
                TamePetFamily(player, creature, 37);
                break;
            case 204: // Raptor.
                TamePetFamily(player, creature, 11);
                break;
            case 205: // Tallstrider.
                TamePetFamily(player, creature, 12);
                break;
            case 206: // Wasp.
                TamePetFamily(player, creature, 44);
                break;
            case 207: // Wolf.
                TamePetFamily(player, creature, 1);
                break;
            case 208: // Core Hound.
                TamePetFamily(player, creature, 45);
                break;
            case 209: // Spirit Beast.
                TamePetFamily(player, creature, 46);
                break;
            case 210: // Devilsaur.
                TamePetFamily(player, creature, 39);
                break;

            case 300: // Bear.
                TamePetFamily(player, creature, 4);
                break;
            case 301: // Boar.
                TamePetFamily(player, creature, 5);
                break;
            case 302: // Crab.
                TamePetFamily(player, creature, 8);
                break;
            case 303: // Crocolisk.
                TamePetFamily(player, creature, 6);
                break;
            case 304: // Gorilla.
                TamePetFamily(player, creature, 9);
                break;
            case 305: // Scorpid.
                TamePetFamily(player, creature, 20);
                break;
            case 306: // Turtle.
                TamePetFamily(player, creature, 21);
                break;
            case 307: // Warp Stalker.
                TamePetFamily(player, creature, 32);
                break;
            case 308: // Rhino.
                TamePetFamily(player, creature, 43);
                break;
            case 309: // Worm.
                TamePetFamily(player, creature, 42);
                break;
            }
        }
        return true;
    }

    void TamePetFamily(Player *player, Creature * creature, uint32 family)
    {
        if (player->GetPet())
        {
            creature->Whisper("You must either stable or abandon your current pet to use this feature.", LANG_UNIVERSAL, player);
            player->PlayerTalkClass->SendCloseGossip();
            return;
        }

        QueryResult result = WorldDatabase.PQuery("SELECT `entry` FROM `creature_template` WHERE  `family`=%u ORDER BY RAND() LIMIT 1", family);

        if (!result)
            return;
        else
            if (result)
            {
            Field * field = result->Fetch();
            uint32 entry = field[0].GetUInt32();

            Creature * target = creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY() + 2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1);
            if (!target)
            {
                player->PlayerTalkClass->SendCloseGossip();
                return;
            }

            if (target->IsDungeonBoss() || target->isWorldBoss() || !target->GetCreatureTemplate()->IsTameable(player->ToPlayer()->CanTameExoticPets()))
            {
                target->RemoveFromWorld();
                TamePetFamily(player, creature, family);
            }

            Pet* pet = player->CreateTamedPetFrom(target);
            if (!pet)
            {
                player->PlayerTalkClass->SendCloseGossip();
                return;
            }

            target->RemoveFromWorld();

            pet->SetPower(POWER_HAPPINESS, 1048000);
            pet->GetMap()->AddToMap(pet->ToCreature());
            pet->SetUInt64Value(UNIT_FIELD_CREATEDBY, player->GetGUID());
            pet->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, player->getFaction());
            pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());
            pet->GetCharmInfo()->SetPetNumber(sObjectMgr->GeneratePetNumber(), true);
            if (!pet->InitStatsForLevel(player->getLevel()))
                pet->UpdateAllStats();


            player->SetMinion(pet, true);

            pet->SavePetToDB(PET_SAVE_AS_CURRENT);
            pet->InitTalentForLevel();
            player->PetSpellInitialize();

            player->PlayerTalkClass->SendCloseGossip();
            }
    }
};

void AddSC_npc_beastmaster()
{
    new npc_beastmaster();
}
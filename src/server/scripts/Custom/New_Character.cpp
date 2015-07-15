#include "ScriptPCH.h"
#include "DisableMgr.h"

class New_Character : public PlayerScript
{
public:
	New_Character() : PlayerScript("New_Character") {}

    void OnLogin(Player* player, bool first)
    {
        if (player->GetTotalPlayedTime() < 1) // first login @TODO fix the bool on onlogin function (use it instead)
        {
            player->DestroyItemCount(2512, 200, true, false); // Rough Arrow.
            player->DestroyItemCount(2516, 200, true, false); // Light Shot.

           player->DestroyItem(INVENTORY_SLOT_BAG_0, 19, true);
           player->DestroyItem(INVENTORY_SLOT_BAG_0, 20, true);
           player->DestroyItem(INVENTORY_SLOT_BAG_0, 21, true);
           player->DestroyItem(INVENTORY_SLOT_BAG_0, 22, true);

            //player->DestroyItemCount(2102, 1, true, false); // Small Ammo Pouch.
            //player->DestroyItemCount(2101, 1, true, false); // Light Quiver.

            switch (player->getClass())
            {
            case CLASS_DRUID:
                player->AddItem(44605, 1); // Wild Spineleaf.
                player->AddItem(44614, 1); // Starleaf Seed.
                break;
            case CLASS_PALADIN:
                player->AddItem(17033, 1); // Symbol of Divinity.
                player->AddItem(21177, 1); // Symbol of Kings.
                break;
            case CLASS_MAGE:
                player->AddItem(17020, 1); // Arcane Powder.
                player->AddItem(17056, 1); // Light Feather.
                break;
            case CLASS_HUNTER:
                player->AddItem(52020, 1); // Shatter Rounds.
                player->AddItem(52021, 1); // Iceblade Arrow.
                break;
            case CLASS_DEATH_KNIGHT:
                player->AddItem(37201, 1); // Corpse Dust.
                break;
            case CLASS_ROGUE:
                player->AddItem(3775, 1); // Crippling Poison.
                player->AddItem(43235, 1); // Wound Poison VII.
                player->AddItem(43237, 1); // Anethetic Poison II.
                player->AddItem(43231, 1); // Instant Poison IX.
                player->AddItem(5237, 1); // Mind-numbing Poison.
                player->AddItem(43233, 1); // Deadly Poison IX.
                break;
            case CLASS_SHAMAN:
                player->AddItem(17058, 1); // Fish Oil.
                player->AddItem(17030, 1); // Ankh.
                player->AddItem(17057, 1); // Shiny Fish Scales.
                break;
            case CLASS_PRIEST:
                player->AddItem(44615, 1); // Devout Candle.
                player->AddItem(17056, 1); // Light Feather.
                break;
            case CLASS_WARLOCK:
                player->AddItem(16583, 1); // Demonic Figurine.
                player->AddItem(5565, 1); // Infernal Stone.
                player->AddItem(6265, 1); // Soul Shard.
                break;
            }
            player->EquipNewItem(19, 23162, true);
            player->EquipNewItem(20, 23162, true);
            player->EquipNewItem(21, 23162, true);
            player->EquipNewItem(22, 23162, true);

            player->AddItem(43236, 1); // Star's Sorrow.
            player->AddItem(21215, 1); // Graccu's Mince Fruitcake.
            player->AddItem(34722, 1); // Heavy Frostweave Bandage.

            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_NECK, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BODY, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_TRINKET1, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_TRINKET2, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_TABARD, true);
            player->DestroyItem(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET, true);
        }
    }
};



void AddSC_New_Character()
{
	new New_Character;
	//new motd_message_player;
}
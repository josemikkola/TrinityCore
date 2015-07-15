#include "Player.h"

class OnLogin_PlayerScript : public PlayerScript
{
public:
    OnLogin_PlayerScript() : PlayerScript("OnLogin_PlayerScript") { }

    void OnLogin(Player* player, bool first)
    {
        SpellEntry* spellInfo = NULL;
        for (uint32 i = 0; i < sSpellStore.GetNumRows(); ++i)
        {
            spellInfo = (SpellEntry*)sSpellStore.LookupEntry(i);
            if (!spellInfo)
                continue;

            for (uint8 j = 0; j < MAX_SPELL_EFFECTS; ++j)
            {
                if (spellInfo->Effect[j] == SPELL_EFFECT_PROFICIENCY && !player->HasSpell(spellInfo->Id) && player->IsSpellFitByClassAndRace(spellInfo->Id))
                {
                    if (spellInfo->EquippedItemClass == ITEM_CLASS_WEAPON && !(player->GetWeaponProficiency() & spellInfo->EquippedItemSubClassMask))
                        player->AddSpell(spellInfo->Id, true, false, true, false);
                    if (spellInfo->EquippedItemClass == ITEM_CLASS_ARMOR && !(player->GetArmorProficiency() & spellInfo->EquippedItemSubClassMask))
                        player->AddSpell(spellInfo->Id, true, false, true, false);
                }
            }
        }
		
		if (player->GetTotalPlayedTime() < 1) // first login @TODO fix the bool on onlogin function (use it instead)
        {
            player->DestroyItemCount(2512, 200, true, false); // Rough Arrow.
            player->DestroyItemCount(2516, 200, true, false); // Light Shot.

           player->DestroyItem(INVENTORY_SLOT_BAG_0, 19, true);
           player->DestroyItem(INVENTORY_SLOT_BAG_0, 20, true);
           player->DestroyItem(INVENTORY_SLOT_BAG_0, 21, true);
           player->DestroyItem(INVENTORY_SLOT_BAG_0, 22, true);
		   
            player->EquipNewItem(19, 23162, true);
            player->EquipNewItem(20, 23162, true);
            player->EquipNewItem(21, 23162, true);
            player->EquipNewItem(22, 23162, true);

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

void AddSC_OnLogin_PlayerScript()
{
    new OnLogin_PlayerScript();
}

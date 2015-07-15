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
    }
};

void AddSC_OnLogin_PlayerScript()
{
    new OnLogin_PlayerScript();
}

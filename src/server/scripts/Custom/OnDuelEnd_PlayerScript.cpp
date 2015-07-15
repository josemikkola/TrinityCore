#include "ScriptPCH.h"

class OnDuelEnd_PlayerScript : public PlayerScript

{
public: OnDuelEnd_PlayerScript() : PlayerScript("OnDuelEnd_PlayerScript") { }
		
        void OnDuelEnd(Player* pWinner, Player* pLoser, DuelCompleteType /*type*/)
        {
            if (pWinner->GetZoneId() == 394)
            {
                if (pWinner->getPowerType() == POWER_MANA)
                {
                    pWinner->SetPower(POWER_MANA, pWinner->GetMaxPower(POWER_MANA));
                }
                pWinner->SetHealth(pWinner->GetMaxHealth());
                pWinner->RemoveArenaSpellCooldowns();
                pWinner->RemoveAura(57723);
                pWinner->RemoveAura(57724);
                pWinner->RemoveAura(25771);
                pWinner->RemoveAura(41425);
                pWinner->RemoveAura(61987);
                pWinner->RemoveAura(57723);
                pWinner->RemoveAura(57724);
                pWinner->RemoveAura(25771);
                pWinner->RemoveAura(41425);
                pWinner->RemoveAura(61987);
            }
            if (pLoser->GetZoneId() == 394)
            {
                if (pLoser->getPowerType() == POWER_MANA)
                {
                    pLoser->SetPower(POWER_MANA, pLoser->GetMaxPower(POWER_MANA));
                }
                pLoser->SetHealth(pWinner->GetMaxHealth());
                pLoser->RemoveArenaSpellCooldowns();
                pLoser->RemoveAura(57723);
                pLoser->RemoveAura(57724);
                pLoser->RemoveAura(25771);
                pLoser->RemoveAura(41425);
                pLoser->RemoveAura(61987);
                pLoser->RemoveAura(57723);
                pLoser->RemoveAura(57724);
                pLoser->RemoveAura(25771);
                pLoser->RemoveAura(41425);
                pLoser->RemoveAura(61987);
            }
        }
};
void AddSC_OnDuelEnd_PlayerScript()
{
    new OnDuelEnd_PlayerScript;
}
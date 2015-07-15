#include "ScriptPCH.h"

class OnDuelStart_PlayerScript : public PlayerScript

{
public: OnDuelStart_PlayerScript() : PlayerScript("OnDuelStart_PlayerScript") { }
		
		void OnDuelStart(Player* player, Player* plTarget)
		{
            if (player->GetZoneId() == 394)
			{
				if ( player->getPowerType() == POWER_MANA )
				{
					player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
				}
				player->SetHealth(player->GetMaxHealth());
				player->RemoveArenaSpellCooldowns();
				player->RemoveAura(57723);
				player->RemoveAura(57724);
				player->RemoveAura(25771);
				player->RemoveAura(41425);
				player->RemoveAura(61987);
				player->RemoveAura(57723);
				player->RemoveAura(57724);
				player->RemoveAura(25771);
				player->RemoveAura(41425);
				player->RemoveAura(61987);
			}
            if (plTarget->GetZoneId() == 394)
			{
				if ( plTarget->getPowerType() == POWER_MANA )
				{
					plTarget->SetPower(POWER_MANA, plTarget->GetMaxPower(POWER_MANA));
				}
				plTarget->SetHealth(plTarget->GetMaxHealth());
				plTarget->RemoveArenaSpellCooldowns();
				plTarget->RemoveAura(57723);
				plTarget->RemoveAura(57724);
				plTarget->RemoveAura(25771);
				plTarget->RemoveAura(41425);
				plTarget->RemoveAura(61987);
				plTarget->RemoveAura(57723);
				plTarget->RemoveAura(57724);
				plTarget->RemoveAura(25771);
				plTarget->RemoveAura(41425);
				plTarget->RemoveAura(61987);
			}
		}
};
void AddSC_OnDuelStart_PlayerScript()
{
    new OnDuelStart_PlayerScript;
}
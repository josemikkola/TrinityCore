#include "Language.h"
#include "Group.h"

void SendSummonRequestToParty(Player* player, uint32 map, uint32 zone, float x, float y, float z, float orientation)
{
    Group* group = player->GetGroup();
    if (!group)
        return;

    Group::MemberSlotList const &members = group->GetMemberSlots();
    for (Group::MemberSlotList::const_iterator itr = members.begin(); itr != members.end(); ++itr)
    {
        Group::MemberSlot const &slot = *itr;
        Player* member = ObjectAccessor::FindPlayer((*itr).guid);
        if (member && member->GetSession())
        {
            if (member->IsInFlight())
            {
                member->GetMotionMaster()->MovementExpired();
                member->CleanupAfterTaxiFlight();
            }
            else
                member->SaveRecallPosition();

            if (member->GetGUID() == player->GetGUID())
                return;

            member->SetSummonPoint(map, x, y, z);
            WorldPacket data(SMSG_SUMMON_REQUEST, 8 + 4 + 4);
            data << uint64(member->GetGUID());
            data << uint32(zone);
            data << uint32(MAX_PLAYER_SUMMON_DELAY*IN_MILLISECONDS);
            member->GetSession()->SendPacket(&data);
        }
    }
}
/*
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2014 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "msgteammember.h"
#include "player.h"

using namespace std;

MsgTeamMember :: MsgTeamMember(const Player& aMember, Action aAction)
    : Msg(sizeof(MsgInfo)), mInfo((MsgInfo*)mBuf)
{
    create(aMember, aAction);
}

MsgTeamMember :: MsgTeamMember(const vector<const Player*>& aMembers, Action aAction)
    : Msg(sizeof(MsgInfo) + (sizeof(TeamMemberInfo) * (aMembers.size() - 1))),
      mInfo((MsgInfo*)mBuf)
{
    create(aMembers, aAction);
}

MsgTeamMember :: ~MsgTeamMember()
{

}

void
MsgTeamMember :: create(const Player& aMember, Action aAction)
{
    ASSERT(&aMember != nullptr);

    mInfo->Header.Length = mLen;
    mInfo->Header.Type = MSG_TEAMMEMBER;

    mInfo->Action = aAction;
    mInfo->Amount = 1;

    strncpy(mInfo->Members[0].Name, aMember.getName(), MAX_NAMESIZE);
    mInfo->Members[0].UniqId = aMember.getUID();
    mInfo->Members[0].LookFace = aMember.getLook();
    mInfo->Members[0].MaxLife = aMember.getMaxHP();
    mInfo->Members[0].CurLife = aMember.getCurHP();
}

void
MsgTeamMember :: create(const vector<const Player*>& aMembers, Action aAction)
{
    ASSERT(&aMembers != nullptr);
    ASSERT(aMembers.size() > 0 && aMembers.size() <= MsgTeamMember::_MAX_TEAMMEMBER);

    mInfo->Header.Length = mLen;
    mInfo->Header.Type = MSG_TEAMMEMBER;

    mInfo->Action = aAction;
    mInfo->Amount = (uint8_t)aMembers.size();

    for (size_t i = 0, count = aMembers.size(); i < count; ++i)
    {
        const Player& member = *aMembers.at(i);
        ASSERT(&member != nullptr);

        strncpy(mInfo->Members[i].Name, member.getName(), MAX_NAMESIZE);
        mInfo->Members[i].UniqId = member.getUID();
        mInfo->Members[i].LookFace = member.getLook();
        mInfo->Members[i].MaxLife = member.getMaxHP();
        mInfo->Members[i].CurLife = member.getCurHP();
    }
}

void
MsgTeamMember :: swap(uint8_t* aBuf) const
{
    ASSERT(aBuf != nullptr);

    MsgInfo* info = (MsgInfo*)aBuf;

    for (int i = 0; i < info->Amount; ++i)
    {
        info->Members[i].UniqId = bswap32(info->Members[i].UniqId);
        info->Members[i].LookFace = bswap32(info->Members[i].LookFace);
        info->Members[i].MaxLife = bswap16(info->Members[i].MaxLife);
        info->Members[i].CurLife = bswap16(info->Members[i].CurLife);
    }
}

/*
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2014 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_MSG_TEAMMEMBER_H_
#define _FAITH_EMULATOR_MSG_TEAMMEMBER_H_

#include "common.h"
#include "msg.h"
#include <vector>

class Player;

class MsgTeamMember : public Msg
{
public:
    static const int _MAX_TEAMMEMBER = 5;

    enum Action
    {
        ACTION_ADD = 0,
        ACTION_DROP = 1
    };

    #pragma pack(push, 1)
    typedef struct
    {
        char Name[MAX_NAMESIZE];
        uint32_t UniqId;
        uint32_t LookFace;
        uint16_t MaxLife;
        uint16_t CurLife;
    }TeamMemberInfo;
    #pragma pack(pop)

public:
    #pragma pack(push, 1)
    typedef struct
    {
        /** Generic header of all msgs */
        Msg::Header Header;
        uint8_t Action;
        uint8_t Amount;
        TeamMemberInfo Members[1];
    }MsgInfo;
    #pragma pack(pop)

public:
    MsgTeamMember(const Player& aMember, Action aAction);
    MsgTeamMember(const std::vector<const Player*>& aMembers, Action aAction);

    /* destructor */
    virtual ~MsgTeamMember();

private:
    /* internal filling of the packet */
    void create(const Player& aMember, Action aAction);
    void create(const std::vector<const Player*>& aMembers, Action aAction);

    /* internal swapping of the integers for neutral-endian support */
    virtual void swap(uint8_t* aBuf) const;

private:
    MsgInfo* mInfo; //!< the casted internal reference to the buffer
};

#endif // _FAITH_EMULATOR_MSG_TEAMMEMBER_H_

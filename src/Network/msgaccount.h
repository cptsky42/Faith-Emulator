/**
 * ****** EoF Emulator - Closed Source ******
 * Copyright (C) 2012 CptSky
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _EOFEMU_MSG_ACCOUNT_H_
#define _EOFEMU_MSG_ACCOUNT_H_

#include "common.h"
#include "msg.h"

class MsgAccount : public Msg
{
public:
    #pragma pack(1)
    typedef struct
    {
        Msg::Header Header;
        char Account[MAX_NAMESIZE];
        char Password[MAX_NAMESIZE];
        char Server[MAX_NAMESIZE];
    }MsgInfo;
    #pragma pack(pop)

public:
    MsgAccount(const char* aAccount, const char* aPassword, const char* aServer);
    MsgAccount(uint8_t** aBuf, size_t aLen);
    virtual ~MsgAccount();

    virtual void process(Client* aClient);

private:
    void create(const char* aAccount, const char* aPassword, const char* aServer);

private:
    MsgInfo* mInfo;
};

#endif // _EOFEMU_MSG_ACCOUNT_H_

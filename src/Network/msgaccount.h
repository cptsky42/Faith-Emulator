/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_MSG_ACCOUNT_H_
#define _FAITH_EMULATOR_MSG_ACCOUNT_H_

#include "common.h"
#include "msg.h"

/**
 * First msg sent to the AccServer to request a new connection.
 */
class MsgAccount : public Msg
{
public:
    #pragma pack(1)
    typedef struct
    {
        /** Generic header of all msgs */
        Msg::Header Header;
        /** The account name */
        char Account[MAX_NAMESIZE];
        /** The encrypted password */
        char Password[MAX_NAMESIZE];
        /** The game server name */
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
    MsgInfo* mInfo; //!< the casted internal reference to the buffer
};

#endif // _FAITH_EMULATOR_MSG_ACCOUNT_H_

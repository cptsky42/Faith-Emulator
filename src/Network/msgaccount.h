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
    /**
     * Create a new MsgAccount packet for the specified account.
     *
     * @param[in]   aAccount    the account
     * @param[in]   aPassword   the password of the account
     * @param[in]   aServer     the server of the role
     */
    MsgAccount(const char* aAccount, const char* aPassword, const char* aServer);

    /**
     * Create a message object from the specified buffer.
     * The buffer will be took by the object and the memory
     * freed when the object will be destroyed.
     *
     * If the server is on a Be architecture, all the integers
     * are swapped.
     *
     * @param[in,out] aBuf        a pointer to the buffer to take
     *                            the pointer will be set to null
     * @param[in]     aLen        the length in bytes of the buffer
     */
    MsgAccount(uint8_t** aBuf, size_t aLen);

    /* destructor */
    virtual ~MsgAccount();

    /**
     * Process the message received from the client.
     *
     * @param[in]     aClient      a pointer to the client which
     *                             has sent the message
     */
    virtual void process(Client* aClient);

private:
    /* internal filling of the packet */
    void create(const char* aAccount, const char* aPassword, const char* aServer);

private:
    MsgInfo* mInfo; //!< the casted internal reference to the buffer
};

#endif // _FAITH_EMULATOR_MSG_ACCOUNT_H_

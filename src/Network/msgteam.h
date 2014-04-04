/*
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2014 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_MSG_TEAM_H_
#define _FAITH_EMULATOR_MSG_TEAM_H_

#include "common.h"
#include "msg.h"

class Player;

class MsgTeam : public Msg
{
public:
    enum Action
    {
        ACTION_CREATE = 0,                  // TS, TC
        ACTION_APPLY_JOIN = 1,              // TS
        ACTION_LEAVE = 2,                   // TS, TC
        ACTION_ACCEPT_INVITE = 3,           // TS
        ACTION_INVITE = 4,                  // TS, TC
        ACTION_AGREE_JOIN = 5,              // TS
        ACTION_DISMISS = 6,                 // TS, TC
        ACTION_KICKOUT = 7,                 // TS, TC
        ACTION_CLOSE_TEAM = 8,              // TS, TC
        ACTION_OPEN_TEAM = 9,               // TS, TC
        ACTION_CLOSE_MONEYACCESS = 10,      // TS
        ACTION_OPEN_MONEYACCESS = 11,       // TS
        ACTION_CLOSE_ITEMACCESS = 12,       // TS
        ACTION_OPEN_ITEMACCESS = 13,        // TS
        ACTION_CLOSE_GEMACCESS = 15,        // TS
        ACTION_OPEN_GEMACCESS = 16          // TS
    };

public:
    #pragma pack(push, 1)
    typedef struct
    {
        /** Generic header of all msgs */
        Msg::Header Header;
        /** The action */
        uint16_t Action;
        /** The unique Id of the player. */
        uint32_t UniqId;
    }MsgInfo;
    #pragma pack(pop)

public:
    MsgTeam(uint32_t aUID, Action aAction);

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
    MsgTeam(uint8_t** aBuf, size_t aLen);

    /* destructor */
    virtual ~MsgTeam();

    /**
     * Process the message received from the client.
     *
     * @param[in]     aClient      a pointer to the client which
     *                             has sent the message
     */
    virtual void process(Client* aClient);

private:
    /* internal filling of the packet */
    void create(uint32_t aUID, Action aAction);

    /* internal swapping of the integers for neutral-endian support */
    virtual void swap(uint8_t* aBuf) const;

private:
    MsgInfo* mInfo; //!< the casted internal reference to the buffer
};

#endif // _FAITH_EMULATOR_MSG_TEAM_H_

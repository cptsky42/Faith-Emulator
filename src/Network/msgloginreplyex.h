/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_MSG_LOGINREPLYEX_H_
#define _FAITH_EMULATOR_MSG_LOGINREPLYEX_H_

#include "common.h"
#include "msg.h"

/**
 *
 */
class MsgLoginReplyEx : public Msg
{
public:
    #pragma pack(1)
    typedef struct
    {
        Msg::Header Header;
        int32_t AccountUID;
        int32_t Data;
        int32_t ServerPort;
        uint32_t Uin; // the 91ID of the user...
        char Info[MAX_NAMESIZE_CLI];

    }MsgInfo;
    #pragma pack(pop)

public:
    MsgLoginReplyEx(int32_t aAccUID, int32_t aData,
                    const char* aInfo, int32_t aServerPort = 5816,
                    uint32_t Uin = 0);

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
    MsgLoginReplyEx(uint8_t** aBuf, size_t aLen);

    /* destructor */
    ~MsgLoginReplyEx();

private:
    /* internal filling of the packet */
    void create(int32_t aAccUID, int32_t aData,
                const char* aInfo, int32_t aServerPort,
                uint32_t Uin);

    /* internal swapping of the integers for neutral-endian support */
    virtual void swap(uint8_t* aBuf);

private:
    MsgInfo* mInfo; //!< the casted internal reference to the buffer
};

#endif // _FAITH_EMULATOR_MSG_LOGINREPLYEX_H_

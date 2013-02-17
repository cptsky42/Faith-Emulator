#ifndef _FAITH_EMULATOR_MSG_CONNECT_H_
#define _FAITH_EMULATOR_MSG_CONNECT_H_

#include "common.h"
#include "msg.h"

/**
 *
 */
class MsgConnect : public Msg
{
public:
    #pragma pack(1)
    typedef struct
    {
        Msg::Header Header;
        int32_t AccountUID;
        int32_t Data;
        char Info[MAX_NAMESIZE];
    }MsgInfo;
    #pragma pack(pop)

public:
    MsgConnect(int32_t aAccUID, int32_t aData, const char* aInfo);

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
    MsgConnect(uint8_t** aBuf, size_t aLen);

    /* destructor */
    ~MsgConnect();

    /**
     * Process the message received from the client.
     *
     * @param[in]     aClient      a pointer to the client which
     *                             has sent the message
     */
    virtual void process(Client* aClient);

private:
    /* internal filling of the packet */
    void create(int32_t aAccUID, int32_t aData, const char* aInfo);

    /* internal swapping of the integers for neutral-endian support */
    virtual void swap(uint8_t* aBuf);

private:
    MsgInfo* mInfo; //!< the casted internal reference to the buffer
};

#endif // _FAITH_EMULATOR_MSG_CONNECT_H_

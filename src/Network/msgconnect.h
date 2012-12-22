#ifndef _EOFEMU_MSG_CONNECT_H_
#define _EOFEMU_MSG_CONNECT_H_

#include "common.h"
#include "msg.h"

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
    MsgConnect(uint8_t** aBuf, size_t aLen);
    ~MsgConnect();

    virtual void process(Client* aClient);

private:
    void create(int32_t aAccUID, int32_t aData, const char* aInfo);

    virtual void swap(uint8_t* aBuf);

private:
    MsgInfo* mInfo;
};

#endif // _EOFEMU_MSG_CONNECT_H_

#ifndef _EOFEMU_MSG_ITEMINFO_H_
#define _EOFEMU_MSG_ITEMINFO_H_

#include "common.h"
#include "msg.h"

class MsgItemInfo : public Msg
{
public:
    enum Action
    {
        ACTION_NONE = 0,
        ACTION_ADD_ITEM = 1,
        ACTION_TRADE = 2,
        ACTION_UPDATE = 3,
        ACTION_OTHER_PLAYER_EQUIP = 4, // uid is user uid
        ACTION_AUCTION = 5
    };

public:
    #pragma pack(1)
    typedef struct
    {
        Msg::Header Header;
        int32_t UniqId;
        int32_t Type;
        uint16_t Amount;
        uint16_t AmountLimit;
        uint8_t Action;
        uint8_t Ident;
        uint8_t Position;
        uint8_t Gem1;
        uint8_t Gem2;
        uint8_t Magic1; // Attr
        uint8_t Magic2; // Unknown
        uint8_t Magic3; // Plus
    }MsgInfo;
    #pragma pack(pop)

public:
    MsgItemInfo(void* aItem, Action aAction); // FIXME!
    MsgItemInfo(uint8_t** aBuf, size_t aLen);
    virtual ~MsgItemInfo();

private:
    void create(void* aItem, Action aAction); // FIXME!

    virtual void swap(uint8_t* aBuf);

private:
    MsgInfo* mInfo;
};

#endif // _EOFEMU_MSG_ITEMINFO_H_

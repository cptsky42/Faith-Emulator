#ifndef _FAITH_EMULATOR_MSG_USERINFO_H_
#define _FAITH_EMULATOR_MSG_USERINFO_H_

#include "common.h"
#include "msg.h"

class MsgUserInfo : public Msg
{
public:
    #pragma pack(1)
    typedef struct
    {
        Msg::Header Header;
        int32_t UniqId;
        int32_t Look;
        int16_t Hair;
        int8_t Length;
        int8_t Fat;
        int32_t Money;
        int32_t Exp;
        uint8_t Padding1[10];
        uint16_t MercenaryExp;
        uint16_t MercenaryLevel;
        uint8_t Padding2[14];
        uint16_t Strength;
        uint16_t Agility;
        uint16_t Vitality;
        uint16_t Spirit;
        uint16_t AddPoints;
        uint16_t CurHP;
        uint16_t CurMP;
        int16_t PkPoints;
        uint8_t Level;
        uint8_t Profession;
        uint8_t AutoAllot;
        uint8_t Metempsychosis;
        uint8_t ShowName;
        uint8_t Buf[1];
    }MsgInfo;
    #pragma pack(pop)

public:
    MsgUserInfo(void* aEntity); // FIXME!
    MsgUserInfo(uint8_t** aBuf, size_t aLen);
    virtual ~MsgUserInfo();

private:
    void create(void* aEntity); // FIXME!

    virtual void swap(uint8_t* aBuf);

private:
    MsgInfo* mInfo; //!< the casted internal reference to the buffer
};

#endif // _FAITH_EMULATOR_MSG_USERINFO_H_

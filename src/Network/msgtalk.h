#ifndef _FAITH_EMULATOR_MSG_TALK_H_
#define _FAITH_EMULATOR_MSG_TALK_H_

#include "common.h"
#include "msg.h"

class MsgTalk : public Msg
{
public:
    enum Channel
    {
        CHANNEL_NORMAL = 2000,
        CHANNEL_PRIVATE = CHANNEL_NORMAL + 1,
        CHANNEL_ACTION = CHANNEL_NORMAL + 2,
        CHANNEL_TEAM = CHANNEL_NORMAL + 3,
        CHANNEL_SYNDICATE = CHANNEL_NORMAL + 4,
        CHANNEL_SYSTEM = CHANNEL_NORMAL + 5,
        CHANNEL_FAMILY = CHANNEL_NORMAL + 6,
        CHANNEL_TALK = CHANNEL_NORMAL + 7,
        CHANNEL_YELP = CHANNEL_NORMAL + 8,
        CHANNEL_FRIEND = CHANNEL_NORMAL + 9,
        CHANNEL_GLOBAL = CHANNEL_NORMAL + 10,
        CHANNEL_GM = CHANNEL_NORMAL + 11,
        CHANNEL_WHISPER = CHANNEL_NORMAL + 12,
        CHANNEL_GHOST = CHANNEL_NORMAL + 13,
        CHANNEL_SERVE = CHANNEL_NORMAL + 14,
        CHANNEL_MY = CHANNEL_NORMAL + 15,

        CHANNEL_REGISTER = CHANNEL_NORMAL + 100,
        CHANNEL_ENTRANCE = CHANNEL_NORMAL + 101,
        CHANNEL_SHOP = CHANNEL_NORMAL + 102,
        CHANNEL_PETTALK = CHANNEL_NORMAL + 103,
        CHANNEL_CRYOUT = CHANNEL_NORMAL + 104,
        CHANNEL_WEBPAGE = CHANNEL_NORMAL + 105,

        CHANNEL_NEWMESSAGE = CHANNEL_NORMAL + 106,
        CHANNEL_TASK = CHANNEL_NORMAL + 107,

        CHANNEL_SYNWAR_FIRST = CHANNEL_NORMAL + 108,
        CHANNEL_SYNWAR_NEXT = CHANNEL_NORMAL + 109,

        CHANNEL_LEAVEWORD = CHANNEL_NORMAL + 110,
        CHANNEL_SYNANNOUNCEG = CHANNEL_NORMAL + 111,
        CHANNEL_SYNANNOUNCEL = CHANNEL_NORMAL + 114,

        CHANNEL_MESSAGEBOX = CHANNEL_NORMAL + 112,
        CHANNEL_REJECT = CHANNEL_NORMAL + 113,

        CHANNEL_TRACE = CHANNEL_NORMAL + 115,

        CHANNEL_MSG_TRAGE = CHANNEL_NORMAL + 201,
        CHANNEL_MSG_FRIEND = CHANNEL_NORMAL + 202,
        CHANNEL_MSG_TEAM = CHANNEL_NORMAL + 203,
        CHANNEL_MSG_SYN = CHANNEL_NORMAL + 204,
        CHANNEL_MSG_OTHER = CHANNEL_NORMAL + 205
    };

    enum Style
    {
        STYLE_NORMAL = 0,
        STYLE_SCROLL = 0x0001,
        STYLE_FLASH = 0x0002,
        STYLE_BLAST = 0x0008
    };

public:
    #pragma pack(1)
    typedef struct
    {
        Msg::Header Header;
        uint32_t Color; // ARGB code
        int16_t Channel;
        int16_t Style;
        int32_t Timestamp;
        uint8_t Buf[1];
    }MsgInfo;
    #pragma pack(pop)

public:
    MsgTalk(const char* aHearer, const char* aSpeaker, const char* aWords,
            Channel aChannel, uint32_t aColor = 0x00FFFFFF);
    MsgTalk(uint8_t** aBuf, size_t aLen);
    virtual ~MsgTalk();

    virtual void process(Client* aClient);

private:
    void create(const char* aHearer, const char* aSpeaker, const char* aEmotion,
                const char* aWords, Channel aChannel, uint32_t aColor);

    virtual void swap(uint8_t* aBuf);

private:
    MsgInfo* mInfo; //!< the casted internal reference to the buffer
};

#endif // _FAITH_EMULATOR_MSG_TALK_H_

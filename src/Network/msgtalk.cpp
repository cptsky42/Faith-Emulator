#include "msgtalk.h"
#include "stringpacker.h"
#include <string.h>

MsgTalk :: MsgTalk(const char* aHearer, const char* aSpeaker, const char* aWords,
                   Channel aChannel, uint32_t aColor)
    : Msg(sizeof(MsgInfo) +
          (aHearer != nullptr ? strlen(aHearer) : 0)  + 1 +
          (aSpeaker != nullptr ? strlen(aSpeaker) : 0)  + 1 +
          /* (aEmotion != nullptr ? strlen(aEmotion) : 0) */ + 1 +
          (aWords != nullptr ? strlen(aWords) : 0) + 1)
{
    mInfo = (MsgInfo*)mBuf;
    create(aHearer, aSpeaker, "", aWords, aChannel, aColor); // HACK !
}

MsgTalk :: MsgTalk(uint8_t** aBuf, size_t aLen)
    : Msg(aBuf, aLen)
{
    ASSERT(aLen >= sizeof(MsgInfo));

    mInfo = (MsgInfo*)mBuf;
    #if BYTE_ORDER == BIG_ENDIAN
    swap(mBuf);
    #endif
}


MsgTalk :: ~MsgTalk()
{

}

void
MsgTalk :: create(const char* aHearer, const char* aSpeaker, const char* aEmotion,
                  const char* aWords, Channel aChannel, uint32_t aColor)
{
    ASSERT(aHearer != nullptr && aHearer[0] != '\0');
    ASSERT(aSpeaker != nullptr && aSpeaker[0] != '\0');
    ASSERT(aEmotion != nullptr);
    ASSERT(aWords != nullptr && aWords[0] != '\0');

    if (strlen(aHearer) < MAX_NAMESIZE &&
        strlen(aSpeaker) < MAX_NAMESIZE &&
        strlen(aEmotion) < MAX_NAMESIZE &&
        strlen(aWords) < MAX_WORDSSIZE)
    {
        mInfo->Header.Length = mLen;
        mInfo->Header.Type = MSG_TALK;

        mInfo->Color = aColor;
        mInfo->Channel = (uint16_t)aChannel;
        mInfo->Style = 0; // TODO : Style enum.
        mInfo->Timestamp = 0; // TODO : timeGetTime();

        StringPacker packer(mInfo->Buf);
        packer.addString(aHearer);
        packer.addString(aSpeaker);
        packer.addString(aEmotion);
        packer.addString(aWords);
    }
    else
    {
        LOG("Invalid length: hearer=%zu, speaker=%zu, emotion=%zu, words=%zu",
            strlen(aHearer), strlen(aSpeaker), strlen(aEmotion), strlen(aWords));
    }
}

void
MsgTalk :: swap(uint8_t* aBuf)
{
    ASSERT(aBuf != nullptr);

    MsgInfo* info = (MsgInfo*)aBuf;

    info->Color = bswap32(info->Color);
    info->Channel = bswap16(info->Channel);
    info->Style = bswap16(info->Style);
    info->Timestamp = bswap32(info->Timestamp);
}

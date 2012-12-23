#include "msgaction.h"
#include "client.h"

MsgAction :: MsgAction(void* aEntity, int32_t aData, Action aAction)
    : Msg(sizeof(MsgInfo))
{
    mInfo = (MsgInfo*)mBuf;
    create(aEntity, aData, aAction);
}

MsgAction :: MsgAction(uint8_t** aBuf, size_t aLen)
    : Msg(aBuf, aLen)
{
    ASSERT(aLen >= sizeof(MsgInfo));

    mInfo = (MsgInfo*)mBuf;
    #if BYTE_ORDER == BIG_ENDIAN
    swap(mBuf);
    #endif
}


MsgAction :: ~MsgAction()
{

}

void
MsgAction :: create(void* aEntity, int32_t aData, Action aAction)
{
    mInfo->Header.Length = mLen;
    mInfo->Header.Type = MSG_ACTION;

    mInfo->Timestamp = 0; // TODO : timeGetTime();
    if (aEntity != nullptr)
    {
        // FIXME ! Use an entity class
        mInfo->UniqId = 1000000;
        mInfo->PosX = 465;
        mInfo->PosY = 50;
        mInfo->Direction = 1;
    }
    else
    {
        mInfo->UniqId = 0;
        mInfo->PosX = 0;
        mInfo->PosY = 0;
        mInfo->Direction = 0;
    }

    mInfo->Data = aData;
    mInfo->Action = aAction;
}

void
MsgAction :: process(Client* aClient)
{
    ASSERT(aClient != nullptr);

    switch (mInfo->Action)
    {
    case ACTION_ENTER_MAP:
        {
            //mInfo->UniqId = 1000000;
            mInfo->PosX = 465;
            mInfo->PosY = 50;
            mInfo->Data = 2000;

            aClient->send(this);
            break;
        }
    default:
        {
            fprintf(stdout, "Unknown action[%04u], data=[%d]\n",
                    mInfo->Action, mInfo->Data);
            break;
        }
    }
}

void
MsgAction :: swap(uint8_t* aBuf)
{
    ASSERT(aBuf != nullptr);

    MsgInfo* info = (MsgInfo*)aBuf;

    info->Timestamp = bswap32(info->Timestamp);
    info->UniqId = bswap32(info->UniqId);
    info->PosX = bswap16(info->PosX);
    info->PosY = bswap16(info->PosY);
    info->Direction = bswap32(info->Direction);
    info->Data = bswap32(info->Data);
    info->Action = bswap32(info->Action);
}

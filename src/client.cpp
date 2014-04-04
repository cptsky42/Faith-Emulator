/*
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "client.h"
#include "networkclient.h"
#include "tqcipher.h"
#include "msg.h"
#include "player.h"
#include "database.h"
#include "world.h"
#include <stdlib.h>

Client :: Client(NetworkClient* aSocket)
    : mSocket(aSocket), mCipher(nullptr),
      mAccountID(-1), mAccLvl(0), mFlags(0),
      mPlayer(nullptr)
{
    ASSERT(aSocket != nullptr);

    TqCipher* cipher = new TqCipher();
    cipher->generateIV(0x0705FD1F, 0x1B7A313F);

    mCipher = cipher;

    mStatus = Client::NOT_AUTHENTICATED;
}

Client :: ~Client()
{
    mSocket = nullptr; // Qt handle the memory

    if (mPlayer != nullptr)
    {
        World& world = World::getInstance();
        world.removePlayer(*mPlayer);

        SAFE_DELETE(mPlayer);
    }

    SAFE_DELETE(mCipher);
}

void
Client :: save()
{
    printf("Calling save for %p ... %s\n",
           this, mPlayer != nullptr ? mPlayer->getName() : "");

    err_t err = ERROR_SUCCESS;
    int tries = 0;

    if (mPlayer != nullptr)
    {
        static const Database& db = Database::getInstance(); // singleton

        do
        {
            err = db.savePlayer(*this);
            ++tries;

            if (!IS_SUCCESS(err))
            {
                LOG(WARN, "Failed to save player %s for %p. Trying again.",
                    mPlayer->getName(), this);
            }
        }
        while (err != ERROR_SUCCESS && tries < 3);

        if (!IS_SUCCESS(err))
        {
            LOG(ERROR, "Failed to save player %s for %p.",
                mPlayer->getName(), this);
        }
    }
}

void
Client :: send(const Msg* aMsg) const
{
    ASSERT(aMsg != nullptr);

    uint8_t* data = new uint8_t[aMsg->getLength()];
    memcpy(data, aMsg->getBuffer(), aMsg->getLength());

    mCipher->encrypt(data, aMsg->getLength());
    mSocket->send(data, aMsg->getLength());

    SAFE_DELETE_ARRAY(data);
}

void
Client :: disconnect()
{
    mSocket->disconnect();
}


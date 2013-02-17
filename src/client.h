/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_CLIENT_H
#define _FAITH_EMULATOR_CLIENT_H

#include "common.h"
#include "tqcipher.h"
#include <string>

class NetworkClient;
class Msg;
class Player;

class Client
{
public:
    enum Status
    {
        /** The client is still not authenticated */
        NOT_AUTHENTICATED,
        /** The client is banned */
        BANNED,
        /** The client use an invalid username */
        INVALID_USERNAME,
        /** The client use an invalid password */
        INVALID_PASSWORD,
        /** The client use an invalid token */
        INVALID_KEY,
        /** The client is normal */
        NORMAL,
        /** The client is a new account */
        NEW_ACCOUNT
    };

public:
    Client(NetworkClient* aSocket);
    ~Client();

    void send(Msg* aMsg);
    void send(uint8_t* aBuf, size_t aLen);

public:
    /** Get a reference to the client cipher */
    TqCipher& getCipher() { return mCipher; }
    /** Get the status of the account */
    Status getStatus() { return mStatus; }
    /** Get the player object linked to this client */
    Player* getPlayer() { return mPlayer; }

    void setAccount(const std::string& aAccount) { mAccount = aAccount; }
    void setStatus(Status aStatus) { mStatus = aStatus; }

private:
    NetworkClient* mSocket; //!< the TCP/IP socket wrapper of the client
    TqCipher mCipher; //!< the cipher of the client

    Status mStatus; //!< the status of the account

    std::string mAccount; //!< the account name
    int8_t mAccLvl; //!< the account permissions level
    int32_t mFlags; //!< the account flags
    std::string mCharacter; //!< the character name

    Player* mPlayer; //!< the character linked to this client
};

#endif // _FAITH_EMULATOR_CLIENT_H

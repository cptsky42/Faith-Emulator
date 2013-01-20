#ifndef _FAITH_EMULATOR_CLIENT_H
#define _FAITH_EMULATOR_CLIENT_H

#include "common.h"
#include "tqcipher.h"
#include <string>

class NetworkClient;
class Msg;

class Client
{
public:
    enum Status
    {
        NOT_AUTHENTICATED,
        BANNED,
        INVALID_USERNAME,
        INVALID_PASSWORD,
        INVALID_KEY,
        NORMAL,
        NEW_ACCOUNT
    };

public:
    Client(NetworkClient* aSocket);
    ~Client();

    void send(Msg* aMsg);
    void send(uint8_t* aBuf, size_t aLen);

public:
    TqCipher& getCipher() { return mCipher; }
    Status getStatus() { return mStatus; }

    void setAccount(const std::string& aAccount) { mAccount = aAccount; }
    void setStatus(Status aStatus) { mStatus = aStatus; }

private:
    NetworkClient* mSocket;
    TqCipher mCipher;

    Status mStatus;

    std::string mAccount;
    int8_t mAccLvl;
    int32_t mFlags;
    std::string mCharacter;
};

#endif // _FAITH_EMULATOR_CLIENT_H

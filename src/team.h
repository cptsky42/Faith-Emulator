#ifndef TEAM_H
#define TEAM_H

#include "common.h"

class Msg;
class Player;

class Team
{
public:
    static const uint8_t MAX_TEAM_AMOUNT = 5;

public:
    ~Team();

public:
    void open() { mIsClosed = false; }
    void close() { mIsClosed = true; }

    void openMoney() { mIsMoneyForbidden = false; }
    void closeMoney() { mIsMoneyForbidden = true; }

    void openItem() { mIsItemForbidden = false; }
    void closeItem() { mIsItemForbidden = true; }

    void openGem() { mIsGemForbidden = false; }
    void closeGem() { mIsGemForbidden = true; }

    void broadcastTeamMsg(const Msg* aMsg) const;

public:
    uint32_t getUID() { return mUID; }

    bool isClosed() const { return mIsClosed; }

private:
    Team();

private:
    const uint32_t mUID;
    Player& mLeader;

    bool mIsClosed;
    bool mIsMoneyForbidden;
    bool mIsItemForbidden;
    bool mIsGemForbidden;
};

#endif // TEAM_H

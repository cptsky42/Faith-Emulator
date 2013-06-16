/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_MSG_PLAYER_H_
#define _FAITH_EMULATOR_MSG_PLAYER_H_

#include "common.h"
#include "msg.h"

class Player;
class Monster;

class MsgPlayer : public Msg
{
public:
    static const int32_t MASK_SYNID = INT32_C(0x00FFFFFF);
    static const int32_t MASK_RANK_SHIFT = INT32_C(24);

public:
    #pragma pack(1)
    typedef struct
    {
        /** Generic header of all msgs */
        Msg::Header Header;
        /** The unique Id of the entity */
        int32_t UniqId;
        /** The look of the entity */
        int32_t Look;

        union
        {
            uint64_t Status;
            struct
            {
                uint16_t StatuaryLife;
                uint16_t StaturayFrame;
            };
        };


        union
        {
            int32_t SynId_Rank;
            int32_t OwnerUID;
        };

        int32_t WeaponRType;
        int32_t WeaponLType;

        union
        {
            int32_t MountType;
            struct
            {
                uint16_t Life;
                uint16_t Level;
            };
        };

        int16_t MantleType;
        uint16_t PosX;
        uint16_t PosY;
        uint16_t Hair;
        int8_t Length;
        int8_t Fat;
        int8_t Direction;
        int8_t Pose;
        uint8_t Unknown; // ActionSpeed; TutorLevel; MercenaryLevel; NobilityRank;
        uint8_t Buf[1];
    }MsgInfo;
    #pragma pack(pop)

public:
    /**
     * Create a new MsgPlayer packet for the specified player.
     *
     * @param[in]   aPlayer     a reference to the player object
     */
    MsgPlayer(Player& aPlayer);

    /**
     * Create a new MsgPlayer packet for the specified monster.
     *
     * @param[in]   aMonster     a reference to the monster object
     */
    MsgPlayer(Monster& aMonster); //TODO...


    /**
     * Create a message object from the specified buffer.
     * The buffer will be took by the object and the memory
     * freed when the object will be destroyed.
     *
     * If the server is on a Be architecture, all the integers
     * are swapped.
     *
     * @param[in,out] aBuf        a pointer to the buffer to take
     *                            the pointer will be set to null
     * @param[in]     aLen        the length in bytes of the buffer
     */
    MsgPlayer(uint8_t** aBuf, size_t aLen);

    /* destructor */
    virtual ~MsgPlayer();

private:
    /* internal filling of the packet */
    void create(Player& aPlayer);
    void create(Monster& aMonster);

    /* internal swapping of the integers for neutral-endian support */
    virtual void swap(uint8_t* aBuf);

private:
    MsgInfo* mInfo; //!< the casted internal reference to the buffer
};

#endif // _FAITH_EMULATOR_MSG_PLAYER_H_

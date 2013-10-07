/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_MSG_LOGINACCOUNTEX_H_
#define _FAITH_EMULATOR_MSG_LOGINACCOUNTEX_H_

#include "common.h"
#include "msg.h"

//if ( strstr( m_pInfo->szInfo, "·þÎñÆ÷Î´Æô¶¯" ) != NULL )
//    strcpy( szInfo, g_objGameDataSet.GetStr( 100400 ) );
//else if ( strstr( m_pInfo->szInfo, "ÕÊºÅÃû»ò¿ÚÁî´í" ) != NULL )
//    strcpy( szInfo, g_objGameDataSet.GetStr( 100401 ) );
//else if ( strstr( m_pInfo->szInfo, "ÇëÉÔºóÖØÐÂµÇÂ¼" ) != NULL )
//    strcpy( szInfo, g_objGameDataSet.GetStr( 100402 ) );
//else if ( strstr( m_pInfo->szInfo, "¸ÃÕÊºÅ±»·âºÅ" ) != NULL )
//    strcpy( szInfo, g_objGameDataSet.GetStr( 100403 ) );
//else if ( strstr( m_pInfo->szInfo, "¸ÃÕÊºÅ±»Ëø¶¨" ) != NULL )
//    strcpy( szInfo, g_objGameDataSet.GetStr( 100404) );
//else if ( strstr( m_pInfo->szInfo, "·þÎñÆ÷ÈËÊýÂú" ) != NULL )
//    strcpy( szInfo, g_objGameDataSet.GetStr( 100405 ) );
//else if ( strstr( m_pInfo->szInfo, "·þÎñÆ÷Î¬»¤»òÍøÂç¶ÂÈû" ) != NULL )
//    strcpy( szInfo, g_objGameDataSet.GetStr( 100406 ) );
//else
//    strcpy( szInfo, g_objGameDataSet.GetStr( 100100 ) );

/**
 * First msg sent to the AccServer to request a new connection.
 * Used by the XY client and not the english one.
 */
class MsgLoginAccountEx : public Msg
{
public:
    #pragma pack(push, 1)
    typedef struct
    {
        /** Generic header of all msgs */
        Msg::Header Header;
        /** Unknown value. */
        int32_t Type;
        /** The account name */
        char Account[MAX_NAMESIZE_CLI];
        /** The encrypted password */
        char Password[MAX_NAMESIZE_CLI];
        /** The game server name */
        char Server[MAX_NAMESIZE_CLI];
        /** The res.dat value */
        char Info[MAX_NAMESIZE_CLI];
    }MsgInfo;
    #pragma pack(pop)

public:
    /**
     * Create a new MsgAccount packet for the specified account.
     *
     * @param[in]   aAccount    the account
     * @param[in]   aPassword   the password of the account
     * @param[in]   aServer     the server of the role
     * @param[in]   aInfo       the information
     */
    MsgLoginAccountEx(const char* aAccount, const char* aPassword,
                      const char* aServer, const char* aInfo);

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
    MsgLoginAccountEx(uint8_t** aBuf, size_t aLen);

    /* destructor */
    virtual ~MsgLoginAccountEx();

    /**
     * Process the message received from the client.
     *
     * @param[in]     aClient      a pointer to the client which
     *                             has sent the message
     */
    virtual void process(Client* aClient);

private:
    /* internal filling of the packet */
    void create(const char* aAccount, const char* aPassword,
                const char* aServer, const char* aInfo);

    /* internal swapping of the integers for neutral-endian support */
    virtual void swap(uint8_t* aBuf);

private:
    MsgInfo* mInfo; //!< the casted internal reference to the buffer
};

#endif // _FAITH_EMULATOR_MSG_LOGINACCOUNTEX_H_

/*
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2014 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "msgteam.h"
#include "client.h"
#include "player.h"
#include "team.h"
#include "mapmanager.h"
#include "gamemap.h"

MsgTeam :: MsgTeam(uint32_t aUID, Action aAction)
    : Msg(sizeof(MsgInfo)), mInfo((MsgInfo*)mBuf)
{
    create(aUID, aAction);
}

MsgTeam :: MsgTeam(uint8_t** aBuf, size_t aLen)
    : Msg(aBuf, aLen), mInfo((MsgInfo*)mBuf)
{
    ASSERT(aLen >= sizeof(MsgInfo));

    #if BYTE_ORDER == BIG_ENDIAN
    swap(mBuf);
    #endif
}


MsgTeam :: ~MsgTeam()
{

}

void
MsgTeam :: create(uint32_t aUID, Action aAction)
{
    mInfo->Header.Length = mLen;
    mInfo->Header.Type = MSG_TEAM;

    mInfo->Action = aAction;
    mInfo->UniqId = aUID;
}

void
MsgTeam :: process(Client* aClient)
{
    ASSERT(aClient != nullptr);
    ASSERT(aClient->getPlayer() != nullptr);

    Client& client = *aClient;
    Player& player = *aClient->getPlayer();

    // TODO isGM / isPM
//    if (player.isGM() && !player.isPM())
//    {
//        // No team
//        return;
//    }

    static const MapManager& mgr = MapManager::getInstance(); // singleton
    GameMap* map = mgr.getMap(player.getMapId());
    if (map != nullptr && map->isTeamDisabled())
        return;

    Team* team = player.getTeam();

    switch (mInfo->Action)
    {
#if 0
        case _MSGTEAM_CREATE:
            {
                DEBUG_TRY
                if (pUser->CreateTeam())
                {
                    pUser->SendMsg(this);
                }
                DEBUG_CATCH("MsgTeam proc create team crash.")
            }
            break;
        case _MSGTEAM_APPLYJOIN:
            {
                if (m_pInfo->idPlayer == ID_NONE)
                    return;

                if (pUser->GetTeam())
                {
                    pUser->SendSysMsg(STR_INTEAM_NOJOIN);
                    return;
                }

                OBJID	idTarget = m_pInfo->idPlayer;
                CUser* pTarget = NULL;

                DEBUG_TRY
                if(!pUser->GetMap()->QueryObj(pUser->GetPosX(), pUser->GetPosY(), OBJ_USER, idTarget, IPP_OF(pTarget)))
                {
                    pUser->SendSysMsg(STR_NO_APPLICANT);
                    return;
                }
                DEBUG_CATCH("MsgTeam apply join Queryobj by ID crash.");

                CTeam* pTeam	= pTarget->GetTeam();
                if (!pTeam)
                {
                    pUser->SendSysMsg(STR_NO_TEAM);
                    return;
                }

                if (pTeam->IsClosed())
                {
                    pUser->SendSysMsg(STR_FORBIDDEN_JOIN);
                    return;
                }

                if (pTeam->GetMemberAmount() >= _MAX_TEAMAMOUNT)
                {
                    pUser->SendSysMsg(STR_TEAM_FULL);
                    return;
                }
                if (!pTarget->IsAlive())
                {
                    pUser->SendSysMsg(STR_APPLIED_LEADER_DEAD);
                    return;
                }

                DEBUG_TRY
                if (pTeam->GetLeader() != pTarget->GetID())
                {
                    pUser->SendSysMsg(STR_NO_CAPTAIN_CLOSE);
                    return;
                }
                DEBUG_CATCH("CMsgTeam apply join Queryobj by leader id crash.");

                //if (!pUser->FetchApply(CUser::APPLY_TEAMAPPLY, pTarget->GetID()))
                //{
                pUser->SetApply(CUser::APPLY_TEAMAPPLY, idTarget);
                IF_NOT(this->Create(pUser->GetID(), _MSGTEAM_APPLYJOIN))
                    return;

                pTarget->SendMsg(this);
                pUser->SendSysMsg(STR_JOIN_REQUEST_SENT);
                /*}
                else
                {
                pUser->SendSysMsg(STR_INVI_SENT);
            }*/
            }
            break;
        case _MSGTEAM_AGREEJOIN:
            {
                if (m_pInfo->idPlayer == ID_NONE)
                    return;

                CTeam* pTeam	= pUser->GetTeam();
                if (!pTeam)
                {
                    pUser->SendSysMsg(STR_NO_TEAM_TO_INVITE);
                    return;
                }
                if (pTeam->GetLeader() != pUser->GetID())
                {
                    pUser->SendSysMsg(STR_NOT_CAPTAIN_INVITE);
                    return;
                }
                if (pTeam->GetMemberAmount() >= _MAX_TEAMAMOUNT)
                {
                    pUser->SendSysMsg(STR_YOUR_TEAM_FULL);
                    return;
                }

                OBJID	idTarget = m_pInfo->idPlayer;
                CUser* pTarget = NULL;

                DEBUG_TRY
                if(!pUser->GetMap()->QueryObj(pUser->GetPosX(), pUser->GetPosY(), OBJ_USER, idTarget, IPP_OF(pTarget)))
                {
                    pUser->SendSysMsg(STR_APPLICANT_NOT_FOUND);
                    return;
                }
                DEBUG_CATCH("CMsgTeam proc accept join Queryobj by idtarget crash.")

                if (pTarget->GetTeam())
                {
                    pTarget->SendSysMsg(STR_HAVE_JOIN_TEAM);
                    return;
                }

                if (pTarget->FetchApply(CUser::APPLY_TEAMAPPLY, pUser->GetID()))
                {
                    pTarget->SetApply(CUser::APPLY_NONE, ID_NONE);
                    if (pUser->AcceptTeamMember(pTarget))
                    {// MsgTeamMember£¨»´∂”µƒ–≈œ¢»´∂”ƒ⁄∏¸–¬π„≤•
                    }
                }
                else
                {
                    pUser->SendSysMsg(STR_NOT_TO_JOIN);
                }
            }
            break;
        case _MSGTEAM_INVITE:
            {
                if (m_pInfo->idPlayer == ID_NONE)
                    return;

                CTeam* pTeam	= pUser->GetTeam();
                if (!pTeam)
                {
                    pUser->SendSysMsg(STR_NOTEAM_TO_INVITE);
                    return;
                }

                if (pTeam->IsClosed())
                {
                    pUser->SendSysMsg(STR_TEAM_CLOSED);
                    return;
                }

                if (pTeam->GetLeader() != pUser->GetID())
                {
                    pUser->SendSysMsg(STR_NOT_CAPTAIN_ACCEPT);
                    return;
                }

                if (pTeam->GetMemberAmount() >= _MAX_TEAMAMOUNT)
                {
                    pUser->SendSysMsg(STR_YOUR_TEAM_FULL);
                    return;
                }

                OBJID	idTarget = m_pInfo->idPlayer;
                CUser* pTarget = NULL;

                DEBUG_TRY
                if(!pUser->GetMap()->QueryObj(pUser->GetPosX(), pUser->GetPosY(), OBJ_USER, idTarget, IPP_OF(pTarget)))
                {
                    pUser->SendSysMsg(STR_INVITED_NOT_FOUND);
                    return;
                }
                DEBUG_CATCH("CMsgTeam proc invite queryobj by id crash.");

                if (pTarget->GetTeam())
                {
                    pUser->SendSysMsg(STR_HAS_IN_TEAM);
                    return;
                }
                if (!pTarget->IsAlive())
                {
                    pUser->SendSysMsg(STR_INVITED_IS_DEAD);
                    return;
                }

                //if (!pUser->FetchApply(CUser::APPLY_TEAMINVIT, pTarget->GetID()))
                //
                pUser->SetApply(CUser::APPLY_TEAMINVIT, pTarget->GetID());
                IF_NOT(this->Create(pUser->GetID(), _MSGTEAM_INVITE))
                    return;

                pTarget->SendMsg(this);
                pUser->SendSysMsg(STR_INVITE_SENT);
            }
            break;
        case _MSGTEAM_ACCEPTINVITE:
            {
                if (m_pInfo->idPlayer == ID_NONE)
                    return;

                if (pUser->GetTeam())
                {
                    //pUser->SendSysMsg("[∂”ŒÈ]ƒ˙“—æ≠ «∂”‘±¡À£¨≤ªƒ‹Ω” ‹—˚«Îº”»Î–¬∂”ŒÈ°£");
                    return;
                }

                OBJID	idTarget = m_pInfo->idPlayer;
                CUser* pTarget = NULL;

                DEBUG_TRY
                if(!pUser->GetMap()->QueryObj(pUser->GetPosX(), pUser->GetPosY(), OBJ_USER, idTarget, IPP_OF(pTarget)))
                {
                    //pUser->SendSysMsg("[∂”ŒÈ]√ª”–’“µΩ—˚«Î’ﬂ°£");
                    return;
                }
                DEBUG_CATCH("CMsgTeam proc accept invite queryobj by id crash.")

                CTeam* pTeam	= pTarget->GetTeam();
                if (!pTeam)
                {
                    pUser->SendSysMsg(STR_NOT_CREATE_TEAM);
                    return;
                }
                if (pTeam->GetMemberAmount() >= _MAX_TEAMAMOUNT)
                {
                    pUser->SendSysMsg(STR_HIS_TEAM_FULL);
                    return;
                }

                if (pTeam->GetLeader() != pTarget->GetID())
                {
                    pUser->SendSysMsg(STR_NO_CAPTAIN_CLOSE);
                    return;
                }

                if (pTarget->FetchApply(CUser::APPLY_TEAMINVIT, pUser->GetID()))
                {
                    pTarget->SetApply(CUser::APPLY_NONE, ID_NONE);
                    if (pUser->AcceptTeamInvit(pTarget))
                    {// MsgTeamMember£¨»´∂”µƒ–≈œ¢»´∂”ƒ⁄∏¸–¬π„≤•
                    }
                }
                else
                {
                    pUser->SendSysMsg(STR_NOT_BE_INVIITED);
                }
            }
            break;
        case _MSGTEAM_LEAVE:
            {
                DEBUG_TRY
                CTeam* pTeam	= pUser->GetTeam();
                if (!pTeam)
                {
                //	pUser->SendSysMsg("[∂”ŒÈ]ƒ˙ªπ≤ª «∂”‘±£¨≤ªƒ‹ÕÀ≥ˆ∂”ŒÈ°£");
                    return;
                }

                m_pInfo->idPlayer	= pUser->GetID();
                pUser->QuitTeam();
                DEBUG_CATCH("CMsgTeam proc quitteam crash.")
            }
            break;
        case _MSGTEAM_DISMISS:
            {
                DEBUG_TRY
                CTeam* pTeam	= pUser->GetTeam();
                if (!pTeam)
                {
                //	pUser->SendSysMsg("[∂”ŒÈ]ƒ˙ªπ√ª”–∂”ŒÈ£¨≤ªƒ‹Ω‚…¢∂”ŒÈ°£");
                    return;
                }
                if (pTeam->GetLeader() != pUser->GetID())
                {
                //	pUser->SendSysMsg("[∂”ŒÈ]ƒ˙≤ª «∂”≥§£¨≤ªƒ‹Ω‚…¢∂”ŒÈ°£");
                    return;
                }

                pUser->DismissTeam();
                DEBUG_CATCH("CMsgTeam proc dismiss crash.")
            }
            break;
        case _MSGTEAM_OPENTEAM:
            {
                CTeam* pTeam	= pUser->GetTeam();
                if (!pTeam)
                {
                //	pUser->SendSysMsg("[∂”ŒÈ]ƒ˙√ª”–∂”ŒÈ°£");
                    return;
                }

                pTeam->Open();
            }
            break;
        case _MSGTEAM_CLOSETEAM:
            {
                CTeam* pTeam	= pUser->GetTeam();
                if (!pTeam)
                {
                //	pUser->SendSysMsg("[∂”ŒÈ]ƒ˙√ª”–∂”ŒÈ°£");
                    return;
                }

                pTeam->Close();
            }
            break;
        case _MSGTEAM_KICKOUT:
            {
                CTeam* pTeam	= pUser->GetTeam();
                if (!pTeam)
                {
                //	pUser->SendSysMsg("[∂”ŒÈ]ƒ˙√ª”–∂”ŒÈ°£");
                    return;
                }

                if(pUser->GetID() != m_pInfo->idPlayer)		// ≤ªƒ‹ø™≥˝◊‘º∫
                    pUser->KickOut(m_pInfo->idPlayer);
            }
            break;
        case _MSGTEAM_CLOSEMONEYACCESS:
            {
                CTeam* pTeam	= pUser->GetTeam();
                if (!pTeam)
                    return;

                pTeam->CloseMoney();
            }
            break;
        case _MSGTEAM_OPENMONEYACCESS:
            {
                CTeam* pTeam	= pUser->GetTeam();
                if (!pTeam)
                    return;

                pTeam->OpenMoney();
            }
            break;
        case _MSGTEAM_CLOSEITEMACCESS:
            {
                CTeam* pTeam	= pUser->GetTeam();
                if (!pTeam)
                    return;

                pTeam->CloseItem();
            }
            break;
        case _MSGTEAM_OPENITEMACCESS:
            {
                CTeam* pTeam	= pUser->GetTeam();
                if (!pTeam)
                    return;

                pTeam->OpenItem();
            }
            break;
        case _MSGTEAM_CLOSEGEMACCESS:
            {
                CTeam* pTeam	= pUser->GetTeam();
                if (!pTeam)
                    return;

                pTeam->CloseGemAccess();
            }
            break;
        case _MSGTEAM_OPENGEMACCESS:
            {
                CTeam* pTeam	= pUser->GetTeam();
                if (!pTeam)
                    return;

                pTeam->OpenGemAccess();
            }
            break;
#endif
        default:
            {
                fprintf(stdout, "Unknown team action[%04u], data=[%d]\n",
                        mInfo->Action, mInfo->UniqId);
                break;
            }
    }
}

void
MsgTeam :: swap(uint8_t* aBuf) const
{
    ASSERT(aBuf != nullptr);

    MsgInfo* info = (MsgInfo*)aBuf;

    info->Action = bswap16(info->Action);
    info->UniqId = bswap32(info->UniqId);
}

/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 CptSky
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_MSG_ACTION_H_
#define _FAITH_EMULATOR_MSG_ACTION_H_

#include "common.h"
#include "msg.h"

class MsgAction : public Msg
{
public:
    enum Action
    {
        ACTION_NONE = 0,
        ACTION_CHG_DIR = 1,
        ACTION_POSITION = 2,
        actionEmotion			=3,
        actionBroadcastPos		=4,
        actionDivorce			=5,
        actionSelfUnfreeze		=6,
        actionChgMap			=7,
        actionFlyMap			=8,
        actionChgWeather		=9,
        actionFireworks			=10,
        actionDie				=11,
        actionQuitSyn			=12,
        actionWalk				=13,
        ACTION_ENTER_MAP = 14,
        actionGetItemSet		=15,
        actionGetGoodFriend		=16,
        actionForward			=17,
        actionLeaveMap			=18,		// ∑˛ŒÒ∆˜->øÕªß∂À,idPlayer
        actionJump				=19,
        actionRun				=20,
        actionEquip				=21,
        actionUnequip			=22,
        actionUplev				=23,
        actionXpCLear			=24,
        actionReborn			=25,
        actionDelRole			=26,
        actionGetWeaponSkillSet	=27,
        actionGetMagicSet		=28,
        actionSetPkMode			=29,
        actionGetSynAttr		=30,
        actionGhost				=31,
        actionSynchro			=32,
        actionQueryFriendInfo	=33,
        actionQueryLeaveWord	=34,
        actionChangeFace		=35,
        actionMine				=36,
        actionTeamMemeberPos	=37,
        actionQueryPlayer		=38,
        actionAbortMagic		=39,
        actionMapARGB			=40,
        actionMapStatus			=41,		// abandon
        actionQueryTeamMember	=42,
        actionCreateBooth		=43,		// ø™ º∞⁄ÃØ server/client; idUser: playerID; unPosX,unPosY: playerpos; unDir:dirofbooth; idTarget:idnpc;
        actionSuspendBooth		=44,		//  ’∆∞⁄ÃØ
        actionResumeBooth		=45,		// ºÃ–¯∞⁄ÃØ server/client; idUser: playerID; unPosX,unPosY: playerpos; unDir:dirofbooth; idTarget:idnpc;
        actionDestroyBooth		=46,		// Õ£÷π∞⁄ÃØ
        actionQueryCryOut		=47,		// ≤È—Ø∞⁄ÃØﬂ∫∫»
        actionPostCmd			=48,		// to client only
        actionQueryEquipment	=49,		// to server //idUserŒ™–Ë“™queryµƒPlayerID
        actionAbortTransform	=50,		// to server
        actionCombineSubSyn		=51,		// to client, idUser-> idSubSyn, idTarget-> idTargetSyn
        actionLanding			=52,		// to server only
        actionGetMoney			=53,		// to client only // ºÒµΩ500“‘º∞500“‘…œ«Æ£¨÷ª¥´∏¯◊‘º∫£¨dwDataŒ™ºÒµΩµƒ«Æ
        actionDischarge			=54,		// to server
        actionQueryEnemyInfo	=55,		// to server
        actionMoveStop			=56,		// data=milli secs.
        actionKickBack			=57,		// to client	idUser is Player ID, unPosX unPosY is Player pos
        actionDropMagic			=58,		// to client only, data is magic type
        actionDropSkill			=59,		// to client only, data is weapon skill type
        actionSoundEffect		=60,		// to client only, client play sound effect, dwData is monster type

        actionQueryMedal		=61,		// to server	idUser is Player ID, dwData is medal
        actionDelMedal			=62,		// to server	idUser is Player ID, dwData is medal
        actionAddMedal			=63,		// to client	idUser is Player ID, dwData is medal
        actionSelectMedal		=64,		// to server	idUser is Player ID, dwData is medal

        actionQueryHonorTitle	=65,		// to server	idUser is Player ID, dwData is title
        actionDelHonorTitle		=66,		// to server	idUser is Player ID, dwData is title
        actionAddHonorTitle		=67,		// to client	idUser is Player ID, dwData is title
        actionSelectHonorTitle	=68,		// to server	idUser is Player ID, dwData is title
        actionOpenDialog		=69,		// to client only, open a dialog, dwData is id of dialog
        actionFlashStatus		=70,		// broadcast to client only, team member only. dwData is dwStatus

        actionQuerySynInfo		=71,		// ≤È—Ø∞Ô≈…–≈œ¢		// to server synicate id
        actionStudentApply		=72,		//  ¶∏∏…Í«Î’– ’ÕΩµ‹	// to server/client idUserŒ™ ¶∏∏ID dwDataŒ™ÕΩµ‹ID
        actionTeacherApply		=73,		// ÕΩµ‹…Í«Î∞› ¶		// to server/client idUserŒ™ÕΩµ‹ID dwDataŒ™ ¶∏∏ID

        actionAgreeStudentApply	=74,		// Õ¨“‚∞› ¶			// to server idUserŒ™ ¶∏∏ID dwDataŒ™ÕΩµ‹ID
        actionAgreeTeacherApply	=75,		// Õ¨“‚’– ’—ß…˙		// to server idUserŒ™ÕΩµ‹ID dwDataŒ™ ¶∏∏ID
        actionDismissStudent    =76,		// ø™≥˝—ß…˙         // to server idUserŒ™ ¶∏∏ID dwDataŒ™ÕΩµ‹ID
        actionLeaveTeacher		=77,		// ±≥≈— ¶√≈			// to server idUserŒ™ÕΩµ‹ID dwDataŒ™ ¶∏∏ID
        actionQuerySchoolMember	=78,		// ≤È—Ø ¶ÕΩ¡–±Ì		//to server //
        actionTeacherRequest	=79,		// ‘⁄–¬ ÷π§ª·÷–∑¢∞› ¶…Í«Î	// to server


        actionQueryPlayerTaskAcceptedList		=80,		// ≤È—ØÕÊº“–¸…Õµƒ“—Ω”»ŒŒÒ¡–±Ì // to server // dwDataŒ™…œ“ª¥Œ≤È—Øµƒ◊Ó∫Û“ª∏ˆID
        actionQueryPlayerTaskUnacceptedList		=81,		// ≤È—ØÕÊº“–¸…ÕµƒŒ¥Ω”»ŒŒÒ¡–±Ì // to server // dwDataŒ™…œ“ª¥Œ≤È—Øµƒ◊Ó∫Û“ª∏ˆID
        actionQueryPlayerTaskCompletedList		=82,		// ≤È—ØÕÊº“–¸…Õµƒ“—ÕÍ≥…»ŒŒÒ¡–±Ì // to server // dwDataŒ™…œ“ª¥Œ≤È—Øµƒ◊Ó∫Û“ª∏ˆID
        actionQueryPlayerMyTaskList				=83,		// ≤È—ØÕÊº“–¸…ÕµƒŒ“µƒ»ŒŒÒ¡–±Ì // to server // dwDataŒ™…œ“ª¥Œ≤È—Øµƒ◊Ó∫Û“ª∏ˆID
        actionQueryPlayerTaskDetail				=84,		// ≤È—ØÕÊº“–¸…Õ»ŒŒÒœÍœ∏ƒ⁄»› // to server // dwDataŒ™≤È—Ø»ŒŒÒID

        actionAcceptPlayerTask					=88,		// Ω” ‹»ŒŒÒ // to server // dwDataŒ™»ŒŒÒID
        actionCompletePlayerTask				=89,		  // ÕÍ≥…»ŒŒÒ // to server // dwDataŒ™»ŒŒÒID
        actionCancelPlayerTask					=90,		// ≥∑œ˙»ŒŒÒ // to server // dwDataŒ™»ŒŒÒID

        actionLockUser							=91,		// À¯∂®øÕªß∂À≤¢Õ¨≤Ω◊¯±Í∑ΩœÚ
        actionUnLockUser						=92,		// Ω‚À¯øÕªß∂À≤¢Õ¨≤Ω◊¯±Í∑ΩœÚ
        actionMagicTrack						=93,		// Õ¨≤Ω◊¯±Í∑ΩœÚ

        actionQueryStudentsOfStudent			=94,		// ≤È—ØÕΩÀÔ¡–±Ì£¨idTarget = –Ë“™≤È—ØÕΩÀÔ¡–±ÌµƒÕΩµ‹ID

        actionBurstXp							=95,		// XP±¨∑¢£¨‘ –Ì π”√XPººƒ‹
        actionChangeToRandomPos					=96,       // ÀÊª˙“∆∂Ø
        actionDisappear							=97
    };

public:
    #pragma pack(1)
    typedef struct
    {
        Msg::Header Header;
        int32_t Timestamp;
        int32_t UniqId;
        uint16_t PosX;
        uint16_t PosY;
        int32_t Direction;
        int32_t Data;
        uint32_t Action;
    }MsgInfo;
    #pragma pack(pop)

public:
    MsgAction(void* aEntity, int32_t aData, Action aAction);
    MsgAction(uint8_t** aBuf, size_t aLen);
    virtual ~MsgAction();

    virtual void process(Client* aClient);

private:
    void create(void* aEntity, int32_t aData, Action aAction);

    virtual void swap(uint8_t* aBuf);

private:
    MsgInfo* mInfo;
};

#endif // _FAITH_EMULATOR_MSG_ACTION_H_

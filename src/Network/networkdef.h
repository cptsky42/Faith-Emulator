#ifndef _EOFEMU_NETWORK_DEF_H_
#define _EOFEMU_NETWORK_DEF_H_

#include "common.h"

const size_t MAX_NAMESIZE = 16;
const size_t MAX_WORDSSIZE = 255;

const uint16_t MSG_NONE = 0;
const uint16_t MSG_GENERAL = 1000;

const uint16_t MSG_REGISTER     = MSG_GENERAL + 1;
const uint16_t MSG_LOGIN        = MSG_GENERAL + 2;
const uint16_t MSG_LOGOUT       = MSG_GENERAL + 3;
const uint16_t MSG_TALK         = MSG_GENERAL + 4;
const uint16_t MSG_WALK         = MSG_GENERAL + 5;
const uint16_t MSG_USERINFO     = MSG_GENERAL + 6;
const uint16_t MSG_ATTACK       = MSG_GENERAL + 7;
const uint16_t MSG_ITEMINFO     = MSG_GENERAL + 8;
const uint16_t MSG_ITEM         = MSG_GENERAL + 9;
const uint16_t MSG_ACTION       = MSG_GENERAL + 10;
const uint16_t MSG_ACCIDENT     = MSG_GENERAL + 11;
const uint16_t MSG_TICK         = MSG_GENERAL + 12;
const uint16_t MSG_ROOM         = MSG_GENERAL + 13;
const uint16_t MSG_PLAYER       = MSG_GENERAL + 14;
const uint16_t MSG_NAME         = MSG_GENERAL + 15;
const uint16_t MSG_WEATHER      = MSG_GENERAL + 16;
const uint16_t MSG_USERATTRIB   = MSG_GENERAL + 17;
const uint16_t MSG_ROLE         = MSG_GENERAL + 18;
const uint16_t MSG_FRIEND       = MSG_GENERAL + 19;
const uint16_t MSG_EFFECT       = MSG_GENERAL + 20;
const uint16_t MSG_QUIZGAME     = MSG_GENERAL + 21;
const uint16_t MSG_INTERACT     = MSG_GENERAL + 22;
const uint16_t MSG_TEAM         = MSG_GENERAL + 23;
const uint16_t MSG_ALLOT        = MSG_GENERAL + 24;
const uint16_t MSG_WEAPONSKILL  = MSG_GENERAL + 25;
const uint16_t MSG_TEAMMEMBER   = MSG_GENERAL + 26;
const uint16_t MSG_GEMEMBED     = MSG_GENERAL + 27;

const uint16_t MSG_ACCOUNT      = MSG_GENERAL + 51;
const uint16_t MSG_CONNECT      = MSG_GENERAL + 52;
const uint16_t MSG_TRADE      = MSG_GENERAL + 56;

#endif // _EOFEMU_NETWORK_DEF_H_

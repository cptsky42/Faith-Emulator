QT += core
QT += network sql
QT -= gui

TARGET = "Faith Emulator"
CONFIG   += console
CONFIG   -= app_bundle

#CONFIG += x86 x86_64

TEMPLATE = app

SOURCES += \
    src/server.cpp \
    src/program.cpp \
    src/client.cpp \
    src/Network/Sockets/tcpserver.cpp \
    src/Network/Sockets/networkclient.cpp \
    src/Security/Cryptography/tqcipher.cpp \
    src/Network/msg.cpp \
    src/Network/msgaccount.cpp \
    src/Network/msgconnect.cpp \
    src/Network/msgtalk.cpp \
    src/Network/stringpacker.cpp \
    src/Network/msgaction.cpp \
    src/Network/msguserinfo.cpp \
    src/Network/msguserattrib.cpp \
    src/Database/database.cpp \
    src/Network/msgiteminfo.cpp \
    src/Security/Cryptography/rc5.cpp \
    src/Entity/entity.cpp \
    src/Entity/player.cpp \
    src/Network/msgwalk.cpp \
    src/Map/mapmanager.cpp \
    src/Map/gamemap.cpp \
    src/IO/binarywriter.cpp \
    src/IO/binaryreader.cpp \
    src/IO/finder.cpp \
    src/Network/msgplayer.cpp \
    src/Network/msgnpcinfo.cpp \
    src/Entity/npc.cpp \
    src/Entity/advancedentity.cpp \
    src/Entity/monster.cpp \
    src/world.cpp \
    src/Common/env.cpp \
    src/item.cpp \
    src/third_party/lua-5.2.2/src/lzio.c \
    src/third_party/lua-5.2.2/src/lvm.c \
    src/third_party/lua-5.2.2/src/lundump.c \
    src/third_party/lua-5.2.2/src/ltm.c \
    src/third_party/lua-5.2.2/src/ltablib.c \
    src/third_party/lua-5.2.2/src/ltable.c \
    src/third_party/lua-5.2.2/src/lstrlib.c \
    src/third_party/lua-5.2.2/src/lstring.c \
    src/third_party/lua-5.2.2/src/lstate.c \
    src/third_party/lua-5.2.2/src/lparser.c \
    src/third_party/lua-5.2.2/src/loslib.c \
    src/third_party/lua-5.2.2/src/lopcodes.c \
    src/third_party/lua-5.2.2/src/lobject.c \
    src/third_party/lua-5.2.2/src/loadlib.c \
    src/third_party/lua-5.2.2/src/lmem.c \
    src/third_party/lua-5.2.2/src/lmathlib.c \
    src/third_party/lua-5.2.2/src/llex.c \
    src/third_party/lua-5.2.2/src/liolib.c \
    src/third_party/lua-5.2.2/src/linit.c \
    src/third_party/lua-5.2.2/src/lgc.c \
    src/third_party/lua-5.2.2/src/lfunc.c \
    src/third_party/lua-5.2.2/src/ldump.c \
    src/third_party/lua-5.2.2/src/ldo.c \
    src/third_party/lua-5.2.2/src/ldebug.c \
    src/third_party/lua-5.2.2/src/ldblib.c \
    src/third_party/lua-5.2.2/src/lctype.c \
    src/third_party/lua-5.2.2/src/lcorolib.c \
    src/third_party/lua-5.2.2/src/lcode.c \
    src/third_party/lua-5.2.2/src/lbitlib.c \
    src/third_party/lua-5.2.2/src/lbaselib.c \
    src/third_party/lua-5.2.2/src/lauxlib.c \
    src/third_party/lua-5.2.2/src/lapi.c

HEADERS += \
    src/server.h \
    src/client.h \
    src/Network/Sockets/tcpserver.h \
    src/Network/Sockets/networkclient.h \
    src/Security/Cryptography/tqcipher.h \
    src/Network/msg.h \
    src/Network/msgaccount.h \
    src/Network/networkdef.h \
    src/Network/msgconnect.h \
    src/Network/allmsg.h \
    src/Network/msgtalk.h \
    src/Network/stringpacker.h \
    src/Common/common.h \
    src/Common/arch.h \
    src/Common/def.h \
    src/Common/err.h \
    src/Common/types.h \
    src/Common/log.h \
    src/Common/myassert.h \
    src/Common/endian.h \
    src/Network/msgaction.h \
    src/Network/msguserinfo.h \
    src/Network/msguserattrib.h \
    src/Database/database.h \
    src/Network/msgiteminfo.h \
    src/Security/Cryptography/rc5.h \
    src/Entity/entity.h \
    src/Entity/player.h \
    src/strres.h \
    src/Network/msgwalk.h \
    src/Map/mapmanager.h \
    src/Map/gamemap.h \
    src/IO/binarywriter.h \
    src/IO/binaryreader.h \
    src/IO/finder.h \
    src/Network/msgplayer.h \
    src/Network/msgnpcinfo.h \
    src/Entity/npc.h \
    src/Common/unicode.h \
    src/Entity/advancedentity.h \
    src/Entity/monster.h \
    src/world.h \
    src/Common/env.h \
    src/item.h \
    src/third_party/lua-5.2.2/src/lzio.h \
    src/third_party/lua-5.2.2/src/lvm.h \
    src/third_party/lua-5.2.2/src/lundump.h \
    src/third_party/lua-5.2.2/src/lualib.h \
    src/third_party/lua-5.2.2/src/luaconf.h \
    src/third_party/lua-5.2.2/src/lua.hpp \
    src/third_party/lua-5.2.2/src/lua.h \
    src/third_party/lua-5.2.2/src/ltm.h \
    src/third_party/lua-5.2.2/src/ltable.h \
    src/third_party/lua-5.2.2/src/lstring.h \
    src/third_party/lua-5.2.2/src/lstate.h \
    src/third_party/lua-5.2.2/src/lparser.h \
    src/third_party/lua-5.2.2/src/lopcodes.h \
    src/third_party/lua-5.2.2/src/lobject.h \
    src/third_party/lua-5.2.2/src/lmem.h \
    src/third_party/lua-5.2.2/src/llimits.h \
    src/third_party/lua-5.2.2/src/llex.h \
    src/third_party/lua-5.2.2/src/lgc.h \
    src/third_party/lua-5.2.2/src/lfunc.h \
    src/third_party/lua-5.2.2/src/ldo.h \
    src/third_party/lua-5.2.2/src/ldebug.h \
    src/third_party/lua-5.2.2/src/lctype.h \
    src/third_party/lua-5.2.2/src/lcode.h \
    src/third_party/lua-5.2.2/src/lauxlib.h \
    src/third_party/lua-5.2.2/src/lapi.h

INCLUDEPATH += \
    src/Common \
    src/Network \
    src/Network/Sockets \
    src/Security/Cryptography \
    src/Database \
    src/Entity \
    src/IO \
    src/Map \
    src \
    src/third_party/lua-5.2.2/src \

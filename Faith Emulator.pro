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
    src/Network/msgplayer.cpp

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
    src/Network/msgplayer.h

INCLUDEPATH += \
    src/Common \
    src/Network \
    src/Network/Sockets \
    src/Security/Cryptography \
    src/Database \
    src/Entity \
    src/IO \
    src/Map \
    src

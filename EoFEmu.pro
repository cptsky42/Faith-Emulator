QT += core
QT += network sql
QT -= gui

TARGET = EoFEmu
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
    src/Network/msgiteminfo.cpp

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
    src/Common/include/common.h \
    src/Common/include/assert.h \
    src/Common/include/arch.h \
    src/Common/include/def.h \
    src/Common/include/endian.h \
    src/Common/include/err.h \
    src/Common/include/types.h \
    src/Common/include/log.h \
    src/Network/msgaction.h \
    src/Network/msguserinfo.h \
    src/Network/msguserattrib.h \
    src/Database/database.h \
    src/Network/msgiteminfo.h

INCLUDEPATH += \
    src/Common/include \
    src/Network \
    src/Network/Sockets \
    src/Security/Cryptography \
    src

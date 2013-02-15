/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_DATABASE_H_
#define _FAITH_EMULATOR_DATABASE_H_

#include "common.h"
#include <QtSql/QSqlDatabase>

class QSqlQuery;

class Database
{
public:
    static Database& getInstance();

public:
    ~Database();

    bool connect(const char* aHost, const char* aDbName,
                 const char* aUserName, const char* aPassword);

private:
    Database();

private:
    static Database* sInstance;

private:
    QSqlDatabase mConnection;
};

#endif // _FAITH_EMULATOR_DATABASE_H_

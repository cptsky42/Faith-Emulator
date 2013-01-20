/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 CptSky
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "database.h"
#include <QtSql/QSqlQuery>

/* static */
Database* Database::sInstance = nullptr;

/* static */
Database&
Database :: getInstance()
{
    // TODO? Thread-safe
    if (sInstance == nullptr)
    {
        sInstance = new Database();
    }
    return *sInstance;
}

Database :: Database()
{
    mConnection = QSqlDatabase::addDatabase("QMYSQL");
}

Database :: ~Database()
{
    if (mConnection.isOpen())
    {
        mConnection.close();
    }
}

bool
Database :: connect(const char* aHost, const char* aDbName,
                    const char* aUserName, const char* aPassword)
{
    if (mConnection.isOpen())
    {
        mConnection.close();
    }

    mConnection.setHostName(aHost);
    mConnection.setDatabaseName(aDbName);
    mConnection.setUserName(aUserName);
    mConnection.setPassword(aPassword);

    return mConnection.open();
}


//QSqlQuery query(db);
//success = query.exec("SELECT name, salary FROM employee WHERE salary > 50000");
//while (query.next())
//{
//     QString name = query.value(0).toString();
//     int salary = query.value(1).toInt();
//     qDebug() << name << salary;
// }


//query.clear();
//query.prepare("INSERT INTO employee (id, name, salary) "
//              "VALUES (:id, :name, :salary)");
//query.bindValue(":id", 1001);
//query.bindValue(":name", "Thad Beaumont");
//query.bindValue(":salary", 65000);
//query.exec();

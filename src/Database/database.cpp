/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "database.h"
#include <QtSql/QSqlQuery>
#include <QVariant>

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
    ASSERT(aHost != nullptr && aHost[0] != '\0');
    ASSERT(aDbName != nullptr && aDbName[0] != '\0');
    ASSERT(aUserName != nullptr && aUserName[0] != '\0');
    ASSERT(aPassword != nullptr && aPassword[0] != '\0');

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

err_t
Database :: authenticate(const char* aAccount, const char* aPassword)
{
    ASSERT_ERR(aAccount != nullptr && aAccount[0] != '\0', ERROR_INVALID_PARAMETER);
    ASSERT_ERR(aPassword != nullptr && aPassword[0] != '\0', ERROR_INVALID_PARAMETER);

    const char* cmd = "SELECT password FROM account WHERE name = :name";

    err_t err = ERROR_SUCCESS;

    QSqlQuery query(mConnection);
    query.prepare(cmd);
    query.bindValue(":name", aAccount);

    if (query.exec())
    {
        if (query.size() == 1)
        {
            query.next(); // get the first result...

            QString password = query.value(0).toString();
            if (password.compare(aPassword) != 0)
            {
                // the Account/Password pair is not found
                err = ERROR_NOT_FOUND;
            }
        }
        else
        {
            LOG("The cmd should return only one result, not %d", query.size());
            err = ERROR_NOT_FOUND; // suppose the account is not found
        }
    }
    else
    {
        LOG("Failed to execute the following cmd : %s", cmd);
        err = ERROR_EXEC_FAILED;
    }

    return err;
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

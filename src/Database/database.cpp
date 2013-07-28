/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#include "log.h"
#include "database.h"
#include "world.h"
#include "mapmanager.h"
#include "npc.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlResult>
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
    ASSERT(aPassword != nullptr);

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
            LOG(ERROR, "The cmd should return only one result, not %d", query.size());
            err = ERROR_NOT_FOUND; // suppose the account is not found
        }
    }
    else
    {
        LOG(ERROR, "Failed to execute the following cmd : %s", cmd);
        err = ERROR_EXEC_FAILED;
    }

    return err;
}

err_t
Database :: loadAllNPCs()
{
    const char* cmd = "SELECT * FROM npc";

    err_t err = ERROR_SUCCESS;

    QSqlQuery query(mConnection);
    query.prepare(cmd);

    if (query.exec())
    {
        World& world = World::getInstance();
        while (ERROR_SUCCESS == err && query.next())
        {
            Npc* npc = new Npc(
                           (int32_t)query.value(0).toInt(),
                           nullptr,
                           (uint8_t)query.value(2).toInt(),
                           (int16_t)query.value(3).toInt(),
                           (int16_t)query.value(4).toInt(),
                           (uint16_t)query.value(5).toInt(),
                           (uint16_t)query.value(6).toInt(),
                           (uint8_t)query.value(9).toInt(),
                           (uint8_t)query.value(10).toInt());

            ASSERT(npc != nullptr);
            ASSERT(world.AllNPCs.find(npc->getUID()) == world.AllNPCs.end());

            world.AllNPCs[npc->getUID()] = npc;
        }
    }
    else
    {
        LOG(ERROR, "Failed to execute the following cmd : %s", cmd);
        err = ERROR_EXEC_FAILED;
    }

    return err;
}

err_t
Database :: loadAllMaps()
{
    const char* cmd = "SELECT id, doc_id, type, weather, portal_x, portal_y, reborn_map, reborn_portal, light FROM map";

    err_t err = ERROR_SUCCESS;

    QSqlQuery query(mConnection);
    query.prepare(cmd);

    if (query.exec())
    {
        MapManager& mgr = MapManager::getInstance();
        while (ERROR_SUCCESS == err && query.next())
        {
            GameMap::Info* info = new GameMap::Info();
            int32_t uid = query.value(0).toInt();

            info->OwnerUID = 0;
            info->DocID = (uint16_t)query.value(1).toInt();
            info->Type = (uint32_t)query.value(2).toInt();
            // TODO: weather
            info->PortalX = (uint16_t)query.value(4).toInt();
            info->PortalY = (uint16_t)query.value(5).toInt();
            info->RebornMap = (int32_t)query.value(6).toInt();
            info->RebornPortal = (int32_t)query.value(7).toInt();
            info->Light = (uint32_t)query.value(8).toInt();

            ASSERT(info != nullptr);
            DOIF(err, mgr.createMap(uid, &info));

            SAFE_DELETE(info);
        }
    }
    else
    {
        LOG(ERROR, "Failed to execute the following cmd : %s", cmd);
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

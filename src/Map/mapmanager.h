/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_MAPMANAGER_H_
#define _FAITH_EMULATOR_MAPMANAGER_H_

#include "fscommon.h"
#include "fsenv.h"
#include "gamemap.h"
#include <map>

class MapData;

class MapManager : public Environment::Global
{
public:
    /**
     * Get the MapManager singleton. If the object does not exist yet,
     * it will be created.
     *
     * @returns A reference to the singleton
     */
    static MapManager& getInstance();

public:
    /* destructor */
    virtual ~MapManager();

    err_t loadData();

    err_t createMap(int32_t aUID, GameMap::Info** aInfo);
    err_t linkMap(int32_t aUID, int32_t aRefUID);

private:
    /* constructor */
    MapManager();

private:
    static MapManager* sInstance; //!< static instance of the singleton

private:
    std::map<int32_t, GameMap*> mGameMaps;
    std::map<uint16_t, MapData*> mMaps;
    std::map<std::string, MapData*> mData;
};

#endif // _FAITH_EMULATOR_MAPMANAGER_H_

/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_MAP_DATA_H_
#define _FAITH_EMULATOR_MAP_DATA_H_

#include "common.h"
#include "mapbase.h"
#include <vector>

class BinaryReader;

class MapData
{
public:
    static err_t load(MapData** aOutData, const char* aPath);

public:
    ~MapData();

public:
    uint16_t getWidth() const { return mWidth; }
    uint16_t getHeight() const { return mHeight; }

    Cell getCell(uint16_t aPosX, uint16_t aPosY);
    int getPassage(uint16_t aPosX, uint16_t aPosY);

    //bool FindPath(PASSPATH0* pPathBuf, int nBufSize, POINT posSource, POINT posTarget, IRoleAttr* pAttr, int nEscapeSteps = 0);
    // nEscapeSteps == 0 : Move Forward

private:
    static const int32_t MAX_PATH = 260;

    static const int32_t MAP_NONE = 0;
    static const int32_t MAP_TERRAIN = 1;
    static const int32_t MAP_TERRAIN_PART = 2;
    static const int32_t MAP_SCENE = 3;
    static const int32_t MAP_COVER = 4;
    static const int32_t MAP_ROLE = 5;
    static const int32_t MAP_HERO = 6;
    static const int32_t MAP_PLAYER = 7;
    static const int32_t MAP_PUZZLE = 8;
    static const int32_t MAP_3DSIMPLE = 9;
    static const int32_t MAP_3DEFFECT = 10;
    static const int32_t MAP_2DITEM = 11;
    static const int32_t MAP_3DNPC = 12;
    static const int32_t MAP_3DOBJ = 13;
    static const int32_t MAP_3DTRACE = 14;
    static const int32_t MAP_SOUND = 15;
    static const int32_t MAP_2DREGION = 16;
    static const int32_t MAP_3DMAGICMAPITEM = 17;
    static const int32_t MAP_3DITEM = 18;
    static const int32_t MAP_3DEFFECTNEW = 19;

private:
    MapData();

private:
    /** Load the map data */
    err_t loadMapData(BinaryReader& aReader);
    /** Load all passages data */
    err_t loadPassageData(BinaryReader& aReader);
    /** Load all regions data */
    err_t loadRegionData(BinaryReader& aReader);
    /** Load all layers data */
    err_t loadLayerData(BinaryReader& aReader);

private:
    /** Convert a position to an index. */
    inline size_t pos2idx(uint16_t aPosX, uint16_t aPosY) { return (aPosX + aPosY * mWidth); }
    /** Convert an index to a x-coord. */
    inline size_t idx2x(size_t aIdx) { return (aIdx % mHeight); }
    /** Convert a position to a y-coord. */
    inline size_t idx2y(size_t aIdx) { return (aIdx / mHeight); }

private:
    uint16_t mWidth;
    uint16_t mHeight;

    Cell* mCells;
    std::vector<Passage*> mPassages;
};

#endif // _FAITH_EMULATOR_MAP_DATA_H_

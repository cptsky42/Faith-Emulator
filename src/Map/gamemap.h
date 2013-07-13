/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_GAMEMAP_H_
#define _FAITH_EMULATOR_GAMEMAP_H_

#include "common.h"
#include "mapbase.h"
#include "mapdata.h"

class Client;

class GameMap
{
    friend class MapManager;

public:
    enum Flags
    {
        TYPE_NORMAL             = 0x0000,
        TYPE_PK_FIELD           = 0x0001,
        TYPE_CHGMAP_DISABLE     = 0x0002, // magic call team member
        TYPE_RECORD_DISABLE     = 0x0004,
        TYPE_PK_DISABLE         = 0x0008,
        TYPE_BOOTH_ENABLE       = 0x0010,
        TYPE_TEAM_DISABLE       = 0x0020,
        TYPE_TELEPORT_DISABLE	= 0x0040, // chgmap by action
        TYPE_SYN_MAP            = 0x0080,
        TYPE_PRISON_MAP         = 0x0100,
        TYPE_WING_DISABLE       = 0x0200, // bowman fly disable
        TYPE_FAMILY             = 0x0400,
        TYPE_MINE_FIELD         = 0x0800,
        TYPE_PK_GAME            = 0x1000
    };

public:
    struct Info
    {
    public:
        uint16_t DocID;
        uint32_t Type;
        int32_t OwnerUID;
        uint16_t PortalX;
        uint16_t PortalY;
        int32_t RebornMap;
        int32_t RebornPortal;
        uint32_t Color;
    };

public:
    static const int32_t PRISON_MAP_UID = 10000; // TODO
    static const int32_t NEWBIE_MAP_UID = 10001; // TODO
    static const int32_t DYNAMIC_MAP_UID = 1000000;

public:
    ~GameMap();

public:
    int32_t getUID() const { return mUID; }
    int32_t getOwnerUID() const { return mInfo->OwnerUID; }
    uint16_t getWidth() const { ASSERT(&mData != nullptr); return mData.getWidth(); }
    uint16_t getHeight() const { ASSERT(&mData != nullptr); return mData.getHeight(); }

    bool getFloorAccess(uint16_t aPosX, uint16_t aPosY) const;
    bool getFloorAlt(uint16_t aPosX, uint16_t aPosY) const;
    //	int		GetWidthOfBlock()				{ return (m_pMapData->GetMapWidth()-1) / CELLS_PER_BLOCK + 1; }
    //	int		GetHeightOfBlock()				{ return (m_pMapData->GetMapHeight()-1) / CELLS_PER_BLOCK + 1; }

    //	int		GetResLev()						{ return m_pData->GetInt(GAMEMAPDATA_RESOURCE_LEV); }
    //	OBJID	GetSynID()						{ if(GetOwnerType() == OWNER_SYN) return GetOwnerID(); return ID_NONE; }
    //	DWORD	GetStatus()						{ return m_nStatus; }
    //	DWORD	GetType()						{ return m_pData->GetInt(GAMEMAPDATA_TYPE); }
    //	POINT	GetPortal()						{ POINT pos; pos.x=m_pData->GetInt(GAMEMAPDATA_PORTAL0_X); pos.y=m_pData->GetInt(GAMEMAPDATA_PORTAL0_Y); return pos;}
    //	OBJID	GetDocID()						{ return m_pData->GetInt(GAMEMAPDATA_MAPDOC); }

public:
    bool isLayItemEnable(uint16_t aPosX, uint16_t aPosY) const { return getFloorAccess(aPosX, aPosY); }
    bool isValidPoint(uint16_t aPosX, uint16_t aPosY) const { return (aPosX < getWidth() && aPosY < getHeight()); }
    bool isNewbieMap() const { return NEWBIE_MAP_UID == mUID; }
    bool isDynaMap() const { return mUID >= DYNAMIC_MAP_UID; }
    bool isPkField() const { return (mInfo->Type & TYPE_PK_FIELD) != 0; }
    bool isChgMapDisabled() const { return (mInfo->Type & TYPE_CHGMAP_DISABLE) != 0; }
    bool isRecordDisabled() const { return (mInfo->Type & TYPE_RECORD_DISABLE) != 0; }
    //	bool	IsPkDisable(void)				{ return ((m_pData->GetInt(GAMEMAPDATA_TYPE)&MAPTYPE_PK_DISABLE) != 0); }
    //	bool	IsWarTime()						{ return (GetStatus() & STATUS_WAR) != 0; }
    //	bool	IsTeamDisable()					{ return (m_pData->GetInt(GAMEMAPDATA_TYPE)&MAPTYPE_TEAM_DISABLE) != 0; }
    //	bool	IsTeleportDisable()				{ return (m_pData->GetInt(GAMEMAPDATA_TYPE)&MAPTYPE_TELEPORT_DISABLE) != 0; }
    //	bool	IsSynMap()						{ return (m_pData->GetInt(GAMEMAPDATA_TYPE)&MAPTYPE_SYN_MAP) != 0; }
    //	bool	IsPrisonMap()					{ return (m_pData->GetInt(GAMEMAPDATA_TYPE)&MAPTYPE_PRISON_MAP) != 0; }
    //	bool	IsTrainMap()					{ return GetID() == 1039; }
    //	bool	IsWingEnable()					{ return (m_pData->GetInt(GAMEMAPDATA_TYPE)&MAPTYPE_WING_DISABLE) == 0; }
    //	bool	IsMineField()					{ return (m_pData->GetInt(GAMEMAPDATA_TYPE)&MAPTYPE_MINEFIELD) != 0; }
    //	bool	IsPkGameMap()					{ return (m_pData->GetInt(GAMEMAPDATA_TYPE)&MAPTYPE_PKGAME) != 0; }
    //	bool	IsFamilyMap()					{ return (m_pData->GetInt(GAMEMAPDATA_TYPE)&MAPTYPE_FAMILY) != 0; }
    //	bool	IsNeverWoundMap()				{ return (m_pData->GetInt(GAMEMAPDATA_TYPE)&MAPTYPE_NEVERWOUND) != 0;}
    //	bool	IsDeadIsland()					{ return (m_pData->GetInt(GAMEMAPDATA_TYPE)&MAPTYPE_DEADISLAND) != 0;}
    //	bool	IsBoothEnable()					{ return (m_pData->GetInt(GAMEMAPDATA_TYPE)&MAPTYPE_BOOTH_ENABLE) != 0;}


public:
//	int		Distance(int x1, int y1, int x2, int y2)	{ return __max(abs(x1-x2), abs(y1-y2)); }
    void sendMapInfo(Client* aClient) const;

private:
    GameMap(int32_t aUID, Info** aInfo, MapData& aData);

private:
    const int32_t mUID;
    Info* mInfo;
    const MapData& mData;
};

#endif // _FAITH_EMULATOR_GAMEMAP_H_

//class CGameMap : public CGameObj
//{
//	bool	Create(PROCESS_ID idProcess, IRecordset* pRes);
//	OBJID	CreateDynaMap(PROCESS_ID idProcess, const NewMapInfo* pInfo);
//	void	OnTimer(DWORD tCurr);
//	bool	QueryObjInPos(int nPosX, int nPosY, OBJID idObjType, void** ppObj);
//	bool	QueryObj(int nCenterX, int nCenterY, OBJID idObjType, OBJID idObj, void** ppObj);
//	IRole*	QueryRole(int nCenterX, int nCenterY, OBJID idObj);
//	IRole*	QueryRoleByPos(int nPosX, int nPosY);
////	IMapData*	QueryMapData()							{ CHECKF(m_pMapData); return m_pMapData; }
//	CWeatherRegion*	QueryWeatherRegion(OBJID id)		{ CHECKF(m_setWeather && id != ID_NONE); return m_setWeather->GetObj(id);}

//public: // block
//	CGameBlock&	QueryBlock(int nPosX, int nPosY)		{ return m_setBlock[Block(nPosX)][Block(nPosY)]; }
//	IMapThing*	QueryThingByIndex(int x, int y, int z)	{ return BlockByIndex(x,y).QuerySet()->GetObjByIndex(z); }
//	CGameBlock&	BlockByIndex(int x, int y)				{ return m_setBlock[x][y]; }		// call by FOR_9_xxx
//protected:
//	IRegionSet*	QueryRegionSet()						{ CHECKF(m_setRegion); return m_setRegion; }

//public: // block info
//	virtual void	SendBlockInfo(IRole* pRole);		// ²»°üº¬×Ô¼º
//	virtual void	BroadcastBlockMsg(IMapThing* pThing, CNetMsg* pMsg, bool bSendSelf = false);
//	virtual void	BroadcastBlockMsg(int nPosX, int nPosY, CNetMsg* pMsg);

//public: // role
//	void	EnterRoom(IMapThing* pThing, BOOL bWithBlock=false);
//	void	LeaveRoom(IMapThing* pThing, BOOL bWithBlock=false);
//	void	MoveTo(IRole* pRole, int nNewPosX, int nNewPosY, BOOL bLeaveBlock=false, BOOL bEnterBlock=false);		// ÓÐ¿ÉÄÜÒÆ¶¯µ½ÏàÁÚµÄBLOCK
//	void	IncRole(int x, int y)		{ m_pMapData->IncRole(x, y); }
//	void	DecRole(int x, int y)		{ m_pMapData->DecRole(x, y); }		// normal use LeaveRoom or MoveTo but dead

//public: // region info
//	void	SendRegionInfo(CUser* pUser);
//	void	ClearRegionInfo(CUser* pUser);
//	void	ChangeRegion(CUser* pUser, int nNewPosX, int nNewPosY);

//public: // region -----------------------------
//	CRegionData*	QueryRegion(int nRegionType, int x, int y);
//	bool	IsInRegionType(int nRegionType, int x, int y);
//	static bool	IsInRegion(CRegionData* pData, OBJID idMap, int x, int y);
//	bool	BroadcastDance(CUser* pUser, OBJID idEmotion);

//public: // light ------------------
//	DWORD	GetLight()						{ return m_dwLightRGB; }
//	void	SetLight(DWORD dwRGB)			{ m_dwLightRGB = dwRGB; }
//protected:
//	DWORD	m_dwLightRGB;


//public: // const
//	bool	IsStandEnable(int nPosX, int nPosY);
//	bool	IsMoveEnable(int x, int y);
//	bool	IsMoveEnable(int xSour, int ySour, int x, int y, int nClimbCap);
//	bool	IsAltEnable(const POINT& posSour, const POINT& pos, int nAltDiff);
//	bool	IsAltOver(const POINT& pos, int nAlt);

//public: // application
//	void	CollectMapThing(MAPTHING_SET& psetMapThing, const POINT pos, int nRange, OBJID idObjTypeUnion);	// idObjTypeUnion Ö§³Ö¶àÀàÐÍ¶ÔÏó
//	bool	FindDropItemCell(int nRange, POINT* pos);			// pos: in/out
//	bool	GetPassageMap(OBJID* pidMap, POINT* pposTarget, const POINT& pos);
//	bool	GetRebornMap(OBJID* pidMap, POINT* pposTarget);
//	bool	SetStatus(int nStatus, bool flag);				// return false: no change
//	void	SetSynID(OBJID idSyn, bool bWithAllNpc);				// true: set all syna npc syn id, yet.
//	void	SetUserID(OBJID idUser, bool bWithAllNpc);				// true: set all syna npc syn id, yet.
//	bool	ChangeMapDoc(OBJID idDoc);						// false: user in map, can't change
//	bool	EraseMap();
//	void	SetResLev(int nData, bool bUpdate)			{ m_pData->SetInt(GAMEMAPDATA_RESOURCE_LEV, nData); if(bUpdate) m_pData->Update(); }
//	void	SetPortal0X(int nData, bool bUpdate)		{ m_pData->SetInt(GAMEMAPDATA_PORTAL0_X, nData); if(bUpdate) m_pData->Update(); }
//	void	SetPortal0Y(int nData, bool bUpdate)		{ m_pData->SetInt(GAMEMAPDATA_PORTAL0_Y, nData); if(bUpdate) m_pData->Update(); }
//	bool	AddTerrainObj(OBJID idOwner, int x, int y, OBJID idTerrainObj);
//	bool	DelTerrainObj(OBJID idOwner);

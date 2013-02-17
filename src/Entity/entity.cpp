#include "entity.h"

Entity :: Entity(int32_t aUniqId)
    : mUniqId(aUniqId)
{
    mLook = 0;
    mMapId = 0;
    mPosX = 0;
    mPosY = 0;
    mDirection = 0;
}

Entity :: ~Entity()
{

}

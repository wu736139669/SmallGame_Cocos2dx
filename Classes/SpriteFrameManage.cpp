

/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		
*  创建时间：	
*
***************************************************************/
#include "ccMacros.h"
#include <vector>
#include "SpriteFrameManage.h"

using namespace std;

NS_CC_BEGIN

static CCSpriteFrameManage *s_pSpriteFrameManage = NULL;

CCSpriteFrameManage* CCSpriteFrameManage::getInstance(void)
{
    if (!s_pSpriteFrameManage)
    {
        s_pSpriteFrameManage = new CCSpriteFrameManage();
        s_pSpriteFrameManage->init();
    }

    return s_pSpriteFrameManage;
}

void CCSpriteFrameManage::purge(void)
{
    CC_SAFE_RELEASE_NULL(s_pSpriteFrameManage);
}

bool CCSpriteFrameManage::init(void)
{
    mpSpriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    return true;
}

CCSpriteFrameManage::~CCSpriteFrameManage(void)
{

}

void CCSpriteFrameManage::addSpriteFramesWithFile(const char *pszPlist, CCTexture2D *pobTexture)
{
	 CCAssert(mpSpriteFrameCache, "mpSpriteFrameCache should not be null");
    mpSpriteFrameCache->addSpriteFramesWithFile(pszPlist,pobTexture);
}

void CCSpriteFrameManage::addSpriteFramesWithFile(const char* plist, const char* textureFileName)
{
    CCAssert(mpSpriteFrameCache, "mpSpriteFrameCache should not be null");
  mpSpriteFrameCache->addSpriteFramesWithFile(plist,textureFileName);
}

void CCSpriteFrameManage::addSpriteFramesWithFile(const char *pszPlist)
{
	 CCAssert(mpSpriteFrameCache, "mpSpriteFrameCache should not be null");
    mpSpriteFrameCache->addSpriteFramesWithFile(pszPlist);
}

void CCSpriteFrameManage::addSpriteFrame(CCSpriteFrame *pobFrame, const char *pszFrameName)
{
	 CCAssert(mpSpriteFrameCache, "mpSpriteFrameCache should not be null");
    mpSpriteFrameCache->addSpriteFrame(pobFrame,pszFrameName);
}

void CCSpriteFrameManage::removeSpriteFrames(void)
{
	 CCAssert(mpSpriteFrameCache, "mpSpriteFrameCache should not be null");
    mpSpriteFrameCache->removeSpriteFrames();
}

void CCSpriteFrameManage::removeUnusedSpriteFrames(void)
{
	 CCAssert(mpSpriteFrameCache, "mpSpriteFrameCache should not be null");
     mpSpriteFrameCache->removeUnusedSpriteFrames();
}

void CCSpriteFrameManage::removeSpriteFrameByName(const char *pszName)
{
	 CCAssert(mpSpriteFrameCache, "mpSpriteFrameCache should not be null");
    mpSpriteFrameCache->removeSpriteFrameByName(pszName);
}

void CCSpriteFrameManage::removeSpriteFramesFromFile(const char* plist)
{
	 CCAssert(mpSpriteFrameCache, "mpSpriteFrameCache should not be null");
   mpSpriteFrameCache->removeSpriteFramesFromFile(plist);
}

void CCSpriteFrameManage::removeSpriteFramesFromTexture(CCTexture2D* texture)
{
	 CCAssert(mpSpriteFrameCache, "mpSpriteFrameCache should not be null");
     mpSpriteFrameCache->removeSpriteFramesFromTexture(texture);
}

CCSpriteFrame* CCSpriteFrameManage::spriteFrameByName(const char *pszName)
{
	 CCAssert(mpSpriteFrameCache, "mpSpriteFrameCache should not be null");
     return mpSpriteFrameCache->spriteFrameByName(pszName);
}

NS_CC_END

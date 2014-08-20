//
//  GameShare_Texture.cpp
//  OnceAgain
//
//  Created by xiaohai on 14-2-24.
//
//

#include "GameShare_Texture.h"

static GameShare_Texture *s_ShareTextManager = NULL;
static GameShare_FrameCache * s_ShareFrameCacheManager = NULL;


GameShare_Texture* GameShare_Texture::sharedTexture(void)
{
    if (!s_ShareTextManager)
    {
        s_ShareTextManager = new GameShare_Texture();
        s_ShareTextManager->init();
    }
    return s_ShareTextManager;
}


bool GameShare_Texture::init()
{
    if(!CCNode::init())
    {
        return false;
    }
    
//    //加载所有的图片
//    CCTextureCache::sharedTextureCache()->addImage(akooakoo_image);
//    CCTextureCache::sharedTextureCache()->addImage(akooboard1_image);
//    CCTextureCache::sharedTextureCache()->addImage(akoocard_image);
//    CCTextureCache::sharedTextureCache()->addImage(akoomenu_image);
//    CCTextureCache::sharedTextureCache()->addImage(akoopang_image);
//    CCTextureCache::sharedTextureCache()->addImage(akooeffect_image);
//    CCTextureCache::sharedTextureCache()->addImage(akoobox1_image);
//    CCTextureCache::sharedTextureCache()->addImage(pause_image);
    
    return true;
}

//获得纹理 没找到 返回NULL
CCTexture2D* GameShare_Texture::GetTextureByKey(const char* rpFileName)
{
    if(rpFileName == NULL) return NULL;
    
    CCTexture2D* pTexture2D = CCTextureCache::sharedTextureCache()->addImage(rpFileName);
    return pTexture2D;
}

CCSprite* GameShare_Texture::GetSpriteByCCRect(const char* rpFileName, CCRect rRect)
{
    if(rpFileName == NULL) return NULL;
    
    CCTexture2D* pTexture2D = GetTextureByKey(rpFileName);
    if(pTexture2D == NULL) return NULL;
    
    CCSprite* pSprite = NULL;
    if(rRect.equals(CCRectMake(0, 0, 0, 0)))
        pSprite = CCSprite::createWithTexture(pTexture2D);
    else
        pSprite = CCSprite::createWithTexture(pTexture2D, rRect);
    return pSprite;
}

CCSpriteFrame*  GameShare_Texture::GetSpriteFrameByCCRect(const char* rpFileName, CCRect rRect)
{
    if(rpFileName == NULL) return NULL;
    
    CCTexture2D* pTexture2D = GetTextureByKey(rpFileName);
    if(pTexture2D == NULL) return NULL;
    
    CCSpriteFrame* pSpriteFrame = NULL;
    pSpriteFrame = CCSpriteFrame::createWithTexture(pTexture2D, rRect);
    return pSpriteFrame;
}




/*
 *          GameShare_FrameCache
 */

bool GameShare_FrameCache::init()
{
    if(!CCNode::init())
    {
        return false;
    }
    return true;
}

GameShare_FrameCache* GameShare_FrameCache::sharedFrameCache()
{
    if (!s_ShareFrameCacheManager)
    {
        s_ShareFrameCacheManager = new GameShare_FrameCache();
        s_ShareFrameCacheManager->init();
    }
    return s_ShareFrameCacheManager;
}

void GameShare_FrameCache::AddFrameCacheWithFile(const char* plist, const char* textureFileName)
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist, textureFileName);
}


CCSprite* GameShare_FrameCache::GetSpriteByFrameName(const char* rpFrameName)
{
    if(rpFrameName == NULL) return NULL;
    
    
    return CCSprite::createWithSpriteFrameName(rpFrameName);
}








//
//  GameShare_Texture.h
//  OnceAgain
//
//  Created by xiaohai on 14-2-24.
//
//

#ifndef OnceAgain_GameShare_Texture_h
#define OnceAgain_GameShare_Texture_h

#include "cocos2d.h"
USING_NS_CC;

// all image define
#define akooakoo_image                  "akooakoo_image.png"
#define akooboard1_image                "akooboard1_image.png"
#define akoocard_image                  "akoocard_image.png"
#define akoomenu_image                  "akoomenu_image.png"
#define akoopang_image                  "akoopang_image.png"
#define akooline_image                  "akooline_image.png"
#define akooeffect_image                "akooeffect_image.png"
#define akoobox1_image                  "akoobox1_image.png"
#define pause_image                     "pause.png"

/*
 *          GameShare_Texture
 */
class GameShare_Texture : public CCNode
{
public:
    virtual bool init();
public:
    static GameShare_Texture* sharedTexture(void);
    
    // to Get Texture By name
    CCTexture2D*    GetTextureByKey(const char* rpFileName);
    
    //create sprite with CCRect
    CCSprite*       GetSpriteByCCRect(const char* rpFileName, CCRect rRect);
    
    //Create SpriteFrame with CCRect
    CCSpriteFrame*  GetSpriteFrameByCCRect(const char* rpFileName, CCRect rRect);
};

/*
 *          GameShare_FrameCache
 */
class GameShare_FrameCache : public CCNode
{
public:
    virtual bool init();
public:
    static GameShare_FrameCache* sharedFrameCache(void);
    
    void AddFrameCacheWithFile(const char* plist, const char* textureFileName);
    
    CCSprite* GetSpriteByFrameName(const char* rpFrameName);
};
#endif

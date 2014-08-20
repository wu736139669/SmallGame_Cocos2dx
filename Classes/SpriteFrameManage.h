
/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		
*  创建时间：	
*
***************************************************************/
#ifndef __SPRITE_CCSPRITE_FRAME_MANAGE_H__
#define __SPRITE_CCSPRITE_FRAME_MANAGE_H__

#include <set>
#include <string>
#include "cocos2d.h"

NS_CC_BEGIN

class CCDictionary;
class CCArray;
class CCSprite;
class CCSpriteFrameCache;
class CCTexture2D;
class CCSpriteFrame;
class CCSpriteFrameManage : public CCObject
{
	CCSpriteFrameCache *mpSpriteFrameCache;
protected:
   
    CCSpriteFrameManage(void) {}
public:
    bool init(void);
    /**
     * @js NA
     * @lua NA
     */
    ~CCSpriteFrameManage(void);
public:
    /** Adds multiple Sprite Frames from a plist file.
     * A texture will be loaded automatically. The texture name will composed by replacing the .plist suffix with .png
     * If you want to use another texture, you should use the addSpriteFramesWithFile:texture method.
     * @js addSpriteFrames
     */
    void addSpriteFramesWithFile(const char *pszPlist);

    /** Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames.
     @since v0.99.5
     @js addSpriteFrames
     */
    void addSpriteFramesWithFile(const char* plist, const char* textureFileName);

    /** Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames. 
     * @js addSpriteFrames
     */
    void addSpriteFramesWithFile(const char *pszPlist, CCTexture2D *pobTexture);

    /** Adds an sprite frame with a given name.
     If the name already exists, then the contents of the old name will be replaced with the new one.
     */
    void addSpriteFrame(CCSpriteFrame *pobFrame, const char *pszFrameName);

    /** Purges the dictionary of loaded sprite frames.
     * Call this method if you receive the "Memory Warning".
     * In the short term: it will free some resources preventing your app from being killed.
     * In the medium term: it will allocate more resources.
     * In the long term: it will be the same.
     */
    void removeSpriteFrames(void);

    /** Removes unused sprite frames.
     * Sprite Frames that have a retain count of 1 will be deleted.
     * It is convenient to call this method after when starting a new Scene.
     */
    void removeUnusedSpriteFrames(void);

    /** Deletes an sprite frame from the sprite frame cache. 
     *  @js getSpriteFrame
     */
    void removeSpriteFrameByName(const char *pszName);

    /** Removes multiple Sprite Frames from a plist file.
    * Sprite Frames stored in this file will be removed.
    * It is convenient to call this method when a specific texture needs to be removed.
    * @since v0.99.5
    */
    void removeSpriteFramesFromFile(const char* plist);

public:
    /** Removes all Sprite Frames associated with the specified textures.
    * It is convenient to call this method when a specific texture needs to be removed.
    * @since v0.995.
    */
    void removeSpriteFramesFromTexture(CCTexture2D* texture);

    /** Returns an Sprite Frame that was previously added.
     If the name is not found it will return nil.
     You should retain the returned copy if you are going to use it.
     @js getSpriteFrame
     */
    CCSpriteFrame* spriteFrameByName(const char *pszName);

public:
    /** Returns the shared instance of the Sprite Frame cache 
     *  @js getInstance
     */
    static CCSpriteFrameManage* getInstance(void);

    /** Purges the cache. It releases all the Sprite Frames and the retained instance. */
    static void purge(void);
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __SPRITE_CCSPRITE_FRAME_CACHE_H__

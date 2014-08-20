//
//  GameShare_Pause.h
//  OnceAgain
//
//  Created by mac on 14-3-4.
//
//

#ifndef __OnceAgain__GameShare_Pause__
#define __OnceAgain__GameShare_Pause__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "GameShare_Msg.h"
#include "GameShare_Texture.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameShare_Pause : public CCLayer
{
public:
    virtual bool init();
    
    GameShare_Pause(void){pauseLayer= NULL;};
    virtual ~GameShare_Pause();
    static cocos2d::CCScene* scene();
    static CCScene* scene(CCRenderTexture *spr,bool isFlip);
    CREATE_FUNC(GameShare_Pause);
    
    void continueGame(CCObject *object);
    void newGame(CCObject *object);
    void quitGame(CCObject *object);
    
    void setContinueCallbackFunc(CCObject* target, SEL_CallFuncO callfun);
    void setNewGameCallbackFunc(CCObject* target, SEL_CallFuncO callfun);
    void setQuitGameCallbackFunc(CCObject* target, SEL_CallFuncO callfun);
	void setHelpCallbackFunc(CCObject* target, SEL_CallFuncO callfun);
private:
//    CCObject*       m_pListener;
//    SEL_CallFuncO    m_pfnSelector;
    UILayer* pauseLayer;
    void setVisible(bool visible);
};
#endif /* defined(__OnceAgain__GameShare_Pause__) */

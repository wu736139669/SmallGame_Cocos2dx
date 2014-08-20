//
//  Scene_GameItem.cpp
//  OnceAgain
//
//  Created by mac on 14-3-21.
//
//

#include "Scene_GameItem.h"
#include "Gamelist.h"
#include "StringUtil.h"
#include "PlayerInfoManager.h"
#include "GameLayer_ItemStrong.h"
#include "GameInfoManager.h"
#include "StrengthenManager.h"
#include "RightTouchDefine.h"
#include "CsvStringData.h"
#include "GameLayer_Tag.h"
#include "NetPacket.h"
#include "MsgDefine.h"
#include "GameItemManager.h"
#include "DialogManager.h"
#include "FruitData.h"
#include "TimeUtil.h"
#include "TaikoDefine.h"
#include "DataManager.h"
#include "GameLayerGameRank.h"
#include "FriendManager.h"
#include "GameMedalLayer.h"
#include "InfoSysManager.h"
#include "GameLayerChallenge.h"
#include "SpriteFrameManage.h"
#include "PkSysManager.h"
#include "GameLayerPkBar.h"
#include "XQDate.h"
#include "JudgeMedalGet.h"
#include "NetCallBack.h"

IMPLEMENT_DLG_ID(Scene_GameItem,GameItem_Tag);

enum LayerTag{
    PkLayerTag = 10000,
	AniLayerTag = 10001
};
enum Item_Btn
{
    Btn_1 = 0,
    Btn_2    ,
    Btn_3    ,
    Btn_4
};
Scene_GameItem::Scene_GameItem()
{
    ul = NULL;
    lvImg1 = NULL;
    lvImg2 = NULL;
    lvImg3 = NULL;
    gameLayer_Strong = NULL;
    returnBtn = NULL;
    rankBtn = NULL;
    taskBtn = NULL;

}
enum EGameItemTag
{
	eGameItemTagBg = 20,
	eGameItemTagBgTop,
};
Scene_GameItem::~Scene_GameItem()
{
//    this->release();
//    CC_SAFE_RELEASE(layer);
    GUIReader::shareReader()->purgeGUIReader();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    ActionManager::shareManager()->purgeActionManager();
}
CCScene* Scene_GameItem::scene()
{
    // 'scene' auto release memory
    CCScene *scene = CCScene::create();
    // 'layer' auto release memory
    //  Scene_GameItem *layer = Scene_GameItem::create();
    auto layer = GetDlgPtr(Scene_GameItem);
    scene->addChild(layer);
    return scene;
}
void Scene_GameItem::onEnter()
{
    CCLayer::onEnter();
    this->initData();
    
    //隐藏pk界面
    this->setPkView(false);
	CCSprite* pSpriteBG = (CCSprite*)getChildByTag(eGameItemTagBg);
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//pSpriteBG->setPosition(ccp(visibleSize.width/2 , pSpriteBG->getContentSize().height/2 + origin.y));
	

	char str1[100]={0};
	switch(GameShare_Global::shareGlobal()->gameType)
	{
	case 1:
		sprintf(str1,"GameSceneBg1.json");
		break;
	case Game_Jelly:
		sprintf(str1,"GameSceneBg2.json");
		break;
	case Game_Fruit: 
		sprintf(str1,"GameSceneBg3.json");
		break;
	case Game_Link:
		sprintf(str1,"GameSceneBg4.json");
		break;
	case Game_TaiKo: 
		sprintf(str1,"GameSceneBg5.json");
		break;
	case Game_Cir:
		sprintf(str1,"GameSceneBg1.json");
		break;
	default:
		break;
	}

	UILayer* ul = UILayer::create();
	auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath(str1).c_str()));
	ul->addWidget(myLayout);
	this->addChild(ul, 0, 100);
	ul->setTouchEnabled(false);

	int nGameType = GameShare_Global::shareGlobal()->gameType;
	if (nGameType==1)
	{
		UIImageView* pHill = dynamic_cast<UIImageView*>(ul->getWidgetByName("san"));
		UIImageView* pHill2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("san2"));
		//CCActionInterval*  actionTo = CCScaleTo::create(2.0f, 0.5f);
		CCActionInterval*  actionBy = CCScaleBy::create(1.0f, 1.0f, 1.1f);
		CCActionInterval*  actionBy2 = CCScaleBy::create(1.0f, 1.1f, 1.0f);
		CCFiniteTimeAction* seq = CCSequence::create(actionBy, actionBy->reverse(),NULL);
		CCActionInterval * repeatForever =CCRepeatForever::create((CCActionInterval* )seq);
		CCFiniteTimeAction* seq1 = CCSequence::create(actionBy2, actionBy2->reverse(),NULL);
		CCActionInterval * repeatForever2 =CCRepeatForever::create((CCActionInterval* )seq1);
		pHill->runAction(repeatForever);
		pHill2->runAction(repeatForever2);
	}
	else if (nGameType==2)
	{
		UIImageView*  pCloud = dynamic_cast<UIImageView*>(ul->getWidgetByName("yun2"));
		UIImageView*  pCloud2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("yun3"));
		CCActionInterval*  actionBy = CCScaleBy::create(1.5f, 1.2f, 1.0f);
		CCActionInterval*  actionBy2 = CCScaleBy::create(1.5f, 1.2f, 1.0f);
		CCFiniteTimeAction* seq1 = CCSequence::create(actionBy, actionBy->reverse(),NULL);
		CCFiniteTimeAction* seq2 = CCSequence::create(actionBy2, actionBy2->reverse(),NULL);
		CCActionInterval * repeatForever1 =CCRepeatForever::create((CCActionInterval* )seq1);
		CCActionInterval * repeatForever2 =CCRepeatForever::create((CCActionInterval* )seq2);
		pCloud->runAction(repeatForever1);
		pCloud2->runAction(repeatForever2);
	}
	else if (nGameType==3)
	{
		UIImageView*  pSugar = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_15"));
		UIImageView*  pSugar1 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_20"));
		CCRotateBy* actionBy2 = CCRotateBy::create(1.5f, -25.0f, -25.0f);
		CCRotateBy* actionBy1 = CCRotateBy::create(1.5f, -25.0f, -25.0f);
		CCFiniteTimeAction* seq1 = CCSequence::create(actionBy2, actionBy2->reverse(), NULL);
		CCFiniteTimeAction* seq2 = CCSequence::create(actionBy1, actionBy1->reverse(), NULL);
		CCActionInterval * repeatForever1 =CCRepeatForever::create((CCActionInterval* )seq1);
		CCActionInterval * repeatForever2 =CCRepeatForever::create((CCActionInterval* )seq2);
		pSugar->runAction(repeatForever1);
		pSugar1->runAction(repeatForever2);

		//星星
		UIImageView*  pXx1 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_23"));
		UIImageView*  pXx2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_32"));
		UIImageView*  pXx3 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_35"));
		UIImageView*  pXx4 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_39"));

		CCActionInterval*  actionBy3 = CCScaleBy::create(1.2f, 1.3f, 1.3f);
		CCActionInterval*  actionBy4 = CCScaleBy::create(1.2f, 1.3f, 1.3f);
		CCActionInterval*  actionBy5 = CCScaleBy::create(1.2f, 1.3f, 1.3f);
		CCActionInterval*  actionBy6 = CCScaleBy::create(1.2f, 1.3f, 1.3f);
		
		CCFiniteTimeAction* seq3 = CCSequence::create(actionBy3, actionBy3->reverse(),NULL);
		CCFiniteTimeAction* seq4 = CCSequence::create(actionBy4, actionBy4->reverse(),NULL);
		CCFiniteTimeAction* seq5 = CCSequence::create(actionBy5, actionBy5->reverse(),NULL);
		CCFiniteTimeAction* seq6 = CCSequence::create(actionBy6, actionBy6->reverse(),NULL);
		
		CCActionInterval * repeatForever3 =CCRepeatForever::create((CCActionInterval* )seq3);
		CCActionInterval * repeatForever4 =CCRepeatForever::create((CCActionInterval* )seq4);
		CCActionInterval * repeatForever5 =CCRepeatForever::create((CCActionInterval* )seq5);
		CCActionInterval * repeatForever6 =CCRepeatForever::create((CCActionInterval* )seq6);
		//pCloud->runAction(repeatForever1);
		pXx1->runAction(repeatForever3);
		pXx2->runAction(repeatForever4);
		pXx3->runAction(repeatForever5);
		pXx4->runAction(repeatForever6);
	}
	else if (nGameType==4)
	{
		UIImageView* pTree = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_8"));
		UIImageView* pTree1 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_13"));
		//CCActionInterval*  actionTo = CCScaleTo::create(2.0f, 0.5f);
		CCActionInterval*  actionBy = CCScaleBy::create(1.0f, 1.0f, 1.1f);
		CCActionInterval*  actionBy2 = CCScaleBy::create(1.0f, 1.0f, 1.1f);
		CCFiniteTimeAction* seq = CCSequence::create(actionBy, actionBy->reverse(),NULL);
		CCActionInterval * repeatForever =CCRepeatForever::create((CCActionInterval* )seq);
		CCFiniteTimeAction* seq1 = CCSequence::create(actionBy2, actionBy2->reverse(),NULL);
		CCActionInterval * repeatForever2 =CCRepeatForever::create((CCActionInterval* )seq1);
		pTree->runAction(repeatForever);
		pTree1->runAction(repeatForever2);
	}
	else if (nGameType ==5)
	{
		UIImageView* pXx1 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_38"));
		UIImageView* pXx2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_41"));
		CCActionInterval*  actionBy = CCScaleBy::create(1.0f, 0.5f, 0.5f);
		CCActionInterval*  actionBy2 = CCScaleBy::create(1.0f, 0.5f, 0.5f);
		CCFiniteTimeAction* seq = CCSequence::create(actionBy, actionBy->reverse(),NULL);
		CCActionInterval * repeatForever =CCRepeatForever::create((CCActionInterval* )seq);
		CCFiniteTimeAction* seq1 = CCSequence::create(actionBy2, actionBy2->reverse(),NULL);
		CCActionInterval * repeatForever2 =CCRepeatForever::create((CCActionInterval* )seq1);
		pXx1->runAction(repeatForever);
		pXx2->runAction(repeatForever2);

		UIImageView* pUFO1 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_15"));
		UIImageView* pUFO2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("Image_21"));
		CCMoveBy* act1 = CCMoveBy::create(2.0, ccp(0, -25));
		CCMoveBy* act2 = CCMoveBy::create(1.0, ccp(0, 25));
		CCFiniteTimeAction* seq3 = CCSequence::create(act1, act1->reverse(),NULL);
		CCFiniteTimeAction* seq4 = CCSequence::create(act2, act2->reverse(),NULL);
		CCActionInterval * repeatForever3 =CCRepeatForever::create((CCActionInterval* )seq3);
		CCActionInterval * repeatForever4 =CCRepeatForever::create((CCActionInterval* )seq4);
		pUFO1->runAction(repeatForever3);
		pUFO2->runAction(repeatForever4);
	}

	if(nGameType ==2||nGameType ==3||nGameType ==4)
	{
		UIImageView* pMg1 = dynamic_cast<UIImageView*>(ul->getWidgetByName("mg1"));
		UIImageView* pMg2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("mg2"));
		UIImageView* pMg3 = dynamic_cast<UIImageView*>(ul->getWidgetByName("mg3"));
		CCActionInterval*  actionBy10 = CCScaleBy::create(1.0f, 1.0f, 1.3f);
		CCActionInterval*  actionBy11 = CCScaleBy::create(1.0f, 1.0f, 1.3f);
		CCActionInterval * actionBy12 = CCSkewTo::create(1, 8, 8);
		CCActionInterval * actionBy13 = CCSkewTo::create(1, 0, 0);
		CCActionInterval * actionBy14 = CCSkewTo::create(1, -8, -8);
		CCFiniteTimeAction* seq10 = CCSequence::create(actionBy10, actionBy10->reverse(),NULL);
		CCActionInterval * repeatForever10 =CCRepeatForever::create((CCActionInterval* )seq10);
		CCFiniteTimeAction* seq11 = CCSequence::create(actionBy11, actionBy11->reverse(),NULL);
		CCActionInterval * repeatForever11 =CCRepeatForever::create((CCActionInterval* )seq11);
		CCFiniteTimeAction* seq12 = CCSequence::create(actionBy12, actionBy13,actionBy14,NULL);
		CCActionInterval * repeatForever12 =CCRepeatForever::create((CCActionInterval* )seq12);

		pMg1->runAction(repeatForever10);
		pMg2->runAction(repeatForever11);
		pMg3->runAction(repeatForever12);
	}
    //
	CCSprite* pAniSp = (CCSprite*)getChildByTag(AniLayerTag);
	pAniSp->stopAllActions();
	CCAnimation* pAni1 = CCAnimation::create();
	CCString str;
	for (int i = 1; i <= 4; ++i){
		str.initWithFormat("role/pig_tl/%d.png",i);
		pAni1->addSpriteFrameWithFileName(str.getCString());
	}
	pAni1->setDelayPerUnit(0.15f);
	pAni1->setLoops(1);

	CCActionInterval* pSeq = CCSequence::create(CCFlipX::create(false),CCAnimate::create(pAni1),CCFlipX::create(true),CCAnimate::create(pAni1),NULL);
	pAniSp->runAction(CCRepeatForever::create(pSeq));

	pAniSp->setPosition(ccp(visibleSize.width/2 + 20,visibleSize.height - pAniSp->getContentSize().height/2 - 93 + 19 -26));

	
}
void Scene_GameItem::onEnterTransitionDidFinish()
{
	GameLayer_Base::onEnterTransitionDidFinish();
	//JudgeMedalGet::isMedalInfoHave(GameShare_Global::shareGlobal()->gameType, this, coco_myevent(Scene_GameItem::MedalInfoBack));
    CTaskMan::sharedInstance().requestDayTasklst();
}
void Scene_GameItem::MedalInfoBack(CCObject* p)
{
	CCLOG("medalinfoget");
}
void Scene_GameItem::initData()
{
    needGold = 0;
    //设置饭
    UILabel* riceNumLabel = dynamic_cast<UILabel*>(ul->getWidgetByName("RiceNum"));
	int i = CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower;
	if(i>=5)
	{
		riceNumLabel->setText("MAX");
		riceNumLabel->setScale(0.8f);
	}else{
		CCString riceNum;
		riceNum.initWithFormat("%d",CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower);
		riceNumLabel->setText(riceNum.getCString());
	}
    
    //装备等级.
    this->setLvNum();
    //重置道具.
    for (int i=0; i<4; i++) {
        CCString imgStr;
        imgStr.initWithFormat("IsSelectImg_%d",i+1);
        UIImageView* img = dynamic_cast<UIImageView*>(ul->getWidgetByName(imgStr.getCString()));
        img->setVisible(false);
        imgStr.initWithFormat("ItemBtn%d",i+1);
        UIButton* btn =  dynamic_cast<UIButton*>(ul->getWidgetByName(imgStr.getCString()));
        btn->setTextures("./CocoStudioResources/ItemNoSelect.png", "./CocoStudioResources/ItemNoSelect.png", "");
    }
    //获取游戏的道具信息
    sGameInfoData* gameData = CGameInfoMan::sharedInstance().getChgTempData(GameShare_Global::shareGlobal()->gameType);
    
    //通过游戏的道具信息获取道具价钱.
    if (gameData) {
        //上面的强化的图片.
        for (int i=0; i<gameData->strengthenId.size(); ++i) {
            //获取玩家的这款游戏的强化信息.
            sMGameStrengthen mStrength;
            if (int tempResult = CPlayerInfoMan::sharedInstance().getMStrengthenByGameTag(GameShare_Global::shareGlobal()->gameType, i,mStrength)) {
                CCString imgStr;
                CCString imgStr_1;
                imgStr.initWithFormat("EquipImg%d",i+1);
                UIImageView* img = dynamic_cast<UIImageView*>(ul->getWidgetByName(imgStr.getCString()));
                
                imgStr_1.initWithFormat("./CocoStudioResources/GameStrengthen/%d_x.png",mStrength.strengthenImg);
                img->setVisible(false);
                //装备按钮.
                imgStr.initWithFormat("EquipBtn%d",i+1);
                UIButton* equipBtn1 = dynamic_cast<UIButton*>(ul->getWidgetByName(imgStr.getCString()));
              
                imgStr.initWithFormat("./CocoStudioResources/GameStrengthen/%d_x.png",mStrength.strengthenImg);
                equipBtn1 -> setTextures(imgStr.getCString(), imgStr_1.getCString(), imgStr.getCString());
                
                  //锁
                imgStr.initWithFormat("EquipLock%d",i+1);
                UIImageView* lock = dynamic_cast<UIImageView*>(ul->getWidgetByName(imgStr.getCString()));
                if (mStrength.strengthenlv == 0) {
//                    ccColor3B color = {128,128,128};
//                    equipBtn1->setColor(color);
//                    lock->setVisible(true);
                }else
                {
                    ccColor3B color = {255,255,255};
                    equipBtn1->setColor(color);
                    lock->setVisible(false);
                }
                equipBtn1->setTag(i);
                //设置装备按钮的点击事件
                equipBtn1->addReleaseEvent(this, coco_releaseselector(Scene_GameItem::equipSuperCallBack));
                //设置装备按钮无法点击
//                if (tempResult == 2) {
//                    equipBtn1->addReleaseEvent(NULL, NULL);
//                    
//                }else{
//                    equipBtn1->addReleaseEvent(this, coco_releaseselector(Scene_GameItem::equipSuperCallBack));
//                }
                
            }
            
        }
        for (int i=0; i<gameData->itemId.size(); ++i) {
            //初始化是否被选择
            
            CCString imgStr;
            imgStr.initWithFormat("IsSelectImg_%d",i+1);
            UIImageView* img = dynamic_cast<UIImageView*>(ul->getWidgetByName(imgStr.getCString()));
            img->setVisible(false);
            imgStr.initWithFormat("ItemBtn%d",i+1);
            UIButton* btn =  dynamic_cast<UIButton*>(ul->getWidgetByName(imgStr.getCString()));
            btn->setTextures("./CocoStudioResources/ItemNoSelect.png", "./CocoStudioResources/ItemNoSelect.png", "");
            //初始化显示图片.
            imgStr.initWithFormat("ItemImg%d",i+1);
            UIImageView* showImg = dynamic_cast<UIImageView*>(ul->getWidgetByName(imgStr.getCString()));
        
            sItemData* itemData = CGameInfoMan::sharedInstance().getItemDate(GameShare_Global::shareGlobal()->gameType, i);
            
            if (itemData) {
                CCString imgStr;
                //设置图片
                imgStr.initWithFormat("./CocoStudioResources/GameItem/%d.png",itemData->ItemImg);
                showImg->setTexture(imgStr.getCString());

				imgStr.initWithFormat("ItemBtn_Img_%d",i+1);
				UIWidget* pImgGold = ul->getWidgetByName(imgStr.getCString());
				//设置金币.
				imgStr.initWithFormat("ItemBtn_Label_%d",i+1);
				UILabel* label = dynamic_cast<UILabel*>(ul->getWidgetByName(imgStr.getCString()));
				CCString valueStr;

				pImgGold->setVisible(true);
				SClientItemData* pItem = CItemMan::sharedInstance().getItem(itemData->ItemId);
				if (pItem&&pItem->fNum > 0)
				{
					pImgGold->setVisible(false);
					valueStr.initWithFormat("%d",(int)pItem->fNum);
				}else
				{
					valueStr.initWithFormat("%d",itemData->CurrencyValue);
				}
                label->setText(valueStr.getCString());
            }
        }
    }
    
    
    
    //下面的提示信息.
    UILabel* itemInfo = dynamic_cast<UILabel*>(ul->getWidgetByName("Label_591"));
    itemInfo->setText(GET_STRING_CSV(1010000024));
    
    
}

bool Scene_GameItem::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
   
    //background
   // CCSprite* pSpriteBG = CCSprite::createWithSpriteFrameName("bg.png");
   // pSpriteBG->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    pSpriteBG->setColor(ccGRAY);
	// by wsp
// 	CCSprite* pSpriteBG = CCSprite::createWithSpriteFrameName("GameSceneBg/GameBg.png");
// 	pSpriteBG->setAnchorPoint(ccp(0.f,0.f));
	CCScale9Sprite* pSpriteBG = CCScale9Sprite::create("./CocoStudioResources/GameSceneBg/GameBg.png");
	pSpriteBG->setAnchorPoint(ccp(0.f,0.f));
	pSpriteBG->setContentSize(CCSizeMake(visibleSize.width,visibleSize.height));
	this->addChild(pSpriteBG, 0);
	pSpriteBG->setTag(eGameItemTagBg);
	CCSprite* pSpriteBGTop = CCSprite::create();
	pSpriteBGTop->setTag(eGameItemTagBgTop);
	this->addChild(pSpriteBGTop, 0);
	
    ul = UILayer::create();
    auto myLayout = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(CStringUtil::convertToUIResPath("Item.json").c_str()));
    ul->addWidget(myLayout);
    ul->setContentSize(visibleSize);
    this->addChild(ul, 1, 100);
    
    //返回按钮.
    returnBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("Return"));
    returnBtn->setPressedActionEnabled(true);
    returnBtn->addReleaseEvent(this, coco_releaseselector(Scene_GameItem::returnBtnCallBack));
    
    //开始游戏按钮.
    UIButton* startGameBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("StartGame"));
//    startGameBtn->setPressedActionEnabled(true);
    startGameBtn->addReleaseEvent(this, coco_releaseselector(Scene_GameItem::startGameCallBack));
    

    //道具按钮.
    UIButton* itemBtn1 = dynamic_cast<UIButton*>(ul->getWidgetByName("ItemBtn1"));
    itemBtn1->setTag(Btn_1);
    itemBtn1->addReleaseEvent(this, coco_releaseselector(Scene_GameItem::itemBtnCallBack));
    
    UIButton* itemBtn2 = dynamic_cast<UIButton*>(ul->getWidgetByName("ItemBtn2"));
    itemBtn2->setTag(Btn_2);
    itemBtn2->addReleaseEvent(this, coco_releaseselector(Scene_GameItem::itemBtnCallBack));
    UIButton* itemBtn3 = dynamic_cast<UIButton*>(ul->getWidgetByName("ItemBtn3"));
    itemBtn3->setTag(Btn_3);
    itemBtn3->addReleaseEvent(this, coco_releaseselector(Scene_GameItem::itemBtnCallBack));
    UIButton* itemBtn4 = dynamic_cast<UIButton*>(ul->getWidgetByName("ItemBtn4"));
    itemBtn4->setTag(Btn_4);
    itemBtn4->addReleaseEvent(this, coco_releaseselector(Scene_GameItem::itemBtnCallBack));
    
    

    
    //勋章任务点击.
    taskBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("TitleBtn"));
    taskBtn->addReleaseEvent(this, coco_releaseselector(Scene_GameItem::taskBtnCallBack));
    taskBtn->setPressedActionEnabled(true);
   
    rankBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("RankingBtn"));
    rankBtn->addReleaseEvent(this, coco_releaseselector(Scene_GameItem::rankBtnCallBack));
    rankBtn->setPressedActionEnabled(true);
    
    CTaskMan::sharedInstance().requestDayTaskSelect(GameShare_Global::shareGlobal()->gameType);
    
	//人物动画
	auto pRole = CCSprite::create("role/pig_tl/1.png");
	pRole->setTag(AniLayerTag);
	this->addChild(pRole,1);
    return true;
}


void Scene_GameItem::setItemByTag(int btnTag)
{
    CCString str;
        UIButton* itemBtn = dynamic_cast<UIButton*>(ul->getWidgetByName(str.getCString()));
    if (itemBtn) {
        itemBtn->setTextures("./CocoStudioResources/ItemSelected.png", "./CocoStudioResources/ItemSelected.png", "");
    }
    for (int i=0; i<4; i++) {
        str.initWithFormat("ItemBtn%d",i+1);
        UIButton* itemBtn = dynamic_cast<UIButton*>(ul->getWidgetByName(str.getCString()));

        if (itemBtn) {
            if (btnTag == i) {
                itemBtn->setTextures("./CocoStudioResources/ItemSelected.png", "./CocoStudioResources/ItemSelected.png", "");

            }else
            {
                itemBtn->setTextures("./CocoStudioResources/ItemNoSelect.png", "./CocoStudioResources/ItemNoSelect.png", "");
            }
        }

    }
}
void Scene_GameItem::itemBtnCallBack(cocos2d::CCObject *object)
{
    UIButton* btn = (UIButton*)object;
    UIImageView* img;
    
    //通过游戏的道具信息获取道具价钱.
    sItemData* itemData = CGameInfoMan::sharedInstance().getItemDate(GameShare_Global::shareGlobal()->gameType, btn->getTag());

    UILabel* itemInfo = dynamic_cast<UILabel*>(ul->getWidgetByName("Label_591"));
    
    
    switch (btn->getTag()) {
        case Btn_1:
            img = dynamic_cast<UIImageView*>(ul->getWidgetByName("IsSelectImg_1"));
            break;
        case Btn_2:
            img = dynamic_cast<UIImageView*>(ul->getWidgetByName("IsSelectImg_2"));
            break;
        case Btn_3:
            img = dynamic_cast<UIImageView*>(ul->getWidgetByName("IsSelectImg_3"));
            break;
        case Btn_4:
            img = dynamic_cast<UIImageView*>(ul->getWidgetByName("IsSelectImg_4"));
            break;
        default:
            break;
    }
    
    if (img->isVisible()) {
        
        img->setVisible(false);

        if (itemData) {
            CCString infoStr;
            infoStr.initWithFormat("%s:%s",itemData->ItemName.c_str(),itemData->ItemDetail.c_str());
            itemInfo->setText(infoStr.getCString());
            needGold -= itemData->CurrencyValue;
        }
    }else{
        img->setVisible(true);
        if (itemData) {
            CCString infoStr;
            infoStr.initWithFormat("%s:%s",itemData->ItemName.c_str(),itemData->ItemDetail.c_str());
            itemInfo->setText(infoStr.getCString());
            needGold += itemData->CurrencyValue;
            if (CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney < needGold) {
                GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
                needGold -= itemData->CurrencyValue;
                alertUl->setText(GET_STRING_CSV(1010000021));
                this->addChild(alertUl,1);
                img->setVisible(false);
            }
        }
        
    }
    this->setItemByTag(btn->getTag());
}
void Scene_GameItem::equipSuperCallBack(cocos2d::CCObject *object)
{
    UIButton* btn = (UIButton*)object;
    if (gameLayer_Strong) {
        gameLayer_Strong = NULL;
    }
    gameLayer_Strong = GameLayer_ItemStrong::create();
    
    gameLayer_Strong->setSureCallbackFunc(this, callfuncO_selector(Scene_GameItem::equipBtnCallBack));
    
    CCString equipName = "";
    int equipLv = 0;
    CCString equipValue = "";
    CCString equipDetail = "";
    CCString equipImg = "";
    //获取玩家的这款游戏的强化信息.
    sMGameStrengthen mStrength;
    if (int temp = CPlayerInfoMan::sharedInstance().getMStrengthenByGameTag(GameShare_Global::shareGlobal()->gameType, btn->getTag(),mStrength)) {
        equipLv = mStrength.strengthenlv;
        equipValue.initWithFormat("x%d", mStrength.currencyValue);
        equipName.initWithFormat("./CocoStudioResources/GameItemName/%d.png",mStrength.strengthenImg);
        equipDetail = mStrength.strengthenDetail;
        equipImg.initWithFormat("./CocoStudioResources/GameStrengthen/%d.png",mStrength.strengthenImg);
        if (temp == 2) {
            equipValue = GET_STRING_CSV(1010000025);
            gameLayer_Strong->setBtnUnClick();
        }
    }
    
    CCString str;
    gameLayer_Strong->setItemInfo(equipDetail.getCString());
    gameLayer_Strong->setItemImg(equipImg.getCString());
    gameLayer_Strong->setItemLv(equipLv);
    gameLayer_Strong->setItemName(equipName.getCString());
    gameLayer_Strong->setItemCurrency(mStrength.currencyValue);
//    gameLayer_Strong->setSureCallbackFunc(this, callfuncO_selector(Scene_GameItem::equipBtnCallBack));
    gameLayer_Strong->setSureBtnTag(btn->getTag());
    gameLayer_Strong->setTag(btn->getTag());
    this->addChild(gameLayer_Strong,1);
    
}
void Scene_GameItem::equipBtnCallBack(cocos2d::CCObject *object)
{
    UIButton* btn = (UIButton*)object;
    //获取游戏的强化信息.
     sMGameStrengthen mStrength;
    if (CPlayerInfoMan::sharedInstance().getMStrengthenByGameTag(GameShare_Global::shareGlobal()->gameType, btn->getTag(),mStrength)) {
        int tempGold = CPlayerInfoMan::sharedInstance().getPlayerInfo().nMoney;
        tempGold = tempGold - mStrength.currencyValue - needGold;
        if (tempGold < 0) {
            GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
            alertUl->setText(GET_STRING_CSV(1010000021));
            alertUl->setSureCallbackFunc(this, callfuncO_selector(Scene_GameItem::equipSuperBtnCanBenClick));
            this->addChild(alertUl, 10);
            return;
        }
        CStrengthenMan::sharedInstance().RequestStrengthenLvUp(mStrength.strengthenId, GameShare_Global::shareGlobal()->gameType);
    }
}

void Scene_GameItem::equipSuperBtnCanBenClick(cocos2d::CCObject *p) {
    gameLayer_Strong -> setBtnCanClick();
}

void Scene_GameItem::equipSureCallBack(cocos2d::CCObject *object)
{
//    UIButton* btn = (UIButton*)object;

   // GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
   //alertUl->setText(GET_STRING_CSV(1010000020));
   // this->addChild(alertUl,1);
    
}
void Scene_GameItem::taskBtnCallBack(cocos2d::CCObject *object)
{
    GameMedalLayer* task = GameMedalLayer::create();
    task -> setGameType(GameShare_Global::shareGlobal()->gameType);
    this->addChild(task,1);
}

void Scene_GameItem::showRankList()
{
    CInfoSysManager::sharedInstance().RequestGetPkInfo();
    CInfoSysManager::sharedInstance().RequestGetBePkInfo();
    //    this->rankBtnCallBack(NULL);
}
void Scene_GameItem::pkBtnCallBack(cocos2d::CCObject *object)
{
    if (!returnBtn->isVisible()) {
        this->setPkView(false);
    }else{
        this->setPkView(true);
    }
    
}
void Scene_GameItem::setPkView(bool isPk)
{
    GameLayerPkBar* layer = (GameLayerPkBar*)this->getChildByTag(PkLayerTag);
    if (layer) {
        layer->removeFromParent();
    }
    returnBtn->setTouchEnable(!isPk);
    returnBtn->setVisible(!isPk);
    rankBtn->setTouchEnable(!isPk);
    rankBtn->setVisible(!isPk);
    taskBtn->setTouchEnable(!isPk);
    taskBtn->setVisible(!isPk);
    if (isPk) {
        GameLayerPkBar* pkLayer = GameLayerPkBar::create();
        pkLayer->setTag(PkLayerTag);
        if (CPkSysManager::sharedInstance().pkType == PkTypeSend) {
            pkLayer->setType(0);
        }else if(CPkSysManager::sharedInstance().pkType == PkTypeReceive){
            pkLayer->setType(1);
        }
        pkLayer->setName(CPkSysManager::sharedInstance().playerName);
        pkLayer->setAvatar(CPkSysManager::sharedInstance().playerUrl);
        pkLayer->addSureCallbackFunc(this, coco_releaseselector(Scene_GameItem::pkBtnCallBack));
        this->addChild(pkLayer,1);
    }else{
        CPkSysManager::sharedInstance().pkType = PkTypeNormal;
    }
}
void Scene_GameItem::rankBtnCallBack(cocos2d::CCObject *object)
{
	CFriendManager::sharedInstance().RequestGetRankByGame(GameShare_Global::shareGlobal()->gameType);
}
void Scene_GameItem::returnBtnCallBack(cocos2d::CCObject *object)
{
    GameShare_Global::shareGlobal()->gameType = Game_Null;
    CCDirector::sharedDirector()->popScene();
}

void goIntoGame(){
    
}
void Scene_GameItem::startGameCallBack(cocos2d::CCObject *object)
{
    UIButton* startBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("StartGame"));
    CCSprite* tempSprite = (CCSprite*)startBtn->getRenderer()->getChildByTag(100);
    
    if (tempSprite && tempSprite->isRunning()) {
        return;
    }
    if (GameShare_Global::shareGlobal()->loginType != LoginType_Tourist) {
        
    
    if (CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower <= 0) {
        GameLayer_Alert *alertUl = GameLayer_Alert::creatWithOnlySure(Type_OnlySure);
        alertUl->setText(GET_STRING_CSV(1010000023));
        this->addChild(alertUl,1);
        return;
    }
    CCUserDefault::sharedUserDefault()->setBoolForKey("P_1", false);
    CCUserDefault::sharedUserDefault()->setBoolForKey("P_2", false);
    CCUserDefault::sharedUserDefault()->setBoolForKey("P_3", false);
    CCUserDefault::sharedUserDefault()->setBoolForKey("P_4", false);
    //////////////////////////////////////////////////////////////////////////
	//道具添加
	auto img = dynamic_cast<UIImageView*>(ul->getWidgetByName("IsSelectImg_1"));
	sItemData* pItemData = NULL;
    if (img&&img->isVisible()){
		pItemData = CGameInfoMan::sharedInstance().getItemDate(GameShare_Global::shareGlobal()->gameType, Btn_1);
// 		if (GameShare_Global::shareGlobal()->gameType == Game_Jelly){
// 			CRtData.addEffectByItemId(pItemData->ItemId);
// 		}
// 		else if(GameShare_Global::shareGlobal()->gameType == Game_Fruit){
// 			if(pItemData)
// 				CFrData.addEffectByItemId(pItemData->ItemId);
//             
// 		}else if (GameShare_Global::shareGlobal()->gameType == Game_TaiKo){
// 			if(pItemData)
// 				CTKData.addEffectByItemId(pItemData->ItemId);
// 		}
//         else 
			if (GameShare_Global::shareGlobal()->gameType == Game_Memory) {
            CCUserDefault::sharedUserDefault()->setBoolForKey("P_3", true);
        }
        else if (GameShare_Global::shareGlobal()->gameType == Game_Link) { 
            CCUserDefault::sharedUserDefault()->setBoolForKey("P_1", true);
        }
        else if (GameShare_Global::shareGlobal()->gameType == Game_SanXiao) {
            CCUserDefault::sharedUserDefault()->setBoolForKey("P_1", true);
        }
// 		SClientItemData* pItem = CItemMan::sharedInstance().getItem(pItemData->ItemId);
// 		if (pItem&&pItem->fNum <= 0)
// 		{
// 		}else
		{
			if (pItemData) {
				CItemMan::sharedInstance().RequestBuyItem(pItemData->ItemId);
			}
		}
        
	}
	auto img1 = dynamic_cast<UIImageView*>(ul->getWidgetByName("IsSelectImg_2"));
	if (img1&&img1->isVisible()){
		pItemData = CGameInfoMan::sharedInstance().getItemDate(GameShare_Global::shareGlobal()->gameType, Btn_2);
// 		if (GameShare_Global::shareGlobal()->gameType == Game_Jelly){
// 			CRtData.addEffectByItemId(pItemData->ItemId);
// 		}
// 		else if(GameShare_Global::shareGlobal()->gameType == Game_Fruit){
// 			if(pItemData)
// 				CFrData.addEffectByItemId(pItemData->ItemId);
// 		}else if (GameShare_Global::shareGlobal()->gameType == Game_TaiKo){
// 			if(pItemData)
// 				CTKData.addEffectByItemId(pItemData->ItemId);
// 		}
//         else
			if (GameShare_Global::shareGlobal()->gameType == Game_Memory) {
             CCUserDefault::sharedUserDefault()->setBoolForKey("P_1", true);
        }
        else if (GameShare_Global::shareGlobal()->gameType == Game_Link) {
            CCUserDefault::sharedUserDefault()->setBoolForKey("P_2", true);
        }
        else if (GameShare_Global::shareGlobal()->gameType == Game_SanXiao) {
            CCUserDefault::sharedUserDefault()->setBoolForKey("P_2", true);
        }
        
// 		SClientItemData* pItem = CItemMan::sharedInstance().getItem(pItemData->ItemId);
// 		if (pItem&&pItem->fNum <= 0)
// 		{
// 		}else
		{
			if (pItemData) {
				CItemMan::sharedInstance().RequestBuyItem(pItemData->ItemId);
			}
		}
        
	}
	auto img2 = dynamic_cast<UIImageView*>(ul->getWidgetByName("IsSelectImg_3"));
	if (img2&&img2->isVisible()){
		pItemData = CGameInfoMan::sharedInstance().getItemDate(GameShare_Global::shareGlobal()->gameType, Btn_3);
// 		if (GameShare_Global::shareGlobal()->gameType == Game_Jelly){
// 			CRtData.addEffectByItemId(pItemData->ItemId);
// 		}
// 		else if(GameShare_Global::shareGlobal()->gameType == Game_Fruit){
// 			if(pItemData)
// 				CFrData.addEffectByItemId(pItemData->ItemId);
// 		}else if (GameShare_Global::shareGlobal()->gameType == Game_TaiKo){
// 			if(pItemData)
// 				CTKData.addEffectByItemId(pItemData->ItemId);
// 		}
//         else 
			if (GameShare_Global::shareGlobal()->gameType == Game_Memory) {
            CCUserDefault::sharedUserDefault()->setBoolForKey("P_2", true);
        }
        else if (GameShare_Global::shareGlobal()->gameType == Game_Link) {
            CCUserDefault::sharedUserDefault()->setBoolForKey("P_3", true);
        }
        else if (GameShare_Global::shareGlobal()->gameType == Game_SanXiao) {
            CCUserDefault::sharedUserDefault()->setBoolForKey("P_3", true);
        }
// 		SClientItemData* pItem = CItemMan::sharedInstance().getItem(pItemData->ItemId);
// 		if (pItem&&pItem->fNum <= 0)
// 		{
// 		}else
		{
			if (pItemData) {
				CItemMan::sharedInstance().RequestBuyItem(pItemData->ItemId);
			}
		}
	}
	auto img3 = dynamic_cast<UIImageView*>(ul->getWidgetByName("IsSelectImg_4"));
	if (img3&&img3->isVisible()){
		pItemData = CGameInfoMan::sharedInstance().getItemDate(GameShare_Global::shareGlobal()->gameType, Btn_4);
// 		if (GameShare_Global::shareGlobal()->gameType == Game_Jelly){
// 			CRtData.addEffectByItemId(pItemData->ItemId);
// 		}
// 		else if(GameShare_Global::shareGlobal()->gameType == Game_Fruit){
// 			if(pItemData)
// 				CFrData.addEffectByItemId(pItemData->ItemId);
// 		}else if (GameShare_Global::shareGlobal()->gameType == Game_TaiKo){
// 			if(pItemData)
// 				CTKData.addEffectByItemId(pItemData->ItemId);
// 		}
//         else 
			if (GameShare_Global::shareGlobal()->gameType == Game_Memory) {
            CCUserDefault::sharedUserDefault()->setBoolForKey("P_4", true);
        }
        else if (GameShare_Global::shareGlobal()->gameType == Game_Link) {
            CCUserDefault::sharedUserDefault()->setBoolForKey("P_4", true);
        }
        else if (GameShare_Global::shareGlobal()->gameType == Game_SanXiao) {
            CCUserDefault::sharedUserDefault()->setBoolForKey("P_4", true);
        }
// 		SClientItemData* pItem = CItemMan::sharedInstance().getItem(pItemData->ItemId);
// 		if (pItem&&pItem->fNum <= 0)
// 		{
// 		}else
		{
			if (pItemData) {
				CItemMan::sharedInstance().RequestBuyItem(pItemData->ItemId);
			}
		}
        
	}
	//////////////////////////////////////////////////////////////////////////
	//设置强化
	CDataManager::GetInstance().updataStrengthenItem(GameShare_Global::shareGlobal()->gameType);
	//////////////////////////////////////////////////////////////////////////

        //消耗体力,纪录体力消耗时间
        if (CPlayerInfoMan::sharedInstance().getPlayerInfo().nPower == 5) {
//            CPlayerInfoMan::sharedInstance().getPlayerInfo().riceEndTime = CTimeUtil::GetSystemTimeStamp();
            CPlayerInfoMan::sharedInstance().getPlayerInfo().riceEndTime = 480;
        }
        CPlayerInfoMan::sharedInstance().RequestUseRice();
        
    }
   
    
    CCSprite* riceEffect = CCSprite::create();
    CCAnimation* pAni = CCAnimation::create();
    CCString str;
    for (int i=1; i<=6; i++) {
        str.initWithFormat("./CocoStudioResources/Rice/UseRice%d.png",i);
        pAni->addSpriteFrameWithFileName(str.getCString());
    }
    pAni->setDelayPerUnit(0.3f/5.f);
    pAni->setLoops(1);
    CCFiniteTimeAction*  pAction = CCSequence::create(
                                                      CCAnimate::create(pAni),
                                                      CCHide::create(),
                                                      CCDelayTime::create(0.2),
                                                     // CCCallFuncO::create(this, callfuncO_selector(Scene_GameItem::gointoGameCallBack),NULL),
                                                      NULL);
    auto *pic = CCSprite::create("./CocoStudioResources/Rice/UseRice1.png");
    riceEffect->setTexture(pic -> getTexture());
    riceEffect->setTextureRect(CCRectMake(0, 0, pic->getContentSize().width, pic -> getContentSize().height));
    riceEffect->setPosition(ccp(riceEffect->getPositionX()-100, riceEffect->getPositionY()));
    startBtn->addRenderer(riceEffect, 100);
    
    riceEffect->runAction(pAction);

}
void Scene_GameItem::gointoGameCallBack(CCObject *object)
{
    CCScene *gameScene = GameShare_Scene::getGameSceneByType(GameShare_Global::shareGlobal()->gameType);
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.4, gameScene));
}
CCSprite*  Scene_GameItem::getLvByScore(int lv)
{
    
    int temp = lv;
    //位数,用于设置横坐标偏移量.
    int digit = 0;
    CCSprite* scroeSprite = CCSprite::create();
//    if (temp == 0) {
//        CCSprite *m_Sprite = m_Sprite = CCSprite::createWithSpriteFrameName("ItemLvNumZero.png");
//        scroeSprite->addChild(m_Sprite);
//        return scroeSprite;
//    }
    
    while (temp>0 || (digit==0 && temp==0)) {
        int remainder = temp % 10;
        temp = temp/10;
        CCSprite *m_Sprite;
        CCRect rc;
        switch(remainder)
        {
            case 0:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ItemLvNumZero.png");
                break;
            }
            case 1:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ItemLvNumOne.png");
                break;
            }
            case 2:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ItemLvNumTwo.png");
                break;
            }
            case 3:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ItemLvNumThree.png");
                break;
            }
            case 4:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ItemLvNumFour.png");
                break;
            }
            case 5:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ItemLvNumFive.png");
                break;
            }
            case 6:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ItemLvNumSix.png");
                break;
            }
            case 7:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ItemLvNumSeven.png");
                break;
            }
            case 8:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ItemLvNumEight.png");
                break;
            }
            case 9:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ItemLvNumNine.png");
                
                break;
            }
            default:
            {
                m_Sprite = CCSprite::create("./CocoStudioResources/ItemLvNumZero.png");
                break;
            }
        }
        
        m_Sprite->setPosition(ccp((digit)*(-20), 0));
        scroeSprite->addChild(m_Sprite);
        //        if (digit%3==0 && digit>0) {
        //            CCSprite *comma = CCSprite::createWithSpriteFrameName("ScoreNumComma.png");;
        //            comma->setPosition(ccp(m_Sprite->getPositionX()+15, -10));
        //            scroeSprite->addChild(comma);
        //        }
        digit++;
    }
        scroeSprite->setContentSize(CCSize(20.0*digit, 20));
        CCArray* array = scroeSprite->getChildren();
        for (int i=0; i<array->count(); i++) {
            CCPoint point = ((CCSprite*)array->objectAtIndex(i))->getPosition();
            point.x += (digit+(digit/3))*20.0;
            ((CCSprite*)array->objectAtIndex(i))->setPosition(point);
        }
    
    return scroeSprite;
}
void Scene_GameItem::setLvNum()
{
    if (lvImg1) {
        lvImg1->removeFromParent();
    }
    if (lvImg2) {
        lvImg2->removeFromParent();
    }
    if (lvImg3) {
        lvImg3->removeFromParent();
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    int lv1 = 0;
    int lv2 = 0;
    int lv3 = 0;
    sMGameStrengthen mGameStreng;
    if (CPlayerInfoMan::sharedInstance().getMStrengthenByGameTag(GameShare_Global::shareGlobal()->gameType, 0, mGameStreng)) {
        lv1 = mGameStreng.strengthenlv;
    }
    if (CPlayerInfoMan::sharedInstance().getMStrengthenByGameTag(GameShare_Global::shareGlobal()->gameType, 1, mGameStreng)) {
        lv2 = mGameStreng.strengthenlv;
    }
  
    if (CPlayerInfoMan::sharedInstance().getMStrengthenByGameTag(GameShare_Global::shareGlobal()->gameType, 2, mGameStreng)) {
        lv3 = mGameStreng.strengthenlv;
    }
    
    if (CPlayerInfoMan::sharedInstance().getMStrengthenByGameTag(GameShare_Global::shareGlobal()->gameType, 0, mGameStreng) == 2) {
        lvImg1 = CCSprite::create("./CocoStudioResources/Item/ItemLvMax.png");
        lvImg1->setPosition(ccp(visibleSize.width/2-145, visibleSize.height/2-37));
        
    }else{
        lvImg1 = this->getLvByScore(lv1);
        lvImg1->setPosition(ccp(visibleSize.width/2-165, visibleSize.height/2-27));
    }
    
    
    ul->addChild(lvImg1);
    
    if (CPlayerInfoMan::sharedInstance().getMStrengthenByGameTag(GameShare_Global::shareGlobal()->gameType, 1, mGameStreng) == 2) {
        lvImg2 = CCSprite::create("./CocoStudioResources/Item/ItemLvMax.png");
        lvImg2->setPosition(ccp(visibleSize.width/2+38, visibleSize.height/2-37));
        
    }else{
        lvImg2 = this->getLvByScore(lv2);
        lvImg2->setPosition(ccp(visibleSize.width/2+18, visibleSize.height/2-27));
    }
    
    ul->addChild(lvImg2);
    
    if (CPlayerInfoMan::sharedInstance().getMStrengthenByGameTag(GameShare_Global::shareGlobal()->gameType, 2, mGameStreng) == 2) {
        lvImg3 = CCSprite::create("./CocoStudioResources/Item/ItemLvMax.png");
        lvImg3->setPosition(ccp(visibleSize.width/2+215, visibleSize.height/2-37));
        
    }else{
        lvImg3 = this->getLvByScore(lv3);
        lvImg3->setPosition(ccp(visibleSize.width/2+195, visibleSize.height/2-27));
    }
    
    ul->addChild(lvImg3);
}
bool Scene_GameItem::onPackageFilter(void *pDataPkg) {
	CResponsePacket* pPkt = (CResponsePacket*)pDataPkg;
	unsigned int unMsgType = pPkt->getMsgType();
	unsigned int unMsgCode = pPkt->getMsgCode();
	int nResCode = pPkt->getResCode();
	
	//网络数据传输完成
	if (pPkt->getDataState() == eNetMsgDataStateComplete/* && nResCode == eNetMsgResCodeSucceed*/)
	{
        if (unMsgType == eNetMsgTypeIntensifySys) {
            if (unMsgCode == eNetMsgCodeIntensifySysLvUp)
			{
                this->initData();
                sMGameStrengthen mStrength;
                if (int temp = CPlayerInfoMan::sharedInstance().getMStrengthenByGameTag(GameShare_Global::shareGlobal()->gameType, gameLayer_Strong->getTag(),mStrength)){
                    gameLayer_Strong->setItemLv(mStrength.strengthenlv);
                    CCString str;
                    str.initWithFormat(GET_STRING_CSV(1010000019), mStrength.currencyValue, "金币");
                    if (temp == 2) {
                        str = GET_STRING_CSV(1010000025);
                        gameLayer_Strong->setBtnUnClick();
                    }
                    gameLayer_Strong->setItemCurrency(mStrength.currencyValue);
                }
                gameLayer_Strong->successLvUp();
			}
        }
        
        ////好友系统
        if (unMsgType == eNetMsgTypeFriendSys) {
           if (unMsgCode == eNetMsgFriendSysGetRankByGame) {
               GameLayerGameRank* task = GetDlgPtr(GameLayerGameRank);
               task->addSureCallbackFunc(this, coco_releaseselector(Scene_GameItem::pkBtnCallBack));
               this->addChild(task, 1);
            }
        }
        //消息系统
        if (unMsgType == eNetMsgTypeMsgSys) {
            if (unMsgCode == eNetMsgGetBePkInfo) {
                GameLayerChallenge* layer = GetDlgPtr(GameLayerChallenge);
                layer->addSureCallbackFunc(this, coco_releaseselector(Scene_GameItem::pkBtnCallBack));
                this->addChild(layer,1);
                layer->setState(0);
            }
        }

		//
		if (unMsgType == eNetMsgTypePlayerSys)
		{
			if (unMsgCode == eNetMsgPlayerSysReduceEnergy)
			{
				gointoGameCallBack(NULL);
			}
		}
		
	}
	return true;
}
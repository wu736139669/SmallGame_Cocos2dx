//
//  GameTableLayer.h
//  ChallengesMaster
//
//  Created by mac on 14-2-21.
//  游戏列表.
//

#ifndef __ChallengesMaster__GameTableLayer__
#define __ChallengesMaster__GameTableLayer__

#include "GameLayer_RiceBar.h"

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameLayer_Base.h"
#include "GameCommon.h"



USING_NS_CC;
USING_NS_CC_EXT;

class GameTableLayer : public GameLayer_Base, public CCTableViewDataSource,public CCTableViewDelegate
{
    DECLARE_DLG_ID();
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    ~GameTableLayer();
    GameTableLayer(void);
    virtual void onEnter();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameTableLayer);
    
    //    DataSource
    
    /**
     
     * cell height for a given table.
     
     *
     
     * @param table table to hold the instances of Class
     
     * @return cell size
     
     */
    
    virtual CCSize cellSizeForTable(CCTableView *table);
    
    /**
     
     * a cell instance at a given index
     
     *
     
     * @param idx index to search for a cell
     
     * @return cell found at idx
     
     */
    
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    
    /**
     
     * Returns number of cells in a given table view.
     
     *
     
     * @return number of cells
     
     */
    
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    // where process down  to set highlight status
    virtual void tableCellHighlight(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    
    //when touch leave  the highlight status disappear
    virtual void tableCellUnhighlight(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    
    //delegate
    
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);

    
    //this must include CCScrollViewDelete beacase the CCTableView inherited from CCScrollView
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
    
    
    
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
    
    void reFresh(void);
    
    virtual bool onPackageFilter(void *pDataPkg);
    
    GameLayer_RiceBar* riceBar;
private:
    
    void beginGame(CCObject *object);
    
    CCSprite* getSpriteByScore(long score);

    
//    CCTableView *tableView;
    
};

#endif /* defined(__ChallengesMaster__GameTableLayer__) */

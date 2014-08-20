/********************************************************************
	created:	2014/04/11 
	filename: 	CounterByImage.h
	author:		王少培
	purpose:	
*********************************************************************/
#include "Counter.h"
#include "CounterByImage.h"
#include "StringUtil.h"
USING_NS_CC;
#define _SCORE_NUM_MAX_ 9

CCounterImage* CCounterImage::create(const VEC_NUMFILENAME& vecNumFileName, char* pDelim,int number, bool bpListLoad)
{
    CCounterImage* pCI = new CCounterImage();
    pCI->init(vecNumFileName,number,pDelim,bpListLoad);
    pCI->autorelease();
    return pCI;
}
bool CCounterImage::init(const VEC_NUMFILENAME& vecNumFileName,int number, char* pDelim, bool bpListLoad)
{
    //int fontSize = 16;
    //CCLabelTTF* goldLabel = CCLabelTTF::create("金币:", "Thonburi", fontSize);
    //this->addChild(goldLabel);
    //CCSize goldLabelSize = goldLabel->getContentSize();
	_delim = pDelim;
    CCString str;
	int nCounter = 0;
    for(int i = 0 ;i < _SCORE_NUM_MAX_;i++){
        int count = vecNumFileName.size();
        CCArray* presenters = CCArray::createWithCapacity(count);
        for(int j = 0;j < count;j++){

			str.initWithFormat(vecNumFileName[j].c_str());
			CCSprite* p = NULL;
			if(bpListLoad)
				p = CCSprite::createWithSpriteFrameName(str.getCString());
			else
				p = CCSprite::create(str.getCString());
            presenters->addObject(p);
        }
        CCounter* counter = CCounter::create(presenters);
        //counter->setPosition(ccp(/*goldLabelSize.width*0.8+*/31 * i, 0));
		this->addChild(counter, 0, i);
		if(_delim){
			if(i % 3 == 0 && i > 0){
				CCSprite* p = NULL;
				p = CCSprite::create(_delim);
				if(p == NULL)
				 p = CCSprite::createWithSpriteFrameName(_delim);
					
				p->setVisible(false);
				p->setPositionY(p->getContentSize().height/2 - counter->getCurrDigit()->getContentSize().height/2);
				this->addChild(p, 0, eDelimStartIndex + nCounter);
				nCounter++;
			}
		}
    }
    this->setNumber(number);
    return true;
}
void CCounterImage::setNumber(int number,bool bAni,unsigned int ceiling)
{
    number = MIN(ceiling, number);
    number = MAX(number, 0);
    _number = number;
	for(int i = 0 ;i < _SCORE_NUM_MAX_;i++){
		 CCounter* counter = (CCounter*)this->getChildByTag(i);
		 counter->setVisible(false);
	}
	int nAmountDot = _SCORE_NUM_MAX_%3 > 0 ? _SCORE_NUM_MAX_/3 : _SCORE_NUM_MAX_/3 - 1;
	for (int i = 0; i < nAmountDot; ++i)
	{
		this->getChildByTag(eDelimStartIndex + i)->setVisible(false);
	}

	_vecNumber.clear();
	int nAmount = CStringUtil::ToString(_number).size();
	int nCounter = 0;
	int nIndex = 0;
    for(int i = nAmount - 1; i >= 0;i--){
		if(_delim && nCounter > 0 && nCounter % 3 == 0){
			CCNode* pDot = this->getChildByTag(eDelimStartIndex + nIndex);
			pDot->setVisible(true);
			_vecNumber.push_back(pDot);
			nIndex ++;
			
		}

        CCounter* counter = (CCounter*)this->getChildByTag(i);
        int digit = _number / (int)(pow(10.0, nAmount-i-1)) % 10;
        counter->setDigit(digit,bAni);
		counter->setVisible(true);
		_vecNumber.push_back(counter);

		nCounter++;
    }
	_updata();

}
void CCounterImage::_updata()
{
	int nTotalWidth = 0;
	int nCounter = 0;
	int nAmount = _vecNumber.size();
	
	for(int i = 0 ;i < nAmount;i++){
		CCounter* counter = dynamic_cast<CCounter*>(_vecNumber[i]);
		if(counter)
			nTotalWidth += /*counter->getCurrDigit()->getContentSize().width*/_cellNumberWidth;
		else{
			nTotalWidth += _vecNumber[i]->getContentSize().width;
		}
	}
	int nWidth = 0;
	for(int i = nAmount-1 ;i >= 0; i--){
		CCounter* counter = dynamic_cast<CCounter*>(_vecNumber[i]);
		if(counter)
		{
			nWidth += /*counter->getCurrDigit()->getContentSize().width*/_cellNumberWidth/2;
			counter->setPositionX(-nTotalWidth/2 + nWidth);
			nWidth += /*counter->getCurrDigit()->getContentSize().width*/_cellNumberWidth/2;
		}else
		{
			nWidth += _vecNumber[i]->getContentSize().width/2;
			_vecNumber[i]->setPositionX(-nTotalWidth/2 + nWidth);
			nWidth += _vecNumber[i]->getContentSize().width/2;
		}
		
		//nWidth += counter->getCurrDigit()->getContentSize().width;
	}
	_totalWidth = nTotalWidth;
}
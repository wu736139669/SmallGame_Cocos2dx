//
//  NumSprite.h
//  OnceAgain
//
//  Created by mac on 14-4-17.
// 用于获取数字标签
//

#ifndef __OnceAgain__NumSprite__
#define __OnceAgain__NumSprite__
#include "cocos2d.h"
USING_NS_CC;
class NumSprite
{
public:
    //通过数字前增加一个图片.数字大小，图片前名称还有图片之间的间隙获取.
    static CCSprite* getNumSprite(std::string addImg, std::string lastImg,int num, std::string imgName, float offSetX,float offset=0.0);
    //通过数字大小，图片前名称还有图片之间的间隙获取.
    static CCSprite* getNumSprite(int num, std::string imgName, float offSetX,float offset=0.0);

	static void setSpriteTexture(CCSprite* p,CCTexture2D* pTex2D);
};

#endif /* defined(__OnceAgain__NumSprite__) */

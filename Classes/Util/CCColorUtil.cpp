//
//  CCColorUtil.cpp
//  OnceAgain
//
//  Created by mac on 14-4-16.
//
//

#include "CCColorUtil.h"

void CCColorUtil::addGray(CCSprite* sp)
{
    do
    {
        CCGLProgram* pProgram = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_Position_uColor);
        sp->setShaderProgram(pProgram);
        CHECK_GL_ERROR_DEBUG();
        
        sp->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        sp->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
        sp->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        CHECK_GL_ERROR_DEBUG();
        
        sp->getShaderProgram()->link();
        CHECK_GL_ERROR_DEBUG();
        
        sp->getShaderProgram()->updateUniforms();
        CHECK_GL_ERROR_DEBUG();
    } while (0);
}
void CCColorUtil::removeGray(CCSprite* sp)
{
    do
    {
        CCGLProgram* pProgram = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor);
        sp->setShaderProgram(pProgram);
        CHECK_GL_ERROR_DEBUG();
        
        sp->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        sp->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
        sp->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        CHECK_GL_ERROR_DEBUG();
        
        sp->getShaderProgram()->link();
        CHECK_GL_ERROR_DEBUG();
        
        sp->getShaderProgram()->updateUniforms();
        CHECK_GL_ERROR_DEBUG();
    } while (0);
}
CCSprite* CCColorUtil::graylightWithCCSprite(CCSprite* oldSprite,bool isLight)
{
	//CCSprite转成CCimage
	CCPoint ptOldAnchor = oldSprite->getAnchorPoint();
	CCPoint ptOld = oldSprite->getPosition();
	oldSprite->setAnchorPoint(ccp(0,0));
	oldSprite->setPosition(ccp(0,0));
	CCRenderTexture *outTexture = CCRenderTexture::create((int)oldSprite->getContentSize().width*1,(int)oldSprite->getContentSize().height*1);
	outTexture->begin();
	oldSprite->visit();
	outTexture->end();
	oldSprite->setAnchorPoint(ptOldAnchor);
	oldSprite->setPosition(ptOld);

	CCImage* finalImage = outTexture->newCCImage();
	unsigned char *pData = finalImage->getData();
	int iIndex = 0;

	if(isLight)
	{
		for (int i = 0; i < finalImage->getHeight(); i ++)
		{
			for (int j = 0; j < finalImage->getWidth(); j ++)
			{
				// highlight
				int iHightlightPlus = 50;
				int iBPos = iIndex;
				unsigned int iB = pData[iIndex];
				iIndex ++;
				unsigned int iG = pData[iIndex];
				iIndex ++;
				unsigned int iR = pData[iIndex];
				iIndex ++;
				//unsigned int o = pData[iIndex];
				iIndex ++;  //原来的示例缺少
				iB = (iB + iHightlightPlus > 255 ? 255 : iB + iHightlightPlus);
				iG = (iG + iHightlightPlus > 255 ? 255 : iG + iHightlightPlus);
				iR = (iR + iHightlightPlus > 255 ? 255 : iR + iHightlightPlus);
				//            iR = (iR < 0 ? 0 : iR);
				//            iG = (iG < 0 ? 0 : iG);
				//            iB = (iB < 0 ? 0 : iB);
				pData[iBPos] = (unsigned char)iB;
				pData[iBPos + 1] = (unsigned char)iG;
				pData[iBPos + 2] = (unsigned char)iR;
			}
		}
	}else{
		for (int i = 0; i < finalImage->getHeight(); i ++)
		{
			for (int j = 0; j < finalImage->getWidth(); j ++)
			{
				// gray
				int iBPos = iIndex;
				unsigned int iB = pData[iIndex];
				iIndex ++;
				unsigned int iG = pData[iIndex];
				iIndex ++;
				unsigned int iR = pData[iIndex];
				iIndex ++;
				//unsigned int o = pData[iIndex];
				iIndex ++; //原来的示例缺少
				unsigned int iGray = 0.3 * iR + 0.4 * iG + 0.2 * iB;
				pData[iBPos] = pData[iBPos + 1] = pData[iBPos + 2] = (unsigned char)iGray;
			}
		}
	}

	CCTexture2D *texture = new CCTexture2D;
	texture->initWithImage(finalImage);
	CCSprite* newSprite = CCSprite::createWithTexture(texture);
	delete finalImage;
	texture->release();
	return newSprite;
}
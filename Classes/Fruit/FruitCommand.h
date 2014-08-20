

#ifndef __CFruitCommand_H__
#define __CFruitCommand_H__

#include "GameCommon.h"
#include <string>
#include "cocos2d.h"
#include "GameCommand.h"

USING_NS_CC;
class CGameFruit;

// 移动
class CRoleMoveCommand : public CGameCommand
{
public:

	// 构造函数
	CRoleMoveCommand(unsigned int startTime, unsigned int duringTime,CCSprite* pFruit, CCPoint& ptDistance);
	// 析构函数
	virtual ~CRoleMoveCommand();
	// 生成执行指令
	virtual void Execute();

	PROPERTY_PASS_VALUE(CCSprite*, Fruit);
	// 位置偏移
	PROPERTY_PASS_CONST_REFERENCE(CCPoint, Distance);

};
class CRoleBombAniCommand: public CGameCommand
{
public:
	// 构造函数
	CRoleBombAniCommand( unsigned int startTime, unsigned int duringTime, CCSprite* pFruit);
	// 析构函数
	virtual ~CRoleBombAniCommand();
	// 生成执行指令
	virtual void Execute();

	PROPERTY_PASS_VALUE(CCSprite*, Fruit);
	// 位置偏移
	PROPERTY_PASS_CONST_REFERENCE(CCPoint, Distance);
};
class CRoleOutCommand : public CGameCommand
{
public:

	// 构造函数
	CRoleOutCommand(unsigned int startTime, unsigned int duringTime,CCObject* pFruit);
	// 析构函数
	virtual ~CRoleOutCommand(){}
	// 生成执行指令
	virtual void Execute();

	PROPERTY_PASS_VALUE(CCObject*, Fruit);

};

class CRoleLightningCommand : public CGameCommand
{
public:

	// 构造函数
	CRoleLightningCommand(unsigned int startTime, unsigned int duringTime,bool bRow,CCSprite* pFruit,CCPoint ptPos,CCObject* pParent,SEL_CallFuncND pCallFunc);
	// 析构函数
	virtual ~CRoleLightningCommand(){}
	// 生成执行指令
	virtual void Execute();

	CC_SYNTHESIZE(CCSprite*, mpFruit,Fruit);
	CC_SYNTHESIZE(CCPoint, mptPos,ptPos);
	CC_SYNTHESIZE(CCObject*, mpParent,Parent);
	CC_SYNTHESIZE(SEL_CallFuncND, mpCallFunc,CallFunc);
	CC_SYNTHESIZE(bool,mbRow,Row);
};

//移动结束
class CRoleMoveEndCommand: public CGameCommand
{
public:

	// 构造函数
	CRoleMoveEndCommand(unsigned int startTime, unsigned int duringTime,CCNode* pMainLayer);
	// 析构函数
	virtual ~CRoleMoveEndCommand();
	// 生成执行指令
	virtual void Execute();

	CC_SYNTHESIZE(CCNode*, mpMainLayer,MainLayer);
};

class CAllMoveEndCommand: public CGameCommand
{
public:
	// 构造函数
	CAllMoveEndCommand(unsigned int startTime, unsigned int duringTime,CCNode* pMainLayer);
	// 析构函数
	virtual ~CAllMoveEndCommand(){}
	// 生成执行指令
	virtual void Execute();

	CC_SYNTHESIZE(CCNode*, mpMainLayer,MainLayer);
};

//分数漂浮
class CScoreFloatCommand: public CGameCommand
{
public:

	// 构造函数
	CScoreFloatCommand(unsigned int startTime, unsigned int duringTime,CCSprite* pScore,CCPoint& pt);
	// 析构函数
	virtual ~CScoreFloatCommand(){}
	// 生成执行指令
	virtual void Execute();

	CC_SYNTHESIZE(CCSprite*, mpScore,Score);
	CC_SYNTHESIZE(CCPoint, mpPt,Point);
};

class CIceAniCommand: public CGameCommand
{
public:

	// 构造函数
	CIceAniCommand(unsigned int startTime, unsigned int duringTime,CGameFruit* pFruit);
	// 析构函数
	virtual ~CIceAniCommand(){}
	// 生成执行指令
	virtual void Execute();

	CC_SYNTHESIZE(CGameFruit*, mpFruit,Fruit);
};

#endif
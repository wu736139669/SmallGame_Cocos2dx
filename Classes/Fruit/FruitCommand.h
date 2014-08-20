

#ifndef __CFruitCommand_H__
#define __CFruitCommand_H__

#include "GameCommon.h"
#include <string>
#include "cocos2d.h"
#include "GameCommand.h"

USING_NS_CC;
class CGameFruit;

// �ƶ�
class CRoleMoveCommand : public CGameCommand
{
public:

	// ���캯��
	CRoleMoveCommand(unsigned int startTime, unsigned int duringTime,CCSprite* pFruit, CCPoint& ptDistance);
	// ��������
	virtual ~CRoleMoveCommand();
	// ����ִ��ָ��
	virtual void Execute();

	PROPERTY_PASS_VALUE(CCSprite*, Fruit);
	// λ��ƫ��
	PROPERTY_PASS_CONST_REFERENCE(CCPoint, Distance);

};
class CRoleBombAniCommand: public CGameCommand
{
public:
	// ���캯��
	CRoleBombAniCommand( unsigned int startTime, unsigned int duringTime, CCSprite* pFruit);
	// ��������
	virtual ~CRoleBombAniCommand();
	// ����ִ��ָ��
	virtual void Execute();

	PROPERTY_PASS_VALUE(CCSprite*, Fruit);
	// λ��ƫ��
	PROPERTY_PASS_CONST_REFERENCE(CCPoint, Distance);
};
class CRoleOutCommand : public CGameCommand
{
public:

	// ���캯��
	CRoleOutCommand(unsigned int startTime, unsigned int duringTime,CCObject* pFruit);
	// ��������
	virtual ~CRoleOutCommand(){}
	// ����ִ��ָ��
	virtual void Execute();

	PROPERTY_PASS_VALUE(CCObject*, Fruit);

};

class CRoleLightningCommand : public CGameCommand
{
public:

	// ���캯��
	CRoleLightningCommand(unsigned int startTime, unsigned int duringTime,bool bRow,CCSprite* pFruit,CCPoint ptPos,CCObject* pParent,SEL_CallFuncND pCallFunc);
	// ��������
	virtual ~CRoleLightningCommand(){}
	// ����ִ��ָ��
	virtual void Execute();

	CC_SYNTHESIZE(CCSprite*, mpFruit,Fruit);
	CC_SYNTHESIZE(CCPoint, mptPos,ptPos);
	CC_SYNTHESIZE(CCObject*, mpParent,Parent);
	CC_SYNTHESIZE(SEL_CallFuncND, mpCallFunc,CallFunc);
	CC_SYNTHESIZE(bool,mbRow,Row);
};

//�ƶ�����
class CRoleMoveEndCommand: public CGameCommand
{
public:

	// ���캯��
	CRoleMoveEndCommand(unsigned int startTime, unsigned int duringTime,CCNode* pMainLayer);
	// ��������
	virtual ~CRoleMoveEndCommand();
	// ����ִ��ָ��
	virtual void Execute();

	CC_SYNTHESIZE(CCNode*, mpMainLayer,MainLayer);
};

class CAllMoveEndCommand: public CGameCommand
{
public:
	// ���캯��
	CAllMoveEndCommand(unsigned int startTime, unsigned int duringTime,CCNode* pMainLayer);
	// ��������
	virtual ~CAllMoveEndCommand(){}
	// ����ִ��ָ��
	virtual void Execute();

	CC_SYNTHESIZE(CCNode*, mpMainLayer,MainLayer);
};

//����Ư��
class CScoreFloatCommand: public CGameCommand
{
public:

	// ���캯��
	CScoreFloatCommand(unsigned int startTime, unsigned int duringTime,CCSprite* pScore,CCPoint& pt);
	// ��������
	virtual ~CScoreFloatCommand(){}
	// ����ִ��ָ��
	virtual void Execute();

	CC_SYNTHESIZE(CCSprite*, mpScore,Score);
	CC_SYNTHESIZE(CCPoint, mpPt,Point);
};

class CIceAniCommand: public CGameCommand
{
public:

	// ���캯��
	CIceAniCommand(unsigned int startTime, unsigned int duringTime,CGameFruit* pFruit);
	// ��������
	virtual ~CIceAniCommand(){}
	// ����ִ��ָ��
	virtual void Execute();

	CC_SYNTHESIZE(CGameFruit*, mpFruit,Fruit);
};

#endif
/***************************************************************
* 
*
*  ���ߣ�		������
*  �ļ�����		CMyTimer.cpp
*  ����ʱ�䣺	
*
***************************************************************/
#ifndef __CGameCommon_H__
#define __CGameCommon_H__

#include "cocos2d.h"
// ���ԣ���ֵ
#define PROPERTY_PASS_VALUE(varType, varName) \
	protected:\
	varType m##varName;\
	public:\
	varType Get##varName() const { return m##varName; }\
	void Set##varName(varType _##varName) { m##varName = _##varName; }

// ���ԣ�����������
#define PROPERTY_PASS_CONST_REFERENCE(varType, varName) \
	protected:\
	varType m##varName;\
	public:\
	const varType& Get##varName() const { return m##varName; }\
	void Set##varName(const varType& _##varName) { m##varName = _##varName; }


// ��������
#define DECLARE_SINGLETON(classType, varName) \
	private:\
	static classType* varName;\
	public:\
	static classType* GetInstance();\
	static void Destroy();

// ʵ�ֵ���
#define IMPLEMENT_SINGLETON(classType, varName) \
	classType* classType::varName = NULL;\
	classType* classType::GetInstance()\
	{\
	if (varName == NULL)\
	varName = new classType();\
	return varName;\
	}\
	void classType::Destroy()\
	{\
	CC_SAFE_DELETE(varName);\
	}

// ��������
#define DESTROY_SINGLE(classType) (classType::GetInstance()->Destroy());

//////////////////////////////////////////////////////////////////////////
// ����DialogID����
#define DECLARE_DLG_ID() \
	private:\
	static int sDialogID;\
	public:\
	static int getDialogIDD(){return sDialogID;}

// ����DialogIDʵ��
#define IMPLEMENT_DLG_ID(classType,Val)	\
	int classType::sDialogID = Val;
	
//////////////////////////////////////////////////////////////////////////

#endif
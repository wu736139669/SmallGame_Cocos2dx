/***************************************************************
* 
*
*  作者：		王少培
*  文件名：		CMyTimer.cpp
*  创建时间：	
*
***************************************************************/
#ifndef __CGameCommon_H__
#define __CGameCommon_H__

#include "cocos2d.h"
// 属性，传值
#define PROPERTY_PASS_VALUE(varType, varName) \
	protected:\
	varType m##varName;\
	public:\
	varType Get##varName() const { return m##varName; }\
	void Set##varName(varType _##varName) { m##varName = _##varName; }

// 属性，传常量引用
#define PROPERTY_PASS_CONST_REFERENCE(varType, varName) \
	protected:\
	varType m##varName;\
	public:\
	const varType& Get##varName() const { return m##varName; }\
	void Set##varName(const varType& _##varName) { m##varName = _##varName; }


// 声明单件
#define DECLARE_SINGLETON(classType, varName) \
	private:\
	static classType* varName;\
	public:\
	static classType* GetInstance();\
	static void Destroy();

// 实现单件
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

// 单件销毁
#define DESTROY_SINGLE(classType) (classType::GetInstance()->Destroy());

//////////////////////////////////////////////////////////////////////////
// 窗口DialogID声明
#define DECLARE_DLG_ID() \
	private:\
	static int sDialogID;\
	public:\
	static int getDialogIDD(){return sDialogID;}

// 窗口DialogID实现
#define IMPLEMENT_DLG_ID(classType,Val)	\
	int classType::sDialogID = Val;
	
//////////////////////////////////////////////////////////////////////////

#endif
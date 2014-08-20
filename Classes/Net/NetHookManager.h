/***************************************************************
* 
*
*  作者：   王少培
*  文件名：   NetHookManager.cpp
*  创建时间： 2014-3-20
*
***************************************************************/
#ifndef __NETHOOKMANAGER_H__
#define __NETHOOKMANAGER_H__
#include <map>
typedef enum ENetHookType {
	eNetHookTypeMainInfo,
	ENetHookTypeDialog,
	eNetHookTypeMax,
};

class INetHook {
  ENetHookType nType;
public:
  INetHook(ENetHookType type): nType(type) {}
  virtual ~INetHook() {}

  virtual bool onPackageFilter(void *pDataPkg) {
    return true;
  }
  virtual ENetHookType getNetHookType() {
    return nType;
  }
};

class CNetHookManager {
  typedef std::map<unsigned int, INetHook *> NetHookList;
  NetHookList m_NetHookList;
public:
  CNetHookManager();
  static CNetHookManager *sharedNetHookManager();
  virtual bool onPackageFilter(void *pDataPkg);

  bool addHook(INetHook *pHook);
  void delHook(INetHook *pHook);
};
#endif

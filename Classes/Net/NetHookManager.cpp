/***************************************************************
* 
*
*  作者：   王少培
*  文件名：   NetHookManager.cpp
*  创建时间： 2014-3-20
*
***************************************************************/
#include "NetHookManager.h"
#include <assert.h>

bool CNetHookManager::addHook(INetHook *pHook) {
  assert(pHook != NULL);
  std::pair<NetHookList::iterator, bool> ret;
  ret = m_NetHookList.insert(std::make_pair(pHook->getNetHookType(), pHook));
  return ret.second;
}

void CNetHookManager::delHook(INetHook *pHook) {
  assert(pHook != NULL);
  NetHookList::iterator iter;
  iter = m_NetHookList.find(pHook->getNetHookType());

  if (iter != m_NetHookList.end()) {
    m_NetHookList.erase(iter);
  }
}

CNetHookManager *CNetHookManager::sharedNetHookManager() {
  static CNetHookManager instance;
  return &instance;
}

bool CNetHookManager::onPackageFilter(void *pDataPkg) {
  bool bRet = false;
  NetHookList::const_iterator iter = m_NetHookList.begin();

  for (; iter != m_NetHookList.end(); ++iter) {
    bRet = iter->second->onPackageFilter(pDataPkg);

    if (bRet == false) {
      break;
    }
  }
  return bRet;
}

CNetHookManager::CNetHookManager() {
    
}

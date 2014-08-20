/********************************************************************
	created:	2014/04/02 
	filename: 	DialogManager.h
	author:		王少培
	purpose:	
*********************************************************************/
#include "DialogManager.h"
#include "cocos2d.h"


// bool CDialogManager::showDialogModal(int iDialogIDD, GameLayer_Base* hParent/*=NULL*/) {
//  
//    return true;
// }
// 
bool CDialogManager::hideDialog(int iDialogIDD) {
  DialogDataMap::const_iterator iteFind = mvDialogDataMap.find(iDialogIDD);

  if (iteFind == mvDialogDataMap.end()) {
    return false;
  }
  iteFind->second.pObject->setVisible(false);
  iteFind->second.pObject->onHide();
  return true;
}
// 
bool CDialogManager::hideAllDialogs() {
  return true;
}
void CDialogManager::releaseAllDialog()
{
	for (DialogDataMap::iterator iter = mvDialogDataMap.begin();
		       iter != mvDialogDataMap.end(); ++iter) {
				     SDialogData &data = iter->second;
					 CC_SAFE_RELEASE(data.pObject);
		}
}
bool CDialogManager::onPackageFilter(void *pDataPkg)
{
	DialogDataMap tmpDlgMap = mvDialogDataMap;
	bool bRet = false;
	DialogDataMap::const_iterator iter = tmpDlgMap.begin();

	for (; iter != tmpDlgMap.end(); ++iter) {
		GameLayer_Base* pObj = iter->second.pObject;
		if (pObj&&pObj->isVisible())
		{
			bRet = pObj->onPackageFilter(pDataPkg);
		}
	}
	return true;
}
void CDialogManager::releaseDialog(int iDialogIDD)
{
	DialogDataMap::iterator iteFind = mvDialogDataMap.find(iDialogIDD);
	if (iteFind != mvDialogDataMap.end()){
		CC_SAFE_RELEASE(iteFind->second.pObject);
        if(iteFind->second.pObject->getParent())
            iteFind->second.pObject->removeFromParent();
		mvDialogDataMap.erase(iteFind);
	}
}
unsigned long CDialogManager::sendDialogMessge(int iDialogIDD, int message, unsigned int wParam, long lParam, GameLayer_Base* hParent /*= NULL*/) {
  return 0;
}
 

DialogDataMap CDialogManager::mvDialogDataMap;

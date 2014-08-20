
#ifndef __DIALOG_MANAGER_H__
#define __DIALOG_MANAGER_H__
#include "GameLayer_Base.h"

class CTCBaseDialog;

struct SDialogData{
	GameLayer_Base* pObject;
};
typedef std::map<int,SDialogData> DialogDataMap;

class CDialogManager
{
public:
	//显示窗口
	template< class T>
 	static T* showDialog(CCNode* pParent=NULL,int nZOrder = 0)
	{
		if (pParent&&!pParent->isRunning())
			return NULL;
		auto dlg =CDialogManager::getDialogObject<T>(T::getDialogIDD()) /*GetDlgPtr(T)*/;
		if(!dlg) 
			return NULL;
		if(pParent){
			if(dlg->getParent())
				return NULL;
			if(!pParent->getChildren()->containsObject(dlg))
				pParent->addChild(dlg,nZOrder);
		}
		dlg->setVisible(true);
		dlg->onShow();
		return dlg;
	}
	//
 	//static bool showDialogModal(int iDialogIDD, GameLayer_Base* hParent=NULL);
	//隐藏窗口
 	static bool hideDialog(int iDialogIDD);
	//隐藏所有窗口
 	static bool hideAllDialogs();
	//释放所有窗口
	static void releaseAllDialog();
	//
	static unsigned long sendDialogMessge(int iDialogIDD, int message, unsigned int wParam, long lParam, GameLayer_Base* hParent = NULL);
	//网络消息包过滤
	static bool onPackageFilter(void *pDataPkg);
	//减引用
	static void releaseDialog(int iDialogIDD);
	//
	template< class T>
	static T* getDialogObject(int iDialogIDD, GameLayer_Base* hParent=NULL){
		T *pObject = NULL;
		DialogDataMap::const_iterator iteFind = mvDialogDataMap.find(iDialogIDD);
		if (iteFind == mvDialogDataMap.end()) {
			SDialogData data;
			data.pObject = (GameLayer_Base *)T::create();
			data.pObject->retain();
			mvDialogDataMap.insert(std::make_pair(iDialogIDD, data));
			pObject = dynamic_cast<T*>(data.pObject);
			//pObject->setVisible(false);
		} else {
			pObject = dynamic_cast<T*>(iteFind->second.pObject);
		}
		return pObject;
	}
public:
	//
	static DialogDataMap& getDialogDataMap(){return mvDialogDataMap;}
private:
	
	static DialogDataMap mvDialogDataMap;
};

#define GetDlgPtr(DlgCls) 	 CDialogManager::getDialogObject<DlgCls>(DlgCls::getDialogIDD())
//#define GET_DLG_PTR_EX_PAR(DlgCls) 	static_cast<DlgCls*>(CDialogManager::GetDialogObject(DlgCls::getDialogIDD(),GetHandle()))
#define ShowDlg(DlgCls,pParent,zorder) CDialogManager::showDialog<DlgCls>(pParent,zorder)
#define HideDlg(DlgCls) CDialogManager::hideDialog(DlgCls::getDialogIDD())
#define ReleaseDlg(DlgCls) CDialogManager::releaseDialog(DlgCls::getDialogIDD())
//#define SHOW_DLG_EX_PAR(DlgCls) CDialogManager::ShowDialog(DlgCls::getDialogIDD(),GetHandle())
//#define HIDE_DLG_EX(DlgCls) CDialogManager::HideDialog(DlgCls::getDialogIDD())

#endif
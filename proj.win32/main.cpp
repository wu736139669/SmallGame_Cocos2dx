#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#ifdef _WIN32
//#include "vld.h"
#endif
#include "DialogManager.h"
USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("HelloCpp");
	eglView->setFrameSize(640,960);
    //eglView->setFrameSize(640, 1136);
	int n = CCApplication::sharedApplication()->run();
	CDialogManager::releaseAllDialog();
    return n;
}

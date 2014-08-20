/***************************************************************
* 
*
*  作者：   王少培
*  文件名：   
*  创建时间： 2014-3-20
*
***************************************************************/
#ifndef _AudioHelper_H_
#define _AudioHelper_H_
using namespace std;

class CAudioHelper
{
public:
	//播放声音
	static int playSound(int nSoundType,bool bLoop = false);
	//播放背景声音
	static bool playBackgroundSound(int nSoundType, bool bLoop = true);
	//背景声音停止
	static bool stopBackgroundSound();
};

#endif
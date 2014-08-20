#ifndef _Mask_h
#define _Mask_h

class CBitMask
{
public:
	CBitMask():mnMask(0x00000000)
	{}
	~CBitMask(){}
public:
	//设置位
	void setMask(int nMask);
	void setMask(short sHi, short sLow);
	//检测位
	bool isMask(int nMask);
	//清空位
	void clrMask();
	//移除某位
	void removeMask(int nMask);
	//取得高位
	int getMaskHi();
	//取得低位
	int getMaskLow();
	//取得位
	inline int getMask() const;
protected:
	//32位标志
	int mnMask;
};

#endif
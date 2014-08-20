#include "Mask.h"

void CBitMask::setMask(int nMask)
{
	mnMask |= nMask;
}
void CBitMask::setMask(short sHi, short sLow)
{
	mnMask = (sHi << 16) + sLow;
}

bool CBitMask::isMask(int nMask)
{
	bool b = ((mnMask&nMask) == nMask);
	if(b)
		return true;
	return false;
}
void CBitMask::removeMask(int nMask)
{
	/*	^运算

		  11111111
		^ 00001000
		------------
		  11110111
	*/
	int nTemp = (0xffffffff) ^ nMask;
	mnMask &= nTemp;
}
void CBitMask::clrMask()
{
	mnMask &= ~mnMask;
}
inline int CBitMask::getMask() const
{
	return mnMask;
}
int CBitMask::getMaskHi()
{
	return mnMask >> 16;
}
int CBitMask::getMaskLow()
{
	return mnMask & 0x0000ffff;
}
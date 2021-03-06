//
// GameNewLinkerMaps.h
// OnceAgain
//
// Created by xiaohai on 14-5-19.
//
//

#ifndef __OnceAgain__GameNewLinkerMaps__
#define __OnceAgain__GameNewLinkerMaps__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

static int imgBompMap[1][25] = {
    {
		1 , 2 , 3 , 4 , 5 ,
		10 , 20 , 30 , 40 , 50 ,
		10 , 20 , 30 , 40 , 50 ,
		10 , 20 , 30 , 40 , 50 ,
		1 , 2 , 3 , 4 , 5
	}
};
static int imgBompMap_Big[1][36] = {
    {
		1 , 2 , 3 , 4 , 5 , 6 ,
		10 , 20 , 30 , 40 , 50 , 60 ,
		10 , 20 , 30 , 40 , 50 , 60 ,
		10 , 20 , 30 , 40 , 50 , 60 ,
        10 , 20 , 30 , 40 , 50 , 60 ,
		1 , 2 , 3 , 4 , 5 , 6
	}
};

static int imgSimpleMap[5][25] = {
    {
		1 , 2 , 1 , 3 , 4 ,
		10 , 20 , 10 , 30 , 40 ,
		10 , 20 , 10 , 30 , 40 ,
		10 , 2 , 10 , 30 , 40 ,
		10 , 10 , 10 , 3 , 4
	},
    {
		1 , 0 , 20 , 20 , 2 ,
		10 , 0 , 20 , 3 , 4 ,
		10 , 0 , 20 , 30 , 40 ,
		10 , 0 , 2 , 3 , 40 ,
		10 , 10 , 10 , 1 , 4
	},
    {
		10 , 1 , 3 , 30 , 30 ,
		10 , 2 , 20 , 4 , 30 ,
		10 , 1 , 20 , 40 , 30 ,
		2 , 20 , 20 , 40 , 30 ,
        4 , 40 , 40 , 40 , 3
	},
    {
        10 , 1 , 2 , 20 , 20 ,
        10 , 3 , 4 , 5 , 20 ,
        10 , 30 , 40 , 50 , 20 ,
        10 , 30 , 40 , 5 , 20 ,
        1 , 3 , 40 , 4 , 2
    },
    {
        2 , 30 , 30 , 30 , 3 ,
        20 , 30 , 40 , 40 , 40 ,
        20 , 3 , 4 , 1 , 40 ,
        20 , 20 , 2 , 10 , 40 ,
        1 , 10 , 10 , 10 , 4
	}
};

static int imgBigMap[7][36] = {
    {
		10 , 1 , 30 , 3 , 4 , 5 ,
		10 , 2 , 30 , 40 , 40 , 50 ,
		10 , 20 , 30 , 40 , 50 , 50 ,
		10 , 20 , 30 , 4 , 50 , 6 ,
		1 , 2 , 3 , 5 , 50 , 60 ,
        6 , 60 , 60 , 60 , 60 , 60 ,
	},
    {
		1 , 10 , 10 , 10 , 10 , 10 ,
		20 , 20 , 20 , 20 , 2 , 10 ,
		20 , 30 , 30 , 30 , 3 , 1 ,
		2 , 3 , 40 , 4 , 5 , 6 ,
		4 , 40 , 40 , 50 , 50 , 60 ,
        5 , 50 , 50 , 50 , 6 , 60 ,
	},
    {
		1 , 20 , 20 , 2 , 3 , 4 ,
		10 , 20 , 30 , 30 , 30 , 40 ,
		10 , 20 , 30 , 5 , 50 , 40 ,
		1 , 2 , 30 , 3 , 50 , 40 ,
		0 , 60 , 60 , 6 , 5 , 40 ,
        0 , 6 , 4 , 40 , 40 , 40 ,
	},
    {
		20 , 20 , 20 , 3 , 4 , 40 ,
		20 , 1 , 2 , 30 , 5 , 40 ,
		20 , 10 , 0 , 3 , 50 , 40 ,
		20 , 10 , 40 , 4 , 50 , 40 ,
		20 , 10 , 40 , 5 , 50 , 40 ,
        2 , 1 , 40 , 40 , 40 , 40 ,
	},
    {
		20 , 20 , 20 , 20 , 20 , 20 ,
		20 , 50 , 50 , 50 , 50 , 20 ,
		20 , 5 , 4 , 3 , 50 , 20 ,
		2 , 4 , 40 , 30 , 50 , 20 ,
		3 , 30 , 30 , 30 , 5 , 20 ,
        1 , 10 , 10 , 1 , 2 , 20 ,
	},
    {
		4 , 2 , 1 , 10 , 1 , 5 ,
		40 , 20 , 20 , 50 , 50 , 50 ,
		40 , 4 , 20 , 5 , 6 , 60 ,
		6 , 3 , 20 , 20 , 20 , 60 ,
		60 , 30 , 30 , 3 , 2 , 60 ,
        60 , 60 , 60 , 60 , 60 , 60 ,
	},
    {
		50 , 5 , 60 , 60 , 60 , 6 ,
		50 , 60 , 60 , 2 , 3 , 30 ,
		50 , 60 , 5 , 40 , 4 , 30 ,
		50 , 6 , 50 , 40 , 40 , 30 ,
		50 , 50 , 50 , 2 , 4 , 30 ,
        1 , 10 , 1 , 3 , 30 , 30 ,
	}
};

static int imgDifMap[6][25] = {
    {
		2 , 1 , 10 , 10 , 1 ,
		20 , 30 , 30 , 30 , 30 ,
		20 , 3 , 4 , 40 , 30 ,
		20 , 2 , 5 , 40 , 3 ,
		5 , 50 , 50 , 40 , 4
	},
    {
		1 , 10 , 2 , 20 , 20 ,
		3 , 10 , 10 , 1 , 20 ,
		30 , 30 , 30 , 30 , 2 ,
		5 , 4 , 40 , 3 , 4 ,
		50 , 5 , 40 , 40 , 40
	},
    {
		10 , 1 , 20 , 2 , 3 ,
		1 , 4 , 20 , 30 , 30 ,
		40 , 40 , 20 , 30 , 5 ,
		40 , 2 , 20 , 3 , 50 ,
		40 , 4 , 5 , 50 , 50
	},
    {
		1 , 10 , 3 , 4 , 40 ,
		2 , 10 , 30 , 3 , 40 ,
		20 , 10 , 10 , 10 , 4 ,
		2 , 5 , 6 , 1 , 6 ,
		5 , 50 , 60 , 60 , 60
	},
    {
		10 , 10 , 1 , 3 , 30 ,
		1 , 2 , 20 , 20 , 30 ,
		4 , 40 , 4 , 2 , 30 ,
		50 , 50 , 50 , 5 , 30 ,
		5 , 6 , 60 , 6 , 3
	},
    {
		10 , 1 , 3 , 2 , 20 ,
		1 , 4 , 30 , 30 , 2 ,
		40 , 40 , 5 , 30 , 3 ,
		40 , 6 , 50 , 50 , 5 ,
		4 , 60 , 60 , 60 , 6
	}
};

static int imgMidMap[7][25] = {
    {
        20 , 20 , 20 , 20 , 2 ,
        20 , 1 , 10 , 10 , 1 ,
        20 , 3 , 4 , 40 , 4 ,
        20 , 30 , 30 , 30 , 30 ,
        20 , 20 , 20 , 2 , 3
    },
    {
        30 , 30 , 3 , 2 , 1 ,
        30 , 4 , 20 , 20 , 10 ,
        30 , 40 , 2 , 10 , 10 ,
        30 , 4 , 1 , 10 , 3 ,
        30 , 30 , 30 , 30 , 30
    },
    {
        0 , 10 , 10 , 10 , 1 ,
        0 , 1 , 20 , 2 , 4 ,
        20 , 20 , 20 , 3 , 40 ,
        20 , 30 , 30 , 30 , 40 ,
        2 , 3 , 4 , 40 , 40
    },
    {
        10 , 10 , 10 , 1 , 2 ,
        10 , 20 , 20 , 20 , 20 ,
        1 , 20 , 30 , 30 , 30 ,
        2 , 20 , 30 , 4 , 3 ,
        3 , 30 , 30 , 40 , 4
    },
    {
        20 , 20 , 20 , 20 , 2 ,
        20 , 1 , 10 , 1 , 5 ,
        2 , 3 , 40 , 4 , 50 ,
        30 , 30 , 40 , 4 , 50 ,
        3 , 5 , 50 , 50 , 50
    },
    {
        10 , 10 , 10 , 10 , 1 ,
        1 , 2 , 20 , 20 , 20 ,
        3 , 4 , 40 , 40 , 20 ,
        30 , 30 , 3 , 4 , 20 ,
        5 , 50 , 5 , 2 , 20
    },
    {
        10 , 10 , 10 , 10 , 10 ,
        10 , 5 , 4 , 3 , 1 ,
        10 , 50 , 40 , 30 , 3 ,
        10 , 5 , 40 , 4 , 2 ,
        10 , 1 , 2 , 20 , 20
    }
};

static int imgEasyList_l[1][25] = {
    {
        1 , 2 , 3 , 4 , 5 ,
        10 , 20 , 30 , 40 , 50 ,
        10 , 20 , 30 , 40 , 50 ,
        10 , 20 , 30 , 40 , 50 ,
        1 , 2 , 3 , 4 , 5
    }
};

static int imgEasyList_b[1][36] = {
    {
        1 , 2 , 3 , 4 , 5 , 6 ,
        10 , 20 , 30 , 40 , 50 , 60 ,
        10 , 20 , 30 , 40 , 50 , 60 ,
        10 , 20 , 30 , 40 , 50 , 60 ,
        10 , 20 , 30 , 40 , 50 , 60 ,
        1 , 2 , 3 , 4 , 5 , 6
        }
};

class GameNewLinkerMaps
{
public:
    static std::vector<int> getMapByPoints(int Points);
    static std::vector<int> getBoomMap(int Points);
    static std::vector<int> getEasyListMap(int Points);
};

#endif /* defined(__OnceAgain__GameNewLinkerMaps__) */
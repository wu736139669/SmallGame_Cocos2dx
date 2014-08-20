//
// GameNewLinkerMaps.cpp
// OnceAgain
//
// Created by xiaohai on 14-5-19.
//
//

#include "GameNewLinkerMaps.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#define myRand arc4random()

#else

#define myRand rand()

#endif
std::vector<int> GameNewLinkerMaps::getMapByPoints(int count) {
    std::vector<int>list;
    if (count <= 5) {
        int index = myRand%5;
        list.insert(list.end(), imgSimpleMap[index], imgSimpleMap[index] + 25);
    }
    else if (count <= 10) {
        int index = myRand%12;
        if (index < 5) {
            list.insert(list.end(), imgSimpleMap[index], imgSimpleMap[index] + 25);
        }
        else {
            index = index - 5;
            list.insert(list.end(), imgMidMap[index], imgMidMap[index] + 25);
        }
    }
    else if (count <= 15) {
        int index = myRand%7;
        list.insert(list.end(), imgMidMap[index], imgMidMap[index] + 25);
    }
    else if (count <= 20) {
        int index = myRand%13;
        if (index < 7) {
            list.insert(list.end(), imgMidMap[index], imgMidMap[index] + 25);
        }
        else {
            index = index - 7;
            list.insert(list.end(), imgDifMap[index], imgDifMap[index] + 25);
        }
    }
    else if (count <= 25) {
        int index = myRand%6;
        list.insert(list.end(), imgDifMap[index], imgDifMap[index] + 25);
    }
    else {
        int index = myRand%7;
        list.insert(list.end(), imgBigMap[index], imgBigMap[index] + 36);
    }
    return list;
}

std::vector<int> GameNewLinkerMaps::getBoomMap(int Points) {
    std::vector<int>list;
    if (Points <= 25) {
        list.insert(list.end(), imgBompMap[0], imgBompMap[0] + 25);
    }
    else {
        list.insert(list.end(), imgBompMap_Big[0], imgBompMap_Big[0] + 36);
    }
    return list;
}

std::vector<int> GameNewLinkerMaps::getEasyListMap(int Points) {
    std::vector<int>list;
    if (Points <= 25) {
        list.insert(list.end(), imgEasyList_l[0], imgEasyList_l[0] + 25);
    }
    else {
        list.insert(list.end(), imgEasyList_b[0], imgEasyList_b[0] + 36);
    }
    return list;

}

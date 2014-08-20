//
//  SanXiaoRuleController.cpp
//  OnceAgain
//
//  Created by xiaoqiang on 14-6-16.
//
//

#include "SanXiaoRuleController.h"

std::vector<ItemBox> SanXiaoRuleController::refreshItemBoxWithDoMove(std::vector<ItemBox>b) {
    countBy3 = 0;
    countBy4 = 0;
    countBy5 = 0;
    hengCount = 0;
    zongCount = 0;
    for (int i = 0; i < 7; i ++) {
        //检查每行
        std::vector<ItemBox>l1;
        for (int j = 0; j < b.size(); j ++) {
            if (i != 6 && b[j].number >= i * 7 && b[j].number < (i + 1) * 7) {
                l1.push_back(b[j]);
            }
            if (i == 6 && b[j].number > 41) {
                l1.push_back(b[j]);
            }
        }
        std::vector<int>wellBeD = wellBeDelItems(l1, 1);
        
        for (int j = 0; j < wellBeD.size(); j ++) {
            for (int k = 0; k < b.size(); k ++) {
                if (b[k].number == wellBeD[j]) {
                    b[k].wellRemove = true;
                }
            }
        }
        l1.clear();
    }
    for (int i = 0; i < 7; i ++) {
        //检查每列
        std::vector<ItemBox>l1;
        for (int j = 0; j< 7; j ++) {
            for (int k = 0; k < b.size(); k ++) {
                if (b[k].number == i + j *7) {
                    l1.push_back(b[k]);
                }
            }
        }
        std::vector<int>wellBeD = wellBeDelItems(l1, 2);
        
        for (int j = 0; j < wellBeD.size(); j ++) {
            for (int k = 0; k < b.size(); k ++) {
                if (b[k].number == wellBeD[j]) {
                    b[k].wellRemove = true;
                }
            }
        }
        l1.clear();
    }
    countBy3 = (countBy3 - countBy4 - countBy5);
    return b;
}
std::vector<int> SanXiaoRuleController::wellBeDelItems(std::vector<ItemBox>box, int kind) {
    std::vector<int> numbersBeD;
    int addCount = kind == 1 ? 1 :7;
        std::vector<int>numberKinds;
        //获取这一行所拥有的所有种类
        for (int i = 0; i < box.size(); i ++) {
            bool wellPush = true;
            for (int j = 0; j < numberKinds.size(); j ++) {
                if (numberKinds[j] == box[i].type) {
                    wellPush = false;
                }
            }
            if (wellPush) {
                numberKinds.push_back(box[i].type);
            }
        }
        //对每一个种类进行检索，是否连续大于3个
        for (int i = 0; i < numberKinds.size(); i ++) {
            for (int j = 0; j < box.size(); j ++) {
                if (box[j].type == numberKinds[i]) {
                    int theBenginIndex = box[j].number;
                    int count1= 0;
                    int mis = theBenginIndex;
                    while (1) {
                        bool wellBreak = true;
                        for (int k = 0; k < box.size(); k ++) {
                            if (box[k].number == mis && box[k].type == numberKinds[i]) {
                                count1 ++;
                                wellBreak = false;
                                mis += addCount;
                            }
                        }
                        if (wellBreak) {
                            break;
                        }
                    }
                    mis = theBenginIndex;
                    if (count1 >= 5) {
                        countBy5 ++;
                    }
                    if (count1 == 4) {
                        countBy4 ++;
                    }
                    if (count1 >= 3) {
                        bool have = false;
                        for (int n = 0; n < numbersBeD.size(); n ++) {
                            if (numberKinds[n] == theBenginIndex) {
                                have = true;
                            }
                        }
                        if (!have) {
                            if (kind == 1) {
                                hengCount ++;
                            }
                            else {
                                zongCount ++;
                            }
                            countBy3++;
                        }
                        while (1) {
                            bool wellBreak = true;
                            for (int k = 0; k < box.size(); k ++) {
                                if (box[k].number == mis && box[k].type == numberKinds[i]) {
                                    numbersBeD.push_back(box[k].number);
                                    wellBreak = false;
                                    mis += addCount;
                                }
                            }
                            if (wellBreak) {
                                break;
                            }
                        }
                    }
                }
            }
        }
    return numbersBeD;
}

std::vector<ItemBox> SanXiaoRuleController::refreshItemBoxWithClickBoom(std::vector<ItemBox>box, int boomIndex) {
   
    std::vector<ItemBox>b1;
    int n1;
    for (int i = 0; i <= 42; i += 7) {
        if (boomIndex - i >= 0 && boomIndex - i < 7) {
            n1 = i;
        }
    }
    for (int i = 0 ; i < box.size(); i ++) {
        if (box[i].number >= n1 && box[i].number < (n1 + 7)) {
            b1.push_back(box[i]);
        }
    }
    for (int i = 0; i < b1.size(); i ++) {
        if (b1[i].number == boomIndex - 1 || b1[i].number == boomIndex + 1 || b1[i].number == boomIndex) {
            b1[i].wellRemove = true;
        }
    }
    for (int i = 0; i < b1.size(); i ++) {
        for (int j = 0; j < box.size(); j ++) {
            if (box[j].number == b1[i].number) {
                box[j] = b1[i];
            }
        }
    }
    
    if (n1 - 7 >= 0) {
        std::vector<ItemBox>b2;
        for (int i = 0 ; i < box.size(); i ++) {
            if (box[i].number >= (n1 - 7) && box[i].number < n1) {
                b2.push_back(box[i]);
            }
        }
        for (int i = 0; i < b2.size(); i ++) {
            if (b2[i].number == boomIndex - 8 || b2[i].number == boomIndex - 6 || b2[i].number == boomIndex - 7) {
                b2[i].wellRemove = true;
            }
        }
        for (int i = 0; i < b2.size(); i ++) {
            for (int j = 0; j < box.size(); j ++) {
                if (box[j].number == b2[i].number) {
                    box[j] = b2[i];
                }
            }
        }
    }
    if (n1 + 7 < 49) {
        std::vector<ItemBox>b2;
        for (int i = 0 ; i < box.size(); i ++) {
            if (box[i].number >= (n1 + 7) && box[i].number < n1 + 14) {
                b2.push_back(box[i]);
            }
        }
        for (int i = 0; i < b2.size(); i ++) {
            if (b2[i].number == boomIndex + 8 || b2[i].number == boomIndex + 6 || b2[i].number == boomIndex + 7) {
                b2[i].wellRemove = true;
            }
        }
        for (int i = 0; i < b2.size(); i ++) {
            for (int j = 0; j < box.size(); j ++) {
                if (box[j].number == b2[i].number) {
                    box[j] = b2[i];
                }
            }
        }
    }
    
    return box;
}

std::vector<ItemBox> SanXiaoRuleController::refreshItemBoxWithHengCross(std::vector<ItemBox>box, int boomIndex) {
    std::vector<ItemBox>list;
    int n1;
    for (int i = 0; i <= 42; i += 7) {
        if (boomIndex - i >= 0 && boomIndex - i < 7) {
            n1 = i;
        }
    }
    for (int i = 0; i < box.size(); i ++) {
        if (box[i].number >= n1 && box[i].number < n1 + 7) {
            list.push_back(box[i]);
        }
    }
    for (int i = 0; i < list.size(); i ++) {
        list[i].wellRemove = true;
        if (list[i].number != boomIndex && list[i].type == heng_Cross) {
            for (int j = 0; j < box.size(); j ++) {
                if (box[j].number == boomIndex) {
                    box[j].type = 0;
                }
            }
            box = refreshItemBoxWithHengCross(box, list[i].number);
        }
        if (list[i].number != boomIndex && list[i].type == zong_Cross) {
            for (int j = 0; j < box.size(); j ++) {
                if (box[j].number == boomIndex) {
                    box[j].type = 0;
                }
            }
            box = refreshItemBoxWithZongCross(box, list[i].number);
        }
        if (list[i].type == threeCross && list[i].number != boomIndex) {
            for (int j = 0; j < box.size(); j ++) {
                if (box[j].number == boomIndex) {
                    box[j].type = 0;
                }
            }
            refreshItemBoxWithThreeCross(box, list[i].number);
        }

    }
    for (int i = 0; i < list.size(); i ++) {
        for (int j = 0; j < box.size(); j ++) {
            if (box[j].number == list[i].number) {
                box[j] = list[i];
            }
        }
    }
    return box;
}

std::vector<ItemBox> SanXiaoRuleController::refreshItemBoxWithZongCross(std::vector<ItemBox>box, int boomIndex) {
    std::vector<ItemBox>list;
    int n1;
    for (int i = 0; i <= 6; i ++) {
        if ((boomIndex - i) %7 == 0) {
            n1 = i;
        }
    }
    for (int i = 0; i < box.size(); i ++) {
        if ((box[i].number - n1) % 7 == 0) {
            list.push_back(box[i]);
        }
    }
    for (int i = 0; i < list.size(); i ++) {
        list[i].wellRemove = true;
        if (list[i].number != boomIndex && list[i].type == heng_Cross) {
            for (int j = 0; j < box.size(); j ++) {
                if (box[j].number == boomIndex) {
                    box[j].type = 0;
                }
            }
            box = refreshItemBoxWithHengCross(box, list[i].number);
        }
        if (list[i].number != boomIndex && list[i].type == zong_Cross) {
            for (int j = 0; j < box.size(); j ++) {
                if (box[j].number == boomIndex) {
                    box[j].type = 0;
                }
            }
            box = refreshItemBoxWithZongCross(box, list[i].number);
        }
        if (list[i].type == threeCross && list[i].number != boomIndex) {
            for (int j = 0; j < box.size(); j ++) {
                if (box[j].number == boomIndex) {
                    box[j].type = 0;
                }
            }
            refreshItemBoxWithThreeCross(box, list[i].number);
        }

    }
    for (int i = 0; i < list.size(); i ++) {
        for (int j = 0; j < box.size(); j ++) {
            if (box[j].number == list[i].number) {
                box[j] = list[i];
            }
        }
    }
    return box;

}

std::vector<ItemBox> SanXiaoRuleController::refreshItemBoxWithThreeCross(std::vector<ItemBox>box, int boomIndex) {
    std::vector<ItemBox>list;
    std::vector<int>listNumber;
    int n1;
    for (int i = 0; i <= 42; i += 7) {
        if (boomIndex - i >= 0 && boomIndex - i < 7) {
            n1 = i;
        }
    }
    if (n1 < 7) {
        listNumber.push_back(0);
        listNumber.push_back(7);
        listNumber.push_back(14);
    }
    else if (n1 > 41) {
        listNumber.push_back(42);
        listNumber.push_back(35);
        listNumber.push_back(28);
    }
    else {
        listNumber.push_back(n1);
        listNumber.push_back(n1 + 7);
        listNumber.push_back(n1 - 7);
    }
    for (int i = 0; i < listNumber.size(); i ++) {
        for (int j = 0; j < box.size(); j ++) {
            if (box[j].number >= listNumber[i] && box[j].number < listNumber[i] + 7) {
                list.push_back(box[j]);
            }
        }
    }
    for (int i = 0; i < list.size(); i ++) {
        list[i].wellRemove = true;
        if (list[i].type == heng_Cross) {
            for (int j = 0; j < box.size(); j ++) {
                if (box[j].number == boomIndex) {
                    box[j].type = 0;
                }
            }
            box = refreshItemBoxWithHengCross(box, list[i].number);
        }
        if (list[i].type == zong_Cross) {
            for (int j = 0; j < box.size(); j ++) {
                if (box[j].number == boomIndex) {
                    box[j].type = 0;
                }
            }
            box = refreshItemBoxWithZongCross(box, list[i].number);
        }
        if (list[i].type == threeCross && list[i].number != boomIndex) {
            for (int j = 0; j < box.size(); j ++) {
                if (box[j].number == boomIndex) {
                    box[j].type = 0;
                }
            }
            refreshItemBoxWithThreeCross(box, list[i].number);
        }
    }
    for (int i = 0; i < list.size(); i ++) {
        for (int j = 0; j < box.size(); j ++) {
            if (list[i].number == box[j].number) {
                box[j] = list[i];
            }
        }
    }
    return box;
}
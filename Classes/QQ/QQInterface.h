//
//  QQInterface.h
//  yueyue
//  QQ空间及QQSDK接口
//  Created by chw on 13-11-19.
//  Copyright (c) 2013年 WSH. All rights reserved.
//


//#import "cocos2d.h"

class QQInterface {
    
    
public:
    static QQInterface* shareInstant(void);
    void login();
private:
    QQInterface(){};
    ~QQInterface();
    
    static QQInterface* m_Instant;
};
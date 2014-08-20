//
//  QQInterface.m
//  yueyue
//
//  Created by chw on 13-7-3.
//  Copyright (c) 2013年 chw. All rights reserved.
//

#import "QQInterface.h"
#import "QQInterface_Objc.h"

QQInterface*  QQInterface::m_Instant = NULL;


QQInterface* QQInterface::shareInstant()
{
    if (m_Instant == NULL) {
        m_Instant = new QQInterface();
    }
    return m_Instant;
}

QQInterface::~QQInterface()
{
    delete m_Instant;
    m_Instant = NULL;
}

void QQInterface::login()
{
    [[QQInterface_Objc shareInstance] login];
}
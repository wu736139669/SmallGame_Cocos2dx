//
//  SinaInterface.m
//  OnceAgain
//
//  Created by mac on 14-3-31.
//
//

#import "SinaInterface.h"
#import "SinaInterface_Objc.h"
SinaInterface*  SinaInterface::m_Instant = NULL;


SinaInterface* SinaInterface::shareInstant()
{
    if (m_Instant == NULL) {
        m_Instant = new SinaInterface();
    }
    return m_Instant;
}

SinaInterface::~SinaInterface()
{
    delete m_Instant;
    m_Instant = NULL;
}

void SinaInterface::login()
{
    [[SinaInterface_Objc shareInstance] login];
}
void SinaInterface::getFriend()
{
    [[SinaInterface_Objc shareInstance] getFriend];
}
void SinaInterface::inviteFriend(const char *uid)
{
    [[SinaInterface_Objc shareInstance] inviteUser:uid];
}
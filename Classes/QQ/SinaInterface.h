//
//  SinaInterface.h
//  OnceAgain
//
//  Created by mac on 14-3-31.
//
//


class SinaInterface {
    
    
public:
    static SinaInterface* shareInstant(void);
    
    void login();
    void getFriend();
    void inviteFriend(const char* uid);
private:
    SinaInterface(){};
    ~SinaInterface();
    
    static SinaInterface* m_Instant;
};

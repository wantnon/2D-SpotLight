

#ifndef __HelloCpp__maskedSceneSprite__
#define __HelloCpp__maskedSceneSprite__

#include <iostream>
#include "cocos2d.h"
#include "GLProgramWithMyUnifos.h"
using namespace cocos2d;
class CmaskedSceneSprite:public CCSprite
{
public:
    CmaskedSceneSprite(){
        r=200;
        CCSize winSize=CCDirector::sharedDirector()->getWinSize();
        c=CCPoint(winSize.width/2,winSize.height/2);
        brightColor[0]=3,brightColor[1]=3,brightColor[2]=3,brightColor[3]=1;
        darkColor[0]=0.5,darkColor[1]=0.5,darkColor[2]=0.5,darkColor[3]=1;
    }
    virtual ~CmaskedSceneSprite(){
    
    }
    void draw();
    bool init(CCTexture2D*texture);
    CGLProgramWithMyUnifos program;
    float r;
    CCPoint c;
    float brightColor[4];
    float darkColor[4];
    
};
#endif /* defined(__HelloCpp__maskedSceneSprite__) */

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "myDef.h"
#include "GLProgramWithMyUnifos.h"
#include "maskedSceneSprite.h"
using namespace cocos2d;
using namespace cocos2d::extension;
class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
public:
    HelloWorld(){
        renderTex=new CCRenderTexture();
        maskedSceneSprite=new CmaskedSceneSprite();
     
    }
    virtual ~HelloWorld(){
        renderTex->release();
        maskedSceneSprite->release();
    
    }
public:
    void visit();
    CmaskedSceneSprite* maskedSceneSprite;
    CCRenderTexture*renderTex;
public:
    CCNode* sceneRoot;
    CCNode* uiRoot;

public:
    //touch
	virtual void ccTouchesBegan(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
	virtual void ccTouchesMoved(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
	virtual void ccTouchesEnded(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
public:
    //slider
    CCControlSlider* m_pSliderCtl;
    void sliderAction(CCObject* sender, CCControlEvent controlEvent);
	//slider2
	CCControlSlider* m_pSliderCtl2;
    void sliderAction2(CCObject* sender, CCControlEvent controlEvent);
    //slider3
	CCControlSlider* m_pSliderCtl3;
    void sliderAction3(CCObject* sender, CCControlEvent controlEvent);
public:

};

#endif // __HELLOWORLD_SCENE_H__

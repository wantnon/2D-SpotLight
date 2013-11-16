#include "HelloWorldScene.h"
#include "AppMacros.h"
USING_NS_CC;
#include "CCControlButton.h"
using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

 /*   /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
*/
    /////////////////////////////
    // 3. add your codes below...
    //enable touch
	setTouchEnabled( true );
    //set projection to 2D (default is 3D). if use 3D projection, may cause tiny projection error, in some situation, if the error accumulated across frames, may cause effect wrong.
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
    //sinSize
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();//winSize equals to designResolutionSize
    //show frame rate info
    CCDirector::sharedDirector()->setDisplayStats(true);
    
    
    //sceneRoot
    sceneRoot=CCNode::create();
    addChild(sceneRoot);
    //uiRoot
    uiRoot=CCNode::create();
    addChild(uiRoot);
    //scene
    CCSprite* backGroundSprite=CCSprite::create();
    backGroundSprite->initWithFile("HelloWorld_iphone5.png");
    backGroundSprite->setAnchorPoint(ccp(0.5, 0.5));
    backGroundSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
    sceneRoot->addChild(backGroundSprite,1);
    //animation
    CCSprite*sprite=CCSprite::create();
    sprite->initWithFile("actor_fish_shayu_normal_001.png");
    sprite->setPosition(ccp(winSize.width/2,winSize.height/2));
    sceneRoot->addChild(sprite,2);
    CCArray* spriteFrames=CCArray::create();
    const int frameCount=29;
    for(int i=0;i<frameCount;i++){
        char fileName[1024];
        int picIndex=i+1;
        CCAssert(picIndex<100, "i must small than 100");
        if(picIndex>9){//i is two-digit number
            sprintf(fileName, "actor_fish_shayu_normal_0%i.png",picIndex);
        }else{//i is one-digit number
            sprintf(fileName, "actor_fish_shayu_normal_00%i.png",picIndex);
        }
        CCTexture2D*texture=CCTextureCache::sharedTextureCache()->addImage(fileName);
        CCSpriteFrame*spriteFrame=CCSpriteFrame::createWithTexture(texture, CCRect(0,0,texture->getContentSize().width,texture->getContentSize().height));
        spriteFrames->addObject(spriteFrame);
    }//get spriteFrames
    CCAnimation*animation=CCAnimation::createWithSpriteFrames(spriteFrames, 0.1);
    sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
    
    
    //maskedSceneSprit (do not add to sceneTree)
    maskedSceneSprite->init(backGroundSprite->getTexture());
    maskedSceneSprite->setAnchorPoint(ccp(0.5,0.5));
    maskedSceneSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
    //renderTex (do not add to sceneTree)
    renderTex->initWithWidthAndHeight(winSize.width, winSize.height, kCCTexture2DPixelFormat_Default);
    
    //slider
	{
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
		slider->setAnchorPoint(ccp(0.5f, 0.5f));
		slider->setMinimumValue(0.0f); // Sets the min value of range
		slider->setMaximumValue(maskedSceneSprite->r*2); // Sets the max value of range
		slider->setValue(maskedSceneSprite->r);
		slider->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 4.0f));
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction), CCControlEventValueChanged);
		m_pSliderCtl=slider;
		uiRoot->addChild(m_pSliderCtl,100);
		//title
		CCLabelTTF* pLabel = CCLabelTTF::create("R ", "Arial", 30);
		pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        uiRoot->addChild(pLabel, 1);
	}
	//slider2
    {
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
		slider->setAnchorPoint(ccp(0.5f, 0.5f));
		slider->setMinimumValue(0.0f); // Sets the min value of range
		slider->setMaximumValue(maskedSceneSprite->brightColor[0]*2); // Sets the max value of range
		slider->setValue(maskedSceneSprite->brightColor[0]);
		slider->setPosition(m_pSliderCtl->getPosition()+ccp(0,-m_pSliderCtl->getContentSize().height));
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction2), CCControlEventValueChanged);
		m_pSliderCtl2=slider;
		uiRoot->addChild(m_pSliderCtl2,100);
		//title
		CCLabelTTF* pLabel = CCLabelTTF::create("brightness ", "Arial", 30);
		pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        uiRoot->addChild(pLabel, 1);
	}
    //slider3
    {
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
		slider->setAnchorPoint(ccp(0.5f, 0.5f));
		slider->setMinimumValue(0.0f); // Sets the min value of range
		slider->setMaximumValue(maskedSceneSprite->darkColor[0]*2); // Sets the max value of range
		slider->setValue(maskedSceneSprite->darkColor[0]);
		slider->setPosition(m_pSliderCtl2->getPosition()+ccp(0,-m_pSliderCtl2->getContentSize().height));
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction3), CCControlEventValueChanged);
		m_pSliderCtl3=slider;
		uiRoot->addChild(m_pSliderCtl3,100);
		//title
		CCLabelTTF* pLabel = CCLabelTTF::create("darkness ", "Arial", 30);
		pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        uiRoot->addChild(pLabel, 1);
	}

  
    
    // author info
    {
        CCLabelTTF* pLabel = CCLabelTTF::create("by yang chao (wantnon) 2013-11-16", "Arial", 30);
        pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - pLabel->getContentSize().height-60));
        uiRoot->addChild(pLabel, 1);
    }
    
    // add a label shows "Hello World"
    // create and initialize a label
 
    CCLabelTTF* pLabel = CCLabelTTF::create("2D SpotLight Demo", "Arial", 45);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    uiRoot->addChild(pLabel, 1);
  
    
   
    
    return true;
}
void HelloWorld::visit(){
    //render sceneRoot to texture
    renderTex->begin();
    sceneRoot->visit();
    renderTex->end();
    //use renderTex's texture as maskedSceneSprite's texture
    maskedSceneSprite->setTexture(renderTex->getSprite()->getTexture());
    //visit interested things manually
    maskedSceneSprite->visit();
    uiRoot->visit();
    

}
void HelloWorld::sliderAction(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    CCLOG("slider value:%f",value);
    maskedSceneSprite->r=value;
    
}
void HelloWorld::sliderAction2(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    CCLOG("slider value:%f",value);
    maskedSceneSprite->brightColor[0]=value;
    maskedSceneSprite->brightColor[1]=value;
    maskedSceneSprite->brightColor[2]=value;
    
}

void HelloWorld::sliderAction3(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    CCLOG("slider value:%f",value);
    maskedSceneSprite->darkColor[0]=value;
    maskedSceneSprite->darkColor[1]=value;
    maskedSceneSprite->darkColor[2]=value;
    
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}


void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        CCPoint loc_GLSpace = CCDirector::sharedDirector()->convertToGL(loc_winSpace);
        maskedSceneSprite->c=loc_GLSpace;
        
    }
}
void HelloWorld::ccTouchesMoved(cocos2d::CCSet* touches , cocos2d::CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        CCPoint loc_GLSpace = CCDirector::sharedDirector()->convertToGL(loc_winSpace);
        maskedSceneSprite->c=loc_GLSpace;


    
        
		
    }
    
}

void HelloWorld::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
	for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        CCPoint loc_GLSpace = CCDirector::sharedDirector()->convertToGL(loc_winSpace);
        //CCLOG("loc_GLSpace:%f,%f",loc_GLSpace.x,loc_GLSpace.y);
       maskedSceneSprite->c=loc_GLSpace;

        
    }
}


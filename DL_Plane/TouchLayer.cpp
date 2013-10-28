//
//  TouchLayer.cpp
//  DL_Plane
//
//  Created by user on 13-10-22.
//
//

#include "TouchLayer.h"

USING_NS_CC;


bool TouchLayer::init(RunGameScene *scene)
{
    bool ret = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        this->scene = scene;
        
        clicked = false;
        
        this->setTouchEnabled(true);
        
        ret = true;
    } while (0);
    
    return ret;
}

void TouchLayer::registerWithTouchDispatcher()
{
    // param 3: whether to swallow the touch
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}


bool TouchLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    //CCPoint toLocation = CCPointZero;
    CCLog("Touch Began!!");
    //scene->getPlayerLayer()->movePlayer(toLocation);
    if(clicked)
    {
        clicked = false;
        CCLog("double click");
        //double click here~
        if(!CCDirector::sharedDirector()->isPaused())
        {
            scene->removeAllEnemy();
        }
    }
    else
    {
        this->scheduleOnce(schedule_selector(TouchLayer::singleClick), 0.25f);
        clicked = true;
    }
    return true;
}

void TouchLayer::singleClick(float dt)
{
    if(clicked)
    {
        clicked = false;
        CCLog("single click");
    }
}

void TouchLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLog("Moved!");
    scene->getPlayerLayer()->movePlayer(pTouch, pEvent);
}

void TouchLayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
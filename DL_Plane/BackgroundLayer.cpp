//
//  BackgroundLayer.cpp
//  DL_Plane
//
//  Created by user on 13-10-22.
//
//

#include "BackgroundLayer.h"

USING_NS_CC;

BackgroundLayer::BackgroundLayer()
{
    
}

BackgroundLayer::~BackgroundLayer()
{
    
}

bool BackgroundLayer::init(RunGameScene *scene)
{
    bool ret = false;
    
    do {
        //CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CC_BREAK_IF(!CCLayer::init());
        
        this->scene = scene;
        
        this->scheduleUpdate();
        
        background1 = CCSprite::createWithSpriteFrame(
                                CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
        background1->setAnchorPoint(ccp(0, 0));
        background1->setPosition(ccp(0, 0));
        this->addChild(background1);
        
        background2 = CCSprite::createWithSpriteFrame(
                                CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
        background2->setAnchorPoint(ccp(0, 0));
        background2->setPosition(ccp(0, background1->getContentSize().height - 2));
        this->addChild(background2);
        
        autoResize();
        
        ret  = true;
    } while (0);
    
    return ret;
}

void BackgroundLayer::update(float dt)
{
    backgroundMove();
}

void BackgroundLayer::backgroundMove()
{
    //CCLog("background move");
    background1->setPositionY(background1->getPositionY() - 2);
    background2->setPositionY(background1->getPositionY() + background2->getContentSize().height - 2);
    if(background2->getPositionY() == 0)
    {
        background1->setPositionY(0);
    }
}

void BackgroundLayer::autoResize()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float scaleX = winSize.width / background1->getContentSize().width;
    float scaleY = winSize.height / background1->getContentSize().height;
    
    background1->setScaleX(scaleX);
    background1->setScaleY(scaleY);
    
    background2->setScaleX(scaleX);
    background2->setScaleY(scaleY);
}
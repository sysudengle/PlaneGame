//
//  MenuLayer.cpp
//  DL_Plane
//
//  Created by user on 13-10-23.
//
//

#include "MenuLayer.h"

USING_NS_CC;

bool MenuLayer::init(RunGameScene *scene)
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!CCLayer::init());
        
        this->scene = scene;
        
        CCSize winSize=CCDirector::sharedDirector()->getWinSize();
        
        // pause item
        CCSprite *normalPause = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));
        CCSprite* pressedPause=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_pressed.png"));
        pPauseItem = CCMenuItemSprite::create(normalPause, pressedPause, this, menu_selector(MenuLayer::menuPauseCallBack));
        
        pPauseItem->setPosition(ccp(normalPause->getContentSize().width/2 + 10,winSize.height - normalPause->getContentSize().height/2));
        //pPauseItem->setPosition(ccp(100, 100));
        CCMenu *menuPause=CCMenu::create(pPauseItem,NULL);
        menuPause->setPosition(CCPointZero);
        this->addChild(menuPause);
        
        // score label
        scoreLabel = CCLabelBMFont::create("0", "font.fnt");
        scoreLabel->setAnchorPoint(ccp(0, 0.5));
        scoreLabel->setPosition(ccp(normalPause->getContentSize().width + 15, winSize.height - normalPause->getContentSize().height/2));
        this->addChild(scoreLabel);
        
        bRet=true;
    } while (0);
    
    return bRet;
}

void MenuLayer::menuPauseCallBack(CCObject *pSender)
{
    if(!CCDirector::sharedDirector()->isPaused())
    {
        CCSprite *normalPause = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_nor.png"));
        CCSprite* pressedPause=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_pressed.png"));
        pPauseItem->setNormalImage(normalPause);
        pPauseItem->setSelectedImage(pressedPause);
        CCDirector::sharedDirector()->pause();
    }
    else
    {
        CCSprite *normalPause = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));
        CCSprite* pressedPause=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_pressed.png"));
        pPauseItem->setNormalImage(normalPause);
        pPauseItem->setSelectedImage(pressedPause);
        CCDirector::sharedDirector()->pause();
        CCDirector::sharedDirector()->resume();
    }
}

void MenuLayer::scoreDisplay(int score)
{
    // update score
    scoreLabel->setString(CCString::createWithFormat("%d", score)->getCString());
}
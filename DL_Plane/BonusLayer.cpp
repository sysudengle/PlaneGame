//
//  BonusLayer.cpp
//  DL_Plane
//
//  Created by user on 13-10-23.
//
//

#include "BonusLayer.h"

USING_NS_CC;

BonusLayer::BonusLayer()
{
    multiBulletFlag = new char('a');
    bigBombFlag = new char('b');
    bonusList = CCArray::create();
    bonusList->retain();
}

BonusLayer::~BonusLayer()
{
    delete multiBulletFlag;
    delete bigBombFlag;
    bonusList->release();
}

bool BonusLayer::init(RunGameScene *scene)
{
    bool ret = false;
    
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        this->scene = scene;
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        bigBombLogo = CCSprite::createWithSpriteFrame(
                                                CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bomb.png"));
        CCSize logoSize = bigBombLogo->getContentSize();
        bigBombLogo->setPosition(ccp(winSize.width - logoSize.width / 2, winSize.height - logoSize.height / 2));
        //bigBombLogo->setPosition(ccp(100, 100));
        
        bigBombNum = CCLabelTTF::create("0$", "Marker Felt", 40);
        bigBombNum->setPosition(ccp(winSize.width - logoSize.width -  bigBombNum->getContentSize().width / 2,
                                    winSize.height - logoSize.height / 2));
        
        this->addChild(bigBombLogo);
        this->addChild(bigBombNum);
        
        schedule(schedule_selector(BonusLayer::addNewBonus), 3.0f);
        ret  = true;
    } while (0);
    
    return ret;

}

void BonusLayer::bigBombBonusDisplay(int bonusNum)
{
    bigBombNum->setString(CCString::createWithFormat("%d$", bonusNum)->getCString());
    /*if(bonusNum == 0)
    {
        if(this->getChildByTag(bigbomb) != NULL)
        {
            this->removeChild(bigBombLogo);
            this->removeChild(bigBombNum);
        }
    }
    else
    {
        if(this->getChildByTag(bigbomb) == NULL)
        {
            this->addChild(bigBombLogo);
            this->addChild(bigBombNum);
        }
        bigBombNum->setString(CCString::createWithFormat("~%d", bonusNum)->getCString());
    }*/
}

void BonusLayer::addNewBonus(float dt)
{
    int choice = random() % 2;
    CCSprite *bonus = NULL;
    
    switch (choice) {
        case 0:
            bonus = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ufo1.png"));
            bonus->setUserData(this->multiBulletFlag);
            break;
        case 1:
            bonus = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ufo2.png"));
            bonus->setUserData(this->bigBombFlag);
            break;
        default:
            break;
    }
    
    CCSize bonusSize = bonus->getContentSize();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int minX = bonusSize.width/2;
    int maxX = winSize.width-bonusSize.width/2;
    int rangeX = maxX-minX;
    int actualX = (rand()%rangeX)+minX;
    
    bonus->setPosition(ccp(actualX,winSize.height+bonusSize.height/2));
    this->addChild(bonus);
    this->bonusList->addObject(bonus);
    
    setBonusAction(bonus);
}

void BonusLayer::addNewMultiBulletBonus(float dt)
{
    CCSprite* mutiBullets = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ufo1.png"));
    
    CCSize mutiBlletsSize = mutiBullets->getContentSize();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int minX = mutiBlletsSize.width/2;
    int maxX = winSize.width-mutiBlletsSize.width/2;
    int rangeX = maxX-minX;
    int actualX = (rand()%rangeX)+minX;
    
    mutiBullets->setUserData(this->multiBulletFlag);
    mutiBullets->setPosition(ccp(actualX,winSize.height+mutiBlletsSize.height/2));
    this->addChild(mutiBullets);
    this->bonusList->addObject(mutiBullets);
    
    setBonusAction(mutiBullets);
}

void BonusLayer::addNewBigBombBonus(float dt)
{
    
}

void BonusLayer::setBonusAction(CCSprite *bonus)
{
    CCSize bonusSize = bonus->getContentSize();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCMoveBy* move1 = CCMoveBy::create(0.5f, CCPointMake(0, -150));
    CCMoveBy* move2 = CCMoveBy::create(0.3f, CCPointMake(0, 100));
    CCMoveBy* move3 = CCMoveBy::create(1.0f, CCPointMake(0,0-winSize.height-bonusSize.height/2));
    CCCallFuncN* moveDone = CCCallFuncN::create(this,callfuncN_selector(BonusLayer::bonusMoveFinish));
    CCFiniteTimeAction* sequence = CCSequence::create(move1,move2,move3,moveDone,NULL);
    
    bonus->runAction(sequence);
}

void BonusLayer::bonusMoveFinish(CCNode *nBonus)
{
    CCSprite *bonus = (CCSprite *)nBonus;
    removeBonus(bonus);
}

void BonusLayer::removeBonus(CCSprite *bonus)
{
    this->bonusList->removeObject(bonus);
    CCLog("1. bonus reference %d:", bonus->retainCount());
    this->removeChild(bonus, true);
    CCLog("2. bonus reference %d:", bonus->retainCount());
}
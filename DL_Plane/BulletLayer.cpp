//
//  BulletLayer.cpp
//  DL_Plane
//
//  Created by user on 13-10-22.
//
//

#include "BulletLayer.h"

USING_NS_CC;

BulletLayer::BulletLayer()
{
    bulletList = CCArray::create();
    bulletList->retain();
    
    speed = 20;
}

BulletLayer::~BulletLayer()
{
    bulletList->release();
}

bool BulletLayer::init(RunGameScene *scene)
{
    bool ret = false;
    
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        scheduleUpdate();
        
        this->scene = scene;
        
        bulletBatchNode = CCSpriteBatchNode::createWithTexture(
                                                        CCTextureCache::sharedTextureCache()->textureForKey("shoot.png"));
        this->addChild(bulletBatchNode);
        
        this->schedule(schedule_selector(BulletLayer::addNewOneBullet), 0.11f);
        
        ret  = true;
    } while (0);
    
    return ret;

}

void BulletLayer::update(float dt)
{
    bulletMove();
}

void BulletLayer::bulletMove()
{
    CCObject *pObject = NULL;
    CCSprite *bullet = NULL;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCARRAY_FOREACH(bulletList, pObject)
    {
        bullet = (CCSprite *)pObject;
        bullet->setPositionY(bullet->getPositionY() + speed);
        
        if(bullet->getPositionY() > winSize.height)
        {
            bulletMoveEnd(bullet);
        }
    }

}

void BulletLayer::MultiBulletShoot()
{
    this->unschedule(schedule_selector(BulletLayer::addNewOneBullet));
    this->schedule(schedule_selector(BulletLayer::addMultiBullet), 0.11f);
    this->scheduleOnce(schedule_selector(BulletLayer::changeToOneBullet), 5.0f);
}

void BulletLayer::stopShoot()
{
    this->unschedule(schedule_selector(BulletLayer::addNewOneBullet));
    this->unschedule(schedule_selector(BulletLayer::addMultiBullet));
//    this->removeAllChildren();
//    this->unscheduleAllSelectors();
}

void BulletLayer::addNewOneBullet(float dt)
{
    CCSprite *bullet = CCSprite::createWithSpriteFrameName("bullet1.png");
    CCPoint point = scene->getPlayerLocation();
    
    bullet->setPosition(point);
    bulletBatchNode->addChild(bullet);
    bulletList->addObject(bullet);
    
    //setBulletAction(bullet);
}

void BulletLayer::addMultiBullet(float dt)
{
    CCLog("Add MultiBullet!");
    CCSprite *bulletLeft = CCSprite::createWithSpriteFrameName("bullet2.png");
    CCSprite *bulletRight = CCSprite::createWithSpriteFrameName("bullet2.png");
    CCPoint playerLocation = scene->getPlayerLocation();
    CCSize playerSize = scene->getPlayerSize();
    
    bulletLeft->setPosition(ccp(playerLocation.x - playerSize.width / 4, playerLocation.y));
    bulletRight->setPosition(ccp(playerLocation.x + playerSize.width / 4, playerLocation.y));

    bulletBatchNode->addChild(bulletLeft);
    bulletBatchNode->addChild(bulletRight);
    
    bulletList->addObject(bulletLeft);
    bulletList->addObject(bulletRight);
    
    //setBulletAction(bulletLeft);
    //setBulletAction(bulletRight);

}

void BulletLayer::changeToOneBullet(float dt)
{
    this->unschedule(schedule_selector(BulletLayer::addMultiBullet));
    this->schedule(schedule_selector(BulletLayer::addNewOneBullet), 0.11f);
}

//old version
/*void BulletLayer::setBulletAction(CCSprite *bullet)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int finalPositionY = winSize.height + bullet->getContentSize().height / 2;
    int routeLength =  finalPositionY - bullet->getPosition().y;
    float flyingTime = routeLength / speed;
    
    CCLog("flying time: %f", flyingTime);
    CCFiniteTimeAction *actionMove = CCMoveTo::create(flyingTime, ccp(bullet->getPosition().x, routeLength));
    CCFiniteTimeAction *actionDone = CCCallFuncN::create(this, callfuncN_selector(BulletLayer::bulletMoveEnd));
    
    bullet->runAction(CCSequence::create(actionMove, actionDone, NULL));
}*/

void BulletLayer::bulletMoveEnd(CCNode *pSender)
{
    CCSprite *bullet = (CCSprite *)pSender;

    CCLog("1. delete: reference %d", bullet->retainCount());
    bulletList->removeObject(bullet);
    CCLog("2. delete: reference %d", bullet->retainCount());
    bulletBatchNode->removeChild(bullet, true);
    CCLog("Final delete: reference %d", bullet->retainCount());
}

/*void BulletLayer::removeAllBullet()
{
    
}*/
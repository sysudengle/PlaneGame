//
//  PlayerLayer.cpp
//  DL_Plane
//
//  Created by user on 13-10-22.
//
//

#include "PlayerLayer.h"

USING_NS_CC;

PlayerLayer::PlayerLayer()
{
    
}

PlayerLayer::~PlayerLayer()
{
    
}

bool PlayerLayer::init(RunGameScene *scene)
{
    bool ret = false;
    
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        this->scene = scene;
        //this->scheduleUpdate();
        isAlive = true;
        loadPlayer();
        setPlayerAction();
        
        ret  = true;
    } while (0);
    
    return ret;
}

CCSize PlayerLayer::getPlayeSize()
{
    return player->getContentSize();
}

void PlayerLayer::loadPlayer()
{
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    
    player = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
    player->setPosition(ccp(winSize.width / 2, player->getContentSize().height / 2));
    this->addChild(player);
}

void PlayerLayer::setPlayerAction()
{
    CCBlink *blink=CCBlink::create(1,3);
    
    CCAnimation* animation=CCAnimation::create();
    animation->setDelayPerUnit(0.1f);
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2.png"));
    CCAnimate* animate=CCAnimate::create(animation);
    
    //player->runAction(blink);
    player->runAction(CCRepeatForever::create(animate));
}

void PlayerLayer::movePlayer(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isAlive)
    {
        CCPoint beginPoint=pTouch->getLocationInView();
        beginPoint=CCDirector::sharedDirector()->convertToGL(beginPoint);

        /*CCRect planeRect = player->boundingBox();
        
        planeRect.origin.x-=15;
        planeRect.origin.y-=15;
        planeRect.size.width+=30;
        planeRect.size.height+=30;*/
        
        //if(planeRect.containsPoint(this->getParent()->convertTouchToNodeSpace(pTouch)))
        CCPoint endPoint=pTouch->getPreviousLocationInView();
        endPoint=CCDirector::sharedDirector()->convertToGL(endPoint);
        
        CCPoint offSet =ccpSub(beginPoint,endPoint);//获取offset
        
        //
        CCPoint toPoint=ccpAdd(player->getPosition(), offSet); //获取真正移动位置
        //moveTo(toPoint);
        moveTo(toPoint);
//        moveTo(offSet);

        }
}

void PlayerLayer::moveTo(CCPoint location)
{
    if(isAlive && !CCDirector::sharedDirector()->isPaused())
    {
        CCPoint actualPoint;
        CCSize winSize=CCDirector::sharedDirector()->getWinSize();
        CCSize planeSize = player->getContentSize();
        
        //bounding detect
        if (location.x<planeSize.width/2)
        {
            location.x=planeSize.width/2;
        }
        if (location.x>winSize.width-planeSize.width/2)
        {
            location.x=winSize.width-planeSize.width/2;
        }
        if (location.y<planeSize.height/2)
        {
            location.y=planeSize.height/2;
        }
        if (location.y>winSize.height-planeSize.height/2)
        {
            location.y=winSize.height-planeSize.height/2;
        }
        player->setPosition(location);
        //player->setPosition(ccp(player->getPositionX() + location.x, player->getPositionY() + location.y));
    }
}

void PlayerLayer::playerBlow()
{
    if(isAlive)
    {
        CCAnimation* animation=CCAnimation::create();
        animation->setDelayPerUnit(0.1f);
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n1.png"));
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n2.png"));
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n3.png"));
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n4.png"));
        
        CCAnimate* animate=CCAnimate::create(animation);
        //    CCCallFuncND* removeEnemy=CCCallFuncND::create(this,callfuncND_selector(),(void*)this);
        CCCallFunc *playerDie = CCCallFunc::create(this, callfunc_selector(PlayerLayer::removePlayer));
//        CCDelayTime *delay = CCDelayTime::create(1.0f);
//        CCCallFunc *gameSceneChange = CCCallFunc::create(this, callfunc_selector(PlayerLayer::gameOver));
//        scene->getBulletLayer()->stopShoot();
        CCSequence* sequence=CCSequence::create(animate, playerDie, NULL);
        player->runAction(sequence);
        isAlive = false;
    }
}

void PlayerLayer::removePlayer()
{
    //scene->getBulletLayer()->stopShoot();
    this->removeChild(player, true);
    player = NULL;
}

void PlayerLayer::gameOver()
{
    CCDirector::sharedDirector()->replaceScene(GameOverScene::create(scene->score));
}
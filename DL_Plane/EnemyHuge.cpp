//
//  EnemyHuge.cpp
//  DL_Plane
//
//  Created by user on 13-10-23.
//
//

#include "EnemyHuge.h"

USING_NS_CC;

EnemyHuge::EnemyHuge()
{
    life = 15;
    maxSpeed = 400;
    minSpeed = 200;
    score = 3000;
}

EnemyHuge::~EnemyHuge()
{
    
}

EnemyHuge *EnemyHuge::create(EnemyLayer *layer)
{
    EnemyHuge *enemy = new EnemyHuge();
    if(enemy && enemy->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n1.png")))
    {
        enemy->setEnemyLayer(layer);
        enemy->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(enemy);
        enemy = NULL;
    }
    return enemy;
}

void EnemyHuge::setEnemyAction()
{
    CCSpriteFrame *enemyFrame1, *enemyFrame2;
    enemyFrame1=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n1.png");
    enemyFrame2=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n2.png");
    CCAnimation* animation=CCAnimation::create();
    animation->setDelayPerUnit(0.1f);
    animation->addSpriteFrame(enemyFrame1);
    animation->addSpriteFrame(enemyFrame2);
    CCAnimate* animate=CCAnimate::create(animation);
    this->runAction(CCRepeatForever::create(animate));
    
    CCFiniteTimeAction *actionDone = CCCallFuncN::create(this, callfuncN_selector(EnemyHuge::enemyMoveFinish));
    EnemyAction(actionDone);
}

void EnemyHuge::enemyMoveFinish(CCNode *pObject)
{
    removeEnemy();
}

CCAnimation *EnemyHuge::enemyBlowAnimation()
{
    CCAnimation* animation=CCAnimation::create();
    animation->setDelayPerUnit(0.15f);
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down1.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down2.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down3.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down4.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down5.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down6.png"));
    
    return animation;
}
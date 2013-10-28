//
//  EnemyMid.cpp
//  DL_Plane
//
//  Created by user on 13-10-23.
//
//

#include "EnemyMid.h"

USING_NS_CC;

EnemyMid::EnemyMid()
{
    life = 8;
    maxSpeed = 400;
    minSpeed = 200;
    score = 700;
}

EnemyMid::~EnemyMid()
{
    
}

EnemyMid *EnemyMid::create(EnemyLayer *layer)
{
    EnemyMid *enemy = new EnemyMid();
    if(enemy && enemy->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2.png")))
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

void EnemyMid::setEnemyAction()
{
    CCFiniteTimeAction *actionDone = CCCallFuncN::create(this, callfuncN_selector(EnemyMid::enemyMoveFinish));
    EnemyAction(actionDone);
}


void EnemyMid::enemyMoveFinish(CCNode *pObject)
{
    removeEnemy();
}

CCAnimation *EnemyMid::enemyBlowAnimation()
{
    CCAnimation* animation=CCAnimation::create();
    animation->setDelayPerUnit(0.1f);
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down1.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down2.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down3.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down4.png"));
    
    return animation;
}
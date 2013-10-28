//
//  EnemySmall.cpp
//  DL_Plane
//
//  Created by user on 13-10-23.
//
//

#include "EnemySmall.h"

USING_NS_CC;

EnemySmall::EnemySmall()
{
    life = 1;
    maxSpeed = 400;
    minSpeed = 200;
    score = 100;
}

EnemySmall::~EnemySmall()
{
    
}

EnemySmall *EnemySmall::create(EnemyLayer *layer)
{
    EnemySmall *enemy = new EnemySmall();
    if(enemy && enemy->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1.png")))
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

void EnemySmall::setEnemyAction()
{
    CCFiniteTimeAction *actionDone = CCCallFuncN::create(this, callfuncN_selector(EnemySmall::enemyMoveFinish));
    EnemyAction(actionDone);
}

void EnemySmall::enemyMoveFinish(CCNode *pObject)
{
    removeEnemy();
}

CCAnimation *EnemySmall::enemyBlowAnimation()
{
    CCAnimation* animation=CCAnimation::create();
    animation->setDelayPerUnit(0.1f);
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down1.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down2.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down3.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down4.png"));
    
    return animation;
}
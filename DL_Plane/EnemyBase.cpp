//
//  EnemyBase.cpp
//  DL_Plane
//
//  Created by user on 13-10-23.
//
//

#include "EnemyBase.h"

USING_NS_CC;

EnemyBase::~EnemyBase()
{
    
}

void EnemyBase::EnemyAction(CCFiniteTimeAction *actionDone)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize enemySize = this->getContentSize();
    int speedRange = maxSpeed - minSpeed;
    int speed = rand() % (speedRange) + minSpeed;
    int roadLength = this->getPositionY() + enemySize.height / 2;
    
    CCFiniteTimeAction *actionMove = CCMoveTo::create(roadLength / speed, ccp(this->getPositionX(), -enemySize.height / 2));
    
    this->runAction(CCSequence::create(actionMove, actionDone, NULL));
}

void EnemyBase::reduceLife()
{
    life--;
}

void EnemyBase::EndLife()
{
    life = 0;
}

void EnemyBase::removeEnemy()
{
    this->removeFromParentAndCleanup(true);
    CCLog("*********** reference %d", this->retainCount());
}

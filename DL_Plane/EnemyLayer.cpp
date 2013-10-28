//
//  EnemyLayer.cpp
//  DL_Plane
//
//  Created by user on 13-10-23.
//
//

#include "EnemyLayer.h"

USING_NS_CC;

EnemyLayer::EnemyLayer()
{
    enemyList = CCArray::create();
    enemyList->retain();
}

EnemyLayer::~EnemyLayer()
{
    enemyList->release();
}

/*EnemyLayer *EnemyLayer::create(RunGameScene *scene)
{
    EnemyLayer *pRet = new EnemyLayer();
    if(pRet && pRet->init(scene))
    {
        pRet->autorelease();
    }
    else
    {
        delete pRet;
        pRet = NULL;
    }
    return pRet;
}*/

bool EnemyLayer::init(RunGameScene *scene)
{
    bool ret = false;
    
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        this->scene = scene;
        scheduleAddEnemy();
        ret  = true;
    } while (0);
    
    return ret;
}

void EnemyLayer::scheduleAddEnemy()
{
    CCLog("schedule Add enemy");
    this->schedule(schedule_selector(EnemyLayer::addEnemy), 1);
}

void EnemyLayer::addEnemy(float dt)
{
    int choice = rand(); // 0~2
    EnemyBase *enemy = NULL;
    CCLog("Add Enemy! %d", choice);
    
    // choice % num ===== num represents the frequency of an enemy type
    if(choice % 2 == 0)
    {
        enemy = EnemySmall::create(this);
    }
    else if(choice % 5 == 0)
    {
        enemy = EnemyMid::create(this);
    }
    else if(choice % 7 == 0)
    {
        enemy = EnemyHuge::create(this);
    }
    else
    {
        enemy = EnemySmall::create(this);
    }
    
    if(enemy == NULL) return;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize enemySize = enemy->getContentSize();
    int maxX = winSize.width - enemySize.width / 2;
    int minX = enemySize.width / 2;
    int rangeX = maxX - minX;
    int positionX = random() % rangeX + minX;
    enemy->setPosition(ccp(positionX, winSize.height + enemySize.height / 2));
    
    enemy->setEnemyAction();
    
    this->enemyList->addObject(enemy);
    this->addChild(enemy);
}

void EnemyLayer::removeEnemy(CCNode *nEnemy, void *data)
{
    EnemyBase *enemy = (EnemyBase *)data;
    if(enemy != NULL)
    {
        //enemy->removeEnemy();
        enemyList->removeObject(enemy);
        CCLog("$$$$$$$$$$%d", enemy->retainCount());
        //enemy->removeFromParentAndCleanup(true);
        this->removeChild(enemy, true);
        CCLog("2.$$$$$$$$$$%d", enemy->retainCount());
    }
}

void EnemyLayer::allEnemyDie()
{
    EnemyBase *enemy = NULL;
    CCObject *oEnemy = NULL;
    CCARRAY_FOREACH(enemyList, oEnemy)
    {
        enemy = (EnemyBase *)oEnemy;
        
        // set life to zero to avoid being operated when detecting
        enemy->EndLife();
        this->enemyBlow(enemy);
    }
}

void EnemyLayer::enemyBlow(EnemyBase *enemy)
{
    // enemy acts different animations according to its type
    CCAnimation *animation = enemy->enemyBlowAnimation();
    
    CCAnimate* animate=CCAnimate::create(animation);
    CCCallFuncND* removeEnemyAction=CCCallFuncND::create(this,callfuncND_selector(EnemyLayer::removeEnemy),(void*)enemy);
    CCSequence* sequence=CCSequence::create(animate, removeEnemyAction, NULL);
    
    enemy->stopAllActions();
    enemy->runAction(sequence);
    
    scene->getScore(enemy->getScore());
}

//
//  EnemyBase.h
//  DL_Plane
//
//  Created by user on 13-10-23.
//
//

#ifndef __DL_Plane__EnemyBase__
#define __DL_Plane__EnemyBase__

#include "cocos2d.h"
//#include "RunGameScene.h"
//#include "EnemyLayer.h"

USING_NS_CC;

class RunGameScene;
class EnemyLayer;

class EnemyBase: public CCSprite
{
public:
    virtual ~EnemyBase();
    virtual void setEnemyAction() = 0;
    virtual void enemyMoveFinish(CCNode *pObject) = 0;
    virtual CCAnimation *enemyBlowAnimation() = 0;
    void removeEnemy();
    
    void EnemyAction(CCFiniteTimeAction *actionDone);
    void reduceLife();
    void EndLife();
    CC_SYNTHESIZE(int, score, Score);
    CC_SYNTHESIZE(int, life, Life);
    CC_SYNTHESIZE(EnemyLayer *, m_enemyLayer, EnemyLayer);
protected:
    CCSpriteFrame *spriteFrame;
    int maxSpeed;
    int minSpeed;
    //int score;
};

#endif /* defined(__DL_Plane__EnemyBase__) */

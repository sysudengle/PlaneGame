//
//  EnemyMid.h
//  DL_Plane
//
//  Created by user on 13-10-23.
//
//

#ifndef __DL_Plane__EnemyMid__
#define __DL_Plane__EnemyMid__

#include "cocos2d.h"
#include "RunGameScene.h"
#include "EnemyBase.h"
#include "EnemyLayer.h"

USING_NS_CC;

class RunGameScene;
class EnemyBase;
class EnemyLayer;

class EnemyMid: public EnemyBase
{
public:
    EnemyMid();
    ~EnemyMid();
    
    void setEnemyAction();

    void enemyMoveFinish(CCNode *pObject);
    CCAnimation *enemyBlowAnimation();
    
    static EnemyMid *create(EnemyLayer *layer);
    CC_SYNTHESIZE(EnemyLayer *, m_enemyLayer, EnemyLayer);
};

#endif /* defined(__DL_Plane__EnemyMid__) */

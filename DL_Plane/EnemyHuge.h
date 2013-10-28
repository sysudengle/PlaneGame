//
//  EnemyHuge.h
//  DL_Plane
//
//  Created by user on 13-10-23.
//
//

#ifndef __DL_Plane__EnemyHuge__
#define __DL_Plane__EnemyHuge__

#include "cocos2d.h"
#include "RunGameScene.h"
#include "EnemyBase.h"
#include "EnemyLayer.h"

USING_NS_CC;

class RunGameScene;
class EnemyBase;
class EnemyLayer;

class EnemyHuge: public EnemyBase
{
public:
    EnemyHuge();
    ~EnemyHuge();
    
    void setEnemyAction();
    
    void enemyMoveFinish(CCNode *pObject);
    CCAnimation *enemyBlowAnimation();
    
    static EnemyHuge *create(EnemyLayer *layer);
    CC_SYNTHESIZE(EnemyLayer *, m_enemyLayer, EnemyLayer);
};

#endif /* defined(__DL_Plane__EnemyHuge__) */

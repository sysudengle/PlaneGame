//
//  EnemySmall.h
//  DL_Plane
//
//  Created by user on 13-10-23.
//
//

#ifndef __DL_Plane__EnemySmall__
#define __DL_Plane__EnemySmall__

#include "cocos2d.h"
#include "RunGameScene.h"
#include "EnemyBase.h"
#include "EnemyLayer.h"

USING_NS_CC;

class RunGameScene;
class EnemyBase;
class EnemyLayer;

class EnemySmall: public EnemyBase
{
public:
    EnemySmall();
    ~EnemySmall();

    void setEnemyAction();
    void removeEnemyFromLayer();

    void enemyMoveFinish(CCNode *pObject);
    CCAnimation *enemyBlowAnimation();
    
    static EnemySmall *create(EnemyLayer *layer);
    CC_SYNTHESIZE(EnemyLayer *, m_enemyLayer, EnemyLayer);
};

#endif /* defined(__DL_Plane__EnemySmall__) */

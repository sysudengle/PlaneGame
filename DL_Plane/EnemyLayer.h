//
//  EnemyLayer.h
//  DL_Plane
//
//  Created by user on 13-10-23.
//
//

#ifndef __DL_Plane__EnemyLayer__
#define __DL_Plane__EnemyLayer__

#include "cocos2d.h"
#include "PlaneMacro.h"
#include "RunGameScene.h"
#include "EnemyBase.h"
#include "EnemySmall.h"
#include "EnemyMid.h"
#include "EnemyHuge.h"

USING_NS_CC;

class RunGameScene;

class EnemyLayer: public CCLayer
{
public:
    EnemyLayer();
    ~EnemyLayer();
    
    CREATE_FUNC_WITH_SCENE(EnemyLayer, RunGameScene);
    bool init(RunGameScene *scene);
    
    void scheduleAddEnemy();
    void addEnemy(float dt);
    void removeEnemy(CCNode *nEnemy, void *data);
    void allEnemyDie();
    
    void enemyBlow(EnemyBase *enemy);
    
    CC_SYNTHESIZE(RunGameScene *, scene, Scene);
    CC_SYNTHESIZE(CCArray *, enemyList, EnemyList);
protected:
    
};


#endif /* defined(__DL_Plane__EnemyLayer__) */

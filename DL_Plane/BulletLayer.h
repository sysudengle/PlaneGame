//
//  BulletLayer.h
//  DL_Plane
//
//  Created by user on 13-10-22.
//
//

#ifndef __DL_Plane__BulletLayer__
#define __DL_Plane__BulletLayer__

#include "cocos2d.h"
#include "PlaneMacro.h"
#include "RunGameScene.h"

USING_NS_CC;

class RunGameScene;

class BulletLayer: public CCLayer
{
public:
    BulletLayer();
    ~BulletLayer();
    
    CREATE_FUNC_WITH_SCENE(BulletLayer, RunGameScene);
    bool init(RunGameScene *scene);
    
    void update(float dt);
    void bulletMoveEnd(CCNode *pSender);
    
    void MultiBulletShoot();
    void stopShoot();
    CC_SYNTHESIZE(RunGameScene *, scene, Scene);
    CC_SYNTHESIZE(CCArray *, bulletList, BulletList);
protected:
    int speed;
    CCSpriteBatchNode *bulletBatchNode;
    //CCSpriteBatchNode *MultiBulletBatchNode;
    void addNewOneBullet(float dt);
    void addMultiBullet(float dt);
    void changeToOneBullet(float dt);
    //void setBulletAction(CCSprite *bullet);
    void bulletMove();
    //void removeAllBullet();
};

#endif /* defined(__DL_Plane__BulletLayer__) */

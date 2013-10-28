//
//  BackgroundLayer.h
//  DL_Plane
//
//  Created by user on 13-10-22.
//
//

#ifndef __DL_Plane__BackgroundLayer__
#define __DL_Plane__BackgroundLayer__

#include "cocos2d.h"
#include "PlaneMacro.h"
#include "RunGameScene.h"

USING_NS_CC;

class RunGameScene;

class BackgroundLayer: public CCLayer
{
public:
    BackgroundLayer();
    ~BackgroundLayer();
    
    CREATE_FUNC_WITH_SCENE(BackgroundLayer, RunGameScene);
    bool init(RunGameScene *scene);
    
    void update(float dt);
    
    CC_SYNTHESIZE(RunGameScene *, scene, Scene);
protected:
    void autoResize();
    void backgroundMove();
    CCSprite *background1;
    CCSprite *background2;
};


#endif /* defined(__DL_Plane__BackgroundLayer__) */

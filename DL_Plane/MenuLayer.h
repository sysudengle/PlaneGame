//
//  MenuLayer.h
//  DL_Plane
//
//  Created by user on 13-10-23.
//
//

#ifndef __DL_Plane__MenuLayer__
#define __DL_Plane__MenuLayer__

#include "cocos2d.h"
#include "PlaneMacro.h"
#include "RunGameScene.h"

USING_NS_CC;

class RunGameScene;

class MenuLayer: public CCLayer
{
public:
    CREATE_FUNC_WITH_SCENE(MenuLayer, RunGameScene);
    bool init(RunGameScene *scene);
    
    void menuPauseCallBack(CCObject *pSender);
    
    void scoreDisplay(int score);
    
    CC_SYNTHESIZE(RunGameScene *, scene, Scene);
protected:
    CCMenuItemSprite *pPauseItem;
    CCLabelBMFont *scoreLabel;
//    CCMenuItem *
};

#endif /* defined(__DL_Plane__MenuLayer__) */

//
//  TouchLayer.h
//  DL_Plane
//
//  Created by user on 13-10-22.
//
//

#ifndef __DL_Plane__TouchLayer__
#define __DL_Plane__TouchLayer__

#include "PlaneMacro.h"
#include "TouchLayerDelegate.h"
#include "RunGameScene.h"

USING_NS_CC;

class RunGameScene;
class TouchLayerDelegate;

class TouchLayer: public CCLayer
{
public:
    CC_SYNTHESIZE(TouchLayerDelegate *, m_pDelegate, Delegate);
    
    CREATE_FUNC_WITH_SCENE(TouchLayer, RunGameScene);
    bool init(RunGameScene *scene);
    void registerWithTouchDispatcher();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    void onExit();
    CC_SYNTHESIZE(RunGameScene *, scene, Scene);
    //NODE_FUNC(TouchLayer);
protected:
    bool clicked;
    void singleClick(float dt);
};

#endif /* defined(__DL_Plane__TouchLayer__) */

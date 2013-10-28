//
//  PlayerLayer.h
//  DL_Plane
//
//  Created by user on 13-10-22.
//
//

#ifndef __DL_Plane__PlayerLayer__
#define __DL_Plane__PlayerLayer__

#include "cocos2d.h"
#include "PlaneMacro.h"
#include "RunGameScene.h"
#include "TouchLayerDelegate.h"
#include "GameOverScene.h"

USING_NS_CC;

class RunGameScene;
class GameOverScene;

class PlayerLayer: public CCLayer, public TouchLayerDelegate
{
public:
    PlayerLayer();
    ~PlayerLayer();
    
    CREATE_FUNC_WITH_SCENE(PlayerLayer, RunGameScene);
    bool init(RunGameScene *scene);
    
    void movePlayer(CCTouch *pTouch, CCEvent *pEvent);
    CCSize getPlayeSize();
    
    void moveTo(CCPoint location);
    void playerBlow();
    CC_SYNTHESIZE(RunGameScene *, scene, Scene);
    CC_SYNTHESIZE(CCSprite *, player, Player);
protected:
    void loadPlayer();
    void setPlayerAction();
    void gameOver();
    void removePlayer();
    bool isAlive;
//    CCSprite *player;
};

#endif /* defined(__DL_Plane__PlayerLayer__) */

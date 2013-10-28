//
//  BonusLayer.h
//  DL_Plane
//
//  Created by user on 13-10-23.
//
//

#ifndef __DL_Plane__BonusLayer__
#define __DL_Plane__BonusLayer__

#include "cocos2d.h"
#include "PlaneMacro.h"
#include "RunGameScene.h"

USING_NS_CC;

enum BONUS {
    bigbomb
};

class RunGameScene;

class BonusLayer: public CCLayer
{
public:
    BonusLayer();
    ~BonusLayer();
    
    CREATE_FUNC_WITH_SCENE(BonusLayer, RunGameScene);
    bool init(RunGameScene *scene);
    
    void bigBombBonusDisplay(int bonusNum);
    
    void removeBonus(CCSprite *bonus);
    
    CC_SYNTHESIZE(RunGameScene *, scene, Scene);
    CC_SYNTHESIZE(CCArray *, bonusList, BonusList);
    CC_SYNTHESIZE(char *, multiBulletFlag, MultiBulletFlag);
    CC_SYNTHESIZE(char *, bigBombFlag, BigBombFlag);
protected:
    void addNewBonus(float dt);
    void addNewMultiBulletBonus(float dt);
    void addNewBigBombBonus(float dt);
    
    void setBonusAction(CCSprite *bonus);
    void bonusMoveFinish(CCNode *nBonus);
    
    CCLabelTTF *bigBombNum;
    CCSprite *bigBombLogo;
};


#endif /* defined(__DL_Plane__BonusLayer__) */

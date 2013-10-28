//
//  RunGameScene.h
//  DL_Plane
//
//  Created by user on 13-10-22.
//
//

#ifndef __DL_Plane__RunGameScene__
#define __DL_Plane__RunGameScene__

#include "cocos2d.h"
#include "PlaneMacro.h"
#include "BackgroundLayer.h"
#include "PlayerLayer.h"
#include "BulletLayer.h"
#include "TouchLayer.h"
#include "EnemyLayer.h"
#include "MenuLayer.h"
#include "BonusLayer.h"
#include "GameOverScene.h"
//#include "GameLostScene.h"
//#include "GameWinScene.h"

USING_NS_CC;

/*enum sprite{
    kingbox_id,
    girl_id
};*/

class BackgroundLayer;
class PlayerLayer;
class BulletLayer;
class EnemyLayer;
class TouchLayer;
class MenuLayer;
class BonusLayer;

class RunGameScene: public CCScene
{
public:
    RunGameScene();
    ~RunGameScene();
    virtual bool init();
    
    void update(float dt);
    void detectBulletCollision();
    void detectPlayerCollision();
    void detectBonusCollision();
    
    CCPoint getPlayerLocation();
    CCSize getPlayerSize();
    
    void removeAllEnemy();
    
    void getScore(int enemyScore);
    
    CC_SYNTHESIZE(BackgroundLayer *, m_backgroundLayer, BackgroundLayer);
    CC_SYNTHESIZE(PlayerLayer *, m_playerLayer, PlayerLayer);
    CC_SYNTHESIZE(BulletLayer *, m_bulletLayer, BulletLayer);
    CC_SYNTHESIZE(TouchLayer *, m_touchLayer, TouchLayer);
    CC_SYNTHESIZE(EnemyLayer *, m_enemyLayer, EnemyLayer);
    CC_SYNTHESIZE(MenuLayer *, m_menuLayer, MenuLayer);
    CC_SYNTHESIZE(BonusLayer *, m_bonusLayer, BonusLayer);
    CREATE_FUNC(RunGameScene);
    
    static int highestScore;
    int score;
protected:
    void loadResourceToCache();
    void loadBackgroundLayer();
    void loadPlayerLayer();
    void loadBulletLayer();
    void loadEnemyLayer();
    void loadTouchLayer();
    void loadMenuLayer();
    void loadBonusLayer();
    
    void stopShoot();
    void gamOver();

    int bigBomb;
};

#endif /* defined(__DL_Plane__RunGameScene__) */

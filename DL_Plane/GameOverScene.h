//
//  GameOverScene.h
//  DL_Plane
//
//  Created by user on 13-10-24.
//
//

#ifndef __DL_Plane__GameOverScene__
#define __DL_Plane__GameOverScene__


#include "cocos2d.h"
#include "RunGameScene.h"

USING_NS_CC;

class RunGameScene;

class GameOverScene: public CCScene
{
public:
    bool init(int score);
    static GameOverScene *create(int score);
    //CREATE_FUNC(GameOverScene);
protected:
    void menuPlayCallBack(CCObject *pSender);
    bool fileExist();
    void getHighestHistoryScore();
    void refreshHighestScore();
    
    int score;
    int highestScore;
    CCLabelBMFont *scoreLabel;
    CCLabelBMFont *highestScoreLabel;
};

#endif /* defined(__DL_Plane__GameOverScene__) */

//
//  RunGameScene.cpp
//  DL_Plane
//
//  Created by user on 13-10-22.
//
//

#include "RunGameScene.h"

USING_NS_CC;

RunGameScene::RunGameScene():bigBomb(0), score(0)
{
    
}

RunGameScene::~RunGameScene()
{
    
}

bool RunGameScene::init()
{
    if(CCScene::init())
    {
        loadResourceToCache();
        loadBackgroundLayer();
        loadBulletLayer();
        loadPlayerLayer();
        loadEnemyLayer();
        loadBonusLayer();
        loadTouchLayer();
        loadMenuLayer();
        
        this->scheduleUpdate();
        return true;
    }
    else
    {
        return false;
    }
}

void RunGameScene::loadResourceToCache()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot_background.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot.plist");
}

void RunGameScene::loadBackgroundLayer()
{
    m_backgroundLayer = BackgroundLayer::create(this);
    this->addChild(m_backgroundLayer);
}

void RunGameScene::loadPlayerLayer()
{
    m_playerLayer = PlayerLayer::create(this);
    this->addChild(m_playerLayer);
}

void RunGameScene::loadBulletLayer()
{
    m_bulletLayer = BulletLayer::create(this);
    this->addChild(m_bulletLayer);
}

void RunGameScene::loadEnemyLayer()
{
    m_enemyLayer = EnemyLayer::create(this);
    this->addChild(m_enemyLayer);
}

void RunGameScene::loadMenuLayer()
{
    m_menuLayer = MenuLayer::create(this);
    this->addChild(m_menuLayer);
}

void RunGameScene::loadTouchLayer()
{
    m_touchLayer = TouchLayer::create(this);
    this->addChild(m_touchLayer);
}

void RunGameScene::loadBonusLayer()
{
    m_bonusLayer = BonusLayer::create(this);
    this->addChild(m_bonusLayer);
}

void RunGameScene::update(float dt)
{
    detectBulletCollision();
    detectPlayerCollision();
    detectBonusCollision();
}

void RunGameScene::detectBulletCollision()
{
    CCArray *bulletToDelete = CCArray::create();
    bulletToDelete->retain();
    CCObject *oBullet, *oEnemy;
    
    CCARRAY_FOREACH(m_bulletLayer->getBulletList(), oBullet)
    {
        CCSprite *bullet = (CCSprite *)oBullet;
        CCArray *enemyToDelete = CCArray::create();
        enemyToDelete->retain();
        
        CCARRAY_FOREACH(m_enemyLayer->getEnemyList(), oEnemy)
        {
            EnemyBase *enemy = (EnemyBase *)oEnemy;
            
            if(bullet->boundingBox().intersectsRect(enemy->boundingBox()))
            {
                if(enemy->getLife() > 1)
                {
                    enemy->reduceLife();
                    bullet->stopAllActions();
                    bulletToDelete->addObject(bullet);
                }
                else if(enemy->getLife() == 1)
                {
                    enemy->reduceLife();
                    bullet->stopAllActions();
                    bulletToDelete->addObject(bullet);
                    enemyToDelete->addObject(enemy);
                }
                // omit [else] to avoid deleting enemies to be operated
            }
        }
        
        CCARRAY_FOREACH(enemyToDelete, oEnemy)
        {
            EnemyBase *enemy = (EnemyBase *)oEnemy;
            //enemy->enemyBlow();
            m_enemyLayer->enemyBlow(enemy);
            CCLog("To deleteeeeeeeeeeee: %d", enemy->retainCount());
        }
        enemyToDelete->release();
    }
    CCARRAY_FOREACH(bulletToDelete, oBullet)
    {
        CCSprite *bullet = (CCSprite *)oBullet;
        //bulletToDelete->removeObject(bullet);
        CCLog("1. bullet reference: %d", bullet->retainCount());
        m_bulletLayer->bulletMoveEnd(bullet);
        CCLog("2. bullet reference: %d", bullet->retainCount());
    }
    
    bulletToDelete->release();
}

void RunGameScene::detectPlayerCollision()
{
    CCObject *oEnemy = NULL;
    CCSprite *player = m_playerLayer->getPlayer();
    if(player != NULL)
    {
        // reshape the player so that collision will ignore the reduced portion
        CCRect playerRect = player->boundingBox();
        playerRect.origin.x += 30;
        playerRect.size.width -= 60;
        
        
        CCARRAY_FOREACH(m_enemyLayer->getEnemyList(), oEnemy)
        {
            CCSprite *enemy = (CCSprite *)oEnemy;
            if(playerRect.intersectsRect(enemy->boundingBox()))
            {
                CCLog("crash player! you are game over!~");
                this->stopShoot();
                m_playerLayer->playerBlow();
                CCDelayTime *delay = CCDelayTime::create(2.0f);
                CCCallFunc *gameEnd = CCCallFunc::create(this, callfunc_selector(RunGameScene::gamOver));
                this->runAction(CCSequence::create(delay, gameEnd));
                break;
            }
        }
    }
}

void RunGameScene::detectBonusCollision()
{
    CCObject *oBonus = NULL;
    CCSprite *player = m_playerLayer->getPlayer();
    if(player != NULL)
    {
        CCARRAY_FOREACH(m_bonusLayer->getBonusList(), oBonus)
        {
            CCSprite *bonus = (CCSprite *)oBonus;
            
            if(bonus->boundingBox().intersectsRect(player->boundingBox()))
            {
                char *bonusFlag = (char *)bonus->getUserData();
                
                if(bonusFlag == m_bonusLayer->getMultiBulletFlag())
                {
                    m_bulletLayer->MultiBulletShoot();
                }
                else if(bonusFlag == m_bonusLayer->getBigBombFlag())
                {
                    this->bigBomb++;
                    m_bonusLayer->bigBombBonusDisplay(this->bigBomb);
                }
                bonus->stopAllActions();
                m_bonusLayer->removeBonus(bonus);
            }
            
        }
    }
}

CCPoint RunGameScene::getPlayerLocation()
{
    return m_playerLayer->getPlayer()->getPosition();
}

CCSize RunGameScene::getPlayerSize()
{
    return m_playerLayer->getPlayeSize();
}

void RunGameScene::removeAllEnemy()
{
    if(bigBomb > 0)
    {
        bigBomb--;
        m_bonusLayer->bigBombBonusDisplay(bigBomb);
        m_enemyLayer->allEnemyDie();
    }
}

void RunGameScene::getScore(int enemyScore)
{
    score += enemyScore;
    m_menuLayer->scoreDisplay(score);
}

void RunGameScene::stopShoot()
{
    m_bulletLayer->stopShoot();
}

void RunGameScene::gamOver()
{
    CCDirector::sharedDirector()->replaceScene(GameOverScene::create(score));
}
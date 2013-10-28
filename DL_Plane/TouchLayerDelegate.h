//
//  TouchLayerDelegate.h
//  DL_Plane
//
//  Created by user on 13-10-22.
//
//

#ifndef __DL_Plane__TouchLayerDelegate__
#define __DL_Plane__TouchLayerDelegate__

#include "cocos2d.h"

USING_NS_CC;

// a proxy used to decoupling
class TouchLayerDelegate
{
public:
    virtual void movePlayer(CCTouch *pTouch, CCEvent *pEvent) = 0;
};


#endif /* defined(__DL_Plane__TouchLayerDelegate__) */

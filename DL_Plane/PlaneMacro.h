//
//  PlaneMacro.h
//  DL_Plane
//
//  Created by user on 13-10-28.
//
//

#ifndef DL_Plane_PlaneMacro_h
#define DL_Plane_PlaneMacro_h

#define CREATE_FUNC_WITH_SCENE(__TYPE__, __SCENETYPE__) \
static __TYPE__* create(__SCENETYPE__ *scene) \
{ \
__TYPE__ *pRet = new __TYPE__(); \
if (pRet && pRet->init(scene)) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = NULL; \
return NULL; \
} \
}

#endif

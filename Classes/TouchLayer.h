#ifndef __TOUCH_LAYER_H__
#define __TOUCH_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class TouchLayer : public CCLayer
{
public:
	virtual bool init();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

// 	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
// 	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
// 	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
// 	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

	CREATE_FUNC(TouchLayer);
};

#endif
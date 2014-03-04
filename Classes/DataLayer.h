#ifndef __DATA_LAYER_H__
#define __DATA_LAYER_H__

#include "cocos2d.h"
#include "Unity.h"
USING_NS_CC;




class DataLayer : public CCLayer
{
	CC_SYNTHESIZE(int,m_nScore,Score)
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	virtual void onExit();
//	virtual void onEnterTransitionDidFinish();

	void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(DataLayer);
private:

};

#endif // __DATA_LAYER_H__

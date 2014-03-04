#ifndef __LOSE_SCENE_H__
#define __LOSE_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;




class LoseLayer : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	virtual void onEnter();
	virtual void onExit();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static CCScene* scene();
    
	void menuRetryCallback(CCObject* pSender);
   
    // implement the "static node()" method manually
    CREATE_FUNC(LoseLayer);
	
};

#endif // __HELLOWORLD_SCENE_H__

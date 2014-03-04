#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Unity.h"
USING_NS_CC;




class SnakeMap : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	virtual void onEnter();
	virtual void onExit();
	virtual void onEnterTransitionDidFinish();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	void snakeMove(float dt);

	CCPoint& GetFoodPos(){return m_iFood;}
	void AddFood();
	void SetMapBlank(int x,int y,bool val);

	//ÇÐ»»³¡¾°
	void ChangeScene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(SnakeMap);
private:

	CCPoint m_iFood;
	bool m_bBlank[WIDTH_NUM][HEIGHT_NUM];
	
};

#endif // __HELLOWORLD_SCENE_H__

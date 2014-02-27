#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

#define WIDTH_NUM 30
#define HEIGHT_NUM 20

enum eDirection
{
	eDir_Up,
	eDir_Down,
	eDir_Left,
	eDir_Right,
};

class SnakeMap : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	virtual void onExit();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	void moveForward(float dt);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    // implement the "static node()" method manually
    CREATE_FUNC(SnakeMap);
private:
	cocos2d::CCPoint m_iPos;
	std::list<cocos2d::CCPoint> m_lBody;
	std::list<cocos2d::CCSprite*> m_lTex;
	cocos2d::CCPoint m_iFood;
	bool m_bBlank[WIDTH_NUM][HEIGHT_NUM];
	eDirection m_eDir;

	void AddFood();
};

#endif // __HELLOWORLD_SCENE_H__

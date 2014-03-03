#ifndef __SNAKE_H__
#define __SNAKE_H__


#include "cocos2d.h"
#include "Unity.h"

USING_NS_CC;



class Snake : public CCNode
{
	CC_SYNTHESIZE_READONLY(eDirection,m_eDir,Direction)
public:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	void Move();
	int GetBodyLength(){return m_lpBody.size();}
	void setDirection(eDirection dir);

	CREATE_FUNC(Snake);
private:
	std::list<CCSprite*> m_lpBody;
	std::list<CCPoint> m_lBodyPos;
	
	//保存Map的一些固定属性，减少重复计算
	CCPoint m_iOrigin;
	CCSize m_iMapSize;
	CCRect m_iBodyRect;
};

#endif
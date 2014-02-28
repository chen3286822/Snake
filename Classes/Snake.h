#ifndef __SNAKE_H__
#define __SNAKE_H__


#include "cocos2d.h"
#include "Unity.h"

USING_NS_CC;



class Snake : public CCNode
{
public:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	void Move();
private:
	std::list<CCSprite*> m_lpBody;
	std::list<CCPoint> m_lBodyPos;
	eDirection m_eDir;
	
	//����Map��һЩ�̶����ԣ������ظ�����
	CCPoint m_iOrigin;
	CCSize m_iMapSize;
	CCRect m_iBodyRect;
};

#endif
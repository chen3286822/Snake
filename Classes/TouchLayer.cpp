#include "TouchLayer.h"
#include "Snake.h"
#include "Unity.h"

bool TouchLayer::init()
{
	bool bRet = false;
	do 
	{        
		CC_BREAK_IF(!CCLayer::init());
		LOGD("content width:%f height:%f",this->getContentSize().width,this->getContentSize().height);

		CCDirector* pDirector = CCDirector::sharedDirector();
		LOGD("win size width:%f height:%f",pDirector->getWinSize().width,pDirector->getWinSize().height);

		this->setTouchMode(kCCTouchesOneByOne);
		this->setTouchEnabled(true);
		// success
		bRet = true;
	} while(0);
	return bRet;
}

void TouchLayer::onExit()
{
	this->setTouchEnabled(false);
}

bool TouchLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	Snake* snake = dynamic_cast<Snake*>(this->getParent()->getChildByTag(eID_Snake));
	if(!snake)
		return false;

	CCPoint location = pTouch->getLocation();
	CCSize size = this->getContentSize();
	float y1 = -1*size.height/size.width*location.x+size.height;
	float y2 = size.height/size.width*location.x;

	eDirection dir;
	if(location.y < y1 && location.y < y2)
	{
		dir = eDir_Down;
	}
	else if (location.y > y1 && location.y > y2)
	{
		dir = eDir_Up;
	}
	else if (location.y < y1 && location.y > y2)
	{
		dir = eDir_Left;
	}
	else if (location.y > y1 && location.y < y2)
	{
		dir = eDir_Right;
	}
	snake->setDirection(dir);
	return true;
}

void TouchLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void TouchLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void TouchLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}

/*
void TouchLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	if (pTouches->count() == 1)
	{
		CCTouch* touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
		CCLayer* layer = dynamic_cast<CCLayer*>(this->getParent()->getChildByTag(1));
		CCSprite* spr = dynamic_cast<CCSprite*>(layer->getChildByTag(2));

		CCPoint locationInNode = spr->convertToNodeSpace(touch->getLocation());
		CCSize s = spr->getContentSize();
		CCRect rect = CCRect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			spr->setOpacity(180);
		}
	}	
}

void TouchLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	if (pTouches->count() == 1)
	{
		CCLayer* layer = dynamic_cast<CCLayer*>(this->getParent()->getChildByTag(1));
		CCSprite* spr = dynamic_cast<CCSprite*>(layer->getChildByTag(4));

		CCTouch* touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
		spr->setPosition(spr->getPosition()+touch->getDelta());
	}
	else if (pTouches->count() == 2)
	{
		CCLayer* layer = dynamic_cast<CCLayer*>(this->getParent()->getChildByTag(1));
		CCSprite* spr = dynamic_cast<CCSprite*>(layer->getChildByTag(2));

		CCTouch* touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
		spr->setPosition(spr->getPosition()+touch->getDelta());
	}
	
}

void TouchLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	if (pTouches->count() == 1)
	{
		CCLayer* layer = dynamic_cast<CCLayer*>(this->getParent()->getChildByTag(1));
		CCSprite* spr = dynamic_cast<CCSprite*>(layer->getChildByTag(2));

		CCTouch* touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
		CCPoint locationInNode = spr->convertToNodeSpace(touch->getLocation());
		CCSize s = spr->getContentSize();
		CCRect rect = CCRect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			spr->setOpacity(255);
		}
	}
	
}

void TouchLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{

}*/
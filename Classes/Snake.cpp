#include "Snake.h"
#include "SnakeMapScene.h"

bool Snake::init()
{
	if ( !CCNode::init() )
	{
		return false;
	}
	m_lpBody.clear();
	m_lBodyPos.clear();
	m_eDir = eDir_Right;
	return true;
}

void Snake::onEnter()
{
	CCNode::onEnter();

	m_iOrigin = CCDirector::sharedDirector()->getVisibleOrigin();

	SnakeMap* mapLayer = dynamic_cast<SnakeMap*>(this->getParent());
	if (mapLayer)
	{
		m_iMapSize = mapLayer->getContentSize();
		m_iBodyRect = CCRectMake(0,0,m_iMapSize.width/WIDTH_NUM,m_iMapSize.height/HEIGHT_NUM);

		CCPoint head = ccp(WIDTH_NUM/2,HEIGHT_NUM/2);
		m_lBodyPos.push_front(head);
		mapLayer->SetMapBlank(head.x,head.y,false);

		CCSprite* snake = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("blank.png"));	
		snake->setTextureRect(m_iBodyRect);
		snake->setColor(ccWHITE);
		snake->setAnchorPoint(ccp(0,0));
		snake->setPosition(ccp(m_iOrigin.x+m_lBodyPos.front().x*m_iBodyRect.size.width,m_iOrigin.y+m_lBodyPos.front().y*m_iBodyRect.size.height));
		this->addChild(snake);
		m_lpBody.push_front(snake);
	}
	else
	{
		//错误
	}
}

void Snake::onExit()
{
	CCNode::onExit();

	m_lpBody.clear();
	m_lBodyPos.clear();
}

void Snake::setDirection(eDirection dir)
{
	if((m_eDir==eDir_Up && dir==eDir_Down) || (m_eDir==eDir_Down && dir==eDir_Up) ||
		(m_eDir==eDir_Right && dir==eDir_Left) || (m_eDir==eDir_Left && dir==eDir_Right))
		return;
	m_eDir = dir;
}

bool Snake::Move()
{
	CCPoint offset = ccp(0,0);
	CCPoint head = m_lBodyPos.front();
	//检测是否出界
	if(m_eDir == eDir_Up)
	{
		if(head.y + 1 >= HEIGHT_NUM)
			return false;
		offset.y = 1;
	}
	else if(m_eDir == eDir_Down)
	{
		if(head.y - 1 < 0)
			return false;
		offset.y = -1;
	}
	else if(m_eDir == eDir_Left)
	{
		if(head.x -1 < 0)
			return false;
		offset.x = -1;
	}
	else if(m_eDir == eDir_Right)
	{
		if(head.x + 1 >= WIDTH_NUM)
			return false;
		offset.x = 1;
	}
	CCPoint next = ccp(head.x+offset.x,head.y+offset.y);
	//检测是否碰到自己
	if(m_lBodyPos.empty())
		return false;
	std::list<CCPoint>::iterator it=m_lBodyPos.begin();
	//先自增it，排除待检测点就是head自己
	for (++it;it!=m_lBodyPos.end();it++)
	{
		if(next.x == (*it).x && next.y == (*it).y)
			return false;
	}
	//检测是否是个食物
	SnakeMap* mapLayer = dynamic_cast<SnakeMap*>(this->getParent());
	if(!mapLayer)
		return false;
	CCPoint& food = mapLayer->GetFoodPos();
	if(next.x == food.x && next.y == food.y)
	{
		m_lBodyPos.push_front(next);
		mapLayer->AddFood();

		CCSprite* snake = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("blank.png"));
		snake->setTextureRect(m_iBodyRect);
		snake->setColor(ccWHITE);
		snake->setAnchorPoint(ccp(0,0));
		snake->setPosition(ccp(m_iOrigin.x+next.x*m_iBodyRect.size.width,m_iOrigin.y+next.y*m_iBodyRect.size.height));
		this->addChild(snake,0);
		m_lpBody.push_front(snake);

		//加分
		mapLayer->setScore(mapLayer->getScore()+1);
		CCLabelTTF* label = dynamic_cast<CCLabelTTF*>(this->getParent()->getChildByTag(eID_Score));
		if(label)
		{
			char score[256];
			sprintf(score,"Score : %d",mapLayer->getScore());
			label->setString(score);
		}
	}
	else
	{
		m_lBodyPos.push_front(next);

		mapLayer->SetMapBlank(next.x,next.y,false);
		mapLayer->SetMapBlank(m_lBodyPos.back().x,m_lBodyPos.back().y,true);

		CCSprite* snake = m_lpBody.back();
		snake->setPosition(ccp(m_iOrigin.x+next.x*m_iBodyRect.size.width,m_iOrigin.y+next.y*m_iBodyRect.size.height));

		m_lpBody.pop_back();
		m_lpBody.push_front(snake);
		m_lBodyPos.pop_back();
	}
	return true;
}
#include "Snake.h"
#include "SnakeMapScene.h"

bool Snake::init()
{
	m_lpBody.clear();
	m_lBodyPos.clear();
	m_eDir = eDir_Right;
}

void Snake::onEnter()
{
	m_iOrigin = CCDirector::sharedDirector()->getVisibleOrigin();

	SnakeMap* mapLayer = dynamic_cast<SnakeMap*>(this->getParent());
	if (mapLayer)
	{
		m_iMapSize = mapLayer->getContentSize();
		m_iBodyRect = CCRectMake(0,0,m_iMapSize.width/WIDTH_NUM,m_iMapSize.height/HEIGHT_NUM);

		CCSprite* snake = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("blank.png"));	
		snake->setTextureRect(m_iBodyRect);
		snake->setColor(ccWHITE);
		snake->setAnchorPoint(ccp(0,0));
		snake->setPosition(ccp(m_iOrigin.x+m_lBodyPos.front().x*m_iBodyRect.size.width,m_iOrigin.y+m_lBodyPos.front().y*m_iBodyRect.size.height));
		this->addChild(snake);
		m_lpBody.push_front(snake);

		CCPoint head = ccp(WIDTH_NUM/2,HEIGHT_NUM/2);
		m_lBodyPos.push_front(head);
		mapLayer->SetMapBlank(head.x,head.y,false);
	}
	else
	{
		//����
	}
}

void Snake::onExit()
{
	m_lpBody.clear();
	m_lBodyPos.clear();
}

void Snake::Move()
{
	CCPoint offset = ccp(0,0);
	CCPoint head = m_lBodyPos.front();
	//����Ƿ����
	if(m_eDir == eDir_Up)
	{
		if(head.y + 1 >= HEIGHT_NUM)
			return;
		offset.y = 1;
	}
	else if(m_eDir == eDir_Down)
	{
		if(head.y - 1 < 0)
			return;
		offset.y = -1;
	}
	else if(m_eDir == eDir_Left)
	{
		if(head.x -1 < 0)
			return;
		offset.x = -1;
	}
	else if(m_eDir == eDir_Right)
	{
		if(head.x + 1 >= WIDTH_NUM)
			return;
		offset.x = 1;
	}
	CCPoint next = ccp(head.x+offset.x,head.y+offset.y);
	//����Ƿ������Լ�
	if(m_lBodyPos.empty())
		return;
	std::list<CCPoint>::iterator it=m_lBodyPos.begin();
	//������it���ų����������head�Լ�
	for (++it;it!=m_lBodyPos.end();it++)
	{
		if(next.x == (*it).x && next.y == (*it).y)
			return;
	}
	//����Ƿ��Ǹ�ʳ��
	SnakeMap* mapLayer = dynamic_cast<SnakeMap*>(this->getParent());
	if(!mapLayer)
		return;
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
}
#include "SnakeMapScene.h"


CCScene* SnakeMap::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SnakeMap *layer = SnakeMap::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void SnakeMap::onExit()
{
	this->setTouchEnabled(false);
}

// on "init" you need to initialize your instance
bool SnakeMap::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	srand((unsigned int)time(NULL));

	this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(SnakeMap::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

//     // add "HelloWorld" splash screen"
//     CCSprite* pSprite = CCSprite::create("HelloWorld.png");
// 
//     // position the sprite on the center of the screen
//     pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
// 
//     // add the sprite as a child to this layer
//     this->addChild(pSprite, 0);
    
	memset(m_bBlank,true,sizeof(bool)*WIDTH_NUM*HEIGHT_NUM);
	m_lBody.clear();
	m_lTex.clear();
	CCPoint head = ccp(WIDTH_NUM/2,HEIGHT_NUM/2);
	m_lBody.push_front(head);
	m_bBlank[(int)head.x][(int)head.y] = false;
	m_eDir = eDir_Right;

	CCSize size = this->getContentSize();
	CCRect rect = CCRectMake(0,0,size.width/WIDTH_NUM,size.height/HEIGHT_NUM);

	CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage("blank.png");
	CCSprite* snake = CCSprite::createWithTexture(tex);
	snake->setTextureRect(rect);
	snake->setColor(ccWHITE);
	snake->setAnchorPoint(ccp(0,0));
	snake->setPosition(ccp(origin.x+head.x*rect.size.width,origin.y+head.y*rect.size.height));
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(SnakeMap::moveForward),this,0.5,false);
	this->addChild(snake,0);
	m_lTex.push_front(snake);

	AddFood();
// 	CCSprite* food = CCSprite::createWithTexture(tex);
// 	food->setTextureRect(rect);
// 	food->setColor(ccWHITE);
// 	food->setAnchorPoint(ccp(0,0));
// 	food->setPosition(ccp(origin.x+m_iFood.x*rect.size.width,origin.y+m_iFood.y*rect.size.height));
// 	this->addChild(food,0,2);
    return true;
}

void SnakeMap::AddFood()
{
	//剩余多少空位
	int left = HEIGHT_NUM*WIDTH_NUM - m_lBody.size();
	int index = (int)(rand()%left + 1);
	int count = 0;
	for (int i=0;i<HEIGHT_NUM*WIDTH_NUM;i++)
	{
		if(m_bBlank[i%WIDTH_NUM][i/WIDTH_NUM] == true)
		{
			count++;
			if(count == index)
			{
				m_iFood.x = i%WIDTH_NUM;
				m_iFood.y = i/WIDTH_NUM;
				m_bBlank[i%WIDTH_NUM][i/WIDTH_NUM] = false;
				break;
			}
		}
	}
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize size = this->getContentSize();
	CCRect rect = CCRectMake(0,0,size.width/WIDTH_NUM,size.height/HEIGHT_NUM);
	CCSprite* food = dynamic_cast<CCSprite*>(this->getChildByTag(2));
	if(food == NULL)
	{
		food = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("blank.png"));
		food->setTextureRect(rect);
		food->setColor(ccWHITE);
		food->setAnchorPoint(ccp(0,0));
		this->addChild(food,0,2);
	}
	food->setPosition(ccp(origin.x+m_iFood.x*rect.size.width,origin.y+m_iFood.y*rect.size.height));
}

void SnakeMap::moveForward(float dt)
{
	CCPoint offset = ccp(0,0);
	CCPoint head = m_lBody.front();
	//检测是否出界
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
	//检测是否碰到自己
	if(m_lBody.empty())
		return;
	std::list<CCPoint>::iterator it=m_lBody.begin();
	//先自增it，排除待检测点就是head自己
	for (++it;it!=m_lBody.end();it++)
	{
		if(next.x == (*it).x && next.y == (*it).y)
			return;
	}
	//检测是否是个食物
	CCSize size = this->getContentSize();
	CCRect rect = CCRectMake(0,0,size.width/WIDTH_NUM,size.height/HEIGHT_NUM);
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	if(next.x == m_iFood.x && next.y == m_iFood.y)
	{
		m_lBody.push_front(next);
		AddFood();


		
		CCSprite* snake = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("blank.png"));
		snake->setTextureRect(rect);
		snake->setColor(ccWHITE);
		snake->setAnchorPoint(ccp(0,0));
		snake->setPosition(ccp(origin.x+next.x*rect.size.width,origin.y+next.y*rect.size.height));
		this->addChild(snake,0);
		m_lTex.push_front(snake);
	}
	else
	{
		m_lBody.push_front(next);

		m_bBlank[(int)next.x][(int)next.y] = false;
		m_bBlank[(int)m_lBody.back().x][(int)m_lBody.back().y] = true;
		CCSprite* snake = m_lTex.back();
		snake->setPosition(ccp(origin.x+next.x*rect.size.width,origin.y+next.y*rect.size.height));
		m_lTex.pop_back();
		m_lTex.push_front(snake);

		m_lBody.pop_back();
	}

// 	CCSprite* snake = dynamic_cast<CCSprite*>(this->getChildByTag(1));
// 	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
// 	CCSize size = this->getContentSize();
// 	CCRect rect = CCRectMake(0,0,size.width/WIDTH_NUM,size.height/HEIGHT_NUM);
// 	snake->setPosition(ccp(origin.x+next.x*rect.size.width,origin.y+next.y*rect.size.height));
}

bool SnakeMap::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint location = pTouch->getLocation();
	CCSize size = this->getContentSize();
	float y1 = -1*size.height/size.width*location.x+size.height;
	float y2 = size.height/size.width*location.x;
	if(location.y < y1 && location.y < y2)
	{
		m_eDir = eDir_Down;
	}
	else if (location.y > y1 && location.y > y2)
	{
		m_eDir = eDir_Up;
	}
	else if (location.y < y1 && location.y > y2)
	{
		m_eDir = eDir_Left;
	}
	else if (location.y > y1 && location.y < y2)
	{
		m_eDir = eDir_Right;
	}
	return true;
}

void SnakeMap::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void SnakeMap::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void SnakeMap::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}


void SnakeMap::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

#include "SnakeMapScene.h"
#include "Snake.h"


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


	Snake* snake = Snake::create();
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(SnakeMap::snakeMove),this,0.5,false);
	this->addChild(snake,0,1);


	AddFood();
    return true;
}

void SnakeMap::AddFood()
{
	// £”‡∂‡…Ÿø’Œª
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

void SnakeMap::snakeMove(float dt)
{
	Snake* snake = dynamic_cast<Snake*>(this->getChildByTag(1));
	if (snake)
	{
		snake->Move();
	}
}

void SnakeMap::SetMapBlank(int x,int y,bool val)
{
	if(x >=0 && x < WIDTH_NUM && y >= 0 && y < HEIGHT_NUM)
		m_bBlank[x][y] = val;
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

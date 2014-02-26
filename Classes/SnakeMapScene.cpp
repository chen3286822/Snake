#include "SnakeMapScene.h"


#define WIDTH_NUM 30
#define HEIGHT_NUM 20

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
    
	m_iPos = ccp(WIDTH_NUM/2,HEIGHT_NUM/2);
	m_eDir = eDir_Right;
	CCSize size = this->getContentSize();
	CCRect rect = CCRectMake(0,0,size.width/WIDTH_NUM,size.height/HEIGHT_NUM);
	CCSprite* snake = CCSprite::create("blank.png");
	snake->setTextureRect(rect);
	snake->setColor(ccWHITE);
	snake->setAnchorPoint(ccp(0,0));
	snake->setPosition(ccp(origin.x+m_iPos.x*rect.size.width,origin.y+m_iPos.y*rect.size.height));
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(SnakeMap::moveForward),this,1,false);
	this->addChild(snake,0,1);
    return true;
}

void SnakeMap::moveForward(float dt)
{
	if(m_eDir == eDir_Up)
	{
		if(m_iPos.y + 1 >= HEIGHT_NUM)
			return;
		m_iPos.y += 1;
	}
	else if(m_eDir == eDir_Down)
	{
		if(m_iPos.y - 1 < 0)
			return;
		m_iPos.y -= 1;
	}
	else if(m_eDir == eDir_Left)
	{
		if(m_iPos.x -1 < 0)
			return;
		m_iPos.x -= 1;
	}
	else if(m_eDir == eDir_Right)
	{
		if(m_iPos.x + 1 >= WIDTH_NUM)
			return;
		m_iPos.x += 1;
	}
	CCSprite* snake = dynamic_cast<CCSprite*>(this->getChildByTag(1));
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize size = this->getContentSize();
	CCRect rect = CCRectMake(0,0,size.width/WIDTH_NUM,size.height/HEIGHT_NUM);
	snake->setPosition(ccp(origin.x+m_iPos.x*rect.size.width,origin.y+m_iPos.y*rect.size.height));
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

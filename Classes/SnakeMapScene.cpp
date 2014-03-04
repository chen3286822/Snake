#include "SnakeMapScene.h"
#include "TouchLayer.h"
#include "Snake.h"
#include "LoseScene.h"


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
	CCLayer::onExit();

	CCUserDefault::sharedUserDefault()->setIntegerForKey("Score",m_nScore);
	CCUserDefault::sharedUserDefault()->flush();
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

	//设定地图层大小位置
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSize controlSize = CCSizeMake(size.width,size.height-DATA_HEIGHT);
	this->setContentSize(controlSize);
	this->setPosition(0,DATA_HEIGHT);
	
	//分数初始化
	m_nScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("Score",0);

	srand((unsigned int)time(NULL));

    


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(SnakeMap::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + controlSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
	char score[256];
	sprintf(score,"Score : %d",m_nScore);
    CCLabelTTF* pLabel = CCLabelTTF::create(score, "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + controlSize.width/2,
                            origin.y + controlSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 0,eID_Score);

//     // add "HelloWorld" splash screen"
//     CCSprite* pSprite = CCSprite::create("HelloWorld.png");
// 
//     // position the sprite on the center of the screen
//     pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
// 
//     // add the sprite as a child to this layer
//     this->addChild(pSprite, 0);
	CCLayer* touchLayer = TouchLayer::create();
	this->addChild(touchLayer,0,eID_TouchLayer);
    
	memset(m_bBlank,true,sizeof(bool)*WIDTH_NUM*HEIGHT_NUM);

	CCTextureCache::sharedTextureCache()->addImage("blank.png");


	CCNode* snake = Snake::create();
	this->addChild(snake,0,eID_Snake);

	AddFood();

    return true;
}

void SnakeMap::onEnterTransitionDidFinish()
{
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(SnakeMap::snakeMove),this,0.25,false);
}

void SnakeMap::AddFood()
{
	//剩余多少空位
	Snake* snake = dynamic_cast<Snake*>(this->getChildByTag(eID_Snake));
	if(!snake)
		return;
	int left = HEIGHT_NUM*WIDTH_NUM - snake->GetBodyLength();
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
	CCSprite* food = dynamic_cast<CCSprite*>(this->getChildByTag(eID_Food));
	if(food == NULL)
	{
		food = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("blank.png"));
		food->setTextureRect(rect);
		food->setColor(ccWHITE);
		food->setAnchorPoint(ccp(0,0));
		this->addChild(food,0,eID_Food);
	}
	food->setPosition(ccp(origin.x+m_iFood.x*rect.size.width,origin.y+m_iFood.y*rect.size.height));
}

void SnakeMap::ChangeScene()
{
	//解除定时函数
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(SnakeMap::snakeMove),this);

	CCScene* loseScene = LoseLayer::scene();
	CCTransitionScene * ts=CCTransitionFlipAngular::create(2,loseScene);
	CCDirector::sharedDirector()->replaceScene(ts);
}

void SnakeMap::snakeMove(float dt)
{
	Snake* snake = dynamic_cast<Snake*>(this->getChildByTag(eID_Snake));
	if (snake)
	{
		if(snake->Move() == false)
		{
			//切换到失败场景
			ChangeScene();
		}
	}
}

void SnakeMap::SetMapBlank(int x,int y,bool val)
{
	if(x >=0 && x < WIDTH_NUM && y >= 0 && y < HEIGHT_NUM)
		m_bBlank[x][y] = val;
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

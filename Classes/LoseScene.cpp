#include "LoseScene.h"
#include "SnakeMapScene.h"
#include "DataLayer.h"


CCScene* LoseLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LoseLayer *layer = LoseLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void LoseLayer::onEnter()
{
	CCLayer::onEnter();

	CCLayer* dataLayer = DataLayer::create();
	CCNode* scene = this->getParent();
	if (scene)
	{
		scene->addChild(dataLayer,0,eID_DataLayer);
	}
}

void LoseLayer::onExit()
{
	CCLayer::onExit();
}

// on "init" you need to initialize your instance
bool LoseLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemFont *pRetryItem = CCMenuItemFont::create( "Retry",this,menu_selector(LoseLayer::menuRetryCallback));
    
	pRetryItem->setPosition(ccp(origin.x + visibleSize.width/2,origin.y + visibleSize.height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pRetryItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);


    return true;
}


void LoseLayer::menuRetryCallback(CCObject* pSender)
{
	CCScene* snakeScene = SnakeMap::scene();
	CCTransitionScene * ts=CCTransitionFlipAngular::create(2,snakeScene);
	CCDirector::sharedDirector()->replaceScene(ts);
}
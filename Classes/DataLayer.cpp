#include "DataLayer.h"



void DataLayer::onExit()
{
	CCLayer::onExit();

	CCUserDefault::sharedUserDefault()->setIntegerForKey("Score",m_nScore);
	CCUserDefault::sharedUserDefault()->flush();
}

// on "init" you need to initialize your instance
bool DataLayer::init()
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
                                        menu_selector(DataLayer::menuCloseCallback));
    
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

    return true;
}

void DataLayer::menuCloseCallback(CCObject* pSender)
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

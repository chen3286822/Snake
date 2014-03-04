#ifndef __USER_DATA_H__
#define __USER_DATA_H__

#include "cocos2d.h"
#include "Unity.h"
USING_NS_CC;

class UserData : CCObject
{
	CC_PROPERTY(int, m_nScore, Score)

public:
	static UserData* sharedUserData();

public:
	virtual ~UserData();
	virtual bool init();

	void WriteData();
};

#endif
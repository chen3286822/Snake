#include "UserData.h"

static UserData* s_SharedUserData= NULL;

UserData* UserData::sharedUserData()
{
	if (!s_SharedUserData)
	{
		s_SharedUserData = new UserData();
		s_SharedUserData->init();
	}

	return s_SharedUserData;
}

UserData::~UserData()
{
	WriteData();
}

bool UserData::init()
{
	m_nScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("Score",0);
	return true;
}

void UserData::WriteData()
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Score",m_nScore);
	CCUserDefault::sharedUserDefault()->flush();
}

void UserData::setScore(int var)
{
	m_nScore = var;
}

int UserData::getScore()
{
	return m_nScore;
}
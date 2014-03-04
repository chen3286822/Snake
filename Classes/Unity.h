#ifndef __UNITY_H__
#define __UNITY_H__

enum eDirection
{
	eDir_Up,
	eDir_Down,
	eDir_Left,
	eDir_Right,
};

#define WIDTH_NUM 30
#define HEIGHT_NUM 20
#define DATA_HEIGHT 50

enum eID
{
	eID_TouchLayer = 0,
	eID_Snake = 1,
	eID_Food = 2,
	eID_Score = 3,
	eID_SnakeMap = 4,
	eID_DataLayer = 5,
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...)
#endif


#endif
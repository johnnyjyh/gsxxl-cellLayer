#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;

#define winSize Director::getInstance()->getWinSize()
#define towerArea (((float)265/(float)640)*((float)winSize.height))

enum CellColor : int
{
			red = 0,
			pink,
			yellow,
			green,
			blue,
			blueand,
			purple,
			snowBlock,
			normalDiamond,
};

enum PlateColor :int
{
			snowPlate=50,
			stellPlate,
};


enum CellGlobalZorder :int
{
			cellZorder = 1000,
			snowBlockZorder ,
			normalDiamondZorder,
};

enum PlateGlobalZorder :int
{
			snowPlateZorder = 1003,
			stellPlateZorder ,
};





const std::map < std::string , double > CellSpeed
{
			{"norCellSpeed",1.0},
			{"snowBlockSpeed",0},
			{"snowPlateSpeed",0},
			{"stellPlateSpeed",0},
			{"diamondSpeed",1.0},
};

enum CellLife :int
{
			cellLife = 1,
			snowBlockLife = 1,		
			normalDiamondLife=1,
};

enum PlateLife :int 
{
			snowPlateLife = 1,
			stellPlateLife = 2,
};
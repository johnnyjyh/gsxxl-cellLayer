#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;



#define winSize Director::getInstance()->getWinSize()
#define towerArea (((float)265/(float)640)*((float)winSize.height))

//cell≈‰÷√
#define CellConfig_LocalCellCol 7
#define CellConfig_LocalCellRow 5
#define CellConfig_PlateHorizontalCol 7
#define CellConfig_PlateHorizontalRow 6
#define CellConfig_PlateVecticalCol 8
#define CellConfig_PlateVecticalRow 5

#define CellColorCN 0
#define PlateColorCN 100;





constexpr std::map<std::string, std::string> _StringTypeFile
{
			{red, ""},
			{ pink, },
			{ yellow, },
			{ green,"operating_ green.png" },
			{ blue,"operating_blue.png" },
			{ blueand, },
			{ purple,"operating_ purple.png" },
			{ snowBlock, "operating_obstacle_004.png"},
			{ normalDiamond,"operating_obstacle_005.png" },
			{ grass,"operating_obstacle_009.png"},
}



enum CellColor : int
{
			red = 1,
			pink,
			yellow,
			green,
			blue,
			blueand,
			purple,//6
			snowBlock,//7
			normalDiamond,//8
			grass,//9
};

enum PlateColor :int
{
			snowPlate=101,
			stellPlate,
};


enum CellGlobalZorder :int
{
			cellZorder = 100,
			snowBlockZorder ,
			normalDiamondZorder,
};

enum PlateGlobalZorder :int
{
			snowPlateZorder = 200,
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





struct CellConfiguration
{
			int _localCell[CellConfig_LocalCellCol][CellConfig_LocalCellRow];
			int _plateHorizontal[CellConfig_PlateHorizontalCol][CellConfig_PlateHorizontalRow];
			int _plateVectical[CellConfig_PlateVecticalCol][CellConfig_PlateVecticalRow];
};
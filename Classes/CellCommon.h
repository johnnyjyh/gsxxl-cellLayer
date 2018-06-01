#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;



#define winSize Director::getInstance()->getWinSize()

#define getSingleTiledSize (Vec2((float)(winSize.width/7),(float)(winSize.height/14)))
#define tileinterval (float)(winSize.width/7)




//cell≈‰÷√
#define CellConfig_LocalCellCol 7
#define CellConfig_LocalCellRow 5
#define CellConfig_PlateHorizontalCol 7
#define CellConfig_PlateHorizontalRow 6
#define CellConfig_PlateVecticalCol 8
#define CellConfig_PlateVecticalRow 5

#define CellColorCN 0
#define PlateColorCN 100

#define PlateVerticalLeftIdx 1.1
#define CellEliminateKind 7

//speed
#define CellConfig_CellSpeed 0.3

#define blinkTag 1








enum alignas(alignof(int)) CellColor : int
{
						nullCell = 0,
						red = 1,
						pink,
						yellow,
						green,
						blue,
						blueand,
						purple,
						snowBlock,
						normalDiamond,
						grass,
						nullPlate = 100,
						snowPlate = 101,
						stellPlate,
};






enum CellGlobalZorder :int
{
			cellZorder = 100,
};

enum PlateGlobalZorder :int
{
			PlateZorder = 200,
};

enum MonsGlobalZorder:int
{
			monsZorder = 300,
};

enum ItemGlobalZorder:int
{
			itemZorder = 400,
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
			normalDiamondLife = 1,
			grassLife = 1,
};

enum PlateLife :int 
{
			snowPlateLife = 1,
			stellPlateLife = 2,
};

enum LineZorder
{
			line = 10000,
};




struct CellConfiguration
{
			int _localCell[CellConfig_LocalCellCol][CellConfig_LocalCellRow];
			int _plateHorizontal[CellConfig_PlateHorizontalCol][CellConfig_PlateHorizontalRow];
			int _plateVectical[CellConfig_PlateVecticalCol][CellConfig_PlateVecticalRow];
};

const std::map<int,std::string> _EnumTypeFromStringCell
{
			{ static_cast<int>(CellColor::red),"red" },
			{ static_cast<int>(CellColor::pink),"pink" },
			{ static_cast<int>(CellColor::yellow),"yellow" },
			{ static_cast<int>(CellColor::green),"green" },
			{ static_cast<int>(CellColor::blue),"blue" },
			{ static_cast<int>(CellColor::blueand),"blueand" },
			{ static_cast<int>(CellColor::purple),"purple" },
			{ static_cast<int>(CellColor::snowBlock),"snowBlock" },
			{ static_cast<int>(CellColor::normalDiamond),"normalDiamond" },
			{ static_cast<int>(CellColor::grass),"grass" },
			{ static_cast<int>(CellColor::snowPlate),"snowPlate" },
			{ static_cast<int>(CellColor::stellPlate),"stellPlate" },
};


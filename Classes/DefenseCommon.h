#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;




#define winSize Director::getInstance()->getWinSize()

//monster config
#define amendMonsterPositon(index) (index*winSize.width/7+winSize.width/14)

//analysis  the single tiled size

#define TowerConfig_Column 5
#define TowerConfig_Row 1
#define MonsterConfig_Column 5
#define MonsterConfig_Row 11
#define singleTiledSize (winSize.width/7)
#define fillingColumnSize 25
#define fillingRowSize 20
#define defenseColumn(n) (singleTiledSize*(n)+singleTiledSize+fillingColumnSize)
#define defenseRow(n) ((n)*(singleTiledSize-18)+fillingRowSize)



enum DefenseType:int
{
			notype = 0,
			monster1 = 11,
			tower1 = 101,
			bullet1 = 201,
};

enum  BulletParaMeter :int
{
			bulletAtt1 = 1,
			bulletLif1 = 1,
			bulletZoder = 200,
};


enum MonsterParaMeter :int
{

			monsterLif1 = 1,
			monsterSpeed1 = 1,
			monsterAtt1 = 1,
			monsterZoder = 10,
			
};

enum TowerParaMeter :int
{
			towerLif1 = 3,
			towerZoder = 100,
};

struct DefenseConfiguration
{
			struct MonsterConfig
			{
						DefenseType m_type;
						double delaytime;
						int col;
						int row;
			};
			int _towerConfig[TowerConfig_Column][TowerConfig_Row];
			std::vector<MonsterConfig> _monsterConfig[MonsterConfig_Column];
};

const std::map<int, std::string> _EnumTypeFromStringDefense
{			
			{ static_cast<int>(DefenseType::monster1),"monster1" },
			{ static_cast<int>(DefenseType::tower1),"tower1" },
			{ static_cast<int>(DefenseType::bullet1),"bullet1" },
};

namespace DefenseAnimationFile
{
			const std::string  BulletCreate = "BulletCreate";
			const std::string BulletCreateFile = "fort1_%d.png";
			const std::string BulletCrash = "BulletCrash";
			const std::string BulletCrashFile = "fort1_burst%d.png";
			const std::string TowerCreate = "TowerCreate";
			const std::string TowerCreateFile = "battery_attack_%03d.png";
			const std::string MonsterCreate = "MonsterCreate";
			const std::string MonsterCreateFile = "pumpkin_rest_%03d.png";
			const std::string MonsterWalk = "MonsterWalk";
			const std::string MonsterWalkFile = "pumpkin_walk_%03d.png";
			const std::string MonsterDeath = "MonsterDeath";
			const std::string MonsterDeathFile = "pumpkin_death_%03d.png";
			const int BulletCreateBegin = 1;
			const int BulletCreateEnd = 11;
			const int BulletCrashBegin = 1;
			const int BulletCrashEnd = 12;
			const int TowerCreateBegin = 1;
			const int TowerCreateEnd = 11;
			const int MonsterCreateBegin = 1;
			const int MonsterCreateEnd = 15;
			const int MonsterWalkBegin = 1;
			const int MonsterWalkEnd = 12;
			const int MonsterDeathBegin = 1;
			const int MonsterDeathEnd = 10;

};


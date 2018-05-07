#ifndef __Common_H__
#define __Common_H__
#define _Test_
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;

#define winSize (Director::getInstance()->getWinSize())
#define randPos (rand()%5)
#define amendMonsterPositon(index) (index*winSize.width/7+winSize.width/14)
#define getSingleTiledSize (Vec2((float)(winSize.width/7),(float)(winSize.height/14)))
#define tileinterval (float)(winSize.width/7)
#define towerArea (((float)265/(float)640)*((float)winSize.height))


enum MonsterZorder
{
			monsterZ1 = 1,
};

enum MonsterLife
{
			monsterL1 = 1,
};

enum MonsterSpeed
{
			monsterS1 = 5,
};

enum Score
{
			monsterScore1 = 1,
};

enum CellsColor : int
{
			red = 0,
			pink,
			yellow,
			green,
			blue,
			blueand,
			purple,
			snowBlock,
			snowPlate,
			stellPlate,
			normalDiamond,
};

enum globalZorder :int
{
			CellsZorder = 30,
};

enum CellsHealth
{
			redHealth = 1,
			pinkHealth=1,
			yellowHealth=1,
			greenHealth=1,
			blueHealth=1,
			blueandHealth=1,
			purpleHealth=1,
			snowBlockHealth=1,
			snowPlateHealth=1,
			stellPlateHealth=1,
			normalDiamondHealth=1,
};

namespace TowerItem
{
			enum TowerOrignal
			{
						life = 3,
						damage = 1,
						speed = 1,
			};
};

//�������ɼ��ʣ����������ؿ��Ͳ���
enum CellCreatProbability
{
			//redProbability = 10,
			//pinkProbability = 5,
			//yellowProbability = 25,
			//greenProbability = 5,
			//blueProbability = 20,
			//blueandProbability = 25,
			//purpleProbability = 10,

			redProbability = 100,
			pinkProbability = 0,
			yellowProbability = 0,
			greenProbability = 0,
			blueProbability = 0,
			blueandProbability = 0,
			purpleProbability = 0,


};

class DrawSpriteFrame
{
public:
			static DrawNode * drawSpriteFrame(Sprite *sp)
			{

						auto draw = DrawNode::create();					
						draw->drawRect(Vec2(sp->getBoundingBox().getMinX(),sp->getBoundingBox().getMinY()), Vec2(sp->getBoundingBox().getMaxX(),sp->getBoundingBox().getMaxY()), Color4F::GREEN);																		
						sp->addChild(draw);
						return draw;
			}
};


namespace BarrierType
{
			enum Block
			{
						SnowBlock = 11,

			};

			enum Plate
			{
						SnowPlate = 21,
						SteelPlate = 22,

			};

			enum Diamond
			{
						NormalDiamond = 41,
			};
};



#endif //__Common_H__
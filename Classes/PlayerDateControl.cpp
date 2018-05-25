#include "PlayerDateControl.h"







PlayerDateControl *PlayerDateControl::_instance = nullptr;

PlayerDateControl::PlayerDateControl()
{
}


PlayerDateControl::~PlayerDateControl()
{
			delete _instance;
			_instance = nullptr;
}

PlayerDateControl * PlayerDateControl::getInstance()
{
			if (_instance == nullptr)
			{
						_instance = new (std::nothrow) PlayerDateControl;
						if (_instance && _instance->init())
						{
									return _instance;
						}
			}
			return _instance;
}

bool PlayerDateControl::init()
{
			auto ret = false;
			do 
			{
						loadAnimate();			
						//初始化 随机数种子
						initRandEngine();
					
						//进入开始界面

						//初始化游戏界面数据  ，从configuration.json 读取配置文件




						ret = true;
			} while (0);


			return ret;
}

Scene * PlayerDateControl::turnToGamePlayScene()
{					

			return GamePlayerScene::createScene(_config);
}

void PlayerDateControl::initRandEngine()
{
			std::default_random_engine generator(time(NULL));
			std::uniform_int_distribution<int> dis(1,8);
			auto dice = std::bind(dis, generator);

			for (int col = 0; col < CellConfig_LocalCellCol; ++col)
			{
						for (int row = 0; row < CellConfig_LocalCellRow; ++row)
						{
									_config._localCell[col][row] = dice();
						}
			}

			std::uniform_int_distribution<int> dis2(100, 101);
			auto dice2 = std::bind(dis2, generator);

			for (int col = 0; col < CellConfig_PlateHorizontalCol; ++col)
			{
						for (int row = 0; row < CellConfig_PlateHorizontalRow; ++row)
						{
									if(row== CellConfig_PlateHorizontalRow-1)
									{
												_config._plateHorizontal[col][row] = 100;
												continue;
									}
									_config._plateHorizontal[col][row] = dice2();
						}
			}

			std::uniform_int_distribution<int> dis3(100, 101);
			auto dice3 = std::bind(dis3, generator);
			for (auto col = 0; col < CellConfig_PlateVecticalCol; ++col)
			{
						for (auto row = 0; row < CellConfig_PlateVecticalRow; ++row)
						{
									_config._plateVectical[col][row] = dice3();
						}
			}

			
}

void PlayerDateControl::loadCellConfigJSon()
{

}

bool PlayerDateControl::loadAnimate()
{
			auto ret = false;
			do
			{
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("battery_attack/tower_create.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tower/tower_bullet_attack.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tower/tower_bullet_burst.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pumpkin_walk/pumpkin_walk.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pumpkin_rest/pumpkin_reset.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pumpkin_death/pumpkin_death.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tiled/tiled.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tower/tower_life.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("playerItem/lifeItem.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tiled/barrier.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("playerItem/cellItem.plist");

						ret = true;
			} while (0);

			return ret;
}


/////////////////////////////////////////////

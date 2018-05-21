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
			std::uniform_int_distribution<int> dis(1,1);
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

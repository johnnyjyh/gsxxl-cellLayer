#include "PlayerDataControl.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "json/rapidjson.h"






PlayerDataControl *PlayerDataControl::_instance = nullptr;

PlayerDataControl::PlayerDataControl()
{
}


PlayerDataControl::~PlayerDataControl()
{
			delete _instance;
			_instance = nullptr;
}

PlayerDataControl * PlayerDataControl::getInstance()
{
			if (_instance == nullptr)
			{
						_instance = new (std::nothrow) PlayerDataControl;
						if (_instance && _instance->init())
						{
									return _instance;
						}
			}
			return _instance;
}

bool PlayerDataControl::init()
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

Scene * PlayerDataControl::turnToGamePlayScene()
{					

			return GamePlayerScene::createScene(_config);
}

void PlayerDataControl::initRandEngine()
{
			
			loadCellConfigJSon("/test.json");
			/*for (int col = 0; col < CellConfig_LocalCellCol; ++col)
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
			}*/

			
}

bool PlayerDataControl::loadCellConfigJSon(const std::string filename)
{
			auto ret = false;
			do 
			{
						std::default_random_engine generator(time(NULL));
						std::uniform_int_distribution<int> dis(1, 7);
						auto dice = std::bind(dis, generator);

						rapidjson::Document doc;

						std::string load_str;
						load_str = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
						CC_BREAK_IF(load_str.empty());
						doc.Parse<0>(load_str.c_str());

						CC_BREAK_IF(doc.HasParseError());
						//CC_BREAK_IF(!doc.IsArray());

						for (unsigned int i = 0; i < doc.Size(); ++i)
						{
									int j = 0;
									for (auto &p : doc[i].GetObject())
									{
												for (unsigned int k = 0; k < p.value.Size(); ++k)
												{

															if (p.name.GetString()==(std::string("cell")+std::to_string(j)))
															{
																		if (p.value[k].GetInt() != 0)
																		{
																					_config._localCell[k][CellConfig_LocalCellRow-1-j] = p.value[k].GetInt();
																		}
																		else
																		{
																					_config._localCell[k][CellConfig_LocalCellRow - 1 - j] = dice();
																		}
															}
															else if (p.name.GetString() == (std::string("honrizontal") + std::to_string(j)))
															{
																		_config._plateHorizontal[k][CellConfig_PlateHorizontalRow-1-j] = p.value[k].GetInt()+100;
															}
															else if (p.name.GetString() == (std::string("vertical") + std::to_string(j)))
															{
																		_config._plateVectical[k][CellConfig_PlateVecticalRow-1-j] = p.value[k].GetInt()+100;
															}
															else
															{
																		log("PlayerDataControl-loadCellConfigJSon-p.name.GetString():wrong");
															}
												}
											
												++j;
									}
									
						}
						ret = true;
			} while (0);
			return ret;
}

bool PlayerDataControl::loadAnimate()
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

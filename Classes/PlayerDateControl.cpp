#include "PlayerDateControl.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "json/rapidjson.h"






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
						//��ʼ�� ���������
						initRandEngine();
					
						//���뿪ʼ����

						//��ʼ����Ϸ��������  ����configuration.json ��ȡ�����ļ�




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

bool PlayerDateControl::loadCellConfigJSon(const std::string filename)
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

									std::string str;
									if (i == 0)
									{
												str += "cell";
									}
									else if (i == 1)
									{
												str += "honrizontal";
									}
									else if (i == 2)
									{
												str += "vertical";
									}
									int j = 0;
									for (auto &p : doc[i].GetObject())
									{

												str += std::to_string(j);
												for (unsigned int k = 0; k < doc[i][str.c_str()].Size(); ++k)
												{

															if (i == 0)
															{
																		if (doc[i][str.c_str()][k].GetInt() != 0)
																		{
																					_config._localCell[j][CellConfig_LocalCellRow - 1 - k] = doc[i][str.c_str()][k].GetInt();
																		}
																		else
																		{
																					_config._localCell[j][CellConfig_LocalCellRow - 1 - k] = dice();
																		}
															}
															else if (i == 1)
															{
																		_config._plateHorizontal[j][CellConfig_PlateHorizontalRow - 1 - k] = doc[i][str.c_str()][k].GetInt()+100;
															}
															else if (i == 2)
															{
																		_config._plateVectical[j][CellConfig_PlateVecticalRow - 1 - k] = doc[i][str.c_str()][k].GetInt()+100;
															}
												}
												str.pop_back();
												++j;
									}
									str.clear();
						}
						ret = true;
			} while (0);
			return ret;
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

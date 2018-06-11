#include "PlayerDataControl.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "json/rapidjson.h"
#include "DefenseUIControler.h"
using namespace  rapidjson; 


#define GameOverEventPriority 12345


PlayerDataControl *PlayerDataControl::_instance = nullptr;

PlayerDataControl::PlayerDataControl()
{
}


PlayerDataControl::~PlayerDataControl()
{
			/*if(_instance!=nullptr)
			{
						delete _instance;
						_instance = nullptr;
			}*/
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

void PlayerDataControl::destroyInstance()
{
			if(_instance!=nullptr)
			{
						delete _instance;
						_instance = nullptr;
			}
}

bool PlayerDataControl::init()
{
			auto ret = false;
			do 
			{
																
						loadAnimate();			
						//初始化 随机数种子
						initRandEngine("level//cell//cell1.json", "level//defense//defense1.json");
						CC_BREAK_IF(!initAnimate());
						//进入开始界面

						//初始化游戏界面数据  ，从configuration.json 读取配置文件

						m_disp = Director::getInstance()->getEventDispatcher();

						auto eventGameOver = EventListenerCustom::create("GameOver", CC_CALLBACK_1(PlayerDataControl::getEventToGameOver, this));
						m_disp->addEventListenerWithFixedPriority(eventGameOver, GameOverEventPriority);


						ret = true;
			} while (0);


			return ret;
}

Scene * PlayerDataControl::turnToGamePlayScene()
{					

			return GamePlayerScene::createScene(m_cell_config,m_defense_config);
}

void PlayerDataControl::initRandEngine(const std::string & cellConfigFile, const std::string & defenseConfigFile)
{
			
			loadCellConfigJSon(cellConfigFile);
			
			loadDefenseConfigJSon(defenseConfigFile);
		
}

bool PlayerDataControl::loadCellConfigJSon(const std::string filename)
{
			auto ret = false;
			do 
			{
						/*std::default_random_engine generator(time(NULL));
						std::uniform_int_distribution<int> dis(1, 5);
						auto dice = std::bind(dis, generator);
						*/



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
																					m_cell_config._localCell[k][CellConfig_LocalCellRow-1-j] = p.value[k].GetInt();
																		}
																		else
																		{
																					m_cell_config._localCell[k][CellConfig_LocalCellRow - 1 - j] = random(1, 1);
																		}
															}
															else if (p.name.GetString() == (std::string("honrizontal") + std::to_string(j)))
															{
																		m_cell_config._plateHorizontal[k][CellConfig_PlateHorizontalRow-1-j] = p.value[k].GetInt()+100;
															}
															else if (p.name.GetString() == (std::string("vertical") + std::to_string(j)))
															{
																		m_cell_config._plateVectical[k][CellConfig_PlateVecticalRow-1-j] = p.value[k].GetInt()+100;
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

bool PlayerDataControl::loadDefenseConfigJSon(const std::string filename)
{
			auto ret = false;
			do 
			{

						rapidjson::Document doc;
						std::string load_str;
						load_str = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
						
						CC_BREAK_IF(load_str.empty());
						doc.Parse<0>(load_str.c_str());
						
						CC_BREAK_IF(doc.HasParseError());
						
						for (unsigned int i = 0; i < doc.Size(); ++i)
						{
									int j = 0;
									for (auto &p : doc[i].GetObject())
									{

												if (p.name.GetString() == (std::string("tower") + std::to_string(j)))
												{
															

																		if (p.value.GetInt() !=11)
																		{
																					m_defense_config._towerConfig[j][0] = p.value.GetInt();
																		}
																		else
																		{
																					m_defense_config._towerConfig[j][0] = 1 + TowerParaMeter::towerZoder;
																		}
															
												}
												else if (p.name.GetString() == (std::string("monster")))
												{
															DefenseConfiguration::MonsterConfig newMonCon;
															newMonCon.col = p.value[0].GetInt();
															newMonCon.row = p.value[1].GetInt();
															newMonCon.m_type =static_cast<DefenseType>(p.value[2].GetInt());
															newMonCon.delaytime = p.value[3].GetInt();
															m_defense_config._monsterConfig.push_back(newMonCon);
												}
												else
												{
															log("PlayerDataControl-loadDefenseConfigJSon-p.name.GetString():wrong");
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
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tower/towerhealth.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("playerItem/lifeItem.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tiled/barrier.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("playerItem/cellItem.plist");

						ret = true;
			} while (0);

			return ret;
}

void PlayerDataControl::getEventToGameOver(EventCustom * eventCus)
{
			
			if (eventCus == nullptr)
			{
						Director::getInstance()->resume();
						return;
			}
			//unscheduleUpdate();
			//removeAllChildrenWithCleanup(true);

			//build  restart or quit game
			if (PlayerDataControl::getInstance()!=nullptr)
			{
						

						auto scene = GamePlayerScene::createScene(m_cell_config, m_defense_config);
						
						Director::getInstance()->replaceScene(scene);
			}

}
bool PlayerDataControl::initAnimate()
{
			auto ret = false;
			do
			{
						char buf[255];
						Vector<SpriteFrame *>spriteFrameVec;
						Animation *animation = nullptr;
						//bullet
						for (int i = DefenseAnimationFile::BulletCreateBegin; i < DefenseAnimationFile::BulletCreateEnd; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, DefenseAnimationFile::BulletCreateFile.c_str(), i);
									SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
									spriteFrameVec.pushBack(sf);
						}
						animation = Animation::createWithSpriteFrames(spriteFrameVec, 0.18f, 1);
						CC_BREAK_IF(animation == nullptr);
						AnimationCache::getInstance()->addAnimation(animation, DefenseAnimationFile::BulletCreate);
						spriteFrameVec.clear();
						for (int i = DefenseAnimationFile::BulletCrashBegin; i < DefenseAnimationFile::BulletCrashEnd; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, DefenseAnimationFile::BulletCrashFile.c_str(), i);
									SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
									spriteFrameVec.pushBack(sf);
						}
						animation = Animation::createWithSpriteFrames(spriteFrameVec, 0.18f, 1);
						CC_BREAK_IF(animation == nullptr);
						AnimationCache::getInstance()->addAnimation(animation, DefenseAnimationFile::BulletCrash);
						spriteFrameVec.clear();
						//tower
						for (int i = DefenseAnimationFile::TowerCreateBegin; i < DefenseAnimationFile::TowerCreateEnd; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, DefenseAnimationFile::TowerCreateFile.c_str(), i);
									SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
									spriteFrameVec.pushBack(frame);
						}
						animation = Animation::createWithSpriteFrames(spriteFrameVec, 0.1f, 1);
						CC_BREAK_IF(animation == nullptr);
						AnimationCache::getInstance()->addAnimation(animation, DefenseAnimationFile::TowerCreate);
						spriteFrameVec.clear();
						//monster
						for (int i = DefenseAnimationFile::MonsterCreateBegin; i < DefenseAnimationFile::MonsterCreateEnd; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, DefenseAnimationFile::MonsterCreateFile.c_str(), i);
									SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
									spriteFrameVec.pushBack(sf);
						}
						animation = Animation::createWithSpriteFrames(spriteFrameVec, 0.1f, 1);
						CC_BREAK_IF(animation == nullptr);
						AnimationCache::getInstance()->addAnimation(animation, DefenseAnimationFile::MonsterCreate);
						spriteFrameVec.clear();
						for (int i = DefenseAnimationFile::MonsterWalkBegin; i < DefenseAnimationFile::MonsterWalkEnd; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, DefenseAnimationFile::MonsterWalkFile.c_str(), i);
									SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
									spriteFrameVec.pushBack(sf);
						}
						animation = Animation::createWithSpriteFrames(spriteFrameVec, 0.1f, -1);
						CC_BREAK_IF(animation == nullptr);
						AnimationCache::getInstance()->addAnimation(animation, DefenseAnimationFile::MonsterWalk);
						spriteFrameVec.clear();
						for (int i = DefenseAnimationFile::MonsterDeathBegin; i < DefenseAnimationFile::MonsterDeathEnd; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, DefenseAnimationFile::MonsterDeathFile.c_str(), i);
									SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
									spriteFrameVec.pushBack(sf);
						}
						animation = Animation::createWithSpriteFrames(spriteFrameVec, 0.1f, 1);
						CC_BREAK_IF(animation == nullptr);
						AnimationCache::getInstance()->addAnimation(animation, DefenseAnimationFile::MonsterDeath);
						spriteFrameVec.clear();
						ret = true;
			} while (0);
			return ret;
}
/////////////////////////////////////////////

#include "DefenseGameLogic.h"


DefenseGameLogic *DefenseGameLogic::_instance = nullptr;

DefenseGameLogic::DefenseGameLogic()
{
}


DefenseGameLogic::~DefenseGameLogic()
{
			
}

DefenseGameLogic * DefenseGameLogic::getInstance(DefenseConfiguration & config)
{
			if(_instance==nullptr)
			{
						_instance= new (std::nothrow) DefenseGameLogic;
						_instance->retain();
						_instance->init(config);
			}
			return _instance;
}

DefenseGameLogic * DefenseGameLogic::getInstance()
{
			if (_instance == nullptr)
			{
						log("0011:DefenseGameLogic-getInstance:_instance==nullptr!");
			}
			return _instance;
			
}

bool DefenseGameLogic::init(DefenseConfiguration & config)
{
			auto ret = false;
			do 
			{
						Node::init();
						m_eventDis = Director::getInstance()->getEventDispatcher();
						setIsTransform(false);					
						monster_config = config;
						CC_BREAK_IF(!initMonster());
						CC_BREAK_IF(!initTower());

						schedule(SEL_SCHEDULE(&DefenseGameLogic::GameLogicMainLoop),1.0f,CC_REPEAT_FOREVER,0.0f);
						

						ret = true;
			} while (0);
			return ret;
}

bool DefenseGameLogic::initMonster()
{
			auto ret = false;
			do 
			{
						for(int i=0;i<MonsterConfig_Column;++i)
						{
									for(auto monsCon:monster_config._monsterConfig[i])
									{
											
												Monster *mons = nullptr;
												if(monsCon.m_type==DefenseType::notype)
												{
															continue;
												}
												else if(monsCon.m_type==DefenseType::monster1)
												{															
															mons = Monster::create();
															mons->setColumn(monsCon.col);
															mons->setRow(monsCon.row);
															mons->setBuildTime(monsCon.delaytime);
															mons->setLife(MonsterParaMeter::monsterLif1);
															mons->setSpeed(static_cast<double>(MonsterParaMeter::monsterSpeed1*1.0));
															mons->setType(static_cast<int>(DefenseType::monster1));
															mons->setPos(i);
															mons->setCanMove(true);
															mons->setCanAttack(true);
															mons->setMoving(false);
															mons->setDataTransForm(false);
															mons->setAttack((double)MonsterParaMeter::monsterAtt1);
															EventCustom createMons = EventCustom(DefenseAnimationFile::MonsterCreate);
															createMons.setUserData((void *)mons);
															m_eventDis->dispatchEvent(&createMons);
												}

												if(mons!=nullptr)
												{
															m_monster.push_back(mons);
												}

									}
						}

						ret = true;
			} while (0);
			return ret;
}

bool DefenseGameLogic::initTower()
{
			auto ret = false;
			do
			{

						for (int j = 0; j < TowerConfig_Column; ++j)
						{
									for (int i = 0; i < TowerConfig_Row; ++i)
									{
												Tower *tow = nullptr;
												if(monster_config._towerConfig[j][i]==DefenseType::notype)
												{
															continue;
												}
												else if(monster_config._towerConfig[j][i]==DefenseType::tower1)
												{
															tow = Tower::create();
															tow->setColumn(j);
															tow->setRow(i);
															tow->setType((int)DefenseType::tower1);
															tow->setPos(j);
															//tow->bindBullet();
															tow->setLife(TowerParaMeter::towerLif1);
															tow->setCanMove(false);
															tow->setCanAttack(true);
															tow->setMoving(false);
															tow->setDataTransForm(false);
															EventCustom createTow= EventCustom(DefenseAnimationFile::TowerCreate);
															createTow.setUserData((void *)tow);
															m_eventDis->dispatchEvent(&createTow);

												}
												if(tow!=nullptr)
												{
															m_tower.push_back(tow);
												}
									}
						}
						ret = true;
			} while (0);
			return ret;;
}

void DefenseGameLogic::GameLogicMainLoop(float dt)
{
			//monster
			//check the runtime for prepare to go down the road
			//if the timing take monster go to where it should be going
			//and give some actions on its going
			_isTransform = false;			
			if(!m_monster.empty())
			{
						for(auto mons:m_monster)
						{
									if (mons!=nullptr&&mons->getLife() > 0)
									{
												if(mons->getCanMove() && ! (mons->getMoving())&&mons->getRow()>1)
												{
															mons->setMoving(true);
															auto i = mons->getRow();
															mons->setRow(i-1);
															EventCustom eve = EventCustom(DefenseAnimationFile::MonsterWalk);
															eve.setUserData(mons);
															m_eventDis->dispatchEvent(&eve);
															_isTransform = true;
															
												}
									}
						}
						
			}

			//tower  
			//ever 3 times take a shoot for monster
			

			//check when tower bullet ,the bullet hit the monster?
			//if hit the monster do something  with bullet & monster
			//if not  clear the bullet 

}


void DefenseGameLogic::monsterClear()
{
			std::vector<std::vector<Monster *>::iterator> desmons;
			for(auto mons=m_monster.begin();mons!=m_monster.end();++mons)
			{
						if(*mons==nullptr)
						{
									desmons.push_back(mons);
						}
						else if((*mons)->getLife()<=0)
						{
									(*mons)->destroy();
									(*mons) = nullptr;
									desmons.push_back(mons);
						}
			}

			for(auto des:desmons)
			{
						m_monster.erase(des);
			}
			desmons.clear();

}

void DefenseGameLogic::towerClear()
{
			std::vector<std::vector<Tower *>::iterator> destow;
			for(auto tow=m_tower.begin();tow!=m_tower.end();++tow)
			{
						if(*tow==nullptr)
						{
									destow.push_back(tow);
						}
						else if((*tow)->getLife()<=0)
						{
									(*tow)->destroy();
									*tow = nullptr;
									destow.push_back(tow);
						}
			}
			for(auto des:destow)
			{
						m_tower.erase(des);
			}
			destow.clear();
}

void DefenseGameLogic::onEnter()
{
			Node::onEnter();
}

void DefenseGameLogic::onExit()
{
			Node::onExit();
			unschedule(SEL_SCHEDULE(&DefenseGameLogic::GameLogicMainLoop));
}

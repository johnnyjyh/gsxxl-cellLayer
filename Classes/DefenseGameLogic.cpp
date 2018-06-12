#include "DefenseGameLogic.h"






DefenseGameLogic::DefenseGameLogic()
{
			DefenseDatabase::m_dataBaseNumber = 0;
}


DefenseGameLogic::~DefenseGameLogic()
{
			
}





DefenseGameLogic *DefenseGameLogic::create(DefenseConfiguration & config)
{
			auto ret = new DefenseGameLogic;
			if(ret && ret->init(config))
			{
						ret->autorelease();
			}
			else
			{
						delete ret;
						ret = false;
			}
			return ret;
}



bool DefenseGameLogic::init(DefenseConfiguration & config)
{
			auto ret = false;
			do 
			{
						monster_config = config;
						Node::init();
						setShootScore(0);					
						m_eventDis = Director::getInstance()->getEventDispatcher();
						setIsTransform(false);					
						
						CC_BREAK_IF(!initMonster());
						CC_BREAK_IF(!initTower());

						schedule(SEL_SCHEDULE(&DefenseGameLogic::GameLogicMainLoop),0.0f,CC_REPEAT_FOREVER,0.0f);
						

						ret = true;
			} while (0);
			return ret;
}

bool DefenseGameLogic::initMonster()
{
			auto ret = false;
			do 
			{
						
									for(auto monsCon:monster_config._monsterConfig)
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
															mons->setPos(monsCon.col);
															mons->setCanMove(true);
															mons->setCanAttack(true);
															mons->setMoving(false);
															mons->setDataTransForm(false);
															mons->setAttack((double)MonsterParaMeter::monsterAtt1);
															mons->setIsDead(false);
														
															/*EventCustom createMons = EventCustom(DefenseAnimationFile::MonsterCreate);
															createMons.setUserData((void *)mons);
															m_eventDis->dispatchEvent(&createMons);*/
												}

												if(mons!=nullptr)
												{
															m_AllMonster.push_back(mons);
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
															tow->setIsDead(false);

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
			m_MainLoopTime += dt;
			_isTransform = false;
			//deal with deadData
			monsterClear();
			bulletClear();
			towerClear();
			
			for(auto mons=m_AllMonster.begin();mons!=m_AllMonster.end();)
			{
						if( *mons!=nullptr && m_MainLoopTime >= (*mons)->getBuildTime())
						{
									EventCustom createMons = EventCustom(DefenseAnimationFile::MonsterCreate);
									createMons.setUserData((void *)*mons);
									m_eventDis->dispatchEvent(&createMons);
									m_monster.push_back(*mons);
									mons = m_AllMonster.erase(mons);
						}
						else
						{
									++mons;
						}
			}

			
			

			
		
			
			
			if(!m_tower.empty())
			{
						if(m_MainLoopTime>=0.1)
						{
									for (auto tow : m_tower)
									{
												if (tow != nullptr && !tow->m_trans)
												{
															EventCustom creattow = EventCustom(DefenseAnimationFile::TowerCreate);
															creattow.setUserData((void *)tow);
															m_eventDis->dispatchEvent(&creattow);
												}
									}
						}
					
						
						do 
						{
									if (m_shootScore >= ShootRecordTime)
									{
												Monster *closeMons = nullptr;
												for (auto mons : m_monster)
												{
															if (mons == nullptr)
															{
																		continue;
															}
															if (closeMons == nullptr)
															{
																		closeMons = mons;
															}
															else
															{
																		if (mons->getRow() < closeMons->getRow())
																		{
																					closeMons = mons;
																		}
															}
												}


												if (closeMons == nullptr)
												{
															break;
												}
												for (auto tow : m_tower)
												{
															//Éä»÷
															
															if (tow != nullptr&&closeMons->getColumn() == tow->getColumn()&& tow->getLife()>=0)
															{
																		tow->bindBullet();
																		EventCustom eve = EventCustom(DefenseAnimationFile::BulletCreate);
																		eve.setUserData(tow->getBullet());
																		m_eventDis->dispatchEvent(&eve);
																		m_bullet.push_back(tow->getBullet());
																		break;
															}
															

												}
												m_shootScore -= ShootRecordTime;
									}
						} while (0);
										
			}

			//deal bullet
			if(!m_bullet.empty())
			{
						for(auto bullet:m_bullet)
						{
									if(bullet!=nullptr)
									{
												//search the monster close with tower
												auto mons = findTheCloseMons(bullet);
												if(mons!=nullptr&&bullet->getLife()>0)
												{
															for(int i=0;i<bullet->getAttack();++i)
															{
																		mons->loseLife();																	
															}
															EventCustom eve = EventCustom(DefenseAnimationFile::BulletCrash);
															eve.setUserData(mons);
															m_eventDis->dispatchEvent(&eve);
												}											
												//É¾³ý×Óµ¯
												bullet->setLife(0);
												
									}
						}
			}




			if(!m_monster.empty())
			{						
						for(auto mons:m_monster)
						{
									if (mons!=nullptr&&mons->getLife() > 0&&! mons->getIsDead())
									{
												if(mons->getCanMove() && ! (mons->getMoving())&&mons->getRow()>2)
												{
															mons->setMoving(true);
															auto i = mons->getRow();
															mons->setRow(i-1);
															EventCustom eve1 = EventCustom(DefenseAnimationFile::MonsterWalk);
															eve1.setUserData(mons);
															m_eventDis->dispatchEvent(&eve1);
															_isTransform = true;
															
												}
												else if(mons->getCanMove() && !(mons->getMoving()) && mons->getRow()<=2)
												{														
															
															//Ëþ¼õÑª´¥·¢
															Tower *tower = nullptr;
															for(auto tow:m_tower)
															{
																		
																		if(tow!=nullptr && tow->getColumn()==mons->getColumn())
																		{
																					tower = tow;
																					break;
																		}
															}
															if(tower==nullptr||tower->getLife()<0)
															{
																		
																		if(mons->getRow()>1)
																		{
																					mons->setMoving(true);
																					auto i = mons->getRow();
																					mons->setRow(i - 1);
																					EventCustom eve1 = EventCustom(DefenseAnimationFile::MonsterWalk);
																					eve1.setUserData(mons);
																					m_eventDis->dispatchEvent(&eve1);
																		}
																		else
																		{
																					EventCustom eve = EventCustom("GameOver");
																					m_eventDis->dispatchEvent(&eve);
																		}
																	
															}
															else
															{
																	
																		mons->setIsDead(true);
																		mons->setLife(0);
																		EventCustom eve2 = EventCustom(DefenseAnimationFile::MonsterDeath);
																		eve2.setUserData(mons);
																		m_eventDis->dispatchEvent(&eve2);
																		if(tower->getLife()==0)
																		{
																					
																					
																					tower->loseLife();
																					EventCustom eve = EventCustom("TowerDestroy");
																					eve.setUserData(tower);
																					m_eventDis->dispatchEvent(&eve);
																		}
																		else if(tower->getLife()>0)
																		{
																					
																					tower->loseLife();
																					EventCustom eve = EventCustom("TowerLoseLife");
																					eve.setUserData(tower);
																					m_eventDis->dispatchEvent(&eve);
																		}
																	

															}
															_isTransform = true;
												}
									}
									else if(mons != nullptr&&mons->getLife() <=0&& !mons->getIsDead())
									{
												mons->setIsDead(true);
												EventCustom eve3 = EventCustom(DefenseAnimationFile::MonsterDeath);
												eve3.setUserData(mons);
												m_eventDis->dispatchEvent(&eve3);
												_isTransform = true;
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
			
			for(auto mons=m_monster.begin();mons!=m_monster.end();)
			{
						if(*mons==nullptr)
						{
									mons=m_monster.erase(mons);
						}
						else if((*mons)->getLife()<=0)
						{
									(*mons)->destroy();
									*mons = nullptr;
									mons=m_monster.erase(mons);
						}
						else
						{
									++mons;
						}
			}

		

}

void DefenseGameLogic::towerClear()
{

			for(auto tow=m_tower.begin();tow!=m_tower.end();)
			{
						if(*tow==nullptr)
						{
									tow = m_tower.erase(tow);
						}
						else if((*tow)->getLife()<0)
						{
									(*tow)->destroy();
									*tow = nullptr;
									tow = m_tower.erase(tow);								
						}
						else
						{
									++tow;
						}
			}

}

void DefenseGameLogic::bulletClear()
{
			for (auto bullet = m_bullet.begin(); bullet != m_bullet.end();)
			{
						if (*bullet == nullptr)
						{
									bullet = m_bullet.erase(bullet);
						}
						else if ((*bullet)->getLife() <= 0)
						{
									for(auto tow:m_tower)
									{
												if(tow->getBullet()!=nullptr && tow->getBullet()->getSignNumber()==(*bullet)->getSignNumber())
												{
															tow->destroyBullet();
															break;
												}
									}
									*bullet = nullptr;
									bullet = m_bullet.erase(bullet);
						}
						else
						{
									++bullet;
						}
			}
}

void DefenseGameLogic::acceptScore(long score)
{
			m_shootScore += score;
}


Monster * DefenseGameLogic::findTheCloseMons(TowerBullet * bullet)
{
			if(bullet==nullptr)
			{
						return nullptr;
			}
			int indexCol = bullet->getColumn();

			Monster *target = nullptr;
			for(auto mons:m_monster)
			{
						if(mons->getColumn()==indexCol)
						{
									if(target==nullptr)
									{
												target = mons;
									}
									else
									{
												if(mons->getRow()<target->getRow())
												{
															target = mons;
												}
									}
						}
			}
			return target;
}



void DefenseGameLogic::onEnter()
{
			Node::onEnter();
}

void DefenseGameLogic::onExit()
{
			Node::onExit();
			unschedule(SEL_SCHEDULE(&DefenseGameLogic::GameLogicMainLoop));
			for (auto mons = m_monster.begin(); mons != m_monster.end();++mons)
			{					
									if(*mons!=nullptr)
									{
												(*mons)->destroy();
									}
																		
			}
			for (auto tow = m_tower.begin(); tow != m_tower.end(); ++tow)
			{
									if(*tow !=nullptr)
									{
												(*tow)->destroy();
									}									
			}
			m_monster.clear();
			m_tower.clear();
			
}

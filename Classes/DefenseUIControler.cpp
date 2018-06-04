#include "DefenseUIControler.h"
#include "DefenseGameLogic.h"

#define fixedRow (6.4)

DefenseUIControler::DefenseUIControler()
{
}


DefenseUIControler::~DefenseUIControler()
{
			DefenseGameLogic::getInstance()->release();
}

DefenseUIControler * DefenseUIControler::create(DefenseConfiguration & config)
{
			auto ret = new (std::nothrow) DefenseUIControler;
			if(ret && ret->init(config))
			{
						ret->autorelease();
			}
			else
			{
						delete ret;
						ret = nullptr;
			}
			return ret;
}

bool DefenseUIControler::init(DefenseConfiguration & config)
{
			auto ret = false;
			do 
			{
						m_config = config;									
						Layer::init();
						CC_BREAK_IF(!initAnimation());
						
						
						 m_dispatcher = Director::getInstance()->getEventDispatcher();
						 //register MonsterCreate
						auto eventMonsCreate = EventListenerCustom::create(DefenseAnimationFile::MonsterCreate, CC_CALLBACK_1(DefenseUIControler::getEventToCreateMonster,this));
						m_dispatcher->addEventListenerWithFixedPriority(eventMonsCreate,DefenseType::monster1);
						//register TowerCreate
						auto eventTowerCreate = EventListenerCustom::create(DefenseAnimationFile::TowerCreate, CC_CALLBACK_1(DefenseUIControler::getEventToCreateTower, this));
						m_dispatcher->addEventListenerWithFixedPriority(eventTowerCreate, DefenseType::tower1);
						//register MonsterMove
						auto eventMonsMove = EventListenerCustom::create(DefenseAnimationFile::MonsterWalk, CC_CALLBACK_1(DefenseUIControler::getEventToMoveMonster, this));
						m_dispatcher->addEventListenerWithFixedPriority(eventMonsMove, DefenseType::monster1+1);


						ret = true;
			} while (0);
			return ret;
}

bool DefenseUIControler::initAnimation()
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
									sprintf(buf,DefenseAnimationFile::BulletCreateFile.c_str(), i);
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
									sprintf(buf, DefenseAnimationFile::BulletCrashFile.c_str(), i );
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
									sprintf(buf, DefenseAnimationFile::TowerCreateFile.c_str(), i );
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
									sprintf(buf, DefenseAnimationFile::MonsterCreateFile.c_str(), i );
									SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
									spriteFrameVec.pushBack(sf);
						}
						animation = Animation::createWithSpriteFrames(spriteFrameVec, 0.1f, 1);
						CC_BREAK_IF(animation == nullptr);
						AnimationCache::getInstance()->addAnimation(animation, DefenseAnimationFile::MonsterCreate);
						spriteFrameVec.clear();
						for (int i = DefenseAnimationFile::MonsterWalkBegin; i <DefenseAnimationFile::MonsterWalkEnd; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, DefenseAnimationFile::MonsterWalkFile.c_str(), i );
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
									sprintf(buf, DefenseAnimationFile::MonsterDeathFile.c_str(), i );
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

void DefenseUIControler::createMonster(DefenseUI * ui)
{
			if(ui==nullptr)
			{
						return;
			}
			else
			{
				
						
					
						auto animate = Animate::create(AnimationCache::getInstance()->getAnimation(DefenseAnimationFile::MonsterCreate));
						
						auto func = CallFuncN::create([=](Node *node) {
							  if(node==nullptr)
							  {
										  return;
							  }
							  auto animate2 = Animate::create(AnimationCache::getInstance()->getAnimation(DefenseAnimationFile::MonsterWalk));
							  node->runAction(animate2);
						});

						auto seq = Sequence::create(animate,func , NULL);
						ui->getSprite()->runAction(seq);
			}
}

void DefenseUIControler::createTower(DefenseUI * ui)
{
			if (ui == nullptr)
			{
						return;
			}
			else
			{
						auto animate = Animate::create(AnimationCache::getInstance()->getAnimation(DefenseAnimationFile::TowerCreate));
						ui->getSprite()->runAction(RepeatForever::create(animate));
			}
}

void DefenseUIControler::createBullet(DefenseUI * ui)
{
			if (ui == nullptr)
			{
						return;
			}
			else
			{
						auto animate = Animate::create(AnimationCache::getInstance()->getAnimation(DefenseAnimationFile::BulletCreate));
						ui->getSprite()->runAction(animate);
			}
}

void DefenseUIControler::moveMonster(uint64_t monsterID, Monster *&mons, int col, int row)
{
			if(m_UIMonsters[monsterID]==nullptr)
			{
						return;
			}
			else
			{
						m_UIMonsters[monsterID]->getSprite()->stopAllActions();
						auto animate = Animate::create(AnimationCache::getInstance()->getAnimation(DefenseAnimationFile::MonsterWalk));						
						auto moveto = MoveTo::create(MonsterParaMeter::monsterSpeed1-8, m_UIMonsters[monsterID]->convertToNodeSpace(Vec2(defenseColumn(col), defenseRow(row+fixedRow)) ));
						auto func = CallFuncN::create([&](Node *node) {
									if(mons==nullptr)
									{
												return;
									}
									mons->setMoving(false);
						});

						auto seq = Sequence::create(moveto,func, NULL);
						m_UIMonsters[monsterID]->getSprite()->runAction(RepeatForever::create(animate));
						m_UIMonsters[monsterID]->getSprite()->runAction(seq);
			}
}

void DefenseUIControler::getEventToCreateMonster(EventCustom *eventCus)
{
			if (eventCus == nullptr)
			{
						return;
			}
			auto mons = static_cast<Monster *>(eventCus->getUserData());
			auto ui = DefenseUI::create(static_cast<DefenseType>(mons->getType()));
			if (ui == nullptr)
			{
						return;
			}
			ui->setSignNum(mons->getSignNumber());
			ui->setPosition(getParent()->convertToNodeSpace(Vec2(defenseColumn(mons->getColumn()), defenseRow(mons->getRow()))));
			addChild(ui, mons->getType() + MonsterParaMeter::monsterZoder);
			createMonster(ui);
			m_UIMonsters.insert({ mons->getSignNumber(), ui });


}

void DefenseUIControler::getEventToMoveMonster(EventCustom * eventCus)
{
			if(eventCus==nullptr)
			{
						return;
			}
			auto mons = static_cast<Monster *>(eventCus->getUserData());
			auto ui = m_UIMonsters[mons->getSignNumber()];
			if(ui==nullptr)
			{
						return;
			}
			ui->stopAllActions();
					
			auto moveto = MoveTo::create(MonsterParaMeter::monsterSpeed1, getParent()->convertToNodeSpace(Vec2(defenseColumn(mons->getColumn()), defenseRow(mons->getRow()))));
			auto func = CallFuncN::create([=](Node *node) {
						if (mons == nullptr)
						{
									return;
						}
						mons->setMoving(false);
			});
			auto seq = Sequence::create(moveto, NULL);
			mons->setMoving(false);
			ui->runAction(seq);
}

void DefenseUIControler::getEventToCreateTower(EventCustom * eventCus)
{
			if (eventCus == nullptr)
			{
						return;
			}
			auto tow = static_cast<Tower *>(eventCus->getUserData());
			auto ui = DefenseUI::create(static_cast<DefenseType>(tow->getType()));
			if (ui == nullptr)
			{
						return;
			}
			ui->setSignNum(tow->getSignNumber());
			ui->setPosition(getParent()->convertToNodeSpace(Vec2(defenseColumn(tow->getColumn()), defenseRow(tow->getRow()) + 5)) );
			createTower(ui);
			addChild(ui, tow->getType() + TowerParaMeter::towerZoder);
			m_UITowers.insert({ tow->getSignNumber() ,ui });
}





void DefenseUIControler::DefenseUIMainLoop(float dt)
{

}

void DefenseUIControler::onEnter()
{
			Layer::onEnter();
}

void DefenseUIControler::onExit()
{
			Layer::onExit();
			//unschedule(SEL_SCHEDULE(&DefenseUIControler::DefenseUIMainLoop));
			m_dispatcher->removeCustomEventListeners(DefenseAnimationFile::MonsterCreate);
			m_dispatcher->removeCustomEventListeners(DefenseAnimationFile::MonsterWalk);
			m_dispatcher->removeCustomEventListeners(DefenseAnimationFile::TowerCreate);
			m_dispatcher->removeCustomEventListeners(DefenseAnimationFile::MonsterWalk);

}




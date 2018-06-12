#include "DefenseUIControler.h"
#include "DefenseGameLogic.h"
#include "ObjectPoolManager.h"

#define fixedRow (6.4)

DefenseUIControler::DefenseUIControler()
{
}


DefenseUIControler::~DefenseUIControler()
{
			
			
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
						//initAnimation();
						
						 m_dispatcher = Director::getInstance()->getEventDispatcher();
						 m_dispatcher->removeCustomEventListeners(DefenseAnimationFile::TowerCreate);
						 m_dispatcher->removeCustomEventListeners(DefenseAnimationFile::MonsterCreate);
						 m_dispatcher->removeCustomEventListeners(DefenseAnimationFile::MonsterWalk);
						 m_dispatcher->removeCustomEventListeners("DestoryBullet");
						 m_dispatcher->removeCustomEventListeners(DefenseAnimationFile::MonsterDeath);
						 m_dispatcher->removeCustomEventListeners(DefenseAnimationFile::BulletCreate);
						 m_dispatcher->removeCustomEventListeners(DefenseAnimationFile::BulletCrash);
						 m_dispatcher->removeCustomEventListeners("TowerLoseLife");
						 m_dispatcher->removeCustomEventListeners("TowerDestroy");

						//register TowerCreate
						auto eventTowerCreate = EventListenerCustom::create(DefenseAnimationFile::TowerCreate, CC_CALLBACK_1(DefenseUIControler::getEventToCreateTower, this));
						m_dispatcher->addEventListenerWithFixedPriority(eventTowerCreate, DefenseType::tower1);
						//register BulletCreate
						auto eventBulletCreate = EventListenerCustom::create(DefenseAnimationFile::BulletCreate, CC_CALLBACK_1(DefenseUIControler::getEventToCreateBullet, this));
						m_dispatcher->addEventListenerWithFixedPriority(eventBulletCreate, DefenseType::bullet1);
						//register BulletCrash
						auto eventBulletCrash = EventListenerCustom::create(DefenseAnimationFile::BulletCrash, CC_CALLBACK_1(DefenseUIControler::getEventToCrashBullet, this));
						m_dispatcher->addEventListenerWithFixedPriority(eventBulletCrash, DefenseType::bullet1 + 1);
						//register DestroyBullet
						auto eventBulletDestory = EventListenerCustom::create("DestoryBullet", CC_CALLBACK_1(DefenseUIControler::getEventToDestroyBullet, this));
						m_dispatcher->addEventListenerWithFixedPriority(eventBulletDestory, DefenseType::bullet1 + 2);
						//register TowerLoseLife
						auto eventTowerLoseLife = EventListenerCustom::create("TowerLoseLife", CC_CALLBACK_1(DefenseUIControler::getEventToTowerLoseLife, this));
						m_dispatcher->addEventListenerWithFixedPriority(eventTowerLoseLife, DefenseType::tower1 + 1);
						//register DestroyTower
						auto eventTowerDestroy = EventListenerCustom::create("TowerDestroy", CC_CALLBACK_1(DefenseUIControler::getEventToTowerDestroy, this));
						m_dispatcher->addEventListenerWithFixedPriority(eventTowerDestroy, DefenseType::tower1 + 2);
						//register MonsterCreate
						auto eventMonsCreate = EventListenerCustom::create(DefenseAnimationFile::MonsterCreate, CC_CALLBACK_1(DefenseUIControler::getEventToCreateMonster, this));
						m_dispatcher->addEventListenerWithFixedPriority(eventMonsCreate, DefenseType::monster1);
						//register MonsterMove
						auto eventMonsMove = EventListenerCustom::create(DefenseAnimationFile::MonsterWalk, CC_CALLBACK_1(DefenseUIControler::getEventToMoveMonster, this));
						m_dispatcher->addEventListenerWithFixedPriority(eventMonsMove, DefenseType::monster1 + 1);
						//register MonsterDeath
						auto eventMonsDeath = EventListenerCustom::create(DefenseAnimationFile::MonsterDeath, CC_CALLBACK_1(DefenseUIControler::getEventToDeathMonster, this));
						m_dispatcher->addEventListenerWithFixedPriority(eventMonsDeath, DefenseType::monster1 + 2);
						 
					
						
						
						
						
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
				
						
					
						//auto animate = Animate::create(AnimationCache::getInstance()->getAnimation(DefenseAnimationFile::MonsterCreate));
						
						/*auto func = CallFuncN::create([=](Node *node) {
							  if(node==nullptr)
							  {
										  return;
							  }
							  auto animate2 = Animate::create(AnimationCache::getInstance()->getAnimation(DefenseAnimationFile::MonsterWalk));
							  node->runAction(animate2);
						});*/
						auto animate = Animate::create(AnimationCache::getInstance()->getAnimation(DefenseAnimationFile::MonsterWalk));
						auto seq = Sequence::create(animate , NULL);
						ui->getSprite()->runAction(RepeatForever::create(seq));
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
						//auto animate = Animate::create(AnimationCache::getInstance()->getAnimation(DefenseAnimationFile::MonsterWalk));						
						auto moveto = MoveTo::create(MonsterParaMeter::monsterSpeed1-8, m_UIMonsters[monsterID]->convertToNodeSpace(Vec2(defenseColumn(col), defenseRow(row+fixedRow)) ));
						auto func = CallFuncN::create([&](Node *node) {
									if(mons==nullptr)
									{
												return;
									}
									mons->setMoving(false);
						});

						auto seq = Sequence::create(moveto,func, NULL);
						//m_UIMonsters[monsterID]->getSprite()->runAction(RepeatForever::create(animate));
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
			auto seq = Sequence::create(moveto,func, NULL);
			//mons->setMoving(false);
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
			
			
			tow->m_trans = true;
			ui->setSignNum(tow->getSignNumber());
			ui->setPosition(getParent()->convertToNodeSpace(Vec2(defenseColumn(tow->getColumn()), defenseRow(tow->getRow()) + 5)) );
			createTower(ui);


			addChild(ui, tow->getType() + TowerParaMeter::towerZoder);
			m_UITowers.insert({ tow->getSignNumber() ,ui });
			
}

void DefenseUIControler::getEventToDeathMonster(EventCustom * eventCus)
{
			
			if (eventCus == nullptr)
			{
						return;
			}
		
			auto mons = static_cast<Monster *>(eventCus->getUserData());
			auto rec_num = mons->getSignNumber();
			auto ui = m_UIMonsters[rec_num];
			if (ui == nullptr)
			{						
						return;
			}
			ui->stopAnimate();

			auto death = Animate::create(AnimationCache::getInstance()->getAnimation(DefenseAnimationFile::MonsterDeath));
			auto func = CallFuncN::create([=](Node *node) {
						/*if (mons == nullptr)
						{
									return;
						}		*/						
						ui->destroy();
						ui->getParent()->removeChild(ui);
						m_UIMonsters.erase(rec_num);
			});
			
			auto seq = Sequence::create(death, func,NULL);		
			ui->getSprite()->runAction(seq);
			
			
}

void DefenseUIControler::getEventToCreateBullet(EventCustom * eventCus)
{
			
			if (eventCus == nullptr)
			{
						return;
			}
			auto bullet = static_cast<TowerBullet *>(eventCus->getUserData());
			auto ui = DefenseUI::create(static_cast<DefenseType>(bullet->getType()));
			if (ui == nullptr)
			{
						return;
			}
			ui->setSignNum(bullet->getSignNumber());
			//bullet ²îÒì»¯
			ui->getSprite()->setAnchorPoint(Point(0.5, 0));
			ui->getSprite()->setScaleY(0.8f);

			ui->setPosition(getParent()->convertToNodeSpace(Vec2(defenseColumn(bullet->getColumn()), defenseRow(bullet->getRow()) )));
			auto animate = Animate::create(AnimationCache::getInstance()->getAnimation(DefenseAnimationFile::BulletCreate));
			auto func = CallFunc::create([=]() {
						ui->stopAnimate();
						ui->destroy();
						m_UIBullets.erase(ui->getSignNum());
						removeChild(ui);						
			});
			auto seq = Sequence::create(animate, func, NULL);
			ui->getSprite()->runAction(seq);

			addChild(ui, bullet->getType() + BulletParaMeter::bulletZoder);
			m_UIBullets.insert({ bullet->getSignNumber() ,ui });
}

void DefenseUIControler::getEventToCrashBullet(EventCustom * eventCus)
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
			auto animate = Animate::create(AnimationCache::getInstance()->getAnimation(DefenseAnimationFile::BulletCrash));

			auto spr = Sprite::create();	
			spr->setPosition(ui->getPosition());
			addChild(spr);
			auto func = CallFunc::create([=]() {
						if (spr == nullptr)
									return;
						removeChild(spr);
			});
			auto seq = Sequence::create(animate, func, NULL);
			spr->runAction(seq);
			//ui->getSprite()->runAction(animate);
}

void DefenseUIControler::getEventToDestroyBullet(EventCustom * eventCus)
{
			if(eventCus==nullptr)
			{
						return;
			}
			auto bullet = static_cast<TowerBullet *>(eventCus->getUserData());
			auto ui = m_UIBullets[bullet->getSignNumber()];
			if(ui==nullptr)
			{
						return;
			}
			ui->stopAnimate();
			ui->destroy();
			removeChild(ui);
			m_UIBullets.erase(bullet->getSignNumber());			
}

void DefenseUIControler::getEventToTowerLoseLife(EventCustom * eventCus)
{
			if(eventCus==nullptr)
			{
						return;
			}
			auto tower = static_cast<Tower *>(eventCus->getUserData());
			auto ui = m_UITowers[tower->getSignNumber()];
			if(ui==nullptr)
			{
						return;
			}
			if(ui->getLifeSlider()==nullptr)
			{
						return;
			}
			float _life =(float)tower->getLife();
			ui->getLifeSlider()->setValue(_life/ TowerParaMeter::towerLif1*100);
}

void DefenseUIControler::getEventToTowerDestroy(EventCustom * eventCus)
{
			if(eventCus==nullptr)
			{
						return;
			}
			auto tower = static_cast<Tower *>(eventCus->getUserData());
			auto ui=m_UITowers[tower->getSignNumber()];
			auto num = tower->getSignNumber();
			if(ui==nullptr)
			{
						return;
			}
			
			ui->stopAnimate();
			ui->destroy();
			removeChild(ui);
			m_UITowers.erase(num);
}







void DefenseUIControler::DefenseUIMainLoop(float dt)
{

}

void DefenseUIControler::onEnter()
{
			Layer::onEnter();
			//{
			//			auto m_dispatcher = Director::getInstance()->getEventDispatcher();

			//			//register TowerCreate
			//			auto eventTowerCreate = EventListenerCustom::create(DefenseAnimationFile::TowerCreate, CC_CALLBACK_1(DefenseUIControler::getEventToCreateTower, this));
			//			m_dispatcher->addEventListenerWithFixedPriority(eventTowerCreate, DefenseType::tower1+1000);
			//			//register BulletCreate
			//			auto eventBulletCreate = EventListenerCustom::create(DefenseAnimationFile::BulletCreate, CC_CALLBACK_1(DefenseUIControler::getEventToCreateBullet, this));
			//			m_dispatcher->addEventListenerWithFixedPriority(eventBulletCreate, DefenseType::bullet1);
			//			//register BulletCrash
			//			auto eventBulletCrash = EventListenerCustom::create(DefenseAnimationFile::BulletCrash, CC_CALLBACK_1(DefenseUIControler::getEventToCrashBullet, this));
			//			m_dispatcher->addEventListenerWithFixedPriority(eventBulletCrash, DefenseType::bullet1 + 1);
			//			//register DestroyBullet
			//			auto eventBulletDestory = EventListenerCustom::create("DestoryBullet", CC_CALLBACK_1(DefenseUIControler::getEventToDestroyBullet, this));
			//			m_dispatcher->addEventListenerWithFixedPriority(eventBulletDestory, DefenseType::bullet1 + 2);
			//			//register TowerLoseLife
			//			auto eventTowerLoseLife = EventListenerCustom::create("TowerLoseLife", CC_CALLBACK_1(DefenseUIControler::getEventToTowerLoseLife, this));
			//			m_dispatcher->addEventListenerWithFixedPriority(eventTowerLoseLife, DefenseType::tower1 + 1);
			//			//register DestroyTower
			//			auto eventTowerDestroy = EventListenerCustom::create("TowerDestroy", CC_CALLBACK_1(DefenseUIControler::getEventToTowerDestroy, this));
			//			m_dispatcher->addEventListenerWithFixedPriority(eventTowerDestroy, DefenseType::tower1 + 2);
			//			//register MonsterCreate
			//			auto eventMonsCreate = EventListenerCustom::create(DefenseAnimationFile::MonsterCreate, CC_CALLBACK_1(DefenseUIControler::getEventToCreateMonster, this));
			//			m_dispatcher->addEventListenerWithFixedPriority(eventMonsCreate, DefenseType::monster1);
			//			//register MonsterMove
			//			auto eventMonsMove = EventListenerCustom::create(DefenseAnimationFile::MonsterWalk, CC_CALLBACK_1(DefenseUIControler::getEventToMoveMonster, this));
			//			m_dispatcher->addEventListenerWithFixedPriority(eventMonsMove, DefenseType::monster1 + 1);
			//			//register MonsterDeath
			//			auto eventMonsDeath = EventListenerCustom::create(DefenseAnimationFile::MonsterDeath, CC_CALLBACK_1(DefenseUIControler::getEventToDeathMonster, this));
			//			m_dispatcher->addEventListenerWithFixedPriority(eventMonsDeath, DefenseType::monster1 + 2);
			//}
			
}

void DefenseUIControler::onEnterDidFinshLanuch()
{
			Layer::onEnterTransitionDidFinish();
			
}

void DefenseUIControler::onExit()
{
			Layer::onExit();
			//unschedule(SEL_SCHEDULE(&DefenseUIControler::DefenseUIMainLoop));
		
			/*m_dispatcher->removeCustomEventListeners(DefenseAnimationFile::MonsterCreate);
			m_dispatcher->removeCustomEventListeners(DefenseAnimationFile::MonsterWalk);
			m_dispatcher->removeCustomEventListeners(DefenseAnimationFile::TowerCreate);
			m_dispatcher->removeCustomEventListeners("DestoryBullet");
			m_dispatcher->removeCustomEventListeners(DefenseAnimationFile::MonsterDeath);
			m_dispatcher->removeCustomEventListeners(DefenseAnimationFile::BulletCreate);
			m_dispatcher->removeCustomEventListeners(DefenseAnimationFile::BulletCrash);
			m_dispatcher->removeCustomEventListeners("TowerLoseLife");
			m_dispatcher->removeCustomEventListeners("TowerDestroy");*/			
			for(auto  monster:m_UIMonsters)
			{
						if(monster.second==nullptr)
						{
									continue;
						}
						(monster.second)->destroy();
			}

			for(auto  tow:m_UITowers)
			{
						if (tow.second == nullptr)
						{
									continue;
						}
						tow.second->destroy();
			}

			for(auto  bul:m_UIBullets)
			{
						if(bul.second ==nullptr)
						{
									continue;
						}
						bul.second->destroy();
			}
			removeAllChildrenWithCleanup(true);	
}




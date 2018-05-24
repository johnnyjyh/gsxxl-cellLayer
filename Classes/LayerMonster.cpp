#include "LayerMonster.h"
#include "PlayerDateControl.h"


LayerMonster::LayerMonster()
{
}


LayerMonster::~LayerMonster()
{
}

bool LayerMonster::init()
{
			auto ret = false;
			do
			{
						char buf[255];
						for (int i = 0; i < 14; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, "pumpkin_rest_%03d.png", i + 1);
									SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
									_spriteFrameVec.pushBack(sf);
						}
						Animation *animation = Animation::createWithSpriteFrames(_spriteFrameVec, 0.1f, 1);
						AnimationCache::getInstance()->addAnimation(animation, "CreateMonster");
						_spriteFrameVec.clear();
						for (int i = 0; i < 11; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, "pumpkin_walk_%03d.png", i + 1);
									SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
									_spriteFrameVec.pushBack(sf);
						}
						animation = Animation::createWithSpriteFrames(_spriteFrameVec, 0.1f, -1);
						AnimationCache::getInstance()->addAnimation(animation, "WalkMonster");
						_spriteFrameVec.clear();
						for (int i = 0; i < 9; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, "pumpkin_death_%03d.png", i + 1);
									SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
									_spriteFrameVec.pushBack(sf);
						}
						animation = Animation::createWithSpriteFrames(_spriteFrameVec, 0.1f, 1);
						AnimationCache::getInstance()->addAnimation(animation, "DeathMonster");
						schedule(SEL_SCHEDULE(&LayerMonster::addMonster), 2.0f);
#ifdef _Test_
						testindex = 0;
#endif //_Test_
						ret = true;

			} while (0);
			return ret;
}

void LayerMonster::addMonster(float dt)
{
#ifdef _Test_
			testindex = rand() % 5 + 1;
#endif //_Test
			auto monster = Monster::create();
			_monster = monster;
			_monsterVec.pushBack(monster);
			monster->BindMonsterSprite(Sprite::createWithSpriteFrameName("pumpkin_rest_001.png"), MonsterLife::monsterL1, MonsterSpeed::monsterS1, testindex);
#ifdef _Test_
			//DrawSpriteFrame::drawSpriteFrame(monster->getSprite());
#endif  //_Test_
			monster->getSprite()->setScale(0.3f);
			auto randmon = rand() % 6 + 1;
			auto monspos = amendMonsterPositon(testindex);
			monster->getSprite()->setPosition(Vec2(monspos, winSize.height - monster->getSprite()->getBoundingBox().size.height /4));
			
			auto ani = Animate::create(AnimationCache::getInstance()->getAnimation("CreateMonster"));
			auto ani2 = Animate::create(AnimationCache::getInstance()->getAnimation("WalkMonster"));
			auto moveto = MoveTo::create(monsterS1, Vec2(monster->getSprite ()->getPosition ().x,winSize.height/2));
			auto funcN = CallFuncN::create([&,monster](Node *node) {
						node->stopAllActions();
						////////////////////
						_monsterVec.eraseObject(static_cast<Monster *>(node->getParent()));
						node->getParent()->removeFromParentAndCleanup(true);
						//PlayerDateControl::getInstance()->loseLife();
			});
			auto seq1 = Sequence::create(moveto, funcN,NULL);
			auto moveandani = Spawn::create(ani2,seq1,NULL);			
			auto seq = Sequence::create(ani,static_cast<ActionInterval *>(moveandani),NULL);
			monster->getSprite()->runAction(seq);		
			
			addChild(monster);

}



int LayerMonster::monsterDeath(Monster *monster)
{
			if (monster)
			{					
						monster->getSprite()->stopAllActions();

						auto ani = Animate::create(AnimationCache::getInstance()->getAnimation("DeathMonster"));
						auto funcNa = CallFuncN::create([&, monster](Node *node) {
									node->getParent()->removeFromParentAndCleanup(true);
									_monsterVec.eraseObject(static_cast<Monster *>(node->getParent()));
						});
						auto seq = Sequence::create(ani, funcNa, NULL);
						monster->getSprite ()->runAction(seq);				
						return Score::monsterScore1;
			}
			return 0;
}

int LayerMonster::updateMonsLife(Monster *monster,int att_Damage)
{
			
			for (int i = 0; i < att_Damage; ++i)
			{
						monster->loseLife();
			}
			if (monster->getLife() <= 0)
			{
						return monsterDeath(monster);
			}
			return 0;
}



#include "LayerTower.h"




LayerTower::LayerTower()
{
}


LayerTower::~LayerTower()
{
}



bool LayerTower::init()
{
			auto ret = false;
			do
			{
						_bulletLayer = LayerBullet::create();
						addChild(_bulletLayer, 15, "BulletLay");

						char buf[255];
						for (int i = 0; i < 10; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, "battery_attack_%03d.png", i + 1);
									SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
									_spriteFrameVec.pushBack(frame);
						}
						Animation *animation = Animation::createWithSpriteFrames(_spriteFrameVec, 0.1f, 1);
						AnimationCache::getInstance()->addAnimation(animation, "CreateTower");
						//scheduleOnce(SEL_SCHEDULE(&LayerTower::addTower),0.0f);
						initTower();
						ret = true;
			} while (0);
			return ret;
}

void LayerTower::addTower(int index)
{
			auto tower = Tower::create();
			_tower = tower;
			tower->bindTowerSprite(Sprite::createWithSpriteFrameName("battery_attack_001.png"), TowerItem::TowerOrignal::life, TowerItem::TowerOrignal::damage, TowerItem::TowerOrignal::speed);
#ifdef _Test_
			//DrawSpriteFrame::drawSpriteFrame(tower->getSprite());
#endif //_Test_		
			tower->getSprite()-> setScale(0.5f);
			
			auto ani = Animate::create(AnimationCache::getInstance()->getAnimation("CreateTower"));
			Vec2 pos = Vec2(amendMonsterPositon(index),winSize.height/2-tower->getSprite()->getBoundingBox().size.height /3+10 );
			
			tower->getSprite()->setPosition(pos);	
			tower->getSprite()->runAction(RepeatForever::create(ani));
	
			addChild(tower,21,"TowerSpr");
			_towerVec.push_back(tower);
			
			
//			schedule([&,tower](float dt) {
//						if (_bulletLayer)
//						{
//									attack(tower);
//									//spr->setPosition(Vec2(winSize.width/2, winSize.height/2));
//									
//#ifdef _Test_
//									//DrawSpriteFrame::drawSpriteFrame(static_cast<Sprite *>(spr->getSprite()));
//#endif //_Test_		
//									
//						}
//			},3.0f,"shootSch");

			
}

void LayerTower::moveTower(int index)
{
			//auto spr = static_cast<Tower *>(getChildByName("TowerSpr"))->getSprite();
			_tower->setIsAttacked(true);
			auto spr = _tower->getSprite();
			//spr->stopAllActions();
			_tower->_pos = index;
			auto pt = convertToWorldSpace (Vec2(amendMonsterPositon(index), winSize.height/2- spr->getBoundingBox().size.height / 3+10));
			auto moveTo = MoveTo::create(0.5f,pt);
			auto func = CallFuncN::create(CC_CALLBACK_1(LayerTower::attack,this));
			auto seq = Sequence::create(moveTo, func, NULL);			
			spr->runAction(seq);
#ifdef _Test_
			
#endif //_Test_
}

void LayerTower::attack(Node *node)
{
			auto tower = static_cast<Sprite *>(node);
			_bulletLayer->startShoot(Vec2(tower->getPosition().x, tower->getPosition().y + tower->getBoundingBox().size.height));
			_tower->setIsAttacked(false);
			//spr->getSprite()->setPosition(Vec2(tower->getSprite()->getPosition().x, tower->getSprite()->getPosition().y + tower->getSprite()->getBoundingBox().size.height));
}

bool LayerTower::initTower()
{
			auto ret = false;
			do
			{
						for (int i = 1; i < 6; ++i)
						{
									addTower(i);
						}
						ret = true;
			} while (0);
			return ret;

}

bool LayerTower::chechTowerPosAndAttack(int index)
{
			auto ret = false;
			do 
			{
						if (_towerVec[index - 1]->getLife() >= 0)
						{
									auto func = CallFuncN::create(CC_CALLBACK_1(LayerTower::attack, this));
									_towerVec[index - 1]->getSprite()->runAction(func);
									ret = true;
						}
			} while (0);
			return ret;
}

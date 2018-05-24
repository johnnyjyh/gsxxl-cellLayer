#include "LayerBullet.h"
#include "LayerTower.h"



LayerBullet::LayerBullet()
{
}


LayerBullet::~LayerBullet()
{
}

bool LayerBullet::init()
{
			Layer::init();
			auto ret = false;
			do
			{
						char buf[255];
						for (int i = 0; i < 10; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, "fort1_%d.png", i + 1);
									SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);								
									_spriteFrameVec.pushBack(sf);
						}
						Animation *animation = Animation::createWithSpriteFrames(_spriteFrameVec, 0.18f, 1);
						AnimationCache::getInstance()->addAnimation(animation, "CreateBullet");
						_spriteFrameVec.clear();
						for (int i = 0; i < 11; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, "fort1_burst%d.png", i + 1);
									SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
									_spriteFrameVec.pushBack(sf);
						}
						animation = Animation::createWithSpriteFrames(_spriteFrameVec, 0.18f, 1);
						AnimationCache::getInstance()->addAnimation(animation, "BulletCrash");
						ret = true;
			} while (0);
			
			return ret;
}

void LayerBullet::startShoot(const Vec2 &pos)
{
			_bullet = Bullet::create();	
			_bullet->BindMonsterSprite(Sprite::createWithSpriteFrameName("fort1_1.png"), 1, 0, 0);
			_bullet->setPosition(pos);
#ifdef _Test_
			//DrawSpriteFrame::drawSpriteFrame(_bullet->getSprite());
			
#endif //_Test_
			
			
			auto spr = _bullet->getSprite();
			_bulletVec.pushBack(_bullet);
			spr->setScaleX(0.5f);
			auto ani = Animate::create(AnimationCache::getInstance ()->getAnimation ("CreateBullet"));
			auto func = CallFuncN::create([&](Node *node) {			
						node->stopAllActions();
						_bulletVec.eraseObject(static_cast<Bullet *>(node->getParent()));
						node->getParent()->removeFromParentAndCleanup(true);
						node->removeAllChildren();
						node->removeFromParent();					
						//_bullet = nullptr;
			});
			auto seq = Sequence::create(ani,func,NULL);			
			spr->runAction(seq);	
			addChild(_bullet,15,"BulletSpr");

}

void LayerBullet::stopShoot()
{
			
}

void LayerBullet::addBulletCallBack(float dt)
{
}

void LayerBullet::removeBullet()
{
}

void LayerBullet::bulletCrashWithMonster(Bullet * bul, Vec2 pos)
{
			auto node = Sprite::createWithSpriteFrameName("fort1_burst1.png");
			node->setPosition(pos);
			auto anima = Animate::create(AnimationCache::getInstance()->getAnimation("BulletCrash"));
			auto func = CallFuncN::create([&](Node *node) {
						auto crash = static_cast<Sprite *>(node);
						crash->stopAllActions();				
						crash->getParent()->removeChild(node);
						crash->removeAllChildrenWithCleanup(true);
						
			});
			auto seq = Sequence::create(anima, func, NULL);
			addChild(node, 25);
			node->runAction(seq);
			
}



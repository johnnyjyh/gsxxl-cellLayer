#ifndef __LayerBullet_H__
#define __LayerBullet_H__
#include "Bullet.h"


class LayerBullet :
			public Layer
{
public:
			LayerBullet();
			~LayerBullet();
			CREATE_FUNC(LayerBullet);
			bool init();
			void startShoot(const Vec2 &pos);
			void stopShoot();
			void addBulletCallBack(float dt);
			void removeBullet();
			void bulletCrashWithMonster(Bullet *bul, Vec2 pos);

			Bullet *_bullet;			
			Vector<Bullet *> _bulletVec;
			Vector<SpriteFrame*> _spriteFrameVec;
};
#endif //__LayerBullet_H__


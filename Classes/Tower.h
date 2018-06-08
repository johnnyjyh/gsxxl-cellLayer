#pragma once
#include "TowerBullet.h"

class Tower:public DefenseDatabase
{
public:
			Tower();
			~Tower();
			static Tower *create();
			void destroy();
			void destroyBullet();
			double getAttack()noexcept {
						if(!isBulletEmpty())
						{
									return m_bullet->_attack;
						}
						else
						{
									return 0.0;
						}
			};
			void setAttack(double att)noexcept { 
						if(!isBulletEmpty())
						{
									m_bullet->_attack = att;
						}
						else
						{
									_attack = 0;
						}
			};
			void bindBullet();
			TowerBullet *getBullet() { 
						if(!isBulletEmpty())
						{
									return m_bullet;
						}
						else
						{
									return nullptr;
						}
			};
			bool isBulletEmpty() { return m_bullet == nullptr; };



			TowerBullet *m_bullet{ nullptr };
};


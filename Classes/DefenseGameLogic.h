#pragma once
#include "Tower.h"
#include "TowerBullet.h"
#include "Monster.h"
#include "cocos2d.h"
USING_NS_CC;

class DefenseGameLogic:public Node
{
public:
			DefenseGameLogic();
			~DefenseGameLogic();
			//static DefenseGameLogic *getInstance(DefenseConfiguration &config);
			static DefenseGameLogic *create(DefenseConfiguration &config);


			bool init(DefenseConfiguration &config);
			bool initMonster();
			bool initTower();
			void GameLogicMainLoop(float dt);
			

			void monsterClear();
			void towerClear();
			void bulletClear();

			
			void acceptScore(long score);
			Monster *findTheCloseMons(TowerBullet *bullet);

		
			
			void onEnter();
			void onExit();

		

			
			CC_SYNTHESIZE(bool, _isTransform, IsTransform);
			float m_MainLoopTime{ 0.0 };
			DefenseConfiguration monster_config;
			EventDispatcher * m_eventDis{ nullptr };
			CC_SYNTHESIZE(long, m_shootScore, ShootScore);
			std::vector<Monster *> m_monster;
			std::vector<Tower *> m_tower;
			std::vector<TowerBullet *> m_bullet;
			
			std::vector<Monster *> m_AllMonster;
			std::vector<Tower *> m_AllTower;
			std::vector<TowerBullet *> m_AllBullet;
};


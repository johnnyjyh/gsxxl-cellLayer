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
			static DefenseGameLogic *getInstance();
			static DefenseGameLogic *create(DefenseConfiguration &config);
			void initInstance(DefenseGameLogic *&_ins);
			void destroyInstance();
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
			static DefenseGameLogic *_instance;
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


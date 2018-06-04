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
			static DefenseGameLogic *getInstance(DefenseConfiguration &config);
			static DefenseGameLogic *getInstance();
			bool init(DefenseConfiguration &config);
			bool initMonster();
			bool initTower();
			void GameLogicMainLoop(float dt);

			void monsterClear();
			void towerClear();
			
			void onEnter();
			void onExit();

			
			CC_SYNTHESIZE(bool, _isTransform, IsTransform);
			static DefenseGameLogic *_instance;
			DefenseConfiguration monster_config;
			EventDispatcher * m_eventDis{ nullptr };
			std::vector<Monster *> m_monster;
			std::vector<Tower *> m_tower;
			std::vector<TowerBullet *> m_bullet;
			
};


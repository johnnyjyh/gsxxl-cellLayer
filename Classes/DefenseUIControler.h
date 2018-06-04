#pragma once
#include "DefenseGameLogic.h"
#include "DefenseUI.h"

class DefenseUIControler:public Layer
{
public:
			DefenseUIControler();
			~DefenseUIControler();
			static DefenseUIControler *create(DefenseConfiguration &config);
			bool init(DefenseConfiguration &config);
			bool initAnimation();
			//
			void createMonster(DefenseUI *ui);
			void createTower(DefenseUI *ui);
			void createBullet(DefenseUI *ui);
			void moveMonster(uint64_t monsterID, Monster *&mons, int col, int row);
			//


			void getEventToCreateMonster(EventCustom *eventCus);
			void getEventToMoveMonster(EventCustom *eventCus);
			
			void getEventToCreateTower(EventCustom *eventCus);




			void DefenseUIMainLoop(float dt);

			void onEnter();
			void onExit();
			//test

			DefenseConfiguration m_config;
			EventDispatcher *m_dispatcher{ nullptr };
			std::map<uint64_t,DefenseUI *> m_UITowers;
			std::map<uint64_t, DefenseUI *> m_UIMonsters;
			std::map<uint64_t, DefenseUI *> m_UIBullets;
};


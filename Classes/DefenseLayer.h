#pragma once
#include "DefenseUIControler.h"

class DefenseLayer :public Layer
{
public:
			DefenseLayer();
			~DefenseLayer();
			static DefenseLayer *create(DefenseConfiguration &config);
			bool init(DefenseConfiguration &config);
			bool initUIControler();

			void onExit();
			void onEnter();
			

			DefenseConfiguration m_monster_config;
			DefenseUIControler *m_UIControler{ nullptr };
};


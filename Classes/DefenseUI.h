#pragma once
#include "DefenseCommon.h"



class DefenseUI:public Node
{
public:
			DefenseUI();
			~DefenseUI();
			static DefenseUI *create(DefenseType type);
			bool init();
			Sprite *getSprite() { return m_spr; };
			void destroy();
			void stopAnimate();
			 ControlSlider *getLifeSlider() { return m_life_slider; };

			CC_SYNTHESIZE(uint64_t, m_sighNum, SignNum);
			DefenseType m_type;
			std::string m_typeString;
			Sprite *m_spr;
			ControlSlider *m_life_slider{ nullptr };
};


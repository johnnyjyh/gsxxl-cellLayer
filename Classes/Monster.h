#pragma once
#include "DefenseDatabase.h"

class Monster :public DefenseDatabase
{
public:
			Monster();
			~Monster();
			static Monster *create();
			void destroy();
			void setBuildTime(double time) { m_buildTime = time; };
			double getBuildTime() { return m_buildTime; };

			double m_buildTime{ 0 };
};


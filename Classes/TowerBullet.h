#pragma once
#include "DefenseDatabase.h"


class TowerBullet:public DefenseDatabase
{
public:
			TowerBullet();
			~TowerBullet();
			static TowerBullet *create();
			void destroy();
};


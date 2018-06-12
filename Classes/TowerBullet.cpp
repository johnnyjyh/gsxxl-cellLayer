#include "TowerBullet.h"



TowerBullet::TowerBullet()
{
}


TowerBullet::~TowerBullet()
{
}

TowerBullet * TowerBullet::create()
{
			auto ret = new (std::nothrow) TowerBullet;
			ret->setSignNumber();
			return ret;
}

void TowerBullet::destroy()
{
			delete this;
}

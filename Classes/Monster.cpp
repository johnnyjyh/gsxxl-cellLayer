#include "Monster.h"



Monster::Monster()
{
}


Monster::~Monster()
{
}

Monster * Monster::create()
{
			auto ret = new (std::nothrow) Monster;
			ret->setSignNumber();
			return ret;
}

void Monster::destroy()
{
			delete this;
}

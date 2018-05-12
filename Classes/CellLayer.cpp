#include "CellLayer.h"



CellLayer::CellLayer()
{
}


CellLayer::~CellLayer()
{
}

CellLayer * CellLayer::create(CellConfiguration config)
{
			auto celllayer = new (std::nothrow) CellLayer;
			if (celllayer && celllayer->init(config))
			{
						celllayer->autorelease();
			}
			else
			{
						delete celllayer;
						celllayer = nullptr;
			}
			return celllayer;
}

bool CellLayer::init(CellConfiguration config)
{
			auto ret = false;
			do 
			{

						ret = true;
			} while (0);
			return ret;
}







void CellLayer::onEnter()
{
}

void CellLayer::onExit()
{
}

#include "DefenseLayer.h"
#include "CommonConfig.h"
#include "PlayerDataControl.h"


DefenseLayer::DefenseLayer()
{
}


DefenseLayer::~DefenseLayer()
{
}

DefenseLayer * DefenseLayer::create(DefenseConfiguration & config)
{
			auto ret = new (std::nothrow) DefenseLayer;
			if(ret && ret->init(config))
			{
						ret->autorelease();
			}
			else
			{
						delete ret;
						ret = nullptr;
			}
			return ret;
}

bool DefenseLayer::init(DefenseConfiguration & config)
{
			auto ret = false;
			do 
			{
						Layer::init();
						m_monster_config = config;
						//³õÊ¼»¯UI¿ØÖÆÆ÷
						CC_BREAK_IF(!initUIControler());

						auto logic = DefenseGameLogic::create(config);
						logic->initInstance(logic);
						addChild(logic);		


						
						ret = true;
			} while (0);
			return ret;
}

bool DefenseLayer::initUIControler()
{
			auto ret = false;
			do 
			{
						m_UIControler = DefenseUIControler::create(m_monster_config);
						CC_BREAK_IF(m_UIControler == nullptr);
						m_UIControler->setAnchorPoint(Point::ZERO);
						m_UIControler->setPosition(Vec2(0, towerArea));
						addChild(m_UIControler);
						ret = true;
			} while (0);
			return ret;
}

void DefenseLayer::onExit()
{
			Layer::onExit();
			//DefenseGameLogic::getInstance()->destroyInstance();
			//removeAllChildrenWithCleanup(true);
}

void DefenseLayer::onEnter()
{
			Layer::onEnter();
}

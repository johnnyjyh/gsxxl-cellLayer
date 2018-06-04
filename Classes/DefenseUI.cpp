#include "DefenseUI.h"
#include "ObjectPoolManager.h"


DefenseUI::DefenseUI()
{
}


DefenseUI::~DefenseUI()
{
}

DefenseUI * DefenseUI::create(DefenseType type)
{
			auto ret = new (std::nothrow) DefenseUI;
			ret->m_type = type;
			if(ret && ret->init())
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

bool DefenseUI::init()
{
			auto ret = false;
			do 
			{
						//一些初始化工作
						switch (m_type)
						{
						case DefenseType::notype:
									return ret;
									break;
						case DefenseType::monster1:
									break;
						case DefenseType::tower1:
									break;
						case DefenseType::bullet1:
									break;
						default:
									break;
						}
						m_typeString = _EnumTypeFromStringDefense.at(static_cast<int>(m_type));						
						m_spr = ObjectPoolManager::getInstance()->getObject(m_typeString);
						if(m_spr==nullptr)
						{
									return ret;
						}
						if(m_type==DefenseType::monster1)
						{
									m_spr->setScale(singleTiledSize / m_spr->getContentSize().width * 2);
						}
						else if(m_type==DefenseType::tower1)
						{
									m_spr->setScale(singleTiledSize / m_spr->getContentSize().width );
						}
						else
						{
									m_spr->setScale(singleTiledSize / m_spr->getContentSize().width );
						}
						
						addChild(m_spr);
						ret = true;
			} while (0);
			return ret;
}

void DefenseUI::destroy()
{
			//归还
			ObjectPoolManager::getInstance()->pushObject(m_typeString, m_spr);
			removeChild(m_spr);
			m_spr = nullptr;
}

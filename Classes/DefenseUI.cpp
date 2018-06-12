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
			

			auto ret = new (std::nothrow)  DefenseUI();
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
									m_life_slider = ControlSlider::create(Sprite::createWithSpriteFrameName("greyhealth.png"), Sprite::createWithSpriteFrameName("lighthealth.png"), Sprite::create());
									m_life_slider->setMinimumValue(0.0f);
									m_life_slider->setMaximumValue(100.0f);
									m_life_slider->setValue(100.0f);
									m_life_slider->setEnabled(false);											
									addChild(m_life_slider,1);
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
									m_life_slider->setScale(singleTiledSize / m_spr->getBoundingBox().size.width/2);
									m_life_slider->setPosition(Vec2(0, -m_spr->getBoundingBox().size.height / 2));
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
			if(m_life_slider!=nullptr)
			{
						removeChild(m_life_slider);
						m_life_slider = nullptr;
			}
			m_spr = nullptr;
}

void DefenseUI::stopAnimate()
{
			stopAllActions();
			m_spr->stopAllActions();
}

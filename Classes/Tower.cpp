#include "Tower.h"



Tower::Tower()
{
}


Tower::~Tower()
{
			if(m_bullet!=nullptr)
			{
						m_bullet->destroy();
						m_bullet = nullptr;
			}
}

Tower * Tower::create()
{
			auto ret = new (std::nothrow) Tower;	
			ret->setSignNumber();
			return ret;
}

void Tower::destroy()
{
			delete this;
}

void Tower::bindBullet()
{
			if(m_bullet!=nullptr)
			{
						delete m_bullet;
						m_bullet = nullptr;
			}
			m_bullet = TowerBullet::create();
			switch (_type)
			{
			case DefenseType::tower1:
						m_bullet->setPos(_pos);
						m_bullet->setAttack(BulletParaMeter::bulletAtt1);
						m_bullet->setCanMove(false);
						m_bullet->setCanAttack(true);
						m_bullet->setLife(BulletParaMeter::bulletLif1);
						m_bullet->setColumn(getColumn());
						m_bullet->setRow(getRow());
						m_bullet->setDataTransForm(false);
			default:
						break;
			}
}

#include "Tower.h"



Tower::Tower()
{
}


Tower::~Tower()
{

}

Tower * Tower::create()
{
			auto ret = new (std::nothrow) Tower;	
			ret->setSignNumber();
			return ret;
}

void Tower::destroy()
{
			//destroyBullet();
			delete this;
}

void Tower::destroyBullet()
{
			if (m_bullet != nullptr)
			{
						m_bullet->destroy();
						m_bullet = nullptr;
			}
}

void Tower::bindBullet()
{

			m_bullet = TowerBullet::create();
			switch (_type)
			{
			case DefenseType::tower1:
						m_bullet->setType(DefenseType::bullet1);
						m_bullet->setPos(_pos);
						m_bullet->setAttack(BulletParaMeter::bulletAtt1);
						m_bullet->setCanMove(false);
						m_bullet->setCanAttack(true);
						m_bullet->setLife(BulletParaMeter::bulletLif1);
						m_bullet->setColumn(getColumn());
						m_bullet->setRow(getRow());
						m_bullet->setDataTransForm(false);
						m_bullet->setIsDead(false);
			default:
						break;
			}
}

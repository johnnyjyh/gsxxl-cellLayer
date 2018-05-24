#ifndef __LayerMonster_H__
#define __LayerMonster_H__
#include "Monster.h"
class LayerMonster:
			public Layer
{
public:
			LayerMonster();
			~LayerMonster();
			CREATE_FUNC(LayerMonster);
			bool init();
			void addMonster(float dt);			
			int monsterDeath(Monster *monster);
			int updateMonsLife(Monster *monster, int att_Damage);


			int testindex;

			Monster *_monster;
			Vector<SpriteFrame *> _spriteFrameVec;
			Vector<Monster *> _monsterVec;
};
#endif //__LayerMonster_H__


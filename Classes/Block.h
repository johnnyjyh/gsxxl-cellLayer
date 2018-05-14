#pragma once
#include "Cell.h"

class Block:public Cell
{
public:
			static Block *create(int col,int row,CellColor color);
			bool init();
			void destroy();




			std::vector<Vec2> _moveVec;
			Vector<FiniteTimeAction *> _moveActionVec;

};

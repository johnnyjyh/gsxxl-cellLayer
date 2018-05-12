#pragma once
#include "Cell.h"

class Block:public Cell
{
public:
			static Block *create(int col,int row,CellColor color);




			bool _isSelected{ false }; //是否被选择
			bool _isCanSelected{ false };//是否能选择
			bool _isUsedLogic{ false };//是否用于计算
			bool _isTouchBack{ false };//是否触摸返回
			bool _isMoving{ false };//是否在移动


			std::vector<Vec2> _moveVec;
			Vector<FiniteTimeAction *> _moveActionVec;

};

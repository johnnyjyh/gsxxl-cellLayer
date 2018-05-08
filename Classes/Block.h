#pragma once
#include "CellCommon.h"

class Block;public Node
{
			static Block *create(int col,int row,CellColor color);


			Sprite *_spr{nullptr};
			CC_SYNTHESIZE(int, _row, Row);
			CC_SYNTHESIZE(int, _column, Column);
			bool _isSelected{ false }; //是否被选择
			bool _isCanSelected{ false };//是否能选择
			bool _isUsedLogic{ false };//是否用于计算
			bool _isTouchBack{ false };//是否触摸返回
			bool _isMoving{ false };//是否在移动


			std::vector<Vec2> _moveVec;
			Vector<FiniteTimeAction *> _moveActionVec;

};

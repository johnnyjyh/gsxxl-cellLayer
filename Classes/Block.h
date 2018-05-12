#pragma once
#include "Cell.h"

class Block:public Cell
{
public:
			static Block *create(int col,int row,CellColor color);




			bool _isSelected{ false }; //�Ƿ�ѡ��
			bool _isCanSelected{ false };//�Ƿ���ѡ��
			bool _isUsedLogic{ false };//�Ƿ����ڼ���
			bool _isTouchBack{ false };//�Ƿ�������
			bool _isMoving{ false };//�Ƿ����ƶ�


			std::vector<Vec2> _moveVec;
			Vector<FiniteTimeAction *> _moveActionVec;

};

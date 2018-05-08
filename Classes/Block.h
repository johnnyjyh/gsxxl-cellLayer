#pragma once
#include "CellCommon.h"

class Block;public Node
{
			static Block *create(int col,int row,CellColor color);


			Sprite *_spr{nullptr};
			CC_SYNTHESIZE(int, _row, Row);
			CC_SYNTHESIZE(int, _column, Column);
			bool _isSelected{ false }; //�Ƿ�ѡ��
			bool _isCanSelected{ false };//�Ƿ���ѡ��
			bool _isUsedLogic{ false };//�Ƿ����ڼ���
			bool _isTouchBack{ false };//�Ƿ�������
			bool _isMoving{ false };//�Ƿ����ƶ�


			std::vector<Vec2> _moveVec;
			Vector<FiniteTimeAction *> _moveActionVec;

};

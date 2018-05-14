#pragma once
#include "CellCommon.h"

class Cell:public Node
{
public:

			//static Cell *create(int col,int row,CellColor color);
			virtual bool init()=0;
			virtual void destroy() = 0;
			virtual inline void setCellColor(const int color) { _color = static_cast<CellColor>(color); };
			virtual inline int getCellColor() const { return static_cast<const int>(_color); };
			virtual inline void setLife(const int life) { _life = life; };
			virtual inline  int getLife() const { return _life; };
			virtual inline Sprite * getCellSprite() const { return _spr;};

					
			
			bool _isSelected{ false }; //�Ƿ�ѡ��
			bool _isCanSelected{ false };//�Ƿ���ѡ��
			bool _isUsedLogic{ false };//�Ƿ����ڼ���
			bool _isTouchBack{ false };//�Ƿ�������
			bool _isMoving{ false };//�Ƿ����ƶ�
			bool _isCanMove{ false };//�Ƿ�����ƶ�

			
			
			Sprite* _spr{nullptr};

			std::string _colorStr;
			
			int _life{ 0 };
			CC_SYNTHESIZE(int, _row, Row);
			CC_SYNTHESIZE(int, _column, Column);
			
			CellColor _color;

};


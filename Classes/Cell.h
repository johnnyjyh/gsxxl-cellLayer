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

					
			
			bool _isSelected{ false }; //是否被选择
			bool _isCanSelected{ false };//是否能选择
			bool _isUsedLogic{ false };//是否用于计算
			bool _isTouchBack{ false };//是否触摸返回
			bool _isMoving{ false };//是否在移动
			bool _isCanMove{ false };//是否可以移动

			
			
			Sprite* _spr{nullptr};

			std::string _colorStr;
			
			int _life{ 0 };
			CC_SYNTHESIZE(int, _row, Row);
			CC_SYNTHESIZE(int, _column, Column);
			
			CellColor _color;

};


#pragma once
#include"CellCommon.h"

class Cell:public Node
{
public:
			Cell();
			~Cell();
			static Cell *create(int col,int row,CellColor color);
			



			int _life{0 };
			
			CellColor _color;		
			Sprite* _spr;			
			CC_SYNTHESIZE(int, _row, Row);
			CC_SYNTHESIZE(int, _column, Column);

};


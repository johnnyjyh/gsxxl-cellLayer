#pragma once
#include "Cell.h"

class Block:public Cell
{
public:
			static Block *create(int col,int row,CellColor color);
			bool init();
			void destroy();
			void onEnter() { Cell::onEnter(); };
			void onExit() { Cell::onExit(); };
			void setNewColor(const int color);


};

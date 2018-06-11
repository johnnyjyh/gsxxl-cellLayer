#pragma once
#include "Cell.h"

class Plate:public Cell
{
public:
			Plate();
			~Plate();
			static Plate *create(int col, int row, CellColor color);
			void onEnter() { Cell::onEnter(); };
			void onExit() { Cell::onExit(); };
			bool init();
			void destroy();
			void setNewColor(const int color);
			
};


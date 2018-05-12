#pragma once
#include "Cell.h"

class Plate:public Cell
{
public:
			Plate();
			~Plate();
			static Plate *create(int col, int row, PlateColor color);
			
};


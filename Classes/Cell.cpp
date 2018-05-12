#include "Cell.h"




Cell::Cell()
{
}


Cell::~Cell()
{
}

Cell * Cell::create(int col, int row, CellColor color)
{
			auto cell = new (std::nothrow) Cell;
			cell->autorelease();
			return cell;
}

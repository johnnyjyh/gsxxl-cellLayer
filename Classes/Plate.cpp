#include "Plate.h"



Plate::Plate()
{
}


Plate::~Plate()
{
}

Plate * Plate::create(int col, int row, PlateColor color)
{
			auto plate = new (std::nothrow) Plate;
			plate->autorelease();
			return plate;
}

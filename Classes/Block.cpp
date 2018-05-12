#include "Block.h"




Block * Block::create(int col, int row, CellColor color)
{
			auto block = new (std::nothrow) Block;
			block->autorelease();
			return block;
}

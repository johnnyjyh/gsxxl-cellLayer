#pragma once
#include"Block.h"
#include "Plate.h"


class CellLayer:public Layer
{
public:
			CellLayer();
			~CellLayer();
			static CellLayer *create(CellConfiguration config);
			bool init(CellConfiguration config);



			void onEnter();
			void onExit();

			
};


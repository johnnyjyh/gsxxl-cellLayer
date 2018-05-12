#pragma once
#include"Block.h"
#include "Plate.h"


class CellLayer:public Layer
{
public:
			CellLayer();
			~CellLayer();
			static CellLayer *create(const CellConfiguration &config);
			bool init(const CellConfiguration &config);



			void onEnter();
			void onExit();

			
};


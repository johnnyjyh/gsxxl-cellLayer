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

			inline Vec2 coordinateToVec2(int col, int row) const { return Vec2(getSingleTiledSize.x*(col + 0.5), (getSingleTiledSize.y + (tileinterval - 95 * 0.5))*(row + 0.5)); };
			inline int * vec2ToCoordinate(Vec2 vec) const {
						int transformArr[2];
						transformArr[0] = vec.x / getSingleTiledSize.x - 0.5;
						transformArr[1] = vec.y / (getSingleTiledSize.y + (tileinterval - 95 * 0.5)) - 0.5;
						return transformArr;
			};

			void displayAll(const CellConfiguration &config);

			void displayCell(int col,int row,Cell *cell,int orientation);

		

			void restoreAction();
			void restoreStalemate();

			int computeTheOneCell(std::vector<Cell *> &cells, Cell * cellCurrent, int count);
			bool isStalemate();
			
			void addGreyAndLightShader();

			void onEnter();
			void onExit();

			//以下四个继承来的虚函数用于来集成控制函数
			bool onTouchBegan(Touch *touch, Event *unused_event);

			void onTouchMoved(Touch *touch, Event *unused_event);

			void onTouchEnded(Touch *touch, Event *unused_event);

			void onTouchCancelled(Touch *touch, Event *unused_event);


			bool _isCanRunning{ false };
			bool _isTransformPos{ false };

			Cell *_recordCouldDesCell{ nullptr };

			Cell * _cellsLogic[CellConfig_LocalCellCol][CellConfig_LocalCellRow];
			Cell * _plateVertical[CellConfig_PlateVecticalCol][CellConfig_PlateVecticalRow];
			Cell *_plateHorizontal[CellConfig_PlateHorizontalCol][CellConfig_PlateHorizontalRow];
			
};


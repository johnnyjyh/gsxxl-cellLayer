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
						int transformArr[2] = {0,0};
						transformArr[0] = vec.x / getSingleTiledSize.x - 0.5;
						transformArr[1] = vec.y / (getSingleTiledSize.y + (tileinterval - 95 * 0.5)) - 0.5;
						return transformArr;
			};
			inline int getPlayerScore()noexcept { return _playerAcquireScoreForCell; };

			void displayAll(const CellConfiguration &config);

			void displayCell(int col,int row,Cell *cell,int orientation);

			void hintTheUsableCell(Cell *cell);

			void restoreAction();
			void restoreStalemate();

			int computeTheOneCell(std::vector<Cell *> &cells, Cell * cellCurrent, int count);
			bool isStalemate();
			
		
	

			Cell *getCellFromTable(int col, int row) noexcept;

			//核心消除逻辑
			//攻击检测
			void grantAttackTypeForCell();
			void attackFromSource();
			Cell *getVerticalPlate(int col, int row);
			Cell *getHorizontalPlate(int col, int row);
			void attackFromDesCell(Cell *cell);
			//补格子，顶排
			void fillUpCellOnTop();

			void coorVecClear();
			void swapCell(int sourceCol, int sourceRow,int destCol,int destRow);
			void controlDrop();
			void animateControl();
			void dropDownCell();
			void dropLeftCell();
			void dropRightCell();
			void getDrowDownTrackCell(Cell *cell);
			void getDrowLeftTrackCell(Cell *cell);
			void getDrowRightTrackCell(Cell *cell);
			bool cellCanMoveDown(Cell *cell) noexcept;
			bool cellCanMoveLeft(Cell *cell) noexcept;
			bool cellCanMoveRight(Cell *cell) noexcept;

			bool TouchCellCanMoveDown(Cell *cell) noexcept;
			bool TouchCellCanMoveLeft(Cell *cell) noexcept;
			bool TouchCellCanMoveRight(Cell *cell) noexcept;

			Cell *srandColorForNewCell(Cell *cell);


			void destroyAndFillUpCells();
			void destroyCells();
			
			//连线
			void linkLineInGrid(int col1, int row1, int col2, int row2);
			void unLinkLineInGrid(int col1, int row1, int col2, int row2);
			//grey & light shader
			void addGreyAndLightShader();
			void recoverLightCells(CellColor col);
			void showLightCells(CellColor col);

			//item for cells
			void shffuleCellsforMenu();

			void onEnter();
			void onExit();



			//以下四个继承来的虚函数用于来集成控制函数
			bool onTouchBegan(Touch *touch, Event *unused_event);

			void onTouchMoved(Touch *touch, Event *unused_event);

			void onTouchEnded(Touch *touch, Event *unused_event);

			void onTouchCancelled(Touch *touch, Event *unused_event);

		
//数据
			bool _isCanRunning{ false };
			bool _isTransformPos{ false };
			bool _dropDownTransformPos{ false };


			int _stalemateCellCount{ 0 };
			Cell *_recordCouldDesCell{ nullptr };
			int _cellPowerNum{ 0 };
			int _playerAcquireScoreForCell{ 0 };
			int _stepOuterTime{ 0 };
			double _stepWatiTime{ 0.0 };
			Cell * _cellsLogic[CellConfig_LocalCellCol][CellConfig_LocalCellRow];
			Cell * _plateVertical[CellConfig_PlateVecticalCol][CellConfig_PlateVecticalRow];
			Cell *_plateHorizontal[CellConfig_PlateHorizontalCol][CellConfig_PlateHorizontalRow];

			std::vector<Cell *> _touchCells;
			std::vector<Cell *> _touchMoveCells;
			std::list<DrawNode *> _linkLineCache;
			
			class Coor
			{
			public:
						Coor()  {}
						Coor(int col,int row):_SourceCol(col), _SourceRow(row){}
						~Coor()
						{
						}
						int _SourceCol{-1};
						int _SourceRow{-1};
						int _destCol{-1};
						int _destRow{ -1 };
						Cell *_sourceCell{nullptr};
						int _stepsLev{0};
			};
			std::vector<Coor > _cellMoveToCoor;



};


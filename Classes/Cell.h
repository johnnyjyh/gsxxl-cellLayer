#pragma once
#include"CellCommon.h"
class Cell
{
public:
			Cell();
			~Cell();
			static Cell *create(int col,int row,bool usablPlate[4]);




			int _life{0 };
			
			CellColor _color;		
			Sprite *_plate;
			
			CC_SYNTHESIZE(int, _row, Row);
			CC_SYNTHESIZE(int, _column, Column);


			//cell 标记量   
			
			bool _usablePlate[4]{ { false },{ false },{ false },{ false } };// 规定plate 0上，1右，2下，3左
			int _usablePlateHealth[4]{ { 0 },{ 0 },{ 0 },{ 0 } };
			Vec2 _usablePlatePos[4];


};


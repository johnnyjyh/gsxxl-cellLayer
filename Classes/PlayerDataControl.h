#pragma once
#include "GamePlayScene.h"





class PlayerDataControl
{
public:
			PlayerDataControl();
			~PlayerDataControl();
			static PlayerDataControl *getInstance();
			bool init();
			Scene *turnToGamePlayScene();
			void initRandEngine();
			bool loadCellConfigJSon(const std::string filename);
			
			CellConfiguration m_cell_config;//cell config
			DefenseConfiguration m_defense_config;//defense config
			static PlayerDataControl *_instance;

			bool loadAnimate();



		
};

//struct configuration
//{
//			int localCell[7][5];
//			int plateHorizontal[7][6];
//			int plateVectical[8][5];
//};
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
			
			CellConfiguration _config;//cell config
			static PlayerDataControl *_instance;

			bool loadAnimate();



		
};

//struct configuration
//{
//			int localCell[7][5];
//			int plateHorizontal[7][6];
//			int plateVectical[8][5];
//};
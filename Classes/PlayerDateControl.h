#pragma once
#include "GamePlayScene.h"


class PlayerDateControl
{
public:
			PlayerDateControl();
			~PlayerDateControl();
			static PlayerDateControl *getInstance();
			bool init();
			Scene *turnToGamePlayScene();
			void initRandEngine();
			
			CellConfiguration _config;//cell config
			static PlayerDateControl *_instance;
};

//struct configuration
//{
//			int localCell[7][5];
//			int plateHorizontal[7][6];
//			int plateVectical[8][5];
//};
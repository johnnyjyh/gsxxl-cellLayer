#pragma once
#include "GamePlayScene.h"





class PlayerDataControl
{
public:
			PlayerDataControl();
			~PlayerDataControl();
			static PlayerDataControl *getInstance();
			void destroyInstance();
			bool init();
			Scene *turnToGamePlayScene();
			void initRandEngine(const std::string & cellConfigFile,const std::string & defenseConfigFile);
			bool loadCellConfigJSon(const std::string filename);
			bool loadDefenseConfigJSon(const std::string filename);
			void getEventToGameOver(EventCustom *eventCus);
			bool initAnimate();
			
			CellConfiguration m_cell_config;//cell config
			DefenseConfiguration m_defense_config;//defense config
			static PlayerDataControl *_instance;
			EventDispatcher *m_disp{ nullptr };
			bool loadAnimate();



		
};

//struct configuration
//{
//			int localCell[7][5];
//			int plateHorizontal[7][6];
//			int plateVectical[8][5];
//};